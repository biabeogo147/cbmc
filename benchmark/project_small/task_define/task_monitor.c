#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "task.h"

TASK(t4)
{
    // Deep loop testing
    int sum = 0;
    for (int i = 0; i < 20; i++) {
        int choice = 0;
        #ifdef __CPROVER_HAVE_NONDET_INT
        choice = nondet_int();
        #endif

        if (choice == 0) {
            sum += i;
        } else if (choice == 1) {
            for (int j = 0; j < 5; j++) {
                sum += j;
            }
        } else {
            break;
        }
    }
    assert(sum >= 0);

    // Test recursive memory search
    Node* list = create_list(10);
    if (list) {
        int total = find_sum_recursive(list, 10);
        assert(total >= 0);
        destroy_list(list);
    }

    TerminateTask();
}
