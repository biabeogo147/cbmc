#include <assert.h>

#ifndef NULL
#define NULL ((void*)0)
#endif

// isr1
// file check-src/t_isr.c line 8
void * isr1(void *arg);
// isr2
// file check-src/t_isr.c line 17
void * isr2(void *arg);
// task1
// file check-src/t_isr.c line 26
void task1(void);
// task2
// file check-src/t_isr.c line 30
void task2(void);

// enable_irq_1
// file check-src/t_isr.c line 4
_Bool enable_irq_1=1;
// enable_irq_2
// file check-src/t_isr.c line 5
_Bool enable_irq_2=1;
// x
// file check-src/t_isr.c line 6
signed int x=0;

// isr1
// file check-src/t_isr.c line 8
void * isr1(void *arg)
{
  __CPROVER_atomic_begin();
  if(!(enable_irq_1 == 0))
  {
    x = x + 1;
    enable_irq_1 = 0;
  }

  __CPROVER_atomic_end();
}

// isr2
// file check-src/t_isr.c line 17
void * isr2(void *arg)
{
  __CPROVER_atomic_begin();
  if(!(enable_irq_2 == 0))
  {
    x = x - 1;
    enable_irq_2 = 0;
  }

  __CPROVER_atomic_end();
}

// main
// file check-src/t_isr.c line 34
signed int main(void)
{
  task1();
  task2();
  (void)sizeof(signed int) /*4ul*/ ;
  /* assertion x == 5 */
  ;
  /* assertion x == 5 */
  if(nondet_0())
  {
    ;
    isr2(NULL);
  }

  /* assertion x == 5 */
  ;
  /* assertion x == 5 */
  ;
  /* assertion x == 5 */
  if(nondet_0())
  {
    ;
    isr1(NULL);
  }

  /* assertion x == 5 */
  ;
  /* assertion x == 5 */
  assert(x == 5);
  return 0;
}

// task1
// file check-src/t_isr.c line 26
void task1(void)
{
  if(nondet_0())
    isr2(NULL);

  if(nondet_0())
    isr1(NULL);

  x = x + 2;
}

// task2
// file check-src/t_isr.c line 30
void task2(void)
{
  if(nondet_0())
    isr2(NULL);

  if(nondet_0())
    isr1(NULL);

  x = x + 3;
}

