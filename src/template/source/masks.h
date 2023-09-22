#ifndef __MASKS__
#define __MASKS__

#define KEY_MASK 0x03FF // 00000011 11111111 mask if all buttons were pressed
#define PAL_BG_SIZE 0x00200
#define DCNT_OBJ 0x1000    //!< Enable objects
#define DCNT_OBJ_1D 0x0040 //!< OBJ-VRAM as array

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
#define ATTR0_Y_MASK 0x00FF
#define ATTR0_Y_SHIFT 0x0000
#define ATTR1_X_MASK 0x01FF
#define ATTR1_X_SHIFT 0

// OBJ_ATTR.attr1{12} defines
// if you want to turn off HFLIP just XOR it with itself
#define ATTR1_HORIZONTAL_FLIP 0x1000

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
#define KEY_A 0x0001	  //!< Button A
#define KEY_B 0x0002	  //!< Button B
#define KEY_SELECT 0x0004 //!< Select button
#define KEY_START 0x0008  //!< Start button
#define KEY_RIGHT 0x0010  //!< Right D-pad
#define KEY_LEFT 0x0020	  //!< Left D-pad
#define KEY_UP 0x0040	  //!< Up D-pad
#define KEY_DOWN 0x0080	  //!< Down D-pad
#define KEY_R 0x0100	  //!< Shoulder R
#define KEY_L 0x0200	  //!< Shoulder L


#endif // __MASKS__