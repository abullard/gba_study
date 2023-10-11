#include "helpers.h"

u16_t __loc_oam_buf_size = 128;
u16_t __key_curr, __key_prev;

// set all tile's object attribute memory to nothing but a hidden sprite.
// this is accomplished by writing base-2 10 to bits 8-9 of attr0
void oamInit(OBJ_ATTR_t *localOamBuffer)
{
    u32_t i = __loc_oam_buf_size;
    u32_t *ptrToLocalBuffer = (u32_t *)localOamBuffer;

    while (i--)
    {
        *ptrToLocalBuffer++ = ATTR0_OBJ_MODE_HIDE; // write first 32 bits of data to localOamBuffer includes `10`
        *ptrToLocalBuffer++ = 0;                   // write an empty second set of bits to localOamBuffer
    }

    copyBufferToOam(oamRAM, localOamBuffer, __loc_oam_buf_size);
}

void copyBufferToOam(OBJ_ATTR_t *destination, OBJ_ATTR_t *localBuffer, u16_t count)
{
    u32_t i = count;

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

OBJ_ATTR_t createObjectAttribute(u16_t a0, u16_t a1, u16_t a2)
{
    OBJ_ATTR_t objectAttributes;
    objectAttributes.attr0 = a0;
    objectAttributes.attr1 = a1;
    objectAttributes.attr2 = a2;
    // the last u16 is filler to align with OBJ_AFFINE

    return objectAttributes;
}
