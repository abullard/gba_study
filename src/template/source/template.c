// source code I wrote
#include "input.h"
#include "types.h"
#include "helpers.h"
#include "registerAndMemoryLocations.h"
#include "masks.h"
#include "playerController.h"
#include "background.h"

OBJ_ATTR localOamBuffer[128];
u16 __key_curr, __key_prev;
BG_POINT bg0_pt = {0, 0};
BG_POINT bg2_pt = {0, 96};

void gameLoop()
{
	// OBJ_ATTR *player = initPlayer(localOamBuffer);

	while (1)
	{
		// vsync once per frame
		// vsync();
		// record input once per frame
		inputPolling();

		bg0_pt.x += keyTriHorz();
		bg2_pt.x += keyTriHorz();

		bg0_pt.y += keyTriVert();
		// REG_BG_OFS[0] = bg0_pt;
		REG_BG2HOFS = bg0_pt.x;

		// naive approach to parallax, also won't work as is.
		// if (delta(bg2_pt.y) < 10) {
		// 	REG_BG2HOFS = bg0_pt.x + 1;
		// }

		// handleMovement(player);

		// apparently we only need to update 1 or something?
		copyBufferToOam(oamRAM, localOamBuffer, 1);
	}
}

int main(void)
{
	initMap();

	REG_DISPCTL = DCNT_OBJ_1D | DCNT_OBJ | DCNT_BG2; //| DCNT_BG0 | DCNT_BG1;

	gameLoop();

	return 0;
}
