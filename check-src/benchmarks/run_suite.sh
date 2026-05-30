#!/usr/bin/env bash
set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/common/env.sh"

manifest=${1:?usage: run_suite.sh <suite.json> [--dry-run]}
shift || true

exec "$PYTHON" "$BENCHMARK_DIR/common/runner.py" "$manifest" "$@"
