#include <assert.h>
#include "../osek/osek_api.h"
#include "../drivers/gpio_driver.h"
#include "../drivers/timer_driver.h"
#include "task.h"

TASK(t21)
{
    gpio_init(5, GPIO_MODE_OUTPUT);
    timer_init(1, 30);

    for (int i = 0; i < 3; i++) {
        gpio_toggle(5);
        timer_start(1);
    }

    TerminateTask();
}