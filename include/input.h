#ifndef INPUT_H
#define INPUT_H

#include <stdint.h>

typedef struct InputState {
    uint8_t current;
    uint8_t previous;
    uint8_t pressed;
} InputState;

void input_update(InputState *input);

#endif
