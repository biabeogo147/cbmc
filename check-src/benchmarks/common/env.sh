#!/usr/bin/env bash
set -euo pipefail

BENCHMARK_DIR=$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)
REPO_ROOT=$(cd "$BENCHMARK_DIR/../.." && pwd)

IMPROVED_CBMC=${IMPROVED_CBMC:-"$REPO_ROOT/cmake-build-debug-cbmc/bin/cbmc"}
IMPROVED_GOTOCC=${IMPROVED_GOTOCC:-"$REPO_ROOT/cmake-build-debug-cbmc/bin/goto-cc"}
STOCK_CBMC=${STOCK_CBMC:-"$IMPROVED_CBMC"}
STOCK_GOTOCC=${STOCK_GOTOCC:-"$IMPROVED_GOTOCC"}
AIB=${AIB:-"$REPO_ROOT/cmake-build-debug-cbmc/bin/aib"}
WORK=${WORK:-"/tmp/cbmc_check_src_benchmarks"}
RESULTS_DIR=${RESULTS_DIR:-"$BENCHMARK_DIR/results"}
PYTHON=${PYTHON:-python3}

mkdir -p "$WORK" "$RESULTS_DIR"
