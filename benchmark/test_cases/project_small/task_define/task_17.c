#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/data_filter.h"
#include "../drivers/gpio_driver.h"
#include "task.h"

TASK(t17)
{
    int arr[4] = {5, 10, 15, 20};
    int avg = apply_moving_average(arr, 4, 2);
    assert(avg >= 0);

    gpio_init(4, GPIO_MODE_OUTPUT);
    gpio_toggle(4);

    TerminateTask();
}