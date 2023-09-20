#include "cat_player.h"
#include "input.h"
#include "types.h"
#include "helpers.h"
#include "registerAndMemoryLocations.h"
#include "masks.h"

#include <string.h>

OBJ_ATTR localOamBuffer[128];

void gameLoop()
{
	// straight up just stole this from tonc
	int start_x = 96, start_y = 32;
	u32 tile_id = 0, pal_bank = 0;

	OBJ_ATTR *playerSpriteOamLocation = getAttrForTile(localOamBuffer, 0);
	
	// TODO AJB: remove these hardcoded values
	OBJ_ATTR playerAttrs;
	playerAttrs.attr0 = 0;	// square sprite
	playerAttrs.attr1 = 0x8000;	// 32x32 pixel sprite 
	playerAttrs.attr2 = pal_bank << 12 | tile_id;

	setAttrForTile(playerSpriteOamLocation, playerAttrs);

	

	while (1)
	{
		// vsync once per frame
		vsync();
		inputPolling();
	}
}


int main(void)
{
 	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ;

	// let's load our graphic into memory
	// charblock 0-3 (tile_mem[0-3]) are for background data
	// charblock 4-5 (tile_mem[4-5]) are for sprite data
	memcpy(&tileVRAM[4][0], cat_playerTiles, cat_playerTilesLen);
	// sprites won't render if we don't load the palette
	memcpy(paletteVRAM, cat_playerPal, cat_playerPalLen);

	// set OAM to hide sprites at first
	oamInit(localOamBuffer);

	gameLoop();

	return 0;
}
