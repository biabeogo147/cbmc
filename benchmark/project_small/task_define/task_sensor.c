#include <assert.h>
#include "../osek/osek_api.h"
#include "../common/lib_mem.h"
#include "../middleware/data_filter.h"
#include "../drivers/gpio_driver.h"
#include "task.h"

int sensor_data = 0;
int processed_output = 0;

TASK(t5)
{
    sensor_data = 100;

    int filtered = apply_recursive_filter(sensor_data, 3);

    gpio_init(0, GPIO_MODE_OUTPUT);
    gpio_write(0, GPIO_STATE_HIGH);

    assert(filtered > 0);
    processed_output = filtered;

    TerminateTask();
}