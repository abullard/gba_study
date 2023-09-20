#ifndef __TEMPLATE__
#define __TEMPLATE__

typedef unsigned int u32, word;
typedef unsigned short u16, hword;
typedef u16 COLOR;

typedef volatile u16 vu16;
typedef volatile u32 vu32;

// 8, 32-bit arrays or 32 bytes of data
typedef struct
{
	u32 data[8];
} TILE, TILE4;

// 1024 bytes of data, the full 6mil addr of VRAM
// (i think this works for 7mil OAM too?)
typedef TILE CHARBLOCK[512];

#define MEM_IO 0x04000000
#define MEM_PAL 0x05000000	// no 8bit write !!
#define MEM_VRAM 0x06000000 // no 8bit write !!

#define PAL_BG_SIZE 0x00200
#define DCNT_OBJ 0x1000	   //!< Enable objects
#define DCNT_OBJ_1D 0x0040 //!< OBJ-VRAM as array

// hey, now we can add sprites/backgrounds to VRAM with array indexes!
#define tileVRAM ((CHARBLOCK *)MEM_VRAM)
#define MEM_PAL_OBJ (MEM_PAL + PAL_BG_SIZE)
#define paletteVRAM ((COLOR *)MEM_PAL_OBJ)
#define REG_BASE MEM_IO

#define REG_DISPCTL *(vu32 *)(REG_BASE + 0x0000)	 // display control
#define VERT_DRAW_COUNT *(vu16 *)(REG_BASE + 0x0006) // vertical count

#define INLINE static inline

INLINE void vsync()
{
	// wait for vDraw, we're "drawing" the 68 extra blank vertical scanlines
	while (VERT_DRAW_COUNT >= 160)
	{
	};
	// wait for vBlank, we're drawing the 160 scanlines at the moment
	while (VERT_DRAW_COUNT < 160)
	{
	};
}

#endif // __TEMPLATE__
