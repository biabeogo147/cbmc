#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../drivers/timer_driver.h"
#include "task.h"

TASK(t15)
{
    int arr[8] = {3, 1, 4, 1, 5, 9, 2, 6};
    int max = find_max_in_array(arr, 8);
    assert(max == 9);

    reverse_array(arr, 8);
    assert(arr[0] == 6);

    timer_init(3, 25);

    TerminateTask();
}