# logger2

Origin: legacy normalized control case; the original upstream source metadata
was not recorded.

Status:
- Staged but disabled in `intabs-large.json`.
- The improved ISR definitions are atomic and live in `improved-pipeline/isr_define/isr.c`.
- The stock tree does not contain CPROVER async modeling, so it is not a valid
  stock-versus-improved comparison case.

Compile files:
- `main.c`
- `model.c`

Improved ISR source:
- `isr_define/isr.c`

ISR/task functions:
- `task_measure1`
- `task_measure2`
- `task_communicate`
