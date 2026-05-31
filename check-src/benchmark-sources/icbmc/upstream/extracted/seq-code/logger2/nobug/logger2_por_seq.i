# 1 "logger2_por_seq.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "logger2_por_seq.c"
# 1 "/usr/include/assert.h" 1 3 4
# 35 "/usr/include/assert.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 364 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 385 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 386 "/usr/include/sys/cdefs.h" 2 3 4
# 365 "/usr/include/features.h" 2 3 4
# 388 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 389 "/usr/include/features.h" 2 3 4
# 36 "/usr/include/assert.h" 2 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 2 "logger2_por_seq.c" 2

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


uint8_t numberOfRecords;
uint16_t records[64];



uint32_t periodCounter;
uint16_t tickCounter;
uint16_t period;
uint32_t startTime;




uint8_t systemState;
# 34 "logger2_por_seq.c"
const int __CPROVER_thread_priorities[] = {2, 5, 1};
const char* __CPROVER_threads[] = {"c::task_communicate", "c::task_measure", "c::task_ext_power"};


void task_communicate(void);
void task_measure(void);
void task_ext_power(void);

extern _Bool __VERIFIER_nondet_bool();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}


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
schedule_irq();
  if (numberOfRecords+1 >= 64) {
schedule_irq();
    systemState = 0;
schedule_irq();
  }
schedule_irq();
  periodCounter = 0;
schedule_irq();
  tickCounter = 0;
schedule_irq();
  numberOfRecords = 0;
schedule_irq();
  startTime = _startTime;
schedule_irq();
  period = _period;
schedule_irq();
  systemState = 1;
schedule_irq();
}

extern uint16_t read_sensor_value();
extern uint16_t process_value(uint32_t time, uint16_t value);
void task_measure(void) {
disable_irq(0);
disable_irq(1);
disable_irq(2);

  __VERIFIER_assume(systemState==1);
  tickCounter++;

  if (tickCounter == period) {
    uint16_t value = read_sensor_value();
    uint8_t pos = numberOfRecords;
    uint32_t _startTime = startTime;
    uint32_t currentTime = _startTime + period*periodCounter+tickCounter;

    tickCounter = 0;
    periodCounter++;

    records[pos] = process_value(currentTime,value);
    numberOfRecords++;

    __VERIFIER_assert(numberOfRecords==pos+1);


  }
enable_irq(0);
enable_irq(1);
enable_irq(2);
}

extern uint8_t get_power_status();
void task_ext_power() {
disable_irq(1);
disable_irq(2);
enable_irq(0);

  uint8_t power = get_power_status();

schedule_irq();
  if(power && systemState==2) {
schedule_irq();
    systemState = 0;
schedule_irq();
  }

schedule_irq();
  if(!power && systemState==0) {
schedule_irq();
    systemState = 2;
schedule_irq();
  }

enable_irq(1);
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
uint8_t msgBuffer[16];
void task_communicate(void) {
disable_irq(0);
disable_irq(2);
enable_irq(1);

  __VERIFIER_assume(systemState!=2);
  uint8_t len = receive_cmd(msgBuffer);
  uint8_t cmd = msgBuffer[0];
  uint8_t decodingStatus = 0;
  if(cmd==2 || cmd==3 || cmd==4 ||
     cmd==1) {
    decodingStatus = 1;
  }
  if (decodingStatus != 1) {
    msgBuffer[0] = 0;
    send_response(msgBuffer,1);
  } else {
    uint8_t rspStatus = 1;
    switch(cmd) {
      case 2:
        if (systemState != 1) {
          rspStatus = 0;
        } else {
schedule_irq();
          systemState = 0;
schedule_irq();
        }
        msgBuffer[0] = rspStatus;
        if(systemState==2) {
          return;
        }
        send_response(msgBuffer,1);
        break;
      case 3:
        msgBuffer[0] = rspStatus;
        msgBuffer[1] = systemState;
schedule_irq();
        msgBuffer[2] = numberOfRecords;
        put_uint32(msgBuffer,3,startTime);
        if(systemState==2) {
          return;
        }
        send_response(msgBuffer,7);
 break;
      case 4: {
        uint8_t pos = msgBuffer[1];
schedule_irq();
        if(pos>=numberOfRecords) {
          msgBuffer[0] = 0;
          if(systemState==2) {
            return;
          }
          send_response(msgBuffer,1);
   } else {
          msgBuffer[0] = 1;
schedule_irq();
          put_uint16(msgBuffer,1,records[pos]);
          if(systemState==2) {
            return;
          }
          send_response(msgBuffer,3);
 }
 break;
      }
      case 1: {
        uint32_t _startTime = get_uint32(msgBuffer,1);
        uint16_t _period = get_uint16(msgBuffer,5);
        restart(_startTime,_period);
        msgBuffer[0] = rspStatus;
        if(systemState==2) {
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
enable_irq(2);
}


void initialize(void) {
  systemState = 2;
  periodCounter = 0;
  tickCounter = 0;
  startTime = 0;
  numberOfRecords = 0;
}

void run(void)
{

enable_irq(0);
enable_irq(1);
enable_irq(2);
schedule_irq();
# 325 "logger2_por_seq.c"
}

void main() {
    initialize();
    run();
}
