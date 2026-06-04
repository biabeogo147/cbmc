# sc1200wdt-1

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc1200wdt_1/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 23

ISR/task functions:
- `writer1`
- `writer2`
- `writer3`
- `writer4`
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
- `writer22`
- `closer`
