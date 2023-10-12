#ifndef __TILES__
#define __TILES__

#include "types.h"
#include "masks.h"
#include "macros.h"

static inline OBJ_ATTR_t *getAttrsForTile(OBJ_ATTR_t *buffer, u16_t index)
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

static inline void setAttrsForTile(OBJ_ATTR_t *tile, OBJ_ATTR_t attributes)
{
    tile->attr0 = attributes.attr0;
    tile->attr1 = attributes.attr1;
    tile->attr2 = attributes.attr2;
    // last 16 bits of OBJ_ATTR are filler space for OBJ_AFFINE alignment
}

// OBJ_ATTR.attr0{0-7} contains Y position data
// OBJ_ATTR.attr1{0-8} contains X position data
static inline void setTilePosition(OBJ_ATTR_t *tile, u32_t posX, u32_t posY)
{
    BITFIELD_SET(tile->attr0, posY, ATTR0_POS_Y);
    BITFIELD_SET(tile->attr1, posX, ATTR1_POS_X);
}

// OBJ_ATTR.attr1{C} contains HFLIP property
static inline void flipTileHorizontally(OBJ_ATTR_t *tile, u16_t hFlip)
{
    BITFIELD_SET(tile->attr1, hFlip, ATTR1_HFLIP);
}

#endif // __TILES__