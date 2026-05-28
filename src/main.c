#include <gb/gb.h>
#include "game.h"
#include "splash.h"

void main(void)
{
    splash_show();
    game_init();

    while (1) {
        game_update();
        vsync();
    }
}
