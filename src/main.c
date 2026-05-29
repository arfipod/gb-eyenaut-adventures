#include <gb/gb.h>
#include "game.h"
#include "splash.h"

void main(void)
{
    SplashChoice splash_choice = splash_show();
    (void)splash_choice;

    game_init();

    while (1) {
        game_update_logic();
        wait_vbl_done();
        game_render_commit();
    }
}
