#include "background.h"

const u16 bg0_se_idx = 24;
const u16 bg1_se_idx = 26;
const u16 bg2_se_idx = 28;
const u16 bg3_se_idx = 30;

BG_POINT bg1_pt = {0, 0};
BG_POINT bg2_pt_parallaxed = {0, 96};

void initMap()
{
    memcpy(&bgPaletteVRAM[0], bgSkyboxPalette, bgSkyboxPaletteLen);       // add palette to VRAM
    memcpy(&bgPaletteVRAM[1], bgPlatformsPalette, bgPlatformsPaletteLen); // add palette to VRAM

    memcpy(&tileVRAM[0][0], bgPlatformsTiles, bgPlatformsTilesLen); // add tiles to VRAM
    memcpy(&tileVRAM[1][0], bgSkyboxTiles, bgSkyboxTilesLen);       // add tiles to VRAM

    memcpy(&screenentryVRAM[bg2_se_idx][0], bgSkyboxMap, bgSkyboxMapLen);       // BG 2 (platforms2)
    memcpy(&screenentryVRAM[bg1_se_idx][0], bgPlatformsMap, bgPlatformsMapLen); // BG 1 (platforms)

    REG_BG1CTL = BG_SBB(bg1_se_idx) | BG_CBB(0) | BG_REG_32x32 | BG_4BPP | DCTL_BG_PRIORITY_SECOND;
    REG_BG2CTL = BG_SBB(bg2_se_idx) | BG_CBB(1) | BG_REG_32x32 | BG_4BPP | DCTL_BG_PRIORITY_THIRD;

    REG_BG2HOFS = bg2_pt_parallaxed.x;
    REG_BG2VOFS = bg2_pt_parallaxed.y;

    // memcpy(&screenentryVRAM[bg0_se_idx][0], , ); // BG 0 (UI)
    // memcpy(&screenentryVRAM[bg3_se_idx][0], bg_PlatformsMap, bg_PlatformsMapLen);    // BG 3 (skybox)

    // REG_BG0CTL = BG_SBB(bg0_se_idx) | BG_CBB(0) | BG_REG_64x32 | BG_4BPP | DCTL_BG_PRIORITY_FIRST;
    // REG_BG3CTL = BG_SBB(bg3_se_idx) | BG_CBB(0) | BG_REG_64x32 | BG_4BPP | DCTL_BG_PRIORITY_FOURTH;

    // REG_BG3HOFS = 0;
    // REG_BG3VOFS = 0;
}

void scrollPlatforms()
{
    bg1_pt.x += keyTriHorz();
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