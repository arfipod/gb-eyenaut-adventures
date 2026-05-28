#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "player.h"

void render_init(void);
void render_world(void);
void render_frame(const Camera *camera, const Player *player);

#endif
