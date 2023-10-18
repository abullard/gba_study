
#include "animations.h"

void nextFrame(ANIMATION *ani)
{
    // advance the animation frame (not the key frame!)
    u32 x = ani->curFrame;

    ani->curFrame =
        (ani->curFrame == ani->durationInFrames) ? 0 : ani->curFrame + 1;
    u32 bits = _log2(ani->tileOffset);
    u32 nextTileId = (ani->curFrame >> bits) << bits;

    OBJ_ATTR updatedObjAttrs =
        createObjectAttribute(ani->object->attr0, ani->object->attr1, (u16)nextTileId);

    setAttrsForTile(ani->object, updatedObjAttrs);
}