#!/usr/bin/env python3
"""Generate the benchmark Markdown report from raw suite CSV files.

Inputs:
  - CSV files from check-src/benchmarks/results/*.csv.
  - Suite manifests from check-src/benchmarks/suites/*.json.
  - Source corpus directories under check-src/benchmark-sources.

Output:
  - check-src/benchmark.md by default, or --out <path>.

The report summarizes measured rows only; warmup rows are ignored. It reports
median phase time, peak RSS, verification output, correctness judgment, and
speed/RAM deltas whenever both variants have measured rows.
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
SOURCE_SUFFIXES = {".c", ".h", ".i"}
DIAGNOSTIC_CATEGORY_ORDER = [
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
CORRECTNESS_VERDICT_ORDER = [
    "same_outcome_comparable",
    "improved_correct",
    "stock_correct",
    "both_correct_different_model",
    "both_need_fix",
    "no_injection_true",
    "no_injection_false",
    "needs_manual_review",
    "not_audited",
]

SOURCE_INVENTORY_ROOTS = {
    "trampoline-stock-cprover-async": "check-src/benchmark-sources/trampoline/stock-cprover-async",
    "trampoline-improved-pipeline": "check-src/benchmark-sources/trampoline/improved-pipeline",
    "icbmc-upstream": "check-src/benchmark-sources/icbmc/upstream",
    "icbmc-po-code": "check-src/benchmark-sources/icbmc/upstream/extracted/po-code",
    "icbmc-seq-code": "check-src/benchmark-sources/icbmc/upstream/extracted/seq-code",
    "icbmc-conc-code": "check-src/benchmark-sources/icbmc/upstream/extracted/conc-code",
    "intabs-upstream": "check-src/benchmark-sources/intabs/upstream/repository",
    "intabs-icbmc": "check-src/benchmark-sources/intabs/upstream/repository/icbmc",
    "intabs-src-test": "check-src/benchmark-sources/intabs/upstream/repository/src/test",
}


def read_csv_rows(path):
    """Read optional CSV rows.

    Args:
        path: CSV path to load.

    Returns:
        List of row dictionaries, or an empty list when the path is missing.
    """
    path = Path(path)
    if not path.exists():
        return []
    with path.open(newline="", encoding="utf-8", errors="replace") as csv_file:
        return list(csv.DictReader(csv_file))


def source_inventory_rows():
    """Return source inventory rows computed directly from corpus directories.

    Args:
        None.

    Returns:
        List of tuples (name, relative_path, source_file_count, loc).
    """
    rows = []
    for name, relative in SOURCE_INVENTORY_ROOTS.items():
        root = REPO_ROOT / relative
        if not root.exists():
            continue
        files = [path for path in root.rglob("*") if path.is_file() and path.suffix in SOURCE_SUFFIXES]
        loc = sum(len(path.read_text(errors="ignore").splitlines()) for path in files)
        rows.append((name, relative, len(files), loc))
    return rows


def audit_action_for_no_injection(row):
    """Return the report action for one no-injection audit row.

    Args:
        row: Row from no-injection-audit.csv.

    Returns:
        Human-readable action text.
    """
    verdict = row.get("verdict", "")
    if verdict == "no_injection_false":
        return "fix ISR source-effect metadata or insertion-site manifest before comparing"
    if verdict == "no_injection_true":
        return "keep as valid no-injection case; no ISR-written global reaches main"
    if verdict == "needs_manual_review":
        return "inspect unresolved ISR/global reachability before comparing"
    return "run no-injection correctness audit"


def summarize_audit_text(value, max_items=5, max_chars=360):
    """Return a compact one-line audit detail.

    Args:
        value: Semicolon-separated audit detail text.
        max_items: Maximum number of semicolon-separated items to keep.
        max_chars: Maximum output length.

    Returns:
        Compact detail string suitable for the main Markdown report.
    """
    text = str(value or "").replace("\n", " ").strip()
    if not text:
        return ""
    items = [item for item in text.split(";") if item]
    if len(items) > max_items:
        text = ";".join(items[:max_items]) + f";...(+{len(items) - max_items} more)"
    if len(text) > max_chars:
        return text[: max_chars - 3].rstrip() + "..."
    return text


def build_audit_annotations(audit_dir):
    """Build case-level correctness notes for the benchmark report.

    Args:
        audit_dir: Directory containing audit CSV files.

    Returns:
        Dictionary keyed by (suite, case) with a short Markdown note.
    """
    annotations = {}
    audit_dir = Path(audit_dir)
    outcome_rows = read_csv_rows(audit_dir / "outcome-mismatch-audit.csv")
    no_injection_rows = read_csv_rows(audit_dir / "no-injection-audit.csv")

    for row in outcome_rows:
        suite_case = (row.get("suite", ""), row.get("case", ""))
        verdict = row.get("verdict", "pending_trace_review")
        correct_variant = row.get("correct_variant", "unknown")
        action = row.get("action", "inspect_trace")
        evidence = summarize_audit_text(row.get("evidence", ""), max_items=2)
        annotations[suite_case] = (
            f"Correctness audit: `{verdict}`; correct variant: `{correct_variant}`; "
            f"action: `{action}`. {evidence}".strip()
        )

    for row in no_injection_rows:
        suite_case = (row.get("suite", ""), row.get("case", ""))
        verdict = row.get("verdict", "pending_no_injection_audit")
        action = audit_action_for_no_injection(row)
        if row.get("candidate_globals"):
            details = "candidate globals: " + summarize_audit_text(row.get("candidate_globals"))
        elif row.get("unknowns"):
            details = "unknowns: " + summarize_audit_text(row.get("unknowns"))
        else:
            details = summarize_audit_text(row.get("evidence", ""))
        annotations[suite_case] = (
            f"Correctness audit: `{verdict}`; action: `{action}`. {details}".strip()
        )
    return annotations


def build_audit_records(audit_dir):
    """Build correctness records from audit CSV files.

    Args:
        audit_dir: Directory containing audit CSV files.

    Returns:
        Dictionary keyed by (suite, case) with correctness fields.
    """
    records = {}
    audit_dir = Path(audit_dir)
    for row in read_csv_rows(audit_dir / "outcome-mismatch-audit.csv"):
        suite_case = (row.get("suite", ""), row.get("case", ""))
        records[suite_case] = {
            "correctness_verdict": row.get("verdict", "needs_manual_review"),
            "correct_variant": row.get("correct_variant", "unknown"),
            "correctness_action": row.get("action", "inspect_trace"),
            "evidence": row.get("evidence", ""),
        }
    for row in read_csv_rows(audit_dir / "no-injection-audit.csv"):
        suite_case = (row.get("suite", ""), row.get("case", ""))
        evidence = ""
        if row.get("candidate_globals"):
            evidence = "candidate globals: " + summarize_audit_text(row.get("candidate_globals"))
        elif row.get("unknowns"):
            evidence = "unknowns: " + summarize_audit_text(row.get("unknowns"))
        else:
            evidence = row.get("evidence", "")
        records[suite_case] = {
            "correctness_verdict": row.get("verdict", "needs_manual_review"),
            "correct_variant": "none",
            "correctness_action": audit_action_for_no_injection(row),
            "evidence": evidence,
        }
    return records


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


def filter_rows_to_known_suites(rows, manifests):
    """Drop rows whose suite manifest is no longer present.

    Args:
        rows: Raw measured CSV rows.
        manifests: Loaded suite manifests keyed by suite name.

    Returns:
        Rows whose benchmark field refers to an existing suite manifest.
    """
    known = set(manifests)
    return [row for row in rows if row.get("benchmark") in known]


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


def diagnostic_category(stock, improved):
    """Return the report category for one diagnostic case.

    Args:
        stock: Stock variant phase statistics.
        improved: Improved variant phase statistics.

    Returns:
        Stable human-readable category used to group diagnostic cases.
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


def correctness_record_for_case(phases, suite, case, manifest, audit_records=None):
    """Return the correctness record for one case.

    Args:
        phases: Summarized phase dictionary from summarize().
        suite: Suite name.
        case: Case name.
        manifest: Loaded suite manifest.
        audit_records: Optional records loaded from audit CSVs.

    Returns:
        Dictionary with performance_status, correctness_verdict,
        correct_variant, correctness_action, and evidence.
    """
    audit_record = (audit_records or {}).get((suite, case))
    if not audit_record:
        same_case_records = [
            record for (record_suite, record_case), record in (audit_records or {}).items() if record_case == case
        ]
        if len(same_case_records) == 1:
            audit_record = same_case_records[0]
    stock, improved, is_comparable, reason = case_comparison_status(phases, suite, case, manifest)
    if is_comparable:
        stock_variant, improved_variant = comparison_variants(manifest)
        return {
            "performance_status": "measured",
            "correctness_verdict": "same_outcome_comparable",
            "correct_variant": f"{stock_variant};{improved_variant}",
            "correctness_action": "report_output_and_performance",
            "evidence": reason,
        }
    if audit_record:
        record = dict(audit_record)
        record["performance_status"] = "measured_output_mismatch"
        return record
    verdict = "not_audited"
    action = "inspect_trace_before_correctness_claim"
    if stock and improved:
        stock_verify = verify_class(stock)
        improved_verify = verify_class(improved)
        if stock_verify == improved_verify:
            verdict = "same_outcome_comparable"
            action = "report_output_and_performance_with_diagnostic_status"
        elif any(item.get("summary") == "NO_INJECTION_CANDIDATES" for item in improved.values()):
            verdict = "needs_manual_review"
            action = "run_no_injection_audit"
        else:
            verdict = "needs_manual_review"
    return {
        "performance_status": "diagnostic",
        "correctness_verdict": verdict,
        "correct_variant": "unknown",
        "correctness_action": action,
        "evidence": reason,
    }


def measured_case_names(rows):
    """Collect suite/case names that have measured CSV rows.

    Args:
        rows: Measured CSV rows.

    Returns:
        Dictionary mapping suite name to sorted measured case names.
    """
    names = defaultdict(set)
    for row in rows:
        names[row["benchmark"]].add(row["case"])
    return {suite: sorted(cases) for suite, cases in names.items()}


def measured_phase_counts(rows):
    """Count measured rows by suite/case/variant/phase.

    Args:
        rows: Measured CSV rows.

    Returns:
        Dictionary keyed by (suite, case, variant, phase) with row counts.
    """
    counts = defaultdict(int)
    for row in rows:
        if row.get("run_kind", "measure") != "measure":
            continue
        counts[(row["benchmark"], row["case"], row["variant"], row["phase"])] += 1
    return counts


def incomplete_run_rows(rows, manifests):
    """Return enabled cases whose measured run count is below suite.runs.

    Args:
        rows: Measured CSV rows.
        manifests: Loaded suite manifests.

    Returns:
        List of dictionaries describing missing measured repetitions.
    """
    counts = measured_phase_counts(rows)
    incomplete = []
    for suite, manifest in sorted(manifests.items()):
        if not manifest.get("enabled", False):
            continue
        expected_runs = int(manifest.get("runs") or 1)
        stock_variant, improved_variant = comparison_variants(manifest)
        for case in manifest.get("cases", []):
            if case.get("enabled", True) is False:
                continue
            variants = list(case.get("variants") or manifest.get("variants") or [stock_variant, improved_variant])
            for variant in variants:
                for phase in variant_phases(variant):
                    measured = counts.get((suite, case["name"], variant, phase), 0)
                    if measured < expected_runs:
                        incomplete.append(
                            {
                                "suite": suite,
                                "case": case["name"],
                                "variant": variant,
                                "phase": phase,
                                "expected_runs": expected_runs,
                                "measured_runs": measured,
                                "missing_runs": expected_runs - measured,
                            }
                        )
    return incomplete


def append_incomplete_run_notes(lines, rows, manifests):
    """Append rerun notes for interrupted or partial benchmark executions.

    Args:
        lines: Markdown line buffer to mutate.
        rows: Measured CSV rows.
        manifests: Loaded suite manifests.

    Returns:
        None.
    """
    incomplete = incomplete_run_rows(rows, manifests)
    lines.extend(["### Rerun Notes", ""])
    append_table_explanation(
        lines,
        "This table identifies partial benchmark runs that should be rerun before final analysis.",
        [
            ("Suite", "Suite manifest that requested the measured repetitions."),
            ("Case", "Enabled case whose phase has fewer measured rows than requested."),
            ("Variant", "Benchmark variant that is missing measured repetitions."),
            ("Phase", "Pipeline phase with incomplete measurement coverage."),
            ("Measured runs", "Number of measured rows currently present in CSV results."),
            ("Expected runs", "Number of measured repetitions requested by the suite manifest."),
            ("Missing runs", "Expected runs minus measured runs."),
        ],
    )
    if not incomplete:
        lines.append("All enabled suite phases currently have the expected measured run count.")
        lines.append("")
        return
    lines.append(
        "The following enabled case phases have fewer measured runs than the suite manifest requests. Rerun these before treating medians as final."
    )
    lines.append("")
    lines.append("| Suite | Case | Variant | Phase | Measured runs | Expected runs | Missing runs |")
    lines.append("| --- | --- | --- | --- | ---: | ---: | ---: |")
    for item in incomplete:
        lines.append(
            "| "
            + " | ".join(
                [
                    markdown_cell(item["suite"]),
                    markdown_cell(item["case"]),
                    markdown_cell(item["variant"]),
                    markdown_cell(item["phase"]),
                    str(item["measured_runs"]),
                    str(item["expected_runs"]),
                    str(item["missing_runs"]),
                ]
            )
            + " |"
        )
    lines.append("")


def correctness_label(record):
    """Return a compact report-facing correctness label.

    Args:
        record: Correctness record for a case.

    Returns:
        Label describing which output is judged correct.
    """
    variant = record.get("correct_variant", "unknown")
    verdict = record.get("correctness_verdict", "")
    if verdict == "same_outcome_comparable":
        return "both"
    if variant == "improved_pipeline":
        return "improved"
    if variant == "stock_cprover_async":
        return "stock"
    if variant == "both":
        return "both"
    if variant in {"none", "unknown", ""}:
        return "unknown"
    if ";" in variant:
        return "both"
    return variant


def append_correctness_sections(lines, rows, phases, manifests, audit_records):
    """Append correctness summary and verdict tables.

    Args:
        lines: Markdown line buffer to mutate.
        rows: Measured CSV rows.
        phases: Summarized phase dictionary from summarize().
        manifests: Loaded suite manifests.
        audit_records: Correctness records loaded from audit CSVs.

    Returns:
        None.
    """
    names = measured_case_names(rows)
    records = []
    for suite in sorted(names):
        manifest = manifests.get(suite)
        for case in names[suite]:
            record = correctness_record_for_case(phases, suite, case, manifest, audit_records)
            record["suite"] = suite
            record["case"] = case
            records.append(record)

    counts = defaultdict(int)
    for record in records:
        counts[record["correctness_verdict"]] += 1

    lines.extend(["### Correctness Summary", ""])
    append_table_explanation(
        lines,
        "This table counts correctness verdicts across measured cases.",
        [
            ("Verdict", "Normalized correctness classification assigned by comparison and audit evidence."),
            ("Cases", "Number of measured cases assigned to the verdict."),
        ],
    )
    lines.append("| Verdict | Cases |")
    lines.append("| --- | ---: |")
    for verdict in CORRECTNESS_VERDICT_ORDER:
        lines.append(f"| `{verdict}` | {counts.get(verdict, 0)} |")
    extra_verdicts = sorted(set(counts) - set(CORRECTNESS_VERDICT_ORDER))
    for verdict in extra_verdicts:
        lines.append(f"| `{verdict}` | {counts[verdict]} |")
    lines.append("")

    lines.extend(["### Correctness Wins", ""])
    append_table_explanation(
        lines,
        "This table lists cases where one variant is judged more faithful than the other.",
        [
            ("Suite", "Suite containing the audited case."),
            ("Case", "Case with an output disagreement or correctness audit result."),
            ("Correct variant", "Variant judged correct by the audit evidence."),
            ("Verdict", "Correctness verdict assigned to the case."),
            ("Evidence summary", "Short explanation of why that output is considered correct."),
            ("Action", "Follow-up action or reporting policy for the case."),
        ],
    )
    lines.append("| Suite | Case | Correct variant | Verdict | Evidence summary | Action |")
    lines.append("| --- | --- | --- | --- | --- | --- |")
    win_rows = [
        record
        for record in records
        if record["correctness_verdict"] in {"improved_correct", "stock_correct"}
    ]
    if not win_rows:
        lines.append("| n/a | n/a | n/a | n/a | No audited correctness wins yet. | n/a |")
    for record in win_rows:
        evidence = summarize_audit_text(record.get("evidence", ""), max_items=2)
        lines.append(
            "| "
            + " | ".join(
                [
                    record["suite"],
                    record["case"],
                    record["correct_variant"],
                    f"`{record['correctness_verdict']}`",
                    evidence.replace("|", "\\|"),
                    record["correctness_action"],
                ]
            )
            + " |"
        )
    lines.append("")


def markdown_cell(value):
    """Escape a value for a Markdown table cell.

    Args:
        value: Cell value.

    Returns:
        Escaped one-line string.
    """
    return str(value or "").replace("|", "\\|").replace("\n", " ")


def append_table_explanation(lines, purpose, columns):
    """Append a short explanation and column guide for a Markdown table.

    Args:
        lines: Markdown line buffer to mutate.
        purpose: One-sentence table purpose.
        columns: Ordered list of (column_name, meaning) tuples.

    Returns:
        None.
    """
    lines.append(purpose)
    lines.append("")
    lines.append("Column guide:")
    lines.append("")
    lines.append("| Column | Meaning |")
    lines.append("| --- | --- |")
    for name, meaning in columns:
        lines.append(f"| `{markdown_cell(name)}` | {markdown_cell(meaning)} |")
    lines.append("")


def append_diagnostic_correctness_details(lines, audit_dir):
    """Append folded correctness-audit details to benchmark.md.

    Args:
        lines: Markdown line buffer to mutate.
        audit_dir: Directory containing audit CSV files.

    Returns:
        None.
    """
    audit_dir = Path(audit_dir)
    inventory = read_csv_rows(audit_dir / "benchmark-inventory.csv")
    no_injection_rows = read_csv_rows(audit_dir / "no-injection-audit.csv")
    outcome_rows = read_csv_rows(audit_dir / "outcome-mismatch-audit.csv")
    if not inventory and not no_injection_rows and not outcome_rows:
        return

    lines.extend(["### Diagnostic Audit Summary", ""])
    append_table_explanation(
        lines,
        "This table summarizes audit CSV coverage, not raw timing coverage.",
        [
            ("Category", "Audit inventory category assigned before report rendering."),
            ("Cases", "Number of cases present in the audit inventory for that category."),
        ],
    )
    lines.append("| Category | Cases |")
    lines.append("| --- | ---: |")
    category_counts = defaultdict(int)
    for row in inventory:
        category_counts[row.get("category", "unknown")] += 1
    for category in sorted(category_counts):
        lines.append(f"| {markdown_cell(category)} | {category_counts[category]} |")
    lines.append("")

    if no_injection_rows:
        lines.extend(["### No Injection Candidate Cases", ""])
        append_table_explanation(
            lines,
            "This table audits no-injection results; such a result is valid only when no ISR-written global can affect a global reachable from `main`.",
            [
                ("Suite", "Suite containing the no-injection case."),
                ("Case", "Case whose improved pipeline reported no injection candidates."),
                ("Verdict", "Audit judgment for the no-injection result."),
                ("Original interleavings", "Interleaving sites before filtering."),
                ("Filtered interleavings", "Interleaving sites after ISR/global filtering."),
                ("Candidate globals", "Globals that may connect ISR writes to main-reachable state."),
                ("Unknowns", "Unresolved source-analysis items requiring manual review."),
            ],
        )
        lines.append("| Suite | Case | Verdict | Original interleavings | Filtered interleavings | Candidate globals | Unknowns |")
        lines.append("| --- | --- | --- | ---: | ---: | --- | --- |")
        for row in no_injection_rows:
            lines.append(
                "| "
                + " | ".join(
                    [
                        markdown_cell(row.get("suite")),
                        markdown_cell(row.get("case")),
                        markdown_cell(row.get("verdict")),
                        markdown_cell(row.get("original_interleavings")),
                        markdown_cell(row.get("filtered_interleavings")),
                        markdown_cell(summarize_audit_text(row.get("candidate_globals", ""), max_items=4)),
                        markdown_cell(summarize_audit_text(row.get("unknowns", ""), max_items=4)),
                    ]
                )
                + " |"
            )
        lines.append("")

    if outcome_rows:
        lines.extend(["### Output Mismatch Audit Details", ""])
        append_table_explanation(
            lines,
            "This table gives evidence for stock/improved output disagreements.",
            [
                ("Category", "Diagnostic category describing the output mismatch."),
                ("Suite", "Suite containing the audited case."),
                ("Case", "Case whose stock and improved outputs differ."),
                ("Stock output", "Verification summary produced by stock CBMC modeling."),
                ("Improved output", "Verification summary produced by the improved pipeline."),
                ("Verdict", "Audit verdict for the disagreement."),
                ("Correct output", "Which output is judged correct after audit."),
                ("Reason", "Compact evidence supporting the audit verdict."),
            ],
        )
        lines.append("| Category | Suite | Case | Stock output | Improved output | Verdict | Correct output | Reason |")
        lines.append("| --- | --- | --- | --- | --- | --- | --- | --- |")
        for row in outcome_rows:
            lines.append(
                "| "
                + " | ".join(
                    [
                        markdown_cell(row.get("category")),
                        markdown_cell(row.get("suite")),
                        markdown_cell(row.get("case")),
                        markdown_cell(row.get("stock_summary")),
                        markdown_cell(row.get("improved_summary")),
                        markdown_cell(row.get("verdict")),
                        markdown_cell(correctness_label({"correct_variant": row.get("correct_variant"), "correctness_verdict": row.get("verdict")})),
                        markdown_cell(summarize_audit_text(row.get("evidence", ""), max_items=3)),
                    ]
                )
                + " |"
            )
        lines.append("")


def append_case(
    lines,
    suite,
    case,
    phases,
    manifest,
    heading_level=3,
    audit_annotations=None,
    audit_records=None,
):
    """Append one case section with phase tables and comparison status.

    Args:
        lines: Markdown line buffer to mutate.
        suite: Suite name.
        case: Case name.
        phases: Summarized phase dictionary from summarize().
        manifest: Loaded suite manifest.
        heading_level: Markdown heading level for the case name.
        audit_annotations: Optional dictionary of correctness-audit notes.
        audit_records: Optional dictionary of correctness records.

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
        correctness = correctness_record_for_case(phases, suite, case, manifest, audit_records)
        evidence = summarize_audit_text(correctness.get("evidence", ""), max_items=2)
        if not evidence:
            evidence = reason
        reason_cell = evidence.replace("|", "\\|")
        lines.append("| Field | Value |")
        lines.append("| --- | --- |")
        lines.append(f"| Stock output | `{verify_class(stock)}` |")
        lines.append(f"| Improved output | `{verify_class(improved)}` |")
        lines.append(f"| Correct output | `{correctness_label(correctness)}` |")
        lines.append(f"| Correctness verdict | `{correctness.get('correctness_verdict', 'unknown')}` |")
        lines.append(f"| Reason | {reason_cell} |")
        lines.append("")
        audit_note = (audit_annotations or {}).get((suite, case))
        if audit_note and not is_comparable:
            lines.append(audit_note)
            lines.append("")
        stock_total = total_time(stock, variant_phases(stock_variant))
        improved_total = total_time(improved, variant_phases(improved_variant))
        stock_peak = peak_rss(stock)
        improved_peak = peak_rss(improved)
        lines.append("| Metric | Stock | Improved | Difference |")
        lines.append("| --- | ---: | ---: | --- |")
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


def build_report(
    rows,
    phases,
    manifests,
    audit_annotations=None,
    audit_records=None,
    audit_dir=None,
):
    """Compose the full Markdown report as a string.

    Args:
        rows: Measured CSV rows.
        phases: Summarized phase dictionary from summarize().
        manifests: Loaded suite manifests.
        audit_annotations: Optional dictionary of correctness-audit notes.
        audit_records: Optional dictionary of correctness records.
        audit_dir: Optional directory containing audit CSVs.

    Returns:
        Complete Markdown report text.
    """
    lines = [
        "# ISR Benchmark Comparison Results",
        "",
        f"Generated: {datetime.now(timezone.utc).strftime('%Y-%m-%d %H:%M:%S UTC')}",
        "",
        "This report is generated from `check-src/benchmarks/results/*.csv` by `check-src/benchmarks/common/report_benchmark.py`.",
        "Warmup rows are ignored; measured rows are summarized with median time and median peak RSS per phase.",
        "This file compares stock CBMC and improved CBMC output, correctness judgment, time, and RAM for every measured case. Diagnostic and no-injection audit evidence is folded into this same report.",
        "",
        "Comparison labels: Stock CPROVER async, Improved pipeline, Correct output, Median, Peak RSS.",
        "",
        "## Benchmark Scope",
        "",
        "### Source Inventory",
        "",
    ]
    append_table_explanation(
        lines,
        "This table describes the source corpus size used to judge benchmark scale.",
        [
            ("Corpus", "Stable corpus label used by this report."),
            ("Path", "Repository-relative source root."),
            ("C/H/I files", "Number of C, header, and preprocessed C files."),
            ("LOC", "Total line count across those files."),
        ],
    )
    lines.append("| Corpus | Path | C/H/I files | LOC |")
    lines.append("| --- | --- | ---: | ---: |")
    for name, relative, files, loc in source_inventory_rows():
        lines.append(f"| `{name}` | `{relative}` | {files} | {loc} |")
    lines.append("")

    lines.append("## Suite Coverage")
    lines.append("")
    lines.append("### Suite Readiness")
    lines.append("")
    append_table_explanation(
        lines,
        "This table shows which suite manifests are active, staged, and large enough for headline reporting.",
        [
            ("Suite", "Suite manifest name used to group cases and CSV rows."),
            ("Manifest enabled", "Whether `run_all.sh` includes this suite automatically."),
            ("Staged cases", "Cases listed in the suite manifest, including disabled cases."),
            ("Enabled cases", "Cases enabled for execution in that suite."),
            ("Enabled compile LOC", "Estimated maximum compile LOC across enabled case variants."),
            ("Headline-ready", "Whether the enabled suite is large enough for headline comparison claims."),
        ],
    )
    lines.append("| Suite | Manifest enabled | Staged cases | Enabled cases | Enabled compile LOC | Headline-ready |")
    lines.append("| --- | --- | ---: | ---: | ---: | --- |")
    for suite, manifest in sorted(manifests.items()):
        staged, enabled, loc, ready = suite_readiness(manifest)
        headline = "yes" if ready else "no"
        lines.append(
            f"| `{suite}` | {str(manifest.get('enabled', False)).lower()} | {staged} | {enabled} | {loc} | {headline} |"
        )
    lines.append("")

    append_incomplete_run_notes(lines, rows, manifests)

    lines.append("## Correctness Results")
    lines.append("")
    append_correctness_sections(lines, rows, phases, manifests, audit_records or {})

    diagnostic_names = suite_case_names(rows, manifests)
    grouped = defaultdict(lambda: defaultdict(list))
    for suite in sorted(diagnostic_names):
        manifest = manifests.get(suite)
        for case in diagnostic_names[suite]:
            stock, improved, is_comparable, _ = case_comparison_status(phases, suite, case, manifest)
            if is_comparable:
                continue
            category = diagnostic_category(stock, improved)
            grouped[category][suite].append(case)

    lines.extend(["## Diagnostic Results", ""])
    lines.extend(["### Diagnostic Summary", ""])
    append_table_explanation(
        lines,
        "This table groups diagnostic cases by the reason they are not clean same-output comparisons.",
        [
            ("Reason", "Diagnostic category derived from stock/improved verification outputs."),
            ("Cases", "Number of cases assigned to that diagnostic category."),
        ],
    )
    lines.append("| Reason | Cases |")
    lines.append("| --- | ---: |")
    for category in DIAGNOSTIC_CATEGORY_ORDER:
        count = sum(len(cases) for cases in grouped.get(category, {}).values())
        lines.append(f"| {category} | {count} |")
    lines.append("")

    if audit_dir:
        append_diagnostic_correctness_details(lines, audit_dir)

    lines.extend(["### Diagnostic Details", ""])
    append_table_explanation(
        lines,
        "This table lists each diagnostic case with the stock output, improved output, and comparison reason.",
        [
            ("Suite", "Suite containing the diagnostic case."),
            ("Case", "Case whose output is diagnostic rather than a clean same-output comparison."),
            ("Stock output", "Normalized verification outcome for the stock variant."),
            ("Improved output", "Normalized verification outcome for the improved variant."),
            ("Reason", "Why the case is diagnostic or how to rerun disabled evidence."),
        ],
    )
    for category in DIAGNOSTIC_CATEGORY_ORDER:
        suites = grouped.get(category)
        if not suites:
            continue
        lines.extend([f"#### {category}", ""])
        lines.append("| Suite | Case | Stock output | Improved output | Reason |")
        lines.append("| --- | --- | --- | --- | --- |")
        for suite in sorted(suites):
            manifest = manifests.get(suite)
            for case in suites[suite]:
                stock, improved, _, reason = case_comparison_status(phases, suite, case, manifest)
                stock_output = verify_class(stock) if stock else "missing"
                improved_output = verify_class(improved) if improved else "missing"
                if manifest and not manifest.get("enabled", False):
                    reason += " Suite is excluded from automatic `run_all.sh`; run it explicitly when diagnostic evidence is needed."
                lines.append(
                    "| "
                    + " | ".join(
                        [
                            markdown_cell(suite),
                            markdown_cell(case),
                            markdown_cell(stock_output),
                            markdown_cell(improved_output),
                            markdown_cell(reason),
                        ]
                    )
                    + " |"
                )
        lines.append("")

    lines.extend(["## Per-Suite Case Measurements", ""])
    lines.append(
        "Each case subsection contains per-phase measurements, correctness fields, and performance deltas. "
        "Phase tables show runs, exits, median time, peak RSS, and summaries; correctness tables show stock/improved outputs and audit judgment; metric tables compare full measured time and peak RSS."
    )
    lines.append("")
    appended_cases = 0
    names = measured_case_names(rows)
    for suite in sorted(names):
        manifest = manifests.get(suite)
        case_lines = []
        suite_case_count = 0
        for case in names[suite]:
            suite_case_count += 1
            appended_cases += 1
            append_case(
                case_lines,
                suite,
                case,
                phases,
                manifest,
                heading_level=4,
                audit_annotations=audit_annotations,
                audit_records=audit_records,
            )
        if suite_case_count == 0:
            continue
        lines.extend([f"### {suite}", ""])
        lines.extend(case_lines)

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
    parser.add_argument("--audit-dir", default=BENCHMARK_DIR / "results" / "audit")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args(argv)

    manifests = load_manifests(Path(args.suite_dir))
    rows = filter_rows_to_known_suites(load_rows(Path(args.results_dir)), manifests)
    phases = summarize(rows)
    audit_annotations = build_audit_annotations(Path(args.audit_dir))
    audit_records = build_audit_records(Path(args.audit_dir))
    audit_dir = Path(args.audit_dir)
    report = build_report(rows, phases, manifests, audit_annotations, audit_records, audit_dir)
    print(f"report rows loaded: {len(rows)}")
    if args.dry_run:
        return 0
    out = Path(args.out)
    out.write_text(report, encoding="utf-8")
    print(f"report: {out}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
