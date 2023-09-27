#ifndef __INPUT__
#define __INPUT__

// === CONSTANTS ======================================================

typedef enum eKeyIndex
{
	KI_A = 0,
	KI_B,
	KI_SELECT,
	KI_START,
	KI_RIGHT,
	KI_LEFT,
	KI_UP,
	KI_DOWN,
	KI_R,
	KI_L,
	KI_MAX
} eKeyIndex;

// === GLOBALS ========================================================

extern u16 __key_curr, __key_prev; // in tonc_core.c

// === PROTOTYPES =====================================================

// --- synchronous key states ---
INLINE void key_poll();

// --- tribools ---
INLINE int key_tri_horz();
INLINE int key_tri_vert();

// === INLINES=========================================================

// --- keys -----------------------------------------------------------

//! Poll for keystates
INLINE void key_poll()
{
	__key_prev = __key_curr;
	__key_curr = ~REG_KEYINPUT & KEY_MASK;
}

//! Horizontal tribool (right,left)=(+,-)
INLINE int key_tri_horz()
{
	return bit_tribool(__key_curr, KI_RIGHT, KI_LEFT);
}

//! Vertical tribool (down,up)=(+,-)
INLINE int key_tri_vert()
{
	return bit_tribool(__key_curr, KI_DOWN, KI_UP);
}

#endif // __INPUT__
