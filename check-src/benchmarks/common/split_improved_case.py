#!/usr/bin/env python3
"""Split an improved single-file case into ISR source plus foreground harness.

Inputs:
  - case_root: directory containing an improved-pipeline main.c.
  - --extern: full extern declaration, for example "int flag".
  - --extern-token: shorthand "type:name", for example "int:flag".

Outputs:
  - case_root/isr.c: original main.c with the main function removed.
  - case_root/main.c: generated foreground harness referencing extern globals.

This is a normalization helper for cases where ISR/task bodies should be in a
separate file passed through variant_isr_sources.
"""

import argparse
import re
from pathlib import Path


MAIN_RE = re.compile(r"\b(?:int|void)\s+main\s*\([^)]*\)\s*\{")


def remove_main_function(text):
    """Return source text with the first int/void main function removed.

    Args:
        text: C source text containing a foreground main function.

    Returns:
        Source text with the first matched main function removed.
    """
    match = MAIN_RE.search(text)
    if not match:
        return text
    start = match.start()
    index = match.end() - 1
    depth = 0
    while index < len(text):
        char = text[index]
        if char == "{":
            depth += 1
        elif char == "}":
            depth -= 1
            if depth == 0:
                return text[:start].rstrip() + "\n\n" + text[index + 1 :].lstrip()
        index += 1
    raise ValueError("could not find end of main function")


def write_harness(path, externs):
    """Write a small foreground main() that keeps selected globals live.

    Args:
        path: Output path for the generated harness C file.
        externs: Extern declarations to emit and touch from main.

    Returns:
        None. Writes the harness file in place.
    """
    lines = [
        "/* Generated foreground harness for improved interleaving benchmarks. */",
    ]
    for declaration in externs:
        lines.append(f"extern {declaration};")
    lines += [
        "",
        "int main(void)",
        "{",
        "  int sink = 0;",
    ]
    for declaration in externs:
        name = declaration.strip().rstrip(";").split()[-1]
        if name.startswith("*"):
            name = name[1:]
        lines.append(f"  sink += (int){name};")
        lines.append(f"  {name} = {name};")
    lines += [
        "  return sink == 1234567;",
        "}",
    ]
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def split_case(case_root, externs):
    """Rewrite main.c and create isr.c for one improved-pipeline case root.

    Args:
        case_root: Directory containing the current improved-pipeline main.c.
        externs: Extern declarations used by the generated foreground harness.

    Returns:
        None. Writes case_root/isr.c and replaces case_root/main.c.
    """
    main_path = case_root / "main.c"
    isr_path = case_root / "isr.c"
    text = main_path.read_text(encoding="utf-8", errors="replace")
    isr_path.write_text(remove_main_function(text), encoding="utf-8")
    write_harness(main_path, externs)


def main(argv=None):
    """CLI entry point for splitting one improved case root.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("case_root")
    parser.add_argument("--extern", action="append", default=[])
    parser.add_argument("--extern-token", action="append", default=[])
    args = parser.parse_args(argv)
    externs = list(args.extern)
    for token in args.extern_token:
        type_name, name = token.split(":", 1)
        externs.append(f"{type_name} {name}")
    split_case(Path(args.case_root), externs)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
