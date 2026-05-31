# rc-core-bug

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/rc-core/rc_core_bug.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, leaving ISR/task functions in the compile unit for pipeline validation.

Compile files:
- `main.c`

ISR/task functions:
- `store_protocols_ldvwrapper`
- `show_protocols_ldvwrapper`
- `ir_devnode_ldvwrapper`
