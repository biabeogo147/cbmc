#include "isr.h"

bool irq_enabled = true;
bool irq_fired = false;
int irq_observed_value = 0;

void *isr_boost_shared(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  if(irq_enabled)
  {
    x += 100;
    irq_observed_value = x;
    irq_fired = true;
    irq_enabled = false;
  }
  __CPROVER_atomic_end();

  return 0;
}
