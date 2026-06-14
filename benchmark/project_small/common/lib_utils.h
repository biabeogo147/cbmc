#ifndef LIB_UTILS_H
#define LIB_UTILS_H

void init_system(void);
int get_system_tick(void);
void delay_ms(int ms);
char* copy_string(char* dest, const char* src, int max_len);
int compare_strings(const char* s1, const char* s2);

#endif