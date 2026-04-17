#ifndef PROTOCOL_STACK_H
#define PROTOCOL_STACK_H

typedef enum {
    S_IDLE,
    S_ACTIVE,
    S_PROCESSING,
    S_ERROR
} ProtoState;

void protocol_init(void);
void protocol_process(int input);
ProtoState protocol_get_state(void);
int protocol_get_counter(void);

#endif