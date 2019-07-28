#include "Banks/SetBank2.h"

#include "../res/src/tiles.h"
#include "../res/src/lose_screen.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"

void Start_StateLose() {

	//INIT_CONSOLE(font, 2);

	InitScrollTiles(0, &tiles, bank_tiles);
	InitScroll(lose_screenWidth, lose_screenHeight, lose_screen, 0, 0, 3);
	SHOW_BKG;

}

void Update_StateLose() {
	if(KEY_PRESSED(J_START)) {
		SetState( StateGame );
	}
}
