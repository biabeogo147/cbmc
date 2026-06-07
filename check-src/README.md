# check-src Benchmark Workspace

`check-src` contains the benchmark sources, suite manifests, runner scripts, and
generated comparison report used to compare stock CBMC with the improved
interleaving pipeline.

## Generated Report

| File | Purpose |
| --- | --- |
| `benchmark.md` | Single generated Markdown report. It includes every measured case, stock output, improved output, correctness judgment, total time, peak RAM, speed/RAM deltas, output-mismatch evidence, timeout/memory diagnostics, and no-injection audit results. |

The benchmark pipeline does not generate any other Markdown report. Audit
helpers write CSV/log artifacts that are folded into `benchmark.md` by
`report_benchmark.py`.

## Quick Start

Run one suite in Docker/Linux/WSL:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json
```

Run all enabled suites and regenerate the report:

```bash
bash check-src/benchmarks/run_all.sh
python3 check-src/benchmarks/common/benchmark_inventory.py --inventory-only
python3 check-src/benchmarks/common/global_effect_scan.py
python3 check-src/benchmarks/common/outcome_mismatch_audit.py
python3 check-src/benchmarks/common/report_benchmark.py
```

Run the Windows structural self-test:

```powershell
PowerShell -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

## Benchmark Pipeline

```text
suite JSON
  -> run_suite.sh or run_all.sh
  -> common/env.sh
  -> common/runner.py
  -> stock_cprover_async:
       copy source
       -> goto-cc
       -> cbmc with C_ASYNC_PROVER-style source modeling
  -> improved_pipeline:
       copy source
       -> goto-cc interleaving manifest
       -> AIB inject
       -> goto-cc
       -> cbmc
  -> results/<suite>.csv
  -> common/benchmark_inventory.py
  -> common/global_effect_scan.py
  -> common/outcome_mismatch_audit.py
  -> common/report_benchmark.py
  -> benchmark.md
```

The runner ignores warmup rows when generating reports. It measures wall-clock
time per phase and samples peak RSS from `/proc/<pid>/status`, so benchmark RAM
numbers should be collected inside Docker, Linux, or WSL.

## Suite JSON Configuration

Suite manifests live under `check-src/benchmarks/suites/*.json`.

Top-level fields:

| Field | Meaning |
| --- | --- |
| `suite_name` | Stable suite id. It becomes `results/<suite_name>.csv` and report heading. |
| `description` | Human-readable suite purpose. |
| `enabled` | `run_all.sh` only runs suites with `enabled: true`; explicit `run_suite.sh` can still run disabled diagnostic suites. |
| `runs` / `warmups` | Measured and warmup run counts. Reports ignore warmups. |
| `variants` | Usually `["stock_cprover_async", "improved_pipeline"]`. |
| `cases` | Case declarations. |

Important case fields:

| Field | Meaning |
| --- | --- |
| `name` | Stable case id used in console output, CSV, logs, and reports. |
| `enabled` / `reason` | Case-level run gate and explanation for disabled cases. |
| `root` / `variant_roots` | Source roots. Use separate `stock-cprover-async` and `improved-pipeline` roots when modeling differs. |
| `sources` / `variant_sources` | Compile units passed to `goto-cc`. |
| `include_dirs` / `variant_include_dirs` | Include directories relative to each variant root. |
| `isr_sources` / `variant_isr_sources` | Files passed to improved `goto-cc --interleaving-source-files`. |
| `isr_functions` | ISR/task entry functions used to filter improved interleaving candidates. |
| `entry_function` | Function passed to `cbmc --function`. |
| `properties` | Optional CBMC property ids. Empty means default selected checks. |
| `unwind` | Bound passed to CBMC. Keep stock and improved equal. |
| `cbmc_args` / `variant_cbmc_args` | Shared or variant-specific CBMC arguments. |
| `timeout_sec` / `memory_limit_mb` | Per-command time and RSS limits. |
| `case_origin` | Traceability back to upstream source. |

Recommended source layout:

```text
check-src/benchmark-sources/<corpus>/cases/<case>/
  stock-cprover-async/
    main.c
  improved-pipeline/
    main.c
    isr_define/
      isr.c
      isr.h
```

For monolithic upstream files with heavy `static` state, keep `main.c` as the
only direct compile source and include extracted ISR source at the original
definition point:

```c
#include "isr_define/isr.c"
```

## Variant Semantics

| Variant | Meaning |
| --- | --- |
| `stock_cprover_async` | Stock CBMC baseline using source modeled with `__CPROVER_ASYNC_*` / C_ASYNC_PROVER-style labels. This is the correct stock-side modeling path because stock CBMC does not run the improved interleaving injection pipeline. |
| `improved_pipeline` | Improved flow using `goto-cc --interleaving-*`, AIB injection, compile, and CBMC verification. ISR/task entries are modeled as atomic benchmark entry points. |

## Common Scripts

| Script | Role | Main input | Main output |
| --- | --- | --- | --- |
| `env.sh` | Resolves benchmark paths, CBMC binaries, AIB path, Docker/container defaults, timeout knobs, memory knobs, work directory, and results directory. | Environment variables and repo layout. | Shell variables consumed by runner scripts. |
| `runner.py` | Validates suite cases, copies variant source trees, runs stock/improved phases, measures wall time and RSS, normalizes exit status, extracts summaries, and writes raw CSV rows. | Suite JSON, source roots, CBMC/goto-cc/AIB binaries. | `results/<suite>.csv`, logs, copied work trees, generated GOTO binaries. |
| `benchmark_inventory.py` | Builds a deduplicated diagnostic inventory directly from suite JSON and raw result CSV. It does not read Markdown. | Suite JSON and `results/*.csv`. | `results/audit/benchmark-inventory.csv`. |
| `global_effect_scan.py` | Audits `NO_INJECTION_CANDIDATES`. A no-injection result is valid only when no ISR-written global can affect a global reachable from `main`. | `benchmark-inventory.csv`, suite JSON, improved source roots. | `results/audit/no-injection-audit.csv`. |
| `outcome_mismatch_audit.py` | Records correctness evidence for cases where stock and improved verification outputs differ. | `benchmark-inventory.csv`, evidence CSV/logs. | `results/audit/outcome-mismatch-audit.csv`. |
| `run_evidence_case.py` | Creates and runs a focused evidence suite for one case with trace-friendly CBMC args. | Suite JSON and selected case name. | Evidence CSV/logs under `results/audit/` and `work/audit/`. |
| `report_benchmark.py` | Joins raw benchmark CSV, suite metadata, diagnostic inventory, no-injection audit, and outcome-mismatch audit into the single Markdown report. | `results/*.csv`, suite JSON, audit CSVs. | `check-src/benchmark.md`. |
| `atomic_wrap_functions.py` | Wraps selected ISR functions with CBMC atomic begin/end calls while preserving early returns. | C source file and function names. | Rewritten C source file. |
| `candidate_scan.py` | Ranks upstream source files that look promising for future ISR/concurrency benchmark normalization. | i-CBMC and IntAbs upstream trees. | `results/audit/candidate-scan.csv`. |
| `corpus_inventory.py` | Counts C/H/I files and LOC for managed source corpora. | Source corpus roots. | Optional JSON inventory. |
| `normalize_case.py` | Normalizes imported cases into the local benchmark source layout and writes concise case metadata text. | Upstream case files. | Normalized case folders. |
| `split_improved_case.py` | Splits source layout when stock C_ASYNC_PROVER modeling and improved pipeline modeling need different source trees. | Normalized case source tree. | Variant-specific source files. |

## Output CSV

CSV files are written under `check-src/benchmarks/results/`.

| Column | Meaning |
| --- | --- |
| `benchmark` | Suite name. |
| `case` | Case name. |
| `variant` | Stock or improved variant id. |
| `phase` | `prepare`, `manifest`, `inject`, `compile`, or `verify`. |
| `run` / `run_kind` | Run id and `warmup`, `measure`, or `prepare`. |
| `exit_code` | Command exit code. CBMC commonly returns `10` for verification failure. |
| `time_ms` | Wall-clock time measured by the runner. |
| `max_rss_kb` / `max_rss_mb` | Peak RSS sampled from `/proc/<pid>/status`. |
| `summary` | Extracted result such as `VERIFICATION SUCCESSFUL`, `VERIFICATION FAILED`, `CBMC_UNSUPPORTED_CONCURRENCY`, `TIMEOUT_AFTER_*`, or `NO_INJECTION_CANDIDATES`. |

Logs and copied/injected source trees are written under `$WORK`; generated work
directories are not source-of-truth and may be deleted after reports are
generated.

## Correctness Policy

`benchmark.md` always compares performance when both variants have measured
rows, even when outputs differ. Matching outputs are labeled correct for both
variants. When outputs differ, the report uses audit CSVs under
`check-src/benchmarks/results/audit/` to state whether stock or improved is
judged correct and why.

Common verdicts:

| Verdict | Meaning |
| --- | --- |
| `same_outcome_comparable` | Stock and improved produce the same verification class. |
| `improved_correct` | Improved matches the intended ISR/task atomic model better than stock. |
| `stock_correct` | Stock is judged more faithful for that case. |
| `no_injection_false` | Improved reported no injection candidates although ISR-written globals affect main-reachable state. |
| `no_injection_true` | The no-injection result is valid because ISR-written globals do not affect main-reachable globals and no conservative blocker was found. |
| `needs_manual_review` | Audit evidence is not enough to decide correctness safely. |
| `both_need_fix` | A model/tool issue must be fixed before trusting either output. |

## Source Corpora

| Corpus | Location | Notes |
| --- | --- | --- |
| Trampoline | `benchmark-sources/trampoline/` | Two normalized variants: stock CPROVER async and improved pipeline. |
| i-CBMC | `benchmark-sources/icbmc/` | Upstream CPROVER i-CBMC artifacts plus normalized runnable cases. |
| IntAbs | `benchmark-sources/intabs/` | Snapshot of the IntAbs repository plus normalized runnable cases. |
| Local/simple | `simple-benchmarks/` | Small smoke and OSEK examples retained for regression coverage. |

## Benchmark Source Provenance

The benchmark set intentionally mixes three source families. They all exercise
interrupt-driven C code, but they stress different parts of the comparison:
i-CBMC provides published CBMC-style interrupt models, IntAbs provides a second
published interrupt-analysis artifact with different examples and Linux-driver
fragments, and Trampoline provides a real RTOS/OSEK code base with larger source
trees.

| Corpus | Public source | Local source used | Selected material | Why it is useful | Trust and limitations |
| --- | --- | --- | --- | --- | --- |
| i-CBMC | `https://www.cprover.org/interrupts/` | `benchmark-sources/icbmc/upstream/archives/` and `benchmark-sources/icbmc/upstream/extracted/` | `po-code`, `seq-code`, and `conc-code` archives; normalized cases under `benchmark-sources/icbmc/cases/`. | This is the closest baseline to stock CBMC interrupt modeling because the project documents `__CPROVER_ASYNC_: isr();` and compares i-CBMC against source-to-source sequentialization and threaded instrumentation. The published benchmark families include Logger, Blink, Brake, and RcCore. | High relevance for ISR model checking because it comes from the CPROVER interrupt-verification work and includes source plus experimental logs. It is still a research artifact, so local normalization is required to split stock C_ASYNC_PROVER modeling from the improved interleaving pipeline. |
| IntAbs | `https://github.com/ChunghaSung/intAbs` and `https://chunghasung.org/pub/` | `benchmark-sources/intabs/upstream/repository/` | Upstream `icbmc/` and `src/test/` cases; normalized runnable cases under `benchmark-sources/intabs/cases/`. | IntAbs is an ASE 2017 artifact for modular verification of interrupt-driven software. It gives an independent set of interrupt examples, including logger/blink/brake-style cases and Linux watchdog/TCO driver fragments, which helps avoid evaluating only on i-CBMC-derived models. | Useful and credible because the repository is linked as the artifact for the ASE 2017 paper. Its README says files are not fully cleaned up, so the benchmark uses normalized copies instead of treating every upstream file as runnable as-is. |
| Trampoline RTOS | `https://github.com/TrampolineRTOS/trampoline` | `benchmark-sources/trampoline/stock-cprover-async/` and `benchmark-sources/trampoline/improved-pipeline/` | Full-source and focused OSEK/Trampoline alarm examples, especially the alarms S1 non case. | Trampoline is a real static RTOS aligned with OSEK/VDX and AUTOSAR OS APIs. It is larger than the research micro-benchmarks and stresses compile/manifest/injection scalability on realistic RTOS source structure. | Good engineering benchmark because it is an active open-source RTOS with public source. It is not originally a CBMC interrupt benchmark, so this repo maintains explicit stock and improved modeling roots to make the comparison fair. |
| Local/simple | This repository | `simple-benchmarks/` | `t_isr_multifile`, `osek_priority_interleaving`, `osek_event_interleaving`, and small regression cases. | These cases are small enough to debug pipeline regressions quickly and document the expected `isr_define/` layout. | Useful for smoke testing only; they are not sufficient for performance claims because the LOC and state space are intentionally small. |

Source selection policy:

- Prefer cases with explicit ISR functions, shared global state, or OSEK/driver
  behavior that can affect `main`.
- Keep stock and improved source roots separate when the modeling contract
  differs: stock uses C_ASYNC_PROVER-style source modeling; improved uses
  interleaving manifest generation and AIB injection.
- Retain upstream snapshots under `benchmark-sources/*/upstream/` and run
  benchmarks from normalized case directories under `benchmark-sources/*/cases/`.
- Treat published artifacts as credible starting points, but trust benchmark
  results only after the local suite compiles, runs in Docker, and records both
  performance and correctness evidence in `benchmark.md`.

## Active Suites

| Suite | Purpose |
| --- | --- |
| `local-smoke.json` | Small ISR smoke tests. |
| `osek-local.json` | OSEK event and priority interleaving demos. |
| `trampoline-current.json` | Main Trampoline improved-vs-stock benchmark. |
| `trampoline-expanded.json` | Full-source Trampoline/OSEK benchmark. |
| `icbmc-large.json` | Normalized i-CBMC cases. |
| `intabs-large.json` | Normalized IntAbs cases. |
| `icbmc-timeout-30m*.json` | Explicit diagnostic suites for timeout/high-memory/logger evidence. |

Historical stock-only source trees can remain under `benchmark-sources/` for
traceability, but benchmark suites must include both `stock_cprover_async` and
`improved_pipeline` unless they are an explicit diagnostic suite.

## Tool Environment

`check-src/benchmarks/common/env.sh` defines default paths. Override these in
Docker/WSL/Linux when needed:

| Variable | Effect |
| --- | --- |
| `STOCK_CBMC`, `STOCK_GOTOCC` | Stock CBMC and `goto-cc`. |
| `IMPROVED_CBMC`, `IMPROVED_GOTOCC` | Improved CBMC and `goto-cc`. |
| `AIB` | Interleaving injector. |
| `WORK` | Temporary run directory for copied sources, logs, and GOTO binaries. |
| `RESULTS_DIR` | Output directory for CSV files. |
| `PYTHON` | Python interpreter for runner/helper scripts. |
