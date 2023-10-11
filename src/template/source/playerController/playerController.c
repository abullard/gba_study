#include "playerController.h"
#include "../graphics/objects/cat_player.h"

#include <string.h>

u16 playerX_g = 15, playerY_g = 100;

s32 playerVelocity_fp_g = 0x00000100;  // 1 in 8.8f
s32 gravity_fp_g = 0x00002000, gravityAccel_fp_g = 0x00001000, maxGravity_g = 3;
int isAirborn_g = 0;

OBJ_ATTR *playerSpriteOamLocation;

void handleMovement(OBJ_ATTR *player)
{
    gravity();

    if (keyHeld(KEY_LEFT))
    {
        playerX_g += GET_FIXEDP_INT(playerVelocity_fp_g) * -1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_HORIZONTAL_FLIP);
    }

    if (keyHeld(KEY_RIGHT))
    {
        playerX_g += GET_FIXEDP_INT(playerVelocity_fp_g) * 1;
        flipTileHorizontally(playerSpriteOamLocation, ATTR1_NO_HORIZONTAL_FLIP);
    }

    if (keyHit(KEY_A))
    {
        // TODO AJB: JUMP
        isAirborn_g ^= 1;
        gravity_fp_g = 0x00002000; // reset gravity to init
    }

    // TODO AJB: check for collision?
    setTilePosition(playerSpriteOamLocation, playerX_g, playerY_g);
}

void gravity()
{
    if (isAirborn_g == 0)
        return;

    if (GET_FIXEDP_INT(gravity_fp_g) < maxGravity_g)
    {
        // increasing gravity by .125
        gravity_fp_g += gravityAccel_fp_g;
    }

    // integer truncation of fixed point fractional bits
    playerY_g += GET_FIXEDP_INT(gravity_fp_g);
}

OBJ_ATTR *initPlayer(OBJ_ATTR *localOamBuffer)
{
    // charblock 0-3 (tile_mem[0-3]) are for background data
    // charblock 4-5 (tile_mem[4-5]) are for sprite data
    memcpy(&tileVRAM[4][0], cat_playerTiles, cat_playerTilesLen);
    // sprites won't render if we don't load the palette
    memcpy(objPaletteVRAM, cat_playerPal, cat_playerPalLen);

    oamInit(localOamBuffer);

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