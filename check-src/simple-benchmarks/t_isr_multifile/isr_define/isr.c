#include "isr.h"

bool enable_irq_1 = true;
bool enable_irq_2 = true;
int x = 0;

void *isr1(void *arg) {
  (void)arg;

  __CPROVER_atomic_begin();
  if (enable_irq_1) {
    ++x;
    enable_irq_1 = false;
  }
  __CPROVER_atomic_end();

  return 0;
}

void *isr2(void *arg) {
  (void)arg;

  __CPROVER_atomic_begin();
  if (enable_irq_2) {
    --x;
    enable_irq_2 = false;
  }
  __CPROVER_atomic_end();

  return 0;
}
