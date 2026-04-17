#ifndef DATA_FILTER_H
#define DATA_FILTER_H

int apply_recursive_filter(int value, int depth);
int apply_moving_average(int* values, int count, int window_size);
int kalman_filter(int measurement, int prev_estimate, float gain);

#endif