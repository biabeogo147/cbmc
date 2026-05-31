#include "model.h"

uint16_t numberOfRecords;
uint16_t records[MAX_RECORDS];
uint32_t intervalCounter;
uint16_t tickCounter;
uint16_t interval;
uint32_t startTime;
uint8_t systemState;
uint8_t communicationEvents;

void stop(void)
{
  systemState = IDLE;
}

void start(uint32_t _startTime, uint16_t _interval)
{
  if(numberOfRecords + 1 >= MAX_RECORDS)
    stop();
  intervalCounter = 0;
  tickCounter = 0;
  numberOfRecords = 0;
  startTime = _startTime;
  interval = _interval;
  systemState = LOGGING;
  assert(numberOfRecords == 0);
}

void initialize(void)
{
  systemState = IDLE;
}

uint8_t get_cmd(uint8_t *decodingStatus)
{
  uint8_t cmd = read_cmd();
  *decodingStatus = CMD_DEC_ERROR;
  if(cmd == CMD_STOP || cmd == CMD_READ_STATE || cmd == CMD_READ_DATA || cmd == CMD_START)
    *decodingStatus = CMD_DEC_OK;
  return cmd;
}
