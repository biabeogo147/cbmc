#!/usr/bin/env python3
"""Build a benchmark diagnostic inventory from suite manifests and CSV results.

Inputs:
  - check-src/benchmarks/suites/*.json.
  - check-src/benchmarks/results/*.csv.

Outputs:
  - check-src/benchmarks/results/audit/benchmark-inventory.csv by default.

The inventory keeps only one row per logical case. Diagnostic repeats are
collapsed using the stock root, improved root, entry function, properties, and
unwind setting so follow-up correctness work does not double-count reruns.
"""

import argparse
import csv
import hashlib
import json
import sys
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent
TARGET_OUTCOME_GROUPS = {
    "Verification Failed vs Successful",
    "Verification Successful vs Failed",
    "Verification Failed vs Exit 6",
}
NO_INJECTION_SUMMARY = "NO_INJECTION_CANDIDATES"
INVENTORY_FIELDS = [
    "category",
    "suite",
    "case",
    "logical_case_id",
    "stock_root",
    "improved_root",
    "entry_function",
    "properties",
    "unwind",
    "stock_summary",
    "improved_summary",
    "needs_no_injection_audit",
]


if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

import report_benchmark  # noqa: E402


def case_by_name(manifest, case_name):
    """Find one case dictionary in a suite manifest.

    Args:
        manifest: Loaded suite manifest.
        case_name: Case name to find.

    Returns:
        Case dictionary.

    Raises:
        KeyError: If the case is missing from the manifest.
    """
    for case in manifest.get("cases", []):
        if case.get("name") == case_name:
            return case
    raise KeyError(f"{manifest.get('suite_name', '<unknown>')} missing case {case_name}")


def variant_root(case, variant):
    """Return the source root for one case variant.

    Args:
        case: Loaded case dictionary.
        variant: Variant name.

    Returns:
        Source root string from variant_roots or root fallback.
    """
    return case.get("variant_roots", {}).get(variant, case.get("root", ""))


def selected_properties(case):
    """Return a stable property-list string for deduplication and CSV output.

    Args:
        case: Loaded case dictionary.

    Returns:
        JSON string containing the selected CBMC properties.
    """
    return json.dumps(case.get("properties", []), sort_keys=True, separators=(",", ":"))


def logical_key(case):
    """Return the semantic identity key used to collapse diagnostic repeats.

    Args:
        case: Loaded case dictionary.

    Returns:
        Tuple containing source roots, entry function, selected properties, and
        unwind.
    """
    return (
        variant_root(case, "stock_cprover_async"),
        variant_root(case, "improved_pipeline"),
        case.get("entry_function", ""),
        selected_properties(case),
        str(case.get("unwind", "")),
    )


def logical_case_id(key):
    """Build a short stable id for one logical case key.

    Args:
        key: Tuple returned by logical_key().

    Returns:
        Human-readable stable id with a sha1 suffix.
    """
    digest = hashlib.sha1("\0".join(key).encode("utf-8")).hexdigest()[:12]
    improved_root = key[1].replace("\\", "/").rstrip("/")
    case_name = improved_root.split("/")[-2] if improved_root.endswith("/improved-pipeline") else improved_root.split("/")[-1]
    return f"{case_name}-{digest}"


def phase_summary(phases, suite, case, variant):
    """Return the verification or injection summary for one variant.

    Args:
        phases: Summarized benchmark phases from report_benchmark.summarize().
        suite: Suite name.
        case: Case name.
        variant: Variant name.

    Returns:
        Compact summary string for the variant.
    """
    phase_items = report_benchmark.phase_set(phases, suite, case, variant)
    for item in phase_items.values():
        if NO_INJECTION_SUMMARY in item.get("summary", ""):
            return report_benchmark.display_summary(item)
    verify = phase_items.get("verify")
    if verify:
        return report_benchmark.display_summary(verify)
    inject = phase_items.get("inject")
    if inject:
        return report_benchmark.display_summary(inject)
    if phase_items:
        first = next(iter(phase_items.values()))
        return report_benchmark.display_summary(first)
    return ""


def has_no_injection_summary(phases, suite, case):
    """Return whether the improved variant reported no injection candidates.

    Args:
        phases: Summarized benchmark phases from report_benchmark.summarize().
        suite: Suite name.
        case: Case name.

    Returns:
        True when any improved phase summary contains NO_INJECTION_CANDIDATES.
    """
    improved = report_benchmark.phase_set(phases, suite, case, "improved_pipeline")
    return any(NO_INJECTION_SUMMARY in item.get("summary", "") for item in improved.values())


def canonical_rank(candidate):
    """Rank duplicate candidates so the best evidence row becomes canonical.

    Args:
        candidate: Inventory row dictionary.

    Returns:
        Sort tuple. Lower values are preferred.
    """
    suite = candidate["suite"]
    return (
        0 if "logger-stable" in suite else 1,
        0 if "highmem" in suite else 1,
        0 if not suite.endswith("timeout-30m") else 1,
        suite,
        candidate["case"],
    )


def collect_inventory(repo_root, suite_dir, results_dir):
    """Collect deduplicated benchmark diagnostic inventory rows.

    Args:
        repo_root: Repository root path. Kept for call-site symmetry.
        suite_dir: Directory containing suite JSON manifests.
        results_dir: Directory containing benchmark CSV files.

    Returns:
        Deduplicated list of inventory dictionaries sorted by category/suite/case.
    """
    del repo_root
    manifests = report_benchmark.load_manifests(Path(suite_dir))
    rows = report_benchmark.load_rows(Path(results_dir))
    phases = report_benchmark.summarize(rows)
    names = report_benchmark.suite_case_names(rows, manifests)
    grouped = {}

    for suite in sorted(names):
        manifest = manifests.get(suite)
        if not manifest:
            continue
        for case_name in names[suite]:
            case = case_by_name(manifest, case_name)
            stock, improved, is_comparable, _ = report_benchmark.case_comparison_status(
                phases, suite, case_name, manifest
            )
            if is_comparable:
                continue
            category = report_benchmark.diagnostic_category(stock, improved)
            include = category in TARGET_OUTCOME_GROUPS or has_no_injection_summary(phases, suite, case_name)
            if not include:
                continue
            stock_root, improved_root, entry_function, properties, unwind = logical_key(case)
            key = (stock_root, improved_root, entry_function, properties, unwind)
            candidate = {
                "category": category,
                "suite": suite,
                "case": case_name,
                "logical_case_id": logical_case_id(key),
                "stock_root": stock_root,
                "improved_root": improved_root,
                "entry_function": entry_function,
                "properties": properties,
                "unwind": unwind,
                "stock_summary": phase_summary(phases, suite, case_name, "stock_cprover_async"),
                "improved_summary": phase_summary(phases, suite, case_name, "improved_pipeline"),
                "needs_no_injection_audit": str(has_no_injection_summary(phases, suite, case_name)).lower(),
            }
            existing = grouped.get(key)
            if not existing or canonical_rank(candidate) < canonical_rank(existing):
                grouped[key] = candidate

    return sorted(grouped.values(), key=lambda row: (row["category"], row["suite"], row["case"]))


def write_inventory(rows, output_path):
    """Write inventory rows to CSV.

    Args:
        rows: Inventory dictionaries.
        output_path: Destination CSV path.

    Returns:
        None.
    """
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", newline="", encoding="utf-8") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=INVENTORY_FIELDS)
        writer.writeheader()
        writer.writerows(rows)


def main(argv=None):
    """CLI entry point.

    Args:
        argv: Optional command-line arguments.

    Returns:
        Process exit code.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=REPO_ROOT)
    parser.add_argument("--suite-dir", default=None)
    parser.add_argument("--results-dir", default=None)
    parser.add_argument("--out", default=None)
    parser.add_argument("--inventory-only", action="store_true")
    args = parser.parse_args(argv)

    repo_root = Path(args.repo_root).resolve()
    suite_dir = Path(args.suite_dir) if args.suite_dir else repo_root / "check-src" / "benchmarks" / "suites"
    results_dir = Path(args.results_dir) if args.results_dir else repo_root / "check-src" / "benchmarks" / "results"
    output_path = (
        Path(args.out)
        if args.out
        else repo_root / "check-src" / "benchmarks" / "results" / "audit" / "benchmark-inventory.csv"
    )
    inventory = collect_inventory(repo_root, suite_dir, results_dir)
    write_inventory(inventory, output_path)
    print(f"inventory rows: {len(inventory)}")
    print(f"inventory: {output_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
