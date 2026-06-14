#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/data_filter.h"
#include "../common/lib_math.h"
#include "task.h"

TASK(t23)
{
    int val = kalman_filter(80, 40, 0.3f);
    assert(val == 52);

    int arr[6] = {1, 2, 3, 4, 5, 6};
    int avg = apply_moving_average(arr, 6, 3);
    assert(avg >= 0);

    TerminateTask();
}