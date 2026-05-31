## Baseline build

```bash
goto-cc \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/viper \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/common \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/com \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/os \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/debug \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/AssertImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/RepeatedTest.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/SchedulingCheck.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/stdImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestCaller.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestCase.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestResult.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestRunner.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestSuite.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_timeobj_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_action.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_error.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_interrupt_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_task_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_resource_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_alarm_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_machine_posix.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_viper_interface.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_autosar.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_irq.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_context.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/posix/archTestConfig.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/common/commonTestConfig.c \
  -o check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non.out
```

## Baseline check

```bash
cbmc \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non.out \
  --function main \
  --unwind 3 \
  --unwinding-assertions
```

In the current `alarms_s1_non` sample, `main` owns three app-level globals
(`alarms_irq_guard_1..3`) and asserts that they keep their expected values
before `StartOS()`. Without injected interleaving, those three assertions stay
`SUCCESS`.

## Interleaving manifest

```bash
goto-cc \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/viper \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/common \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/com \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/os \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/debug \
  -I check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/AssertImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/RepeatedTest.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/SchedulingCheck.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/stdImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestCaller.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestCase.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestResult.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestRunner.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/embUnit/TestSuite.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_timeobj_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_action.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_error.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_interrupt_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_task_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_resource_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/os/tpl_os_alarm_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_machine_posix.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_viper_interface.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_autosar.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_irq.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posix_context.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/posix/archTestConfig.c \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/machines/common/commonTestConfig.c \
  --interleaving-project-root check-src/benchmark-sources/trampoline/improved-pipeline \
  --interleaving-source-files check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/isr_define/isr.c \
  --interleaving-output check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/interleaving_pipeline.json \
  -o check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/alarms_s1_non_interleaving.out
```

## Injected project

```bash
aib \
  check-src/benchmark-sources/trampoline/improved-pipeline \
  check-src/benchmark-sources/trampoline/improved-pipeline/tests/functional/alarms_s1_non/interleaving_pipeline.json \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/interleaving_pipeline_injected.json
```

## Injected build

```bash
goto-cc \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/viper \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/machines/common \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/machines/posix \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/com \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/os \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/debug \
  -I check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/AssertImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/RepeatedTest.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/SchedulingCheck.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/stdImpl.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/TestCaller.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/TestCase.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/TestResult.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/TestRunner.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/embUnit/TestSuite.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_timeobj_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_action.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_error.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_os_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_os.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_interrupt_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_task_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_resource_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/os/tpl_os_alarm_kernel.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_machine_posix.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_viper_interface.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_posix_autosar.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_posix_irq.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_posix_context.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/machines/posix/archTestConfig.c \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/machines/common/commonTestConfig.c \
  -o check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1_non_injected.out
```

## Injected check

```bash
cbmc \
  check-src/benchmark-sources/trampoline/improved-pipeline-injected/tests/functional/alarms_s1_non/alarms_s1_non_injected.out \
  --function main \
  --unwind 3 \
  --unwinding-assertions
```

With the current ISR experiment, the injected build should now expose failures
on the three `main.assertion.*` properties for `alarms_irq_guard_1..3`, in
addition to the existing broader Trampoline/POSIX bounded-check surface.
