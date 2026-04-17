#include "lib_utils.h"
#include <stddef.h>
#include <string.h>

static int system_tick = 0;

void init_system(void) {
    system_tick = 0;
}

int get_system_tick(void) {
    return system_tick++;
}

void delay_ms(int ms) {
    for (volatile int i = 0; i < ms; i++) {}
}

char* copy_string(char* dest, const char* src, int max_len) {
    if (dest == NULL || src == NULL || max_len <= 0) return dest;
    int i = 0;
    while (i < max_len - 1 && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int compare_strings(const char* s1, const char* s2) {
    if (s1 == NULL && s2 == NULL) return 0;
    if (s1 == NULL) return -1;
    if (s2 == NULL) return 1;
    while (*s1 && *s2 && *s1 == *s2) {
        s1++;
        s2++;
    }
    return *s1 - *s2;
}