# OSEK Event Regression Mirror

This folder mirrors the OSEK event regression fixtures used by
`regression/cbmc` and also acts as the local staging area for new event tests.

## Layout

- `osek-event-basic/`: basic `SetEvent`, `GetEvent`, `ClearEvent`
- `osek-event-wait-block/`: `WaitEvent` blocking behavior
- `osek-event-wait-noblock/`: `WaitEvent` non-blocking behavior
- `osek-event-multi-bits/`: multiple event bits (`0x1`, `0x2`, `0x4`)

## Workflow for new tests

1. Create new OSEK event fixture under this folder first.
2. Copy/sync that fixture to `regression/cbmc/` so regression runner can use it.
3. Run regression checks from `regression/cbmc`.

A helper script is included: `sync_to_regression.ps1`.

## Quick run examples

If your Run Configuration uses Docker toolchain binaries, these one-line checks
match that style:

```powershell
cmake-build-debug-docker/bin/cbmc check-src/osek_event_regression/osek-event-basic/main.c --os-api osek --osek-oil check-src/osek_event_regression/osek-event-basic/config.oil
cmake-build-debug-docker/bin/cbmc check-src/osek_event_regression/osek-event-wait-block/main.c --os-api osek --osek-oil check-src/osek_event_regression/osek-event-wait-block/config.oil
cmake-build-debug-docker/bin/cbmc check-src/osek_event_regression/osek-event-wait-noblock/main.c --os-api osek --osek-oil check-src/osek_event_regression/osek-event-wait-noblock/config.oil
cmake-build-debug-docker/bin/cbmc check-src/osek_event_regression/osek-event-multi-bits/main.c --os-api osek --osek-oil check-src/osek_event_regression/osek-event-multi-bits/config.oil
```

If you run the official regression harness in an environment with Perl:

```powershell
perl regression/test.pl -C -p -c cmake-build-debug-docker/bin/cbmc regression/cbmc/osek-event-basic
perl regression/test.pl -C -p -c cmake-build-debug-docker/bin/cbmc regression/cbmc/osek-event-wait-block
perl regression/test.pl -C -p -c cmake-build-debug-docker/bin/cbmc regression/cbmc/osek-event-wait-noblock
perl regression/test.pl -C -p -c cmake-build-debug-docker/bin/cbmc regression/cbmc/osek-event-multi-bits
```

## Sync mirror to regression

```powershell
powershell -ExecutionPolicy Bypass -File check-src/osek_event_regression/sync_to_regression.ps1
```


