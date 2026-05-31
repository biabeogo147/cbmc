#include <assert.h>

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

//void irq_err(void) {ERROR: goto ERROR;}
void task_communicate(void);
void task_measure(void);
void task_ext_power(void);

extern _Bool  __VERIFIER_nondet_bool();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}

// Scheduler
int num_irqs = 3;
int count = 4;

int irq_enabled[] = {0, 0, 0}; 

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
        case 2:
          task_ext_power();
          break;
        default:
          ;
      }
    }
  }
}


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

extern uint16_t read_sensor_value();
extern uint16_t process_value(uint32_t time, uint16_t value);
void task_measure(void) {
disable_irq(1);
disable_irq(2);
enable_irq(0); 

schedule_irq();
  __VERIFIER_assume(systemState==LOGGING); // R-W dependency
schedule_irq();
  tickCounter++; // W-W dependency
schedule_irq();

  if (tickCounter == period) { // R-W dependency
    uint16_t value = read_sensor_value();
schedule_irq();
    uint8_t pos = numberOfRecords; // R-W dependency
schedule_irq();
    uint32_t _startTime = startTime; // R-W dependency
schedule_irq();
    uint32_t currentTime = _startTime + period*periodCounter+tickCounter; // R-W dependency
 
schedule_irq();
    tickCounter = 0; // W-W dependency
schedule_irq();
    periodCounter++; // W-W dependency
schedule_irq();
    
    records[pos] =  process_value(currentTime,value); // W-W dependency
schedule_irq();
    numberOfRecords++; // W-W dependency
schedule_irq();
    //assert(startTime==_startTime);
    //assert(numberOfRecords==pos+1);
    __VERIFIER_assert(numberOfRecords==pos+1);
    //if(numberOfRecords!=pos+1) irq_err(); // R-W dependency
  }

enable_irq(1);
enable_irq(2);
}

extern uint8_t get_power_status();
void task_ext_power() {
disable_irq(0);
disable_irq(2);
enable_irq(1);

  uint8_t power = get_power_status();

schedule_irq();
  if(power && systemState==SLEEP) { // R-W dependency
schedule_irq();
    systemState = IDLE; // W-W dependency
schedule_irq();
  }

schedule_irq();
  if(!power && systemState==IDLE) { // R-W dependency
schedule_irq();
    systemState = SLEEP; // W-W dependency
schedule_irq();
  }

enable_irq(0);
enable_irq(2);
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
extern void send_response(uint8_t* buffer, uint8_t len);
uint8_t msgBuffer[MAX_BUFFER];
void task_communicate(void) {
disable_irq(0);
disable_irq(1);
disable_irq(2);

  __VERIFIER_assume(systemState!=SLEEP);
  uint8_t len = receive_cmd(msgBuffer);
  uint8_t cmd = msgBuffer[0];
  uint8_t decodingStatus = CMD_DEC_ERROR;
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_RESTART) {
    decodingStatus = CMD_DEC_OK;
  }
  if (decodingStatus != CMD_DEC_OK) {
    msgBuffer[0] = RSP_ERROR;
    send_response(msgBuffer,1);
  } else {
    uint8_t rspStatus = RSP_SUCCESS;
    switch(cmd) {
      case CMD_STOP:   
        if (systemState != LOGGING) {
          rspStatus = RSP_ERROR;
        } else {
          systemState = IDLE;
        }
        msgBuffer[0] = rspStatus;
        if(systemState==SLEEP) {
          return;
        }
        send_response(msgBuffer,1);
        break;
      case CMD_READ_STATE:
        msgBuffer[0] = rspStatus;
        msgBuffer[1] = systemState;
        msgBuffer[2] = numberOfRecords;
        put_uint32(msgBuffer,3,startTime);
        if(systemState==SLEEP) {
          return;
        }
        send_response(msgBuffer,7);
	break;
      case CMD_READ_DATA: {
        uint8_t pos = msgBuffer[1];
        if(pos>=numberOfRecords) {
          msgBuffer[0] = RSP_ERROR;
          if(systemState==SLEEP) {
            return;
          }
          send_response(msgBuffer,1);
  	} else {
          msgBuffer[0] = RSP_SUCCESS;
          put_uint16(msgBuffer,1,records[pos]);
          if(systemState==SLEEP) {
            return;
          }
          send_response(msgBuffer,3);
	}
	break;
      }
      case CMD_RESTART: {
        uint32_t _startTime = get_uint32(msgBuffer,1);
        uint16_t _period = get_uint16(msgBuffer,5);
        restart(_startTime,_period);
        msgBuffer[0] = rspStatus;
        if(systemState==SLEEP) {
          return;
        }
        send_response(msgBuffer,1);
        break;
      }
      default: 
        break;
    }
  }

enable_irq(0);
enable_irq(1);
enable_irq(2);
}


void initialize(void) {
  systemState = SLEEP; // W-W dependency
  periodCounter = 0; // W-W dependency
  tickCounter = 0; // W-W dependency
  startTime = 0; // W-W dependency
  numberOfRecords = 0; // W-W dependency
}

void run(void)
{
  // Lihao
  enable_irq(0);
  enable_irq(1);
  enable_irq(2);
  schedule_irq();

  // while(1) {
  /*
    __CPROVER_ASYNC_1: 
    task_ext_power();

    __CPROVER_ASYNC_1: 
    task_communicate();

    __CPROVER_ASYNC_1: 
    task_communicate();

    __CPROVER_ASYNC_1: 
    task_measure();
  */
    //  }
}

void main() {
    initialize();
    run();
}
