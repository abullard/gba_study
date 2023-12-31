#include "../helpers.h"
#include "../include/macros.h"
#include "../include/memmap.h"

#include <string.h>
#include <gfx.h>

extern const u16 bg0_se_idx;
extern const u16 bg1_se_idx;
extern const u16 bg2_se_idx;
extern const u16 bg3_se_idx;

void initMap();
void skyboxParallax();
void scrollPlatforms();
void checkScreenEntry();

static inline u32 findScreenEntryIndex(u32 tileX, u32 tileY, u32 pitch)
{
    u32 sbb = ((tileX >> 5) + (tileY >> 5) * (pitch >> 5));

    return sbb * 1024 + ((tileX & 31) + (tileY & 31) * 32);
}

static inline void setBackgroundOffset(int bgIndex, BG_POINT bgCoords)
{
    if (bgIndex < 0 || bgIndex > 3)
    {
        REG_DISPCNT = 0;
        // TODO AJB: create a text warning that logs to the screen
    }

    REG_BG_OFS[bgIndex] = bgCoords;
}