# OSEK Priority + Interleaving Sample

This sample is a bridge fixture for the planned `os-api/osek` integration.

It combines:
- an OIL file that defines task priority, schedule type, and autostart
- three OSEK task-control APIs in the program under test:
  `ActivateTask`, `TerminateTask`, and `ChainTask`
- one ISR-style interleaving source file so the current interleaving-analysis
  and `aib` flow can still be exercised

## Layout

- `app.oil`: source-of-truth OSEK-style task metadata
- `harness.c`: small entry point that boots the sample
- `osek/osek_runtime_stub.c`: temporary compatibility runtime so the sample
  builds before `src/os-api/osek` exists
- `task_define/tasks.c`: task bodies and assertions that depend on task order
- `isr_define/isr.c`: ISR-like source for interleaving injection

## Expected behavior

Without `--os-api osek`, the compatibility runtime is intentionally incomplete:
it keeps the sample buildable but does not schedule tasks on behalf of CBMC.

With the planned OSEK integration enabled, the tasks should execute in the
intended order:

1. `controller` starts first
2. `controller` activates higher-priority `worker`
3. `worker` updates shared state and terminates
4. `controller` resumes and chains to `cleanup`
5. `cleanup` finalizes the shared state

The shared value should end at `3`. Without OSEK scheduling support, the
baseline harness should fail because the autostart `ActivateTask()` call is a
no-op in the stub.

With injected ISR calls, `isr_boost_shared()` may perturb `shared_value`
between task steps, so the assertions in `tasks.c` become sensitive to both
task ordering and interleaving injection.

## Current limitation

`osek/osek_runtime_stub.c` is a temporary compile-only scaffold. It does not
model task scheduling, preemption, or chaining. Once `--os-api osek --osek-oil
app.oil` exists, the sample should be checked through the new scheduler path
instead of relying on the stub.
