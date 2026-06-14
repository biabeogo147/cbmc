#include "isr_adc.h"
#include "../osek/osek_api.h"
#include <stdbool.h>

extern int shared_value;
bool adc_irq_enabled = true;
int adc_value = 0;

void isr_adc_handler(void) {
    __CPROVER_atomic_begin();
    if (adc_irq_enabled) {
        adc_value += 1;
        shared_value += 3;
        SetEvent(TASK_ID_5, EVENT_DATA_READY);
    }
    __CPROVER_atomic_end();
}