#ifndef WORLD_H
#define WORLD_H

#include <stdbool.h>
#include <stdint.h>

#define WORLD_WIDTH_TILES 32u
#define WORLD_HEIGHT_TILES 18u

void world_init(void);
uint8_t world_get_tile(uint8_t tx, uint8_t ty);
void world_set_tile(uint8_t tx, uint8_t ty, uint8_t tile);
bool world_is_solid_tile(uint8_t tile);
bool world_is_solid_at_pixel(int16_t x, int16_t y);
void world_mine_at_pixel(int16_t x, int16_t y);
void world_place_at_pixel(int16_t x, int16_t y, uint8_t tile);
const uint8_t *world_tiles(void);

#endif
