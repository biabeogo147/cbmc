#include "osek_api.h"
#include <stdbool.h>
#include <stddef.h>

typedef enum {
    STATE_SUSPENDED,
    STATE_READY,
    STATE_RUNNING,
    STATE_WAITING
} TaskState;

typedef struct {
    task_idt id;
    TaskState state;
    unsigned int priority;
    EventMaskType events;
} TCB;

#define MAX_TASKS 10
static TCB task_table[MAX_TASKS];
static task_idt current_task_id = 0;

void init_osek_runtime(void) {
    for (int i = 0; i < MAX_TASKS; i++) {
        task_table[i].id = (task_idt)i;
        task_table[i].state = STATE_SUSPENDED;
        task_table[i].events = 0;
    }
}

void ActivateTask(task_idt task_id) {
    if (task_id < MAX_TASKS) {
        task_table[task_id].state = STATE_READY;
    }
}

void TerminateTask(void) {
    if (current_task_id < MAX_TASKS) {
        task_table[current_task_id].state = STATE_SUSPENDED;
    }
}

void SetEvent(task_idt task_id, EventMaskType mask) {
    if (task_id < MAX_TASKS) {
        task_table[task_id].events |= mask;
        if (task_table[task_id].state == STATE_WAITING) {
            task_table[task_id].state = STATE_READY;
        }
    }
}

void ClearEvent(EventMaskType mask) {
    if (current_task_id < MAX_TASKS) {
        task_table[current_task_id].events &= ~mask;
    }
}

void GetEvent(task_idt task_id, EventMaskRefType event) {
    if (task_id < MAX_TASKS && event != NULL) {
        *event = task_table[task_id].events;
    }
}

void WaitEvent(EventMaskType mask) {
    if (current_task_id < MAX_TASKS) {
        // Simplified: wait until the mask is satisfied
        while ((task_table[current_task_id].events & mask) == 0) {
            task_table[current_task_id].state = STATE_WAITING;
            // In a real OS, a scheduler would switch here.
            // For CBMC, we allow the model checker to explore interleavings.
        }
    }
}

void boot_autostart_task(void) {
    init_osek_runtime();
    ActivateTask(TASK_ID_1);
}
