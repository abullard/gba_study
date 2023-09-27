#include "background.h"

void initMap()
{
    // TODO AJB: come back to this and make something readable
    REG_BG0CTL = 0 << 2 | 28 << 8 | 0xC000;

    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;

    // palette added to VRAM
    memcpy(paletteVRAM, bgPalette, bgPaletteLen);
    // tiles added to VRAM
    memcpy(&tileVRAM[0][0], bgTiles, bgTilesLen);
    // add our tileMap to our screenEntry VRAM
    memcpy(&screenentryVRAM[28][0], bgMap, bgMapLen);
}