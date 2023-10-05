//
// map_block1.c
// showing map-block boundaries regular backgrounds
//
// (20031114 - 20060317, Cearn)

#include "toolbox.h"
#include "input.h"

#define CBB_0 0
#define SBB_0 28

#define X_CENTER 15
#define Y_CENTER 10

BG_POINT bg1_pt= { 0, 0 };
SCR_ENTRY *bg0_map= se_mem[SBB_0];

// what do we need to find the SE index for???
// I think we can just black box this for now
u32 se_index(u32 tx, u32 ty, u32 pitch)
{
	u32 sbb = ((tx >> 5) + (ty >> 5) * (pitch >> 5));

	return sbb * 1024 + ((tx & 31) + (ty & 31) * 32);
}

// this sets up our background 0 using control, sets h and v offsets for screen pos on map
// and fills object palette memory with our tiles and colors. Also sets pal_bank on our screenblock screen entries
void init_map()
{
	int ii, jj;

	// initialize a background
	REG_BG0CNT = BG_CBB(CBB_0) | BG_SBB(SBB_0) | BG_REG_64x64;
	// set our offsets to be at (0,0)
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;

	// create the tiles: basic tile and a cross
	const TILE tiles[2] =
		{
			// the whole 8x8p obj is black, and adding a 1 fills it with the palettes color
			{{0x11111111, 0x01111111, 0x01111111, 0x01111111,
			  0x01111111, 0x01111111, 0x01111111, 0x00000001}},
			{{0x00000000, 0x00100100, 0x01100110, 0x00011000,
			  0x00011000, 0x01100110, 0x00100100, 0x00000000}},
		};

	// put the objects we just created as "TILES" into our characterblock base
	tile_mem[CBB_0][0] = tiles[0];
	tile_mem[CBB_0][1] = tiles[1];

	// create a palette
	pal_bg_bank[0][1] = RGB15(31, 0, 0);
	pal_bg_bank[1][1] = RGB15(0, 31, 0);
	pal_bg_bank[2][1] = RGB15(0, 0, 31);
	pal_bg_bank[3][1] = RGB15(16, 16, 16);

	// Create a map: four contingent blocks of
	//   0x0000, 0x1000, 0x2000, 0x3000.
	SCR_ENTRY *pse = bg0_map; // u16 pointer to se28 in VRAM
	for (ii = 0; ii < 4; ii++)
		for (jj = 0; jj < 32 * 32; jj++)
			// 4 screenblocks need palette IDs. set bits SE{C-F} in VRAM 6mil @ se28
			// this ALSO writes 0's to tileId of the screen-entry as well
			*pse++ = SE_PALBANK(ii) | 0;
}

int main()
{
	init_map();
	// setup the display
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_OBJ;

	// tx = 0 indexed, tile counted, center of x-axis of screen
	// ty = 0 indexed, tile counted, center of y-axis of screen
	u32 tx, ty, se_curr, se_prev = Y_CENTER * 32 + X_CENTER;

	bg0_map[se_prev]++; // initial position of cross
	while (1)
	{
		vid_vsync();

		key_poll();
		bg1_pt.x += key_tri_horz();
		bg1_pt.y += key_tri_vert();

		// Testing bg_se_id()
		// If all goes well the cross should be around the center of
		// the screen at all times.
		tx = ((bg1_pt.x >> 3) + X_CENTER) & 0x3F;
		ty = ((bg1_pt.y >> 3) + Y_CENTER) & 0x3F;

		// i think pitch is 64 here because there are 64 8x8 screen enteries,
		// and the player is an 8x8 screen entry. So instead of the pitch being in pixels, 
		// we're simplifying the math
		se_curr = se_index(tx, ty, 64);
		// se_curr is where the cross rests
		// se_prev is where the cross was resting
		if (se_curr != se_prev)
		{
			bg0_map[se_prev]--;	// 16b pointer to SE with cross, subtract one back to tile[0]
			bg0_map[se_curr]++;	// 16b pointer to SE that cross is moving to. Add one, moving to tile[1], so cross renders
			se_prev = se_curr;
		}

		REG_BG_OFS[0] = bg1_pt; // write new position
	}
	return 0;
}
