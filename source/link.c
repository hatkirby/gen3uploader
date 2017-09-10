/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "link.h"
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

//from my tests 50us seems to be the lowest
//safe si transfer delay in between calls
#define SI_TRANS_DELAY 500

static u8* resbuf;
static u8* cmdbuf;

void initLink()
{
  cmdbuf = memalign(32,32);
  resbuf = memalign(32,32);
}

static volatile u32 transval = 0;
void transcb(s32 chan, u32 ret)
{
  transval = 1;
}

static volatile u32 resval = 0;
void acb(s32 res, u32 val)
{
  resval = val;
}

void doreset()
{
  cmdbuf[0] = 0xFF; //reset
  transval = 0;
  SI_Transfer(1, cmdbuf, 1, resbuf, 3, transcb, SI_TRANS_DELAY);

  while (transval == 0);
}

void getstatus()
{
  cmdbuf[0] = 0; //status
  transval = 0;
  SI_Transfer(1, cmdbuf, 1, resbuf, 3, transcb, SI_TRANS_DELAY);

  while (transval == 0);
}

u32 recv()
{
  memset(resbuf,0,32);
  cmdbuf[0]=0x14; //read
  transval = 0;
  SI_Transfer(1, cmdbuf, 1, resbuf, 5, transcb, SI_TRANS_DELAY);

  while (transval == 0);
  //printf("%08lx\n", *(vu32*)resbuf);
  return *(vu32*)resbuf;
}

void send(u32 msg)
{
  cmdbuf[0] = 0x15;
  cmdbuf[1] = (msg >> 0) & 0xFF;
  cmdbuf[2] = (msg >> 8) & 0xFF;
  cmdbuf[3] = (msg >> 16) & 0xFF;
  cmdbuf[4] = (msg >> 24) & 0xFF;

  transval = 0;
  resbuf[0] = 0;
  SI_Transfer(1, cmdbuf, 5, resbuf, 1, transcb, SI_TRANS_DELAY);

  while (transval == 0);
}

u32 getMsg()
{
  u32 val = __builtin_bswap32(recv());
  send(0);

  return val;
}

void getMsgArr(u32* arr, int len)
{
  for (int i=0; i<len; i++)
  {
    *(vu32*)(arr+i) = recv();
  }
}

void sendMsg(u32 msg)
{
  send(msg);
}

void waitForGBA()
{
  resval = 0;

  do
  {
    SI_GetTypeAsync(1, acb);

    for (;;)
    {
      if (resval)
      {
        if (resval == 0x80 || resval & 8)
        {
          resval = 0;
          SI_GetTypeAsync(1, acb);
        } else if (resval)
        {
          break;
        }
      }
    }
  } while (!(resval & SI_GBA));
}

void waitForBIOS()
{
  resbuf[2]=0;

  do
  {
    doreset();
  } while (!(resbuf[1] > 4));
}

void waitForGame()
{
  do
  {
    doreset();
  } while ((resbuf[0] != 0) || !(resbuf[2] & 0x10));
}

void waitForAck()
{
  while (recv() != 0) {sleep(1);}
}
