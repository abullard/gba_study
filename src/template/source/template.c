
#include "cat_player.h"
#include "template.h"
#include "input.h"

void gameLoop()
{
	while (1)
	{
		// vsync once per frame
		vsync();
		inputPolling();
	}
}

int main(void)
{
	// turn on object (tile) rendering in 1D mapping mode
	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ;

	// let's load our graphic into memory
	// charblock 0-3 (tile_mem[0-3]) are for background data
	// charblock 4-5 (tile_mem[4-5]) are for sprite data
	memcpy(&tileVRAM[4][0], cat_playerTiles, cat_playerTilesLen);
	// sprites won't render if we don't load the palette
	memcpy(paletteVRAM, cat_playerPal, cat_playerPalLen);

	// set OAM to hide sprites at first
	// AJB TODO:
	oamInit();

	gameLoop();

	return 0;
}
