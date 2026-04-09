#include <assert.h>

#include "isr_define/isr.h"
#include "osek/osek_runtime_stub.h"

extern _Bool nondet_bool(void);
void *isr_touch_shared(void *arg);

int shared_value = 0;
int controller_done = 0;

int main(void)
{
  boot_autostart_task();

  if (nondet_bool()) isr_touch_shared(0);
  assert(controller_done == 1);
  if (nondet_bool()) isr_touch_shared(0);
  assert(shared_value == 2);
  assert(!irq_fired);
  return 0;
}

