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


def measure(csv_writer, log_dir, suite, case, variant, phase, run_id, command):
    log_dir.mkdir(parents=True, exist_ok=True)
    log_path = log_dir / f"{suite}.{case}.{variant}.{phase}.{run_id}.log"
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
                    "exit_code": 127,
                    "time_ms": elapsed_ms,
                    "max_rss_kb": 0,
                    "max_rss_mb": "0.0",
                    "summary": f"COMMAND_START_FAILED: {exc}",
                }
            )
            return 127
        while proc.poll() is None:
            max_rss_kb = max(max_rss_kb, read_rss_kb(proc.pid))
            time.sleep(0.02)
        max_rss_kb = max(max_rss_kb, read_rss_kb(proc.pid))
    elapsed_ms = int((time.monotonic() - start) * 1000)
    summary = summarize_log(log_path)
    csv_writer.writerow(
        {
            "benchmark": suite,
            "case": case,
            "variant": variant,
            "phase": phase,
            "run": run_id,
            "exit_code": proc.returncode,
            "time_ms": elapsed_ms,
            "max_rss_kb": max_rss_kb,
            "max_rss_mb": f"{max_rss_kb / 1024:.1f}",
            "summary": summary,
        }
    )
    return proc.returncode


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
        root = REPO_ROOT / case["root"]
        if not root.exists():
            raise ValueError(f"{case['name']}: missing root {root}")
        for source in case["sources"] + case["isr_sources"]:
            path = root / source
            if not path.exists():
                raise ValueError(f"{case['name']}: missing source {path}")
        for include_dir in case["include_dirs"]:
            path = root / include_dir
            if not path.exists():
                raise ValueError(f"{case['name']}: missing include dir {path}")
        if not case["isr_functions"]:
            raise ValueError(f"{case['name']}: isr_functions must not be empty")


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


def verify_args(case, variant):
    args = ["--function", case["entry_function"]]
    if variant == "improved_targeted":
        args.append("--no-standard-checks")
    args.extend(["--unwind", str(case["unwind"])])
    for prop in case.get("properties", []):
        args.extend(["--property", prop])
    return args


def write_prepare_row(csv_writer, suite, case, variant, summary):
    csv_writer.writerow(
        {
            "benchmark": suite,
            "case": case,
            "variant": variant,
            "phase": "prepare",
            "run": "0",
            "exit_code": 0,
            "time_ms": 0,
            "max_rss_kb": 0,
            "max_rss_mb": "0.0",
            "summary": summary,
        }
    )


def run_case(csv_writer, manifest_path, suite, case, work_root, logs, dry_run):
    name = case["name"]
    source_root = REPO_ROOT / case["root"]
    case_work = work_root / suite / name
    original = case_work / "original"
    stock_naive = case_work / "stock_naive"
    improved_original = case_work / "improved_original"
    improved_targeted = case_work / "improved_targeted"

    print(f"{suite}:{name}")
    if dry_run:
        return

    if case_work.exists():
        shutil.rmtree(case_work)
    copy_tree(source_root, original)
    copy_tree(source_root, improved_original)

    stock_cbmc, stock_gotocc, improved_cbmc, improved_gotocc, aib = command_paths()

    inject_cmd = [
        sys.executable,
        str(SCRIPT_DIR / "inject_naive.py"),
        str(manifest_path),
        name,
        str(stock_naive),
    ]
    result = subprocess.run(inject_cmd, capture_output=True, text=True, check=False)
    (case_work / "stock_naive_insertions.csv").write_text(result.stdout + result.stderr)
    write_prepare_row(csv_writer, suite, name, "stock_naive", f"isr_insertions_log={case_work / 'stock_naive_insertions.csv'}")

    stock_out = case_work / "stock_naive.out"
    stock_compile = [str(stock_gotocc), *rel_args(stock_naive, case["include_dirs"], "-I"), *source_args(stock_naive, case["sources"]), "-o", str(stock_out)]
    if measure(csv_writer, logs, suite, name, "stock_naive", "compile", "1", stock_compile) == 0:
        stock_verify = [str(stock_cbmc), str(stock_out), *verify_args(case, "stock_naive")]
        measure(csv_writer, logs, suite, name, "stock_naive", "verify", "1", stock_verify)

    interleaving_json = case_work / "interleaving_pipeline.json"
    improved_manifest_out = case_work / "improved_manifest.out"
    interleaving_sources = [str(improved_original / path) for path in case["isr_sources"]]
    improved_manifest_cmd = [
        str(improved_gotocc),
        *rel_args(improved_original, case["include_dirs"], "-I"),
        *source_args(improved_original, case["sources"]),
        "--interleaving-project-root",
        str(improved_original),
        "--interleaving-source-files",
        *interleaving_sources,
        "--interleaving-output",
        str(interleaving_json),
        "-o",
        str(improved_manifest_out),
    ]
    if measure(csv_writer, logs, suite, name, "improved_targeted", "manifest", "1", improved_manifest_cmd) == 0:
        injected_manifest = improved_targeted / "interleaving_pipeline_injected.json"
        aib_cmd = [str(aib), str(improved_original), str(interleaving_json), str(improved_targeted), str(injected_manifest)]
        if measure(csv_writer, logs, suite, name, "improved_targeted", "inject", "1", aib_cmd) == 0:
            improved_out = case_work / "improved_targeted.out"
            improved_compile = [str(improved_gotocc), *rel_args(improved_targeted, case["include_dirs"], "-I"), *source_args(improved_targeted, case["sources"]), "-o", str(improved_out)]
            if measure(csv_writer, logs, suite, name, "improved_targeted", "compile", "1", improved_compile) == 0:
                improved_verify = [str(improved_cbmc), str(improved_out), *verify_args(case, "improved_targeted")]
                measure(csv_writer, logs, suite, name, "improved_targeted", "verify", "1", improved_verify)


def main(argv):
    parser = argparse.ArgumentParser()
    parser.add_argument("manifest")
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args(argv)

    manifest_path = Path(args.manifest).resolve()
    manifest = json.loads(manifest_path.read_text())
    validate_manifest(manifest)

    suite = manifest["suite_name"]
    if args.dry_run:
        for case in manifest["cases"]:
            if case.get("enabled", True):
                print(f"{suite}:{case['name']}")
        return 0

    default_work = Path(tempfile.gettempdir()) / "cbmc_check_src_benchmarks"
    work_root = Path(os.environ.get("WORK", default_work))
    results_dir = Path(os.environ.get("RESULTS_DIR", BENCHMARK_DIR / "results"))
    logs = work_root / "logs"
    results_dir.mkdir(parents=True, exist_ok=True)
    work_root.mkdir(parents=True, exist_ok=True)
    csv_path = results_dir / f"{suite}.csv"

    with csv_path.open("w", newline="", encoding="utf-8") as csv_file:
        fields = ["benchmark", "case", "variant", "phase", "run", "exit_code", "time_ms", "max_rss_kb", "max_rss_mb", "summary"]
        writer = csv.DictWriter(csv_file, fieldnames=fields)
        writer.writeheader()
        for case in manifest["cases"]:
            if not case.get("enabled", True):
                continue
            run_case(writer, manifest_path, suite, case, work_root, logs, args.dry_run)

    print(f"results: {csv_path}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
