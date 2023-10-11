#ifndef __HELPERS__
#define __HELPERS__

#include "include/types.h"
#include "include/masks.h"
#include "include/registerAndMemoryLocations.h"

void oamInit(OBJ_ATTR *);
void copyBufferToOam(OBJ_ATTR *, OBJ_ATTR *, u16);

OBJ_ATTR createObjectAttribute(u16, u16, u16);

static inline void vsync()
{
    // wait for vDraw, we're "drawing" the 68 extra blank vertical scanlines
    while (VERT_DRAW_COUNT >= 160)
    {
    };
    // wait for vBlank, we're drawing the 160 scanlines at the moment
    while (VERT_DRAW_COUNT < 160)
    {
    };
}

static inline s16 clamp(s16 value, int min, int max)
{
    return (value > max) ? max : (value < min) ? min
                                               : value;
}

#endif // __HELPERS__
