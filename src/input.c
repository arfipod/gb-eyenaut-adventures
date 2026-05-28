#include <gb/gb.h>
#include "input.h"

void input_update(InputState *input)
{
    input->previous = input->current;
    input->current = joypad();
    input->pressed = (uint8_t)(input->current & (uint8_t)~input->previous);
}
