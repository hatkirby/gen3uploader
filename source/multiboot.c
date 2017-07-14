#include "multiboot.h"
#include <gccore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "link.h"

extern u8 gba_mb_gba[];
extern u32 gba_mb_gba_size;

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

bool sendMultibootImage()
{
  printf("Waiting on BIOS\n");
  waitForBIOS();

  printf("BIOS handed over to game, waiting on game\n");
  waitForGame();

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
    return false;
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

    return false;
  }

  // derive the boot key from the found KeyC, and send to GBA. if this is
  // not correct, GBA will not jump to the multiboot image it was sent.
  u32 bootkey = docrc(0xBB,keyc) | 0xbb000000;
  printf("BootKey = 0x%08lx\n",bootkey);

  send(bootkey);
  sleep(2);

  return true;
}
