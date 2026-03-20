#ifndef T_ISR_MULTIFILE_ISR_H
#define T_ISR_MULTIFILE_ISR_H

#include <stdbool.h>

extern bool enable_irq_1;
extern bool enable_irq_2;
extern int x;

void *isr1(void *arg);
void *isr2(void *arg);

#endif
