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
const u32 __loc_oam_buf_size = 128;

// === (tonc_oam.c) ===================================================

void oam_init(OBJ_ATTR *obj)
{
	u32 i = __loc_oam_buf_size;	// 128 times, because that's how large our obj_buffer is
	u32 *dst = (u32 *)obj;	// u32 is 4 bytes, so dst++ moves us 4 bytes ahead of where we're currently pointing 

	while (i--)
	{
		// writing 00000001 00000000 = 0x0200 = ATTR0_HIDE to OAM hides the sprite from rendering
		*dst++ = ATTR0_HIDE;	// write the first 4 bytes of our 64 bit struct. this covers attr0 and attr1
		*dst++ = 0;				// write the second 4 bytes of our 64 bit struct, this covers attr2 and fill
	}

	// init oam, i.e. write our OBJ_ATTR data to the 0x07000000 addr on the gba. This is how we tell the gba
	// to render the metroid data we placed in MEM_VRAM. Since we're not using bit mask mode, we have to 
	// explicitly tell OAM to render
	oam_copy(oam_mem, obj, __loc_oam_buf_size);
}

void oam_copy(OBJ_ATTR *dst, const OBJ_ATTR *src, u32 count)
{
	u32 i = count;
// NOTE: while struct-copying is the Right Thing to do here,
//   there's a strange bug in DKP that sometimes makes it not work
//   If you see problems, just use the word-copy version.
#if 1
	while (i--)
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
