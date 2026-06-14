#ifndef ISR_TIMER_H
#define ISR_TIMER_H

#include <stdbool.h>

extern bool timer_irq_enabled;
extern int shared_value;

void isr_timer_handler(void);

#endif