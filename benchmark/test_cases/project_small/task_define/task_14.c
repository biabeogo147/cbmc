#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../middleware/data_filter.h"
#include "task.h"

TASK(t14)
{
    int arr[5] = {10, 20, 30, 40, 50};
    float avg = calc_average(arr, 5);
    assert(avg > 0);

    int filtered = kalman_filter(100, 50, 0.5f);
    assert(filtered == 75);

    TerminateTask();
}