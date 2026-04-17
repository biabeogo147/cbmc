#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/data_filter.h"
#include "../drivers/timer_driver.h"
#include "task.h"

TASK(t11)
{
    int filtered = apply_recursive_filter(1000, 10);
    assert(filtered >= 0);

    timer_init(2, 75);
    timer_start(2);

    int val = timer_get_value(2);
    assert(val >= 0);

    TerminateTask();
}