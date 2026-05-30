#include <assert.h>

typedef unsigned int TaskType;
typedef unsigned int EventMaskType;

enum
{
  TASK_ID_TaskW = 1,
  TASK_ID_TaskS = 2
};

void ActivateTask(TaskType task);
void TerminateTask(void);
void WaitEvent(EventMaskType mask);

static int waiter_progress = 0;
static int setter_progress = 0;

void TaskW(void)
{
  WaitEvent(1u);
  waiter_progress = 1;
  TerminateTask();
}

void TaskS(void)
{
  setter_progress = 1;
  TerminateTask();
}

int main(void)
{
  ActivateTask(TASK_ID_TaskW);
  ActivateTask(TASK_ID_TaskS);

  assert(waiter_progress == 0);
  assert(setter_progress == 1);
  return 0;
}

