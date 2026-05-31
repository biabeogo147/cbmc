#!/usr/bin/env bash
# Shared environment defaults for benchmark shell entry points.
#
# Inputs:
#   - Optional environment overrides supplied by Docker/WSL/Linux callers.
#   - Repository layout relative to this file.
#
# Outputs:
#   - Exports shell variables used by run_suite.sh and runner.py.
#   - Ensures WORK and RESULTS_DIR directories exist.
#
# Important variables:
#   IMPROVED_CBMC / IMPROVED_GOTOCC: improved toolchain under test.
#   STOCK_CBMC / STOCK_GOTOCC: stock baseline toolchain.
#   AIB: interleaving injector used by improved_pipeline.
#   WORK: copied source trees, generated GOTO files, and logs.
#   RESULTS_DIR: suite CSV output directory.
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
