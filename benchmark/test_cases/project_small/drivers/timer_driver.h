#ifndef TIMER_DRIVER_H
#define TIMER_DRIVER_H

void timer_init(int timer_id, int period_ms);
void timer_start(int timer_id);
void timer_stop(int timer_id);
int timer_get_value(int timer_id);
void timer_set_callback(int timer_id, void (*callback)(void));

#endif