#ifndef __PLAYERCONTROLLER__
#define __PLAYERCONTROLLER__

#include "../include/tiles.h"
#include "../graphics/objects/cat_player.h"
#include "../helpers.h"

void handleMovement(OBJ_ATTR *);
void gravity();
OBJ_ATTR *initPlayer(OBJ_ATTR *);

#endif // __PLAYERCONTROLLER__