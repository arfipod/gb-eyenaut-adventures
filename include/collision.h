#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>
#include <stdint.h>

bool collision_aabb_solid(int16_t x, int16_t y, uint8_t w, uint8_t h);

#endif
