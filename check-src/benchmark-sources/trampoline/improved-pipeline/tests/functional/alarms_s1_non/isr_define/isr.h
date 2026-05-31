#ifndef TRAMPOLINE_ALARMS_S1_NON_ISR_H
#define TRAMPOLINE_ALARMS_S1_NON_ISR_H

#include <stdbool.h>

extern bool enable_irq_1;
extern bool enable_irq_2;
extern bool enable_irq_3;

extern int alarms_irq_guard_1;
extern int alarms_irq_guard_2;
extern int alarms_irq_guard_3;

void *isr1(void *arg);
void *isr2(void *arg);
void *isr3(void *arg);

#endif
