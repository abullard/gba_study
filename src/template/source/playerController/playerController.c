#include "playerController.h"
#include "../graphics/objects/cat_player.h"
#include <string.h>

u8 movementSpeed_g = 1;                           // 1m/s, or 32 pixels with my determined scale??
u16 playerX_g = 96, playerY_g = 32;               // starting coords
s16 gravity_g = 0x0020, gravity_accel_g = 0x0010; // fixed point 1.125
u16 max_gravity_g = 2;
s16 is_airborn_g = 0;

OBJ_ATTR *playerSpriteOamLocation;

void handleMovement(OBJ_ATTR *player)
{
    gravity();

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

    if (keyHit(KEY_A))
    {
        // JUMP
        is_airborn_g ^= 1;
    }

    setTilePosition(playerSpriteOamLocation, playerX_g, playerY_g);
}

void gravity()
{
    if (is_airborn_g == 1)
    {
        // has gravity reached maximum speed?
        if ((gravity_g >> 8) < 2)
        {
            // increasing gravity by 1.5 with integer truncation
            gravity_g += gravity_accel_g;
        }

        playerY_g += (gravity_g >> 8); // integer truncation of fixed point fractional bits
    }
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