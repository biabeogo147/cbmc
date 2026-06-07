#!/usr/bin/env python3
"""Audit NO_INJECTION_CANDIDATES cases with conservative global-effect scans.

Inputs:
  - check-src/benchmarks/results/audit/benchmark-inventory.csv.
  - check-src/benchmarks/suites/*.json.
  - Improved source roots referenced by suite manifests.

Outputs:
  - check-src/benchmarks/results/audit/no-injection-audit.csv by default.

The scan is intentionally conservative. It reports no_injection_true only when
it can see that ISR-reachable writes and main-reachable globals do not intersect
and no uncertain pointer/call behavior was found.
"""

import argparse
import csv
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path


SCRIPT_DIR = Path(__file__).resolve().parent
BENCHMARK_DIR = SCRIPT_DIR.parent
REPO_ROOT = BENCHMARK_DIR.parent.parent
DEFAULT_INVENTORY = BENCHMARK_DIR / "results" / "audit" / "benchmark-inventory.csv"
DEFAULT_OUTPUT = BENCHMARK_DIR / "results" / "audit" / "no-injection-audit.csv"
OUTPUT_FIELDS = [
    "suite",
    "case",
    "logical_case_id",
    "verdict",
    "isr_functions",
    "isr_written_globals",
    "main_reachable_globals",
    "candidate_globals",
    "candidate_details",
    "original_interleavings",
    "filtered_interleavings",
    "unknowns",
    "evidence",
]
KEYWORDS = {
    "if",
    "for",
    "while",
    "switch",
    "return",
    "sizeof",
    "__CPROVER_atomic_begin",
    "__CPROVER_atomic_end",
}
DECL_SKIP_PREFIXES = (
    "typedef",
    "struct",
    "union",
    "enum",
    "extern",
    "return",
    "case",
    "break",
    "continue",
    "goto",
)


if str(SCRIPT_DIR) not in sys.path:
    sys.path.insert(0, str(SCRIPT_DIR))

import atomic_wrap_functions  # noqa: E402
import report_benchmark  # noqa: E402


@dataclass
class FunctionInfo:
    name: str
    params: str
    body: str
    path: Path
    calls: set[str] = field(default_factory=set)
    local_names: set[str] = field(default_factory=set)
    used_globals: set[str] = field(default_factory=set)
    written_globals: set[str] = field(default_factory=set)
    unknowns: set[str] = field(default_factory=set)


def strip_comments_and_strings(text):
    """Remove comments and string/char literals from C-like text.

    Args:
        text: Source text.

    Returns:
        Text with comments and literal contents replaced by whitespace.
    """
    text = re.sub(r"//.*?$|/\*.*?\*/", " ", text, flags=re.MULTILINE | re.DOTALL)
    text = re.sub(r'"(?:\\.|[^"\\])*"', '""', text)
    text = re.sub(r"'(?:\\.|[^'\\])*'", "''", text)
    return text


def top_level_statements(text):
    """Yield semicolon-terminated statements at top-level brace depth.

    Args:
        text: Source text with comments removed.

    Returns:
        Iterator of top-level statement strings.
    """
    depth = 0
    start = 0
    for index, char in enumerate(text):
        if char == "{":
            depth += 1
        elif char == "}":
            depth = max(0, depth - 1)
            start = index + 1
        elif char == ";" and depth == 0:
            statement = text[start : index + 1].strip()
            start = index + 1
            if statement:
                yield statement


def declaration_names(statement):
    """Extract likely variable names from one top-level declaration.

    Args:
        statement: Top-level C statement ending in semicolon.

    Returns:
        Set of declared variable names.
    """
    compact = " ".join(statement.split())
    if not compact or compact.startswith("#") or compact.startswith(DECL_SKIP_PREFIXES):
        return set()
    if "(" in compact and ")" in compact and compact.rstrip(";").endswith(")"):
        return set()
    if "__attribute__" in compact:
        compact = re.sub(r"__attribute__\s*\(\([^)]*\)\)", " ", compact)
    compact = compact.rstrip(";")
    names = set()
    for part in compact.split(","):
        part = part.split("=")[0]
        part = re.sub(r"\[[^\]]*\]", "", part)
        tokens = re.findall(r"\b[A-Za-z_]\w*\b", part)
        if tokens:
            name = tokens[-1]
            if name not in KEYWORDS and name not in {"const", "volatile", "static", "unsigned", "signed"}:
                names.add(name)
    return names


def collect_globals(files):
    """Collect likely file-scope global variables from source files.

    Args:
        files: Iterable of source paths.

    Returns:
        Set of likely global variable names.
    """
    globals_found = set()
    for path in files:
        text = strip_comments_and_strings(path.read_text(encoding="utf-8", errors="ignore"))
        for statement in top_level_statements(text):
            globals_found.update(declaration_names(statement))
    return globals_found


def find_function_definitions(path):
    """Find function definitions in one source file.

    Args:
        path: Source file path.

    Returns:
        Dictionary mapping function name to FunctionInfo.
    """
    text = path.read_text(encoding="utf-8", errors="ignore")
    clean = strip_comments_and_strings(text)
    pattern = re.compile(
        r"(?m)(^|\n)\s*[A-Za-z_][\w\s\*\(\),\[\]]*?\b([A-Za-z_]\w*)\s*\(([^;{}]*)\)\s*\{"
    )
    functions = {}
    for match in pattern.finditer(clean):
        name = match.group(2)
        if name in KEYWORDS:
            continue
        open_brace = match.end() - 1
        try:
            close_brace = atomic_wrap_functions.find_matching_brace(clean, open_brace)
        except ValueError:
            continue
        functions[name] = FunctionInfo(
            name=name,
            params=match.group(3),
            body=clean[open_brace + 1 : close_brace],
            path=path,
        )
    return functions


def collect_functions(files):
    """Collect function definitions from source files.

    Args:
        files: Iterable of source paths.

    Returns:
        Dictionary mapping function name to FunctionInfo.
    """
    functions = {}
    for path in files:
        functions.update(find_function_definitions(path))
    return functions


def analyze_function(function, globals_found, known_functions):
    """Populate call/global-use/write sets for one function.

    Args:
        function: FunctionInfo to mutate.
        globals_found: Set of known global names.
        known_functions: Set of function names defined in scanned files.

    Returns:
        None.
    """
    body = function.body
    function.local_names = local_names(function.params, body)
    visible_globals = globals_found - function.local_names
    identifiers = set(re.findall(r"\b[A-Za-z_]\w*\b", body))
    function.used_globals = identifiers & visible_globals
    calls = set(re.findall(r"\b([A-Za-z_]\w*)\s*\(", body)) - KEYWORDS
    function.calls = calls & known_functions
    external_calls = calls - known_functions - KEYWORDS
    for call in external_calls:
        if call not in {"assert", "__CPROVER_assert", "__CPROVER_assume", "nondet_bv"}:
            function.unknowns.add(f"external_call:{call}")
    written = set()
    for global_name in visible_globals:
        escaped = re.escape(global_name)
        patterns = [
            rf"\b{escaped}\b\s*(?:->|\.)?[A-Za-z_]\w*\s*(?:[+\-*/%&|^]?=)",
            rf"\b{escaped}\b\s*(?:[+\-*/%&|^]?=)",
            rf"\b{escaped}\b\s*(?:\+\+|--)",
            rf"(?:\+\+|--)\s*\b{escaped}\b",
            rf"\b{escaped}\b\s*\[[^\]]+\]\s*(?:[+\-*/%&|^]?=)",
        ]
        if any(re.search(pattern, body) for pattern in patterns):
            written.add(global_name)
    function.written_globals = written
    if re.search(r"(^|[^A-Za-z0-9_])\*\s*[A-Za-z_]\w*\s*=", body):
        function.unknowns.add("pointer_write")


def local_names(params, body):
    """Collect likely parameter and local variable names.

    Args:
        params: Function parameter text between parentheses.
        body: Function body text.

    Returns:
        Set of likely local names that should shadow globals.
    """
    names = set()
    for param in params.split(","):
        tokens = re.findall(r"\b[A-Za-z_]\w*\b", param)
        if tokens and tokens[-1] not in {"void", "const", "volatile"}:
            names.add(tokens[-1])
    for statement in re.findall(r"(^|[;{}])\s*([^;{}]+;)", body):
        text = statement[1].strip()
        first = re.match(r"([A-Za-z_]\w*)\b", text)
        if not first:
            continue
        starter = first.group(1)
        if starter in KEYWORDS or starter in {"return", "assert"}:
            continue
        for part in text.rstrip(";").split(","):
            before_init = part.split("=")[0]
            before_init = re.sub(r"\[[^\]]*\]", "", before_init)
            tokens = re.findall(r"\b[A-Za-z_]\w*\b", before_init)
            if len(tokens) >= 2:
                names.add(tokens[-1])
    return names


def reachable_functions(start_functions, functions):
    """Compute functions reachable through direct in-file calls.

    Args:
        start_functions: Iterable of function names.
        functions: Mapping of function names to FunctionInfo.

    Returns:
        Set of reachable function names that exist in functions.
    """
    seen = set()
    work = [name for name in start_functions if name in functions]
    while work:
        name = work.pop()
        if name in seen:
            continue
        seen.add(name)
        work.extend(sorted(functions[name].calls - seen))
    return seen


def resolve_paths(root, names):
    """Resolve manifest-relative paths under a source root.

    Args:
        root: Source root path.
        names: Relative source path names.

    Returns:
        List of existing paths.
    """
    paths = []
    for name in names:
        path = root / name
        if path.exists():
            paths.append(path)
    return paths


def variant_array(case, field, variant, default_field):
    """Return variant-specific array from a case manifest.

    Args:
        case: Loaded case dictionary.
        field: Variant field name.
        variant: Variant name.
        default_field: Fallback field name.

    Returns:
        List of configured strings.
    """
    variant_values = case.get(field, {}).get(variant)
    if variant_values is not None:
        return list(variant_values)
    return list(case.get(default_field, []))


def count_interleavings(path):
    """Count interleaving entries in a manifest JSON file.

    Args:
        path: Manifest JSON path.

    Returns:
        Entry count as a string, or an empty string when unavailable.
    """
    if not path or not path.exists():
        return ""
    try:
        data = json.loads(path.read_text(encoding="utf-8", errors="replace"))
    except (OSError, json.JSONDecodeError):
        return ""
    return str(len(data.get("interleaving", [])))


def evidence_interleaving_counts(work_dir, suite, case):
    """Read original and filtered interleaving counts from evidence work.

    Args:
        work_dir: Audit work directory.
        suite: Original suite name.
        case: Case name.

    Returns:
        Tuple of original and filtered interleaving counts as strings.
    """
    evidence_dir = work_dir / f"{suite}__{case}__evidence"
    original = next(evidence_dir.rglob("improved_pipeline_interleaving_pipeline.json"), None) if evidence_dir.exists() else None
    filtered = (
        next(evidence_dir.rglob("improved_pipeline_interleaving_pipeline.filtered.json"), None)
        if evidence_dir.exists()
        else None
    )
    return count_interleavings(original), count_interleavings(filtered)


def scan_case(repo_root, manifest, case, logical_case_id, work_dir=None):
    """Scan one no-injection candidate case.

    Args:
        repo_root: Repository root path.
        manifest: Loaded suite manifest.
        case: Loaded case dictionary.
        logical_case_id: Stable inventory id.
        work_dir: Optional audit work directory containing evidence reruns.

    Returns:
        CSV row dictionary containing scan verdict and evidence.
    """
    improved_root = repo_root / case.get("variant_roots", {}).get("improved_pipeline", case.get("root", ""))
    source_names = variant_array(case, "variant_sources", "improved_pipeline", "sources")
    isr_source_names = variant_array(case, "variant_isr_sources", "improved_pipeline", "isr_sources")
    files = resolve_paths(improved_root, sorted(set(source_names + isr_source_names)))
    globals_found = collect_globals(files)
    functions = collect_functions(files)
    for function in functions.values():
        analyze_function(function, globals_found, set(functions))

    isr_functions = list(case.get("isr_functions", []))
    entry = case.get("entry_function", "main")
    isr_reachable = reachable_functions(isr_functions, functions)
    main_reachable = reachable_functions([entry], functions)
    isr_written = set()
    main_globals = set()
    isr_writers = {}
    main_users = {}
    unknowns = set()
    for name in isr_reachable:
        info = functions[name]
        isr_written.update(info.written_globals)
        for global_name in info.written_globals:
            isr_writers.setdefault(global_name, set()).add(name)
        unknowns.update(info.unknowns)
    for name in main_reachable:
        info = functions[name]
        main_globals.update(info.used_globals)
        for global_name in info.used_globals:
            main_users.setdefault(global_name, set()).add(name)
        unknowns.update(info.unknowns)
    missing_isrs = [name for name in isr_functions if name not in functions]
    if missing_isrs:
        unknowns.add("missing_isr_definition:" + ",".join(sorted(missing_isrs)))
    if entry not in functions:
        unknowns.add(f"missing_entry_definition:{entry}")
    candidates = isr_written & main_globals
    if candidates:
        verdict = "no_injection_false"
    elif unknowns:
        verdict = "needs_manual_review"
    else:
        verdict = "no_injection_true"
    evidence = (
        f"globals={len(globals_found)}; "
        f"isr_reachable={len(isr_reachable)}; "
        f"main_reachable={len(main_reachable)}"
    )
    candidate_details = []
    for global_name in sorted(candidates):
        writers = ",".join(sorted(isr_writers.get(global_name, set())))
        users = ",".join(sorted(main_users.get(global_name, set())))
        candidate_details.append(f"{global_name}:isr={writers}:main={users}")
    original_interleavings, filtered_interleavings = "", ""
    if work_dir:
        original_interleavings, filtered_interleavings = evidence_interleaving_counts(
            Path(work_dir), manifest["suite_name"], case["name"]
        )
    return {
        "suite": manifest["suite_name"],
        "case": case["name"],
        "logical_case_id": logical_case_id,
        "verdict": verdict,
        "isr_functions": ";".join(isr_functions),
        "isr_written_globals": ";".join(sorted(isr_written)),
        "main_reachable_globals": ";".join(sorted(main_globals)),
        "candidate_globals": ";".join(sorted(candidates)),
        "candidate_details": ";".join(candidate_details),
        "original_interleavings": original_interleavings,
        "filtered_interleavings": filtered_interleavings,
        "unknowns": ";".join(sorted(unknowns)),
        "evidence": evidence,
    }


def case_by_name(manifest, case_name):
    """Find a case dictionary in a manifest.

    Args:
        manifest: Loaded suite manifest.
        case_name: Case name to find.

    Returns:
        Matching case dictionary.
    """
    for case in manifest.get("cases", []):
        if case.get("name") == case_name:
            return case
    raise KeyError(f"{manifest.get('suite_name', '<unknown>')} missing case {case_name}")


def load_inventory(path):
    """Load audit inventory rows that need no-injection checks.

    Args:
        path: Inventory CSV path.

    Returns:
        List of rows with needs_no_injection_audit=true.
    """
    with path.open(newline="", encoding="utf-8", errors="replace") as csv_file:
        return [row for row in csv.DictReader(csv_file) if row.get("needs_no_injection_audit") == "true"]


def write_rows(rows, output_path):
    """Write scan rows to CSV.

    Args:
        rows: Scan row dictionaries.
        output_path: Destination CSV path.

    Returns:
        None.
    """
    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w", newline="", encoding="utf-8") as csv_file:
        writer = csv.DictWriter(csv_file, fieldnames=OUTPUT_FIELDS)
        writer.writeheader()
        writer.writerows(rows)


def split_semicolon(value):
    """Split a semicolon-separated audit field.

    Args:
        value: Semicolon-separated field value.

    Returns:
        List of non-empty item strings.
    """
    return [item for item in str(value or "").split(";") if item]


def compact_items(value, limit=12):
    """Format semicolon-separated values for compact diagnostics.

    Args:
        value: Semicolon-separated field value.
        limit: Maximum number of items to display before truncation.

    Returns:
        Compact text.
    """
    items = split_semicolon(value)
    if not items:
        return ""
    if len(items) > limit:
        items = items[:limit] + [f"...(+{len(items) - limit} more)"]
    return "; ".join(items)


def main(argv=None):
    """CLI entry point.

    Args:
        argv: Optional command-line arguments.

    Returns:
        Process exit code.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=REPO_ROOT)
    parser.add_argument("--inventory", default=DEFAULT_INVENTORY)
    parser.add_argument("--suite-dir", default=BENCHMARK_DIR / "suites")
    parser.add_argument("--out", default=DEFAULT_OUTPUT)
    parser.add_argument("--work", default=BENCHMARK_DIR / "work" / "audit")
    parser.add_argument("--case", action="append", default=[])
    args = parser.parse_args(argv)

    repo_root = Path(args.repo_root).resolve()
    manifests = report_benchmark.load_manifests(Path(args.suite_dir))
    selected = set(args.case)
    rows = []
    for item in load_inventory(Path(args.inventory)):
        if selected and item["case"] not in selected:
            continue
        manifest = manifests[item["suite"]]
        case = case_by_name(manifest, item["case"])
        rows.append(scan_case(repo_root, manifest, case, item["logical_case_id"], Path(args.work)))
    write_rows(rows, Path(args.out))
    print(f"no-injection audit rows: {len(rows)}")
    print(f"no-injection audit: {Path(args.out)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
