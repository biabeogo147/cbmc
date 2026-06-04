# rc-core-conc-cprover

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/rc-core/nobug/rc_core_conc_cprover.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 3

ISR/task functions:
- `show_protocols_ldvwrapper`
- `ir_devnode_ldvwrapper`
- `store_protocols_ldvwrapper`
