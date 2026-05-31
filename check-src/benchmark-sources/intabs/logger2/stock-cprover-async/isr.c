#include "model.h"

void *task_measure1(void *unused)
{
  __CPROVER_atomic_begin();
  (void)unused;
  tickCounter++;
  tickCounter = 0;
  if(tickCounter != 0)
    assert(0);
  intervalCounter++;
  records = 1;
  numberOfRecords++;
  __CPROVER_atomic_end();
  return 0;
}

void *task_measure2(void *unused)
{
  __CPROVER_atomic_begin();
  (void)unused;
  tickCounter = 0;
  if(tickCounter != 0)
    assert(0);
  __CPROVER_atomic_end();
  return 0;
}

void *task_communicate(void *unused)
{
  __CPROVER_atomic_begin();
  (void)unused;
  int _startTime = 1;
  int _interval = 1;
  cmd = nondet_int();
  rspStatus = nondet_int();
  decodingStatus = 0;

  if(cmd == CMD_STOP || cmd == CMD_READ_STATE || cmd == CMD_READ_DATA || cmd == 1)
    decodingStatus = 1;

  if(rspStatus == 1)
  {
    if(cmd == CMD_STOP)
    {
      if(systemState != LOGGING)
        rspStatus = 0;
      else
        systemState = IDLE;
      sendit = 1;
    }
    if(cmd == CMD_READ_STATE)
      sendit = 1;
    if(cmd == CMD_READ_DATA)
      sendit = 1;
    if(cmd == 1)
    {
      if(systemState != IDLE)
        rspStatus = 0;
      else
      {
        if(numberOfRecords + 1 >= 64)
          systemState = IDLE;
        intervalCounter = 0;
        tickCounter = 0;
        numberOfRecords = 0;
        startTime = _startTime;
        interval = _interval;
        systemState = LOGGING;
        if(numberOfRecords != 0)
          assert(0);
        sendit = 1;
      }
    }
  }
  __CPROVER_atomic_end();
  return 0;
}
