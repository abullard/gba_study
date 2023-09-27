// source code I wrote
#include "input.h"
#include "types.h"
#include "helpers.h"
#include "registerAndMemoryLocations.h"
#include "masks.h"
#include "playerController.h"

OBJ_ATTR localOamBuffer[128];
u16 __key_curr, __key_prev;

void initMap()
{
}

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
	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG0;

	gameLoop();

	return 0;
}
