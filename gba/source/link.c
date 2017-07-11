#include "link.h"

#define JOY_WRITE 2
#define JOY_READ 4
#define JOY_RW 6

void waitForWriteAccess()
{
  //while ((REG_HS_CTRL & JOY_READ) == 0);
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
	//waitForWriteAccess();
}

void sendU32(u32 val)
{
  REG_JOYTR = val;
	//waitForWriteAccess();
}

u32 recieveU32()
{
  while ((REG_HS_CTRL & JOY_WRITE) == 0);
  REG_HS_CTRL |= JOY_RW;
	return REG_JOYRE;
}

