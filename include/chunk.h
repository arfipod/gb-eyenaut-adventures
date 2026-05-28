#ifndef CHUNK_H
#define CHUNK_H

#include <stdint.h>

#define CHUNK_WIDTH_TILES 8u
#define WORLD_CHUNK_COUNT 16u

uint8_t chunk_generate_tile(uint8_t chunk_index, uint8_t local_x, uint8_t y);
void chunk_tick(uint16_t camera_x);
uint8_t chunk_active_index(void);

#endif
