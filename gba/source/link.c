/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "link.h"

#define JOY_WRITE 2
#define JOY_READ 4
#define JOY_RW 6

void initializeLink()
{
  REG_HS_CTRL |= JOY_RW;
  REG_JOYTR = 0;
  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
}

void waitForAck()
{
  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
  REG_JOYTR = 0;
  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
}

void sendS32(s32 val)
{
  REG_JOYTR = val;
}

void sendU32(u32 val)
{
  REG_JOYTR = val;
}
