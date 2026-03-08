#include <stdio.h>

// ESBMC intrinsics
extern unsigned int __ESBMC_spawn_thread(void (*func)(void));
extern void __ESBMC_yield(void);

void thread_A(void)
{
    printf("Thread A executing\n");
    __ESBMC_yield();
    printf("Thread A continuing\n");
    __ESBMC_yield();
    printf("Thread A finishing\n");
}

void thread_B(void)
{
    printf("Thread B executing\n");
    __ESBMC_yield();
    printf("Thread B continuing\n");
    __ESBMC_yield();
    printf("Thread B finishing\n");
}

int main(void)
{
    printf("Main thread starting\n");
    
    // Use original spawn_thread (not activation_task)
    // This should use original ESBMC scheduler when no --task-priority-json
    unsigned int tid1 = __ESBMC_spawn_thread(thread_A);
    printf("Created thread A with ID: %u\n", tid1);
    
    unsigned int tid2 = __ESBMC_spawn_thread(thread_B);
    printf("Created thread B with ID: %u\n", tid2);
    
    printf("Main thread finishing\n");
    return 0;
}

// Expected behavior:
// WITHOUT --task-priority-json: Should use original ESBMC round-robin scheduler
// WITH --task-priority-json: Should still work but threads have priority 0 (default)
