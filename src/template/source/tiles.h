#ifndef __TILES__
#define __TILES__

#include "types.h"
#include "masks.h"

static inline OBJ_ATTR *getAttrsForTile(OBJ_ATTR *buffer, u16 index)
{
    // we only have room for 128 obj_attr entries
    if (index < 0 || index > 127)
    {
        // TODO AJB: could i use iprintf() here? would I need some kind of
        // error function that interrupts VDraw, puts the gba into the right
        // display mode, and writes the error to the screen. Totally doable
        return 0;
    }

    return &buffer[index];
}

static inline void setAttrsForTile(OBJ_ATTR *tile, OBJ_ATTR attributes)
{
    tile->attr0 = attributes.attr0;
    tile->attr1 = attributes.attr1;
    tile->attr2 = attributes.attr2;
    // last 16 bits of OBJ_ATTR are filler space for OBJ_AFFINE alignment
}

// OBJ_ATTR.attr0{0-7} contain Y position data
// OBJ_ATTR.attr1{0-8} contain X position data
static inline void setTilePosition(OBJ_ATTR *tile, u32 posX, u32 posY)
{
    // TODO AJB: change this to some reuseable
    tile->attr0 = ((tile->attr0) & ~ATTR0_Y_MASK) | (((posY) << ATTR0_Y_SHIFT) & ATTR0_Y_MASK);
    tile->attr1 = ((tile->attr1) & ~ATTR1_X_MASK) | (((posX) << ATTR1_X_SHIFT) & ATTR1_X_MASK);
}

#endif // __TILES__