# blink-seq

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/seq-code/blink/nobug/blink_por_seq.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 2

ISR/task functions:
- `VirtualizeTimerC_0_updateFromTimer_runTask`
- `AlarmToTimerC_0_fired_runTask`
