#ifndef INTABS_LOGGER2_MODEL_H
#define INTABS_LOGGER2_MODEL_H

#include <assert.h>

#define IDLE 0
#define LOGGING 1
#define CMD_STOP 2
#define CMD_READ_STATE 3
#define CMD_READ_DATA 4

extern int numberOfRecords;
extern int records;
extern int intervalCounter;
extern int tickCounter;
extern int interval;
extern int startTime;
extern int decodingStatus;
extern int cmd;
extern int sendit;
extern int systemState;
extern int rspStatus;

int nondet_int(void);
void initialize(void);
void *task_measure1(void *unused);
void *task_measure2(void *unused);
void *task_communicate(void *unused);

#endif
