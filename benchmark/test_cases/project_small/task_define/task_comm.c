#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/protocol_stack.h"
#include "task.h"

TASK(t3)
{
    // Communication task simulating a protocol state machine
    for (int i = 0; i < 5; i++) {
        int input = 0;
        #ifdef __CPROVER_HAVE_NONDET_INT
        input = nondet_int();
        #endif

        protocol_process(input);
        ProtoState s = protocol_get_state();
        assert(s != S_ERROR || input == -1);
    }
    TerminateTask();
}
