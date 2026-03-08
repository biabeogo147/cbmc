#include <stdlib.h>

int main() {
    int *p = (int*)malloc(sizeof(int));
    *p = 1;
    free(p);

    // use-after-free
    *p = 2;

    return 0;
}
