#pragma bank 3
unsigned char bank_tiles = 3;
const unsigned char tiles_tiles[] = {
	//Frame 0
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	
	//Frame 1
	0xcf,0x20,0xc3,0x20,0x00,0xff,0xfb,0x04,
	0xf9,0x04,0x78,0x04,0x00,0xff,0xdf,0x20,
	
	//Frame 2
	0x3c,0x3c,0x7e,0x7e,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0x7e,0x7e,0x3c,0x3c,
	
	//Frame 3
	0xc1,0x00,0x41,0x00,0x61,0x00,0x33,0x00,
	0x1e,0x00,0x18,0x00,0x6c,0x00,0xc4,0x00,
	
	//Frame 4
	0x7e,0x7e,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0x7e,0x7e,
	
	//Frame 5
	0x7f,0x7f,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0x7f,0x7f,
	
	//Frame 6
	0xfc,0xfc,0xfe,0xfe,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xfe,0xfe,0xfc,0xfc,
	
	//Frame 7
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

#include "TilesInfo.h"
const struct TilesInfo tiles = {
	8, //width
	8, //height
	8, //num_tiles
	tiles_tiles, //tiles
	0, //CGB palette
};