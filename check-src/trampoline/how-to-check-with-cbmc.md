## Baseline build

```bash
goto-cc \
  -I check-src/trampoline/machines/posix \
  -I check-src/trampoline/viper \
  -I check-src/trampoline/tests/embUnit \
  -I check-src/trampoline/tests/machines/common \
  -I check-src/trampoline/tests/machines/posix \
  -I check-src/trampoline/com \
  -I check-src/trampoline/os \
  -I check-src/trampoline/debug \
  -I check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/trampoline/tests/embUnit/AssertImpl.c \
  check-src/trampoline/tests/embUnit/RepeatedTest.c \
  check-src/trampoline/tests/embUnit/SchedulingCheck.c \
  check-src/trampoline/tests/embUnit/stdImpl.c \
  check-src/trampoline/tests/embUnit/TestCaller.c \
  check-src/trampoline/tests/embUnit/TestCase.c \
  check-src/trampoline/tests/embUnit/TestResult.c \
  check-src/trampoline/tests/embUnit/TestRunner.c \
  check-src/trampoline/tests/embUnit/TestSuite.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/trampoline/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/trampoline/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/trampoline/os/tpl_os_kernel.c \
  check-src/trampoline/os/tpl_os_timeobj_kernel.c \
  check-src/trampoline/os/tpl_os_action.c \
  check-src/trampoline/os/tpl_os_error.c \
  check-src/trampoline/os/tpl_os_os_kernel.c \
  check-src/trampoline/os/tpl_os_os.c \
  check-src/trampoline/os/tpl_os_interrupt_kernel.c \
  check-src/trampoline/os/tpl_os_task_kernel.c \
  check-src/trampoline/os/tpl_os_resource_kernel.c \
  check-src/trampoline/os/tpl_os_alarm_kernel.c \
  check-src/trampoline/machines/posix/tpl_machine_posix.c \
  check-src/trampoline/machines/posix/tpl_viper_interface.c \
  check-src/trampoline/machines/posix/tpl_posix_autosar.c \
  check-src/trampoline/machines/posix/tpl_posix_irq.c \
  check-src/trampoline/machines/posix/tpl_posix_context.c \
  check-src/trampoline/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/trampoline/tests/machines/posix/archTestConfig.c \
  check-src/trampoline/tests/machines/common/commonTestConfig.c \
  -o check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non.out
```

## Baseline check

```bash
cbmc \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non.out \
  --function main \
  --unwind 3 \
  --unwinding-assertions
```

## Interleaving manifest

```bash
goto-cc \
  -I check-src/trampoline/machines/posix \
  -I check-src/trampoline/viper \
  -I check-src/trampoline/tests/embUnit \
  -I check-src/trampoline/tests/machines/common \
  -I check-src/trampoline/tests/machines/posix \
  -I check-src/trampoline/com \
  -I check-src/trampoline/os \
  -I check-src/trampoline/debug \
  -I check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/trampoline/tests/embUnit/AssertImpl.c \
  check-src/trampoline/tests/embUnit/RepeatedTest.c \
  check-src/trampoline/tests/embUnit/SchedulingCheck.c \
  check-src/trampoline/tests/embUnit/stdImpl.c \
  check-src/trampoline/tests/embUnit/TestCaller.c \
  check-src/trampoline/tests/embUnit/TestCase.c \
  check-src/trampoline/tests/embUnit/TestResult.c \
  check-src/trampoline/tests/embUnit/TestRunner.c \
  check-src/trampoline/tests/embUnit/TestSuite.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/trampoline/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/trampoline/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/trampoline/os/tpl_os_kernel.c \
  check-src/trampoline/os/tpl_os_timeobj_kernel.c \
  check-src/trampoline/os/tpl_os_action.c \
  check-src/trampoline/os/tpl_os_error.c \
  check-src/trampoline/os/tpl_os_os_kernel.c \
  check-src/trampoline/os/tpl_os_os.c \
  check-src/trampoline/os/tpl_os_interrupt_kernel.c \
  check-src/trampoline/os/tpl_os_task_kernel.c \
  check-src/trampoline/os/tpl_os_resource_kernel.c \
  check-src/trampoline/os/tpl_os_alarm_kernel.c \
  check-src/trampoline/machines/posix/tpl_machine_posix.c \
  check-src/trampoline/machines/posix/tpl_viper_interface.c \
  check-src/trampoline/machines/posix/tpl_posix_autosar.c \
  check-src/trampoline/machines/posix/tpl_posix_irq.c \
  check-src/trampoline/machines/posix/tpl_posix_context.c \
  check-src/trampoline/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/trampoline/tests/machines/posix/archTestConfig.c \
  check-src/trampoline/tests/machines/common/commonTestConfig.c \
  --interleaving-project-root check-src/trampoline \
  --interleaving-source-files check-src/trampoline/tests/functional/alarms_s1_non/isr_define/isr.c \
  --interleaving-output check-src/trampoline/tests/functional/alarms_s1_non/interleaving_pipeline.json \
  -o check-src/trampoline/tests/functional/alarms_s1_non/alarms_s1_non_interleaving.out
```

## Injected project

```bash
aib \
  check-src/trampoline \
  check-src/trampoline/tests/functional/alarms_s1_non/interleaving_pipeline.json \
  check-src/trampoline_injected \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/interleaving_pipeline_injected.json
```

## Injected build

```bash
goto-cc \
  -I check-src/trampoline_injected/machines/posix \
  -I check-src/trampoline_injected/viper \
  -I check-src/trampoline_injected/tests/embUnit \
  -I check-src/trampoline_injected/tests/machines/common \
  -I check-src/trampoline_injected/tests/machines/posix \
  -I check-src/trampoline_injected/com \
  -I check-src/trampoline_injected/os \
  -I check-src/trampoline_injected/debug \
  -I check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1_non \
  check-src/trampoline_injected/tests/embUnit/AssertImpl.c \
  check-src/trampoline_injected/tests/embUnit/RepeatedTest.c \
  check-src/trampoline_injected/tests/embUnit/SchedulingCheck.c \
  check-src/trampoline_injected/tests/embUnit/stdImpl.c \
  check-src/trampoline_injected/tests/embUnit/TestCaller.c \
  check-src/trampoline_injected/tests/embUnit/TestCase.c \
  check-src/trampoline_injected/tests/embUnit/TestResult.c \
  check-src/trampoline_injected/tests/embUnit/TestRunner.c \
  check-src/trampoline_injected/tests/embUnit/TestSuite.c \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1.c \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/task1_instance.c \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/isr_define/isr.c \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1_non/tpl_app_config.c \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1_non/tpl_os.c \
  check-src/trampoline_injected/os/tpl_os_kernel.c \
  check-src/trampoline_injected/os/tpl_os_timeobj_kernel.c \
  check-src/trampoline_injected/os/tpl_os_action.c \
  check-src/trampoline_injected/os/tpl_os_error.c \
  check-src/trampoline_injected/os/tpl_os_os_kernel.c \
  check-src/trampoline_injected/os/tpl_os_os.c \
  check-src/trampoline_injected/os/tpl_os_interrupt_kernel.c \
  check-src/trampoline_injected/os/tpl_os_task_kernel.c \
  check-src/trampoline_injected/os/tpl_os_resource_kernel.c \
  check-src/trampoline_injected/os/tpl_os_alarm_kernel.c \
  check-src/trampoline_injected/machines/posix/tpl_machine_posix.c \
  check-src/trampoline_injected/machines/posix/tpl_viper_interface.c \
  check-src/trampoline_injected/machines/posix/tpl_posix_autosar.c \
  check-src/trampoline_injected/machines/posix/tpl_posix_irq.c \
  check-src/trampoline_injected/machines/posix/tpl_posix_context.c \
  check-src/trampoline_injected/machines/posix/tpl_posixvp_irq_gen.c \
  check-src/trampoline_injected/tests/machines/posix/archTestConfig.c \
  check-src/trampoline_injected/tests/machines/common/commonTestConfig.c \
  -o check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1_non_injected.out
```

## Injected check

```bash
cbmc \
  check-src/trampoline_injected/tests/functional/alarms_s1_non/alarms_s1_non_injected.out \
  --function main \
  --unwind 3 \
  --unwinding-assertions
```
