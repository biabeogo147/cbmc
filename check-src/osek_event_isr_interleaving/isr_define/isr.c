#include "isr.h"

bool irq_enabled = true;
bool irq_fired = false;
int irq_observed_value = 0;

void *isr_touch_shared(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  if(irq_enabled)
  {
    shared_value += 100;
    irq_observed_value = shared_value;
    irq_fired = true;
    irq_enabled = false;
  }
  __CPROVER_atomic_end();

  return 0;
}

