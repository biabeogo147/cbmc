# logger3

Origin: `check-src/benchmark-sources/intabs/upstream/repository/src/test/logger3/main.c`

Normalization:
- `stock-cprover-async`: preserves upstream CPROVER async labels and converts active `pthread_create` launches to CPROVER async calls.
- `improved-pipeline`: removes active `__CPROVER_ASYNC_*:` labels and active `pthread_create` launches, leaving ISR/task functions in the compile unit for pipeline validation.

Compile files:
- `main.c`

ISR/task functions:
- `task_communicate`
- `task_measure1`
- `task_measure2`
- `task_measure3`
