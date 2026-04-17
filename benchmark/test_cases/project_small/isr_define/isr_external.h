#ifndef ISR_EXTERNAL_H
#define ISR_EXTERNAL_H

#include <stdbool.h>

extern bool ext_irq_enabled;
extern int shared_value;

void isr_external_handler(void);

#endif