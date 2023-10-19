#ifndef __MACROS__
#define __MACROS__

#define FIXED_POINT_SHIFT 16
#define GET_FIXEDP_INT(n) ((n) >> FIXED_POINT_SHIFT)
#define GET_FIXEDP_FRAC(n) ((u16)n)

#endif // __MACROS__
