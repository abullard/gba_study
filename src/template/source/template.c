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

	OBJ_ATTR *playerSpriteOamLocation = getAttrsForTile(localOamBuffer, 0);

	setAttrsForTile(playerSpriteOamLocation,
					createObjectAttribute(
						ATTR0_OBJ_MODE_REGULAR | ATTR0_COLOR_MODE_8BPP, // square sprite
						ATTR1_SIZE_32x32,		// 32x32 pixel sprite
						pal_bank << 12 | tile_id));

	setTilePosition(playerSpriteOamLocation, start_x, start_y);

	while (1)
	{
		// vsync once per frame
		vsync();
		inputPolling();

		// apparently we only need to update 1 or something?
		copyBufferToOam(oamRAM, localOamBuffer, 1);
	}
}

int main(void)
{
	// let's load our graphic into memory
	// charblock 0-3 (tile_mem[0-3]) are for background data
	// charblock 4-5 (tile_mem[4-5]) are for sprite data
	memcpy(&tileVRAM[4][0], cat_playerTiles, cat_playerTilesLen);
	// sprites won't render if we don't load the palette
	memcpy(paletteVRAM, cat_playerPal, cat_playerPalLen);

	// set OAM to hide sprites at first
	oamInit(localOamBuffer);

	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ;

	gameLoop();

	return 0;
}
