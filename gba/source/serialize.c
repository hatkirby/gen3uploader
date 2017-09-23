/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "serialize.h"
#include "gamedata.h"
#include "link.h"
#include "basestats.h"
#include "exptables.h"
#include "dexorder.h"
#include "sha2.h"

u32 CalculateStat(
  u8 base,
  u32 iv,
  u8 ev,
  u8 level,
  u8 statIndex,
  u8 nature)
{
  u32 n = (((2 * base + iv + ev / 4) * level) / 100) + 5;

  u8 naturePlus = (nature / 5);
  u8 natureMinus = (nature % 5);

  if (naturePlus != natureMinus)
  {
    if (statIndex == naturePlus)
    {
      return (u32)(n * 110) / 100;
    } else if (statIndex == natureMinus)
    {
      return (u32)(n * 90) / 100;
    }
  }

  return n;
}

void PokemonIntermediateInit(
  struct PokemonIntermediate* pki,
  struct BoxPokemon* bpkm,
  u16 trainerId,
  u16 secretId)
{
  DecryptBoxPokemon(bpkm);

  struct PokemonSubstruct0* sub0 = GetBoxPokemonSubstruct0(bpkm);
  struct PokemonSubstruct1* sub1 = GetBoxPokemonSubstruct1(bpkm);
  struct PokemonSubstruct2* sub2 = GetBoxPokemonSubstruct2(bpkm);
  struct PokemonSubstruct3* sub3 = GetBoxPokemonSubstruct3(bpkm);

  u32 identifier[3];
  identifier[0] = bpkm->otId;             // original trainer
  identifier[1] = bpkm->personality;      // personality value
  identifier[2] = ((const u32*)sub3)[1];  // IVs (plus two non-random bits)

  sha224(
    (const unsigned char*)identifier,
    12,
    (unsigned char*)pki->key);

  const struct SmallBaseStats* baseStats = BaseStatsForSpecies(sub0->species);

  for (int i=0; i<POKEMON_NAME_LENGTH; i++)
  {
    pki->nickname[i] = bpkm->nickname[i];
  }

  for (int i=0; i<OT_NAME_LENGTH; i++)
  {
    pki->otName[i] = bpkm->otName[i];
  }

  pki->otId = bpkm->otId & 0x0000FFFF;
  pki->otGender = sub3->otGender;
  pki->species = gSpeciesToNationalPokedexNum[sub0->species - 1];
  pki->heldItem = sub0->heldItem;
  pki->experience = sub0->experience;

  pki->moves[0] = sub1->moves[0];
  pki->moves[1] = sub1->moves[1];
  pki->moves[2] = sub1->moves[2];
  pki->moves[3] = sub1->moves[3];

  pki->ppBonuses = sub0->ppBonuses;
  pki->metLevel = sub3->metLevel;
  pki->metLocation = sub3->metLocation;
  pki->pokeball = sub3->pokeball;
  pki->altAbility = sub3->altAbility;
  pki->language = bpkm->language & 7;
  pki->orre = (sub3->metGame == 15);

  // Derive nature from the personality value.
  pki->nature = (bpkm->personality % 25);

  // Derive gender from the personality value.
  int genderThreshold = baseStats->genderRatio;

  if (genderThreshold == 255)
  {
    pki->gender = 2;
  } else if (genderThreshold == 0)
  {
    pki->gender = 0;
  } else if (genderThreshold == 254)
  {
    pki->gender = 1;
  } else {
    u8 genderDeterminer = bpkm->personality & 0x000000FF;

    if (genderDeterminer >= genderThreshold)
    {
      pki->gender = 0;
    } else {
      pki->gender = 1;
    }
  }

  // Determine shininess from the personality value.
  u16 shinyDeterminer =
      (trainerId)
    ^ (secretId)
    ^ ((bpkm->personality >> 16) & 0x0000FFFF)
    ^ (bpkm->personality & 0x0000FFFF);

  if (shinyDeterminer < 8)
  {
    pki->shiny = 1;
  } else {
    pki->shiny = 0;
  }

  // Determine Unown letter from the personality value.
  if (sub0->species == UNOWN_SPECIES_INDEX)
  {
    u8 unownDeterminer =
        ((bpkm->personality & 0x07000000) >> 18)
      | ((bpkm->personality & 0x00070000) >> 12)
      | ((bpkm->personality & 0x00000700) >> 6)
      |  (bpkm->personality & 0x00000007);

    pki->unownLetter = (unownDeterminer % 28);
  }

  // Calculate level from experience.
  pki->level = 1;

  const u32* expTable = gExperienceTables[baseStats->growthRate];
  while ((pki->level <= 100) && (expTable[pki->level] <= sub0->experience))
  {
    pki->level++;
  }

  pki->level--;

  // Calculate stats.
  if (sub0->species == SHEDINJA_SPECIES_INDEX)
  {
    pki->hp = 1;
  } else {
    u32 n = 2 * baseStats->baseHP + sub3->hpIV;
    pki->hp = (((n + sub2->hpEV / 4) * pki->level) / 100) + pki->level + 10;
  }

  pki->attack = CalculateStat(
    baseStats->baseAttack,
    sub3->attackIV,
    sub2->attackEV,
    pki->level,
    0,
    pki->nature);

  pki->defense = CalculateStat(
    baseStats->baseDefense,
    sub3->defenseIV,
    sub2->defenseEV,
    pki->level,
    1,
    pki->nature);

  pki->speed = CalculateStat(
    baseStats->baseSpeed,
    sub3->speedIV,
    sub2->speedEV,
    pki->level,
    2,
    pki->nature);

  pki->spAttack = CalculateStat(
    baseStats->baseSpAttack,
    sub3->spAttackIV,
    sub2->spAttackEV,
    pki->level,
    3,
    pki->nature);

  pki->spDefense = CalculateStat(
    baseStats->baseSpDefense,
    sub3->spDefenseIV,
    sub2->spDefenseEV,
    pki->level,
    4,
    pki->nature);

  // Approximate the values of the contest conditions.
  pki->cool = ((u16)(sub2->cool) * 10) / 255;
  pki->beauty = ((u16)(sub2->beauty) * 10) / 255;
  pki->cute = ((u16)(sub2->cute) * 10) / 255;
  pki->smart = ((u16)(sub2->smart) * 10) / 255;
  pki->tough = ((u16)(sub2->tough) * 10) / 255;
  pki->sheen = ((u16)(sub2->sheen) * 10) / 255;

  // Determine Pokerus status.
  if (sub3->pokerus & 0xF0)
  {
    if (sub3->pokerus & 0x0F)
    {
      pki->pokerus = 1;
    } else {
      pki->pokerus = 2;
    }
  } else {
    pki->pokerus = 0;
  }

  EncryptBoxPokemon(bpkm);
}

void PokemonIntermediateStream(struct PokemonIntermediate* pki)
{
  u32* raw = (u32*)pki;

  for (int i=0; i<(sizeof(struct PokemonIntermediate)/4); i++)
  {
    directSendU32(raw[i]);
  }
}
