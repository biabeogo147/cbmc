# check-src Benchmark Workspace

`check-src` contains the benchmark framework, runnable benchmark source corpora,
legacy local experiments, and the latest benchmark report.

## Quick Start

On Linux, WSL, or Docker-like shells:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json
```

On Windows without WSL, use the structural self-test:

```powershell
PowerShell -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

## Top-Level Content

| Item | Role | Notes |
| --- | --- | --- |
| `benchmark.md` | Comparable benchmark report | Docker-measured stock CBMC vs improved CBMC cases whose verification outcomes can be compared. |
| `uncomparable.md` | Non-comparable benchmark report | Cases that cannot be compared directly, including unsupported concurrency, different verification outcomes, missing measured rows, or no injection candidates. |
| `benchmark-sources/` | Managed source corpora | Runnable benchmark source roots. Each larger case should keep stock CPROVER async and improved pipeline variants here. |
| `benchmarks/` | Framework | Suite manifests, runner, measurement, documentation, logs, and result output. |
| `simple-benchmarks/` | Legacy local inputs | Small demos and OSEK cases retained for smoke tests. Trampoline was moved out to `benchmark-sources/`. |

## Benchmark Sources

| Item | Suite or role | Notes |
| --- | --- | --- |
| `benchmark-sources/trampoline/improved-pipeline/` | `trampoline-current.json` | Trampoline source modeled for the improved CBMC interleaving pipeline. |
| `benchmark-sources/trampoline/stock-cprover-async/` | `trampoline-current.json`, `trampoline-c-async.json` | Trampoline source modeled with CPROVER async labels for stock CBMC. |
| `benchmark-sources/trampoline/PROVENANCE.md` | Provenance | Records that both Trampoline variants were moved from the previous local source trees. |
| `benchmark-sources/icbmc/upstream/` | Collected upstream corpus | CPROVER i-CBMC `po-code`, `seq-code`, and `conc-code` artifacts: 232 C/H/I files, 216799 LOC. |
| `benchmark-sources/icbmc/cases/` | `icbmc-large.json` | Runnable normalized i-CBMC cases with stock CPROVER async and improved pipeline variants. |
| `benchmark-sources/icbmc/PROVENANCE.md` | Provenance | Records CPROVER source page and imported artifact. |
| `benchmark-sources/intabs/upstream/` | Collected upstream corpus | Exported `chunghasung/intabs` repository snapshot: 120 C/H/I files, 87868 LOC. |
| `benchmark-sources/intabs/cases/` | `intabs-large.json` | Runnable normalized IntAbs cases with stock CPROVER async and improved pipeline variants. |
| `benchmark-sources/intabs/PROVENANCE.md` | Provenance | Records upstream repository and imported revision. |

## Legacy Simple Benchmark Inputs

| Item | Suite or role | Notes |
| --- | --- | --- |
| `simple-benchmarks/Interleaving Pipeline Checking.md` | Documentation | Original pipeline notes, now linked to manifest runner. |
| `simple-benchmarks/t_isr_multifile/` | `local-smoke.json` | Multi-file ISR pipeline smoke case. |
| `simple-benchmarks/osek_event_interleaving/` | `osek-local.json` | OSEK event interleaving demo. |
| `simple-benchmarks/osek_event_regression/` | `osek-local.json` | OSEK event regression cases. |
| `simple-benchmarks/osek_priority_interleaving/` | `osek-local.json` | OSEK priority interleaving demo. |

## Preferred Benchmark Variants

| Variant | Meaning |
| --- | --- |
| `stock_cprover_async` | Stock CBMC baseline using `__CPROVER_ASYNC_*`/C_ASYNC_PROVER-style source modeling. |
| `improved_pipeline` | Improved CBMC flow using `goto-cc --interleaving-*`, `aib`, compile, and verify. |
