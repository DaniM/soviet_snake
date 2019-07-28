#include "Banks/SetBank2.h"

#include "../res/src/tiles.h"
#include "../res/src/intro.h"
#include "../res/src/font.h"

#include "ZGBMain.h"
#include "Scroll.h"
#include "SpriteManager.h"
#include "Print.h"
#include "Keys.h"

extern UINT8* russia_mod_Data[]; 
void Start_StateIntro() {

	//INIT_CONSOLE(font, 2);
	InitScrollTiles(0, &font, bank_tiles);
	InitScroll(introWidth, introHeight, intro, 0, 0, 3);
	SHOW_BKG;
	PlayMusic(russia_mod_Data, 3, 1);
}

void Update_StateIntro() {
	if(KEY_PRESSED(J_START)) {
		SetState( StateGame );
	}
}
