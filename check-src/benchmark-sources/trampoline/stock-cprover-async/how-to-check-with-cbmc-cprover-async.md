## Async build

```bash
goto-cc \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/viper \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/tests/machines/common \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/tests/machines/posix \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/com \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/os \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/debug \
  -I check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/AssertImpl.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/RepeatedTest.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/SchedulingCheck.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/stdImpl.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/TestCaller.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/TestCase.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/TestResult.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/TestRunner.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/embUnit/TestSuite.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_timeobj_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_action.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_error.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_os_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_os.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_interrupt_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_task_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_resource_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/os/tpl_os_alarm_kernel.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_machine_posix.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_viper_interface.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_posix_autosar.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_posix_irq.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_posix_context.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/machines/posix/archTestConfig.c \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/machines/common/commonTestConfig.c \
  -o check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1_non_async.out
```

## Async check

```bash
cbmc \
  check-src/benchmark-sources/trampoline/stock-cprover-async/tests/functional/alarms_s1_non/alarms_s1_non_async.out \
  --function main \
  --unwind 3 \
  --unwinding-assertions
```

In this variant, the interleaving points are encoded directly in
`tests/functional/alarms_s1_non/alarms_s1.c` with explicit
`__CPROVER_ASYNC_*: isrX(0);` statements, so there is no `aib` step.

With the current full Trampoline source slice, `goto-cc` succeeds on this
async variant, but the direct `cbmc` run currently stops early with:

```text
pointer handling for concurrency is unsound
```

so this folder is useful as a direct async modeling experiment, but not yet as
a full end-to-end replacement for the previous non-async pipeline.
