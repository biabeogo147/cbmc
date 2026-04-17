#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_utils.h"
#include "../common/lib_math.h"
#include "task.h"

TASK(t22)
{
    init_system();
    int tick1 = get_system_tick();
    int tick2 = get_system_tick();
    assert(tick2 > tick1);

    int fib = calc_fibonacci(12);
    assert(fib == 144);

    TerminateTask();
}