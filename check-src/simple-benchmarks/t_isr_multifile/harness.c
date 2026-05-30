#include <assert.h>

#include "isr_define/isr.h"
#include "task_define/task.h"

int main(void) {
  task1();
  task2();

  assert(x == 5);

  return 0;
}
