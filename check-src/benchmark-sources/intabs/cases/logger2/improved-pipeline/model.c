#include "model.h"

int numberOfRecords;
int records;
int intervalCounter;
int tickCounter;
int interval;
int startTime;
int decodingStatus;
int cmd;
int sendit;
int systemState;
int rspStatus;

void initialize(void)
{
  systemState = IDLE;
}
