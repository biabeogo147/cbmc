#!/usr/bin/env python3
import argparse
import json
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".h", ".i"}


def count_source(root: Path):
    files = [path for path in root.rglob("*") if path.is_file() and path.suffix in SOURCE_SUFFIXES]
    loc = 0
    for path in files:
        loc += len(path.read_text(errors="ignore").splitlines())
    return {"files": len(files), "loc": loc}


def main(argv=None):
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--json-out")
    parser.add_argument("--md-out", default="check-src/benchmark-sources/INVENTORY.md")
    args = parser.parse_args(argv)

    repo = Path(args.repo_root).resolve()
    roots = {
        "trampoline-stock-cprover-async": repo / "check-src/benchmark-sources/trampoline/stock-cprover-async",
        "trampoline-improved-pipeline": repo / "check-src/benchmark-sources/trampoline/improved-pipeline",
        "icbmc-upstream": repo / "check-src/benchmark-sources/icbmc/upstream",
        "icbmc-po-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/po-code",
        "icbmc-seq-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/seq-code",
        "icbmc-conc-code": repo / "check-src/benchmark-sources/icbmc/upstream/extracted/conc-code",
        "intabs-upstream": repo / "check-src/benchmark-sources/intabs/upstream/repository",
        "intabs-icbmc": repo / "check-src/benchmark-sources/intabs/upstream/repository/icbmc",
        "intabs-src-test": repo / "check-src/benchmark-sources/intabs/upstream/repository/src/test",
    }

    inventory = {}
    for name, root in roots.items():
        if root.exists():
            inventory[name] = {"path": root.relative_to(repo).as_posix(), **count_source(root)}

    if args.json_out:
        Path(args.json_out).write_text(json.dumps(inventory, indent=2) + "\n", encoding="utf-8")

    lines = [
        "# Benchmark Source Inventory",
        "",
        "| Corpus | Path | C/H/I files | LOC |",
        "| --- | --- | ---: | ---: |",
    ]
    for name, item in inventory.items():
        lines.append(f"| `{name}` | `{item['path']}` | {item['files']} | {item['loc']} |")
    Path(args.md_out).write_text("\n".join(lines) + "\n", encoding="utf-8")
    print(f"inventory entries: {len(inventory)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
