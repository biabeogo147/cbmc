#include "osek_api.h"
#include "osek_runtime_stub.h"

void ActivateTask(task_idt task_id)
{
  (void)task_id;
}

void TerminateTask(void)
{
}

void SetEvent(task_idt task_id, EventMaskType mask)
{
  (void)task_id;
  (void)mask;
}

void ClearEvent(EventMaskType mask)
{
  (void)mask;
}

void GetEvent(task_idt task_id, EventMaskRefType event)
{
  (void)task_id;
  (void)event;
}

void WaitEvent(EventMaskType mask)
{
  (void)mask;
}

void boot_autostart_task(void)
{
  ActivateTask(TASK_ID_controller);
}

