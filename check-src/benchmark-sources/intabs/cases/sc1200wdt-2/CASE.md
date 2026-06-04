# sc1200wdt-2

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc1200wdt_2/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 2

Harness notes:
- The upstream test body references `len` after manually expanding `sc1200wdt_write`; the normalized compile source declares it as a harness integer.

ISR/task functions:
- `writer1`
- `closer`
