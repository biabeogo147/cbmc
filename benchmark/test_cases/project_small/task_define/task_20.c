#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../middleware/data_filter.h"
#include "task.h"

TASK(t20)
{
    Node* list = create_list(8);
    int sum = 0;
    if (list) {
        sum = find_sum_recursive(list, 8);
        destroy_list(list);
    }
    assert(sum >= 0);

    int filtered = apply_recursive_filter(sum, 2);
    assert(filtered >= 0);

    TerminateTask();
}