#include <assert.h>

typedef unsigned int TaskType;
typedef unsigned int EventMaskType;
typedef EventMaskType *EventMaskRefType;

#define EVENT_1 (1u << 0)
#define EVENT_2 (1u << 1)
#define EVENT_3 (1u << 2)

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

  SetEvent(TASK_ID_TaskE, EVENT_1);
  SetEvent(TASK_ID_TaskE, EVENT_3);
  GetEvent(TASK_ID_TaskE, &snapshot);
  assert(snapshot == (EVENT_1 | EVENT_3));

  SetEvent(TASK_ID_TaskE, EVENT_2);
  GetEvent(TASK_ID_TaskE, &snapshot);
  assert(snapshot == (EVENT_1 | EVENT_2 | EVENT_3));

  ClearEvent(EVENT_1 | EVENT_3);
  GetEvent(TASK_ID_TaskE, &snapshot);
  assert(snapshot == EVENT_2);

  ClearEvent(EVENT_2);
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


