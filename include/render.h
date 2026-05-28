#ifndef RENDER_H
#define RENDER_H

#include "camera.h"
#include "inventory.h"
#include "player.h"

void render_init(void);
void render_world(const Camera *camera);
void render_hud(const Inventory *inventory);
void render_menu(const Inventory *inventory, bool near_workbench);
void render_frame(const Camera *camera, const Player *player);

#endif
