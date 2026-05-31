#!/usr/bin/env python3
import argparse
import re
import shutil
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent
ASYNC_LABEL_RE = re.compile(r"^(\s*)__CPROVER_ASYNC_\d+\s*:\s*$")
PTHREAD_CREATE_RE = re.compile(
    r"^(?P<indent>\s*)pthread_create\s*\(\s*&?[^,]+,\s*[^,]+,\s*(?P<func>[A-Za-z_][A-Za-z0-9_]*)\s*,\s*(?P<arg>[^)]+)\)\s*;\s*$"
)


def strip_async_labels(source: str) -> str:
    lines = []
    for line in source.splitlines():
        if ASYNC_LABEL_RE.match(line):
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"


def stock_async_model(source: str) -> str:
    lines = []
    async_index = 1
    for line in source.splitlines():
        if line.lstrip().startswith("//"):
            lines.append(line)
            continue
        match = PTHREAD_CREATE_RE.match(line)
        if match:
            indent = match.group("indent")
            function = match.group("func")
            arg = match.group("arg").strip()
            lines.append(f"{indent}__CPROVER_ASYNC_{async_index}:")
            lines.append(f"{indent}{function}({arg});")
            async_index += 1
        else:
            lines.append(line)
    return "\n".join(lines) + "\n"


def improved_pipeline_model(source: str) -> str:
    lines = []
    for line in strip_async_labels(source).splitlines():
        if line.lstrip().startswith("//"):
            lines.append(line)
            continue
        if PTHREAD_CREATE_RE.match(line):
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"


def copy_case(repo, corpus, case_name, source, compile_name, isr_functions, force):
    source_path = (repo / source).resolve()
    if not source_path.exists():
        raise FileNotFoundError(source_path)
    case_dir = repo / "check-src" / "benchmark-sources" / corpus / "cases" / case_name
    stock_dir = case_dir / "stock-cprover-async"
    improved_dir = case_dir / "improved-pipeline"
    if case_dir.exists() and force:
        shutil.rmtree(case_dir)
    stock_dir.mkdir(parents=True, exist_ok=True)
    improved_dir.mkdir(parents=True, exist_ok=True)

    stock_target = stock_dir / compile_name
    improved_target = improved_dir / compile_name
    text = source_path.read_text(errors="ignore")
    stock_target.write_text(stock_async_model(text), encoding="utf-8", errors="replace")
    improved_target.write_text(improved_pipeline_model(text), encoding="utf-8")
    for header in source_path.parent.glob("*.h"):
        shutil.copy2(header, stock_dir / header.name)
        shutil.copy2(header, improved_dir / header.name)

    functions = [item.strip() for item in isr_functions.split(",") if item.strip()]
    case_md = [
        f"# {case_name}",
        "",
        f"Origin: `{source}`",
        "",
        "Normalization:",
        "- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.",
        "- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, leaving ISR/task functions in the compile unit for pipeline validation.",
        "",
        "Compile files:",
        f"- `{compile_name}`",
        "",
        "ISR/task functions:",
    ]
    if functions:
        case_md.extend(f"- `{function}`" for function in functions)
    else:
        case_md.append("- Pending explicit function selection.")
    (case_dir / "CASE.md").write_text("\n".join(case_md) + "\n", encoding="utf-8")
    return case_dir


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--corpus", required=True, choices=["icbmc", "intabs"])
    parser.add_argument("--case", required=True)
    parser.add_argument("--source", required=True)
    parser.add_argument("--compile-name", default="main.c")
    parser.add_argument("--isr-functions", default="")
    parser.add_argument("--force", action="store_true")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    case_dir = copy_case(
        repo,
        args.corpus,
        args.case,
        args.source,
        args.compile_name,
        args.isr_functions,
        args.force,
    )
    print(case_dir.relative_to(repo).as_posix())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
