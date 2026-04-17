#ifndef OSEK_EVENT_ISR_INTERLEAVING_API_H
#define OSEK_EVENT_ISR_INTERLEAVING_API_H

#define TASK(name) void name(void)

typedef unsigned int EventMaskType;
typedef EventMaskType *EventMaskRefType;

typedef enum task_id
{
  TASK_ID_1 = 1,
  TASK_ID_2 = 2,
  TASK_ID_3 = 3,
  TASK_ID_4 = 4,
  TASK_ID_5 = 5,
  TASK_ID_6 = 6,
  TASK_ID_7 = 7,
  TASK_ID_8 = 8,
  TASK_ID_9 = 9,
  TASK_ID_10 = 10,
  TASK_ID_11 = 11,
  TASK_ID_12 = 12,
  TASK_ID_13 = 13,
  TASK_ID_14 = 14,
  TASK_ID_15 = 15,
  TASK_ID_16 = 16,
  TASK_ID_17 = 17,
  TASK_ID_18 = 18,
  TASK_ID_19 = 19,
  TASK_ID_20 = 20,
  TASK_ID_21 = 21,
  TASK_ID_22 = 22,
  TASK_ID_23 = 23,
  TASK_ID_24 = 24,
  TASK_ID_25 = 25,
  TASK_ID_26 = 26,
  TASK_ID_27 = 27,
  TASK_ID_28 = 28,
  TASK_ID_29 = 29,
  TASK_ID_30 = 30
} task_idt;

enum
{
  EVENT_WORK_DONE = 1u,
  EVENT_DATA_READY = 2u,
  EVENT_TIMER_EXP = 4u
};

void ActivateTask(task_idt task_id);
void TerminateTask(void);
void SetEvent(task_idt task_id, EventMaskType mask);
void ClearEvent(EventMaskType mask);
void GetEvent(task_idt task_id, EventMaskRefType event);
void WaitEvent(EventMaskType mask);

#endif