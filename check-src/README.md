# check-src Benchmark Workspace

`check-src` contains the manifest-driven benchmark framework and the latest
benchmark report. The older local CBMC experiments, ISR interleaving demos,
OSEK regressions, and Trampoline source trees are grouped under
`check-src/simple-benchmarks`.

## Quick Start

On Linux or WSL:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json
```

On Windows without WSL, use the structural self-test:

```powershell
PowerShell -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

The legacy entry point still exists:

```bash
bash check-src/isr_large_benchmark.sh
```

It delegates to the manifest-driven runner.

## Existing Content Ownership

| Item | Suite or role | Notes |
| --- | --- | --- |
| `benchmark.md` | Latest benchmark report | Docker-measured stock CBMC vs improved CBMC result for the current Trampoline ISR case. |
| `benchmarks/` | Framework | Manifests, runner, measurement, reporting, tests. |
| `external/` | External benchmark staging | Imported i-CBMC and IntAbs sources plus provenance notes. |
| `isr_large_benchmark.sh` | Compatibility wrapper | Runs `trampoline-current.json`. |
| `simple-benchmarks/` | Local source corpus | Existing simple demos, OSEK cases, and Trampoline inputs moved out of the top level. |

## Simple Benchmark Inputs

| Item | Suite or role | Notes |
| --- | --- | --- |
| `simple-benchmarks/Interleaving Pipeline Checking.md` | Documentation | Original pipeline notes, now linked to manifest runner. |
| `simple-benchmarks/interleaving_adding_config.json` | Documentation/config | Small historical AIB config example. |
| `simple-benchmarks/isr_large_simple_benchmark.sh` | Legacy implementation | Preserved copy of the one-off Trampoline benchmark script. |
| `simple-benchmarks/t_interleaving.c` | `local-smoke.json` | Small interleaving smoke input. |
| `simple-benchmarks/t_isr.c` | `local-smoke.json` | Small ISR smoke input. |
| `simple-benchmarks/t_isr_added.c` | `local-smoke.json` | Previously injected ISR smoke input. |
| `simple-benchmarks/t_isr_multifile/` | `local-smoke.json` | Multi-file ISR pipeline smoke case. |
| `simple-benchmarks/osek_event_interleaving/` | `osek-local.json` | OSEK event interleaving demo. |
| `simple-benchmarks/osek_event_regression/` | `osek-local.json` | OSEK event regression cases. |
| `simple-benchmarks/osek_priority_interleaving/` | `osek-local.json` | OSEK priority interleaving demo. |
| `simple-benchmarks/trampoline/` | `trampoline-current.json` | Current large ISR benchmark source tree. |
| `simple-benchmarks/trampoline_c_async/` | `trampoline-c-async.json` | Historical CPROVER async comparison tree. |

## Benchmark Variants

The runner compares two default variants:

- `stock_naive`: copy the source tree and insert nondeterministic ISR calls after
  candidate statements.
- `improved_targeted`: use improved `goto-cc` to emit an interleaving manifest,
  run `aib`, and verify the targeted injected program.

Reports include time, peak RSS, exit code, verification summary, ISR insertion
count, speedup percentage, and RAM reduction percentage.
