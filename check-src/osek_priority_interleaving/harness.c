#include <assert.h>

#include "isr_define/isr.h"
#include "osek/osek_runtime_stub.h"

int main(void)
{
  boot_autostart_task();

  assert(shared_value == 3);
  assert(!irq_fired);

  return 0;
}
