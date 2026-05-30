#!/usr/bin/env bash
set -euo pipefail

SCRIPT_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)
REPO_ROOT=$(cd "$SCRIPT_DIR/.." && pwd)

echo "isr_large_benchmark.sh is now a compatibility wrapper."
echo "Prefer: bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json"
echo

cd "$REPO_ROOT"
exec bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json "$@"
