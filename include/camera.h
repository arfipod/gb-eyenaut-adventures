#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include "player.h"

typedef struct Camera {
    uint8_t x;
    uint8_t y;
} Camera;

void camera_update(Camera *camera, const Player *player);

#endif
