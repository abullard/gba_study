// source code I wrote
#include "helpers.h"
#include "playerController/playerController.h"
#include "graphics/background.h"

#include <tonc.h>

OBJ_ATTR localOamBuffer_g[128];

void gameLoop()
{
	OBJ_ATTR *player = initPlayer(localOamBuffer_g);

	while (1)
	{
		// vsync once per frame
		vsync();
		// record input once per frame
		key_poll();
		
		skyboxParallax(); // does nothing right now, todo on func
		scrollPlatforms();

		handleMovement(player);

		// apparently we only need to update 1 or something?
		copyBufferToOam(oam_mem, localOamBuffer_g, 1);
	}
}

int main(void)
{
	initMap();

	REG_DISPCNT = DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2 | DCNT_BG1;

	gameLoop();

	return 0;
}
