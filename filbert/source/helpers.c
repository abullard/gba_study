#include "helpers.h"

u16 __loc_oam_buf_size = 128;

// set all tile's object attribute memory to nothing but a hidden sprite.
// this is accomplished by writing base-2 10 to bits 8-9 of attr0
void oamInit(OBJ_ATTR *localOamBuffer)
{
    u32 i = __loc_oam_buf_size;
    u32 *ptrToLocalBuffer = (u32 *)localOamBuffer;

    while (i--)
    {
        *ptrToLocalBuffer++ = ATTR0_HIDE; // write first 32 bits of data to localOamBuffer includes `10`
        *ptrToLocalBuffer++ = 0;                   // write an empty second set of bits to localOamBuffer
    }

    copyBufferToOam(oam_mem, localOamBuffer, __loc_oam_buf_size);
}

void copyBufferToOam(OBJ_ATTR *destination, OBJ_ATTR *localBuffer, u16 count)
{
    u32 i = count;

#if 1
    while (i--)
    {
        *destination++ = *localBuffer++;
    }
#else
    u32 *dstw = (u32 *)dst, *srcw = (u32 *)src;
    while (count--)
    {
        *dstw++ = *srcw++;
        *dstw++ = *srcw++;
    }
#endif
}

OBJ_ATTR createObjectAttribute(u16 a0, u16 a1, u16 a2)
{
    OBJ_ATTR objectAttributes;
    objectAttributes.attr0 = a0;
    objectAttributes.attr1 = a1;
    objectAttributes.attr2 = a2;
    // the last u16 is filler to align with OBJ_AFFINE

    return objectAttributes;
}
