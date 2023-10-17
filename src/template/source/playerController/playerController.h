#ifndef __PLAYERCONTROLLER__
#define __PLAYERCONTROLLER__

#include "../include/tiles.h"
#include "../graphics/objects/filbert_idle.h"
#include "../helpers.h"

void handleMovement(OBJ_ATTR *);
void gravity();
OBJ_ATTR *initPlayer(OBJ_ATTR *);
void idleAnimation(int frames);

#endif // __PLAYERCONTROLLER__