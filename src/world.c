#include "world.h"
#include "tile_defs.h"

static uint8_t tiles[WORLD_WIDTH_TILES * WORLD_HEIGHT_TILES];

void world_init(void)
{
    uint8_t chunk;
    uint8_t local_x;
    uint8_t y;

    for (chunk = 0u; chunk < WORLD_CHUNK_COUNT; ++chunk) {
        for (local_x = 0u; local_x < CHUNK_WIDTH_TILES; ++local_x) {
            for (y = 0u; y < WORLD_HEIGHT_TILES; ++y) {
                world_set_tile((uint16_t)((chunk * CHUNK_WIDTH_TILES) + local_x),
                               y,
                               chunk_generate_tile(chunk, local_x, y));
            }
        }
    }
}

uint8_t world_get_tile(uint16_t tx, uint8_t ty)
{
    if (tx >= WORLD_WIDTH_TILES || ty >= WORLD_HEIGHT_TILES) {
        return TILE_STONE;
    }

    return tiles[(ty * WORLD_WIDTH_TILES) + tx];
}

void world_set_tile(uint16_t tx, uint8_t ty, uint8_t tile)
{
    if (tx < WORLD_WIDTH_TILES && ty < WORLD_HEIGHT_TILES) {
        tiles[(ty * WORLD_WIDTH_TILES) + tx] = tile;
    }
}

bool world_is_solid_tile(uint8_t tile)
{
    return tile != TILE_EMPTY && tile != TILE_TORCH;
}

bool world_is_solid_at_pixel(int16_t x, int16_t y)
{
    if (x < 0 || y < 0) {
        return true;
    }

    return world_is_solid_tile(world_get_tile((uint16_t)(x >> 3), (uint8_t)(y >> 3)));
}

uint8_t world_mine_at_pixel(int16_t x, int16_t y)
{
    uint16_t tx;
    uint8_t ty;
    uint8_t tile;

    if (x < 0 || y < 0) {
        return TILE_EMPTY;
    }

    tx = (uint16_t)(x >> 3);
    ty = (uint8_t)(y >> 3);

    if (tx >= WORLD_WIDTH_TILES || ty >= WORLD_HEIGHT_TILES) {
        return TILE_EMPTY;
    }

    tile = world_get_tile(tx, ty);

    if (tile != TILE_EMPTY) {
        world_set_tile(tx, ty, TILE_EMPTY);
    }

    return tile;
}

bool world_place_at_pixel(int16_t x, int16_t y, uint8_t tile)
{
    uint16_t tx;
    uint8_t ty;

    if (x < 0 || y < 0) {
        return false;
    }

    tx = (uint16_t)(x >> 3);
    ty = (uint8_t)(y >> 3);

    if (tx >= WORLD_WIDTH_TILES || ty >= WORLD_HEIGHT_TILES) {
        return false;
    }

    return world_place_tile(tx, ty, tile);
}

bool world_place_tile(uint16_t tx, uint8_t ty, uint8_t tile)
{
    if (tx >= WORLD_WIDTH_TILES || ty >= WORLD_HEIGHT_TILES || tile == TILE_EMPTY) {
        return false;
    }

    if (world_get_tile(tx, ty) != TILE_EMPTY) {
        return false;
    }

    world_set_tile(tx, ty, tile);
    return true;
}

bool world_has_tile_near_pixel(int16_t x, int16_t y, uint8_t tile, uint8_t radius)
{
    int8_t dx;
    int8_t dy;
    int16_t center_tx;
    int16_t center_ty;

    if (x < 0 || y < 0) {
        return false;
    }

    center_tx = x >> 3;
    center_ty = y >> 3;

    for (dy = (int8_t)-radius; dy <= (int8_t)radius; ++dy) {
        for (dx = (int8_t)-radius; dx <= (int8_t)radius; ++dx) {
            int16_t tx = center_tx + dx;
            int16_t ty = center_ty + dy;

            if (tx < 0 || ty < 0) {
                continue;
            }

            if (world_get_tile((uint16_t)tx, (uint8_t)ty) == tile) {
                return true;
            }
        }
    }

    return false;
}

const uint8_t *world_tiles(void)
{
    return tiles;
}
