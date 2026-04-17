#include "isr_uart.h"
#include "../osek/osek_api.h"
#include <stdbool.h>

extern int shared_value;
bool uart_irq_enabled = true;
char uart_buffer[64] = {0};
static int uart_buffer_idx = 0;

void isr_uart_handler(void) {
    __CPROVER_atomic_begin();
    if (uart_irq_enabled) {
        shared_value -= 2;
        if (uart_buffer_idx < 63) {
            uart_buffer[uart_buffer_idx] = 'A';
            uart_buffer_idx++;
        }
        SetEvent(TASK_ID_6, EVENT_WORK_DONE);
    }
    __CPROVER_atomic_end();
}