#ifndef __MASKS__
#define __MASKS__

#define KEY_MASK 0x03FF // 00000011 11111111 mask if all buttons were pressed
#define PAL_BG_SIZE 0x00200
#define DCNT_OBJ 0x1000    //!< Enable objects
#define DCNT_OBJ_1D 0x0040 //!< OBJ-VRAM as array
#define DCNT_BG0 0x0100    //!< OBJ-VRAM as array
#define DCNT_BG1 0x0200    //!< OBJ-VRAM as array
#define DCNT_BG2 0x0400    //!< OBJ-VRAM as array
#define DCNT_BG3 0x0800    //!< OBJ-VRAM as array

#define DCTL_BG_PRIORITY_FIRST 0x0000
#define DCTL_BG_PRIORITY_SECOND 0x0001
#define DCTL_BG_PRIORITY_THIRD 0x0002
#define DCTL_BG_PRIORITY_FOURTH 0x0003

// OBJ_ATTR.attr0{8-9} defines
#define ATTR0_OBJ_MODE_REGULAR 0x0000
#define ATTR0_OBJ_MODE_AFFINE 0x0100
#define ATTR0_OBJ_MODE_HIDE 0x0200
#define ATTR0_OBJ_MODE_AFFINE_DOUBLE 0x0300

// OBJ_ATTR.attr0{A-B} defines
#define ATTR0_GRAPHICS_MODE_NORMAL 0x0000
#define ATTR0_GRAPHICS_MODE_ALPHA_BLEND 0x0400
#define ATTR0_GRAPHICS_MODE_WINDOW 0x0800

// OBJ_ATTR.attr0{C} defines
#define ATTR0_MOSAIC 0x1000

// OBJ_ATTR.attr0{D} defines
#define ATTR0_COLOR_MODE_4BPP 0x0000
#define ATTR0_COLOR_MODE_8BPP 0x2000

// OBJ_ATTR.attr0{E-F} defines
#define ATTR0_SPRITE_SHAPE_SQUARE 0x0000
#define ATTR0_SPRITE_SHAPE_WIDE 0x4000
#define ATTR0_SPRITE_SHAPE_TALL 0x8000

// TODO AJB: to be frank, i don't know what these do yet.
#define ATTR0_POS_Y_MASK 0x00FF // attr0{0-7}, hence 0x00FF, 1111 1111
#define ATTR0_POS_Y_SHIFT 0x0000
#define ATTR1_POS_X_MASK 0x01FF // attr1{0-8}, hence 0x01FF, 0001 1111 1111
#define ATTR1_POS_X_SHIFT 0x0000

// OBJ_ATTR.attr1{12} defines
// if you want to turn off HFLIP just XOR it with itself
#define ATTR1_HORIZONTAL_FLIP 0x1
#define ATTR1_NO_HORIZONTAL_FLIP 0x0

#define ATTR1_HFLIP_MASK 0x1000
#define ATTR1_HFLIP_SHIFT 12 // shift 12 bits in to align with attr1

// OBJ_ATTR.attr1{13} defines
#define ATTR1_VERTICAL_FLIP 0x2000

// OBJ_ATTR.attr1{E-F} defines
// lot's of duplication here, but the actual names for the bit masks has a lot of value
// when there's a lot of sprites rendered with animations all over the place

// Base sizes
#define ATTR1_SIZE_8 0
#define ATTR1_SIZE_16 0x4000
#define ATTR1_SIZE_32 0x8000
#define ATTR1_SIZE_64 0xC000

// Square sizes
#define ATTR1_SIZE_8x8 0
#define ATTR1_SIZE_16x16 0x4000
#define ATTR1_SIZE_32x32 0x8000
#define ATTR1_SIZE_64x64 0xC000

// Tall sizes
#define ATTR1_SIZE_8x16 0
#define ATTR1_SIZE_8x32 0x4000
#define ATTR1_SIZE_16x32 0x8000
#define ATTR1_SIZE_32x64 0xC000

// Wide sizes
#define ATTR1_SIZE_16x8 0
#define ATTR1_SIZE_32x8 0x4000
#define ATTR1_SIZE_32x16 0x8000
#define ATTR1_SIZE_64x32 0xC000

// input button masks
#define KEY_A 0x0001      //!< Button A
#define KEY_B 0x0002      //!< Button B
#define KEY_SELECT 0x0004 //!< Select button
#define KEY_START 0x0008  //!< Start button
#define KEY_RIGHT 0x0010  //!< Right D-pad
#define KEY_LEFT 0x0020   //!< Left D-pad
#define KEY_UP 0x0040     //!< Up D-pad
#define KEY_DOWN 0x0080   //!< Down D-pad
#define KEY_R 0x0100      //!< Shoulder R
#define KEY_L 0x0200      //!< Shoulder L

#define BG_MOSAIC 0x0040 //!< Enable Mosaic
#define BG_4BPP 0        //!< 4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP 0x0080   //!< 8bpp (256 color) bg (no effect on affine bg)
#define BG_WRAP 0x2000   //!< Wrap around edges of affine bgs
#define BG_SIZE0 0
#define BG_SIZE1 0x4000
#define BG_SIZE2 0x8000
#define BG_SIZE3 0xC000
#define BG_REG_32x32 0        //!< reg bg, 32x32 (256x256 px)
#define BG_REG_64x32 0x4000   //!< reg bg, 64x32 (512x256 px)
#define BG_REG_32x64 0x8000   //!< reg bg, 32x64 (256x512 px)
#define BG_REG_64x64 0xC000   //!< reg bg, 64x64 (512x512 px)
#define BG_AFF_16x16 0        //!< affine bg, 16x16 (128x128 px)
#define BG_AFF_32x32 0x4000   //!< affine bg, 32x32 (256x256 px)
#define BG_AFF_64x64 0x8000   //!< affine bg, 64x64 (512x512 px)
#define BG_AFF_128x128 0xC000 //!< affine bg, 128x128 (1024x1024 px)

#define BG_CBB_SHIFT 2
#define BG_CBB(n) ((n) << BG_CBB_SHIFT)

#define BG_SBB_SHIFT 8
#define BG_SBB(n) ((n) << BG_SBB_SHIFT)

#define BITFIELD_SHIFT(bitsToUse, name) ((bitsToUse << name##_SHIFT) & name##_MASK)

// AJB: we use the currMask & 1's complmenet (~) of name##_MASK for the bits we care about to set all bits we want to
// change to 0, while leaving the rest of the currMask intact. i.e. currMask & ~(0100) => currMask & 1011 => 0001
// Then we OR with the bitsToUse, which will toggle all the bits we care about to whatever bitsToUse is.
#define BITFIELD_SET(currMask, bitsToUse, name) (currMask = (currMask & ~name##_MASK) | BITFIELD_SHIFT(bitsToUse, name))

#endif // __MASKS__