# 1 "logger_bug_por_seq.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "logger_bug_por_seq.c"
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



# 2 "logger_bug_por_seq.c" 2

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;


uint16_t numberOfRecords;
uint16_t records[64];


uint8_t msgBuffer[64];

uint32_t intervalCounter;
uint16_t tickCounter;
uint16_t interval;
uint32_t startTime;



uint8_t systemState;
# 37 "logger_bug_por_seq.c"
const int __CPROVER_thread_priorities[] = {5, 22};
const char* __CPROVER_threads[] = {"c::task_communicate", "c::task_measure"};


void task_communicate(void);
void task_measure(void);

extern _Bool __VERIFIER_nondet_bool();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}


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
  systemState = 0;
}

inline void start(uint32_t _startTime,uint16_t _interval)
{
schedule_irq();
  if (numberOfRecords+1 >= 64) {
    stop();
  }
schedule_irq();
  intervalCounter = 0;
schedule_irq();
  tickCounter = 0;
schedule_irq();
  numberOfRecords = 0;
schedule_irq();
  startTime = _startTime;
schedule_irq();
  interval = _interval;
schedule_irq();
  systemState = 1;
schedule_irq();
  __VERIFIER_assert(numberOfRecords==0);


}

extern uint16_t read_sensor_value();
void task_measure(void)
{
disable_irq(0);
disable_irq(1);

  tickCounter++;

  if (tickCounter == interval) {
    uint16_t value = read_sensor_value();

    tickCounter = 0;
    intervalCounter++;

    records[numberOfRecords] = value;
    numberOfRecords++;
  }
enable_irq(0);
enable_irq(1);
}

extern uint8_t read_cmd();
uint8_t get_cmd(uint8_t* decodingStatus) {
  uint8_t cmd = read_cmd();
  *decodingStatus = 0;
  if(cmd==2 || cmd==3 || cmd==4 ||
     cmd==1) {
    *decodingStatus = 1;
  }
  return cmd;
}

extern uint16_t get_uint16();
extern uint32_t get_uint32();
extern void send_response();
void task_communicate(void)
{
disable_irq(0);
enable_irq(1);

  uint8_t decodingStatus;
  uint8_t cmd = get_cmd(&decodingStatus);
  uint8_t rspStatus = 1;

  if (decodingStatus != 1) {
    rspStatus = 0;
  }
  if (rspStatus == 1) {
    switch(cmd) {
      case 2:
        if (systemState != 1) {
          rspStatus = 0;
        } else {
          stop();
        }
        send_response();
        break;
      case 3:
        send_response();
 break;
      case 4:
        send_response();
 break;
      case 1:
        if (systemState != 0) {
          rspStatus = 0;
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
}


void initialize(void) {
  systemState = 0;
}

void run(void)
{

enable_irq(0);
enable_irq(1);
schedule_irq();
# 236 "logger_bug_por_seq.c"
}

void main() {
    initialize();
    run();
}
