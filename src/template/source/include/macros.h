#ifndef __MACROS__
#define __MACROS__

#define WIN_BUILD(low, high) \
    (((high) << 8) | (low))
#define WININ_BUILD(win0, win1) WIN_BUILD(win0, win1)
#define WINOUT_BUILD(out, obj) WIN_BUILD(out, obj)

#define BG_CBB_SHIFT 2
#define BG_CBB(n) ((n) << BG_CBB_SHIFT)

#define BG_SBB_SHIFT 8
#define BG_SBB(n) ((n) << BG_SBB_SHIFT)

#define FIXED_POINT_SHIFT 16
#define GET_FIXEDP_INT(n) ((n) >> FIXED_POINT_SHIFT)
#define GET_FIXEDP_FRAC(n) ((u16)n)

// AJB: we use the currMask & 1's complmenet (~) of name##_MASK for the bits we care about to set all bits we want to
// change to 0, while leaving the rest of the currMask intact. i.e. currMask & ~(0100) => currMask & 1011 => 0001
// Then we OR with the bitsToUse, which will toggle all the bits we care about to whatever bitsToUse is.
#define BITFIELD_SHIFT(bitsToUse, name) ((bitsToUse << name##_SHIFT) & name##_MASK)
#define BITFIELD_SET(currMask, bitsToUse, name) (currMask = (currMask & ~name##_MASK) | BITFIELD_SHIFT(bitsToUse, name))

#define ATTR0_POS_Y(n) ((n) << ATTR0_POS_Y_SHIFT)

#define ATTR1_POS_X(n) ((n) << ATTR1_POS_X_SHIFT)
#define ATTR1_HFLIP(n) ((n) << ATTR1_HFLIP_SHIFT)

#endif // __MACROS__
