#include <assert.h>

// ESBMC intrinsics
extern unsigned int __ESBMC_activation_task(const char *task_id, void (*func)(void));

int x = 0;

void task_1(void)
{
    assert(x==1);
    x = 1;
}

void task_2(void)
{
    assert(x==0);
    x = 1;
    __ESBMC_activation_task("taskB", task_1);
    x = 2;
}

int main(void)
{
    __ESBMC_activation_task("taskA", task_2);
    return 0;
}
