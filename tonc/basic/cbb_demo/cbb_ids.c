//======================================================================
//
//	ids8, 72x8@8, 
//	+ 9 tiles not compressed
//	Total size: 576 = 576
//
//	Time-stamp: 2005-12-24, 18:28:50
//	Exported by Cearn's Usenti v1.7.1
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

const unsigned int ids8Tiles[144]=
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x000D0D00,0x00000000,0x0D000000,0x00000000,
	0x000D0000,0x00000000,0x00000D00,0x00000000,0x0D0D0D00,0x00000000,0x00000000,0x00000000,	
	// 16 entries of 32bits bits per entry can be accessed by [0] when indexing by TILE8 (u32 * |16|)

	0x00000000,0x00000000,0x00000000,0x00000000,0x000D0D00,0x000A0A00,0x0D000000,0x000A0000,
	0x000D0000,0x000A0000,0x00000D00,0x000A0000,0x0D0D0D00,0x0A0A0A00,0x00000000,0x00000000,	// [1]

	0x00000000,0x00000000,0x00000000,0x00000000,0x000D0D00,0x000A0A00,0x0D000000,0x0A000000,
	0x000D0000,0x000A0000,0x00000D00,0x00000A00,0x0D0D0D00,0x0A0A0A00,0x00000000,0x00000000,	// [2]

	0x00000000,0x00000000,0x00000000,0x00000000,0x000D0D00,0x000A0000,0x0D000000,0x0A000A00,
	0x000D0000,0x0A000A00,0x0D000000,0x0A000A00,0x000D0D00,0x000A0000,0x00000000,0x00000000,	// [3]

	0x00000000,0x00000000,0x00000000,0x00000000,0x000D0D00,0x000A0A00,0x0D000000,0x000A0000,
	0x000D0000,0x000A0000,0x0D000000,0x000A0000,0x000D0D00,0x0A0A0A00,0x00000000,0x00000000,	// [4]

	0x00000000,0x00000000,0x00000000,0x00000000,0x0D000D00,0x000A0000,0x0D000D00,0x0A000A00,
	0x0D0D0D00,0x0A000A00,0x0D000000,0x0A000A00,0x0D000000,0x000A0000,0x00000000,0x00000000,	// [5]

	0x00000000,0x00000000,0x00000000,0x00000000,0x0D000D00,0x000A0A00,0x0D000D00,0x000A0000,
	0x0D0D0D00,0x000A0000,0x0D000000,0x000A0000,0x0D000000,0x0A0A0A00,0x00000000,0x00000000,	// [6]

	0x00000000,0x00000000,0x00000000,0x00000000,0x0D0D0D00,0x000A0000,0x00000D00,0x0A000A00,
	0x000D0D00,0x0A000A00,0x0D000000,0x0A000A00,0x000D0D00,0x000A0000,0x00000000,0x00000000,	// [7]

	0x00000000,0x00000000,0x00000000,0x00000000,0x0D0D0D00,0x000A0A00,0x00000D00,0x000A0000,
	0x000D0D00,0x000A0000,0x0D000000,0x000A0000,0x000D0D00,0x0A0A0A00,0x00000000,0x00000000,	// [8]
};

//======================================================================
//
//	ids4, 40x8@4, 
//	+ palette 16 entries, not compressed
//	+ 5 tiles not compressed
//	Total size: 32 + 160 = 192
//
//	Time-stamp: 2005-12-24, 18:29:30
//	Exported by Cearn's Usenti v1.7.1
//	(comments, kudos, flames to "daytshen@hotmail.com")
//
//======================================================================

const unsigned int ids4Pal[8]=
{
	0x00100000,0x02100200,0x40104000,0x63184200,0x001F4210,0x03FF03E0,0x7C1F7C00,0x7FFF7FE0,
};

const unsigned int ids4Tiles[40]=
{
	0x00000000,0x00000000,0x00000E00,0x0000E0E0,0x0000E0E0,0x0000E0E0,0x00000E00,0x00000000,	
	// 8 entries of 32bits bits per entry can be accessed by [0] when indexing by TILE (u32 * |8|)

	0x00000000,0x00000000,0x09900E00,0x0900E0E0,0x0900E0E0,0x0900E0E0,0x99900E00,0x00000000,	// [1]

	0x00000000,0x00000000,0x09900E00,0x9000E0E0,0x0900E0E0,0x0090E0E0,0x99900E00,0x00000000,	// [2]

	0x00000000,0x00000000,0x09000EE0,0x90900E00,0x90900E00,0x90900E00,0x0900EEE0,0x00000000,	// [3]

	0x00000000,0x00000000,0x09900EE0,0x09000E00,0x09000E00,0x09000E00,0x9990EEE0,0x00000000,	// [4]
};
