#!/usr/bin/env bash
set -euo pipefail

suite_dir="$(dirname "${BASH_SOURCE[0]}")/suites"
for manifest in "$suite_dir"/*.json; do
  PYTHON=${PYTHON:-python3}
  "$PYTHON" - "$manifest" <<'PY' | grep -q '^True$' || continue
import json
import pathlib
import sys
print(json.loads(pathlib.Path(sys.argv[1]).read_text()).get("enabled", False))
PY
  bash "$(dirname "${BASH_SOURCE[0]}")/run_suite.sh" "$manifest" "$@"
done

if [ "${1:-}" != "--dry-run" ]; then
  common_dir="$(dirname "${BASH_SOURCE[0]}")/common"
  "${PYTHON:-python3}" "$common_dir/benchmark_inventory.py" --inventory-only
  "${PYTHON:-python3}" "$common_dir/global_effect_scan.py"
  "${PYTHON:-python3}" "$common_dir/outcome_mismatch_audit.py"
  "${PYTHON:-python3}" "$common_dir/report_benchmark.py"
fi
