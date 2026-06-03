# wdt-pci-2

Origin: `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_2/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps the foreground harness in `main.c`, and keeps ISR/task definitions in `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

ISR/task functions:
- `closer3`
- `writer3`
- `closer1`
- `writer1`
