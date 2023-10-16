#ifndef __HELPERS__
#define __HELPERS__

#include <tonc.h>

void oamInit(OBJ_ATTR *);
void copyBufferToOam(OBJ_ATTR *, OBJ_ATTR *, u16);
OBJ_ATTR createObjectAttribute(u16, u16, u16);

static inline void vsync()
{
    // wait for vDraw, we're "drawing" the 68 extra blank vertical scanlines
    while (REG_VCOUNT >= 160)
    {
    };
    // wait for vBlank, we're drawing the 160 scanlines at the moment
    while (REG_VCOUNT < 160)
    {
    };
}

#endif // __HELPERS__
