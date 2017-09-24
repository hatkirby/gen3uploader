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
#include <fat.h>
#include "cJSON.h"
#include "link.h"
#include "encoding.h"
#include "multiboot.h"
#include "pokemon.h"
#include "http.h"
#include "netinf.h"
#include "deserialize.h"

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

cJSON* getConfig()
{
  FILE* fp = fopen("/gen3uploader.cfg", "r");
  if (!fp)
  {
    fatalError("ERROR: Could not find config file!\n");
  }

  fseek(fp, 0L, SEEK_END);
  long lSize = ftell(fp);
  rewind(fp);

  char* buffer = calloc(1, lSize+1);
  if (!buffer)
  {
    fclose(fp);
    fatalError("ERROR: Could not allocate memory.\n");
  }

  if (fread(buffer, lSize, 1, fp) != 1)
  {
    fclose(fp);
    free(buffer);
    fatalError("ERROR: Could not read config file.\n");
  }

  cJSON* config = cJSON_Parse(buffer);

  fclose(fp);
  free(buffer);

  return config;
}

void* extractor(void* userdata)
{
  cJSON* config = (cJSON*)userdata;

  WOLFSSL_CTX* sslContext = 0;
  if (cJSON_HasObjectItem(config, "certificate"))
  {
    wolfSSL_Init();

    sslContext = wolfSSL_CTX_new(wolfTLSv1_client_method());
    if (sslContext == NULL)
    {
      fatalError("wolfSSL_CTX_new error.\n");
    }

    if (wolfSSL_CTX_load_verify_locations(
      sslContext,
      cJSON_GetObjectItem(config, "certificate")->valuestring,
      0) != SSL_SUCCESS)
    {
      fatalError("Error loading certificate file.\n");
    }
  }

  while (!initializeNetwork())
  {
    printf("Could not initialize network.\n");
    printf("Press A to try again, press B to exit.\n");

    if (waitForButtons(PAD_BUTTON_A | PAD_BUTTON_B) == PAD_BUTTON_B)
    {
      endproc();
    }
  }

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

    cJSON* root = cJSON_CreateObject();

    cJSON_AddItemToObject(
      root,
      "playerName",
      cJSON_CreateString(d_trainerName));

    cJSON_AddNumberToObject(root, "playerId", trainerId);
    cJSON_AddNumberToObject(root, "gameId", gameId);
    cJSON_AddNumberToObject(root, "language", gameLanguage);

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

    // Start receiving pokémon.
    printf("Getting party...\n");

    u32 partyCount = getMsg();

    cJSON* jParty = cJSON_CreateArray();

    for (u32 i = 0; i < partyCount; i++)
    {
      usleep(5000);

      u32 rawdata[sizeof(struct PokemonIntermediate) / 4];
      getMsgArr(rawdata, sizeof(struct PokemonIntermediate) / 4);

      struct PokemonIntermediate* pki = (struct PokemonIntermediate*)(&rawdata);

      cJSON* jPoke = pokemonToJson(pki);

      cJSON_AddStringToObject(jPoke, "storage", "party");
      cJSON_AddNumberToObject(jPoke, "slot", i);

      cJSON_AddItemToArray(jParty, jPoke);
    }

    for (int i=0; i<14; i++)
    {
      printf("Getting box %d...\n", i+1);

      for (int j=0; j<30; j++)
      {
        int isPoke = getMsg();

        if (isPoke == 1)
        {
          usleep(5000);

          u32 rawdata[sizeof(struct PokemonIntermediate) / 4];
          getMsgArr(rawdata, sizeof(struct PokemonIntermediate) / 4);

          struct PokemonIntermediate* pki =
            (struct PokemonIntermediate*)(&rawdata);

          cJSON* jPoke = pokemonToJson(pki);

          cJSON_AddStringToObject(jPoke, "storage", "box");
          cJSON_AddNumberToObject(jPoke, "box", i);
          cJSON_AddNumberToObject(jPoke, "slot", j);

          cJSON_AddItemToArray(jParty, jPoke);
        }
      }
    }

    cJSON_AddItemToObject(root, "pokemon", jParty);

    char *rendered = cJSON_Print(root);
    //printf("%s\n", rendered);

    printf("Press A to send.\n");

    waitForButtons(PAD_BUTTON_A);

    int result = submitToApi(
      cJSON_GetObjectItem(config, "url")->valuestring,
      sslContext,
      root,
      cJSON_GetObjectItem(config, "username")->valuestring,
      cJSON_GetObjectItem(config, "password")->valuestring);

    printf("Result: %d\n", result);

    waitForButtons(PAD_BUTTON_A);
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

  if (!fatInitDefault())
  {
    printmain();
    fatalError("ERROR: Cannot find config file!\n");
  }

  cJSON* config = getConfig();

  initLink();

  lwp_t extractorHandle = (lwp_t)NULL;

  LWP_CreateThread(
    &extractorHandle,   // thread handle
    extractor,          // code
    config,             // userdata
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
