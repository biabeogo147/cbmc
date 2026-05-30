#!/usr/bin/env bash
set -euo pipefail

manifest=${1:?usage: inject_naive_isr.sh <suite.json> <case-name> <output-root>}
case_name=${2:?usage: inject_naive_isr.sh <suite.json> <case-name> <output-root>}
output_root=${3:?usage: inject_naive_isr.sh <suite.json> <case-name> <output-root>}

PYTHON=${PYTHON:-python3}
"$PYTHON" "$(dirname "${BASH_SOURCE[0]}")/inject_naive.py" "$manifest" "$case_name" "$output_root"
