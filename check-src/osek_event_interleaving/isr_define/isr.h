#ifndef OSEK_EVENT_ISR_INTERLEAVING_ISR_H
#define OSEK_EVENT_ISR_INTERLEAVING_ISR_H

#include <stdbool.h>

#ifndef __CPROVER_atomic_begin
#define __CPROVER_atomic_begin() ((void)0)
#endif

#ifndef __CPROVER_atomic_end
#define __CPROVER_atomic_end() ((void)0)
#endif

extern bool irq_enabled;
extern bool irq_fired;
extern int irq_observed_value;
extern int shared_value;
extern int controller_done;

void *isr_touch_shared(void *arg);

#endif

