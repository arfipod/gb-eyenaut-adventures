#include "collision.h"
#include "world.h"

bool collision_aabb_solid(int16_t x, int16_t y, uint8_t w, uint8_t h)
{
    return world_is_solid_at_pixel(x, y) ||
           world_is_solid_at_pixel((int16_t)(x + w - 1), y) ||
           world_is_solid_at_pixel(x, (int16_t)(y + h - 1)) ||
           world_is_solid_at_pixel((int16_t)(x + w - 1), (int16_t)(y + h - 1));
}
