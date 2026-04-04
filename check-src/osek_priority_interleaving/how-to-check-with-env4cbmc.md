# How To Check With `env4cbmc`

## 1. Generate the interleaving manifest

```bash
goto-cc \
  check-src/osek_priority_interleaving/harness.c \
  check-src/osek_priority_interleaving/isr_define/isr.c \
  check-src/osek_priority_interleaving/task_define/tasks.c \
  check-src/osek_priority_interleaving/osek/osek_runtime_stub.c \
  --interleaving-project-root check-src/osek_priority_interleaving \
  --interleaving-source-files check-src/osek_priority_interleaving/isr_define/isr.c \
  --interleaving-output check-src/osek_priority_interleaving/interleaving_harness.json \
  -o check-src/osek_priority_interleaving/osek_priority_interleaving.out
```

## 2. Inject interleaving blocks

```bash
aib \
  check-src/osek_priority_interleaving \
  check-src/osek_priority_interleaving/interleaving_harness.json \
  check-src/osek_priority_interleaving_injected \
  check-src/osek_priority_interleaving_injected/interleaving_harness_injected.json
```

## 3. Rebuild the injected tree

```bash
goto-cc \
  check-src/osek_priority_interleaving_injected/harness.c \
  check-src/osek_priority_interleaving_injected/isr_define/isr.c \
  check-src/osek_priority_interleaving_injected/task_define/tasks.c \
  check-src/osek_priority_interleaving_injected/osek/osek_runtime_stub.c \
  -o check-src/osek_priority_interleaving_injected/osek_priority_interleaving_injected.out
```

## 4. Run CBMC on the injected sample

```bash
cbmc \
  check-src/osek_priority_interleaving_injected/osek_priority_interleaving_injected.out \
  --function main \
  --unwind 6 \
  --unwinding-assertions
```

## Expected status while implementing

- Before `--os-api osek` exists, the command above without OSEK options should
  fail because the runtime stub does not execute scheduled tasks.
- After the new OSEK module exists, the baseline sample should pass with:

```bash
cbmc \
  check-src/osek_priority_interleaving/osek_priority_interleaving.out \
  --function main \
  --unwind 6 \
  --unwinding-assertions \
  --os-api osek \
  --osek-oil check-src/osek_priority_interleaving/app.oil
```

## 5. Future OSEK scheduler check

Once the new module exists, rerun the final CBMC command with the OSEK options
you introduce, for example:

```bash
cbmc \
  check-src/osek_priority_interleaving_injected/osek_priority_interleaving_injected.out \
  --function main \
  --os-api osek \
  --osek-oil check-src/osek_priority_interleaving/app.oil
```
