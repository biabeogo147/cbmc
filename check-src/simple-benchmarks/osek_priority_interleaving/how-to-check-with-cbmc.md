# Baseline: OSEK-scheduled task flow

```bash
goto-cc \
  check-src/simple-benchmarks/osek_priority_interleaving/harness.c \
  check-src/simple-benchmarks/osek_priority_interleaving/isr_define/isr.c \
  check-src/simple-benchmarks/osek_priority_interleaving/task_define/tasks.c \
  check-src/simple-benchmarks/osek_priority_interleaving/osek/osek_runtime_stub.c \
  -o check-src/simple-benchmarks/osek_priority_interleaving/osek_priority_interleaving.out
```

```bash
cbmc \
  check-src/simple-benchmarks/osek_priority_interleaving/osek_priority_interleaving.out \
  --function main \
  --unwind 6 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/simple-benchmarks/osek_priority_interleaving/app.oil
```

# With AIB injection

## 1. Generate the interleaving manifest

```bash
goto-cc \
  check-src/simple-benchmarks/osek_priority_interleaving/harness.c \
  check-src/simple-benchmarks/osek_priority_interleaving/isr_define/isr.c \
  check-src/simple-benchmarks/osek_priority_interleaving/task_define/tasks.c \
  check-src/simple-benchmarks/osek_priority_interleaving/osek/osek_runtime_stub.c \
  --interleaving-project-root check-src/simple-benchmarks/osek_priority_interleaving \
  --interleaving-source-files check-src/simple-benchmarks/osek_priority_interleaving/isr_define/isr.c \
  --interleaving-output check-src/simple-benchmarks/osek_priority_interleaving/interleaving_harness.json \
  -o check-src/simple-benchmarks/osek_priority_interleaving/osek_priority_interleaving.out
```

## 2. Inject interleaving blocks

```bash
aib \
  check-src/simple-benchmarks/osek_priority_interleaving \
  check-src/simple-benchmarks/osek_priority_interleaving/interleaving_harness.json \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/interleaving_harness_injected.json
```

## 3. Rebuild the injected tree

```bash
goto-cc \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/harness.c \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/isr_define/isr.c \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/task_define/tasks.c \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/osek/osek_runtime_stub.c \
  -o check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/osek_priority_interleaving_injected.out
```

Expected result: `VERIFICATION SUCCESSFUL`

## 4. Injected OSEK + interleaving check

Run the injected tree with the same OSEK options:

```bash
cbmc \
  check-src/simple-benchmarks/osek_priority_interleaving_injected_os_api/osek_priority_interleaving_injected.out \
  --function main \
  --unwind 6 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/simple-benchmarks/osek_priority_interleaving/app.oil
```

Expected result: `VERIFICATION FAILED` with 5 failing properties, showing that
the injected ISR interleavings still perturb the OSEK-scheduled task flow.
