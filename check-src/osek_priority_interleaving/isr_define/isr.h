#ifndef OSEK_PRIORITY_INTERLEAVING_ISR_H
#define OSEK_PRIORITY_INTERLEAVING_ISR_H

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

void *isr_boost_shared(void *arg);

#endif
