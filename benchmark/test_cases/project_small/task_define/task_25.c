#include <assert.h>
#include "../osek/osek_api.h"
#include "../middleware/protocol_stack.h"
#include "../common/lib_utils.h"
#include "task.h"

TASK(t25)
{
    protocol_init();
    assert(protocol_get_state() == S_IDLE);

    protocol_process(1);
    assert(protocol_get_state() != S_ERROR);

    char s1[10] = "test";
    char s2[10] = "test";
    int cmp = compare_strings(s1, s2);
    assert(cmp == 0);

    TerminateTask();
}