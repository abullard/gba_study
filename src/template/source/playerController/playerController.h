#ifndef __PLAYERCONTROLLER__
#define __PLAYERCONTROLLER__

#include "../include/types.h"
#include "../include/input.h"
#include "../include/tiles.h"

void handleMovement(OBJ_ATTR_t *);
void gravity();
OBJ_ATTR_t *initPlayer(OBJ_ATTR_t *);

#endif // __PLAYERCONTROLLER__