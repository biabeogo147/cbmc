#include <assert.h>
#include "../osek/osek_api.h"
#include "../drivers/gpio_driver.h"
#include "../middleware/protocol_stack.h"
#include "task.h"

TASK(t29)
{
    gpio_init(7, GPIO_MODE_OUTPUT);
    gpio_write(7, GPIO_STATE_HIGH);

    protocol_init();
    for (int i = 0; i < 4; i++) {
        protocol_process(i);
    }

    TerminateTask();
}