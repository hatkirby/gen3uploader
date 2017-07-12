/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <gba.h>
#include "gamedata.h"
#include "link.h"

int main(void)
{
  initializeLink();

  // Identify the host game.
  if (GAME_RUBY)
  {
    sendS32(1);
  } else if (GAME_SAPP)
  {
    sendS32(2);
  } else if (GAME_FR)
  {
    sendS32(3);
  } else if (GAME_LG)
  {
    sendS32(4);
  } else if (GAME_EM)
  {
    sendS32(5);
  } else {
    sendS32(-1);
    waitForAck();

    return 0;
  }

  waitForAck();

  // Get access to save data.
  pSaveBlock1 SaveBlock1;
  pSaveBlock2 SaveBlock2;
  pSaveBlock3 SaveBlock3;

  if (!initSaveData(&SaveBlock1, &SaveBlock2, &SaveBlock3))
  {
    // Unsupported game version.
    sendS32(-1);
    waitForAck();

    return 0;
  }

  sendS32(1);
  waitForAck();

  // Send trainer name.
  u8* trainerName = 0;

  if (GAME_RS)
  {
    trainerName = SaveBlock2->rs.playerName;
  } else if (GAME_FRLG)
  {
    trainerName = SaveBlock2->frlg.playerName;
  } else if (GAME_EM)
  {
    trainerName = SaveBlock2->e.playerName;
  }

  u32 tn1 =
      (trainerName[0] << 24)
    | (trainerName[1] << 16)
    | (trainerName[2] << 8)
    | (trainerName[3]);

  u32 tn2 =
      (trainerName[4] << 24)
    | (trainerName[5] << 16)
    | (trainerName[6] << 8)
    | (trainerName[7]);

  sendU32(tn1);
  waitForAck();

  sendU32(tn2);
  waitForAck();

  // Send trainer ID.
  u8* trainerId = 0;
  if (GAME_RS)
  {
    trainerId = SaveBlock2->rs.playerTrainerId;
  } else if (GAME_FRLG)
  {
    trainerId = SaveBlock2->frlg.playerTrainerId;
  } else if (GAME_EM)
  {
    trainerId = SaveBlock2->e.playerTrainerId;
  }

  u32 tti =
      (trainerId[1] << 8)
    | (trainerId[0]);

  sendU32(tti);
  waitForAck();
}
