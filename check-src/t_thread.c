#include <pthread.h>
#include <assert.h>

static int x = 0;

void* t1(void* arg) {
    x = 1;              // write 1
    return 0;
}

void* t2(void* arg) {
    x = 2;              // write 2
    return 0;
}

int main(void) {
    pthread_t a, b;

    pthread_create(&a, 0, t1, 0);
    pthread_create(&b, 0, t2, 0);

    // Wait for both threads
    pthread_join(a, 0);
    pthread_join(b, 0);

    // Because writes race, final x can be 1 or 2 depending on schedule.
    // This assertion is NOT always true -> ESBMC should find a counterexample.
    assert(x == 1);

    return 0;
}
