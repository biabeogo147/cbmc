#include <assert.h>

typedef unsigned int TaskType;
typedef unsigned int EventMaskType;
typedef EventMaskType *EventMaskRefType;

enum
{
  TASK_ID_TaskE = 1
};

void ActivateTask(TaskType task);
void TerminateTask(void);
void SetEvent(TaskType task, EventMaskType mask);
void ClearEvent(EventMaskType mask);
void GetEvent(TaskType task, EventMaskRefType event);

static int done = 0;

void TaskE(void)
{
  EventMaskType snapshot = 0;

  SetEvent(TASK_ID_TaskE, 1u);
  GetEvent(TASK_ID_TaskE, &snapshot);
  assert(snapshot == 1u);

  ClearEvent(1u);
  GetEvent(TASK_ID_TaskE, &snapshot);
  assert(snapshot == 0u);

  done = 1;
  TerminateTask();
}

int main(void)
{
  ActivateTask(TASK_ID_TaskE);
  assert(done == 1);
  return 0;
}
