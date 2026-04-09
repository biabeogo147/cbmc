#include <assert.h>

#include "../isr_define/isr.h"
#include "../osek/osek_api.h"
#include "tasks.h"

extern _Bool nondet_bool(void);
void *isr_touch_shared(void *arg);

TASK(controller)
{
  EventMaskType snapshot = 0;

  ActivateTask(TASK_ID_worker);
  WaitEvent(EVENT_WORK_DONE);
  GetEvent(TASK_ID_controller, &snapshot);
  assert((snapshot & EVENT_WORK_DONE) != 0u);
  ClearEvent(EVENT_WORK_DONE);
if (nondet_bool()) isr_touch_shared(0);

  assert(shared_value == 2);
  controller_done = 1;
  TerminateTask();
}

TASK(worker)
{
  if (nondet_bool()) isr_touch_shared(0);
  assert(controller_done == 0);
  shared_value = 2;
  SetEvent(TASK_ID_controller, EVENT_WORK_DONE);
  TerminateTask();
}

