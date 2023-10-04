#include "background.h"

const u16 bg0_se_idx = 24;
const u16 bg1_se_idx = 26;
const u16 bg2_se_idx = 28;
const u16 bg3_se_idx = 30;

void initMap()
{
    memcpy(&bgPaletteVRAM[0], bgSkyboxPalette, bgSkyboxPaletteLen); // add palette to VRAM
    memcpy(&bgPaletteVRAM[1], bgPlatformsPalette, bgPlatformsPaletteLen); // add palette to VRAM

    memcpy(&tileVRAM[2][0], bgSkyboxTiles, bgSkyboxTilesLen);   // add tiles to VRAM
    memcpy(&tileVRAM[1][0], bgPlatformsTiles, bgPlatformsTilesLen);   // add tiles to VRAM

    memcpy(&screenentryVRAM[bg2_se_idx][0], bgSkyboxMap, bgSkyboxMapLen);       // BG 2 (platforms2)
    memcpy(&screenentryVRAM[bg1_se_idx][0], bgPlatformsMap, bgPlatformsMapLen); // BG 1 (platforms)

    REG_BG1CTL = BG_SBB(bg1_se_idx) | BG_CBB(1) | BG_REG_32x32 | BG_4BPP | DCTL_BG_PRIORITY_SECOND;
    REG_BG2CTL = BG_SBB(bg2_se_idx) | BG_CBB(2) | BG_REG_32x32 | BG_4BPP | DCTL_BG_PRIORITY_THIRD;

    REG_BG2HOFS = 0;
    REG_BG2VOFS = 96;

    // memcpy(&screenentryVRAM[bg0_se_idx][0], , ); // BG 0 (UI)
    // memcpy(&screenentryVRAM[bg3_se_idx][0], bg_PlatformsMap, bg_PlatformsMapLen);    // BG 3 (skybox)

    // REG_BG0CTL = BG_SBB(bg0_se_idx) | BG_CBB(0) | BG_REG_64x32 | BG_4BPP | DCTL_BG_PRIORITY_FIRST;
    // REG_BG3CTL = BG_SBB(bg3_se_idx) | BG_CBB(0) | BG_REG_64x32 | BG_4BPP | DCTL_BG_PRIORITY_FOURTH;
    
    // REG_BG3HOFS = 0;
    // REG_BG3VOFS = 0;
}