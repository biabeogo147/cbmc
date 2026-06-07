#!/usr/bin/env python3
"""Rerun one benchmark case into an isolated audit evidence directory.

Inputs:
  - A suite manifest path from check-src/benchmarks/suites.
  - A case name and optional variant selection.

Outputs:
  - CSV rows under check-src/benchmarks/results/audit.
  - Command logs and copied source trees under check-src/benchmarks/work/audit.
  - Evidence metadata at check-src/benchmarks/results/audit/evidence-metadata.csv.

This wrapper creates a temporary one-case manifest and invokes runner.py. It is
for correctness audit evidence only; it must not overwrite headline benchmark
CSV files under check-src/benchmarks/results.
"""

import argparse
import csv
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent
RUNNER = SCRIPT_DIR / "runner.py"
EVIDENCE_FIELDS = [
    "logical_case_id",
    "suite",
    "case",
    "variant",
    "phase",
    "exit_code",
    "summary",
    "log_path",
    "trace_path",
    "verdict_hint",
]


if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

import benchmark_inventory  # noqa: E402


def load_manifest(path):
    """Load a suite manifest JSON file.

    Args:
        path: Manifest JSON path.

    Returns:
        Loaded manifest dictionary.
    """
    return json.loads(path.read_text(encoding="utf-8"))


def find_case(manifest, case_name):
    """Find one case in a manifest.

    Args:
        manifest: Loaded suite manifest.
        case_name: Case name to select.

    Returns:
        Matching case dictionary.

    Raises:
        SystemExit: If the case is missing.
    """
    for case in manifest.get("cases", []):
        if case.get("name") == case_name:
            return case
    raise SystemExit(f"case not found in {manifest.get('suite_name', '<unknown>')}: {case_name}")


def append_unique(items, values):
    """Append values that are not already present.

    Args:
        items: Mutable list of command-line arguments.
        values: Values to append.

    Returns:
        None.
    """
    for value in values:
        if value not in items:
            items.append(value)


def cbmc_supports_json_ui(cbmc_path):
    """Check whether a CBMC binary advertises --json-ui.

    Args:
        cbmc_path: CBMC executable path.

    Returns:
        True when --json-ui appears in the help text; otherwise False.
    """
    try:
        result = subprocess.run(
            [str(cbmc_path), "--help"],
            stdout=subprocess.PIPE,
            stderr=subprocess.STDOUT,
            text=True,
            errors="replace",
            timeout=10,
            check=False,
        )
    except (OSError, subprocess.TimeoutExpired):
        return False
    return "--json-ui" in result.stdout


def trace_args(enable_trace, enable_json_ui):
    """Return CBMC arguments for evidence reruns.

    Args:
        enable_trace: Whether to request counterexample trace output.
        enable_json_ui: Whether to request JSON UI output.

    Returns:
        List of CBMC arguments.
    """
    args = []
    if enable_trace:
        args.extend(["--trace", "--stop-on-fail"])
    if enable_json_ui:
        args.append("--json-ui")
    return args


def build_evidence_manifest(manifest, case_name, suite_name, enable_trace, enable_json_ui):
    """Create a one-case manifest for an evidence rerun.

    Args:
        manifest: Loaded original manifest.
        case_name: Case to keep enabled.
        suite_name: Temporary evidence suite name.
        enable_trace: Whether to add trace arguments.
        enable_json_ui: Whether to add --json-ui.

    Returns:
        Tuple of evidence manifest and selected original case dictionary.
    """
    selected = find_case(manifest, case_name)
    evidence_manifest = dict(manifest)
    evidence_manifest["suite_name"] = suite_name
    evidence_manifest["enabled"] = True
    case_copy = json.loads(json.dumps(selected))
    case_copy["enabled"] = True
    append_unique(case_copy.setdefault("cbmc_args", []), trace_args(enable_trace, enable_json_ui))
    evidence_manifest["cases"] = [case_copy]
    return evidence_manifest, selected


def write_manifest(manifest, work_dir):
    """Write an evidence manifest under the audit work directory.

    Args:
        manifest: Evidence manifest dictionary.
        work_dir: Audit work directory.

    Returns:
        Path to the written manifest.
    """
    manifest_dir = work_dir / "evidence_manifests"
    manifest_dir.mkdir(parents=True, exist_ok=True)
    path = manifest_dir / f"{manifest['suite_name']}.json"
    path.write_text(json.dumps(manifest, indent=2) + "\n", encoding="utf-8")
    return path


def log_path_for(work_dir, suite_name, row):
    """Return the log path produced by runner.py for a CSV row.

    Args:
        work_dir: Audit work directory.
        suite_name: Evidence suite name.
        row: Runner CSV row.

    Returns:
        Expected log path as a string, or an empty string for prepare rows.
    """
    if row.get("run_kind") == "prepare":
        return ""
    name = ".".join(
        [
            suite_name,
            row["case"],
            row["variant"],
            row["phase"],
            row.get("run_kind", "measure"),
            row.get("run", "1"),
        ]
    )
    return str(work_dir / "logs" / f"{name}.log")


def verdict_hint(summary, exit_code):
    """Return a coarse hint from one phase summary.

    Args:
        summary: Runner summary text.
        exit_code: Runner exit code.

    Returns:
        Hint string used in evidence metadata.
    """
    if "VERIFICATION FAILED" in summary:
        return "counterexample"
    if "VERIFICATION SUCCESSFUL" in summary:
        return "proof"
    if "NO_INJECTION_CANDIDATES" in summary:
        return "no_injection_candidates"
    if str(exit_code) not in {"", "0"}:
        return f"exit_{exit_code}"
    return "ok"


def append_metadata(csv_path, metadata_path, original_suite, logical_case_id, work_dir, trace_enabled):
    """Append evidence metadata rows for one runner CSV.

    Args:
        csv_path: Runner CSV produced by the evidence suite.
        metadata_path: Destination metadata CSV.
        original_suite: Original suite name before evidence renaming.
        logical_case_id: Stable logical case id.
        work_dir: Audit work directory.
        trace_enabled: Whether trace output was requested.

    Returns:
        Number of metadata rows appended.
    """
    metadata_path.parent.mkdir(parents=True, exist_ok=True)
    exists = metadata_path.exists()
    count = 0
    suite_name = csv_path.stem
    with csv_path.open(newline="", encoding="utf-8", errors="replace") as source, metadata_path.open(
        "a", newline="", encoding="utf-8"
    ) as target:
        reader = csv.DictReader(source)
        writer = csv.DictWriter(target, fieldnames=EVIDENCE_FIELDS)
        if not exists:
            writer.writeheader()
        for row in reader:
            if row.get("run_kind") == "warmup":
                continue
            log_path = log_path_for(work_dir, suite_name, row)
            trace_path = log_path if trace_enabled and row.get("phase") == "verify" else ""
            writer.writerow(
                {
                    "logical_case_id": logical_case_id,
                    "suite": original_suite,
                    "case": row["case"],
                    "variant": row["variant"],
                    "phase": row["phase"],
                    "exit_code": row["exit_code"],
                    "summary": row.get("summary", ""),
                    "log_path": log_path,
                    "trace_path": trace_path,
                    "verdict_hint": verdict_hint(row.get("summary", ""), row.get("exit_code", "")),
                }
            )
            count += 1
    return count


def run_runner(manifest_path, case_name, variant, results_dir, work_dir):
    """Invoke runner.py for the evidence manifest.

    Args:
        manifest_path: Temporary evidence manifest path.
        case_name: Case to run.
        variant: Variant selection, or both.
        results_dir: Audit results directory.
        work_dir: Audit work directory.

    Returns:
        CompletedProcess from subprocess.run().
    """
    env = os.environ.copy()
    env["RESULTS_DIR"] = str(results_dir)
    env["WORK"] = str(work_dir)
    command = [sys.executable, str(RUNNER), str(manifest_path), "--case", case_name]
    if variant != "both":
        command.extend(["--variant", variant])
    return subprocess.run(command, env=env, check=False)


def main(argv=None):
    """CLI entry point.

    Args:
        argv: Optional command-line arguments.

    Returns:
        Process exit code.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--suite", required=True)
    parser.add_argument("--case", required=True)
    parser.add_argument("--variant", choices=["stock_cprover_async", "improved_pipeline", "both"], default="both")
    parser.add_argument("--trace", action="store_true")
    parser.add_argument("--json-ui", action="store_true")
    parser.add_argument("--results-dir", default=BENCHMARK_DIR / "results" / "audit")
    parser.add_argument("--work", default=BENCHMARK_DIR / "work" / "audit")
    parser.add_argument("--metadata-out", default=None)
    parser.add_argument("--keep-work", action="store_true")
    args = parser.parse_args(argv)

    suite_path = Path(args.suite).resolve()
    results_dir = Path(args.results_dir).resolve()
    work_dir = Path(args.work).resolve()
    metadata_path = Path(args.metadata_out).resolve() if args.metadata_out else results_dir / "evidence-metadata.csv"
    manifest = load_manifest(suite_path)
    original_suite = manifest["suite_name"]
    evidence_suite = f"{original_suite}__{args.case}__evidence"
    enable_json_ui = bool(args.json_ui)
    if enable_json_ui:
        cbmc_path = Path(os.environ.get("IMPROVED_CBMC", REPO_ROOT / "cmake-build-debug-cbmc" / "bin" / "cbmc"))
        enable_json_ui = cbmc_supports_json_ui(cbmc_path)
        if not enable_json_ui:
            print("warning: --json-ui requested but not supported or cbmc is unavailable; using text logs")

    evidence_manifest, selected_case = build_evidence_manifest(
        manifest, args.case, evidence_suite, args.trace, enable_json_ui
    )
    logical_id = benchmark_inventory.logical_case_id(benchmark_inventory.logical_key(selected_case))
    results_dir.mkdir(parents=True, exist_ok=True)
    work_dir.mkdir(parents=True, exist_ok=True)
    if not args.keep_work:
        shutil.rmtree(work_dir / evidence_suite, ignore_errors=True)
    evidence_manifest_path = write_manifest(evidence_manifest, work_dir)
    result = run_runner(evidence_manifest_path, args.case, args.variant, results_dir, work_dir)
    csv_path = results_dir / f"{evidence_suite}.csv"
    if csv_path.exists():
        rows = append_metadata(csv_path, metadata_path, original_suite, logical_id, work_dir, args.trace)
        print(f"evidence metadata rows: {rows}")
        print(f"evidence metadata: {metadata_path}")
    else:
        print(f"warning: evidence csv missing: {csv_path}")
    return result.returncode


if __name__ == "__main__":
    raise SystemExit(main())
