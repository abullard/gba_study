#ifndef __INPUT__
#define __INPUT__

#include "helpers.h"
#include "masks.h"

#define REG_BUTTONMASK *(vu16 *)(MEM_IO + 0x0130)

u16 __key_curr, __key_prev;

static inline void inputPolling()
{
    // we're saving transitional state with this as well
    __key_prev = __key_curr;

    // register bits go low when button is pressed. So invert and mask with 1's
    __key_curr = ~REG_BUTTONMASK & KEY_MASK;
}

static inline u16 keyCurrentState()
{
    return __key_curr;
}

static inline u16 keyPreviousState()
{
    return __key_prev;
}

static inline u16 keyIsDown(u16 key)
{
    return __key_curr & key;
}

static inline u16 keyIsUp(u16 key)
{
    return ~__key_curr & key;
}

static inline u16 keyWasDown(u16 key)
{
    return __key_prev & key;
}

static inline u16 keyWasUp(u16 key)
{
    return ~__key_prev & key;
}

// key is moving down
static inline u16 keyTransit(u16 key)
{
    // this is an XOR, if it was down in one, but not in the other
    // we've changed state
    return (__key_prev ^ __key_curr) & key;
}

// key was pressed in prev and is currently pressed
static inline u16 keyHeld(u16 key)
{
    return (__key_prev & __key_curr) & key;
}

// key was just pressed this frame
static inline u16 keyHit(u16 key)
{
    return (~__key_prev & __key_curr) & key;
}

// key was just released this frame
static inline u16 keyReleased(u16 key)
{
    return (__key_prev & ~__key_curr) & key;
}

#endif // __INPUT__
