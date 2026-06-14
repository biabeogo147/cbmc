#include <assert.h>
#include <stddef.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../middleware/data_filter.h"
#include "task.h"

/*
 * BUG: Time-of-Check to Time-of-Use (TOCTOU) Race Condition
 *
 * This bug demonstrates a classic concurrency issue where a task reads
 * a shared variable, makes a decision based on that value, and then
 * acts on that decision - but the value could change between the check
 * and the use if an ISR fires.
 *
 * Race scenario detected by CBMC with interleaving:
 * 1. Task t1 reads shared_value (currently 0)
 * 2. ISR fires and modifies shared_value (adds 10)
 * 3. Task t1 continues with stale value and fails assertion
 *
 * How CBMC detects this:
 * - CBMC's interleaving analysis explores all possible execution orders
 * - When isr_timer_handler is in the interleaving-source-files, CBMC
 *   allows it to execute at any point during task execution
 * - The assertion will fail in paths where ISR fires between t1's read and check
 */

int shared_value = 0;
int controller_done = 0;

TASK(t1)
{
    /* Step 1: Read shared_value into local variable */
    int local_copy = shared_value;

    /* Step 2: Activate t2 which will set shared_value = 2 */
    ActivateTask(TASK_ID_2);
    WaitEvent(EVENT_WORK_DONE);
    GetEvent(TASK_ID_1, NULL);

    /*
     * Step 3: Check - but ISR could have fired between step 1 and here
     *
     * BUG: If ISR fired, shared_value is now 10 or -5 or -2, not the 0 we read
     * The check below assumes shared_value hasn't changed, but it may have
     *
     * With interleaving enabled, CBMC will explore:
     * - t1 reads shared_value (0)
     * - isr_timer_handler fires: shared_value becomes 10
     * - t1 asserts shared_value == 0 -> FAILS!
     */
    assert(shared_value == local_copy);  /* FAILS if ISR modified shared_value */

    /* Additional safety check - this should also fail in buggy interleavings */
    assert(shared_value >= 0);

    ClearEvent(EVENT_WORK_DONE);

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