//
// toolbox.c
// 
// Tools source for pageflip
// 
// (20060922-20060922, cearn)
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can 
//   be found in tonclib, and might not represent the 
//   final forms.

#include "toolbox.h"

// === (tonc_core.c) ==================================================

COLOR *vid_page= vid_mem_back;


// === (tonc_bitmap.c) ================================================

void vid_flip()
{

	// when vid_page is a global, this sets vid_page to point to the back frame, so we can modify it's contents
	vid_page= (COLOR*)((u32)vid_page ^ VRAM_PAGE_SIZE);

	// this XOR between the data in REG_DISPCTL and 0x0010 or 16 in binary 10000 is a bitmask to flip 
	// the currently displayed frame from 0 to 1, bitmask after operation is:
	// 10000010100, MODE_4, BG_2, FRAME_1
	REG_DISPCNT ^= DCNT_PAGE;	// update control register	
}
