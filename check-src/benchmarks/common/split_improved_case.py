#!/usr/bin/env python3
import argparse
import re
from pathlib import Path


MAIN_RE = re.compile(r"\b(?:int|void)\s+main\s*\([^)]*\)\s*\{")


def remove_main_function(text):
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
    main_path = case_root / "main.c"
    isr_path = case_root / "isr.c"
    text = main_path.read_text(encoding="utf-8", errors="replace")
    isr_path.write_text(remove_main_function(text), encoding="utf-8")
    write_harness(main_path, externs)


def main(argv=None):
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
