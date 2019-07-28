#include "Banks/SetBank2.h"

#include "../res/src/tiles.h"
#include "../res/src/win_screen.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"


void Start_StateWin() {

	//INIT_CONSOLE(font, 2);
	InitScrollTiles(0, &tiles, bank_tiles);
	InitScroll(win_screenWidth, win_screenHeight, win_screen, 0, 0, 3);
	SHOW_BKG;

}

void Update_StateWin() {
	if(KEY_PRESSED(J_START)) {
		SetState( StateGame );
	}
}
