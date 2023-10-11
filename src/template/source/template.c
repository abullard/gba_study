// source code I wrote
#include "include/input.h"
#include "helpers.h"
#include "playerController/playerController.h"
#include "graphics/background.h"
#include "include/types.h"
#include "include/registerAndMemoryLocations.h"
#include "include/masks.h"

OBJ_ATTR_t localOamBuffer_g[128];

void gameLoop()
{
	OBJ_ATTR_t *player = initPlayer(localOamBuffer_g);

	while (1)
	{
		// vsync once per frame
		vsync();
		// record input once per frame
		inputPolling();

		skyboxParallax(); // does nothing right now, todo on func
		scrollPlatforms();

		handleMovement(player);

		// apparently we only need to update 1 or something?
		copyBufferToOam(oamRAM, localOamBuffer_g, 1);
	}
}

int main(void)
{
	initMap();

	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2 | DCNT_BG1;

	gameLoop();

	return 0;
}
