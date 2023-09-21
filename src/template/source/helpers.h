#ifndef __HELPERS__
#define __HELPERS__

#include "types.h"
#include "masks.h"
#include "registerAndMemoryLocations.h"

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
    // #define BFN_SET(y, x, name) (y = ((y) & ~name##_MASK) | BFN_PREP(x, name))
    // #define BFN_PREP(x, name) (((x) << name##_SHIFT) & name##_MASK)

    // BFN_SET(obj->attr0, y, ATTR0_Y);
	// BFN_SET(obj->attr1, x, ATTR1_X);

    tile->attr0 = ((tile->attr0) & ~ATTR0_Y_MASK) | (((posY) << ATTR0_Y_SHIFT) & ATTR0_Y_MASK);
    tile->attr1 = ((tile->attr1) & ~ATTR1_X_MASK) | (((posX) << ATTR1_X_SHIFT) & ATTR1_X_MASK);
}

#endif // __HELPERS__
