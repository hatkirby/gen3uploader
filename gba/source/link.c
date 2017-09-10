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
  REG_JOYTR = 0;
  REG_HS_CTRL |= JOY_RW;
  while ((REG_HS_CTRL & JOY_READ) == 0);
  REG_HS_CTRL |= JOY_RW;
}

void waitForAck()
{
  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
}

u32 waitForResponse()
{
  u32 val;

  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
  val = REG_JOYRE;

  return val;
}

void sendS32(s32 val)
{
  sendU32(val);
}

void sendU32(u32 val)
{
  REG_JOYTR = val;
}

void directSendU32(u32 val)
{
  REG_JOYTR = val;
  while ((REG_HS_CTRL & JOY_READ) == 0);
  REG_HS_CTRL |= JOY_RW;
}
