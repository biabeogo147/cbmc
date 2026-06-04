# brake2-1-bug-po

Origin: `check-src/benchmark-sources/icbmc/upstream/extracted/po-code/brake/brake2_1_bug_po.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, keeps `main.c` as the compile source, and uses `isr_define/isr.c` for `--interleaving-source-files`.

Compile files:
- `main.c`

Improved ISR source:
- `isr_define/isr.c`

Extracted ISR/task definitions: 5

Harness notes:
- Copied the upstream generated Brake model C files and headers used by `main.c`.
- The suite defines `CBMC`, matching the upstream conditional that includes those model definitions.
- The ISR bundle is included at the last extracted task definition so model globals remain visible.

ISR/task functions:
- `task_RR_Wheel`
- `task_RL_Wheel`
- `task_FR_Wheel`
- `task_FL_Wheel`
- `task_compute`
