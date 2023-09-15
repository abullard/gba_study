//
//! \file txt_se2.c
//!   Screen entry text demo
//! \date 20051028 - 20060103
//! \author cearn
//
// === NOTES ===

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <tonc.h>

#define LEGACY_TEXT_V11
#include <tonc_legacy.h>

#include "gba_pic.h"

// --------------------------------------------------------------------
// CONSTANTS & STRUCTS
// --------------------------------------------------------------------

int gtimes[5];

const char *strs[5] =
	{"u16 array", "u32 array", "memcpy", "memcpy32", "DMA32"};

// hw : 674978, 260299, 195171, 86846, 76902
// no$: 672162, 259309, 194608, 85283, 76901
// vba: 557081, 192183, 160367, 80049,   222

// --------------------------------------------------------------------
// FUNCTIONS
// --------------------------------------------------------------------

// copy via u16 array
void test_0(u16 *dst, const u16 *src, u32 len)
{
	u32 i;
	// this is just a timer to see number of clock cycles it takes to complete this operation
	profile_start();

	// ...len is 38400 bytes, the number of bytes needed to get through src (the whole bitmap).
	// len / 2 is the number of iters needed to write src to VRAM in halfword aligned chunks.
	// Stated differently, it takes 19200 iters to write 2 bytes of data at a time from src to VRAM.
	// Which will end up being 38400 bytes.
	for (i = 0; i < len / 2; i++)
		dst[i] = src[i];

	// this stops the timer
	gtimes[0] = profile_stop();
}

// copy via u32 array
void test_1(u32 *dst, const u32 *src, u32 len)
{
	u32 i;
	profile_start();

	// down here we divide 38400 by 4, which is 9600 iters to write all 38400 bytes of data
	// to VRAM in 4 byte chunks. This saves %160 operation cost or whatever tonc said
	for (i = 0; i < len / 4; i++)
		// indexing into src like this is explained as follows: src[0] will be 32 bits of data from 0..31
		// the mem addr of src, src[1] is 32...63 bits of data. This is COMPLETELY DEPENDENT ON THE SIZE
		// OF THE POINTER TO THE DATA
		dst[i] = src[i];
	gtimes[1] = profile_stop();
}

// copy via memcpy
void test_2(void *dst, const void *src, u32 len)
{
	profile_start();
	memcpy(dst, src, len);
	gtimes[2] = profile_stop();
}

// copy via my own memcpy32
void test_3(void *dst, const void *src, u32 len)
{
	profile_start();
	memcpy32(dst, src, len / 4);
	gtimes[3] = profile_stop();
}

// copy using DMA
void test_4(void *dst, const void *src, u32 len)
{
	profile_start();
	dma3_cpy(dst, src, len);
	
	gtimes[4] = profile_stop();
}

int main()
{
	irq_init(NULL);
	irq_add(II_VBLANK, NULL);

	// gba_picBitmapLen is gba_picBitmap length in bytes (9600 word entries at 4 bytes a piece), |gba_picBitmap| = 9600.
	// 9600 * 4 (bytes) = 38400... (continued in test_0)
	test_0((u16 *)vid_mem, (const u16 *)gba_picBitmap, gba_picBitmapLen);
	test_1((u32 *)vid_mem, (const u32 *)gba_picBitmap, gba_picBitmapLen);
	test_2(vid_mem, gba_picBitmap, gba_picBitmapLen);
	test_3(vid_mem, gba_picBitmap, gba_picBitmapLen);
	test_4(vid_mem, gba_picBitmap, gba_picBitmapLen);

	// clear the screenblock I'm about to use
	SBB_CLEAR(7);

	// init map text
	txt_init_std();
	txt_init_se(0, BG_SBB(7), 0, CLR_YELLOW, 0);

	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;

	// print results
	int i;
	char str[32];
	for (i = 0; i < 5; i++)
	{
		siprintf(str, "%12s %6d", strs[i], gtimes[i]);
		se_puts(8, 8 + 8 * i, str, 0);
	}

	while (1)
		VBlankIntrWait();

	return 0;
}
