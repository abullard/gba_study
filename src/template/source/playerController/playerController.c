#include "playerController.h"

#include <string.h>

s32 playerX_fp_g = 0x000F0000, playerY_fp_g = 0x00640000; // x: 15, y: 100 in 16.16fp
s32 playerVelocity_fp_g = 0x0001F000;
s32 gravity_fp_g = 0x00008000, gravityAccel_fp_g = 0x00001000, maxGravity_g = 3;

int idleAnimationFrame_g = 0;

// booleans, 0 = false, 1 = true
int isAirborn_g = 0, idle_g = 0, falling_g = 0;

OBJ_ATTR *playerSpriteOamLocation_g;

void handleMovement(OBJ_ATTR *player)
{
    int moving = key_tri_horz();
    idle_g = (moving == 0) ? 1 : 0;
    playerX_fp_g += playerVelocity_fp_g * moving;

    (moving == -1)  ? flipTileHorizontally(player, ATTR1_HFLIP >> 12)
    : (moving == 1) ? flipTileHorizontally(player, (ATTR1_HFLIP & 0x0) >> 12)
                    : 0;

    if (key_hit(KEY_A))
    {
        idle_g = 0;
        // TODO AJB: JUMP
        isAirborn_g ^= 1;
        gravity_fp_g = 0x00002000; // reset gravity to init
    }

    // TODO AJB: check for collision?
    idleAnimation(4);
    gravity();
    setTilePosition(player, GET_FIXEDP_INT(playerX_fp_g), GET_FIXEDP_INT(playerY_fp_g));
}

void idleAnimation(int frames)
{
    if (idle_g == 0)
        return;

    idleAnimationFrame_g += 1;
    if (idleAnimationFrame_g > 127)
    {
        idleAnimationFrame_g = 0;
    }

    //  0, 32, 64, 96 for idle animation tile spacing
    setAttrsForTile(playerSpriteOamLocation_g,
                    createObjectAttribute(playerSpriteOamLocation_g->attr0,
                                          playerSpriteOamLocation_g->attr1,
                                          ((idleAnimationFrame_g >> 5) << 5)));
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
    playerY_fp_g += gravity_fp_g;
}

OBJ_ATTR *initPlayer(OBJ_ATTR *localOamBuffer)
{
    // charblock 0-3 (tile_mem[0-3]) are for background data
    // charblock 4-5 (tile_mem[4-5]) are for sprite data
    memcpy(&tile_mem[4][0], filbert_idleTiles, filbert_idleTilesLen);
    // sprites won't render if we don't load the palette
    memcpy(pal_obj_mem, filbert_idlePal, filbert_idlePalLen);

    oamInit(localOamBuffer);

    u32 tile_id = 0, pal_bank = 0;
    playerSpriteOamLocation_g = getAttrsForTile(localOamBuffer, 0);

    setAttrsForTile(playerSpriteOamLocation_g,
                    createObjectAttribute(
                        ATTR0_REG | ATTR0_8BPP, // square sprite
                        ATTR1_SIZE_32x32,       // 32x32 pixel sprite
                        pal_bank << 12 | tile_id));

    setTilePosition(playerSpriteOamLocation_g, playerX_fp_g, playerY_fp_g);

    return playerSpriteOamLocation_g;
}