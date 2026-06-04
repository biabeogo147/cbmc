# rcmain

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/rcmain/rc_core.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 5

ISR/task functions:
- `ir_devnode_ldvwrapper`
- `store_protocols_ldvwrapper`
- `show_protocols_ldvwrapper`
- `rc_dev_uevent_ldvwrapper`
- `rc_dev_release_ldvwrapper`
