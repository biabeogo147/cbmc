#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../drivers/gpio_driver.h"
#include "../drivers/timer_driver.h"
#include "task.h"

int gpio_toggle_count = 0;

TASK(t8)
{
    gpio_init(1, GPIO_MODE_OUTPUT);
    timer_init(1, 50);

    for (int i = 0; i < 5; i++) {
        gpio_toggle(1);
        gpio_toggle_count++;
        timer_start(1);
    }

    int max = calc_max(gpio_toggle_count, 10);
    assert(max >= 5);

    TerminateTask();
}