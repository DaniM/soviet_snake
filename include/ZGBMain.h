#ifndef ZGBMAIN_H
#define ZGBMAIN_H

#define STATES \
_STATE(StateIntro)\
_STATE(StateGame)\
_STATE(StateWin)\
_STATE(StateLose)\
STATE_DEF_END

#define SPRITES \
_SPRITE_DMG(SpritePlayer, player)\
_SPRITE_DMG(SpriteFruit, fruit)\
SPRITE_DEF_END

#include "ZGBMain_Init.h"

#endif
