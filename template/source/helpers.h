#ifndef __HELPERS__
#define __HELPERS__

#include <tonc.h>

void oamInit(OBJ_ATTR *);
void copyBufferToOam(OBJ_ATTR *, OBJ_ATTR *, u16);
OBJ_ATTR createObjectAttribute(u16, u16, u16);

static inline u32 _multiply(u32 multiplicand, u32 multiplier)
{
    u32 product = 0, i;

    for (i = 0; i < multiplier; i++)
    {
        product += multiplicand;
    }

    return product;
}

static inline u32 _log2(u32 value)
{
    u32 numBits = 0;
    while (value > 1)
    {
        numBits++;
        value >>= 1;
    }

    return numBits;
}

#endif // __HELPERS__
