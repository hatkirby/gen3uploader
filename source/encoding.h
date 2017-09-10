/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef ENCODING_H_95547384
#define ENCODING_H_95547384

#include <gccore.h>
#include "pokemon.h"

void decodePokemonCharset(
  const u8* input,
  int maxLength,
  char* output,
  enum PokemonLanguage language);

#endif /* end of include guard: ENCODING_H_95547384 */
