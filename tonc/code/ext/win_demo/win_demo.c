//
// win_demo.c
// Playing hide and seek with a rocket item
// using windowing
//
// (20040104 - 20060926, cearn)
// === NOTES ===
//   bg 0, cbb  0, sbb  2, pb 0: numbered forground
//   bg 1, cbb  0, sbb  3, pb 0: fenced background
//   oam 0: tile 0-3: rocket

//   win 0: objects
//   win 1: bg 0
//   win out : bg 1

#include <tonc.h>
#include "nums.h"
#include "rocket.h"

#define ROCKET_OID 0

// --- global buffers for window registers ---
// This will allow you to poke them inside IWRAM,
// since you can't poke REG_WINx directly. :(

typedef struct tagRECT_U8
{
	u8 left, top, right, bottom;
} RECT_U8;

// Objects in win0, BG in win1
RECT_U8 win[2] = {
	// win0: 40x40 rect	
	// win0 is the black box that reveals stuff from behind BG0
	// left, top, right, bottom
	{36, 20, 76, 60},

	// win1: screen minus 12 margin.
	// 0 + 12, 0 + 12, 240 - 12, 160 - 12
	{12, 12, 228, 148}};

// foreground map is alternating numbered tile pattern
// is inside window 1
void init_front_map()
{
	int ii, jj;

	// copy our tileset and color palette
	memcpy32(&tile8_mem[0][1], nums8Tiles, nums8TilesLen / 4); // write 32 bits, 256 times from hex tiles to tileVRAM
	memcpy32(pal_bg_mem, numsPal, numsPalLen / 4);

	pal_bg_mem[0] = CLR_BLACK; // transparent color in palette 0 is black

	// screen entry for SBB(2) pointer in 16 bits
	u16 *pse = &se_mem[2][0];

	// populate the tileID on screen entry blocks for the whole screen
	// these blocks are the colored and numbered tiles on the background
	for (ii = 0; ii < 20; ii++)
	{
		for (jj = 0; jj < 32; jj++)
		{
			*pse++ = ((ii + jj) & 0x0F) + 1;
		}
	}
	REG_BG0CNT = BG_CBB(0) | BG_SBB(2) | BG_8BPP;
}

// fill a second background with a (not so) nice thread pattern
// is on outside
void init_back_map()
{
	// this creates the winOut tiles 4bpp (1 nibble) tiles
	const TILE back_tile =
		{{0x33123333, 0x33123333, 0x13213331, 0x21212112,
		  0x12121221, 0x33123332, 0x33213333, 0x33213333}};

	// 1 charblock is 16kB, s-tiles are 32B, so 512 possible s-tiles (@ 4bpp)
	// 1 charblock is 16kB, d-tiles are 64B, so 256 possible d-tiles (@ 8bpp)
	// I think 48 was choosen at random to be above the 32 d-tiles
	tile_mem[BG_CBB(0)][0x30] = back_tile;

	// looks like we can index into palette mem with nibbles?
	// could also use ints with 33, 34, 35. hex is way less readable, but forces 16 bits
	pal_bg_mem[0x21] = 0x09BA;
	pal_bg_mem[0x22] = 0xC0DE;
	pal_bg_mem[0x23] = 0x0015;

	// tile 0x30, pal-bank 2 written to screen entry as 0010 0000 0011 0000
	u32 ses = 0x30 | SE_PALBANK(2);
	// final value after these bitops is 2C30:2030h
	// 32 bits is two 16 bit screen entries, one is h/v flipped, one is not. Put these side by side for grid
	ses |= (ses | SE_HFLIP | SE_VFLIP) << 16;

	// 320 times, copy 32 bits from ses to screen entry mem (VRAM) SBB(3) for background.
	// I think this fills the whole screen, but the window work hides the center of it
	memset32(&se_mem[3][0], ses, 32 * 20 / 2);

	// tell background 1 to use charblock 0 and screen entry base block 3 for tiles
	REG_BG1CNT = BG_CBB(0) | BG_SBB(3);
}

// rocket is inside window 0
void init_rocket()
{
	// AJB: nothing we're doing here relates to window 0, comment above is misleading
	memcpy32(&tile_mem[4][0], rocketTiles, rocketTilesLen / 4);	 // put the missile expansion sprite into obj VRAM
	memcpy32(pal_obj_mem, rocketPal, rocketPalLen / 4);

	OBJ_ATTR *rocket = &oam_mem[ROCKET_OID];
	obj_set_attr(rocket, ATTR0_SQUARE, ATTR1_SIZE_16, 0);
	obj_set_pos(rocket, 96, 32);
}

void win_copy()
{
	// take the right value and place it in the first 2 nibbles, take the left 
	// window value and place it in the upper two nibbles. this matches integer format of window size registers
	// horizontal window values
	REG_WIN0H = win[0].left << 8 | win[0].right;
	REG_WIN1H = win[1].left << 8 | win[1].right;
	// vertical window values
	REG_WIN0V = win[0].top << 8 | win[0].bottom;
	REG_WIN1V = win[1].top << 8 | win[1].bottom;
}

void test_win()
{
	win_copy();
	while (1)
	{
		key_poll();
		vid_vsync();

		// key_hit() or key_is_down() 'switch'
		// A depressed: move on direction press (std movement)
		// A pressed  : moves on direction hit (fine movement)
		int keys = key_curr_state();
		if (key_is_down(KEY_A))
			keys &= ~key_prev_state();

		if (keys & KEY_RIGHT)
		{
			win[0].left++;
			win[0].right++;
		}
		else if (keys & KEY_LEFT)
		{
			win[0].left--;
			win[0].right--;
		}
		if (keys & KEY_DOWN)
		{
			win[0].top++;
			win[0].bottom++;
		}
		else if (keys & KEY_UP)
		{
			win[0].top--;
			win[0].bottom--;
		}

		// randomize rocket position
		if (key_hit(KEY_START))
			obj_set_pos(&oam_mem[ROCKET_OID],
						qran_range(0, 232), qran_range(0, 152));

		win_copy();
	}
}

int main()
{
	// obvious inits
	oam_init(oam_mem, 128);
	init_front_map();
	init_back_map();
	init_rocket();

	// windowing inits
	win_copy();
	// we've loaded our window sizes into their respective registers, go ahead and enable windows 0 & 1
	REG_DISPCNT = DCNT_BG0 | DCNT_BG1 | DCNT_OBJ |
				  DCNT_OBJ_1D | DCNT_WIN0 | DCNT_WIN1;


	// winIn is stuff inside our win0 and win1, which is bg0 and objs
	// winOut is everything else, in this case bg1.
	REG_WININ = WININ_BUILD(WIN_OBJ, WIN_BG0); // from gbatek: Inside of Window 0 and 1
	REG_WINOUT = WINOUT_BUILD(WIN_BG1, 0);	// from gbatek: Inside of OBJ Window & Outside of Windows
	// NOTE: these work like REG_DISPCNT, you have to enable the bits in the register mask for winIn 
	// to render those layers. i.e. if I don't include DCNT_BG0 while setting REG_DISPCNT, bg0 won't render.
	// if I don't include WIN_BG0 while setting REG_WININ, the inside of my windows won't render bg0.
	// this is the meat of how you include/exclude layers from your windows

	test_win();

	return 0;
}
