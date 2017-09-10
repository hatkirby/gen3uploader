/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef POKEMON_H_67C60AC1
#define POKEMON_H_67C60AC1

#include <gba.h>

struct BoxPokemon;
struct PokemonIntermediate;
struct GameData;

void PokemonIntermediateInit(
  struct PokemonIntermediate* pki,
  struct BoxPokemon* bpkm,
  u16 trainerId,
  u16 secretId);

void PokemonIntermediateStream(struct PokemonIntermediate* pki);

#endif /* end of include guard: POKEMON_H_67C60AC1 */
