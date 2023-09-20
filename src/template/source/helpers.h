#ifndef __HELPERS__
#define __HELPERS__

#include "types.h"
#include "registerAndMemoryLocations.h"

void oamInit(OBJ_ATTR *);
void copyBufferToOam(OBJ_ATTR *, OBJ_ATTR *, u16);

OBJ_ATTR *getAttrForTile(OBJ_ATTR *, u16);

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

static inline OBJ_ATTR *getAttrForTile(OBJ_ATTR *buffer, u16 index)
{
    // we only have room for 128 obj_attr entries
    if (index < 0 || index > 127)
    {
        // TODO AJB: could i use iprintf() here? would I need some kind of
        // error function that puts the gba into the right display mode?
        return 0;
    }

    return &buffer[index];
}

static inline void setAttrForTile(OBJ_ATTR *tile, OBJ_ATTR attributes)
{
    tile->attr0 = attributes.attr0;
    tile->attr1 = attributes.attr1;
    tile->attr2 = attributes.attr2;
    // last 16 bits of OBJ_ATTR are filler space for OBJ_AFFINE alignment
}

// OBJ_ATTR.attr0{0-7} contain Y position data
// OBJ_ATTR.attr1{0-8} contain X position data
static inline void setTilePosition(OBJ_ATTR* tile, u32 posX, u32 posY)
{
    // (tile->attr0 & ~0x00FF) | (posY << 0) & 0x00FF
    tile->attr0, posY
    tile->attr1, posX
}

#endif // __HELPERS__
