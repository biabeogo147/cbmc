# check-src Benchmarks

This directory contains the manifest-driven benchmark runner for `check-src`.
Runnable benchmark source corpora live in `check-src/benchmark-sources`; this
directory owns suite manifests, runner scripts, measurement, logs, and result
reporting.

## Main Flow

```text
suite json
  -> run_suite.sh
  -> common/runner.py
  -> stock_cprover_async: stock goto-cc -> stock cbmc
  -> improved_pipeline: improved goto-cc manifest -> aib inject -> improved goto-cc -> improved cbmc
  -> results/<suite>.csv + WORK/logs
```

Supported benchmark variants:

| Variant | Meaning |
| --- | --- |
| `stock_cprover_async` | Stock CBMC baseline using source modeled with `__CPROVER_ASYNC_*` labels. This matches the CPROVER async interrupt style instead of the improved pipeline. |
| `improved_pipeline` | Improved CBMC pipeline: `goto-cc --interleaving-*` emits the manifest, `aib` injects only targeted ISR calls, and improved CBMC verifies the injected program. |

## Files and Folders

| Path | Role |
| --- | --- |
| `.gitignore` | Ignores generated benchmark artifacts: `work/`, CSV/log files in `results/`, and generated summaries. |
| `README.md` | This document. It explains the runner layout and points to detailed pipeline/configuration docs. |
| `PIPELINE.md` | Step-by-step source-to-CSV pipeline documentation, including current time/RAM measurement limitations. |
| `VERIFICATION_PROTOCOL.md` | Reporting rules: record environment, tool versions, function/unwind/property settings, and only compare compatible verification outcomes. |
| `manifest.schema.json` | JSON schema for suite manifests. Useful for checking required fields and expected types. |
| `run_suite.sh` | Entrypoint for one suite. It loads `common/env.sh` and calls `common/runner.py <suite.json>`. |
| `run_all.sh` | Scans `suites/*.json` and runs only top-level suites with `enabled: true`. |
| `common/env.sh` | Default environment variables for repo paths, stock/improved tools, `aib`, `WORK`, `RESULTS_DIR`, and `PYTHON`. |
| `common/runner.py` | Main runner. It validates manifests, copies variant sources, runs phases, samples peak RSS from `/proc/<pid>/status`, enforces timeout/RSS limits, and writes CSV rows. |
| `common/atomic_wrap_functions.py` | Ensures staged ISR/task entry functions are wrapped in `__CPROVER_atomic_begin/end` when normalizing benchmark inputs. |
| `common/report_benchmark.py` | Generates `check-src/benchmark.md` from measured CSV files, suite manifests, and source inventory. It computes medians and refuses speed/RAM deltas for not-comparable verification outcomes. |
| `common/corpus_inventory.py` | Counts C/H/I files and LOC in managed benchmark corpora and writes `benchmark-sources/INVENTORY.md`. |
| `common/candidate_scan.py` | Ranks upstream i-CBMC/IntAbs candidate source files by LOC and interrupt/concurrency markers. |
| `common/normalize_case.py` | Creates staged normalized case directories with `stock-cprover-async` and `improved-pipeline` variants from selected single-file upstream cases. |
| `results/` | CSV output directory. Generated CSV files are ignored so temporary machine-specific measurements are not committed by accident. |
| `results/.gitkeep` | Keeps `results/` present in git without committing generated CSV data. |
| `suites/` | Suite manifest directory. Add or enable benchmark cases here. |
| `tests/selftest.ps1` | Windows structural test. It parses suite JSON, checks enabled case paths, and verifies the top-level `check-src` README documents visible items. |
| `work/` | Generated work area: copied sources, injected sources, GOTO binaries, logs, downloaded stock toolchain, and import staging. This directory is ignored. |

## Environment Variables

`common/env.sh` defines defaults. Override these in Docker/WSL/Linux when needed:

| Variable | Default | Effect |
| --- | --- | --- |
| `IMPROVED_CBMC` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/cbmc` | Improved CBMC used for `improved_pipeline` verification. |
| `IMPROVED_GOTOCC` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/goto-cc` | Improved `goto-cc` used to emit interleaving manifests and compile injected source. |
| `STOCK_CBMC` | `$IMPROVED_CBMC` | Stock CBMC used for `stock_cprover_async`. For real comparisons this should point to the extracted stock binary, for example CBMC 5.95.0 from `diffblue/cbmc`. |
| `STOCK_GOTOCC` | `$IMPROVED_GOTOCC` | Stock `goto-cc` used for stock variants. |
| `AIB` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/aib` | Interleaving injector that consumes the manifest emitted by improved `goto-cc`. |
| `WORK` | `/tmp/cbmc_check_src_benchmarks` | Temporary run directory for copied source, injected source, GOTO files, and logs. Docker runs in this repo usually set it to `check-src/benchmarks/work/<run-name>`. |
| `RESULTS_DIR` | `$BENCHMARK_DIR/results` | Directory for CSV output. |
| `PYTHON` | `python3` | Python interpreter for runner/helper scripts. |

## Suite JSON

Suite JSON configuration is documented in one place: `PIPELINE.md`.

Use these sections when adding or changing benchmark cases:

| Topic | Where |
| --- | --- |
| Full JSON example | `PIPELINE.md#suite-json-configuration` |
| Top-level suite fields | `PIPELINE.md#top-level-fields` |
| Case fields | `PIPELINE.md#case-fields` |
| Recommended source layout | `PIPELINE.md#source-layout-recommendation` |
| `variant_sources` and `variant_isr_sources` patterns | `PIPELINE.md#common-configuration-patterns` |

## Current Suites

| Suite | Enabled | Purpose |
| --- | --- | --- |
| `local-smoke.json` | Yes | Small local ISR smoke tests under `simple-benchmarks`. |
| `osek-local.json` | Yes | Local OSEK event/priority demos. Some regression cases remain disabled until they have explicit ISR source metadata. |
| `trampoline-current.json` | Yes | Main Trampoline `alarms_s1_non` benchmark. Stock uses `stock-cprover-async`; improved uses `improved-pipeline`. |
| `trampoline-c-async.json` | Yes | Historical stock-only Trampoline CPROVER async tree. |
| `trampoline-expanded.json` | Yes | Full-source Trampoline/OSEK suite using the same normalized source family as the current benchmark. |
| `icbmc-large.json` | Yes | Normalized large i-CBMC cases under `benchmark-sources/icbmc/cases`. |
| `intabs-large.json` | Yes | Normalized large IntAbs cases under `benchmark-sources/intabs/cases`. |

## Output and Logs

CSV columns:

| Column | Meaning |
| --- | --- |
| `benchmark` | Suite name. |
| `case` | Case name. |
| `variant` | Variant name, for example `stock_cprover_async` or `improved_pipeline`. |
| `phase` | `prepare`, `compile`, `verify`, `manifest`, or `inject`. |
| `run` | Run id within `run_kind`. Measured and warmup phases start at `1`; prepare rows use the same run id as the variant run they describe. |
| `run_kind` | `warmup`, `measure`, or `prepare`. Report generation ignores `warmup`. |
| `exit_code` | Command exit code. CBMC commonly returns `10` for verification failure. |
| `time_ms` | Wall-clock time measured by the runner. |
| `max_rss_kb` / `max_rss_mb` | Peak RSS sampled from `/proc/<pid>/status`; use Docker/WSL/Linux for meaningful values. |
| `summary` | Short result extracted from the log, such as `VERIFICATION FAILED`, `VERIFICATION SUCCESSFUL`, or `CBMC_UNSUPPORTED_CONCURRENCY`. |

Detailed logs are written to `$WORK/logs`:

```text
<suite>.<case>.<variant>.<phase>.<run>.log
```

Typical generated source folders under `$WORK/<suite>/<case>/`:

| Folder/file | Meaning |
| --- | --- |
| `stock_cprover_async/` | Stock source tree using CPROVER async labels. |
| `improved_pipeline_original/` | Improved source tree before AIB injection. |
| `improved_pipeline/` | Source tree after AIB injection. |
| `*.out` | GOTO binaries produced by `goto-cc`. |
| `*_interleaving_pipeline.json` | Manifest emitted by improved `goto-cc`. |
| `interleaving_pipeline_injected.json` | Manifest emitted by `aib` for the injected tree. |

## Adding a Benchmark

1. Put runnable source under `check-src/benchmark-sources/<corpus>/<case>/`.
2. Use two variant roots: `stock-cprover-async` and `improved-pipeline`.
3. Create or update `check-src/benchmarks/suites/<suite>.json`.
4. Fill `variant_roots`, `sources`, `include_dirs`, `isr_sources`, `isr_functions`, `entry_function`, `unwind`, `timeout_sec`, and `memory_limit_mb`.
5. Run a dry-run:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json --dry-run
```

6. Run the real benchmark inside Docker/WSL/Linux to collect RSS:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/<suite>.json
```

7. Regenerate the Markdown report:

```bash
python3 check-src/benchmarks/common/report_benchmark.py
```

External i-CBMC and IntAbs cases must remain out of headline reports until the
suite has at least five enabled normalized cases or at least 5000 enabled
compile LOC, and every enabled case has comparable or explicitly not-comparable
verification outcomes.

The complete suite JSON example and field-by-field guidance live in
`PIPELINE.md`.
