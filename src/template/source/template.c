// source code I wrote
#include "input.h"
#include "helpers.h"
#include "playerController/playerController.h"
#include "graphics/background.h"
#include "defines/types.h"
#include "defines/registerAndMemoryLocations.h"
#include "defines/masks.h"

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

		skyboxParallax(); // does nothing right now, todo on func
		scrollPlatforms();

		handleMovement(player);

		// apparently we only need to update 1 or something?
		copyBufferToOam(oamRAM, localOamBuffer, 1);
	}
}

int main(void)
{
	initMap();

	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2 | DCNT_BG1;

	gameLoop();

	return 0;
}
