# wdt-pci-src-3

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/wdt_pci_3/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, leaving ISR/task functions in the compile unit for pipeline validation.

Compile files:
- `main.c`

ISR/task functions:
- `closer1`
- `closer2`
- `closer3`
- `closer4`
