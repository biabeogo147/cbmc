# OSEK Priority + Interleaving Sample

This sample is the regression fixture for the modular `os-api/osek`
integration.

It combines:
- an OIL file that defines task priority, schedule type, and autostart
- three OSEK task-control APIs in the program under test:
  `ActivateTask`, `TerminateTask`, and `ChainTask`
- one ISR-style interleaving source file so the current interleaving-analysis
  and `aib` flow can still be exercised

## Layout

- `app.oil`: source-of-truth OSEK-style task metadata
- `harness.c`: small entry point that boots the sample
- `osek/osek_runtime_stub.c`: compile-only runtime surface; CBMC scheduling is
  provided by `--os-api osek`
- `task_define/tasks.c`: task bodies and assertions that depend on task order
- `isr_define/isr.c`: ISR-like source for interleaving injection

## Expected behavior

Without `--os-api osek`, the compatibility runtime is intentionally incomplete:
it keeps the sample buildable but does not schedule tasks on behalf of CBMC.

With the implemented OSEK integration enabled, the tasks execute in the
intended order:

1. `controller` starts first
2. `controller` activates higher-priority `worker`
3. `worker` updates shared state and terminates
4. `controller` resumes and chains to `cleanup`
5. `cleanup` finalizes the shared state

The shared value should end at `3`. With:

```bash
cbmc \
  check-src/osek_priority_interleaving/osek_priority_interleaving.out \
  --function main \
  --unwind 6 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/osek_priority_interleaving/app.oil
```

the baseline fixture now passes.

With injected ISR calls, `isr_boost_shared()` may perturb `shared_value`
between task steps, so the assertions in `tasks.c` become sensitive to both
task ordering and interleaving injection.

## Verified status

- Baseline OSEK run: `0 of 6 failed`
- Injected AIB run: `5 of 6 failed`

`osek/osek_runtime_stub.c` remains a compile-only scaffold. The intended way to
check the sample is through the `--os-api osek --osek-oil app.oil` scheduler
path.
