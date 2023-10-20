#include "background.h"

const u16 bg0_se_idx = 24;
const u16 bg1_se_idx = 26;
const u16 bg2_se_idx = 28;
const u16 bg3_se_idx = 30;

BG_POINT bg1_pt = {0, 0};
BG_POINT bg2_pt_parallaxed = {0, 96};

void initMap()
{
    // TODO AJB:
    // * palette size is wrong in gfx.h, check grit opts
    // * load bg data into the right registers
    // * anything else? it's still broken, you'll need to investigate stuff

    // BG 1
    memcpy(&bgPaletteVRAM[0], lvl1_bg1_bedroomPal, lvl1_bg1_bedroomPalLen);
    memcpy(&tile_mem[0][0], lvl1_bg1_bedroomTiles, lvl1_bg1_bedroomTilesLen);
    memcpy(&se_mem[bg1_se_idx][0], lvl1_bg1_bedroomMap, lvl1_bg1_bedroomMapLen);

    // BG 2
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

    REG_BG2HOFS = bg2_pt_parallaxed.x;
    REG_BG2VOFS = bg2_pt_parallaxed.y;
}

void scrollPlatforms()
{
    bg1_pt.x += key_tri_horz();
    bg1_pt.x = clamp(bg1_pt.x, 0, 0x10);

    setBackgroundOffset(1, bg1_pt);
}

// keep this for now, you'll want it when there's an actual background
// TODO AJB: this won't work, you need to move bg2 when bg1 scrolls a certain distance
// s16 bg2_actual = 0;
void skyboxParallax()
{
    // bg2_actual += keyTriHorz();

    // // naive approach to parallax, if we've moved 10 pixels, move skybox by 1 pixel
    // if (bg2_actual > 1000) {
    //     bg2_actual = 0;
    // 	bg2_pt_parallaxed.x += 1;
    // }
    // else if(bg2_actual < 0) {
    //     bg2_actual = 0;
    // 	bg2_pt_parallaxed.x -= 1;
    // }

    // setBackgroundOffset(2, bg2_pt_parallaxed);
}