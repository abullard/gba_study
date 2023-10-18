#include "playerController.h"

#include <string.h>

s32 playerX_fp_g = 0x000F0000, playerY_fp_g = 0x00640000; // x: 15, y: 100 in 16.16fp
s32 playerVelocity_fp_g = 0x0001F000;
s32 gravity_fp_g = 0x00008000, gravityAccel_fp_g = 0x00001000, maxGravity_g = 3;

// booleans, 0 = false, 1 = true
int isAirborn_g = 0, idle_g = 0, falling_g = 0;

ANIMATION idleAni; //, *jump, *walk, *run;

OBJ_ATTR *playerSpriteOamLocation_g;

void handleMovement(OBJ_ATTR *player)
{
    int moving = key_tri_horz();
    idle_g = (moving == 0) ? 1 : 0;
    playerX_fp_g += playerVelocity_fp_g * moving;

    (moving == -1)  ? flipTileHorizontally(player, (ATTR1_HFLIP) >> 12)
    : (moving == 1) ? flipTileHorizontally(player, (ATTR1_HFLIP & 0x0) >> 12)
                    : 0;

    if (key_hit(KEY_A))
    {
        // TODO AJB: JUMP
        isAirborn_g ^= 1;
        gravity_fp_g = 0x00002000; // reset gravity to init
    }

    // TODO AJB: check for collision?
    idleAnimation();
    gravity();
    setTilePosition(player, GET_FIXEDP_INT(playerX_fp_g), GET_FIXEDP_INT(playerY_fp_g));
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

    initIdleAnimation();
    // initWalkAnimation();
    // initRunAnimation();
    // initJumpAnimation();

    return playerSpriteOamLocation_g;
}

// 4 keyFrames, tileIds [0, 32, 64, 96]
void initIdleAnimation()
{
    u16 _tileOffset = _multiply(16, 2);
    
    idleAni.object = playerSpriteOamLocation_g;
    idleAni.curFrame = 0;
    // 16 dTiles @ 8bpp, each tile takes 2 nibbles
    idleAni.tileOffset = _tileOffset;
    // numScreenRefreshesPerKeyFrame * keyFrames,
    // numScreenRefreshesPerKeyFrame = tileOffset in this case, but is not related
    idleAni.durationInFrames = 128;
    idleAni.bits = _log2(_tileOffset);
}

//  0, 32, 64, 96 for idle ani. key frames tile start indexes
void idleAnimation()
{
    if (idle_g == 1)
        nextFrame(&idleAni);
}