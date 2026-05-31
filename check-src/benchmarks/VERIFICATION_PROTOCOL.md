# Verification Protocol

Use this protocol for headline stock CBMC vs improved CBMC numbers.

1. Record machine information, OS/runtime, CPU, RAM, CBMC paths, CBMC versions,
   branch names, and build type.
2. Run one warmup and five measured runs by default.
3. Use identical `--function`, `--unwind`, `--property`, timeout, and memory
   limit for stock and improved variants.
4. Report median `time_ms` and `max_rss_mb`.
5. Refuse headline speed/RAM deltas when stock and improved verification
   summaries differ.
6. Store raw logs under `$WORK` and CSV/Markdown summaries under
   `check-src/benchmarks/results`.
7. On Windows without WSL, structural self-tests may run, but benchmark RAM
   numbers require Linux/WSL because the sampler reads `/proc/<pid>/status`.

## Docker Command Template

```powershell
docker --config "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc\check-src\benchmarks\work\docker-config" run --rm `
  -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" `
  -w /repo `
  -e STOCK_CBMC=/repo/check-src/benchmarks/work/stock-toolchain/bin/cbmc `
  -e STOCK_GOTOCC=/repo/check-src/benchmarks/work/stock-toolchain/bin/goto-cc `
  -e IMPROVED_CBMC=/repo/cmake-build-debug-cbmc/bin/cbmc `
  -e IMPROVED_GOTOCC=/repo/cmake-build-debug-cbmc/bin/goto-cc `
  -e AIB=/repo/cmake-build-debug-cbmc/bin/aib `
  -e WORK=/repo/check-src/benchmarks/work/run-headline `
  -e RESULTS_DIR=/repo/check-src/benchmarks/results `
  bkmeeting-vpcd-aimet:ubuntu22.04-py310 `
  bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/icbmc-large.json && python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/intabs-large.json && python3 check-src/benchmarks/common/report_benchmark.py"
```

## Failure Interpretation

| Result | Interpretation |
| --- | --- |
| Exit `0` | Command succeeded. |
| Exit `10` | CBMC found a property violation; this can still be comparable when both variants report the same verification class. |
| Exit `6` or `CBMC_UNSUPPORTED_CONCURRENCY` | Not comparable. |
| `TIMEOUT_AFTER_*` | Not comparable. |
| `MEMORY_LIMIT_EXCEEDED_*` | Not comparable. |
| Compile, manifest, or inject failure | Not comparable until the case is fixed or explicitly classified as a failed setup. |
