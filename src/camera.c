#include "camera.h"
#include "world.h"

#define SCREEN_W 160u
#define SCREEN_H 144u

void camera_update(Camera *camera, const Player *player)
{
    int16_t desired_x = (int16_t)(player->x - 72);
    int16_t desired_y = (int16_t)(player->y - 64);
    uint16_t max_x = 0u;
    uint8_t max_y = 0u;

    if (WORLD_WIDTH_PIXELS > SCREEN_W) {
        max_x = (uint16_t)(WORLD_WIDTH_PIXELS - SCREEN_W);
    }

    if (WORLD_HEIGHT_PIXELS > SCREEN_H) {
        max_y = (uint8_t)(WORLD_HEIGHT_PIXELS - SCREEN_H);
    }

    if (desired_x < 0) {
        camera->x = 0u;
    } else if ((uint16_t)desired_x > max_x) {
        camera->x = max_x;
    } else {
        camera->x = (uint16_t)desired_x;
    }

    if (desired_y < 0) {
        camera->y = 0u;
    } else if ((uint8_t)desired_y > max_y) {
        camera->y = max_y;
    } else {
        camera->y = (uint8_t)desired_y;
    }
}
