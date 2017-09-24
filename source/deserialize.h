/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef DESERIALIZE_H_3E597847
#define DESERIALIZE_H_3E597847

#include <gccore.h>
#include "pokemon.h"
#include "cJSON.h"

cJSON* pokemonToJson(const struct PokemonIntermediate* pki);

#endif /* end of include guard: DESERIALIZE_H_3E597847 */
