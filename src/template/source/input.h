#ifndef __INPUT__
#define __INPUT__

#include "helpers.h"
#include "masks.h"

extern u16 __key_curr, __key_prev;

static inline void inputPolling();
static inline u32 keyCurrentState();
static inline u32 keyPreviousState();

static inline u32 keyIsDown(u32 key); // any of key currently down?
static inline u32 keyIsUp(u32 key);	 // any of key currently up?

static inline u32 keyWasDown(u32 key); // any of key previously down?
static inline u32 keyWasUp(u32 key);	  // any of key previously up?

static inline u32 keyTransit(u32 key);  // any of key changing?
static inline u32 keyHeld(u32 key);	  // any of key held down?
static inline u32 keyHit(u32 key);	  // any of key being hit (going down)?
static inline u32 keyReleased(u32 key); // any of key being released?

static inline void inputPolling()
{
    // we're saving transitional state with this as well
    __key_prev = __key_curr;

    // register bits go low when button is pressed. So invert and mask with 1's
    __key_curr = ~REG_BUTTONMASK & KEY_MASK;
}

static inline u32 keyCurrentState()
{
    return __key_curr;
}

static inline u32 keyPreviousState()
{
    return __key_prev;
}

static inline u32 keyIsDown(u32 key)
{
    return __key_curr & key;
}

static inline u32 keyIsUp(u32 key)
{
    return ~__key_curr & key;
}

static inline u32 keyWasDown(u32 key)
{
    return __key_prev & key;
}

static inline u32 keyWasUp(u32 key)
{
    return ~__key_prev & key;
}

// key is moving down
static inline u32 keyTransit(u32 key)
{
    // this is an XOR, if it was down in one, but not in the other
    // we've changed state
    return (__key_prev ^ __key_curr) & key;
}

// key was pressed in prev and is currently pressed
static inline u32 keyHeld(u32 key)
{
    return (__key_prev & __key_curr) & key;
}

// key was just pressed this frame
static inline u32 keyHit(u32 key)
{
    return (~__key_prev & __key_curr) & key;
}

// key was just released this frame
static inline u32 keyReleased(u32 key)
{
    return (__key_prev & ~__key_curr) & key;
}

#endif // __INPUT__
