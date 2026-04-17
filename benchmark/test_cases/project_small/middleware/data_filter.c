#include "data_filter.h"
#include <stddef.h>

int apply_recursive_filter(int value, int depth) {
    if (depth <= 0) return value;
    int result = value;
    for (int i = 0; i < depth; i++) {
        result = (result * 3) / 4;
    }
    return result;
}

int apply_moving_average(int* values, int count, int window_size) {
    if (values == NULL || count <= 0 || window_size <= 0) return 0;
    int sum = 0;
    int actual_window = (window_size < count) ? window_size : count;
    for (int i = 0; i < actual_window; i++) {
        sum += values[i];
    }
    return sum / actual_window;
}

int kalman_filter(int measurement, int prev_estimate, float gain) {
    return (int)((1.0f - gain) * prev_estimate + gain * measurement);
}