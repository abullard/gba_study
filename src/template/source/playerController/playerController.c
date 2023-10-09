#include "playerController.h"
#include "../graphics/objects/cat_player.h"
#include <string.h>

u8 movementSpeed_g = 1;
u16 playerX_g = 96, playerY_g = 32; // starting coords
u16 g_gravity = 10, airborn_g = 0;  // 10 m/s for simplicity and no floats
s16 velocity_g = 0;

OBJ_ATTR *playerSpriteOamLocation;

void handleMovement(OBJ_ATTR *player)
{
    if (keyHeld(KEY_LEFT))
    {
        playerX_g += movementSpeed_g * -1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_HORIZONTAL_FLIP);
    }

    if (keyHeld(KEY_RIGHT))
    {
        playerX_g += movementSpeed_g * 1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_NO_HORIZONTAL_FLIP);
    }

    // if(airborn_g == 1) {
    //     v
    // }

    setTilePosition(playerSpriteOamLocation, playerX_g, playerY_g);
}

void gravity(OBJ_ATTR *localOamBuffer)
{
}

OBJ_ATTR *initPlayer(OBJ_ATTR *localOamBuffer)
{
    // let's load our graphic into memory
    // charblock 0-3 (tile_mem[0-3]) are for background data
    // charblock 4-5 (tile_mem[4-5]) are for sprite data
    memcpy(&tileVRAM[4][0], cat_playerTiles, cat_playerTilesLen);
    // sprites won't render if we don't load the palette
    memcpy(objPaletteVRAM, cat_playerPal, cat_playerPalLen);

    // set OAM to hide sprites at first
    oamInit(localOamBuffer);

    // straight up just stole this from tonc
    u32 tile_id = 0, pal_bank = 0;

    playerSpriteOamLocation = getAttrsForTile(localOamBuffer, 0);

    setAttrsForTile(playerSpriteOamLocation,
                    createObjectAttribute(
                        ATTR0_OBJ_MODE_REGULAR | ATTR0_COLOR_MODE_8BPP, // square sprite
                        ATTR1_SIZE_32x32,                               // 32x32 pixel sprite
                        pal_bank << 12 | tile_id));

    setTilePosition(playerSpriteOamLocation, playerX_g, playerY_g);

    return playerSpriteOamLocation;
}