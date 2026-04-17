#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_math.h"
#include "../middleware/protocol_stack.h"
#include "../drivers/timer_driver.h"
#include "task.h"

int comm_counter = 0;

TASK(t6)
{
    protocol_init();
    timer_init(0, 100);

    for (int i = 0; i < 3; i++) {
        int fib = calc_fibonacci(i + 2);
        protocol_process(fib);
        comm_counter++;
    }

    timer_start(0);
    assert(comm_counter >= 0);

    TerminateTask();
}