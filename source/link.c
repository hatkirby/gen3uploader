/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "link.h"

u32 waitForButtons(u32 mask)
{
  for (;;)
  {
    PAD_ScanPads();
    VIDEO_WaitVSync();

    u32 btns = PAD_ButtonsDown(0);
    if (btns & mask)
    {
      return btns;
    }
  }
}
