# os-api/core

`core/` holds API-agnostic execution-model pieces that can be reused by OSEK
and future integrations.

## Current status

This folder currently provides:

1. Scheduler/task runtime types shared with symbolic execution state.
2. A ready-queue implementation that preserves deterministic FIFO behaviour
   among equal-priority tasks.
3. A dispatcher that loads the selected OS API model from `optionst` and
   routes recognized API calls to the appropriate integration.
4. Generic next-step results so `goto-symex` can apply scheduler decisions
   without embedding OSEK-specific parsing logic.
