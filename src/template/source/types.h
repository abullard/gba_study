#ifndef __TYPES__
#define __TYPES__

#define ALIGN_WORD __attribute__((aligned(4))) // Align 4 BYTES (32 bits)

typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef u16 COLOR;
typedef u16 SCREEN_ENTRY;

typedef volatile u16 vu16;
typedef volatile u32 vu32;

typedef struct BG_POINT
{
	s16 x, y;
} ALIGN_WORD BG_POINT;

// 8, 32-bit arrays or 32 bytes of data
typedef struct
{
	u32 data[8];
} TILE, TILE4;

// 1024 bytes of data, the full 6mil addr of VRAM
// (i think this works for 7mil OAM too?)
typedef TILE CHARBLOCK[512];

typedef SCREEN_ENTRY SCREENBLOCK[1024];

// 64 bits of memory, last 16 bits help align OBJ_ATTR WITH OBJ_AFFINE,
// since these data structures overlap
typedef struct
{
	u16 attr0;
	u16 attr1;
	u16 attr2;
	u16 fill;
} ALIGN_WORD OBJ_ATTR;

#endif // __TYPES__
