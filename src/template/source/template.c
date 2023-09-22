// sprites
#include "cat_player.h"

// source code I wrote
#include "input.h"
#include "types.h"
#include "helpers.h"
#include "registerAndMemoryLocations.h"
#include "masks.h"
#include "tiles.h"
#include "playerController.h"

// C includes
#include <string.h>

OBJ_ATTR localOamBuffer[128];
u16 __key_curr, __key_prev;

void gameLoop()
{
	OBJ_ATTR *player = initPlayer(localOamBuffer);

	while (1)
	{
		// vsync once per frame
		vsync();
		// record input once per frame
		inputPolling();

		handleMovement(player);

		// apparently we only need to update 1 or something?
		copyBufferToOam(oamRAM, localOamBuffer, 1);
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
