#ifndef __REGISTERANDMEMEORYLOCATIONS__
#define __REGISTERANDMEMEORYLOCATIONS__

#include "types.h"

#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000  // no 8bit write !!
#define MEM_VRAM 0x06000000 // no 8bit write !!
#define MEM_OAM 0x07000000  // no 8bit write !!

#define objPaletteVRAM ((COLOR *)(MEM_PAL + PAL_BG_SIZE))
#define bgPaletteVRAM ((PALETTE *)MEM_PAL)

#define tileVRAM ((CHARBLOCK *)MEM_VRAM)
#define oamRAM ((OBJ_ATTR *)MEM_OAM)
#define screenentryVRAM ((SCREENBLOCK *)MEM_VRAM)

#define REG_DISPCTL *(vu32 *)(MEM_IO + 0x0000) // display control
#define REG_BG0CTL *(vu16 *)(MEM_IO + 0x0008)  // display control
#define REG_BG1CTL *(vu16 *)(MEM_IO + 0x000A)  // display control
#define REG_BG2CTL *(vu16 *)(MEM_IO + 0x000C)  // display control
#define REG_BG3CTL *(vu16 *)(MEM_IO + 0x000E)  // display control

#define VERT_DRAW_COUNT *(vu16 *)(MEM_IO + 0x0006) // vertical count
#define REG_BUTTONMASK *(vu16 *)(MEM_IO + 0x0130)

#define REG_BG_OFS ((BG_POINT *)(MEM_IO + 0x0010)) // (write only!)
#define REG_BG0HOFS *(vu16 *)(MEM_IO + 0x0010)     // bg 0-3 offsets
#define REG_BG0VOFS *(vu16 *)(MEM_IO + 0x0012)
#define REG_BG1HOFS *(vu16 *)(MEM_IO + 0x0014)
#define REG_BG1VOFS *(vu16 *)(MEM_IO + 0x0016)
#define REG_BG2HOFS *(vu16 *)(MEM_IO + 0x0018)
#define REG_BG2VOFS *(vu16 *)(MEM_IO + 0x001A)
#define REG_BG3HOFS *(vu16 *)(MEM_IO + 0x001C)
#define REG_BG3VOFS *(vu16 *)(MEM_IO + 0x001E)

#endif // __REGISTERANDMEMEORYLOCATIONS__