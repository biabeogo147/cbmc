# OSEK Event + Interleaving Sample

This sample is the regression fixture for the modular `os-api/osek`
integration when OSEK event flow is combined with ISR-style interleaving
injection.

It combines:
- an OIL file that defines task priority, schedule type, task type, and event
  mask metadata
- OSEK task and event APIs in the program under test:
  `ActivateTask`, `WaitEvent`, `SetEvent`, `GetEvent`, `ClearEvent`, and
  `TerminateTask`
- one ISR-style interleaving source file so the current interleaving-analysis
  and `aib` flow can still be exercised

## Layout

- `app.oil`: source-of-truth OSEK-style task and event metadata
- `harness.c`: small entry point that boots the sample and checks final state
- `osek/osek_runtime_stub.c`: compile-only runtime surface; CBMC scheduling is
  provided by `--os-api osek`
- `task_define/tasks.c`: event protocol between controller and worker
- `isr_define/isr.c`: ISR-like source for interleaving injection
- `interleaving_harness.json`: example manifest for the AIB flow

## Expected behavior

Without `--os-api osek`, the compatibility runtime is intentionally incomplete:
it keeps the sample buildable but does not schedule tasks or resolve event
state on behalf of CBMC.

With the implemented OSEK integration enabled, the tasks execute in the
intended order:

1. `controller` starts first
2. `controller` activates extended `worker`
3. `worker` waits for the configured event bit
4. `controller` sets the event, allowing `worker` to resume
5. `worker` observes and clears the event, updates shared state, and terminates
6. the harness checks the final state reached by the event protocol

The shared value should end at `2`. With:

```bash
cbmc \
  check-src/simple-benchmarks/osek_event_interleaving/osek_event_interleaving.out \
  --function main \
  --unwind 8 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/simple-benchmarks/osek_event_interleaving/app.oil
```

the baseline fixture passes.

With injected ISR calls, `isr_touch_shared()` may perturb `shared_value`
between task steps, so the assertions in `tasks.c` become sensitive to both
event ordering and interleaving injection.

## Verified status

- Baseline OSEK run: `VERIFICATION SUCCESSFUL`
- Injected AIB run: intended to expose assertion failures when ISR injection
  perturbs the shared state assumptions in the event protocol

`osek/osek_runtime_stub.c` remains a compile-only scaffold. The intended way to
check the sample is through the `--os-api osek --osek-oil app.oil` scheduler
path.
