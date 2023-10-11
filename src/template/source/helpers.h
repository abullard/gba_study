#ifndef __HELPERS__
#define __HELPERS__

#include "include/types.h"
#include "include/masks.h"
#include "include/registerAndMemoryLocations.h"

void oamInit(OBJ_ATTR_t *);
void copyBufferToOam(OBJ_ATTR_t *, OBJ_ATTR_t *, u16_t);

OBJ_ATTR_t createObjectAttribute(u16_t, u16_t, u16_t);

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

static inline s16_t clamp(s16_t value, int min, int max)
{
    return (value > max) ? max : (value < min) ? min
                                               : value;
}

#endif // __HELPERS__
