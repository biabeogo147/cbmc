#include <assert.h>

#include "../isr_define/isr.h"
#include "../osek/osek_api.h"
#include "tasks.h"

TASK(controller)
{
  shared_value = 1;
  ActivateTask(TASK_ID_worker);
  assert(shared_value == 2);
  ChainTask(TASK_ID_cleanup);
}

TASK(worker)
{
  assert(shared_value == 1);
  shared_value = 2;
  TerminateTask();
}

TASK(cleanup)
{
  assert(shared_value == 2);
  shared_value = 3;
  TerminateTask();
}
