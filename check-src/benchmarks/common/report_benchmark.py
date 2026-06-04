#!/usr/bin/env python3
"""Generate benchmark Markdown reports from raw suite CSV files.

Inputs:
  - CSV files from check-src/benchmarks/results/*.csv.
  - Suite manifests from check-src/benchmarks/suites/*.json.
  - Optional source inventory table from check-src/benchmark-sources/INVENTORY.md.

Outputs:
  - check-src/benchmark.md for comparable cases by default, or --out <path>.
  - check-src/uncomparable.md for cases that cannot be compared, or
    --uncomparable-out <path>.

The report summarizes measured rows only; warmup rows are ignored. It reports
median phase time and peak RSS, then decides whether stock and improved results
are comparable before printing speed/RAM deltas.
"""

import argparse
import csv
import json
from collections import defaultdict
from datetime import datetime, timezone
from pathlib import Path
from statistics import median


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent

VARIANT_LABELS = {
    "stock_cprover_async": "Stock CPROVER async",
    "improved_pipeline": "Improved pipeline",
}
MEASURED_PHASES = {"compile", "verify", "manifest", "inject"}
STOCK_PHASES = ["compile", "verify"]
IMPROVED_PHASES = ["manifest", "inject", "compile", "verify"]
STOCK_VARIANTS = {"stock_cprover_async"}
IMPROVED_VARIANTS = {"improved_pipeline"}
UNCOMPARABLE_CATEGORY_ORDER = [
    "Verification Failed vs Successful",
    "Verification Successful vs Failed",
    "Verification Failed vs Exit 6",
    "CBMC Unsupported Concurrency",
    "Stock Timeout",
    "Improved Timeout",
    "Stock Memory Limit",
    "Improved Memory Limit",
    "No Injection Candidates",
    "Missing Variant Results",
    "Not Run / Disabled Cases",
    "Other Verification Outcome Mismatches",
]


def load_manifests(suite_dir):
    """Load suite JSON files keyed by suite_name.

    Args:
        suite_dir: Directory containing suite manifest JSON files.

    Returns:
        Dictionary mapping suite_name to loaded manifest dictionaries.
    """
    manifests = {}
    for path in sorted(suite_dir.glob("*.json")):
        try:
            manifest = json.loads(path.read_text(encoding="utf-8"))
        except json.JSONDecodeError:
            continue
        manifests[manifest.get("suite_name", path.stem)] = manifest
    return manifests


def load_rows(results_dir):
    """Load raw CSV rows and drop warmup rows from report calculations.

    Args:
        results_dir: Directory containing raw benchmark CSV files.

    Returns:
        List of CSV rows as dictionaries. Warmup rows are excluded.
    """
    rows = []
    for path in sorted(results_dir.glob("*.csv")):
        with path.open(newline="", encoding="utf-8", errors="replace") as csv_file:
            reader = csv.DictReader(csv_file)
            for row in reader:
                row["_csv"] = path.name
                if not row.get("run_kind"):
                    row["run_kind"] = "measure"
                if row["run_kind"] == "warmup":
                    continue
                rows.append(row)
    return rows


def summary_class(summary, exit_code):
    """Map log summary text and exit code to a comparable outcome class.

    Args:
        summary: Summary text extracted from a command log.
        exit_code: Recorded command exit code.

    Returns:
        Normalized outcome class such as success, failed, unsupported, timeout,
        memory_limit, exit_<code>, or ok.
    """
    text = (summary or "").strip()
    if "CBMC_UNSUPPORTED_CONCURRENCY" in text:
        return "unsupported"
    if "TIMEOUT_AFTER_" in text:
        return "timeout"
    if "MEMORY_LIMIT_EXCEEDED_" in text:
        return "memory_limit"
    if "VERIFICATION SUCCESSFUL" in text:
        return "success"
    if "VERIFICATION FAILED" in text:
        return "failed"
    if str(exit_code) not in {"", "0"}:
        return f"exit_{exit_code}"
    return "ok"


def display_summary(item):
    """Return the report-facing summary string for one phase item.

    Args:
        item: Phase statistics dictionary.

    Returns:
        Explicit summary when present, OK for zero exit, or EXIT_<code>.
    """
    summary = item["summary"]
    if summary:
        return summary
    if str(item["exit_code"]) == "0":
        return "OK"
    return f"EXIT_{item['exit_code']}"


def summarize(rows):
    """Bucket rows by suite/case/variant/phase and compute medians.

    Args:
        rows: Measured CSV rows.

    Returns:
        Dictionary keyed by (suite, case, variant, phase) with median time,
        median RSS, exit code, summary, and run count.
    """
    buckets = defaultdict(list)
    for row in rows:
        if row.get("phase") not in MEASURED_PHASES:
            continue
        key = (row["benchmark"], row["case"], row["variant"], row["phase"])
        buckets[key].append(row)

    phases = {}
    for key, items in buckets.items():
        times = [float(item.get("time_ms") or 0) for item in items]
        rss = [float(item.get("max_rss_mb") or 0) for item in items]
        last = items[-1]
        phases[key] = {
            "time_ms": int(median(times)),
            "rss_mb": median(rss),
            "exit_code": last.get("exit_code", ""),
            "summary": last.get("summary", ""),
            "runs": len(items),
        }
    return phases


def phase_set(phases, suite, case, variant):
    """Return all available phase summaries for one case variant.

    Args:
        phases: Summarized phase dictionary from summarize().
        suite: Suite name.
        case: Case name.
        variant: Variant name.

    Returns:
        Dictionary mapping phase name to phase statistics.
    """
    return {
        phase: phases[(suite, case, variant, phase)]
        for phase in MEASURED_PHASES
        if (suite, case, variant, phase) in phases
    }


def variant_phases(variant):
    """Return the expected phase order for a variant.

    Args:
        variant: Variant name.

    Returns:
        Ordered phase list for report display and total-time calculation.
    """
    if variant in IMPROVED_VARIANTS:
        return IMPROVED_PHASES
    return STOCK_PHASES


def comparison_variants(manifest):
    """Resolve stock and improved variants from a suite manifest.

    Args:
        manifest: Loaded suite manifest, or None.

    Returns:
        Tuple of stock variant name and improved variant name.
    """
    variants = list((manifest or {}).get("variants") or [])
    stock = next((variant for variant in variants if variant in STOCK_VARIANTS), "stock_cprover_async")
    improved = next((variant for variant in variants if variant in IMPROVED_VARIANTS), "improved_pipeline")
    return stock, improved


def total_time(phase_stats, ordered_phases):
    """Sum median time across selected phases.

    Args:
        phase_stats: Phase statistics for one variant.
        ordered_phases: Phases to include in the total.

    Returns:
        Total median time in milliseconds.
    """
    return sum(phase_stats[phase]["time_ms"] for phase in ordered_phases if phase in phase_stats)


def peak_rss(phase_stats):
    """Return the maximum median RSS across phases.

    Args:
        phase_stats: Phase statistics for one variant.

    Returns:
        Peak median RSS in MiB, or 0.0 when no phases exist.
    """
    if not phase_stats:
        return 0.0
    return max(item["rss_mb"] for item in phase_stats.values())


def verify_class(phase_stats):
    """Return the normalized verification outcome for one variant.

    Args:
        phase_stats: Phase statistics for one variant.

    Returns:
        Verification outcome class, or missing_verify when no verify phase exists.
    """
    if "verify" not in phase_stats:
        return "missing_verify"
    item = phase_stats["verify"]
    return summary_class(item["summary"], item["exit_code"])


def comparable(stock_stats, improved_stats):
    """Return whether the report may print speed/RAM percentage deltas.

    Args:
        stock_stats: Phase statistics for the stock variant.
        improved_stats: Phase statistics for the improved variant.

    Returns:
        Tuple of (is_comparable, reason_text).
    """
    stock_verify = verify_class(stock_stats)
    improved_verify = verify_class(improved_stats)
    if stock_verify == "memory_limit":
        return False, "Not comparable: stock verification hit the memory limit."
    if improved_verify == "memory_limit":
        return False, "Not comparable: improved verification hit the memory limit."
    if stock_verify == "timeout":
        return False, "Not comparable: stock verification hit the timeout."
    if improved_verify == "timeout":
        return False, "Not comparable: improved verification hit the timeout."
    for item in improved_stats.values():
        if item.get("summary") == "NO_INJECTION_CANDIDATES":
            return False, "Not comparable: improved variant had no injection candidates."
    if stock_verify == "unsupported":
        return False, "Not comparable: stock CBMC reports unsupported concurrency."
    if stock_verify.startswith("missing") or improved_verify.startswith("missing"):
        return False, "Not comparable: one variant has no verification result."
    if stock_verify != improved_verify:
        return False, f"Not comparable: verification outcomes differ ({stock_verify} vs {improved_verify})."
    return True, "Comparable: both variants reached the same verification outcome."


def percent_delta(stock_value, improved_value, lower_is_better=True):
    """Format a percent difference between stock and improved values.

    Args:
        stock_value: Baseline numeric value.
        improved_value: Improved variant numeric value.
        lower_is_better: Whether smaller values indicate improvement.

    Returns:
        Human-readable percentage delta string.
    """
    if stock_value == 0:
        return "n/a"
    delta = (stock_value - improved_value) / stock_value * 100
    if lower_is_better:
        if delta >= 0:
            return f"improved is {delta:.1f}% faster"
        return f"improved is {-delta:.1f}% slower"
    if delta >= 0:
        return f"improved uses {delta:.1f}% less RAM"
    return f"improved uses {-delta:.1f}% more RAM"


def suite_case_names(rows, manifests):
    """Collect all case names that should appear in the report.

    Args:
        rows: Measured CSV rows.
        manifests: Loaded suite manifests.

    Returns:
        Dictionary mapping suite name to sorted case name list.
    """
    names = defaultdict(set)
    for row in rows:
        names[row["benchmark"]].add(row["case"])
    for suite, manifest in manifests.items():
        for case in manifest.get("cases", []):
            names[suite].add(case["name"])
    return {suite: sorted(cases) for suite, cases in names.items()}


def compile_loc(case, manifest=None):
    """Estimate enabled compile LOC for suite readiness reporting.

    Args:
        case: Loaded case dictionary.
        manifest: Optional loaded suite manifest for variant information.

    Returns:
        Maximum compile LOC across variants for the case.
    """
    totals = []
    variants = list((manifest or {}).get("variants") or ["default"])
    variant_roots = case.get("variant_roots") or {}
    variant_sources = case.get("variant_sources") or {}
    for variant in variants:
        total = 0
        root = REPO_ROOT / variant_roots.get(variant, case.get("root", ""))
        sources = variant_sources.get(variant, case.get("sources", []))
        for source in sources:
            path = root / source
            if path.exists():
                total += len(path.read_text(errors="ignore").splitlines())
        totals.append(total)
    return max(totals) if totals else 0


def suite_readiness(manifest):
    """Compute report readiness metadata for a suite.

    Args:
        manifest: Loaded suite manifest.

    Returns:
        Tuple of staged case count, enabled case count, enabled compile LOC, and
        headline-readiness boolean.
    """
    cases = manifest.get("cases", [])
    enabled = [case for case in cases if case.get("enabled", True)]
    enabled_loc = sum(compile_loc(case, manifest) for case in enabled)
    staged = len(cases)
    ready = bool(manifest.get("enabled", False)) and (len(enabled) >= 5 or enabled_loc >= 5000)
    return staged, len(enabled), enabled_loc, ready


def case_comparison_status(phases, suite, case, manifest):
    """Classify whether one case is comparable.

    Args:
        phases: Summarized phase dictionary from summarize().
        suite: Suite name.
        case: Case name.
        manifest: Loaded suite manifest.

    Returns:
        Tuple of stock phase stats, improved phase stats, comparable boolean,
        and reason text.
    """
    stock_variant, improved_variant = comparison_variants(manifest)
    stock = phase_set(phases, suite, case, stock_variant)
    improved = phase_set(phases, suite, case, improved_variant)
    if not stock and not improved:
        case_config = next(
            (item for item in (manifest or {}).get("cases", []) if item.get("name") == case),
            {},
        )
        if case_config.get("enabled", True) is False:
            disabled_reason = case_config.get("reason", "Case is disabled in the suite manifest.")
            return stock, improved, False, f"Not run: {disabled_reason}"
        return stock, improved, False, "No measured CSV rows are available yet."
    if not stock or not improved:
        return stock, improved, False, "Not comparable: one variant has no measured CSV rows."
    is_comparable, reason = comparable(stock, improved)
    return stock, improved, is_comparable, reason


def uncomparable_category(stock, improved):
    """Return the report category for one non-comparable case.

    Args:
        stock: Stock variant phase statistics.
        improved: Improved variant phase statistics.

    Returns:
        Stable human-readable category used to group uncomparable cases.
    """
    if not stock and not improved:
        return "Not Run / Disabled Cases"
    if not stock or not improved:
        return "Missing Variant Results"

    stock_verify = verify_class(stock)
    improved_verify = verify_class(improved)
    if stock_verify == "memory_limit":
        return "Stock Memory Limit"
    if improved_verify == "memory_limit":
        return "Improved Memory Limit"
    if stock_verify == "timeout":
        return "Stock Timeout"
    if improved_verify == "timeout":
        return "Improved Timeout"
    if any(item.get("summary") == "NO_INJECTION_CANDIDATES" for item in improved.values()):
        return "No Injection Candidates"
    if stock_verify == "unsupported":
        return "CBMC Unsupported Concurrency"
    if stock_verify.startswith("missing") or improved_verify.startswith("missing"):
        return "Missing Variant Results"
    if stock_verify == "failed" and improved_verify == "success":
        return "Verification Failed vs Successful"
    if stock_verify == "success" and improved_verify == "failed":
        return "Verification Successful vs Failed"
    if stock_verify == "failed" and improved_verify == "exit_6":
        return "Verification Failed vs Exit 6"
    return "Other Verification Outcome Mismatches"


def append_case(lines, suite, case, phases, manifest, headline_ready, heading_level=3):
    """Append one case section with phase tables and comparison status.

    Args:
        lines: Markdown line buffer to mutate.
        suite: Suite name.
        case: Case name.
        phases: Summarized phase dictionary from summarize().
        manifest: Loaded suite manifest.
        headline_ready: Whether speed/RAM deltas may be headline results.
        heading_level: Markdown heading level for the case name.

    Returns:
        True when the case is comparable, otherwise False.
    """
    stock_variant, improved_variant = comparison_variants(manifest)
    stock, improved, is_comparable, reason = case_comparison_status(phases, suite, case, manifest)
    heading = "#" * heading_level
    if not stock and not improved:
        lines.append(f"{heading} {case}")
        lines.append("")
        lines.append(reason)
        lines.append("")
        return False

    lines.append(f"{heading} {case}")
    lines.append("")
    lines.append("| Variant | Phase | Runs | Exit | Median time (ms) | Peak RSS (MB) | Summary |")
    lines.append("| --- | --- | ---: | ---: | ---: | ---: | --- |")
    for variant in [stock_variant, improved_variant]:
        stats = phase_set(phases, suite, case, variant)
        for phase in variant_phases(variant):
            if phase not in stats:
                continue
            item = stats[phase]
            summary = display_summary(item)
            lines.append(
                f"| {VARIANT_LABELS.get(variant, variant)} | {phase} | {item['runs']} | {item['exit_code']} | "
                f"{item['time_ms']} | {item['rss_mb']:.1f} | `{summary}` |"
            )
    lines.append("")

    if stock and improved:
        lines.append(reason)
        lines.append("")
        stock_total = total_time(stock, variant_phases(stock_variant))
        improved_total = total_time(improved, variant_phases(improved_variant))
        stock_peak = peak_rss(stock)
        improved_peak = peak_rss(improved)
        lines.append("| Metric | Stock | Improved | Difference |")
        lines.append("| --- | ---: | ---: | --- |")
        if not is_comparable:
            lines.append(f"| Full measured time | {stock_total} ms | {improved_total} ms | Not reported for not-comparable verification outcomes. |")
            lines.append(f"| Peak RSS | {stock_peak:.1f} MB | {improved_peak:.1f} MB | Not reported for not-comparable verification outcomes. |")
        elif not headline_ready:
            lines.append(
                f"| Full measured time | {stock_total} ms | {improved_total} ms | Not reported because the suite is not headline-ready. |"
            )
            lines.append(
                f"| Peak RSS | {stock_peak:.1f} MB | {improved_peak:.1f} MB | Not reported because the suite is not headline-ready. |"
            )
        else:
            lines.append(
                f"| Full measured time | {stock_total} ms | {improved_total} ms | {percent_delta(stock_total, improved_total)} |"
            )
            lines.append(
                f"| Peak RSS | {stock_peak:.1f} MB | {improved_peak:.1f} MB | {percent_delta(stock_peak, improved_peak, False)} |"
            )
        lines.append("")
    elif reason:
        lines.append(reason)
        lines.append("")
    return is_comparable


def build_report(rows, phases, manifests, report_kind="comparable"):
    """Compose the full Markdown report as a string.

    Args:
        rows: Measured CSV rows.
        phases: Summarized phase dictionary from summarize().
        manifests: Loaded suite manifests.
        report_kind: Either comparable or uncomparable.

    Returns:
        Complete Markdown report text.
    """
    comparable_report = report_kind == "comparable"
    title = "ISR Comparable Benchmark Results" if comparable_report else "ISR Uncomparable Benchmark Results"
    scope = (
        "This file contains cases whose stock and improved verification outcomes are comparable."
        if comparable_report
        else "This file contains cases that cannot be compared directly."
    )
    lines = [
        f"# {title}",
        "",
        f"Generated: {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M:%S UTC')}",
        "",
        "This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.",
        "Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.",
        scope,
        "",
        "Comparison labels: Stock CPROVER async, Improved pipeline, Comparable, Not comparable, Median, Peak RSS.",
        "",
        "## Source Inventory",
        "",
    ]
    inventory = REPO_ROOT / "check-src" / "benchmark-sources" / "INVENTORY.md"
    if inventory.exists():
        inventory_lines = inventory.read_text(encoding="utf-8", errors="replace").splitlines()
        table = [line for line in inventory_lines if line.startswith("|")]
        lines.extend(table)
    else:
        lines.append("`check-src/benchmark-sources/INVENTORY.md` has not been generated yet.")
    lines.append("")

    lines.append("## Suite Readiness")
    lines.append("")
    lines.append("| Suite | Manifest enabled | Staged cases | Enabled cases | Enabled compile LOC | Headline-ready |")
    lines.append("| --- | --- | ---: | ---: | ---: | --- |")
    readiness_manifests = manifests.items()
    if comparable_report:
        readiness_manifests = (
            (suite, manifest)
            for suite, manifest in manifests.items()
            if manifest.get("enabled", False)
        )
    for suite, manifest in sorted(readiness_manifests):
        staged, enabled, loc, ready = suite_readiness(manifest)
        headline = "yes" if ready else "no"
        lines.append(
            f"| `{suite}` | {str(manifest.get('enabled', False)).lower()} | {staged} | {enabled} | {loc} | {headline} |"
        )
    lines.append("")

    names = suite_case_names(rows, manifests)
    appended_cases = 0
    if comparable_report:
        for suite in sorted(names):
            manifest = manifests.get(suite)
            headline_ready = True
            if manifest:
                _, _, _, headline_ready = suite_readiness(manifest)
            case_lines = []
            suite_case_count = 0
            for case in names[suite]:
                _, _, is_comparable, _ = case_comparison_status(phases, suite, case, manifest)
                if not is_comparable:
                    continue
                suite_case_count += 1
                appended_cases += 1
                append_case(case_lines, suite, case, phases, manifest, headline_ready)
            if suite_case_count == 0:
                continue
            lines.extend([f"## {suite}", ""])
            lines.extend(case_lines)
    else:
        grouped = defaultdict(lambda: defaultdict(list))
        for suite in sorted(names):
            manifest = manifests.get(suite)
            for case in names[suite]:
                stock, improved, is_comparable, _ = case_comparison_status(phases, suite, case, manifest)
                if is_comparable:
                    continue
                category = uncomparable_category(stock, improved)
                grouped[category][suite].append(case)
                appended_cases += 1

        lines.extend(["## Uncomparable Summary", ""])
        lines.append("| Reason | Cases |")
        lines.append("| --- | ---: |")
        for category in UNCOMPARABLE_CATEGORY_ORDER:
            count = sum(len(cases) for cases in grouped.get(category, {}).values())
            lines.append(f"| {category} | {count} |")
        lines.append("")

        for category in UNCOMPARABLE_CATEGORY_ORDER:
            suites = grouped.get(category)
            if not suites:
                continue
            lines.extend([f"## {category}", ""])
            for suite in sorted(suites):
                manifest = manifests.get(suite)
                headline_ready = True
                if manifest:
                    _, _, _, headline_ready = suite_readiness(manifest)
                lines.extend([f"### {suite}", ""])
                if manifest and not manifest.get("enabled", False):
                    lines.append(
                        "Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed."
                    )
                    lines.append("")
                for case in suites[suite]:
                    append_case(
                        lines,
                        suite,
                        case,
                        phases,
                        manifest,
                        headline_ready,
                        heading_level=4,
                    )

    if not rows:
        lines.append("No CSV rows were loaded.")
        lines.append("")
    elif appended_cases == 0:
        lines.append("No cases matched this report scope.")
        lines.append("")
    return "\n".join(lines) + "\n"


def main(argv=None):
    """CLI entry point for benchmark Markdown report generation.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--results-dir", default=BENCHMARK_DIR / "results")
    parser.add_argument("--suite-dir", default=BENCHMARK_DIR / "suites")
    parser.add_argument("--out", default=REPO_ROOT / "check-src" / "benchmark.md")
    parser.add_argument("--uncomparable-out", default=REPO_ROOT / "check-src" / "uncomparable.md")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args(argv)

    rows = load_rows(Path(args.results_dir))
    manifests = load_manifests(Path(args.suite_dir))
    phases = summarize(rows)
    comparable_report = build_report(rows, phases, manifests, "comparable")
    uncomparable_report = build_report(rows, phases, manifests, "uncomparable")
    print(f"report rows loaded: {len(rows)}")
    if args.dry_run:
        return 0
    out = Path(args.out)
    uncomparable_out = Path(args.uncomparable_out)
    out.write_text(comparable_report, encoding="utf-8")
    uncomparable_out.write_text(uncomparable_report, encoding="utf-8")
    print(f"report: {out}")
    print(f"uncomparable report: {uncomparable_out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
