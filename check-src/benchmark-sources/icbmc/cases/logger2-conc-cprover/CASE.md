# logger2-conc-cprover

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/conc-code/logger2/nobug/logger2_conc_cprover.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 4

Harness notes:
- The ISR bundle is included at the last extracted task definition so globals declared between Logger2 tasks remain visible.
- The 30-minute timeout review normalized the improved ISR bundle from local atomic blocks to whole-function atomic ISR entries.

ISR/task functions:
- `task_ext_power`
- `task_communicate`
- `task_communicate2`
- `task_measure`
