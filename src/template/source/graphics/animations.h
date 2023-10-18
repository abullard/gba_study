#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include "../helpers.h"
#include "../include/tiles.h"

typedef struct ANIMATION
{
    OBJ_ATTR *object;
    u32 curFrame;
    u32 durationInFrames;
    u32 tileOffset;
} ANIMATION;

void nextFrame(ANIMATION *);

#endif // __ANIMATIONS__