//
// toolbox.c
//
// Tools source for obj_demo
//
// (20060922-20060924, cearn)
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can
//   be found in tonclib, and might not represent the
//   final forms.

#include "toolbox.h"

// === (tonc_core.c) ==================================================

u16 __key_curr = 0, __key_prev = 0;

// === (tonc_oam.c) ===================================================

// this sets all the attr0 8-9 bits to 10, this hides them from the display.
// ZEROING out attr0 DOES NOT GIVE YOU A BLANK SCREEN. Instead it 8x8 sprites, using
// tile 0 for their graphics located at (0,0)
void oam_init(OBJ_ATTR *obj, u32 count)
{
	// 128 times, because that's how large our obj_buffer is
	u32 i = count;
	// u32 is 32 bits or 4 bytes, so dst++ moves us one chunk (chunk is scoped to this var. and is 4 bytes) 
	// ahead
	u32 *dst = (u32 *)obj;

	// Hide each object
	while (i--)
	{
		// write the first 4 bytes or 32 bits of our 64 bit struct. this covers attr0 and attr1
		// remember that writing 00000001 00000000 (0x0200, ATTR0_HIDE) hides the sprite from rendering
		*dst++ = ATTR0_HIDE;

		// write the second 4 bytes of our 64 bit struct
		// this covers attr2 and fill
		*dst++ = 0;
	}

	// init oam, i.e. write our OBJ_ATTR data to the 0x07000000 addr on the gba. This is how we tell the gba
	// to render the metroid data we placed in MEM_VRAM
	oam_copy(oam_mem, obj, count);
}

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count)
{

// NOTE: while struct-copying is the Right Thing to do here,
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
	while (count--)
		*dst++ = *src++;
#else
	u32 *dstw = (u32 *)dst, *srcw = (u32 *)src;
	while (count--)
	{
		*dstw++ = *srcw++;
		*dstw++ = *srcw++;
	}
#endif
}

void obj_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count)
{
	int ii;
	for (ii = 0; ii < count; ii++)
	{
		dst[ii].attr0 = src[ii].attr0;
		dst[ii].attr1 = src[ii].attr1;
		dst[ii].attr2 = src[ii].attr2;
	}
}
