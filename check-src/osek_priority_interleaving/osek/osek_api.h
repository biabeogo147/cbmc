#ifndef OSEK_PRIORITY_INTERLEAVING_API_H
#define OSEK_PRIORITY_INTERLEAVING_API_H

#define TASK(name) void name(void)

typedef enum task_id
{
  TASK_ID_controller = 1,
  TASK_ID_worker = 2,
  TASK_ID_cleanup = 3
} task_idt;

void ActivateTask(task_idt task_id);
void TerminateTask(void);
void ChainTask(task_idt task_id);
void Schedule(void);

#endif
