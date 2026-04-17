# Baseline: OSEK event regression fixtures

## 1. Basic event set / get / clear

```bash
cbmc \
  check-src/osek_event_regression/osek-event-basic/main.c \
  --os-api osek \
  --osek-oil check-src/osek_event_regression/osek-event-basic/config.oil
```

Expected result: `VERIFICATION SUCCESSFUL`

## 2. WaitEvent blocks until another task runs

```bash
cbmc \
  check-src/osek_event_regression/osek-event-wait-block/main.c \
  --os-api osek \
  --osek-oil check-src/osek_event_regression/osek-event-wait-block/config.oil
```

Expected result: `VERIFICATION SUCCESSFUL`

## 3. WaitEvent does not block when the bit is already set

```bash
cbmc \
  check-src/osek_event_regression/osek-event-wait-noblock/main.c \
  --os-api osek \
  --osek-oil check-src/osek_event_regression/osek-event-wait-noblock/config.oil
```

Expected result: `VERIFICATION SUCCESSFUL`

## 4. Multi-bit event accumulation and selective clear

```bash
cbmc \
  check-src/osek_event_regression/osek-event-multi-bits/main.c \
  --os-api osek \
  --osek-oil check-src/osek_event_regression/osek-event-multi-bits/config.oil
```

Expected result: `VERIFICATION SUCCESSFUL`

# Sync to `regression/cbmc`

## 1. Copy the local mirror into the regression tree

```bash
pwsh -File check-src/osek_event_regression/sync_to_regression.ps1
```

## 2. Run the mirrored fixtures directly

```bash
cbmc \
  regression/cbmc/osek-event-basic/main.c \
  --os-api osek \
  --osek-oil regression/cbmc/osek-event-basic/config.oil
```

```bash
cbmc \
  regression/cbmc/osek-event-wait-block/main.c \
  --os-api osek \
  --osek-oil regression/cbmc/osek-event-wait-block/config.oil
```

```bash
cbmc \
  regression/cbmc/osek-event-wait-noblock/main.c \
  --os-api osek \
  --osek-oil regression/cbmc/osek-event-wait-noblock/config.oil
```

```bash
cbmc \
  regression/cbmc/osek-event-multi-bits/main.c \
  --os-api osek \
  --osek-oil regression/cbmc/osek-event-multi-bits/config.oil
```

Expected result: `VERIFICATION SUCCESSFUL`

# Optional regression harness

If the environment has a complete Perl runtime, you can also run the mirrored
fixtures through the standard regression harness:

```bash
perl regression/test.pl -C -p -c ./cmake-build-debug-cbmc/bin/cbmc \
  regression/cbmc/osek-event-basic \
  regression/cbmc/osek-event-wait-block \
  regression/cbmc/osek-event-wait-noblock \
  regression/cbmc/osek-event-multi-bits
```

If the container ships an incomplete Perl installation, prefer the direct
`cbmc` commands above.
