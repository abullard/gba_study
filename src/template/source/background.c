#include "background.h"

void initMap()
{
    memcpy(bgPaletteVRAM, bgPalette, bgPaletteLen);
    memcpy(&tileVRAM[0][0], bgTiles, bgTilesLen);
    // add our tileMap to our screenEntry VRAM
    memcpy(&screenentryVRAM[28][0], bgMap, bgMapLen);

    // mostly copied the #defines from tonc, but it's because they just make sense
    REG_BG0CTL = BG_SBB(28) | BG_CBB(0) | BG_REG_64x32 | BG_4BPP;

    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
}