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

Legacy suites can still use:

| Variant | Meaning |
| --- | --- |
| `stock_naive` | Copy a source tree, insert nondeterministic ISR calls with `inject_naive.py`, compile with stock `goto-cc`, then verify with stock CBMC. |
| `improved_targeted` | Historical name for the improved pipeline. It is kept for older local smoke tests. |

The preferred benchmark variants are:

| Variant | Meaning |
| --- | --- |
| `stock_cprover_async` | Stock CBMC baseline using source modeled with `__CPROVER_ASYNC_*` labels. This matches the CPROVER async interrupt style instead of the improved pipeline. |
| `improved_pipeline` | Improved CBMC pipeline: `goto-cc --interleaving-*` emits the manifest, `aib` injects only targeted ISR calls, and improved CBMC verifies the injected program. |

## Files and Folders

| Path | Role |
| --- | --- |
| `.gitignore` | Ignores generated benchmark artifacts: `work/`, CSV/log files in `results/`, and generated summaries. |
| `README.md` | This document. It explains the runner layout and each suite/config field. |
| `VERIFICATION_PROTOCOL.md` | Reporting rules: record environment, tool versions, function/unwind/property settings, and only compare compatible verification outcomes. |
| `manifest.schema.json` | JSON schema for suite manifests. Useful for checking required fields and expected types. |
| `run_suite.sh` | Entrypoint for one suite. It loads `common/env.sh` and calls `common/runner.py <suite.json>`. |
| `run_all.sh` | Scans `suites/*.json` and runs only top-level suites with `enabled: true`. |
| `common/env.sh` | Default environment variables for repo paths, stock/improved tools, `aib`, `WORK`, `RESULTS_DIR`, and `PYTHON`. |
| `common/runner.py` | Main runner. It validates manifests, copies variant sources, runs phases, samples peak RSS from `/proc/<pid>/status`, enforces timeout/RSS limits, and writes CSV rows. |
| `common/inject_naive.py` | Legacy `stock_naive` source rewriter. It inserts guarded calls to ISR functions after candidate statements. |
| `common/inject_naive_isr.sh` | Small shell wrapper around `inject_naive.py` for manual injection tests. |
| `common/measure.sh` | Shell measurement helper retained for legacy scripts. `runner.py` has its own measurement logic. |
| `common/report.sh` | Reads CSV files in `results/` and writes a summary Markdown report. |
| `common/report_benchmark.py` | Generates `check-src/benchmark.md` from measured CSV files, suite manifests, and source inventory. It computes medians and refuses speed/RAM deltas for not-comparable verification outcomes. |
| `common/corpus_inventory.py` | Counts C/H/I files and LOC in managed benchmark corpora and writes `benchmark-sources/INVENTORY.md`. |
| `common/candidate_scan.py` | Ranks upstream i-CBMC/IntAbs candidate source files by LOC and interrupt/concurrency markers. |
| `common/normalize_case.py` | Creates staged normalized case directories with `stock-cprover-async` and `improved-pipeline` variants from selected single-file upstream cases. |
| `common/validate_manifest.sh` | Shell-side manifest validator for required fields and enabled-case paths. |
| `importers/` | Import/normalization notes for external benchmark artifacts. Current runnable normalized sources are stored under `check-src/benchmark-sources`. |
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
| `STOCK_CBMC` | `$IMPROVED_CBMC` | Stock CBMC used for `stock_cprover_async` and `stock_naive`. For real comparisons this should point to the extracted stock binary, for example CBMC 5.95.0 from `diffblue/cbmc`. |
| `STOCK_GOTOCC` | `$IMPROVED_GOTOCC` | Stock `goto-cc` used for stock variants. |
| `AIB` | `$REPO_ROOT/cmake-build-debug-cbmc/bin/aib` | Interleaving injector that consumes the manifest emitted by improved `goto-cc`. |
| `WORK` | `/tmp/cbmc_check_src_benchmarks` | Temporary run directory for copied source, injected source, GOTO files, and logs. Docker runs in this repo usually set it to `check-src/benchmarks/work/<run-name>`. |
| `RESULTS_DIR` | `$BENCHMARK_DIR/results` | Directory for CSV output. |
| `PYTHON` | `python3` | Python interpreter for runner/helper scripts. |

## Suite JSON

Each file in `suites/*.json` contains one top-level suite and a list of cases.
All paths are relative to the repository root.

### Top-Level Fields

| Field | Required | Used by runner? | Meaning |
| --- | --- | --- | --- |
| `suite_name` | Yes | Yes | Suite name used in console output, log names, and `results/<suite_name>.csv`. |
| `description` | Yes | Metadata | Short human-readable suite description. |
| `enabled` | Yes | Used by `run_all.sh` | `run_all.sh` only runs suites with `enabled: true`; direct `runner.py <suite.json>` still runs the specified file. |
| `runs` | No | Yes | Number of measured runs per enabled case and variant. Defaults to `1`. |
| `warmups` | No | Yes | Number of warmup runs per enabled case and variant. Defaults to `0`; warmup rows are ignored by the generated report. |
| `variants` | No | Yes | Variant order for each enabled case. Preferred values are `stock_cprover_async` and `improved_pipeline`. |
| `cases` | Yes | Yes | Benchmark case list. Disabled cases are skipped. |

### Case Fields

| Field | Required | Used by runner? | Meaning |
| --- | --- | --- | --- |
| `name` | Yes | Yes | Case name used in console output, CSV rows, log files, and `WORK/<suite>/<case>/`. |
| `enabled` | No | Yes | `false` skips the case. |
| `reason` | No | Metadata | Explanation for disabled cases or normalization notes. |
| `root` | Yes | Yes | Default source root, relative to repo root. Used when a variant-specific root is not provided. |
| `variant_roots` | No | Yes | Per-variant source roots. Use this to keep stock CPROVER async source separate from improved pipeline source. |
| `sources` | Yes | Yes | Files compiled by `goto-cc`, relative to the selected variant root. |
| `include_dirs` | Yes | Yes | Include directories, relative to the selected variant root; runner converts these to `-I<root>/<dir>`. |
| `isr_sources` | Yes | Yes | Files containing ISR functions. Improved `goto-cc` receives these through `--interleaving-source-files`. |
| `isr_functions` | Yes | Yes | ISR function names. Used by `stock_naive`; retained as manifest metadata for the preferred variants. |
| `entry_function` | Yes | Yes | Function passed to `cbmc --function`. Usually `main`. |
| `properties` | No | Yes | Optional list of property IDs passed with `--property`. Empty means CBMC uses the command's default checks. |
| `unwind` | Yes | Yes | Value passed to `cbmc --unwind`. |
| `defines` | No | Yes | Macro definitions passed to `goto-cc` as `-D...`. |
| `expected_result` | No | Metadata | Expected relationship between variants. It is documented but not enforced. |
| `expected_summary` | No | Metadata | Expected CBMC summary class for later review, for example `success`, `failed`, or `pending`. |
| `case_origin` | No | Metadata | Upstream corpus path used to normalize the case. |
| `min_compile_loc` | No | Yes | Minimum LOC across files in `sources` for each selected variant root. Enabled cases below this gate fail manifest validation. |
| `timeout_sec` | Yes | Yes | Per-command wall-clock timeout. Runner kills the command and records `TIMEOUT_AFTER_<n>s`. |
| `memory_limit_mb` | Yes | Yes | Per-command peak RSS limit. Runner kills the command and records `MEMORY_LIMIT_EXCEEDED_<n>MB`. |

## Current Suites

| Suite | Enabled | Purpose |
| --- | --- | --- |
| `local-smoke.json` | Yes | Small local ISR smoke tests under `simple-benchmarks`. They keep the legacy `stock_naive`/`improved_targeted` flow for fast framework checks. |
| `osek-local.json` | Yes | Local OSEK event/priority demos. Some regression cases remain disabled until they have explicit ISR source metadata. |
| `trampoline-current.json` | Yes | Main Trampoline `alarms_s1_non` benchmark. Stock uses `stock-cprover-async`; improved uses `improved-pipeline`. |
| `trampoline-c-async.json` | Yes | Historical stock-only Trampoline CPROVER async tree. |
| `trampoline-expanded.json` | No | Placeholder for larger Trampoline cases after hardware-specific inputs are stubbed. |
| `icbmc-interrupts.json` | No | Full i-CBMC corpus is collected under `benchmark-sources/icbmc/upstream`; current Logger case is smoke-only until larger cases are normalized. |
| `intabs-interrupts.json` | No | Full IntAbs corpus is collected under `benchmark-sources/intabs/upstream`; current Logger2 case is smoke-only until larger cases are normalized. |
| `icbmc-large.json` | No | Staged normalized large i-CBMC cases under `benchmark-sources/icbmc/cases`. Cases stay disabled until both variants compile and verify in Docker. |
| `intabs-large.json` | No | Staged normalized large IntAbs cases under `benchmark-sources/intabs/cases`. Cases stay disabled until both variants compile and verify in Docker. |

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
| `stock_naive/` | Legacy source tree after naive ISR insertion. |
| `*.out` | GOTO binaries produced by `goto-cc`. |
| `*_interleaving_pipeline.json` | Manifest emitted by improved `goto-cc`. |
| `interleaving_pipeline_injected.json` | Manifest emitted by `aib` for the injected tree. |
| `stock_naive_insertions.csv` | Legacy naive insertion counts. |

## Adding a Benchmark

1. Put runnable source under `check-src/benchmark-sources/<corpus>/<case>/`.
2. Prefer two variant roots: `stock-cprover-async` and `improved-pipeline`.
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
