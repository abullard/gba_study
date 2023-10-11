#include "../include/registerAndMemoryLocations.h"
#include "../include/masks.h"
#include "tiles/BG_Externs.h"
#include "../include/input.h"
#include "../helpers.h"

#include <string.h>

extern const u16_t bg0_se_idx;
extern const u16_t bg1_se_idx;
extern const u16_t bg2_se_idx;
extern const u16_t bg3_se_idx;

void initMap();
void skyboxParallax();
void scrollPlatforms();

static inline u32_t findScreenEntryIndex(u32_t tileX, u32_t tileY, u32_t pitch)
{
    u32_t sbb = ((tileX >> 5) + (tileY >> 5) * (pitch >> 5));

    return sbb * 1024 + ((tileX & 31) + (tileY & 31) * 32);
}

static inline void setBackgroundOffset(int bgIndex, BG_POINT_t bgCoords)
{
    if (bgIndex < 0 || bgIndex > 3)
    {
        REG_DISPCTL = 0;
        // TODO AJB: create a text warning that logs to the screen
    }

    REG_BG_OFS[bgIndex] = bgCoords;
}