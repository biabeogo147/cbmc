#include <assert.h>

#include "../isr_define/isr.h"
#include "../osek/osek_api.h"
#include "tasks.h"

TASK(t1)
{
  x = 1;
  ActivateTask(TASK_ID_2);
  assert(x == 2);
  ChainTask(TASK_ID_3);
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
