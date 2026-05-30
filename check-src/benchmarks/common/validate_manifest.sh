#!/usr/bin/env bash
set -euo pipefail

manifest=${1:?usage: validate_manifest.sh <suite.json>}

PYTHON=${PYTHON:-python3}
"$PYTHON" - "$manifest" <<'PY'
import json
import pathlib
import sys

manifest_path = pathlib.Path(sys.argv[1])
repo_root = manifest_path.resolve().parents[3]
data = json.loads(manifest_path.read_text())

for key in ["suite_name", "description", "enabled", "cases"]:
    if key not in data:
        raise SystemExit(f"missing suite field: {key}")

required = [
    "name", "root", "sources", "include_dirs", "isr_sources",
    "isr_functions", "entry_function", "unwind", "timeout_sec",
    "memory_limit_mb",
]

for case in data["cases"]:
    for key in required:
        if key not in case:
            raise SystemExit(f"{case.get('name', '<unnamed>')}: missing {key}")
    if case.get("enabled", True) is False:
        continue
    root = repo_root / case["root"]
    if not root.exists():
        raise SystemExit(f"{case['name']}: missing root {root}")
    for source in case["sources"] + case["isr_sources"]:
        path = root / source
        if not path.exists():
            raise SystemExit(f"{case['name']}: missing source {path}")
    for include_dir in case["include_dirs"]:
        path = root / include_dir
        if not path.exists():
            raise SystemExit(f"{case['name']}: missing include dir {path}")
    if not case["isr_functions"]:
        raise SystemExit(f"{case['name']}: isr_functions must not be empty")

print("manifest ok")
PY
