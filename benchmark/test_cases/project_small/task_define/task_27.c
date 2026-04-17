#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../drivers/timer_driver.h"
#include "task.h"

TASK(t27)
{
    int fib = calc_fibonacci(8);
    assert(fib == 21);

    int fact = calc_factorial(6);
    assert(fact == 720);

    timer_init(2, 100);

    TerminateTask();
}