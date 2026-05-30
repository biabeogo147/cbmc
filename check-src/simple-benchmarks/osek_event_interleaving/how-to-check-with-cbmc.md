# Baseline: OSEK event scheduling

```bash
goto-cc \
  check-src/simple-benchmarks/osek_event_interleaving/harness.c \
  check-src/simple-benchmarks/osek_event_interleaving/isr_define/isr.c \
  check-src/simple-benchmarks/osek_event_interleaving/task_define/tasks.c \
  check-src/simple-benchmarks/osek_event_interleaving/osek/osek_runtime_stub.c \
  -o check-src/simple-benchmarks/osek_event_interleaving/osek_event_interleaving.out
```

```bash
cbmc \
  check-src/simple-benchmarks/osek_event_interleaving/osek_event_interleaving.out \
  --function main \
  --unwind 8 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/simple-benchmarks/osek_event_interleaving/app.oil
```

# With AIB injection

## 1. Generate interleaving manifest

```bash
goto-cc \
  check-src/simple-benchmarks/osek_event_interleaving/harness.c \
  check-src/simple-benchmarks/osek_event_interleaving/isr_define/isr.c \
  check-src/simple-benchmarks/osek_event_interleaving/task_define/tasks.c \
  check-src/simple-benchmarks/osek_event_interleaving/osek/osek_runtime_stub.c \
  --interleaving-project-root check-src/simple-benchmarks/osek_event_interleaving \
  --interleaving-source-files check-src/simple-benchmarks/osek_event_interleaving/isr_define/isr.c \
  --interleaving-output check-src/simple-benchmarks/osek_event_interleaving/interleaving_harness.json \
  -o check-src/simple-benchmarks/osek_event_interleaving/osek_event_interleaving.out
```

## 2. Inject interleaving blocks

```bash
aib \
  check-src/simple-benchmarks/osek_event_interleaving \
  check-src/simple-benchmarks/osek_event_interleaving/interleaving_harness.json \
  check-src/simple-benchmarks/osek_event_interleaving_injected \
  check-src/simple-benchmarks/osek_event_interleaving_injected/interleaving_harness_injected.json
```

## 3. Rebuild injected tree

```bash
goto-cc \
  check-src/simple-benchmarks/osek_event_interleaving_injected/harness.c \
  check-src/simple-benchmarks/osek_event_interleaving_injected/isr_define/isr.c \
  check-src/simple-benchmarks/osek_event_interleaving_injected/task_define/tasks.c \
  check-src/simple-benchmarks/osek_event_interleaving_injected/osek/osek_runtime_stub.c \
  -o check-src/simple-benchmarks/osek_event_interleaving_injected/osek_event_interleaving_injected.out
```

## 4. Check injected tree with OSEK scheduler

```bash
cbmc \
  check-src/simple-benchmarks/osek_event_interleaving_injected/osek_event_interleaving_injected.out \
  --function main \
  --unwind 8 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/simple-benchmarks/osek_event_interleaving/app.oil
```
