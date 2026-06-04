# i8xx-tco-1

Origin: `check-src/benchmark-sources/intabs/upstream/repository/icbmc/i8xx_tco_1/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 3

ISR/task functions:
- `writer1`
- `closer1`
- `closer2`
