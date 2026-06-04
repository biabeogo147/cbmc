#!/usr/bin/env python3
"""Normalize a single upstream C case into stock and improved variant roots.

Inputs:
  - --corpus: target corpus name, currently icbmc or intabs.
  - --case: normalized case directory name.
  - --source: upstream source file path, relative to repo root.
  - --compile-name: filename to use inside each variant root, default main.c.
  - --isr-functions: comma-separated ISR/task names for generated CASE.md.

Outputs:
  - check-src/benchmark-sources/<corpus>/cases/<case>/stock-cprover-async/
  - check-src/benchmark-sources/<corpus>/cases/<case>/improved-pipeline/
  - check-src/benchmark-sources/<corpus>/cases/<case>/CASE.md

This helper edits normalized copies only. It does not modify upstream corpus
files in place.
"""

import argparse
import re
import shutil
from pathlib import Path

from atomic_wrap_functions import function_matches, wrap_functions


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent
ASYNC_LABEL_RE = re.compile(r"^(\s*)__CPROVER_ASYNC_\d+\s*:\s*$")
PTHREAD_CREATE_RE = re.compile(
    r"^(?P<indent>\s*)pthread_create\s*\(\s*&?[^,]+,\s*[^,]+,\s*(?P<func>[A-Za-z_][A-Za-z0-9_]*)\s*,\s*(?P<arg>.*)\)\s*;\s*$"
)
ZERO_ARG_FUNCTION_RE = re.compile(
    r"\b(?:void|int)\s+(?P<func>[A-Za-z_][A-Za-z0-9_]*)\s*\(\s*(?:void\s*)?\)\s*\{"
)


def extract_isr_definitions(source: str, isr_functions: list[str], include_path: str) -> tuple[str, str, int]:
    """Move selected function definitions into an includable ISR source.

    The improved benchmark source may be a monolithic upstream file with many
    static helpers. To preserve that static scope, the extracted ISR source is
    included at the last extracted definition location instead of compiled as
    a separate translation unit. This keeps declarations placed between task
    definitions visible to every extracted task.

    Args:
        source: Improved-model source text.
        isr_functions: Function names to extract.
        include_path: Include path to insert into the improved compile source.

    Returns:
        Tuple of rewritten compile source, ISR source text, and extracted count.
    """
    replacements: list[tuple[int, int]] = []
    extracted: list[tuple[int, str]] = []
    for function in isr_functions:
        definitions: list[tuple[int, int, str]] = []
        for start, open_brace, close_brace in function_matches(source, function):
            candidate = source[start : close_brace + 1]
            signature = candidate.split("{", 1)[0]
            if ";" in signature:
                continue
            definitions.append((start, close_brace + 1, candidate.lstrip("\n")))
        if len(definitions) != 1:
            continue
        start, end, text = definitions[0]
        replacements.append((start, end))
        extracted.append((start, text))

    if not replacements:
        return source, "/* No ISR/task definitions were extracted. */\n", 0

    replacements.sort()
    extracted.sort()
    parts: list[str] = []
    cursor = 0
    include_line = f'#include "{include_path}"\n'
    last_replacement = len(replacements) - 1
    for index, (start, end) in enumerate(replacements):
        parts.append(source[cursor:start])
        if index == last_replacement:
            if parts and not parts[-1].endswith("\n"):
                parts.append("\n")
            parts.append(include_line)
        cursor = end
    parts.append(source[cursor:])

    isr_source = "/* Extracted ISR/task definitions for the improved interleaving pipeline. */\n\n"
    isr_source += "\n\n".join(text for _, text in extracted) + "\n"
    isr_source, _ = wrap_functions(isr_source, isr_functions)
    return "".join(parts), isr_source, len(extracted)


def strip_async_labels(source: str) -> str:
    """Remove active __CPROVER_ASYNC_* labels from source text.

    Args:
        source: C source text.

    Returns:
        Source text without standalone CPROVER async labels.
    """
    lines = []
    for line in source.splitlines():
        if ASYNC_LABEL_RE.match(line):
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"


def stock_async_model(source: str) -> str:
    """Convert active launch sites to CPROVER async-style direct calls.

    Args:
        source: C source text from the upstream case.

    Returns:
        Stock-model source text where upstream async labels are renumbered and
        pthread_create calls become __CPROVER_ASYNC-labeled direct calls.
    """
    lines = []
    zero_arg_functions = {
        match.group("func") for match in ZERO_ARG_FUNCTION_RE.finditer(source)
    }
    async_index = 1
    for line in source.splitlines():
        if line.lstrip().startswith("//"):
            lines.append(line)
            continue
        async_match = ASYNC_LABEL_RE.match(line)
        if async_match:
            lines.append(f"{async_match.group(1)}__CPROVER_ASYNC_{async_index}:")
            async_index += 1
            continue
        match = PTHREAD_CREATE_RE.match(line)
        if match:
            indent = match.group("indent")
            function = match.group("func")
            arg = match.group("arg").strip()
            if function in zero_arg_functions:
                arg = ""
            lines.append(f"{indent}__CPROVER_ASYNC_{async_index}:")
            lines.append(f"{indent}{function}({arg});")
            async_index += 1
        else:
            lines.append(line)
    return "\n".join(lines) + "\n"


def improved_pipeline_model(source: str) -> str:
    """Remove active thread launch statements for improved pipeline modeling.

    Args:
        source: C source text from the upstream case.

    Returns:
        Improved-model source text without active async labels or pthread_create
        launch statements.
    """
    lines = []
    skip_async_call = False
    for line in source.splitlines():
        if line.lstrip().startswith("//"):
            lines.append(line)
            continue
        if ASYNC_LABEL_RE.match(line):
            skip_async_call = True
            continue
        if skip_async_call:
            if re.match(r"^\s*[A-Za-z_][A-Za-z0-9_]*\s*\([^;]*\)\s*;\s*$", line):
                skip_async_call = False
                continue
            skip_async_call = False
        if PTHREAD_CREATE_RE.match(line):
            continue
        lines.append(line)
    return "\n".join(lines) + "\n"


def copy_case(repo, corpus, case_name, source, compile_name, isr_functions, force, split_isr_source, isr_source):
    """Create variant roots and provenance notes for one normalized case.

    Args:
        repo: Repository root.
        corpus: Target corpus folder name, for example icbmc or intabs.
        case_name: Normalized benchmark case directory name.
        source: Upstream source path relative to repo.
        compile_name: File name to write inside each variant root.
        isr_functions: Comma-separated ISR/task function names.
        force: Whether to delete an existing normalized case directory first.
        split_isr_source: Whether to extract improved ISR functions.
        isr_source: Improved ISR source path relative to improved-pipeline.

    Returns:
        Path to the generated case directory.
    """
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
    functions = [item.strip() for item in isr_functions.split(",") if item.strip()]
    stock_target.write_text(stock_async_model(text), encoding="utf-8", errors="replace")
    improved_text = improved_pipeline_model(text)
    extracted_count = 0
    if split_isr_source:
        isr_path = Path(isr_source)
        if isr_path.is_absolute() or ".." in isr_path.parts:
            raise ValueError(f"invalid relative ISR source path: {isr_source}")
        include_path = isr_path.as_posix()
        improved_text, isr_text, extracted_count = extract_isr_definitions(
            improved_text,
            functions,
            include_path,
        )
        isr_target = improved_dir / isr_path
        isr_target.parent.mkdir(parents=True, exist_ok=True)
        isr_target.write_text(isr_text, encoding="utf-8")
        isr_header = isr_target.with_suffix(".h")
        if not isr_header.exists():
            isr_header.write_text(
                "#ifndef ISR_DEFINE_ISR_H\n"
                "#define ISR_DEFINE_ISR_H\n\n"
                "/* ISR definitions are included by the normalized compile source. */\n\n"
                "#endif\n",
                encoding="ascii",
            )
    else:
        (improved_dir / "isr_define").mkdir(parents=True, exist_ok=True)
        (improved_dir / "isr_define" / "isr.c").write_text(
            "/* Pending improved-pipeline ISR definitions. */\n",
            encoding="ascii",
        )
        (improved_dir / "isr_define" / "isr.h").write_text(
            "#ifndef ISR_DEFINE_ISR_H\n"
            "#define ISR_DEFINE_ISR_H\n\n"
            "/* Reserved for improved-pipeline ISR definitions. */\n\n"
            "#endif\n",
            encoding="ascii",
        )
    improved_target.write_text(improved_text, encoding="utf-8")
    for header in source_path.parent.glob("*.h"):
        shutil.copy2(header, stock_dir / header.name)
        shutil.copy2(header, improved_dir / header.name)

    case_md = [
        f"# {case_name}",
        "",
        f"Origin: `{source}`",
        "",
        "Normalization:",
        "- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.",
        (
            f"- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, "
            f"keeps `{compile_name}` as the compile source, and uses `{isr_source}` for `--interleaving-source-files`."
            if split_isr_source
            else "- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches."
        ),
        "",
        "Compile files:",
        f"- `{compile_name}`",
        "",
        "Improved ISR source:",
        f"- `{isr_source}`" if split_isr_source else "- Pending split into `isr_define/isr.c`.",
        "",
        f"Extracted ISR/task definitions: {extracted_count}" if split_isr_source else "Extracted ISR/task definitions: 0",
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
    """CLI entry point for one case normalization.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--corpus", required=True, choices=["icbmc", "intabs"])
    parser.add_argument("--case", required=True)
    parser.add_argument("--source", required=True)
    parser.add_argument("--compile-name", default="main.c")
    parser.add_argument("--isr-functions", default="")
    parser.add_argument("--split-isr-source", action="store_true")
    parser.add_argument("--isr-source", default="isr_define/isr.c")
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
        args.split_isr_source,
        args.isr_source,
    )
    print(case_dir.relative_to(repo).as_posix())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
