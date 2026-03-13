#include <assert.h>
#include <stdbool.h>

bool enable_irq_1 = true;
bool enable_irq_2 = true;
int x = 0;

void *isr1(void *arg) {
  __CPROVER_atomic_begin();
  if (enable_irq_1) {
    ++x;
    enable_irq_1 = false;
  }
  __CPROVER_atomic_end();
}

void *isr2(void *arg) {
  __CPROVER_atomic_begin();
  if (enable_irq_2) {
    --x;
    enable_irq_2 = false;
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
  task1();
  task2();

  assert(x == 5);

  return 0;
}