/*
 * Copyright (C) 2016 FIX94
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <gba.h>
#include <stdio.h>
#include <stdlib.h>
#include "libSave.h"
#include "gamedata.h"
#include "link.h"

#define	REG_WAITCNT *(vu16 *)(REG_BASE + 0x204)
#define JOY_WRITE 2
#define JOY_READ 4
#define JOY_RW 6

u8 save_data[0x20000] __attribute__ ((section (".sbss")));

s32 getGameSize(void)
{
  if(*(vu32*)(0x08000004) != 0x51AEFF24)
    return -1;
  s32 i;
  for(i = (1<<20); i < (1<<25); i<<=1)
  {
    vu16 *rompos = (vu16*)(0x08000000+i);
    int j;
    bool romend = true;
    for(j = 0; j < 0x1000; j++)
    {
      if(rompos[j] != j)
      {
        romend = false;
        break;
      }
    }
    if(romend) break;
  }
  return i;
}


// === (from tonc_memdef.h) ===========================================

// --- REG_DISPCNT defines ---
#define DCNT_MODE0     0x0000
#define DCNT_MODE1      0x0001
#define DCNT_MODE2      0x0002
#define DCNT_MODE3      0x0003
#define DCNT_MODE4      0x0004
#define DCNT_MODE5      0x0005
// layers
#define DCNT_BG0        0x0100
#define DCNT_BG1        0x0200
#define DCNT_BG2        0x0400
#define DCNT_BG3        0x0800
#define DCNT_OBJ        0x1000
typedef u16 COLOR;
#define MEM_VRAM    0x06000000
#define SCREEN_WIDTH   240
#define vid_mem     ((u16*)MEM_VRAM)
static inline void m3_plot(int x, int y, COLOR clr)
{   vid_mem[y*SCREEN_WIDTH+x]= clr;    }
static inline COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }
void plot_sqr(int x, int y, COLOR clr)
{
	/*for (int j=0;j<8; j++)
	{
		for (int i=0;i<8; i++)
		{
			vid_mem[(y*8+j+32)*SCREEN_WIDTH+x*8+i+32] = clr;
		}
	}
	vid_mem[(y*8+1+32)*SCREEN_WIDTH+x*8+1+32] = RGB15(31,31,31);*/
}
void m3_fill(COLOR clr) 
{   
    /*int ii;
    u32 *dst= (u32*)vid_mem;
    u32 wd= (clr<<16) | clr;

    for(ii=0; ii<SCREEN_WIDTH/4; ii++)
        *dst++= wd;*/
}

//---------------------------------------------------------------------------------
// Program entry point
//---------------------------------------------------------------------------------
int main(void)
{
	//REG_IME = 0;
  //REG_DISPCNT= DCNT_MODE3 | DCNT_BG2;
	m3_fill(RGB15(31,31,31));
  plot_sqr( 4, 4, RGB15(31, 0, 0) );    // or CLR_RED


	
  //*(vu16 *)(REG_BASE + 0x84) = 0x8f;
  //REG_IME = 1;
  // the vblank interrupt must be enabled for VBlankIntrWait() to work
  // since the default dispatcher handles the bios flags no vblank handler
  // is required
  //irqInit();
  //irqEnable(IRQ_VBLANK);

  //consoleDemoInit();
  //REG_JOYTR = 0;

  // ansi escape sequence to set print co-ordinates
  // /x1b[line;columnH
  //u32 i;
  //iprintf("\x1b[9;2HPokemon Gen III Data Extractor\n");
  //iprintf("\x1b[10;4HPlease look at the TV\n");

  // disable this, needs power
  //SNDSTAT = 0;
  //SNDBIAS = 0;

  // Set up waitstates for EEPROM access etc.
  //REG_WAITCNT = 0x0317;

  //clear out previous messages
  REG_HS_CTRL |= JOY_RW;
	sendU32(0);
  plot_sqr( 4, 5, RGB15( 0,31, 0) );    // or CLR_LIME
  while (1)
  {
		waitForWriteAccess();
		//while (recieveU32() != 0);
		//waitForAck();
  plot_sqr( 4, 6, RGB15( 0, 0,31) );    // or CLR_BLUE
    // Send game size to acknowledge that an actual cart is inserted.
    //s32 gamesize = getGameSize();
    //sendS32(gamesize);
    //waitForAck();

    // If the game size is illegal, start over.
    //if (gamesize == -1)
    //{
    //  sendS32(0);
		//
    //  continue;
    //}

    // Identify the inserted game.
    if (GAME_RUBY)
    {
      sendS32(1);
    } else if (GAME_SAPP)
    {
      sendS32(2);
    } else if (GAME_FR)
    {
      sendS32(3);
    } else if (GAME_LG)
    {
      sendS32(4);
    } else if (GAME_EM)
    {
      sendS32(5);
    } else {
      sendS32(-1);
      waitForAck();

      sendS32(0);

      continue;
    }
  plot_sqr( 5, 4, RGB15( 31, 0,31) );
    waitForAck();
  plot_sqr( 5, 5, RGB15( 16, 16,16) );
    // Get access to save data.
    pSaveBlock1 SaveBlock1;
    pSaveBlock2 SaveBlock2;
    pSaveBlock3 SaveBlock3;
    if (!initSaveData(&SaveBlock1, &SaveBlock2, &SaveBlock3))
    {
      // Unsupported game version.
      //iprintf("Unsupported game version\n");
      sendS32(-1);
      waitForAck();

      sendS32(0);

      continue;
    }
  plot_sqr( 5, 6, RGB15( 0, 31,16) );
    sendS32(1);
    waitForAck();
		/*
    // Send trainer name.
    u8* trainerName;

    if (GAME_RS)
    {
      trainerName = SaveBlock2->rs.playerName;
    } else if (GAME_FRLG)
    {
      trainerName = SaveBlock2->frlg.playerName;
    } else if (GAME_EM)
    {
      trainerName = SaveBlock2->e.playerName;
    }
    iprintf("%d\n", trainerName[0]);
    iprintf("%d\n", trainerName[1]);
    iprintf("%d\n", trainerName[2]);
    iprintf("%d\n", trainerName[3]);
    iprintf("%d\n", trainerName[4]);
    iprintf("%d\n", trainerName[5]);
    iprintf("%d\n", trainerName[6]);
    iprintf("%d\n", trainerName[7]);

    u32 tn1 =
        (trainerName[0] << 24)
      | (trainerName[1] << 16)
      | (trainerName[2] << 8)
      | (trainerName[3]);

    u32 tn2 =
        (trainerName[4] << 24)
      | (trainerName[5] << 16)
      | (trainerName[6] << 8)
      | (trainerName[7]);

    sendU32(tn1);
    waitForAck();

    sendU32(tn2);
    waitForAck();
*/
    // Send trainer ID.
    u8* trainerId = 0;

    if (GAME_RS)
    {
      trainerId = SaveBlock2->rs.playerTrainerId;
    } else if (GAME_FRLG)
    {
      trainerId = SaveBlock2->frlg.playerTrainerId;
    } else if (GAME_EM)
    {
      trainerId = SaveBlock2->e.playerTrainerId;
    }

    u32 tti =
        (trainerId[2] << 8)
      | (trainerId[3]);

    sendU32(tti);
    waitForAck();

    // Restart, because we're just testing.
    sendS32(0);
    //continue;
		break;

/*


      //game in, send header
      for(i = 0; i < 0xC0; i+=4)
      {
        REG_JOYTR = *(vu32*)(0x08000000+i);
        while((REG_HS_CTRL&JOY_READ) == 0) ;
        REG_HS_CTRL |= JOY_RW;
      }
      REG_JOYTR = 0;
      //wait for other side to choose
      while((REG_HS_CTRL&JOY_WRITE) == 0) ;
      REG_HS_CTRL |= JOY_RW;
      u32 choseval = REG_JOYRE;
      if(choseval == 0)
      {
        REG_JOYTR = 0;
        continue; //nothing to read
      }
      else if(choseval == 1)
      {
        //disable interrupts
        u32 prevIrqMask = REG_IME;
        REG_IME = 0;
        //dump the game
        for(i = 0; i < gamesize; i+=4)
        {
          REG_JOYTR = *(vu32*)(0x08000000+i);
          while((REG_HS_CTRL&JOY_READ) == 0) ;
          REG_HS_CTRL |= JOY_RW;
        }
        //restore interrupts
        REG_IME = prevIrqMask;
      }
      else if(choseval == 2)
      {
        //disable interrupts
        u32 prevIrqMask = REG_IME;
        REG_IME = 0;
        //backup save
        switch (savesize){
          case 0x200:
            GetSave_EEPROM_512B(save_data);
            break;
          case 0x2000:
            GetSave_EEPROM_8KB(save_data);
            break;
          case 0x8000:
            GetSave_SRAM_32KB(save_data);
            break;
          case 0x10000:
            GetSave_FLASH_64KB(save_data);
            break;
          case 0x20000:
            GetSave_FLASH_128KB(save_data);
            break;
          default:
            break;
        }
        //restore interrupts
        REG_IME = prevIrqMask;
        //say gc side we read it
        REG_JOYTR = savesize;
        //wait for a cmd receive for safety
        while((REG_HS_CTRL&JOY_WRITE) == 0) ;
        REG_HS_CTRL |= JOY_RW;
        //send the save
        for(i = 0; i < savesize; i+=4)
        {
          REG_JOYTR = *(vu32*)(save_data+i);
          while((REG_HS_CTRL&JOY_READ) == 0) ;
          REG_HS_CTRL |= JOY_RW;
        }
      }
      else if(choseval == 3 || choseval == 4)
      {
        REG_JOYTR = savesize;
        if(choseval == 3)
        {
          //receive the save
          for(i = 0; i < savesize; i+=4)
          {
            while((REG_HS_CTRL&JOY_WRITE) == 0) ;
            REG_HS_CTRL |= JOY_RW;
            *(vu32*)(save_data+i) = REG_JOYRE;
          }
        }
        else
        {
          //clear the save
          for(i = 0; i < savesize; i+=4)
            *(vu32*)(save_data+i) = 0;
        }
        //disable interrupts
        u32 prevIrqMask = REG_IME;
        REG_IME = 0;
        //write it
        switch (savesize){
          case 0x200:
            PutSave_EEPROM_512B(save_data);
            break;
          case 0x2000:
            PutSave_EEPROM_8KB(save_data);
            break;
          case 0x8000:
            PutSave_SRAM_32KB(save_data);
            break;
          case 0x10000:
            PutSave_FLASH_64KB(save_data);
            break;
          case 0x20000:
            PutSave_FLASH_128KB(save_data);
            break;
          default:
            break;
        }
        //restore interrupts
        REG_IME = prevIrqMask;
        //say gc side we're done
        REG_JOYTR = 0;
        //wait for a cmd receive for safety
        while((REG_HS_CTRL&JOY_WRITE) == 0) ;
        REG_HS_CTRL |= JOY_RW;
      }
      REG_JOYTR = 0;
    }
    } else if(REG_HS_CTRL&JOY_WRITE)
    {
      REG_HS_CTRL |= JOY_RW;
      u32 choseval = REG_JOYRE;
      if(choseval == 5)
      {
        //disable interrupts
        u32 prevIrqMask = REG_IME;
        REG_IME = 0;
        //dump BIOS
        for (i = 0; i < 0x4000; i+=4)
        {
          // the lower bits are inaccurate, so just get it four times :)
          u32 a = MidiKey2Freq((WaveData *)(i-4), 180-12, 0) * 2;
          u32 b = MidiKey2Freq((WaveData *)(i-3), 180-12, 0) * 2;
          u32 c = MidiKey2Freq((WaveData *)(i-2), 180-12, 0) * 2;
          u32 d = MidiKey2Freq((WaveData *)(i-1), 180-12, 0) * 2;
          REG_JOYTR = ((a>>24<<24) | (d>>24<<16) | (c>>24<<8) | (b>>24));
          while((REG_HS_CTRL&JOY_READ) == 0) ;
          REG_HS_CTRL |= JOY_RW;
        }
        //restore interrupts
        REG_IME = prevIrqMask;
      }
      REG_JOYTR = 0;
    }*/
    Halt();
  }
}


