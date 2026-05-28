#include <gb/gb.h>
#include "camera.h"
#include "chunk.h"
#include "game.h"
#include "input.h"
#include "inventory.h"
#include "player.h"
#include "render.h"
#include "world.h"

static InputState input;
static Player player;
static Camera camera;
static Inventory inventory;
static uint8_t menu_open;

static bool player_near_workbench(void)
{
    return world_has_tile_near_pixel((int16_t)(player.x + (PLAYER_WIDTH / 2)),
                                     (int16_t)(player.y + (PLAYER_HEIGHT / 2)),
                                     TILE_WORKBENCH,
                                     2u);
}

void game_init(void)
{
    input.current = 0u;
    input.previous = 0u;
    input.pressed = 0u;

    world_init();
    inventory_init(&inventory);
    player_init(&player);
    camera.x = 0u;
    camera.y = 0u;
    menu_open = 0u;

    render_init();
    render_hud(&inventory);

    /* TODO: add save data after the world representation is stable. */
    /* TODO: fake lighting with tile variants or coarse palettes on CGB later. */
}

void game_update(void)
{
    bool near_workbench;

    input_update(&input);

    if (input.pressed & J_SELECT) {
        menu_open = (uint8_t)!menu_open;
    }

    near_workbench = player_near_workbench();

    if (menu_open) {
        if ((input.pressed & J_RIGHT) || (input.pressed & J_DOWN)) {
            inventory_next_recipe(&inventory);
        }

        if ((input.pressed & J_LEFT) || (input.pressed & J_UP)) {
            inventory_prev_recipe(&inventory);
        }

        if (input.pressed & J_A) {
            inventory_craft_selected(&inventory, near_workbench);
        }

        if (input.pressed & J_B) {
            menu_open = 0u;
        }

        render_menu(&inventory, near_workbench);
        render_frame(&camera, &player);
        return;
    }

    player_update(&player, &input, &inventory);
    camera_update(&camera, &player);
    chunk_tick(camera.x);
    render_world(&camera);
    render_hud(&inventory);
    render_frame(&camera, &player);
}
