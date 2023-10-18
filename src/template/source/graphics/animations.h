#ifndef __ANIMATIONS__
#define __ANIMATIONS__

#include "../helpers.h"
#include "../include/tiles.h"

typedef struct ANIMATION
{
    OBJ_ATTR *object;
    u16 curFrame;
    u16 durationInFrames;
    u16 tileOffset;
    u16 bits;
} ALIGN4 ANIMATION;

void nextFrame(ANIMATION *);

#endif // __ANIMATIONS__