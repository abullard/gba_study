//
// all_gfx.h
//
// One header to rule them and in the darkness bind them
// Date: 2023-10-20 11:23:25 AM

#ifdef __cplusplus
extern "C" {
#endif

//{{BLOCK(filbert_idle)

//======================================================================
//
//	filbert_idle, 32x128@8, 
//	+ palette 256 entries, not compressed
//	+ 64 tiles not compressed
//	Total size: 512 + 4096 = 4608
//
//	Time-stamp: 2023-10-20, 11:23:25
//	Exported by Cearn's GBA Image Transmogrifier, v0.8.6
//	( http://www.coranac.com/projects/#grit )
//
//======================================================================

#ifndef GRIT_FILBERT_IDLE_H
#define GRIT_FILBERT_IDLE_H

#define filbert_idleTilesLen 4096
extern const unsigned int filbert_idleTiles[1024];

#define filbert_idlePalLen 512
extern const unsigned short filbert_idlePal[256];

#endif // GRIT_FILBERT_IDLE_H

//}}BLOCK(filbert_idle)

#ifdef __cplusplus
};
#endif

