#include <assert.h>

#include "../isr_define/isr.h"
#include "../osek/osek_api.h"
#include "tasks.h"

TASK(t1)
{
  EventMaskType snapshot = 0;

  ActivateTask(TASK_ID_2);
  WaitEvent(EVENT_WORK_DONE);
  GetEvent(TASK_ID_1, &snapshot);
  assert((snapshot & EVENT_WORK_DONE) != 0u);
  ClearEvent(EVENT_WORK_DONE);

  assert(shared_value == 2);
  controller_done = 1;
  TerminateTask();
}

TASK(t2)
{
  assert(controller_done == 0);
  shared_value = 2;
  SetEvent(TASK_ID_1, EVENT_WORK_DONE);
  TerminateTask();
}

