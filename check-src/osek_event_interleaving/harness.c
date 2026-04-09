#include <assert.h>

#include "isr_define/isr.h"
#include "osek/osek_runtime_stub.h"

int shared_value = 0;
int controller_done = 0;

int main(void)
{
  boot_autostart_task();

  assert(controller_done == 1);
  assert(shared_value == 2);
  assert(!irq_fired);
  return 0;
}

