/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "deserialize.h"
#include <stdio.h>
#include "encoding.h"

cJSON* pokemonToJson(const struct PokemonIntermediate* pki)
{
  char d_pokename[31];
  decodePokemonCharset(pki->nickname, 10, d_pokename, pki->language);

  char d_otName[22];
  decodePokemonCharset(pki->otName, 7, d_otName, pki->language);

  char d_key[57];
  sprintf(
    d_key,
    "%08lx%08lx%08lx%08lx%08lx%08lx%08lx",
    pki->key[0],
    pki->key[1],
    pki->key[2],
    pki->key[3],
    pki->key[4],
    pki->key[5],
    pki->key[6]);

  cJSON* jPoke = cJSON_CreateObject();

  cJSON_AddNumberToObject(
    jPoke,
    "species",
    __builtin_bswap16(pki->species));

  cJSON_AddItemToObject(
    jPoke,
    "nickname",
    cJSON_CreateString(d_pokename));

  cJSON_AddItemToObject(
    jPoke,
    "otName",
    cJSON_CreateString(d_otName));

  cJSON_AddNumberToObject(
    jPoke,
    "otId",
    __builtin_bswap16(pki->otId));

  cJSON_AddNumberToObject(
    jPoke,
    "level",
    pki->level);

  cJSON_AddNumberToObject(
    jPoke,
    "hp",
    __builtin_bswap32(pki->hp));

  cJSON_AddNumberToObject(
    jPoke,
    "attack",
    __builtin_bswap32(pki->attack));

  cJSON_AddNumberToObject(
    jPoke,
    "defense",
    __builtin_bswap32(pki->defense));

  cJSON_AddNumberToObject(
    jPoke,
    "speed",
    __builtin_bswap32(pki->speed));

  cJSON_AddNumberToObject(
    jPoke,
    "spAttack",
    __builtin_bswap32(pki->spAttack));

  cJSON_AddNumberToObject(
    jPoke,
    "spDefense",
    __builtin_bswap32(pki->spDefense));

  cJSON_AddNumberToObject(
    jPoke,
    "coolness",
    pki->cool);

  cJSON_AddNumberToObject(
    jPoke,
    "beauty",
    pki->beauty);

  cJSON_AddNumberToObject(
    jPoke,
    "cuteness",
    pki->cute);

  cJSON_AddNumberToObject(
    jPoke,
    "smartness",
    pki->smart);

  cJSON_AddNumberToObject(
    jPoke,
    "toughness",
    pki->tough);

  cJSON_AddNumberToObject(
    jPoke,
    "sheen",
    pki->sheen);

  cJSON_AddItemToObject(
    jPoke,
    "key",
    cJSON_CreateString(d_key));

  cJSON_AddNumberToObject(
    jPoke,
    "experience",
    __builtin_bswap32(pki->experience));

  if (pki->heldItem)
  {
    cJSON_AddNumberToObject(
      jPoke,
      "heldItem",
      __builtin_bswap16(pki->heldItem));
  }

  cJSON* jMoves = cJSON_CreateArray();

  for (int j=0; j<4; j++)
  {
    if (pki->moves[j] != 0)
    {
      cJSON* jMove = cJSON_CreateObject();

      cJSON_AddNumberToObject(
        jMove,
        "id",
        __builtin_bswap16(pki->moves[j]));

      cJSON_AddNumberToObject(
        jMove,
        "ppBonuses",
        (pki->ppBonuses >> (2*j)) & 3);

      cJSON_AddItemToArray(jMoves, jMove);
    } else {
      break;
    }
  }

  cJSON_AddItemToObject(
    jPoke,
    "moves",
    jMoves);

  if (pki->otGender)
  {
    cJSON_AddStringToObject(jPoke, "otGender", "female");
  } else {
    cJSON_AddStringToObject(jPoke, "otGender", "male");
  }

  cJSON_AddNumberToObject(
    jPoke,
    "metLevel",
    pki->metLevel);

  cJSON_AddNumberToObject(
    jPoke,
    "metLocation",
    pki->metLocation);

  cJSON_AddBoolToObject(
    jPoke,
    "shiny",
    pki->shiny);

  cJSON_AddNumberToObject(
    jPoke,
    "nature",
    pki->nature);

  if (pki->gender == 0)
  {
    cJSON_AddStringToObject(jPoke, "gender", "male");
  } else if (pki->gender == 1)
  {
    cJSON_AddStringToObject(jPoke, "gender", "female");
  } else if (pki->gender == 2)
  {
    cJSON_AddStringToObject(jPoke, "gender", "genderless");
  }

  cJSON_AddBoolToObject(
    jPoke,
    "secondAbility",
    pki->altAbility);

  // Handle Unown form.
  if (__builtin_bswap16(pki->species) == 201)
  {
    cJSON_AddNumberToObject(
      jPoke,
      "unownLetter",
      pki->unownLetter);
  }

  cJSON_AddNumberToObject(jPoke, "coolRibbons", pki->coolRibbons);
  cJSON_AddNumberToObject(jPoke, "beautyRibbons", pki->beautyRibbons);
  cJSON_AddNumberToObject(jPoke, "cuteRibbons", pki->cuteRibbons);
  cJSON_AddNumberToObject(jPoke, "smartRibbons", pki->smartRibbons);
  cJSON_AddNumberToObject(jPoke, "toughRibbons", pki->toughRibbons);

  u16 miscRibbons = __builtin_bswap16(pki->miscRibbons);
  if (miscRibbons & CHAMPION_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "championRibbon", true);
  }

  if (miscRibbons & WINNING_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "winningRibbon", true);
  }

  if (miscRibbons & VICTORY_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "victoryRibbon", true);
  }

  if (miscRibbons & ARTIST_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "artistRibbon", true);
  }

  if (miscRibbons & EFFORT_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "effortRibbon", true);
  }

  if (miscRibbons & MARINE_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "marineRibbon", true);
  }

  if (miscRibbons & LAND_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "landRibbon", true);
  }

  if (miscRibbons & SKY_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "skyRibbon", true);
  }

  if (miscRibbons & COUNTRY_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "countryRibbon", true);
  }

  if (miscRibbons & NATIONAL_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "nationalRibbon", true);
  }

  if (miscRibbons & EARTH_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "earthRibbon", true);
  }

  if (miscRibbons & WORLD_RIBBON)
  {
    cJSON_AddBoolToObject(jPoke, "worldRibbon", true);
  }

  return jPoke;
}
