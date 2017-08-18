/*
 * Copyright (C) 2017 Scott Norton
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef BASESTATS_H
#define BASESTATS_H

#include <gba.h>

struct SmallBaseStats {
  u8 baseHP;
  u8 baseAttack;
  u8 baseDefense;
  u8 baseSpeed;
  u8 baseSpAttack;
  u8 baseSpDefense;
  u8 genderRatio;
  u8 growthRate;
};

extern const struct SmallBaseStats gSmallBaseStats[];

#endif
