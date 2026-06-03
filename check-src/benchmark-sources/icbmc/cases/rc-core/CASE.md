# rc-core

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/rc-core/rc_core.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile translation unit, and includes extracted ISR/task definitions from `isr_define/isr.c` so `--interleaving-source-files` has a dedicated ISR source.

Compile files:
- `main.c` includes `isr_define/isr.c`

ISR/task functions:
- `show_protocols_ldvwrapper`
- `ir_devnode_ldvwrapper`
- `store_protocols_ldvwrapper`
