#include "Banks/SetBank2.h"

#include "../res/src/tiles.h"
#include "../res/src/intro.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"


void Start_StateIntro() {

	//INIT_CONSOLE(font, 2);
	InitScrollTiles(0, &font, bank_tiles);
	InitScroll(introWidth, introHeight, intro, 0, 0, 3);
	SHOW_BKG;

}

void Update_StateIntro() {
	if(KEY_PRESSED(J_START)) {
		SetState( StateGame );
	}
}
