#include "Banks/SetBank2.h"

#include "../res/src/tiles.h"
#include "../res/src/map.h"
#include "../res/src/font.h"
#include "../res/src/window.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"

#include "Sound.h"

// the map is 18x20
// up, left and right borders

//UINT8 logic_map[360];

UINT8 available_fruits[14][18];
UINT16 score;

void Start_StateGame() {

	NR52_REG = 0x80; //Enables sound, you should always setup this first
	NR51_REG = 0xFF; //Enables all channels (left and right)
	NR50_REG = 0x77; //Max volume

	score = 0;

	INIT_FONT(font, PRINT_WIN);
	WX_REG = 7;
	WY_REG = (144 - (1 << 3));
	//scroll_h_border = 2 << 3;
	InitWindow(0, 0, 20, 2, window, 3, 0);
	SHOW_WIN;
	
	SPRITES_8x8;
	for(UINT8 i = 0; i != N_SPRITE_TYPES; ++ i) {
		SpriteManagerLoad(i);
	}
	SHOW_SPRITES;

	InitScrollTiles(0, &tiles, bank_tiles);
	InitScroll(mapWidth, mapHeight, map, 0, 0, 3);
	SHOW_BKG;

	for( UINT8 i = 0; i != 14; ++i )
	{
		for( UINT8 j = 0; j !=  18; ++j )
		{
			available_fruits[i][j] = 1;
		}
	}


	
	SpriteManagerAdd(SpritePlayer, 64, 64);
}

void Update_StateGame() {
	}
