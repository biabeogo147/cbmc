#!/usr/bin/env python3
"""Count source files and LOC for managed benchmark corpora.

Inputs:
  - --repo-root: repository root, default current directory.
  - Known corpus directories under check-src/benchmark-sources.

Outputs:
  - Optional JSON inventory when --json-out is provided.

The main benchmark report computes source inventory directly, so this helper is
for ad-hoc inspection only.
"""

import argparse
import json
from pathlib import Path


SOURCE_SUFFIXES = {".c", ".h", ".i"}


def count_source(root: Path):
    """Return number of C/H/I files and total line count under root.

    Args:
        root: Directory to scan recursively.

    Returns:
        Dictionary with file count and LOC count.
    """
    files = [path for path in root.rglob("*") if path.is_file() and path.suffix in SOURCE_SUFFIXES]
    loc = 0
    for path in files:
        loc += len(path.read_text(errors="ignore").splitlines())
    return {"files": len(files), "loc": loc}


def main(argv=None):
    """CLI entry point that writes a JSON inventory file.

    Args:
        argv: Optional command-line argument list. When None, argparse reads
            from sys.argv.

    Returns:
        Process-style exit code. Returns 0 on success.
    """
    parser = argparse.ArgumentParser()
    parser.add_argument("--repo-root", default=".")
    parser.add_argument("--json-out")
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

    print(f"inventory entries: {len(inventory)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
