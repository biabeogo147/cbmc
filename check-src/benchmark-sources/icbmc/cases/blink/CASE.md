# blink

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/blink/blink.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, leaving ISR/task functions in the compile unit for pipeline validation.

Compile files:
- `main.c`

ISR/task functions:
- `VirtualizeTimerC_0_updateFromTimer_runTask`
- `AlarmToTimerC_0_fired_runTask`
