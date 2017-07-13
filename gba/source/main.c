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
  // This possibly increases stability, I don't rightly know, this is all black
  // magic, will test more later.
  REG_IME = 0;

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

  // Does the player want to import this game?
  if (waitForResponse() == 0)
  {
    return 0;
  }

  // Send Pokédex data
  u8* pokedexSeen = 0;
  if (GAME_RS)
  {
    pokedexSeen = SaveBlock2->rs.pokedex.seen;
  } else if (GAME_FRLG)
  {
    pokedexSeen = SaveBlock2->frlg.pokedex.seen;
  } else if (GAME_EM)
  {
    pokedexSeen = SaveBlock2->e.pokedex.seen;
  }

  for (int i=0; i<13; i++)
  {
    u32 psi =
        (pokedexSeen[i*4])
      | (pokedexSeen[i*4+1] << 8)
      | (pokedexSeen[i*4+2] << 16)
      | (pokedexSeen[i*4+3] << 24);

    directSendU32(psi);
  }

  u8* pokedexCaught = 0;
  if (GAME_RS)
  {
    pokedexCaught = SaveBlock2->rs.pokedex.owned;
  } else if (GAME_FRLG)
  {
    pokedexCaught = SaveBlock2->frlg.pokedex.owned;
  } else if (GAME_EM)
  {
    pokedexCaught = SaveBlock2->e.pokedex.owned;
  }

  for (int i=0; i<13; i++)
  {
    u32 psi =
        (pokedexCaught[i*4])
      | (pokedexCaught[i*4+1] << 8)
      | (pokedexCaught[i*4+2] << 16)
      | (pokedexCaught[i*4+3] << 24);

    directSendU32(psi);
  }
}
