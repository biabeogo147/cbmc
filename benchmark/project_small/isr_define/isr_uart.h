#ifndef ISR_UART_H
#define ISR_UART_H

#include <stdbool.h>

extern bool uart_irq_enabled;
extern char uart_buffer[64];

void isr_uart_handler(void);

#endif