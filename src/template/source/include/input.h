#ifndef __INPUT__
#define __INPUT__

#include "../helpers.h"
#include "masks.h"

extern u16_t __key_curr, __key_prev;

static inline void inputPolling();
static inline u32_t keyCurrentState();
static inline u32_t keyPreviousState();

static inline u32_t keyIsDown(u32_t key); // any of key currently down?
static inline u32_t keyIsUp(u32_t key);   // any of key currently up?

static inline u32_t keyWasDown(u32_t key); // any of key previously down?
static inline u32_t keyWasUp(u32_t key);   // any of key previously up?

static inline u32_t keyTransit(u32_t key);  // any of key changing?
static inline u32_t keyHeld(u32_t key);     // any of key held down?
static inline u32_t keyHit(u32_t key);      // any of key being hit (going down)?
static inline u32_t keyReleased(u32_t key); // any of key being released?

// stole this from tonc as well, 
// plus and minus pressed? return 0
// plus button pressed? return +1
// minus button pressed? return -1
static inline int bit_tribool(u32_t flags, int plus, int minus)
{
    return ((flags >> plus) & 1) - ((flags >> minus) & 1);
}

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

static inline void inputPolling()
{
    // we're saving transitional state with this as well
    __key_prev = __key_curr;

    // register bits go low when button is pressed. So invert and mask with 1's
    __key_curr = ~REG_BUTTONMASK & KEY_MASK;
}

static inline u32_t keyCurrentState()
{
    return __key_curr;
}

static inline u32_t keyPreviousState()
{
    return __key_prev;
}

static inline u32_t keyIsDown(u32_t key)
{
    return __key_curr & key;
}

static inline u32_t keyIsUp(u32_t key)
{
    return ~__key_curr & key;
}

static inline u32_t keyWasDown(u32_t key)
{
    return __key_prev & key;
}

static inline u32_t keyWasUp(u32_t key)
{
    return ~__key_prev & key;
}

// key is moving down
static inline u32_t keyTransit(u32_t key)
{
    // this is an XOR, if it was down in one, but not in the other
    // we've changed state
    return (__key_prev ^ __key_curr) & key;
}

// key was pressed in prev and is currently pressed
static inline u32_t keyHeld(u32_t key)
{
    return (__key_prev & __key_curr) & key;
}

// key was just pressed this frame
static inline u32_t keyHit(u32_t key)
{
    return (~__key_prev & __key_curr) & key;
}

// key was just released this frame
static inline u32_t keyReleased(u32_t key)
{
    return (__key_prev & ~__key_curr) & key;
}

static inline int keyTriHorz()
{
    return bit_tribool(__key_curr, KI_RIGHT, KI_LEFT);
}

//! Vertical tribool (down,up)=(+,-)
static inline int keyTriVert()
{
    return bit_tribool(__key_curr, KI_DOWN, KI_UP);
}

//! Shoulder-button tribool (R,L)=(+,-)
static inline int keyTriShoulder()
{
    return bit_tribool(__key_curr, KI_R, KI_L);
}

//! Fire-button tribool (A,B)=(+,-)
static inline int keyTriFire()
{
    return bit_tribool(__key_curr, KI_A, KI_B);
}

#endif // __INPUT__
