# wdt-pci-1-main2

Origin: `check-src/benchmark-sources/intabs/upstream/repository/icbmc/wdt_pci_1/main2.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 30

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
- `writer23`
- `writer24`
- `writer25`
- `writer26`
- `writer27`
- `writer28`
- `writer29`
- `closer`
