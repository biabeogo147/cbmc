#include "osek_api.h"
#include "osek_runtime_stub.h"

void ActivateTask(task_idt task_id)
{
  (void)task_id;
}

void TerminateTask(void)
{
}

void ChainTask(task_idt task_id)
{
  (void)task_id;
}

void Schedule(void)
{
}

void boot_autostart_task(void)
{
  ActivateTask(TASK_ID_1);
}
