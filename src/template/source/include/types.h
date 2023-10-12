#ifndef __TYPES__
#define __TYPES__

#define ALIGN_WORD __attribute__((aligned(4))) // Align 4 BYTES (32 bits)

typedef unsigned char u8_t;
typedef signed char s8_t;
typedef unsigned short u16_t;
typedef signed short s16_t;
typedef unsigned int u32_t;
typedef signed int s32_t;

typedef u16_t COLOR_t;
typedef u16_t SCREEN_ENTRY_t;

typedef volatile u16_t vu16_t;
typedef volatile u32_t vu32_t;

typedef struct BG_POINT_t
{
	s16_t x, y;
} ALIGN_WORD BG_POINT_t;

// 8, 32-bit arrays or 32 bytes of data
typedef struct
{
	u32_t
		data[8];
} TILE_t, TILE4_t;

typedef TILE_t CHARBLOCK_t[512];			// 16kB of data
typedef SCREEN_ENTRY_t SCREENBLOCK_t[1024]; // 16kB of data

// 64 bits of memory, last 16 bits help align OBJ_ATTR WITH OBJ_AFFINE,
// since these data structures overlap
typedef struct
{
	u16_t attr0;
	u16_t attr1;
	u16_t attr2;
	u16_t fill;
} ALIGN_WORD OBJ_ATTR_t;

typedef struct
{
	COLOR_t colors[16];
} PALETTE_t;

typedef struct WIN_CORNERS_t
{
	u8_t left, top, right, bottom;
} WIN_CORNERS_t;

#endif // __TYPES__
