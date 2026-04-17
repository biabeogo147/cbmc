#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../drivers/gpio_driver.h"
#include "task.h"

TASK(t9)
{
    int fib = calc_fibonacci(10);
    assert(fib == 55);

    gpio_init(2, GPIO_MODE_OUTPUT);
    gpio_write(2, GPIO_STATE_HIGH);

    TerminateTask();
}