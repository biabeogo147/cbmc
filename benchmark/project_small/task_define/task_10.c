#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../common/lib_utils.h"
#include "task.h"

TASK(t10)
{
    Node* node = create_list(7);
    if (node) {
        int sum = find_sum_recursive(node, 7);
        assert(sum >= 0);
        destroy_list(node);
    }

    init_system();
    int tick = get_system_tick();
    assert(tick >= 0);

    TerminateTask();
}