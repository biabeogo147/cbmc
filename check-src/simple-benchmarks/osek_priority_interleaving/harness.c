#include <assert.h>

#include "isr_define/isr.h"
#include "osek/osek_runtime_stub.h"

int x = 0;

int main(void)
{
  boot_autostart_task();

  assert(x == 3);
  assert(!irq_fired);

  return 0;
}
