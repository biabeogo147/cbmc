#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../middleware/data_filter.h"
#include "task.h"

int shared_value = 0;
int controller_done = 0;

TASK(t1)
{
    EventMaskType snapshot = 0;

    ActivateTask(TASK_ID_2);
    WaitEvent(EVENT_WORK_DONE);
    GetEvent(TASK_ID_1, &snapshot);
    assert((snapshot & EVENT_WORK_DONE) != 0u);
    ClearEvent(EVENT_WORK_DONE);

    assert(shared_value == 2);

    // Test recursive filter
    int filtered = apply_recursive_filter(100, 5);
    assert(filtered > 0);

    controller_done = 1;
    TerminateTask();
}

TASK(t2)
{
    assert(controller_done == 0);
    shared_value = 2;
    SetEvent(TASK_ID_1, EVENT_WORK_DONE);
    TerminateTask();
}
