
#include "animations.h"

void nextFrame(ANIMATION *ani)
{
    // advance the animation frame (not the key frame!)
    ani->curFrame =
        (ani->curFrame == ani->durationInFrames - 1) ? 0 : ani->curFrame + 1;

    OBJ_ATTR updatedObjAttrs =
        createObjectAttribute(ani->object->attr0,
                              ani->object->attr1,
                              (u16)((ani->curFrame >> ani->bits) << ani->bits));

    setAttrsForTile(ani->object, updatedObjAttrs);
}