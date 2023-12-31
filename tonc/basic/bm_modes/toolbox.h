//
// toolbox.h
// 
// Tools header for bm_modes
// 
// (20060211-20060922, cearn)
//
// === NOTES ===
// * This is a _small_ set of typedefs, #defines and inlines that can 
//   be found in tonclib, and might not represent the 
//   final forms.


#ifndef TOOLBOX_H
#define TOOLBOX_H

// === (tonc_types.h) ============================================

typedef unsigned char  u8,  byte;
typedef unsigned short u16, hword;
typedef unsigned int   u32, word;
typedef unsigned long long u64;

typedef signed char  s8;
typedef signed short s16; 
typedef signed int   s32;
typedef signed long long s64;

// and volatiles for registers 'n stuff
typedef volatile u8  vu8;
typedef volatile u16 vu16;
typedef volatile u32 vu32;
typedef volatile u64 vu64;

typedef volatile s8  vs8;
typedef volatile s16 vs16;
typedef volatile s32 vs32;
typedef volatile s64 vs64;

typedef u16 COLOR;

#define INLINE static inline

// === (tonc_memmap.h) ===========================================

#define MEM_IO		0x04000000
#define MEM_PAL		0x05000000		// no 8bit write !!
#define MEM_VRAM	0x06000000		// no 8bit write !!

#define PAL_SIZE		0x00400
#define VRAM_SIZE		0x18000

#define M3_SIZE			0x12C00
#define M4_SIZE			0x09600
#define M5_SIZE			0x0A000
#define VRAM_PAGE_SIZE	0x0A000


#define MEM_VRAM_BACK	(MEM_VRAM+ VRAM_PAGE_SIZE)

// --- memmap ---

// pal_bg_mem[y] = COLOR (color y)
#define pal_bg_mem		((COLOR*)MEM_PAL)

// vid_mem[a] = COLOR
#define vid_mem			((COLOR*)MEM_VRAM)

#define vid_mem_front	((COLOR*)MEM_VRAM)
#define vid_mem_back	((COLOR*)MEM_VRAM_BACK)


#define REG_BASE	MEM_IO

#define REG_DISPCNT			*(vu32*)(REG_BASE+0x0000)	// display control
#define REG_DISPSTAT		*(vu16*)(REG_BASE+0x0004)	// display interupt status
#define REG_VCOUNT			*(vu16*)(REG_BASE+0x0006)	// vertical count

#define REG_KEYINPUT		*(vu16*)(REG_BASE+0x0130)	// Key status


// === (tonc_memdef.h) =======================================----

// --- REG_DISPCNT ---
#define DCNT_MODE0				 0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-2: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap
#define DCNT_GB				0x0008	//!< (R) GBC indicator
#define DCNT_PAGE			0x0010	//!< Page indicator
#define DCNT_OAM_HBL		0x0020	//!< Allow OAM updates in HBlank
#define DCNT_OBJ_2D				 0	//!< OBJ-VRAM as matrix
#define DCNT_OBJ_1D			0x0040	//!< OBJ-VRAM as array
#define DCNT_BLANK			0x0080	//!< Force screen blank
#define DCNT_BG0			0x0100	//!< Enable bg 0
#define DCNT_BG1			0x0200	//!< Enable bg 1
#define DCNT_BG2			0x0400	//!< Enable bg 2
#define DCNT_BG3			0x0800	//!< Enable bg 3
#define DCNT_OBJ			0x1000	//!< Enable objects
#define DCNT_WIN0			0x2000	//!< Enable window 0
#define DCNT_WIN1			0x4000	//!< Enable window 1
#define DCNT_WINOBJ			0x8000	//!< Enable object window

#define DCNT_MODE_MASK		0x0007
#define DCNT_MODE_SHIFT			 0
#define DCNT_MODE(n)	   ((n)<<DCNT_MODE_SHIFT)

#define DCNT_LAYER_MASK		0x1F00
#define DCNT_LAYER_SHIFT		 8
#define DCNT_LAYER(n)	  ((n)<<DCNT_LAYER_SHIFT)

#define DCNT_WIN_MASK		0xE000
#define DCNT_WIN_SHIFT			13
#define DCNT_WIN(n)			((n)<<DCNT_WIN_SHIFT)

#define DCNT_BUILD(mode, layer, win, obj1d, objhbl)				\
(																\
		(((win)&7)<<13) | (((layer)&31)<<8) | (((obj1d)&1)<<6)	\
	| (((oamhbl)&1)<<5) | ((mode)&7)							\
)


// --- REG_KEYINPUT ---

#define KEY_A			0x0001	//!< Button A
#define KEY_B			0x0002	//!< Button B
#define KEY_SELECT		0x0004	//!< Select button
#define KEY_START		0x0008	//!< Start button
#define KEY_RIGHT		0x0010	//!< Right D-pad
#define KEY_LEFT		0x0020	//!< Left D-pad
#define KEY_UP			0x0040	//!< Up D-pad
#define KEY_DOWN		0x0080	//!< Down D-pad
#define KEY_R			0x0100	//!< Shoulder R
#define KEY_L			0x0200	//!< Shoulder L

#define KEY_ANY			0x03FF	//!< any key
#define KEY_DIR			0x00F0	//!< any-dpad
#define KEY_ACCEPT		0x0009	//!< A or start
#define KEY_CANCEL		0x0002	//!< B (well, it usually is)
#define KEY_SHOULDER	0x0300	//!< L or R

#define KEY_RESET		0x000F	//!< St+Se+A+B

#define KEY_MASK		0x03FF

// === (tonc_core.h) =============================================

extern COLOR *vid_page;
extern u16 __key_curr, __key_prev;

// === (tonc_input.h) ============================================

// --- Synchronous key states ---
INLINE void key_poll();
INLINE u32 key_curr_state();
INLINE u32 key_prev_state();

INLINE u32 key_is_down(u32 key);	// any of key currently down?

INLINE u32 key_hit(u32 key);		// any of key being hit (going down)?


// === (tonc_math.h) =============================================

INLINE int clamp(int x, int min, int max);
INLINE int reflect(int x, int min, int max);
INLINE int wrap(int x, int min, int max);


// === (tonc_video.h) ============================================

// --- sizes ---
#define SCREEN_WIDTH	240
#define SCREEN_HEIGHT	160

#define M3_WIDTH	SCREEN_WIDTH
#define M3_HEIGHT	SCREEN_HEIGHT
#define M4_WIDTH	SCREEN_WIDTH
#define M4_HEIGHT	SCREEN_HEIGHT
#define M5_WIDTH	160
#define M5_HEIGHT	128

// --- colors ---

#define CLR_BLACK	0x0000
#define CLR_RED		0x001F
#define CLR_LIME	0x03E0
#define CLR_YELLOW	0x03FF
#define CLR_BLUE	0x7C00
#define CLR_MAG		0x7C1F
#define CLR_CYAN	0x7FE0
#define CLR_WHITE	0x7FFF

INLINE void vid_vsync();
u16 *vid_flip();

INLINE COLOR RGB15(u32 red, u32 green, u32 blue);


INLINE void m3_plot(int x, int y, COLOR clr);
INLINE void m4_plot(int x, int y, u8 clrid);
INLINE void m5_plot(int x, int y, COLOR clr);

// === INLINES ========================================================

// --- (tonc_input.h) -------------------------------------------------

//! Poll for keystates
INLINE void key_poll()
{	__key_prev= __key_curr;	__key_curr= ~REG_KEYINPUT & KEY_MASK;	}

//! Get current key state
INLINE u32 key_curr_state()			{	return __key_curr;			}

//! Get previous key state
INLINE u32 key_prev_state()			{	return __key_prev;			}

//! Gives the keys of \a key that are currently down
INLINE u32 key_is_down(u32 key)		{	return  __key_curr & key;	}

//! Gives the keys of \a key that are pressed (down now but not before)
INLINE u32 key_hit(u32 key)
{	return (__key_curr&~__key_prev) & key;	}


// --- (tonc_math.h) --------------------------------------------------

//! Truncates \a x to stay in range [\a min, \a max>
/*!	\return Truncated value of \a x.
*	\note	\a max is exclusive!
*/
INLINE int clamp(int x, int min, int max)
{	return (x>=max) ? (max-1)		: ( (x<min) ? min		: x );		}

//! Reflects \a x at boundaries \a min and \a max
/*! If \a x is outside the range [\a min, \a max>, 
*	  it'll be placed inside again with the same distance 
*	  to the 'wall', but on the other side. Example for lower 
*	  border: y = \a min - (\a x- \a min)  = 2*\a min + \a x.
*	\return	Reflected value of \a x.
*	\note	\a max is exclusive!
*/
INLINE int reflect(int x, int min, int max)
{	return (x>=max) ? (2*(max-1)-x)	: ( (x<min) ? (2*min-x) : x );		}

//! Wraps \a x to stay in range [\a min, \a max>
INLINE int wrap(int x, int min, int max)
{	return (x>=max) ? (x+min-max)	: ( (x<min) ? (x+max-min) : x );	}


// --- (tonc_video.h) -------------------------------------------------

//! Wait for next VBlank
INLINE void vid_vsync()
{
	while(VERT_DRAW_COUNT >= 160);	// wait till VDraw
	while(VERT_DRAW_COUNT < 160);	// wait till VBlank
}

//! Create a 15bit BGR color.
INLINE COLOR RGB15(u32 red, u32 green, u32 blue)
{	return red | (green<<5) | (blue<<10);	}

//! Plot a single \a clr colored pixel in mode 3 at (\a x, \a y).
INLINE void m3_plot(int x, int y, COLOR clr)
{	vid_mem[y*SCREEN_WIDTH+x]= clr;	}


//! Plot a \a clrid pixel on the current mode 4 backbuffer
INLINE void m4_plot(int x, int y, u8 clrid)
{
	u16 *dst= &vid_page[(y*M4_WIDTH+x)>>1];
	if(x&1)
		*dst= (*dst& 0xFF) | (clrid<<8);
	else
		*dst= (*dst&~0xFF) | clrid;
}

//! Plot a \a clrid pixel on the current mode 5 backbuffer
INLINE void m5_plot(int x, int y, COLOR clr)
{	vid_page[y*M5_WIDTH+x]= clr;	}


#endif // TOOLBOX_H

