#include <assert.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

#define MAX_RECORDS  64
uint16_t numberOfRecords;
uint16_t records[MAX_RECORDS];

#define MAX_BUFFER  64
uint8_t msgBuffer[MAX_BUFFER];

uint32_t intervalCounter; 
uint16_t tickCounter;     
uint16_t interval;     
uint32_t startTime;

#define IDLE 0
#define LOGGING 1
uint8_t systemState;

#define CMD_DEC_OK 1
#define CMD_DEC_ERROR 0
#define RSP_SUCCESS 1
#define RSP_ERROR 0

#define TASK_COMMUNICATE 1
#define TASK_MEASURE 2

#define CMD_START 1
#define CMD_STOP 2
#define CMD_READ_STATE 3
#define CMD_READ_DATA 4

// Lihao
const int __CPROVER_thread_priorities[] = {5, 2};
const char* __CPROVER_threads[] = {"c::task_communicate", "c::task_measure"};

extern _Bool  __VERIFIER_nondet_bool();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}

//void irq_err(void) { ERROR: goto ERROR;}
void task_communicate(void);
void task_measure(void);

// Scheduler
int num_irqs = 2;
int count = 2;

int irq_enabled[] = {0, 0}; 

void enable_irq(int i) {
  irq_enabled[i] = 1;  
}

void disable_irq(int i) {
  irq_enabled[i] = 0;  
}

void schedule_irq(void) {
  int j = count;
  int irq;

  for (int i = 0; i < j; i++) {
    irq = __VERIFIER_nondet_int();
    __VERIFIER_assume(irq >= 0 && irq < num_irqs);

    if(irq_enabled[irq] && __VERIFIER_nondet_bool()) {
      count--;

      switch(irq) {
        case 0:
          task_communicate();
          break;
        case 1:
          task_measure();
          break;
        default:
          ;
      }
    }
  }
}

void stop(void)
{
  systemState = IDLE;
}

inline void start(uint32_t _startTime,uint16_t _interval)
{
  if (numberOfRecords+1 >= MAX_RECORDS) {
    stop();
  }
  intervalCounter = 0;
  tickCounter = 0;
  numberOfRecords = 0;
  startTime = _startTime;
  interval = _interval;
  systemState = LOGGING;
  //if(numberOfRecords!=0) irq_err();
  //assert(numberOfRecords==0);
  __VERIFIER_assert(numberOfRecords==0);
}

extern uint16_t read_sensor_value();
void task_measure(void) 
{
disable_irq(1);
enable_irq(0);

schedule_irq();
  tickCounter++; // W-W dependency
schedule_irq();

  if (tickCounter == interval) { // R-W dependency
    uint16_t value = read_sensor_value();
 
schedule_irq();
    tickCounter = 0; // W-W dependency
schedule_irq();
    intervalCounter++; // W-W dependency
schedule_irq();
    
    records[numberOfRecords] =  value; // R-W dependency
schedule_irq();
    numberOfRecords++; // W-W dependency
schedule_irq();
  }
enable_irq(1);
}

extern uint8_t read_cmd();
uint8_t get_cmd(uint8_t* decodingStatus) {
  uint8_t cmd = read_cmd();
  *decodingStatus = CMD_DEC_ERROR;
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_START) {
    *decodingStatus = CMD_DEC_OK;
  }
  return cmd;
}

extern uint16_t get_uint16();
extern uint32_t get_uint32();
extern void send_response();
void task_communicate(void)
{
disable_irq(0);
disable_irq(1);

  uint8_t decodingStatus;
  uint8_t cmd = get_cmd(&decodingStatus);
  uint8_t rspStatus = RSP_SUCCESS;

  if (decodingStatus != CMD_DEC_OK) {
    rspStatus = RSP_ERROR;
  }
  if (rspStatus == RSP_SUCCESS) {
    switch(cmd) {
      case CMD_STOP:   
        if (systemState != LOGGING) {
          rspStatus = RSP_ERROR;
        } else {
          stop();
        }
        send_response();
        break;
      case CMD_READ_STATE:
        send_response();
	break;
      case CMD_READ_DATA:
        send_response();
	break;
      case CMD_START:
        if (systemState != IDLE) {
          rspStatus = RSP_ERROR;  
        } else {
          uint32_t _startTime = get_uint32();
          uint16_t _interval = get_uint16();
	  start(_startTime,_interval);
	}
        send_response();
        break;
      default: break;
    }
  }

enable_irq(0);
enable_irq(1);
}


void initialize(void) {
  systemState = IDLE; // W-W dependency
}

void run(void)
{
  // Lihao
  enable_irq(0);
  enable_irq(1);
  schedule_irq();

/*
  __CPROVER_ASYNC_1: 
  task_communicate();

  __CPROVER_ASYNC_1: 
  task_measure();
*/

/*
  while(1) {
    uint8_t currentTask;
    switch(currentTask) {
      case TASK_COMMUNICATE :
        task_communicate();
	break;
      case TASK_MEASURE:
        task_measure();
        break;
      default: break;
    }
  }
*/
}

void main() {
    initialize();
    run();
}
