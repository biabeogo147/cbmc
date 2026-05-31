# i-CBMC Benchmark Source Provenance

Import date: 2026-05-30

Primary source page: https://www.cprover.org/interrupts/

Imported artifacts:
- `https://www.cprover.org/interrupts/benchmarks/po-code.tar.gz`
- `https://www.cprover.org/interrupts/benchmarks/seq-code.tar.gz`
- `https://www.cprover.org/interrupts/benchmarks/conc-code.tar.gz`
- i-CBMC Logger source family under `po-code/logger1+2/`

Collected upstream corpus:
- Archive copies: `upstream/archives/{po-code,seq-code,conc-code}.tar.gz`
- Extracted source: `upstream/extracted/{po-code,seq-code,conc-code}`
- Total collected C/H/I size: 232 files, 216799 LOC
- `po-code`: 32 files, 31302 LOC
- `seq-code`: 72 files, 79314 LOC
- `conc-code`: 128 files, 106183 LOC

Normalized runnable case:
- `logger/stock-cprover-async`: CPROVER async-label model for stock CBMC.
- `logger/improved-pipeline`: split foreground/ISR model for the improved CBMC interleaving pipeline.

Notes:
- The CPROVER page describes interrupt arrivals using labels named `__CPROVER_ASYNC_` followed by ISR calls.
- The runnable Logger case is smoke-only and must not be used as the headline i-CBMC benchmark.
- Select and normalize larger cases from `upstream/extracted` before enabling the suite for benchmark reporting.
