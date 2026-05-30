#include <assert.h>

typedef unsigned int TaskType;
typedef unsigned int EventMaskType;

enum
{
  TASK_ID_TaskW = 1
};

void ActivateTask(TaskType task);
void TerminateTask(void);
void SetEvent(TaskType task, EventMaskType mask);
void WaitEvent(EventMaskType mask);

static int progressed = 0;

void TaskW(void)
{
  SetEvent(TASK_ID_TaskW, 1u);
  WaitEvent(1u);
  progressed = 1;
  TerminateTask();
}

int main(void)
{
  ActivateTask(TASK_ID_TaskW);
  assert(progressed == 1);
  return 0;
}

