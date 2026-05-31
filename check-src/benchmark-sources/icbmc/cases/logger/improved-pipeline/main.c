#include "model.h"

void run(void)
{
  if(systemState == IDLE)
    start(get_uint32(), get_uint16());

  tickCounter++;
  intervalCounter++;
  communicationEvents++;
}

int main(void)
{
  initialize();
  run();
  return 0;
}
