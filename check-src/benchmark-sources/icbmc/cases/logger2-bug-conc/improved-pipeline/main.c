
extern void __VERIFIER_atomic_begin();
extern void __VERIFIER_atomic_end();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}

//void irq_err(void) {ERROR: goto ERROR;}


int __TRANS_thread_running[] = {0, 0, 0, 0};

void __VERIFIER_atomic_TRANS_atomic_assume_task_communicate(void) {
__VERIFIER_assume( __TRANS_thread_running[1]==0);
}

void TRANS_atomic_assume_task_communicate(void) {
__VERIFIER_assume( __TRANS_thread_running[1]==0);
}

void TRANS_task_communicate_enter_thread() {
__VERIFIER_assume( __TRANS_thread_running[1]==0);
__TRANS_thread_running[0]=1;
__VERIFIER_assume( __TRANS_thread_running[1]==0);
}

void TRANS_task_communicate_leave_thread() {
__VERIFIER_assume( __TRANS_thread_running[1]==0);
__TRANS_thread_running[0]=0;
__VERIFIER_assume( __TRANS_thread_running[1]==0);
}

void __VERIFIER_atomic_TRANS_atomic_assume_task_communicate2(void) {
__VERIFIER_assume( __TRANS_thread_running[0]==0);
}

void TRANS_atomic_assume_task_communicate2(void) {
__VERIFIER_assume( __TRANS_thread_running[0]==0);
}

void TRANS_task_communicate2_enter_thread() {
__VERIFIER_assume( __TRANS_thread_running[0]==0);
__TRANS_thread_running[1]=1;
__VERIFIER_assume( __TRANS_thread_running[0]==0);
}

void TRANS_task_communicate2_leave_thread() {
__VERIFIER_assume( __TRANS_thread_running[0]==0);
__TRANS_thread_running[1]=0;
__VERIFIER_assume( __TRANS_thread_running[0]==0);
}

void __VERIFIER_atomic_TRANS_atomic_assume_task_measure(void) {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
}

void TRANS_atomic_assume_task_measure(void) {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
}

void TRANS_task_measure_enter_thread() {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
__TRANS_thread_running[2]=1;
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
}

void TRANS_task_measure_leave_thread() {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
__TRANS_thread_running[2]=0;
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0);
}

void __VERIFIER_atomic_TRANS_atomic_assume_task_ext_power(void) {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
}

void TRANS_atomic_assume_task_ext_power(void) {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
}

void TRANS_task_ext_power_enter_thread() {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
__TRANS_thread_running[3]=1;
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
}

void TRANS_task_ext_power_leave_thread() {
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
__TRANS_thread_running[3]=0;
__VERIFIER_assume(__TRANS_thread_running[0]==0 && __TRANS_thread_running[1]==0 && __TRANS_thread_running[2]==0);
}


#include <assert.h>
#include <pthread.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define MAX_RECORDS  64
uint8_t numberOfRecords;
uint16_t records[MAX_RECORDS];

#define MAX_BUFFER 16

uint32_t periodCounter;
uint16_t tickCounter;
uint16_t period;
uint32_t startTime;

#define IDLE 0
#define LOGGING 1
#define SLEEP 2
uint8_t systemState;

#define CMD_DEC_OK 1
#define CMD_DEC_ERROR 0
#define RSP_SUCCESS 1
#define RSP_ERROR 0

#define CMD_RESTART 1
#define CMD_STOP 2
#define CMD_READ_STATE 3
#define CMD_READ_DATA 4

// Lihao
const int __CPROVER_thread_priorities[] = {22, 5, 1};
const char* __CPROVER_threads[] = {"c::task_communicate", "c::task_measure", "c::task_ext_power"};

void restart(uint32_t _startTime,uint16_t _period)
{
  if (numberOfRecords+1 >= MAX_RECORDS) {
    systemState = IDLE;
  }
  periodCounter = 0;
  tickCounter = 0;
  numberOfRecords = 0;
  startTime = _startTime;
  period = _period;
  systemState = LOGGING;
}

extern uint8_t nondet_uint8();
uint16_t read_sensor_value(void) {
  return (uint16_t)nondet_uint8();
}
uint16_t process_value(uint32_t time, uint16_t value) {
  (void)time;
  (void)value;
  return (uint16_t)nondet_uint8();
}

extern uint8_t nondet_uint8();
uint8_t get_power_status(void) {
  return nondet_uint8();
}

uint8_t get_cmd(uint8_t* buffer, uint8_t* cmd) {
}

uint16_t get_uint16(uint8_t* buffer, uint8_t pos) {
  return (((uint16_t)buffer[pos])<<8) | (uint16_t)buffer[pos+1];
}
void put_uint16(uint8_t* buffer, uint8_t pos, uint16_t val) {
  buffer[pos] = (uint8_t)(val>>8);
  buffer[pos+1] = (uint8_t)val;
}
uint32_t get_uint32(uint8_t* buffer, uint8_t pos) {
  return (((uint32_t)buffer[pos])<<24) |
         (((uint32_t)buffer[pos+1])<<16) |
         (((uint32_t)buffer[pos+2])<<8) |
         (uint32_t)buffer[pos+3];
}
void put_uint32(uint8_t* buffer, uint8_t pos, uint32_t val) {
  buffer[pos] = (uint8_t)(val>>24);
  buffer[pos+1] = (uint8_t)(val>>16);
  buffer[pos+2] = (uint8_t)(val>>8);
  buffer[pos+3] = (uint8_t)val;
}
extern uint8_t nondet_uint8();
uint8_t receive_cmd(uint8_t* buffer) {
  buffer[0] = nondet_uint8();
  buffer[1] = nondet_uint8();
  buffer[2] = nondet_uint8();
  buffer[3] = nondet_uint8();
  buffer[4] = nondet_uint8();
  buffer[5] = nondet_uint8();
  buffer[6] = nondet_uint8();
}
void send_response(uint8_t* buffer, uint8_t len) {
  (void)buffer;
  (void)len;
}
uint8_t msgBuffer[MAX_BUFFER];

#include "isr_define/isr.c"


void initialize(void) {
  systemState = SLEEP;
  periodCounter = 0;
  tickCounter = 0;
  startTime = 0;
  numberOfRecords = 0;
}

void run(void)
{
  // Lihao
  pthread_t t1, t2, t3, t4;

#if 0
  // while(1) {



    //  }
#endif
}

void main() {
    initialize();
    run();
}
