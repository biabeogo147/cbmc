#include <assert.h>
#include <stddef.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../common/lib_utils.h"
#include "../middleware/data_filter.h"
#include "task.h"

int data_buffer[10] = {0};
int buffer_idx = 0;

TASK(t7)
{
    init_system();

    Node* list = create_list(5);
    if (list != NULL) {
        int sum = find_sum_recursive(list, 5);
        assert(sum >= 0);
        destroy_list(list);
    }

    for (int i = 0; i < 10; i++) {
        data_buffer[i] = get_system_tick() + i;
    }

    int max = find_max_in_array(data_buffer, 10);
    assert(max >= 0);

    int filtered = apply_moving_average(data_buffer, 10, 3);
    assert(filtered >= 0);

    TerminateTask();
}