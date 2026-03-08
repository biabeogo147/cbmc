#include <limits.h>
#include <assert.h>

//esbmc t_overflow.c --overflow-check

int main() {
    int x = INT_MAX;
    int y = x + 1;          // signed overflow (undefined behavior)
    (void)y;
    return 0;
}
