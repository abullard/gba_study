#ifndef __MASKS__
#define __MASKS__

#define KEY_MASK 0x03FF // 00000011 11111111 mask if all buttons were pressed
#define PAL_BG_SIZE 0x00200
#define DCNT_OBJ 0x1000    //!< Enable objects
#define DCNT_OBJ_1D 0x0040 //!< OBJ-VRAM as array

// OBJ_ATTR.attr0{8-9} defines
#define ATTR0_OBJ_MODE_REG 0x0000
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


// TODO AJB: create defines for ATTR1 and ATTR2

#endif // __MASKS__