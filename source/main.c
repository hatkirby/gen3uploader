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
#include "link.h"
#include "encoding.h"
#include "multiboot.h"
#include "pokemon.h"

void printmain()
{
  printf("\x1b[2J");
  printf("\x1b[37m");
  printf("Pokemon Gen III Data Extractor by hatkirby\n");
  printf("Based on gba-gen3multiboot by slipstream/RoL\n");
  printf("Based on GBA Link Cable Dumper v1.6 by FIX94\n");
}

void endproc()
{
  printf("Start pressed, exit\n");
  VIDEO_WaitVSync();
  VIDEO_WaitVSync();
  exit(0);
}

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

void* extractor(void* userdata)
{
  for (;;)
  {
    printmain();

    printf("Press A when GBA is plugged in and turned off.\n");
    waitForButtons(PAD_BUTTON_A);

    printf("Turn on your GBA.\n");
    printf("Waiting for a GBA in port 2...\n");
    waitForGBA();

    printf("GBA Found! Sending multiboot image...\n");
    if (!sendMultibootImage())
    {
      warnError("Failed sending multiboot image.\n");

      continue;
    }

    printf("Waiting for GBA...\n");
    waitForAck();

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
    sleep(1);

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

    // Get game language.
    enum PokemonLanguage gameLanguage = getMsg();

    char d_trainerName[25];
    decodePokemonCharset(trainerName, 8, d_trainerName, gameLanguage);

    printf("Trainer: %s (%ld)\n", d_trainerName, trainerId);

    // Wait for confirmation.
    printf("Press A to import the data from this game.\n");
    printf("Press B to cancel.\n");
    VIDEO_WaitVSync();

    if (waitForButtons(PAD_BUTTON_A | PAD_BUTTON_B) & PAD_BUTTON_B)
    {
      printf("Cancelling...\n");
      VIDEO_WaitVSync();

      sendMsg(0);

      continue;
    }

    printf("Importing...\n");
    VIDEO_WaitVSync();

    sendMsg(1);

    // Get Pokédex data
    u32 pokedexSeen[13];
    u32 pokedexCaught[13];

    getMsgArr(pokedexSeen, 13);
    getMsgArr(pokedexCaught, 13);

    printf("Saw: ");
    for (int i=0; i<(13*32); i++)
    {
      if (pokedexSeen[i >> 5] >> (i & 31) & 1)
      {
        printf("#%d, ", i+1);
      }
    }

    printf("\nCaught: ");
    for (int i=0; i<(13*32); i++)
    {
      if (pokedexCaught[i >> 5] >> (i & 31) & 1)
      {
        printf("#%d, ", i+1);
      }
    }

    printf("\n");

    sendMsg(1);

    // Start receiving party pokémon.
    printf("Getting party...\n");

    u32 partyCount = getMsg();

    for (u32 i = 0; i < partyCount; i++)
    {
      usleep(5000);

      u32 rawdata[sizeof(struct PokemonIntermediate) / 4];
      getMsgArr(rawdata, sizeof(struct PokemonIntermediate) / 4);

      struct PokemonIntermediate* pki = (struct PokemonIntermediate*)(&rawdata);

      char d_pokename[31];
      decodePokemonCharset(pki->nickname, 10, d_pokename, pki->language);

      char d_otName[22];
      decodePokemonCharset(pki->otName, 7, d_otName, pki->language);

      char d_key[57];
      sprintf(
        d_key,
        "%08lx%08lx%08lx%08lx%08lx%08lx%08lx",
        pki->key[0],
        pki->key[1],
        pki->key[2],
        pki->key[3],
        pki->key[4],
        pki->key[5],
        pki->key[6]);

      printf("Species: %d\n", __builtin_bswap16(pki->species));
      printf("Nickname: %s\n", d_pokename);
      printf("OT: %s\n", d_otName);
      printf("Level: %d\n", pki->level);
      printf("HP: %ld\n", __builtin_bswap32(pki->hp));
      printf("Attack: %ld\n", __builtin_bswap32(pki->attack));
      printf("Defense: %ld\n", __builtin_bswap32(pki->defense));
      printf("Special Attack: %ld\n", __builtin_bswap32(pki->spAttack));
      printf("Special Defense: %ld\n", __builtin_bswap32(pki->spDefense));
      printf("Speed: %ld\n", __builtin_bswap32(pki->speed));
      printf("Key: %s\n", d_key);

      printf("\n");
    }

    waitForButtons(PAD_BUTTON_START);
  }

  return NULL;
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

  initLink();

  lwp_t extractorHandle = (lwp_t)NULL;

  LWP_CreateThread(
    &extractorHandle,   // thread handle
    extractor,          // code
    NULL,               // userdata
    NULL,               // stack base
    16*1024,            // stack size
    LWP_PRIO_HIGHEST);  // thread priority

  for (;;)
  {
    VIDEO_WaitVSync();
    PAD_ScanPads();

    if (PAD_ButtonsDown(0) & PAD_BUTTON_START)
    {
      endproc();
    }
  }

  return 0;
}
