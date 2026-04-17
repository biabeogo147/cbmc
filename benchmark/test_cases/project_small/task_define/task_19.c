#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/protocol_stack.h"
#include "../drivers/timer_driver.h"
#include "task.h"

TASK(t19)
{
    protocol_init();
    for (int i = 0; i < 10; i++) {
        protocol_process(i % 2);
    }

    timer_init(0, 50);
    timer_start(0);

    TerminateTask();
}