#ifndef ISR_ADC_H
#define ISR_ADC_H

#include <stdbool.h>

extern bool adc_irq_enabled;
extern int adc_value;

void isr_adc_handler(void);

#endif