#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include <gba.h>
#include "saveblocks.h"

#define GAME_RUBY (((*(u32*)(0x80000AC)) << 8) == 'VXA\x00')
#define GAME_SAPP (((*(u32*)(0x80000AC)) << 8) == 'PXA\x00')
#define GAME_RS   ((GAME_RUBY) || (GAME_SAPP))
#define GAME_FR   (((*(u32*)(0x80000AC)) << 8) == 'RPB\x00')
#define GAME_LG   (((*(u32*)(0x80000AC)) << 8) == 'GPB\x00')
#define GAME_FRLG ((GAME_FR) || (GAME_LG))
#define GAME_EM   (((*(u32*)(0x80000AC)) << 8) == 'EPB\x00')

#define LANG_JAPAN ((*(u8*)(0x80000AF)) == 'J')

bool initSaveData(
    pSaveBlock1* SaveBlock1,
    pSaveBlock2* SaveBlock2,
    pSaveBlock3* SaveBlock3);

#endif
