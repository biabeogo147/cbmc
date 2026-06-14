#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_utils.h"
#include "../common/lib_math.h"
#include "../middleware/data_filter.h"
#include "task.h"

TASK(t30)
{
    init_system();
    int tick = get_system_tick();
    assert(tick >= 0);

    int fib = calc_fibonacci(5);
    assert(fib == 5);

    int filtered = kalman_filter(200, 100, 0.4f);
    assert(filtered >= 0);

    char dest[20] = {0};
    copy_string(dest, "Final Task", 20);
    int cmp = compare_strings(dest, "Final Task");
    assert(cmp == 0);

    TerminateTask();
}