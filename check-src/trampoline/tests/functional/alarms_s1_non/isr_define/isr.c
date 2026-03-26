#include "isr.h"

bool enable_irq_1 = true;
bool enable_irq_2 = true;
bool enable_irq_3 = true;

void *isr1(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  if (enable_irq_1) {
    ++tpl_locking_depth;
  }
  __CPROVER_atomic_end();

  return 0;
}

void *isr2(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  if (enable_irq_2) {
    tpl_user_task_lock = (tpl_bool)(tpl_user_task_lock ? 0 : 1);
  }
  __CPROVER_atomic_end();

  return 0;
}

void *isr3(void *arg)
{
  (void)arg;

  __CPROVER_atomic_begin();
  if (enable_irq_3) {
    ++tpl_cpt_os_task_lock;
  }
  __CPROVER_atomic_end();

  return 0;
}
