# OSEK Event + ISR Interleaving Sample

This sample combines OSEK event APIs with ISR-style interleaving injection.

## What it covers

- OSEK event flow: `ActivateTask`, `WaitEvent`, `SetEvent`, `GetEvent`,
  `ClearEvent`, `TerminateTask`
- task scheduling from `--os-api osek --osek-oil app.oil`
- ISR interleaving metadata consumed by `aib`

## Layout

- `app.oil`: task metadata for controller/worker
- `harness.c`: entry point assertions for final state
- `task_define/tasks.c`: event protocol between tasks
- `isr_define/isr.c`: ISR-like writer to shared state
- `osek/osek_runtime_stub.c`: compile-only API surface
- `interleaving_harness.json`: example manifest for AIB flow

## Expected behavior

- Baseline OSEK run (no injection): expected to pass.
- Injected run (with `isr_touch_shared` calls): expected to expose violations in
  assertions that assume `shared_value == 2`.

