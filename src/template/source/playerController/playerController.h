#ifndef __PLAYERCONTROLLER__
#define __PLAYERCONTROLLER__

#include "../include/types.h"
#include "../input.h"
#include "../tiles.h"

void handleMovement(OBJ_ATTR *);
void gravity(OBJ_ATTR *);
OBJ_ATTR *initPlayer(OBJ_ATTR *);

#endif // __PLAYERCONTROLLER__