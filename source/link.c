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
