#include "lib_math.h"

int calc_fibonacci(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int calc_factorial(int n) {
    if (n <= 1) return 1;
    int result = 1;
    for (int i = 2; i <= n; i++) {
        result *= i;
    }
    return result;
}

float calc_average(int* values, int count) {
    if (count <= 0) return 0.0f;
    long sum = 0;
    for (int i = 0; i < count; i++) {
        sum += values[i];
    }
    return (float)sum / count;
}

int calc_max(int a, int b) {
    return a > b ? a : b;
}

int calc_min(int a, int b) {
    return a < b ? a : b;
}