# sc520wdt-2

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/sc520wdt_2/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps the foreground harness in `main.c`, and keeps ISR/task definitions in `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

ISR/task functions:
- `writer1`
- `writer2`
- `writer3`
- `writer4`
- `closer`
