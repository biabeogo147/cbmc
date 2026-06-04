# wdt-pci-1

Origin: `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_1/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 4

ISR/task functions:
- `closer1`
- `closer2`
- `writer1`
- `writer2`
