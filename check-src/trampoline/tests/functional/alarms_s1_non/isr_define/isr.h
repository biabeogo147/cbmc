#ifndef TRAMPOLINE_ALARMS_S1_NON_ISR_H
#define TRAMPOLINE_ALARMS_S1_NON_ISR_H

#include "tpl_os_internal_types.h"

extern bool enable_irq_1;
extern bool enable_irq_2;
extern bool enable_irq_3;

extern volatile uint32 tpl_locking_depth;
extern tpl_bool tpl_user_task_lock;
extern uint32 tpl_cpt_os_task_lock;

void *isr1(void *arg);
void *isr2(void *arg);
void *isr3(void *arg);

#endif
