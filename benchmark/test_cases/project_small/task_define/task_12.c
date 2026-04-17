#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/protocol_stack.h"
#include "../common/lib_math.h"
#include "task.h"

TASK(t12)
{
    protocol_init();
    int counter = protocol_get_counter();
    assert(counter == 0);

    for (int i = 0; i < 5; i++) {
        protocol_process(i);
    }

    int fib = calc_fibonacci(7);
    assert(fib == 13);

    TerminateTask();
}