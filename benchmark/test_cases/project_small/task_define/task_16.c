#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_utils.h"
#include "../middleware/protocol_stack.h"
#include "task.h"

TASK(t16)
{
    init_system();

    for (int i = 0; i < 20; i++) {
        get_system_tick();
    }

    protocol_init();
    protocol_process(5);

    TerminateTask();
}