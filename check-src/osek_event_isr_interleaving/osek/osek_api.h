#ifndef OSEK_EVENT_ISR_INTERLEAVING_API_H
#define OSEK_EVENT_ISR_INTERLEAVING_API_H

#define TASK(name) void name(void)

typedef unsigned int EventMaskType;
typedef EventMaskType *EventMaskRefType;

typedef enum task_id
{
  TASK_ID_controller = 1,
  TASK_ID_worker = 2
} task_idt;

enum
{
  EVENT_WORK_DONE = 1u
};

void ActivateTask(task_idt task_id);
void TerminateTask(void);
void SetEvent(task_idt task_id, EventMaskType mask);
void ClearEvent(EventMaskType mask);
void GetEvent(task_idt task_id, EventMaskRefType event);
void WaitEvent(EventMaskType mask);

#endif

