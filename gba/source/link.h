#ifndef _LINK_H_
#define _LINK_H_

#include <gba.h>

void waitForWriteAccess();
void waitForAck();
void sendS32(s32 val);
void sendU32(u32 val);
u32 recieveU32();

#endif
