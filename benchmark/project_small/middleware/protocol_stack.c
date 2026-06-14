#include "protocol_stack.h"

static ProtoState current_state = S_IDLE;
static int protocol_counter = 0;

void protocol_init(void) {
    current_state = S_IDLE;
    protocol_counter = 0;
}

void protocol_process(int input) {
    switch (current_state) {
        case S_IDLE:
            if (input >= 0) {
                current_state = S_ACTIVE;
                protocol_counter++;
            } else {
                current_state = S_ERROR;
            }
            break;
        case S_ACTIVE:
            if (input >= 0) {
                current_state = S_PROCESSING;
                protocol_counter++;
            } else {
                current_state = S_ERROR;
            }
            break;
        case S_PROCESSING:
            if (input >= 0) {
                protocol_counter++;
            } else {
                current_state = S_ERROR;
            }
            break;
        case S_ERROR:
            break;
    }
}

ProtoState protocol_get_state(void) {
    return current_state;
}

int protocol_get_counter(void) {
    return protocol_counter;
}