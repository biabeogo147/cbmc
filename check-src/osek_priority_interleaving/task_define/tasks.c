#include <assert.h>

#include "../isr_define/isr.h"
#include "../osek/osek_api.h"
#include "tasks.h"

TASK(t1)
{
  x = 1;
  ActivateTask(TASK_ID_worker);
  assert(x == 2);
  ChainTask(TASK_ID_cleanup);
}

TASK(t2)
{
  assert(x == 1);
  x = 2;
  TerminateTask();
}

TASK(t3)
{
  assert(x == 2);
  x = 3;
  TerminateTask();
}
