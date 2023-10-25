#include "background.h"

const u16 bg1_se_idx = 24;
const u16 bg2_se_idx = 26;
const u16 bg3_se_idx = 28;

BG_POINT bg1_pt = {0, 0};
BG_POINT bg2_pt = {0, 0};
BG_POINT bg3_pt = {0, 0};

void initMap()
{
    // BG 1
    memcpy(&bgPaletteVRAM[0], lvl1_bg1_bedroomPal, lvl1_bg1_bedroomPalLen);
    memcpy(&tile_mem[0][0], lvl1_bg1_bedroomTiles, lvl1_bg1_bedroomTilesLen);
    memcpy(&se_mem[bg1_se_idx][0], lvl1_bg1_bedroomMap, lvl1_bg1_bedroomMapLen);

    // // BG 2
    memcpy(&bgPaletteVRAM[1], lvl1_bg2_bedroomPal, lvl1_bg2_bedroomPalLen);
    memcpy(&tile_mem[1][0], lvl1_bg2_bedroomTiles, lvl1_bg2_bedroomTilesLen);
    memcpy(&se_mem[bg2_se_idx][0], lvl1_bg2_bedroomMap, lvl1_bg2_bedroomMapLen);

    // BG 3
    memcpy(&bgPaletteVRAM[2], lvl1_bg3_bedroomPal, lvl1_bg3_bedroomPalLen);
    memcpy(&tile_mem[2][0], lvl1_bg3_bedroomTiles, lvl1_bg3_bedroomTilesLen);
    memcpy(&se_mem[bg3_se_idx][0], lvl1_bg3_bedroomMap, lvl1_bg3_bedroomMapLen);

    REG_BG1CNT = BG_SBB(bg1_se_idx) | BG_CBB(0) | BG_REG_32x32 | BG_4BPP | BG_PRIO(1);
    REG_BG2CNT = BG_SBB(bg2_se_idx) | BG_CBB(1) | BG_REG_32x32 | BG_4BPP | BG_PRIO(2);
    REG_BG3CNT = BG_SBB(bg3_se_idx) | BG_CBB(2) | BG_REG_32x32 | BG_4BPP | BG_PRIO(3);

    REG_BG2HOFS = bg2_pt.x;
    REG_BG2VOFS = bg2_pt.y;
    REG_BG3HOFS = bg3_pt.x;
    REG_BG3VOFS = bg3_pt.y;
}

void scrollPlatforms()
{
    bg1_pt.x += key_tri_horz();
    bg2_pt.x += key_tri_horz();
    bg3_pt.x += key_tri_horz();

    bg1_pt.x = clamp(bg1_pt.x, 0, 0x10);
    bg2_pt.x = clamp(bg1_pt.x, 0, 0x10);
    bg3_pt.x = clamp(bg1_pt.x, 0, 0x10);

    setBackgroundOffset(1, bg1_pt);
    setBackgroundOffset(2, bg2_pt);
    setBackgroundOffset(3, bg3_pt);
}

// TODO AJB: find screen entry on every frame, if player moves into 
// #define X_CENTER 15
// #define Y_CENTER 10
// void checkScreenEntry() 
// {
//     u32 tx, ty;
//
//     tx = ((bg1_pt.x >> 3) + X_CENTER) & 0x3F;
//     ty = ((bg1_pt.y >> 3) + Y_CENTER) & 0x3F;
//
//     u32 se_curr = findScreenEntryIndex(tx, ty, 128);
// }