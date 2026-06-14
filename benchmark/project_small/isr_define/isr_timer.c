#include "isr_timer.h"
#include "../osek/osek_api.h"
#include <stdbool.h>

extern int shared_value;
bool timer_irq_enabled = true;

void isr_timer_handler(void)
{
    __CPROVER_atomic_begin();
    if (timer_irq_enabled) {
        shared_value += 10;
        SetEvent(TASK_ID_4, EVENT_TIMER_EXP);
    }
    __CPROVER_atomic_end();
}
