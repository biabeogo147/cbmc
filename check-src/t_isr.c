#include <assert.h>
#include <stdbool.h>

bool enable_irq = true;
int x = 0;

void *isr1(void *arg) {
  __CPROVER_atomic_begin();
  if (enable_irq) {
    ++x;
  }
  __CPROVER_atomic_end();
}

void task1() {
  x += 2;
}

void task2() {
  x += 3;
}

int main() {
  __CPROVER_ASYNC_0: isr1(0);

  task1();
  task2();

  assert(x == 5);

  return 0;
}