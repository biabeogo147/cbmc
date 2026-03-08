#include <assert.h>

int __ESBMC_activation_task(const char *task_id, void (*func)(void));

int x1 = 0;
int x2 = 0;
int x3 = 0;

void t3(void)
{
  assert(x1 == 0);
  x2 = 1;
  assert(x3 == 0 || x3 == 1);
}

void t2(void)
{
  assert(x2 == 0);
  x3 = 1;
  assert(x1 == 1);
}

void t1(void)
{
  x1 = 1;
  __ESBMC_activation_task("t3", t3);
  __ESBMC_activation_task("t2", t2);
  if (!x3)
    assert(x2 == 1);
}

int main(void)
{
  __ESBMC_activation_task("t1", t1);
  return 0;
}