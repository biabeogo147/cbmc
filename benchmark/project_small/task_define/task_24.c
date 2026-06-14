#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../drivers/gpio_driver.h"
#include "task.h"

TASK(t24)
{
    int arr[5] = {25, 10, 30, 5, 15};
    int max = find_max_in_array(arr, 5);
    assert(max == 30);

    reverse_array(arr, 5);
    assert(arr[4] == 25);

    gpio_init(6, GPIO_MODE_OUTPUT);

    TerminateTask();
}