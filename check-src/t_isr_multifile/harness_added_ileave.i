extern _Bool enable_irq_1;
extern _Bool enable_irq_2;
extern int x;
void *isr1(void *arg);
void *isr2(void *arg);
_Bool enable_irq_1 = 1;
_Bool enable_irq_2 = 1;
int x = 0;
void *isr1(void *arg) {
  (void)arg;
  __CPROVER_atomic_begin();
  if (enable_irq_1) {
    ++x;
    enable_irq_1 = 0;
  }
  __CPROVER_atomic_end();
  return 0;
}
void *isr2(void *arg) {
  (void)arg;
  __CPROVER_atomic_begin();
  if (enable_irq_2) {
    --x;
    enable_irq_2 = 0;
  }
  __CPROVER_atomic_end();
  return 0;
}
void task1(void);
void task2(void);
void task1(void) {
  if (nondet_bool()) isr1(0);
  if (nondet_bool()) isr2(0);
  x += 2;
}
void task2(void) {
  if (nondet_bool()) isr1(0);
  if (nondet_bool()) isr2(0);
  x += 3;
}

extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));
extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));
extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));

int main(void) {
  task1();
  task2();
  if (nondet_bool()) isr1(0);
  if (nondet_bool()) isr2(0);
  ((void) sizeof ((x == 5) ? 1 : 0), __extension__ ({ if (x == 5) ; else __assert_fail ("x == 5", "harness.c", 10, __extension__ __PRETTY_FUNCTION__); }));
  return 0;
}
