# os-api/osek

`osek/` is the first concrete OS API integration hosted by `src/os-api/`.

## Current status

This folder now contains:

1. A small OIL parser that loads `TASK`, `PRIORITY`, `SCHEDULE`, and
   `AUTOSTART`.
2. API classification for `ActivateTask`, `TerminateTask`, `ChainTask`, and
   `Schedule`.
3. Scheduler-decision handlers that convert OSEK API calls into generic
   next-step actions for `goto-symex`.
4. The runtime task mapping used by the new regression fixture and
   `goto-symex` task scheduling hook.

## Implemented semantics

- `ActivateTask` enqueues the target task and immediately starts it when its
  priority is higher than the currently running task, or when no task is
  running yet.
- `TerminateTask` removes the current task and reschedules against the ready
  queue and any suspended caller task.
- `ChainTask` terminates the current task, enqueues the target task, and then
  reschedules from the resulting runnable set.
- `Schedule` acts as an explicit reschedule point using the current ready queue.

## Current limitations

- OIL parsing intentionally covers only the subset needed for task scheduling.
- OIL task IDs are assigned by declaration order to match `TASK_ID_*` enums in
  the regression fixture.
- `AUTOSTART` is parsed and preserved in metadata, but the current workflow
  still expects the harness/runtime stub to call `ActivateTask(...)` explicitly
  for bootstrapping.
