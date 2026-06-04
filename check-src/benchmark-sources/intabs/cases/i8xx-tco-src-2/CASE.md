# i8xx-tco-src-2

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/i8xx_tco_2/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 21

ISR/task functions:
- `closer1`
- `closer2`
- `writer1`
- `writer2`
- `writer5`
- `writer6`
- `writer7`
- `writer8`
- `writer9`
- `writer10`
- `writer11`
- `writer12`
- `writer13`
- `writer14`
- `writer15`
- `writer16`
- `writer17`
- `writer18`
- `writer19`
- `writer20`
- `writer21`
