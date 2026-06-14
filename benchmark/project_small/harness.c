#include <assert.h>
#include "osek/osek_api.h"
#include "osek/osek_runtime_stub.h"
#include "common/lib_math.h"
#include "common/lib_mem.h"
#include "common/lib_utils.h"
#include "drivers/gpio_driver.h"
#include "drivers/timer_driver.h"
#include "middleware/data_filter.h"
#include "middleware/protocol_stack.h"
#include "isr_define/isr_timer.h"
#include "isr_define/isr_external.h"
#include "isr_define/isr_adc.h"
#include "isr_define/isr_uart.h"
#include "task_define/task.h"

int shared_value = 0;
int controller_done = 0;

extern void task_main_run(void);

/*
 * TODO: Test with aib, cmbc not interleaved, cbmc interleaved.
 */
int main() {
    init_osek_runtime();
    protocol_init();
    gpio_init(0, GPIO_MODE_OUTPUT);
    gpio_init(1, GPIO_MODE_OUTPUT);
    gpio_init(2, GPIO_MODE_OUTPUT);
    gpio_init(3, GPIO_MODE_OUTPUT);
    gpio_init(4, GPIO_MODE_OUTPUT);
    gpio_init(5, GPIO_MODE_OUTPUT);
    gpio_init(6, GPIO_MODE_OUTPUT);
    gpio_init(7, GPIO_MODE_OUTPUT);
    timer_init(0, 100);
    timer_init(1, 50);
    timer_init(2, 75);
    timer_init(3, 25);

    ActivateTask(TASK_ID_1);
    ActivateTask(TASK_ID_2);
    ActivateTask(TASK_ID_3);
    ActivateTask(TASK_ID_4);
    ActivateTask(TASK_ID_5);
    ActivateTask(TASK_ID_6);
    ActivateTask(TASK_ID_7);
    ActivateTask(TASK_ID_8);
    ActivateTask(TASK_ID_9);
    ActivateTask(TASK_ID_10);
    ActivateTask(TASK_ID_11);
    ActivateTask(TASK_ID_12);
    ActivateTask(TASK_ID_13);
    ActivateTask(TASK_ID_14);
    ActivateTask(TASK_ID_15);
    ActivateTask(TASK_ID_16);
    ActivateTask(TASK_ID_17);
    ActivateTask(TASK_ID_18);
    ActivateTask(TASK_ID_19);
    ActivateTask(TASK_ID_20);
    ActivateTask(TASK_ID_21);
    ActivateTask(TASK_ID_22);
    ActivateTask(TASK_ID_23);
    ActivateTask(TASK_ID_24);
    ActivateTask(TASK_ID_25);
    ActivateTask(TASK_ID_26);
    ActivateTask(TASK_ID_27);
    ActivateTask(TASK_ID_28);
    ActivateTask(TASK_ID_29);
    ActivateTask(TASK_ID_30);

    isr_timer_handler();
    isr_external_handler();
    isr_adc_handler();
    isr_uart_handler();

    assert(shared_value >= -100);

    return 0;
}