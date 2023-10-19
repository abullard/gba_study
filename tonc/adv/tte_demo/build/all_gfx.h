//
// all_gfx.h
//
// One header to rule them and in the darkness bind them
// Date: 2023-10-11 09:37:57 AM

#ifdef __cplusplus
extern "C" {
#endif

//{{BLOCK(dlgbox)

//======================================================================
//
//	dlgbox, 240x32@4, 
//	+ palette 16 entries, not compressed
//	+ 120 tiles not compressed
//	Total size: 32 + 3840 = 3872
//
//	Time-stamp: 2023-10-11, 09:37:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DLGBOX_H
#define GRIT_DLGBOX_H

#define dlgboxTilesLen 3840
extern const unsigned int dlgboxTiles[960];

#define dlgboxPalLen 32
extern const unsigned short dlgboxPal[16];

#endif // GRIT_DLGBOX_H

//}}BLOCK(dlgbox)

//{{BLOCK(dungeon01)

//======================================================================
//
//	dungeon01, 512x512@4, 
//	+ palette 134 entries, lz77 compressed
//	+ 144 tiles (t|f|p reduced) lz77 compressed
//	+ regular map (in SBBs), lz77 compressed, 64x64 
//	Total size: 268 + 2852 + 2008 = 5128
//
//	Time-stamp: 2023-10-11, 09:37:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_DUNGEON01_H
#define GRIT_DUNGEON01_H

#define dungeon01TilesLen 2852
extern const unsigned int dungeon01Tiles[713];

#define dungeon01MapLen 2008
extern const unsigned short dungeon01Map[1004];

#define dungeon01PalLen 268
extern const unsigned short dungeon01Pal[134];

#endif // GRIT_DUNGEON01_H

//}}BLOCK(dungeon01)

//{{BLOCK(menu_gfx)

//======================================================================
//
//	menu_gfx, 240x160@8, 
//	+ palette 256 entries, not compressed
//	+ bitmap rle compressed
//	Total size: 512 + 2784 = 3296
//
//	Time-stamp: 2023-10-11, 09:37:57
//	Exported by Cearn's GBA Image Transmogrifier, v0.9.2
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_MENU_GFX_H
#define GRIT_MENU_GFX_H

#define menu_gfxBitmapLen 2784
extern const unsigned int menu_gfxBitmap[696];

#define menu_gfxPalLen 512
extern const unsigned short menu_gfxPal[256];

#endif // GRIT_MENU_GFX_H

//}}BLOCK(menu_gfx)

#ifdef __cplusplus
};
#endif

