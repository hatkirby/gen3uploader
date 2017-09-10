/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef POKEMON_H_AD844D6F
#define POKEMON_H_AD844D6F

#define POKEMON_NAME_LENGTH 10
#define OT_NAME_LENGTH 7
#define TILE_SIZE_4BPP 32

enum PokemonLanguage {
  Japanese = 1,
  English = 2,
  French = 3,
  Italian = 4,
  German = 5,
  Spanish = 7
};

struct PokemonIntermediate {
  u32 otId;
  u32 experience;

  // the stats are calculated from the base stats, IVs, EVs, and Nature, before
  // transmitting the pokemon's data, in order to keep the IVs and EVs secret.
  u32 hp;
  u32 attack;
  u32 defense;
  u32 speed;
  u32 spAttack;
  u32 spDefense;

  u16 species;
  u16 heldItem;
  u16 moves[4];

  u8 ppBonuses;
  u8 otGender:1;
  u8 metLevel:7;
  u8 metLocation;
  u8 nickname[POKEMON_NAME_LENGTH];
  u8 otName[OT_NAME_LENGTH];
  u8 pokeball;
  u8 language:3;
  u8 altAbility:1;
  u8 filler:4; // waste of space but nothing to pack it with

  // the following values are generated from the personality value.
  u8 nature:6;
  u8 gender:1;
  u8 shiny:1;
  u8 unownLetter;

  // the level is calculated from the species and experience. this is mostly
  // included for convenience.
  u8 level;

  // instead of being represented as a number from 0 to 255, the conditions are
  // transmitted as numbers from 0 to 10, so as to keep the exact condition
  // values secret, since only an approximation of the condition value is ever
  // visible in the game proper. the same goes for the sheen.
  u8 cool;
  u8 beauty;
  u8 cute;
  u8 smart;
  u8 tough;
  u8 sheen;

  // this field can have the following values:
  //   0 - pokemon does not have pokerus
  //   1 - pokemon has pokerus
  //   2 - pokemon had pokerus at one point
  u8 pokerus;
};

#endif /* end of include guard: POKEMON_H_AD844D6F */
