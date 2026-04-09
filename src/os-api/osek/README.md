# os-api/osek

`osek/` is the first concrete OS API integration hosted by `src/os-api/`.

## Current status

This folder now contains:

1. A small OIL parser that loads `TASK`, `PRIORITY`, `SCHEDULE`,
   `AUTOSTART`, `TYPE`, and `EVENT_MASK`.
2. API classification for `ActivateTask`, `TerminateTask`, `ChainTask`,
   `Schedule`, `SetEvent`, `ClearEvent`, `GetEvent`, and `WaitEvent`.
3. Scheduler-decision handlers that convert OSEK API calls into generic
   next-step actions for `goto-symex`.
4. The runtime task mapping used by the new regression fixture and
   `goto-symex` task scheduling hook.
5. Event API classification and handlers for `SetEvent`, `ClearEvent`,
   `GetEvent`, and `WaitEvent`.
6. OIL parsing extensions for `TYPE = BASIC|EXTENDED` and `EVENT_MASK = ...`.

## Implemented semantics

- `ActivateTask` enqueues the target task and immediately starts it when its
  priority is higher than the currently running task, or when no task is
  running yet.
- `TerminateTask` removes the current task and reschedules against the ready
  queue and any suspended caller task.
- `ChainTask` terminates the current task, enqueues the target task, and then
  reschedules from the resulting runnable set.
- `Schedule` acts as an explicit reschedule point using the current ready queue.
- `SetEvent` updates the target extended task's event bits and may wake it from
  waiting state.
- `ClearEvent` clears event bits of the current extended task.
- `GetEvent` writes the target task's current set-event mask through the API
  output pointer.
- `WaitEvent` currently models the scheduling point and block/no-block decision
  from the event mask; wake-up continuation is approximated via task dispatch.

## Current limitations

- OIL parsing intentionally covers only the subset needed for task scheduling.
- OIL task IDs are assigned by declaration order to match `TASK_ID_*` enums in
  the regression fixture.
- Event masks are modeled as a 64-bit bitset loaded from `EVENT_MASK`.
- `TYPE` defaults to `BASIC` and a missing `EVENT_MASK` defaults to `0`.
- `AUTOSTART` is parsed and preserved in metadata, but the current workflow
  still expects the harness/runtime stub to call `ActivateTask(...)` explicitly
  for bootstrapping.
