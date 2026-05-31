#ifndef ICBMC_LOGGER_MODEL_H
#define ICBMC_LOGGER_MODEL_H

#include <assert.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define MAX_RECORDS 64
#define IDLE 0
#define LOGGING 1
#define CMD_DEC_OK 1
#define CMD_DEC_ERROR 0
#define RSP_SUCCESS 1
#define RSP_ERROR 0
#define CMD_START 1
#define CMD_STOP 2
#define CMD_READ_STATE 3
#define CMD_READ_DATA 4

extern uint16_t numberOfRecords;
extern uint16_t records[MAX_RECORDS];
extern uint32_t intervalCounter;
extern uint16_t tickCounter;
extern uint16_t interval;
extern uint32_t startTime;
extern uint8_t systemState;
extern uint8_t communicationEvents;

uint16_t read_sensor_value(void);
uint8_t read_cmd(void);
uint16_t get_uint16(void);
uint32_t get_uint32(void);
void send_response(void);

void initialize(void);
void stop(void);
void start(uint32_t _startTime, uint16_t _interval);
uint8_t get_cmd(uint8_t *decodingStatus);
void task_measure(void);
void task_communicate(void);

#endif
