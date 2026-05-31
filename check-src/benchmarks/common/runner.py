#!/usr/bin/env python3
import argparse
import csv
import json
import os
import shutil
import subprocess
import sys
import time
import tempfile
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent


def env_path(name, default):
    return Path(os.environ.get(name, default))


def read_rss_kb(pid):
    status = Path(f"/proc/{pid}/status")
    if not status.exists():
        return 0
    try:
        for line in status.read_text(errors="ignore").splitlines():
            if line.startswith("VmRSS:"):
                return int(line.split()[1])
    except OSError:
        return 0
    return 0


def summarize_log(log_path):
    summary = ""
    try:
        for line in log_path.read_text(errors="ignore").splitlines():
            if "VERIFICATION SUCCESSFUL" in line or "VERIFICATION FAILED" in line:
                summary = line
            elif "Failed properties:" in line:
                summary = f"{summary} | {line}" if summary else line
            elif "pointer handling for concurrency is unsound" in line:
                summary = "CBMC_UNSUPPORTED_CONCURRENCY"
    except OSError as exc:
        summary = f"log read failed: {exc}"
    return summary


IMPROVED_VARIANTS = {"improved_pipeline"}
STOCK_ASYNC_VARIANTS = {"stock_cprover_async"}
DEFAULT_VARIANTS = ["stock_cprover_async", "improved_pipeline"]


def measure(
    csv_writer,
    log_dir,
    suite,
    case,
    variant,
    phase,
    run_id,
    run_kind,
    command,
    timeout_sec=None,
    memory_limit_mb=None,
):
    log_dir.mkdir(parents=True, exist_ok=True)
    log_path = log_dir / f"{suite}.{case}.{variant}.{phase}.{run_kind}.{run_id}.log"
    start = time.monotonic()
    max_rss_kb = 0
    with log_path.open("w", encoding="utf-8", errors="replace") as log:
        try:
            proc = subprocess.Popen(command, stdout=log, stderr=subprocess.STDOUT)
        except OSError as exc:
            elapsed_ms = int((time.monotonic() - start) * 1000)
            log.write(f"failed to start command: {exc}\n")
            csv_writer.writerow(
                {
                    "benchmark": suite,
                    "case": case,
                    "variant": variant,
                    "phase": phase,
                    "run": run_id,
                    "run_kind": run_kind,
                    "exit_code": 127,
                    "time_ms": elapsed_ms,
                    "max_rss_kb": 0,
                    "max_rss_mb": "0.0",
                    "summary": f"COMMAND_START_FAILED: {exc}",
                }
            )
            return 127
        killed_summary = ""
        while proc.poll() is None:
            max_rss_kb = max(max_rss_kb, read_rss_kb(proc.pid))
            elapsed = time.monotonic() - start
            if timeout_sec and elapsed > timeout_sec:
                killed_summary = f"TIMEOUT_AFTER_{timeout_sec}s"
                proc.kill()
                break
            if memory_limit_mb and max_rss_kb > memory_limit_mb * 1024:
                killed_summary = f"MEMORY_LIMIT_EXCEEDED_{memory_limit_mb}MB"
                proc.kill()
                break
            time.sleep(0.02)
        proc.wait()
        max_rss_kb = max(max_rss_kb, read_rss_kb(proc.pid))
    elapsed_ms = int((time.monotonic() - start) * 1000)
    summary = killed_summary or summarize_log(log_path)
    csv_writer.writerow(
        {
            "benchmark": suite,
            "case": case,
            "variant": variant,
            "phase": phase,
            "run": run_id,
            "run_kind": run_kind,
            "exit_code": proc.returncode,
            "time_ms": elapsed_ms,
            "max_rss_kb": max_rss_kb,
            "max_rss_mb": f"{max_rss_kb / 1024:.1f}",
            "summary": summary,
        }
    )
    return proc.returncode


def variants_for(manifest, case):
    return case.get("variants", manifest.get("variants", DEFAULT_VARIANTS))


def sources_for(case, variant=None):
    variant_sources = case.get("variant_sources", {})
    if variant in variant_sources:
        return variant_sources[variant]
    return case["sources"]


def isr_sources_for(case, variant=None):
    variant_isr_sources = case.get("variant_isr_sources", {})
    if variant in variant_isr_sources:
        return variant_isr_sources[variant]
    return case["isr_sources"]


def case_root(case, variant=None):
    roots = case.get("variant_roots", {})
    if variant in roots:
        return REPO_ROOT / roots[variant]
    return REPO_ROOT / case["root"]


def compile_loc(root, sources):
    total = 0
    for source in sources:
        path = root / source
        total += len(path.read_text(errors="ignore").splitlines())
    return total


def validate_manifest(manifest):
    for key in ["suite_name", "description", "enabled", "cases"]:
        if key not in manifest:
            raise ValueError(f"missing suite field: {key}")
    required = [
        "name",
        "root",
        "sources",
        "include_dirs",
        "isr_sources",
        "isr_functions",
        "entry_function",
        "unwind",
        "timeout_sec",
        "memory_limit_mb",
    ]
    for case in manifest["cases"]:
        for key in required:
            if key not in case:
                raise ValueError(f"{case.get('name', '<unnamed>')}: missing {key}")
        if not case.get("enabled", True):
            continue
        roots = []
        for variant in variants_for(manifest, case):
            root = case_root(case, variant)
            if root not in roots:
                roots.append(root)
        for root in roots:
            if not root.exists():
                raise ValueError(f"{case['name']}: missing root {root}")
            root_variants = [
                variant
                for variant in variants_for(manifest, case)
                if case_root(case, variant) == root
            ]
            root_sources = []
            for variant in root_variants:
                root_sources.extend(sources_for(case, variant))
                root_sources.extend(isr_sources_for(case, variant))
            for source in sorted(set(root_sources)):
                path = root / source
                if not path.exists():
                    raise ValueError(f"{case['name']}: missing source {path}")
            for include_dir in case["include_dirs"]:
                path = root / include_dir
                if not path.exists():
                    raise ValueError(f"{case['name']}: missing include dir {path}")
        if not case["isr_functions"]:
            raise ValueError(f"{case['name']}: isr_functions must not be empty")
        min_compile_loc = int(case.get("min_compile_loc", 0))
        if min_compile_loc:
            for variant in variants_for(manifest, case):
                root = case_root(case, variant)
                loc = compile_loc(root, sources_for(case, variant))
                if loc < min_compile_loc:
                    raise ValueError(
                        f"{case['name']}:{variant}: compile LOC {loc} < min_compile_loc {min_compile_loc}"
                    )


def copy_tree(src, dst):
    if dst.exists():
        shutil.rmtree(dst)
    shutil.copytree(
        src,
        dst,
        ignore=shutil.ignore_patterns("benchmarks", "external", "work", "results", "__pycache__"),
    )


def command_paths():
    improved_cbmc = env_path("IMPROVED_CBMC", REPO_ROOT / "cmake-build-debug-cbmc/bin/cbmc")
    improved_gotocc = env_path("IMPROVED_GOTOCC", REPO_ROOT / "cmake-build-debug-cbmc/bin/goto-cc")
    stock_cbmc = env_path("STOCK_CBMC", improved_cbmc)
    stock_gotocc = env_path("STOCK_GOTOCC", improved_gotocc)
    aib = env_path("AIB", REPO_ROOT / "cmake-build-debug-cbmc/bin/aib")
    return stock_cbmc, stock_gotocc, improved_cbmc, improved_gotocc, aib


def rel_args(root, paths, prefix):
    return [f"{prefix}{root / path}" for path in paths]


def source_args(root, paths):
    return [str(root / path) for path in paths]


def define_args(case):
    return [f"-D{define}" for define in case.get("defines", [])]


def verify_args(case, variant):
    args = ["--function", case["entry_function"]]
    if variant in IMPROVED_VARIANTS:
        args.append("--no-standard-checks")
    args.extend(["--unwind", str(case["unwind"])])
    for prop in case.get("properties", []):
        args.extend(["--property", prop])
    return args


def write_prepare_row(csv_writer, suite, case, variant, run_id, summary):
    csv_writer.writerow(
        {
            "benchmark": suite,
            "case": case,
            "variant": variant,
            "phase": "prepare",
            "run": run_id,
            "run_kind": "prepare",
            "exit_code": 0,
            "time_ms": 0,
            "max_rss_kb": 0,
            "max_rss_mb": "0.0",
            "summary": summary,
        }
    )


def write_phase_row(csv_writer, suite, case, variant, phase, run_id, run_kind, exit_code, summary):
    csv_writer.writerow(
        {
            "benchmark": suite,
            "case": case,
            "variant": variant,
            "phase": phase,
            "run": run_id,
            "run_kind": run_kind,
            "exit_code": exit_code,
            "time_ms": 0,
            "max_rss_kb": 0,
            "max_rss_mb": "0.0",
            "summary": summary,
        }
    )


def copy_variant_source(case, variant, destination):
    copy_tree(case_root(case, variant), destination)


def filtered_interleaving_manifest(source_manifest, filtered_manifest, allowed_functions):
    data = json.loads(source_manifest.read_text(encoding="utf-8"))
    allowed = set(allowed_functions)
    filtered = []
    for entry in data.get("interleaving", []):
        if allowed and entry.get("name") not in allowed:
            continue
        file_entries = entry.get("line_added_block_with_file", [])
        usable_entries = [
            item
            for item in file_entries
            if item.get("file") and item.get("line")
        ]
        if not usable_entries:
            continue
        entry = dict(entry)
        entry["line_added_block_with_file"] = usable_entries
        filtered.append(entry)
    data["interleaving"] = filtered
    filtered_manifest.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    return len(filtered)


def run_stock_cprover_async(csv_writer, suite, case, name, case_work, logs, run_id, run_kind):
    stock_async = case_work / "stock_cprover_async"
    copy_variant_source(case, "stock_cprover_async", stock_async)
    write_prepare_row(
        csv_writer,
        suite,
        name,
        "stock_cprover_async",
        run_id,
        f"source_root={case_root(case, 'stock_cprover_async')}",
    )
    stock_cbmc, stock_gotocc, _, _, _ = command_paths()

    stock_out = case_work / "stock_cprover_async.out"
    stock_compile = [
        str(stock_gotocc),
        *rel_args(stock_async, case["include_dirs"], "-I"),
        *define_args(case),
        *source_args(stock_async, sources_for(case, "stock_cprover_async")),
        "-o",
        str(stock_out),
    ]
    if measure(
        csv_writer,
        logs,
        suite,
        name,
        "stock_cprover_async",
        "compile",
        run_id,
        run_kind,
        stock_compile,
        case["timeout_sec"],
        case["memory_limit_mb"],
    ) == 0:
        stock_verify = [str(stock_cbmc), str(stock_out), *verify_args(case, "stock_cprover_async")]
        measure(
            csv_writer,
            logs,
            suite,
            name,
            "stock_cprover_async",
            "verify",
            run_id,
            run_kind,
            stock_verify,
            case["timeout_sec"],
            case["memory_limit_mb"],
        )


def run_improved_pipeline(csv_writer, suite, case, name, case_work, logs, variant, run_id, run_kind):
    original = case_work / f"{variant}_original"
    targeted = case_work / variant
    copy_variant_source(case, variant, original)
    _, _, improved_cbmc, improved_gotocc, aib = command_paths()

    interleaving_json = case_work / f"{variant}_interleaving_pipeline.json"
    improved_manifest_out = case_work / f"{variant}_manifest.out"
    variant_sources = sources_for(case, variant)
    variant_isr_sources = isr_sources_for(case, variant)
    interleaving_sources = [str(original / path) for path in variant_isr_sources]
    improved_manifest_cmd = [
        str(improved_gotocc),
        *rel_args(original, case["include_dirs"], "-I"),
        *define_args(case),
        *source_args(original, variant_sources),
        "--interleaving-project-root",
        str(original),
        "--interleaving-source-files",
        *interleaving_sources,
        "--interleaving-output",
        str(interleaving_json),
        "-o",
        str(improved_manifest_out),
    ]
    if measure(
        csv_writer,
        logs,
        suite,
        name,
        variant,
        "manifest",
        run_id,
        run_kind,
        improved_manifest_cmd,
        case["timeout_sec"],
        case["memory_limit_mb"],
    ) == 0:
        aib_input_json = case_work / f"{variant}_interleaving_pipeline.filtered.json"
        injection_candidates = filtered_interleaving_manifest(
            interleaving_json,
            aib_input_json,
            case.get("isr_functions", []),
        )
        inject_exit = 0
        if injection_candidates == 0:
            copy_tree(original, targeted)
            write_phase_row(
                csv_writer,
                suite,
                name,
                variant,
                "inject",
                run_id,
                run_kind,
                0,
                "NO_INJECTION_CANDIDATES",
            )
        else:
            injected_manifest = targeted / "interleaving_pipeline_injected.json"
            aib_cmd = [str(aib), str(original), str(aib_input_json), str(targeted), str(injected_manifest)]
            inject_exit = measure(
                csv_writer,
                logs,
                suite,
                name,
                variant,
                "inject",
                run_id,
                run_kind,
                aib_cmd,
                case["timeout_sec"],
                case["memory_limit_mb"],
            )
        if inject_exit == 0:
            improved_out = case_work / f"{variant}.out"
            improved_compile = [
                str(improved_gotocc),
                *rel_args(targeted, case["include_dirs"], "-I"),
                *define_args(case),
                *source_args(targeted, variant_sources),
                "-o",
                str(improved_out),
            ]
            if measure(
                csv_writer,
                logs,
                suite,
                name,
                variant,
                "compile",
                run_id,
                run_kind,
                improved_compile,
                case["timeout_sec"],
                case["memory_limit_mb"],
            ) == 0:
                improved_verify = [str(improved_cbmc), str(improved_out), *verify_args(case, variant)]
                measure(
                    csv_writer,
                    logs,
                    suite,
                    name,
                    variant,
                    "verify",
                    run_id,
                    run_kind,
                    improved_verify,
                    case["timeout_sec"],
                    case["memory_limit_mb"],
                )


def run_variant_set(csv_writer, manifest_path, suite, case, manifest, work_root, logs, variants, run_id, run_kind):
    name = case["name"]
    case_work = work_root / suite / name / f"{run_kind}-{run_id}"

    if case_work.exists():
        shutil.rmtree(case_work)
    case_work.mkdir(parents=True, exist_ok=True)

    for variant in variants:
        if variant in STOCK_ASYNC_VARIANTS:
            run_stock_cprover_async(csv_writer, suite, case, name, case_work, logs, run_id, run_kind)
        elif variant in IMPROVED_VARIANTS:
            run_improved_pipeline(csv_writer, suite, case, name, case_work, logs, variant, run_id, run_kind)
        else:
            raise ValueError(f"{name}: unknown variant {variant}")


def run_case(csv_writer, manifest_path, suite, case, manifest, work_root, logs, dry_run, selected_variants):
    name = case["name"]
    variants = selected_variants or variants_for(manifest, case)

    print(f"{suite}:{name}")
    if dry_run:
        return

    warmups = int(manifest.get("warmups", 0))
    runs = int(manifest.get("runs", 1))
    for run_kind, total in [("warmup", warmups), ("measure", runs)]:
        for run_id in range(1, total + 1):
            run_variant_set(
                csv_writer,
                manifest_path,
                suite,
                case,
                manifest,
                work_root,
                logs,
                variants,
                str(run_id),
                run_kind,
            )


def main(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest")
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--case", dest="case_names", action="append", default=[])
    parser.add_argument("--variant", dest="variants", action="append", default=[])
    parser.add_argument("--list-cases", action="store_true")
    args = parser.parse_args(argv)

    manifest_path = Path(args.manifest).resolve()
    manifest = json.loads(manifest_path.read_text())
    validate_manifest(manifest)

    suite = manifest["suite_name"]
    if args.list_cases:
        for case in manifest["cases"]:
            if case.get("enabled", True):
                print(f"{suite}:{case['name']}")
        return 0
    if args.dry_run:
        selected = set(args.case_names)
        for case in manifest["cases"]:
            if not case.get("enabled", True):
                continue
            if selected and case["name"] not in selected:
                continue
            print(f"{suite}:{case['name']}")
        return 0

    default_work = Path(tempfile.gettempdir()) / "cbmc_check_src_benchmarks"
    work_root = Path(os.environ.get("WORK", default_work))
    results_dir = Path(os.environ.get("RESULTS_DIR", BENCHMARK_DIR / "results"))
    logs = work_root / "logs"
    results_dir.mkdir(parents=True, exist_ok=True)
    work_root.mkdir(parents=True, exist_ok=True)
    csv_path = results_dir / f"{suite}.csv"

    with csv_path.open("w", newline="", encoding="utf-8", buffering=1) as csv_file:
        fields = [
            "benchmark",
            "case",
            "variant",
            "phase",
            "run",
            "run_kind",
            "exit_code",
            "time_ms",
            "max_rss_kb",
            "max_rss_mb",
            "summary",
        ]
        writer = csv.DictWriter(csv_file, fieldnames=fields)
        writer.writeheader()
        selected_cases = set(args.case_names)
        for case in manifest["cases"]:
            if not case.get("enabled", True):
                continue
            if selected_cases and case["name"] not in selected_cases:
                continue
            run_case(
                writer,
                manifest_path,
                suite,
                case,
                manifest,
                work_root,
                logs,
                args.dry_run,
                args.variants,
            )

    print(f"results: {csv_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
