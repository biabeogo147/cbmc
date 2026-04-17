# OSEK Event Regression Mirror

This folder is the local staging area for OSEK event fixtures and mirrors the
same tests under `regression/cbmc/`.

It currently covers:
- `osek-event-basic`: `SetEvent`, `GetEvent`, `ClearEvent`
- `osek-event-wait-block`: blocking `WaitEvent`
- `osek-event-wait-noblock`: non-blocking `WaitEvent`
- `osek-event-multi-bits`: multi-bit event accumulation and clearing

For command-by-command verification, see
[`how-to-check-with-cbmc.md`](how-to-check-with-cbmc.md).

To sync the local mirror into `regression/cbmc/`, run:

```bash
pwsh -File check-src/osek_event_regression/sync_to_regression.ps1
```
