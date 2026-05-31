#include "model.h"

void run(void)
{
  __CPROVER_ASYNC_1:
  task_measure();

  if(systemState == IDLE)
    start(get_uint32(), get_uint16());
  communicationEvents++;
}

int main(void)
{
  initialize();
  run();
  return 0;
}
