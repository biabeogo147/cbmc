#include <stdio.h>

// ESBMC intrinsics
extern unsigned int __ESBMC_activation_task(const char *task_id, void (*func)(void));
extern void __ESBMC_yield(void);

// Shared functions that will be called by different tasks
void function_A(void)
{
    printf("Function A executing\n");
    __ESBMC_yield();
}

void function_B(void)
{
    printf("Function B executing\n");
    __ESBMC_yield();
}

void function_C(void)
{
    printf("Function C executing\n");
    __ESBMC_yield();
}

void function_D(void)
{
    printf("Function D executing\n");
    __ESBMC_yield();
}

// TaskA entry point (priority 10) - calls A, B, D
void taskA_entry(void)
{
    printf("TaskA starting (high priority)\n");
    function_A();  // Should run with priority 10
    function_B();  // Should run with priority 10
    function_D();  // Should run with priority 10
    printf("TaskA finishing\n");
}

// TaskB entry point (priority 5) - calls A, B, C
void taskB_entry(void)
{
    printf("TaskB starting (low priority)\n");
    function_A();  // Should run with priority 5
    function_B();  // Should run with priority 5
    function_C();  // Should run with priority 5
    printf("TaskB finishing\n");
}

int main(void)
{
    printf("Main thread starting\n");
    
    // Create TaskA with high priority (10)
    unsigned int tid1 = __ESBMC_activation_task("taskA", taskA_entry);
    printf("Created taskA with thread ID: %u\n", tid1);
    
    // Create TaskB with low priority (5)
    unsigned int tid2 = __ESBMC_activation_task("taskB", taskB_entry);
    printf("Created taskB with thread ID: %u\n", tid2);
    
    printf("Main thread finishing\n");
    return 0;
}

// Expected behavior with strict priority scheduling:
// 1. Main thread creates both tasks
// 2. TaskA (priority 10) should run completely before TaskB (priority 5)
// 3. All function calls within TaskA should inherit priority 10
// 4. All function calls within TaskB should inherit priority 5
// 5. Even though both tasks call the same functions (A, B), 
//    the scheduler should prioritize based on the task priority, not function name
