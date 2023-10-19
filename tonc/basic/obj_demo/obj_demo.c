//
// obj_demo.c
// testing various sprite related things
//
// (20031003 - 20060924, Cearn)

#include <string.h>
#include "toolbox.h"
#include "metr.h"

// OAM is 1kb long, or 1024 bytes. so 128 entries at 8 bytes a piece is 1024 bytes
// basically, obj_buffer covers the entire OAM for us. 
OBJ_ATTR obj_buffer[128];
OBJ_AFFINE *obj_aff_buffer = (OBJ_AFFINE *)obj_buffer;
u16 __key_curr, __key_prev;


// testing a few sprite things
// D-pad: move
// SELECT: switch palette
// START: toggle mapping mode
// A: horizontal flip
// B: vertical flip
// L & R shift starting tile
void gameLoop()
{
	int start_x = 96, start_y = 32;
	u32 tile_id = 0, pal_bank = 0; // tile id, pal-bank

	// & returns actual address of the variable, seems the idea here is to
	// create an obj_attr sized pointer to the starting address of our obj_buffer, then set the 
	// actual obj_attr data for our metroid sprite. this does not copy to 7mil OAM though
	OBJ_ATTR *metroid = &obj_buffer[0];
	// if you wanted to set other properties of obj_attr 0, 1, or 2 you could use bitwise operators on 
	// the params of obj_set_attr()
	obj_set_attr(metroid,
				 ATTR0_SQUARE,			   // Square, regular sprite
				 ATTR1_SIZE_64,			   // 64x64p,
				 ATTR2_PALBANK(pal_bank) | tile_id); // palbank 0, tile 0

	// position sprite (redundant here; the _real_ position
	// is set further down
	obj_set_pos(metroid, start_x, start_y);

	while (1)
	{
		// wait for next vblank to give us processing time
		vid_vsync();

		// GOTTA GO FAST
		// all this does is check what keys are pressed, and then records button transition data into a buffer
		key_poll();

		// move left/right
		start_x += 2 * key_tri_horz();

		// move up/down
		start_y += 2 * key_tri_vert();

		// increment/decrement starting tile with R/L
		tile_id += bit_tribool(key_hit(-1), KI_R, KI_L);

		// flip
		if (key_hit(KEY_A)) // horizontally
			metroid->attr1 ^= ATTR1_HFLIP;
		if (key_hit(KEY_B)) // vertically
			metroid->attr1 ^= ATTR1_VFLIP;

		// make it glow (via palette swapping)
		pal_bank = key_is_down(KEY_SELECT) ? 1 : 0;

		// toggle mapping mode
		if (key_hit(KEY_START))
			REG_DISPCNT ^= DCNT_OBJ_1D;

		// Hey look, it's one of them build macros!
		metroid->attr2 = ATTR2_BUILD(tile_id, pal_bank, 0);
		obj_set_pos(metroid, start_x, start_y);

		// Woah! We did all of our gameLoop logic, let's go ahead and write our obj_attr changes to 
		// 7mil OAM now.
		oam_copy(oam_mem, obj_buffer, 1); // only need to update one
	}
}

int main()
{
	// Places the glyphs of a 4bpp (s-tile) boxed metroid sprite
	//   into LOW obj memory (charblock base, cbb == 4 which is sprite tiles in VRAM)
	memcpy(&tile_mem[4][0], metrTiles, metrTilesLen);
	// places BGR colors into 5mil block of palette RAM, without a palette, tiles will NOT render
	memcpy(pal_obj_mem, metrPal, metrPalLen);

	oam_init(obj_buffer);

	// 0x1000 | 0x0040 result: 0001000001000000, bit 6 is high (1D object mapping mode, tiles are sequential)
	// bit 12 (C) is high for rendering OBJ layer. 8, 9, A, & B are all low, meaning all backgrounds are off
	// mode 0 is used, which is a tiled mode
	REG_DISPCNT = DCNT_OBJ | DCNT_OBJ_1D;

	gameLoop();

	return 0;
}
