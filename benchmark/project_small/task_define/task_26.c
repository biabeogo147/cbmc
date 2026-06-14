#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/data_filter.h"
#include "../middleware/protocol_stack.h"
#include "task.h"

TASK(t26)
{
    int filtered = apply_recursive_filter(500, 5);
    assert(filtered >= 0);

    protocol_init();
    protocol_process(10);
    protocol_process(5);

    int val = kalman_filter(filtered, 100, 0.2f);
    assert(val >= 0);

    TerminateTask();
}