#include "gpio_driver.h"

static GPIO_State gpio_states[16] = {GPIO_STATE_LOW};

void gpio_init(int pin, GPIO_Mode mode) {
    if (pin >= 0 && pin < 16) {
        gpio_states[pin] = GPIO_STATE_LOW;
    }
}

void gpio_write(int pin, GPIO_State state) {
    if (pin >= 0 && pin < 16) {
        gpio_states[pin] = state;
    }
}

GPIO_State gpio_read(int pin) {
    if (pin >= 0 && pin < 16) {
        return gpio_states[pin];
    }
    return GPIO_STATE_LOW;
}

void gpio_toggle(int pin) {
    if (pin >= 0 && pin < 16) {
        gpio_states[pin] = (gpio_states[pin] == GPIO_STATE_LOW) ? GPIO_STATE_HIGH : GPIO_STATE_LOW;
    }
}