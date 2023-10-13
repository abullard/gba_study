#ifndef __WINDOW__
#define __WINDOW__

#include "registerAndMemoryLocations.h"
#include "macros.h"
#include "masks.h"

// write corners of our window0 to their registers.
// call this once per frame if your window moves
static inline void createWindow0FromCorners(WIN_CORNERS_t *windowCoords)
{
    REG_WIN0H = windowCoords[0].left << 8 | windowCoords[0].right;
    REG_WIN0V = windowCoords[0].top << 8 | windowCoords[0].bottom;
}

// call this once per frame if your window moves
static inline void createWindow1FromCorners(WIN_CORNERS_t *windowCoords)
{
    REG_WIN1H = windowCoords[0].left << 8 | windowCoords[0].right;
    REG_WIN1V = windowCoords[0].top << 8 | windowCoords[0].bottom;
}

// winIn = win0 U win1
static inline void winInEnableLayers(u16_t layerMask)
{
    REG_WININ = WININ_BUILD(WIN_OBJ, WIN_BG0); 
}

// winObj and winOut. winOut = ~winIn
static inline void winOutEnableLayers(u16_t layerMask)
{
    REG_WINOUT = WINOUT_BUILD(WIN_BG1, 0);
}

#endif // __WINDOW__