#include "isr_external.h"
#include "../osek/osek_api.h"
#include <stdbool.h>

extern int shared_value;
bool ext_irq_enabled = true;

void isr_external_handler(void)
{
    __CPROVER_atomic_begin();
    if (ext_irq_enabled) {
        shared_value -= 5;
        SetEvent(TASK_ID_3, EVENT_DATA_READY);
    }
    __CPROVER_atomic_end();
}
