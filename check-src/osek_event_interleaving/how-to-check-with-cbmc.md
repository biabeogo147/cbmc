# Baseline: OSEK event scheduling

```bash
goto-cc \
  check-src/osek_event_interleaving/harness.c \
  check-src/osek_event_interleaving/isr_define/isr.c \
  check-src/osek_event_interleaving/task_define/tasks.c \
  check-src/osek_event_interleaving/osek/osek_runtime_stub.c \
  -o check-src/osek_event_interleaving/osek_event_interleaving.out
```

```bash
cbmc \
  check-src/osek_event_interleaving/osek_event_interleaving.out \
  --function main \
  --unwind 8 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/osek_event_interleaving/app.oil
```

# With AIB injection

## 1. Generate interleaving manifest

```bash
goto-cc \
  check-src/osek_event_interleaving/harness.c \
  check-src/osek_event_interleaving/isr_define/isr.c \
  check-src/osek_event_interleaving/task_define/tasks.c \
  check-src/osek_event_interleaving/osek/osek_runtime_stub.c \
  --interleaving-project-root check-src/osek_event_interleaving \
  --interleaving-source-files check-src/osek_event_interleaving/isr_define/isr.c \
  --interleaving-output check-src/osek_event_interleaving/interleaving_harness.json \
  -o check-src/osek_event_interleaving/osek_event_interleaving.out
```

## 2. Inject interleaving blocks

```bash
aib \
  check-src/osek_event_interleaving \
  check-src/osek_event_interleaving/interleaving_harness.json \
  check-src/osek_event_interleaving_injected \
  check-src/osek_event_interleaving_injected/interleaving_harness_injected.json
```

## 3. Rebuild injected tree

```bash
goto-cc \
  check-src/osek_event_interleaving_injected/harness.c \
  check-src/osek_event_interleaving_injected/isr_define/isr.c \
  check-src/osek_event_interleaving_injected/task_define/tasks.c \
  check-src/osek_event_interleaving_injected/osek/osek_runtime_stub.c \
  -o check-src/osek_event_interleaving_injected/osek_event_interleaving_injected.out
```

## 4. Check injected tree with OSEK scheduler

```bash
cbmc \
  check-src/osek_event_interleaving_injected/osek_event_interleaving_injected.out \
  --function main \
  --unwind 8 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/osek_event_interleaving/app.oil
```
