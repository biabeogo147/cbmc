#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../common/lib_utils.h"
#include "task.h"

TASK(t28)
{
    Node* list = create_list(4);
    int sum = 0;
    if (list) {
        sum = find_sum_recursive(list, 4);
        destroy_list(list);
    }
    assert(sum >= 0);

    init_system();
    delay_ms(5);

    TerminateTask();
}