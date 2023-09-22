#include "playerController.h"

u8 movementSpeed = 2;
u16 playerX = 96, playerY = 32;

OBJ_ATTR *playerSpriteOamLocation;

void handleMovement(OBJ_ATTR *player)
{
    // TODO AJB: you need some way to set individual attrs for a tile
    if (keyHeld(KEY_LEFT))
    {
        playerX += movementSpeed * -1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_HORIZONTAL_FLIP);
    }

    if (keyHeld(KEY_RIGHT))
    {
        playerX += movementSpeed * 1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_NO_HORIZONTAL_FLIP);
    }

    setTilePosition(playerSpriteOamLocation, playerX, playerY);
}

OBJ_ATTR *initPlayer(OBJ_ATTR *localOamBuffer)
{
    // straight up just stole this from tonc
    u32 tile_id = 0, pal_bank = 0;

    playerSpriteOamLocation = getAttrsForTile(localOamBuffer, 0);

    setAttrsForTile(playerSpriteOamLocation,
                    createObjectAttribute(
                        ATTR0_OBJ_MODE_REGULAR | ATTR0_COLOR_MODE_8BPP, // square sprite
                        ATTR1_SIZE_32x32,                               // 32x32 pixel sprite
                        pal_bank << 12 | tile_id));

    setTilePosition(playerSpriteOamLocation, playerX, playerY);

    return playerSpriteOamLocation;
}