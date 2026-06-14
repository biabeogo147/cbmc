#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../common/lib_utils.h"
#include "task.h"

TASK(t18)
{
    int max = calc_max(100, 200);
    assert(max == 200);

    int min = calc_min(100, 200);
    assert(min == 100);

    int fact = calc_factorial(5);
    assert(fact == 120);

    TerminateTask();
}