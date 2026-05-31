#include "model.h"

int main(void)
{
  initialize();
  cmd = nondet_int();
  rspStatus = nondet_int();
  tickCounter++;
  intervalCounter++;
  return 0;
}
