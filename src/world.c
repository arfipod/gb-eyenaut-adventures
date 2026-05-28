#include "world.h"
#include "tile_defs.h"

static uint8_t tiles[WORLD_WIDTH_TILES * WORLD_HEIGHT_TILES];

void world_init(void)
{
    uint8_t x;
    uint8_t y;

    for (y = 0u; y < WORLD_HEIGHT_TILES; ++y) {
        for (x = 0u; x < WORLD_WIDTH_TILES; ++x) {
            if (y == 13u) {
                world_set_tile(x, y, TILE_GRASS);
            } else if (y > 13u && y < 17u) {
                world_set_tile(x, y, TILE_DIRT);
            } else if (y == 17u) {
                world_set_tile(x, y, TILE_STONE);
            } else {
                world_set_tile(x, y, TILE_EMPTY);
            }
        }
    }

    /* Tiny cave hint. TODO: replace with chunk generation and cave carving. */
    world_set_tile(12u, 14u, TILE_EMPTY);
    world_set_tile(13u, 14u, TILE_EMPTY);
    world_set_tile(14u, 14u, TILE_EMPTY);
}

uint8_t world_get_tile(uint8_t tx, uint8_t ty)
{
    if (tx >= WORLD_WIDTH_TILES || ty >= WORLD_HEIGHT_TILES) {
        return TILE_STONE;
    }

    return tiles[(ty * WORLD_WIDTH_TILES) + tx];
}

void world_set_tile(uint8_t tx, uint8_t ty, uint8_t tile)
{
    if (tx < WORLD_WIDTH_TILES && ty < WORLD_HEIGHT_TILES) {
        tiles[(ty * WORLD_WIDTH_TILES) + tx] = tile;
    }
}

bool world_is_solid_tile(uint8_t tile)
{
    return tile != TILE_EMPTY;
}

bool world_is_solid_at_pixel(int16_t x, int16_t y)
{
    if (x < 0 || y < 0) {
        return true;
    }

    return world_is_solid_tile(world_get_tile((uint8_t)(x >> 3), (uint8_t)(y >> 3)));
}

void world_mine_at_pixel(int16_t x, int16_t y)
{
    uint8_t tx;
    uint8_t ty;

    if (x < 0 || y < 0) {
        return;
    }

    tx = (uint8_t)(x >> 3);
    ty = (uint8_t)(y >> 3);

    if (world_get_tile(tx, ty) != TILE_STONE) {
        world_set_tile(tx, ty, TILE_EMPTY);
    }
}

void world_place_at_pixel(int16_t x, int16_t y, uint8_t tile)
{
    uint8_t tx;
    uint8_t ty;

    if (x < 0 || y < 0) {
        return;
    }

    tx = (uint8_t)(x >> 3);
    ty = (uint8_t)(y >> 3);

    if (world_get_tile(tx, ty) == TILE_EMPTY) {
        world_set_tile(tx, ty, tile);
    }
}

const uint8_t *world_tiles(void)
{
    return tiles;
}
