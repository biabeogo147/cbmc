# Check Src Benchmark Refactor Plan

Goal: turn `check-src` into a manifest-driven benchmark framework while keeping
all existing demos, regressions, and Trampoline inputs.

## Existing Inputs Kept

- `check-src/simple-benchmarks/Interleaving Pipeline Checking.md`
- `check-src/simple-benchmarks/interleaving_adding_config.json`
- `check-src/isr_large_benchmark.sh`
- `check-src/simple-benchmarks/isr_large_simple_benchmark.sh`
- `check-src/simple-benchmarks/t_interleaving.c`
- `check-src/simple-benchmarks/t_isr.c`
- `check-src/simple-benchmarks/t_isr_added.c`
- `check-src/simple-benchmarks/t_isr_multifile/`
- `check-src/simple-benchmarks/osek_event_interleaving/`
- `check-src/simple-benchmarks/osek_event_regression/`
- `check-src/simple-benchmarks/osek_priority_interleaving/`
- `check-src/simple-benchmarks/trampoline/`
- `check-src/simple-benchmarks/trampoline_c_async/`

## New Framework

- `check-src/benchmarks/suites/*.json` describes benchmark cases.
- `check-src/benchmarks/common/runner.py` runs manifest cases and records CSV.
- `check-src/benchmarks/common/inject_naive.py` creates stock naive ISR copies.
- `check-src/benchmarks/run_suite.sh` is the Linux/WSL entry point.
- `check-src/benchmarks/run_all.sh` runs all enabled suites.
- `check-src/benchmarks/tests/selftest.ps1` validates manifests and structure on Windows.

## Suite Mapping

- `local-smoke.json`: small ISR/interleaving files and `t_isr_multifile`.
- `osek-local.json`: local OSEK event and priority examples.
- `trampoline-current.json`: the current `isr_large_benchmark.sh` source set.
- `trampoline-c-async.json`: the current CPROVER async comparison tree.
- `trampoline-expanded.json`: disabled placeholder for larger Trampoline ISR cases.
- `icbmc-interrupts.json`: disabled placeholder for CProver i-CBMC interrupt benchmarks.
- `intabs-interrupts.json`: disabled placeholder for IntAbs interrupt-driven benchmarks.

## Verification Protocol

For headline numbers, run in Linux/WSL/Docker where CBMC binaries are executable:

```bash
bash check-src/benchmarks/run_suite.sh check-src/benchmarks/suites/trampoline-current.json
```

Report stock and improved `time_ms`, `max_rss_mb`, verification result, faster
percentage, RAM reduction percentage, and ISR insertion reduction.
