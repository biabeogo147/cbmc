#include "model.h"

int main(void)
{
  initialize();

  __CPROVER_ASYNC_1:
  task_communicate(0);

  __CPROVER_ASYNC_2:
  task_measure1(0);

  __CPROVER_ASYNC_3:
  task_measure2(0);

  return 0;
}
