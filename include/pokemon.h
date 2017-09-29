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

#define CHAMPION_RIBBON (1 << 0)
#define WINNING_RIBBON  (1 << 1)
#define VICTORY_RIBBON  (1 << 2)
#define ARTIST_RIBBON   (1 << 3)
#define EFFORT_RIBBON   (1 << 4)
#define MARINE_RIBBON   (1 << 5)
#define LAND_RIBBON     (1 << 6)
#define SKY_RIBBON      (1 << 7)
#define COUNTRY_RIBBON  (1 << 8)
#define NATIONAL_RIBBON (1 << 9)
#define EARTH_RIBBON    (1 << 10)
#define WORLD_RIBBON    (1 << 11)

struct __attribute__((aligned(4))) PokemonIntermediate {
  // a hash that can be used to identify the Pokémon. because the games do not
  // naturally generate unique identifiers for Pokémon, this hash is generated
  // from parts of the Pokémon's data that are guaranteed never to change. the
  // parts used are the trainer ID and secret ID of the Pokémon's original
  // trainer, the personality value, and the IVs. almost all of this data is
  // secret, and should not be derivable from the identifier, which is why the
  // identifier is hashed. while this identifier is not guaranteed to be unique,
  // probability of collision is astronomically small given that the
  // personality value and IVs provide essentially 52 bits of randomness
  // (technically less because the IVs of bred Pokémon are not uniformly
  // random, but this variation is statistically insignificant). the OT ID,
  // while not uniformly random (amongst Pokémon), is included as a sort of
  // "namespace", in that any Pokémon with matching PVs and IVs must also have
  // the same OT, thus preventing collaboratively finding PV and IV collisions.
  // there is one deterministic way that two Pokémon can have the same hash:
  // when a Nincada evolves into a Ninjask and a Shedinja is generated, the
  // Shedinja is guaranteed to have the same IVs and personality value as the
  // Ninjask. we circumvent this by also including a boolean in the hash which
  // is set to true if the Pokémon is a Shedinja, and false otherwise. this
  // differentiates a Shedinja from the Ninjask it came from, but also allows
  // the Ninjask to be associated with the Nincada it used to be.
  u32 key[7];

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
  u16 otId; // only the lower 2 bytes, because the upper 2 are secret
  u16 miscRibbons;

  u8 coolRibbons;
  u8 beautyRibbons;
  u8 cuteRibbons;
  u8 smartRibbons;
  u8 toughRibbons;
  u8 ppBonuses;
  u8 otGender;
  u8 metLevel;
  u8 metLocation;
  u8 nickname[POKEMON_NAME_LENGTH];
  u8 otName[OT_NAME_LENGTH];
  u8 pokeball;
  u8 language;
  u8 altAbility;
  u8 gender;
  u8 orre;
  u8 shiny;
  u8 nature;
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
