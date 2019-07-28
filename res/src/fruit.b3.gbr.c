#pragma bank 3
unsigned char bank_fruit = 3;
const unsigned char fruit_tiles[] = {
	//Frame 0
	0x3c,0x00,0x4a,0x3c,0x8d,0x7e,0x9d,0x7e,
	0xbf,0x7e,0xbd,0x7e,0x40,0x06,0x3c,0x00
};

#include "TilesInfo.h"
const struct TilesInfo fruit = {
	8, //width
	8, //height
	1, //num_tiles
	fruit_tiles, //tiles
	0, //CGB palette
};