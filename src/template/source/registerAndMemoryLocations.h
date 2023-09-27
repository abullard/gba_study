#ifndef __REGISTERANDMEMEORYLOCATIONS__
#define __REGISTERANDMEMEORYLOCATIONS__

#include "types.h"

#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000  // no 8bit write !!
#define MEM_VRAM 0x06000000 // no 8bit write !!
#define MEM_OAM 0x07000000  // no 8bit write !!

#define tileVRAM ((CHARBLOCK *)MEM_VRAM)
#define oamRAM ((OBJ_ATTR *)MEM_OAM)
#define screenentryVRAM ((SCREENBLOCK *)MEM_VRAM)

#define MEM_PAL_OBJ (MEM_PAL + PAL_BG_SIZE)
#define paletteVRAM ((COLOR *)MEM_PAL_OBJ)
#define REG_BASE MEM_IO

#define REG_DISPCTL *(vu32 *)(REG_BASE + 0x0000)     // display control
#define VERT_DRAW_COUNT *(vu16 *)(REG_BASE + 0x0006) // vertical count
#define REG_BUTTONMASK *(vu16 *)(MEM_IO + 0x0130)

#endif // __REGISTERANDMEMEORYLOCATIONS__