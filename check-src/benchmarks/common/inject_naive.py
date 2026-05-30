#!/usr/bin/env python3
import json
import re
import shutil
import sys
from pathlib import Path


def main(argv):
    if len(argv) != 3:
        raise SystemExit("usage: inject_naive.py <suite.json> <case-name> <output-root>")

    manifest_path = Path(argv[0]).resolve()
    case_name = argv[1]
    output_root = Path(argv[2])
    repo_root = manifest_path.parents[3]
    data = json.loads(manifest_path.read_text())
    case = next((candidate for candidate in data["cases"] if candidate["name"] == case_name), None)
    if case is None:
        raise SystemExit(f"case not found: {case_name}")

    source_root = repo_root / case["root"]
    if output_root.exists():
        shutil.rmtree(output_root)
    shutil.copytree(source_root, output_root)

    isr_sources = set(case["isr_sources"])
    isr_functions = case["isr_functions"]
    prologue = "extern _Bool nondet_bool(void);\n" + "".join(
        f"void *{name}(void *arg);\n" for name in isr_functions
    )
    total = 0

    for rel in case["sources"]:
        if rel in isr_sources:
            continue
        path = output_root / rel
        if path.suffix not in [".c", ".h", ".cpp"]:
            continue
        text = path.read_text(errors="ignore")
        if "nondet_bool(void)" not in text:
            match = re.search(r"((?:#include[^\n]*\n)+)", text)
            if match:
                text = text[: match.end()] + prologue + text[match.end() :]
            else:
                text = prologue + text

        lines = text.splitlines(True)
        out = []
        inserted = 0
        depth = 0
        paren_depth = 0
        in_function = False
        pending_function = False
        prev_trim = ""
        for line in lines:
            trim = line.strip()
            if (
                in_function
                and depth > 0
                and paren_depth == 0
                and trim.endswith(";")
                and (prev_trim.endswith(";") or prev_trim.endswith("{") or prev_trim.endswith("}"))
                and trim != ";"
                and not trim.startswith(("return", "extern", "typedef", "struct", "enum", "union", "#"))
                and not re.match(r"^(VAR|CONST|FUNC|P2VAR|P2CONST|CONSTP2CONST|CONSTP2VAR)\s*\(", trim)
                and not re.match(r"^(if|for|while|switch)\b", trim)
                and "nondet_bool" not in trim
                and not any(f"{name}(" in trim for name in isr_functions)
            ):
                for name in isr_functions:
                    out.append(f"  if(nondet_bool()) {name}(0);\n")
                    inserted += 1
            out.append(line)

            enters_function = (
                depth == 0
                and (re.search(r"\)\s*\{", line) is not None or (pending_function and "{" in line))
            )
            depth += line.count("{") - line.count("}")
            depth = max(depth, 0)
            paren_depth += line.count("(") - line.count(")")
            paren_depth = max(paren_depth, 0)

            if enters_function and depth > 0:
                in_function = True
                pending_function = False
            elif depth == 0:
                in_function = False
                pending_function = (
                    re.search(r"\)\s*$", line) is not None
                    and re.match(r"\s*[A-Z_]+\s*\(", line) is None
                    and "," not in line
                    and re.match(r"\s*(if|for|while|switch)\b", line) is None
                )
            if trim:
                prev_trim = trim

        path.write_text("".join(out))
        total += inserted
        print(f"{rel},{inserted}")

    print(f"TOTAL,{total}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
