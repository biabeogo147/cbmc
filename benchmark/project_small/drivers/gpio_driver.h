#ifndef GPIO_DRIVER_H
#define GPIO_DRIVER_H

typedef enum {
    GPIO_MODE_INPUT,
    GPIO_MODE_OUTPUT,
    GPIO_MODE_ALTERNATE
} GPIO_Mode;

typedef enum {
    GPIO_STATE_LOW,
    GPIO_STATE_HIGH
} GPIO_State;

void gpio_init(int pin, GPIO_Mode mode);
void gpio_write(int pin, GPIO_State state);
GPIO_State gpio_read(int pin);
void gpio_toggle(int pin);

#endif