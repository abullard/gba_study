//
// first.c
// "Hello World" equivalent
//
// (20030901 - 20060211, cearn)
// === NOTES ===
// * You are not expected to understand this. Check second.c for
//   a more proper version.

typedef unsigned int u32;
typedef unsigned short u16;
typedef u16 COLOR;
typedef volatile u32 vu32;
typedef struct
{
	int x, y;
} POINT;

#define IO_MEM_REG 0x04000000
#define MEM_VRAM 0x06000000

// #define REG_DISPCNT *(u32 *)(IO_MEM_REG + 0x0000) 			// DOES NOT WORK
#define REG_DISPCNT *(vu32 *)IO_MEM_REG // DOES WORK?
// AJB: volatile means it can change, so don't let the compiler pre-optimize
// non-volatile pointers

#define vid_mem ((COLOR *)MEM_VRAM)

#define MODE_3 0x0003
#define BG2 0x0400

#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

int main()
{
	// display mode 3, with background 2
	REG_DISPCNT = MODE_3 | BG2;

	int ix, iy;
	u16 clr = 0x001F;
	u16 *vram_start_loc = (COLOR *)(vid_mem);

	for (iy = 0; iy < SCREEN_HEIGHT; iy++)
	{
		for (ix = 0; ix < SCREEN_WIDTH; ix++)
		{
			*vram_start_loc++ = clr;
		}
	}

	// drawPixel(120, 80, 0x001F);
	// drawPixel(136, 80, 0x03E0);
	// drawPixel(120, 96, 0x7C00);

	while (1)
	{
	};

	return 0;
}
