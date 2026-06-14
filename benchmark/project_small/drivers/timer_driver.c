#include "timer_driver.h"
#include <stddef.h>

static int timer_values[4] = {0};
static int timer_periods[4] = {0};
static void (*timer_callbacks[4])(void) = {NULL};

void timer_init(int timer_id, int period_ms) {
    if (timer_id >= 0 && timer_id < 4) {
        timer_values[timer_id] = 0;
        timer_periods[timer_id] = period_ms;
    }
}

void timer_start(int timer_id) {
    if (timer_id >= 0 && timer_id < 4) {
        timer_values[timer_id] = 0;
    }
}

void timer_stop(int timer_id) {
    if (timer_id >= 0 && timer_id < 4) {
        timer_values[timer_id] = 0;
    }
}

int timer_get_value(int timer_id) {
    if (timer_id >= 0 && timer_id < 4) {
        return timer_values[timer_id];
    }
    return 0;
}

void timer_set_callback(int timer_id, void (*callback)(void)) {
    if (timer_id >= 0 && timer_id < 4) {
        timer_callbacks[timer_id] = callback;
    }
}