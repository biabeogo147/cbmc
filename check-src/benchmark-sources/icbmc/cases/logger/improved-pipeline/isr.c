#include "model.h"

void task_measure(void)
{
  __CPROVER_atomic_begin();
  tickCounter++;

  if(tickCounter == interval)
  {
    uint16_t value = read_sensor_value();
    tickCounter = 0;
    intervalCounter++;
    records[numberOfRecords] = value;
    numberOfRecords++;
  }
  __CPROVER_atomic_end();
}

void task_communicate(void)
{
  __CPROVER_atomic_begin();
  uint8_t decodingStatus;
  uint8_t cmd = get_cmd(&decodingStatus);
  uint8_t rspStatus = RSP_SUCCESS;
  communicationEvents++;

  if(decodingStatus != CMD_DEC_OK)
    rspStatus = RSP_ERROR;

  if(rspStatus == RSP_SUCCESS)
  {
    switch(cmd)
    {
    case CMD_STOP:
      if(systemState != LOGGING)
        rspStatus = RSP_ERROR;
      else
        stop();
      send_response();
      break;
    case CMD_READ_STATE:
      send_response();
      break;
    case CMD_READ_DATA:
      send_response();
      break;
    case CMD_START:
      if(systemState != IDLE)
        rspStatus = RSP_ERROR;
      else
        start(get_uint32(), get_uint16());
      send_response();
      break;
    default:
      break;
    }
  }
  __CPROVER_atomic_end();
}
