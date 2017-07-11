/*
 * Copyright (C) 2017 hatkirby
 * Copyright (C) 2017 slipstream/RoL
 * Copyright (C) 2016 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <gccore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include "link.h"
#include "encoding.h"

//from my tests 50us seems to be the lowest
//safe si transfer delay in between calls
#define SI_TRANS_DELAY 50

extern u8 gba_mb_gba[];
extern u32 gba_mb_gba_size;

void printmain()
{
  printf("\x1b[2J");
  printf("\x1b[37m");
  printf("Pokemon Gen III Data Extractor by hatkirby\n");
	printf("Based on gba-gen3multiboot by slipstream/RoL\n");
  printf("Based on GBA Link Cable Dumper v1.6 by FIX94\n");
}

u8 *resbuf,*cmdbuf;

volatile u32 transval = 0;
void transcb(s32 chan, u32 ret)
{
  transval = 1;
}

volatile u32 resval = 0;
void acb(s32 res, u32 val)
{
  resval = val;
}

unsigned int docrc(u32 crc,u32 val)
{
	u32 result;

	result = val ^ crc;
	for (int i = 0; i < 0x20; i++)
	{
		if (result & 1)
		{
			result >>= 1;
			result ^= 0xA1C1;
		} else {
			result >>= 1;
		}
	}

	return result;
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

void endproc()
{
	doreset();
  printf("Start pressed, exit\n");
  VIDEO_WaitVSync();
  VIDEO_WaitVSync();
  exit(0);
}

u32 recv()
{
  memset(resbuf,0,32);
  cmdbuf[0]=0x14; //read
  transval = 0;
  SI_Transfer(1, cmdbuf, 1, resbuf, 5, transcb, SI_TRANS_DELAY);

	while (transval == 0);
	printf("%08lx\n", *(vu32*)resbuf);
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

void warnError(char *msg)
{
  puts(msg);
  VIDEO_WaitVSync();
  VIDEO_WaitVSync();
  sleep(2);
}

void fatalError(char *msg)
{
  puts(msg);
  VIDEO_WaitVSync();
  VIDEO_WaitVSync();
  sleep(5);
  exit(0);
}

u32 genKeyA()
{
	u32 retries = 0;

	for (;;)
	{
		u32 key = 0;

		if (retries > 32)
		{
			key = 0xDD654321;
		} else {
			key = (rand() & 0x00ffffff) | 0xDD000000;
		}

		u32 unk = (key % 2 != 0);
		u32 v12 = key;
		for (u32 v13 = 1; v13 < 32; v13++)
		{
			v12 >>= 1;
			unk += (v12 % 2 != 0);
		}

		if ((unk >= 10 && unk <= 24))
		{
			if (retries > 4)
			{
				printf("KeyA retries = %ld", retries);
			}

			printf("KeyA = 0x%08lx\n", key);

			return key;
		}

		retries++;
	}
}

u32 checkKeyB(u32 KeyBRaw)
{
	if ((KeyBRaw & 0xFF) != 0xEE)
	{
		printf("Invalid KeyB - lowest 8 bits should be 0xEE, actually 0x%02x\n",
			((u8)(KeyBRaw)));

		return 0;
	}

	u32 KeyB = KeyBRaw & 0xffffff00;
	u32 val = KeyB;
	u32 unk = (val < 0);
	for (u32 i = 1; i < 24; i++)
	{
		val <<= 1;
		unk += (val < 0);
	}

	if (unk > 14)
	{
		printf("Invalid KeyB - high 24 bits bad: 0x%08lx\n", KeyB);

		return 0;
	}

	printf("Valid KeyB: 0x%08lx\n", KeyB);

	return KeyB;
}

u32 deriveKeyC(u32 keyCderive, u32 kcrc)
{
	u32 keyc = 0;
	u32 keyCi = 0;

	do
	{
		u32 v5 = 0x1000000 * keyCi - 1;
		u32 keyCattempt = docrc(kcrc,v5);

		if (keyCderive == keyCattempt)
		{
			keyc = v5;

			printf("Found keyC: %08lx\n",keyc);

			return keyc;
		}

		keyCi++;
	} while (keyCi < 256);

	return keyc;
}

u32 getMsg()
{
  u32 val = 0;
	while (val == 0)
	{
		val = __builtin_bswap32(recv());
		sleep(1);
	}

  send(0);
	while (recv()!=0) {sleep(1);};
	send(0);

	return val;
}

int main(int argc, char *argv[])
{
  void *xfb = NULL;
  GXRModeObj *rmode = NULL;
  VIDEO_Init();
  rmode = VIDEO_GetPreferredMode(NULL);
  xfb = MEM_K0_TO_K1(SYS_AllocateFramebuffer(rmode));
  VIDEO_Configure(rmode);
  VIDEO_SetNextFramebuffer(xfb);
  VIDEO_SetBlack(FALSE);
  VIDEO_Flush();
  VIDEO_WaitVSync();
  if(rmode->viTVMode&VI_NON_INTERLACE) VIDEO_WaitVSync();
  int x = 24, y = 32, w, h;
  w = rmode->fbWidth - (32);
  h = rmode->xfbHeight - (48);
  CON_InitEx(rmode, x, y, w, h);
  VIDEO_ClearFrameBuffer(rmode, xfb, COLOR_BLACK);
  PAD_Init();
  cmdbuf = memalign(32,32);
  resbuf = memalign(32,32);

  for (;;)
  {
    printmain();

		printf("Press A to begin, press Start to quit.\n");
		if (waitForButtons(PAD_BUTTON_A | PAD_BUTTON_START) & PAD_BUTTON_START)
		{
			endproc();
		}

    printf("Waiting for a GBA in port 2...\n");
    resval = 0;

    SI_GetTypeAsync(1,acb);
    while(1)
    {
      if (resval)
      {
        if (resval == 0x80 || resval & 8)
        {
          resval = 0;
          SI_GetTypeAsync(1,acb);
        } else if (resval)
        {
          break;
        }
      }

      PAD_ScanPads();
      VIDEO_WaitVSync();
      if (PAD_ButtonsHeld(0) & PAD_BUTTON_START)
      {
				getstatus();
        endproc();
      }
    }

    if (resval & SI_GBA)
    {
      printf("GBA Found! Waiting on BIOS\n");

			resbuf[2]=0;

			// wait for the BIOS to hand over to the game
			do
			{
				doreset();
			} while (!(resbuf[1] > 4));

			printf("BIOS handed over to game, waiting on game\n");

			do
			{
				doreset();
			} while ((resbuf[0] != 0) || !(resbuf[2] & 0x10));

			// receive the game-code from GBA side.
			u32 gamecode = recv();

			printf("Ready, sending multiboot ROM\n");

			unsigned int sendsize = ((gba_mb_gba_size+7)&~7);

			// generate KeyA
			unsigned int ourkey = genKeyA();

			//printf("Our Key: %08x\n", ourkey);
			printf("Sending game code that we got: 0x%08lx\n",
				__builtin_bswap32(gamecode));

			// send the game code back, then KeyA.
			send(__builtin_bswap32(gamecode));
			send(ourkey);

			// get KeyB from GBA, check it to make sure its valid, then xor with KeyA
			// to derive the initial CRC value and the sessionkey.
			u32 sessionkeyraw = 0;
			do
			{
				sessionkeyraw = recv();
			} while (sessionkeyraw == gamecode);

			sessionkeyraw = checkKeyB(__builtin_bswap32(sessionkeyraw));
			if (sessionkeyraw == 0)
			{
				warnError("Cannot continue.\n");

				continue;
			}

			u32 sessionkey = sessionkeyraw ^ ourkey;
			u32 kcrc = sessionkey;
			printf("start kCRC=%08lx\n",kcrc);

			sessionkey = (sessionkey*0x6177614b)+1;

			// send hacked up send-size in uint32s
			u32 hackedupsize = (sendsize >> 3) - 1;

			printf("Sending hacked up size 0x%08lx\n",hackedupsize);
			send(hackedupsize);

			//unsigned int fcrc = 0x00bb;
			// send over multiboot binary header, in the clear until the end of the
			// nintendo logo. GBA checks this, if nintendo logo does not match the
			// one in currently inserted cart's ROM, it will not accept any more data.
			for (int i = 0; i < 0xA0; i+=4)
			{
				vu32 rom_dword = *(vu32*)(gba_mb_gba+i);
				send(__builtin_bswap32(rom_dword));
			}

			printf("\n");
			printf("Header done! Sending ROM...\n");

			// Add each uint32 of the multiboot image to the checksum, encrypt the
			// uint32 with the session key, increment the session key, send the
			// encrypted uint32.
			for (int i = 0xA0; i < sendsize; i+=4)
			{
				u32 dec = (
					(((gba_mb_gba[i+3]) << 24) & 0xff000000) |
					(((gba_mb_gba[i+2]) << 16) & 0x00ff0000) |
					(((gba_mb_gba[i+1]) << 8)  & 0x0000ff00) |
					(((gba_mb_gba[i])   << 0)  & 0x000000ff)
				);

				u32 enc = (dec - kcrc) ^ sessionkey;
				kcrc = docrc(kcrc,dec);
				sessionkey = (sessionkey * 0x6177614B) + 1;
				//enc^=((~(i+(0x20<<20)))+1);
				//enc^=0x6f646573;//0x20796220;

				send(enc);
			}

			//fcrc |= (sendsize<<16);
			printf("ROM done! CRC: %08lx\n", kcrc);
			//get crc back (unused)

			// Get KeyC derivation material from GBA (eventually)
			u32 keyCderive = 0;
			do
			{
				keyCderive = recv();
			} while (keyCderive <= 0xfeffffff);

			keyCderive = __builtin_bswap32(keyCderive);
			keyCderive >>= 8;

			printf("KeyC derivation material: %08lx\n",keyCderive);

			// (try to) find the KeyC, using the checksum of the multiboot image, and
			// the derivation material that GBA sent to us
			u32 keyc = deriveKeyC(keyCderive,kcrc);
			if (keyc == 0)
			{
				printf("Could not find keyC - kcrc=0x%08lx\n",kcrc);
        warnError("Cannot continue.\n");

				continue;
			}

			// derive the boot key from the found KeyC, and send to GBA. if this is
      // not correct, GBA will not jump to the multiboot image it was sent.
			u32 bootkey = docrc(0xBB,keyc) | 0xbb000000;
			printf("BootKey = 0x%08lx\n",bootkey);

			send(bootkey);
			sleep(2);

			printf("Waiting for GBA...\n");
			while (recv() != 0) {sleep(1);};
			send(0);

      VIDEO_WaitVSync();

      // Get game
      // -1 - unsupported game
      //  1 - Ruby
      //  2 - Sapphire
      //  3 - FireRed
      //  4 - LeafGreen
      //  5 - Emerald
      u32 gameId = getMsg();
      if (gameId == -1)
      {
        warnError("ERROR: Unsupported GBA game inserted!\n");

        continue;
      }

      printf("\nPokemon ");
      switch (gameId)
      {
        case 1: printf("Ruby"); break;
        case 2: printf("Sapphire"); break;
        case 3: printf("FireRed"); break;
        case 4: printf("LeafGreen"); break;
        case 5: printf("Emerald"); break;
      }

      printf("\n");
			VIDEO_WaitVSync();

			u32 isValid = getMsg();
      if (isValid == -1)
      {
        warnError("ERROR: Unsupported game version inserted!\n");

        continue;
      }

      // Get trainer name
      u8 trainerName[8];

      u32 tnd = getMsg();
      trainerName[0] = (tnd & 0xFF000000) >> 24;
      trainerName[1] = (tnd & 0x00FF0000) >> 16;
      trainerName[2] = (tnd & 0x0000FF00) >> 8;
      trainerName[3] = (tnd & 0x000000FF);

      tnd = getMsg();
      trainerName[4] = (tnd & 0xFF000000) >> 24;
      trainerName[5] = (tnd & 0x00FF0000) >> 16;
      trainerName[6] = (tnd & 0x0000FF00) >> 8;
      trainerName[7] = (tnd & 0x000000FF);

      // Get trainer ID
      u32 trainerId = getMsg();

      printf("Trainer: ");

			for (int i = 0; i < 8; i++)
			{
				if (trainerName[i] == 0xFF)
				{
					break;
				} else {
					printf("%c", debugGen3Decode(trainerName[i]));
				}
			}

      printf(" (%ld)\n", trainerId);

      // Wait for confirmation.
      printf("Press A to import the data from this game.\n");
      printf("Press B to cancel.\n");
			VIDEO_WaitVSync();

      if (waitForButtons(PAD_BUTTON_A | PAD_BUTTON_B) & PAD_BUTTON_B)
      {
        continue;
      }
    }
  }

  return 0;
}
