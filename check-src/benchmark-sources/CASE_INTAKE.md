# Benchmark Case Intake

This note defines how to turn an upstream i-CBMC or IntAbs source file into a
normalized benchmark case.

## Intake Order

Use `CANDIDATES.md` as the queue. Its `phase` column means:

| Phase | Meaning |
| --- | --- |
| `staged` | A normalized case directory already exists. Do not import it again. |
| `phase-1` | IntAbs watchdog core cases that should be normalized first. |
| `phase-2` | High-score i-CBMC `rc-core` and `blink` conc/seq cases. |
| `phase-3` | i-CBMC `logger2` and `brake` breadth/control cases. |
| `phase-4` | Remaining IntAbs driver variants and `main2.c` variants. |
| `backlog` | Lower-priority source, or source that needs manual triage. |

Within a phase, prefer higher score first unless a pair should be imported
together, such as bug/nobug variants or `main.c`/`main2.c` variants.

## Normalized Layout

Every runnable case lives under:

```text
check-src/benchmark-sources/<corpus>/cases/<case-name>/
  CASE.md
  stock-cprover-async/
  improved-pipeline/
```

The stock variant uses C_ASYNC_PROVER-compatible modeling. It may keep active
`__CPROVER_ASYNC_*:` labels or convert active `pthread_create` launches to
async-labeled direct calls.

The improved variant is the source consumed by the improved interleaving
pipeline. It must not contain active C_ASYNC_PROVER launch modeling.

Headline improved cases must provide:

```text
improved-pipeline/isr_define/isr.c
improved-pipeline/isr_define/isr.h
```

For monolithic upstream files with many `static` declarations, keep `main.c` as
the compile source and include the extracted ISR source at the original
definition point:

```c
#include "isr_define/isr.c"
```

The suite entry should then keep:

```json
"variant_sources": {
  "improved_pipeline": ["main.c"]
},
"variant_isr_sources": {
  "improved_pipeline": ["isr_define/isr.c"]
}
```

For naturally multi-file cases, compile `isr_define/isr.c` directly:

```json
"variant_sources": {
  "improved_pipeline": ["main.c", "isr_define/isr.c"]
}
```

## Normalization Helper

For a first-pass monolithic case:

```powershell
$py = "$env:USERPROFILE\.cache\codex-runtimes\codex-primary-runtime\dependencies\python\python.exe"
& $py .\check-src\benchmarks\common\normalize_case.py `
  --corpus icbmc `
  --case my-case `
  --source check-src/benchmark-sources/icbmc/upstream/extracted/.../source.c `
  --isr-functions "isr1,isr2" `
  --split-isr-source
```

Review the output before enabling the case. The helper is a starting point, not
a proof that the case is benchmark-ready.

## Suite Entry Checklist

Each enabled i-CBMC or IntAbs case must have:

- `variant_roots.stock_cprover_async`
- `variant_roots.improved_pipeline`
- `variant_isr_sources.improved_pipeline`
- an improved ISR source path containing `isr_define/`
- at least one `isr_functions` entry
- timeout and memory limits high enough for Docker validation

Use `variant_include_dirs` when improved includes or compiles files under
`isr_define/`.

Use `variant_cbmc_args` only when verification options differ by variant. OSEK
examples use this for `--os-api osek --osek-oil <file>`.

## Enable Or Stage

Keep a new case `enabled: false` until both variants compile in Docker.

Enable a case when:

- stock compile reaches a verification phase;
- improved manifest generation succeeds;
- improved injection either runs `aib` or produces a documented
  `NO_INJECTION_CANDIDATES` result;
- improved compile reaches a verification phase;
- the result can be classified in `benchmark.md` or `uncomparable.md`.

Do not force a case into `benchmark.md`. The report generator decides
comparability from measured CSV rows.

## Classification

Comparable cases go to `benchmark.md` only when stock and improved verification
outcomes match and neither side hits unsupported concurrency, timeout, memory
limit, missing rows, or no injection candidates.

Cases go to `uncomparable.md` when:

- stock CBMC reports unsupported concurrency;
- stock and improved verification outcomes differ;
- improved has `NO_INJECTION_CANDIDATES`;
- one variant has no measured rows;
- timeout or memory limit is hit.

## Required Verification

Run structural checks:

```powershell
PowerShell -NoProfile -ExecutionPolicy Bypass -File .\check-src\benchmarks\tests\selftest.ps1
```

Run a Docker smoke for each new case:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/runner.py check-src/benchmarks/suites/<suite>.json --case <case>"
```

After a phase, regenerate reports:

```powershell
docker run --rm -v "D:\DS-AI\Research-thay-Hoa\CBMC Research\cbmc:/repo" -w /repo bkmeeting-vpcd-aimet:ubuntu22.04-py310 bash -lc "python3 check-src/benchmarks/common/candidate_scan.py && python3 check-src/benchmarks/common/corpus_inventory.py && python3 check-src/benchmarks/common/report_benchmark.py"
```

