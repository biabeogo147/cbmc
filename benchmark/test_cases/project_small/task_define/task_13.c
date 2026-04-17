#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_utils.h"
#include "../drivers/gpio_driver.h"
#include "task.h"

TASK(t13)
{
    char dest[32] = {0};
    copy_string(dest, "Hello OSEK", 32);
    int cmp = compare_strings(dest, "Hello OSEK");
    assert(cmp == 0);

    gpio_init(3, GPIO_MODE_OUTPUT);

    TerminateTask();
}