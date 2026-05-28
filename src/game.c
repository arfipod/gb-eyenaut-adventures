#include <gb/gb.h>
#include "camera.h"
#include "chunk.h"
#include "game.h"
#include "input.h"
#include "player.h"
#include "render.h"
#include "world.h"

static InputState input;
static Player player;
static Camera camera;

void game_init(void)
{
    input.current = 0u;
    input.previous = 0u;
    input.pressed = 0u;

    world_init();
    player_init(&player);
    camera.x = 0u;
    camera.y = 0u;

    render_init();

    /* TODO: add save data after the world representation is stable. */
    /* TODO: fake lighting with tile variants or coarse palettes on CGB later. */
}

void game_update(void)
{
    input_update(&input);
    player_update(&player, &input);
    camera_update(&camera, &player);
    chunk_tick();
    render_world();
    render_frame(&camera, &player);
}
