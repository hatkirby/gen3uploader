/*
 * Copyright (C) 2017 hatkirby
 * Copyright (C) 2017 slipstream/RoL
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "gamedata.h"

static void decryptSaveStructures(
    pSaveBlock1 SaveBlock1,
    pSaveBlock2 SaveBlock2,
    pSaveBlock3 SaveBlock3)
{
  if (GAME_RS)
  {
    // R/S doesn't have save crypto.
    return;
  }

  u8* sb1raw = (u8*)SaveBlock1;
  u8* sb2raw = (u8*)SaveBlock2;
  //u8* sb3raw = (u8*)SaveBlock3; // unused

  u32* xor_key_ptr = (u32*)(&sb2raw[( GAME_EM ? 0xA8 : 0xF20 )]);

  u32 xor_key = *xor_key_ptr;
  u16 xor_key16 = (u16)xor_key;
  if (!xor_key)
  {
    // xor key is zero, nothing needs to be done.
    return;
  }

  u32* ptr_to_xor;
  u32 save_offset;
  int i;
  u32* bag_pocket_offsets;
  u32* bag_pocket_counts;
  if (GAME_FRLG)
  {
    // loop over and decrypt various things
    save_offset = 0x3D38 + 4;
    for (i = 3; i >= 0; i--)
    {
      ptr_to_xor = (u32*)(&sb1raw[save_offset]);
      *ptr_to_xor ^= xor_key;
      save_offset += 12;
    }

    for (i = 0; i <= 0x3f; i++)
    {
      save_offset = 0x1200 + (i*sizeof(u32));
      ptr_to_xor = (u32*)(&sb1raw[save_offset]);
      *ptr_to_xor ^= xor_key;
    }

    // loop over each of the bag pockets and decrypt decrypt decrypt
    bag_pocket_offsets = (u32[5]) { 0x310, 0x388, 0x430, 0x464, 0x54C };
    bag_pocket_counts = (u32[5]) { 42, 30, 13, 58, 43 };

    for (i = 0; i < 5; i++)
    {
      for (int bag_i = 0; bag_i < bag_pocket_counts[i]; bag_i++)
      {
        save_offset = bag_pocket_offsets[i] + (sizeof(u32) * bag_i) + 2;
        *(u16*)(&sb1raw[save_offset]) ^= xor_key16;
      }
    }

    // decrypt some more stuff
    save_offset = 0xaf8;
    ptr_to_xor = (u32*)(&sb1raw[save_offset]);
    *ptr_to_xor ^= xor_key;

    save_offset = 0x290;
    ptr_to_xor = (u32*)(&sb1raw[save_offset]);
    *ptr_to_xor ^= xor_key;

    save_offset = 0x294;
    *(u16*)(&sb1raw[save_offset]) ^= xor_key16;
  } else {
    // Emerald

    // loop over and decrypt various things
    for (i = 0; i <= 0x3f; i++)
    {
      save_offset = 0x159c + (i*sizeof(u32));
      ptr_to_xor = (u32*)(&sb1raw[save_offset]);
      *ptr_to_xor ^= xor_key;
    }

    // loop over each of the bag pockets and decrypt decrypt decrypt
    bag_pocket_offsets = (u32[5]) { 0x560, 0x5D8, 0x650, 0x690, 0x790 };
    bag_pocket_counts = (u32[5]) { 30, 30, 16, 64, 46 };

    for (i = 0; i < 5; i++)
    {
      for (int bag_i = 0; bag_i < bag_pocket_counts[i]; bag_i++)
      {
        save_offset = bag_pocket_offsets[i] + (sizeof(u32) * bag_i) + 2;
        *(u16*)(&sb1raw[save_offset]) ^= xor_key16;
      }
    }

    // decrypt some more stuff
    save_offset = 0x1F4;
    ptr_to_xor = (u32*)(&sb1raw[save_offset]);
    *ptr_to_xor ^= xor_key;

    save_offset = 0x490;
    ptr_to_xor = (u32*)(&sb1raw[save_offset]);
    *ptr_to_xor ^= xor_key;

    save_offset = 0x494;
    *(u16*)(&sb1raw[save_offset]) ^= xor_key16;
  }

  *xor_key_ptr = 0;
}

static void CryptBoxPokemon(struct BoxPokemon* pkm)
{
	for (u32 i = 0; i < 12; i++)
  {
		pkm->secure.raw[i] ^= (pkm->otId ^ pkm->personality);
	}
}

bool initSaveData(struct GameData* gameData)
{
  // check the ROM code, make sure this game is supported.
  u8* ROM = (u8*) 0x8000000;

  u32 gamecode = (*(u32*)(&ROM[0xAC]));

  void(*loadsave)(char a1);
  //void(*mainloop)();
  //void(*load_pokemon)();
  pSaveBlock1 gSaveBlock1;
  pSaveBlock2 gSaveBlock2;
  pSaveBlock3 gSaveBlock3;
  struct BaseStats* gBaseStats;
  const u32 (*gExpTables)[101];
  const u16* gNatOrder;
  //u32 titlemid = 0;

  // get the address of the save loading function.
  switch (gamecode)
  {
    // --- R/S ---
    case 'DVXA': // Ruby German
    case 'DPXA': // Sapphire German
    {
      // TODO: detect debug ROM?
      gSaveBlock1 = (pSaveBlock1) 0x2025734;
      gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
      gSaveBlock3 = (pSaveBlock3) 0x20300A0;
      loadsave = (void(*)(char)) 0x8126249; // same for v1.0 + v1.1
      //mainloop = (void(*)()) 0x80003D9;
      //load_pokemon = (void(*)()) 0x8047da9;

      break;
    }

    case 'FVXA': // Ruby French
    case 'FPXA': // Sapphire French
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025734;
      gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
      gSaveBlock3 = (pSaveBlock3) 0x20300A0;
      loadsave = (void(*)(char)) 0x8126351; // same for v1.0 + v1.1
      //mainloop = (void(*)()) 0x80003D9;
      //load_pokemon = (void(*)()) 0x8047e95;

      break;
    }

    case 'IVXA': // Ruby Italian
    case 'IPXA': // Sapphire Italian
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025734;
      gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
      gSaveBlock3 = (pSaveBlock3) 0x20300A0;
      loadsave = (void(*)(char)) 0x8126249; // same for v1.0 + v1.1
      //mainloop = (void(*)()) 0x80003D9;
      //load_pokemon = (void(*)()) 0x8047dbd;

      break;
    }

    case 'SVXA': // Ruby Spanish
    case 'SPXA': // Sapphire Spanish
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025734;
      gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
      gSaveBlock3 = (pSaveBlock3) 0x20300A0;
      loadsave = (void(*)(char)) 0x8126349; // same for v1.0 + v1.1
      //mainloop = (void(*)()) 0x80003D9;
      //load_pokemon = (void(*)()) 0x8047ea5;

      break;
    }

    case 'EVXA': // Ruby English
    case 'EPXA': // Sapphire English
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025734;
      gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
      gSaveBlock3 = (pSaveBlock3) 0x20300A0;
      //mainloop = (void(*)()) 0x80002A5;

      // version number
      switch (ROM[0xBC])
      {
        case 0:
        {
          loadsave = (void(*)(char)) 0x8125EC9;
          //load_pokemon = (void(*)()) 0x8047a85;

          break;
        }

        case 1:
        case 2:
        {
          loadsave = (void(*)(char)) 0x8125EE9;
          //load_pokemon = (void(*)()) 0x8047aa5;

          break;
        }

        default:
        {
          return false; // unsupported version
        }
      }

      break;
    }

    case 'JVXA': // Ruby Japanese
    case 'JPXA': // Sapphire Japanese
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025494;
      gSaveBlock2 = (pSaveBlock2) 0x2024C04;
      gSaveBlock3 = (pSaveBlock3) 0x202FDBC;
      loadsave = (void(*)(char)) 0x8120d05; // same for v1.0 + v1.1
      //mainloop = (void(*)()) 0x80002A9;
      //load_pokemon = (void(*)()) 0x8044d55;

      break;
    }

      /// --- FR/LG ---
      // In FR/LG, the function that initialises the save-block pointers to
      // default does not set up saveblock3. Which will need to be set up before
      // loading the save if we want boxed Pokémon to not disappear. Oh, and
      // loadsave() offset is different between FR and LG...

    case 'DRPB': // FireRed German
    case 'DGPB': // LeafGreen German
    {
      gSaveBlock1 = (pSaveBlock1) 0x202552C;
      gSaveBlock2 = (pSaveBlock2) 0x2024588;
      gSaveBlock3 = (pSaveBlock3) 0x2029314;
      *(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
      loadsave = (void(*)(char)) ( GAME_FR ? 0x80da721 : 0x80da6f5 );
      //mainloop = (void(*)()) 0x8000425;
      //titlemid = 0x80791df;
      //load_pokemon = (void(*)()) 0x804c251;

      break;
    }

    case 'FRPB': // FireRed French
    case 'FGPB': // LeafGreen French
    {
      gSaveBlock1 = (pSaveBlock1) 0x202552C;
      gSaveBlock2 = (pSaveBlock2) 0x2024588;
      gSaveBlock3 = (pSaveBlock3) 0x2029314;
      *(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
      loadsave = (void(*)(char)) ( GAME_FR ? 0x80da7e1 : 0x80da7b5 );
      //mainloop = (void(*)()) 0x8000417;
      //titlemid = 0x807929f;
      //load_pokemon = (void(*)()) 0x804c311;

      break;
    }

    case 'IRPB': // FireRed Italian
    case 'IGPB': // LeafGreen Italian
    {
      gSaveBlock1 = (pSaveBlock1) 0x202552C;
      gSaveBlock2 = (pSaveBlock2) 0x2024588;
      gSaveBlock3 = (pSaveBlock3) 0x2029314;
      *(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
      loadsave = (void(*)(char)) ( GAME_FR ? 0x80da721 : 0x80da6f5 );
      //mainloop = (void(*)()) 0x8000425;
      //titlemid = 0x80791cb;
      //load_pokemon = (void(*)()) 0x804c23d;

      break;
    }

    case 'SRPB': // FireRed Spanish
    case 'SGPB': // LeafGreen Spanish
    {
      gSaveBlock1 = (pSaveBlock1) 0x202552C;
      gSaveBlock2 = (pSaveBlock2) 0x2024588;
      gSaveBlock3 = (pSaveBlock3) 0x2029314;
      *(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
      loadsave = (void(*)(char)) ( GAME_FR ? 0x80da809 : 0x80da7dd );
      //mainloop = (void(*)()) 0x8000417;
      //titlemid = 0x80792b3;
      //load_pokemon = (void(*)()) 0x804c325;

      break;
    }

    case 'ERPB': // FireRed English
    case 'EGPB': // LeafGreen English
    {
      gSaveBlock1 = (pSaveBlock1) 0x202552C;
      gSaveBlock2 = (pSaveBlock2) 0x2024588;
      gSaveBlock3 = (pSaveBlock3) 0x2029314;
      *(pSaveBlock3*)(0x3005010) = gSaveBlock3;

      // version number
      switch (ROM[0xBC])
      {
        case 0:
        {
          loadsave = (void(*)(char)) ( GAME_FR ? 0x80da4fd : 0x80da4d1 );
          //mainloop = (void(*)()) 0x800041b;
          //titlemid = 0x807927b;
          //load_pokemon = (void(*)()) 0x804c231;

          break;
        }

        case 1:
        {
          loadsave = (void(*)(char)) ( GAME_FR ? 0x80da511 : 0x80da4e5 );
          //mainloop = (void(*)()) 0x8000429;
          //titlemid = 0x807928f;
          //load_pokemon = (void(*)()) 0x804c245;
          gBaseStats = (struct BaseStats*) ( GAME_FR ? 0 : 0x82547d0 );
          gExpTables = (ExperienceTables) ( GAME_FR ? 0 : 0x8253b30 );
          gNatOrder = (const u16*) ( GAME_FR ? 0 : 0x825203a );

          break;
        }

        default:
        {
          return false; // unsupported version
        }
      }

      break;
    }

    case 'JRPB': // FireRed Japanese
    case 'JGPB': // LeafGreen Japanese
    {
      gSaveBlock1 = (pSaveBlock1) 0x202548C;
      gSaveBlock2 = (pSaveBlock2) 0x20244E8;
      gSaveBlock3 = (pSaveBlock3) 0x202924C;
      *(pSaveBlock3*)(0x3005050) = gSaveBlock3;

      // version number
      switch (ROM[0xBC])
      {
        case 0:
        {
          loadsave = (void(*)(char)) ( GAME_FR ? 0x80db4e5 : 0x80db4b9 );
          //mainloop = (void(*)()) 0x800041b;
          //titlemid = 0x8078a0f;
          //load_pokemon = (void(*)()) 0x804b9e9;

          break;
        }

        case 1:
        {
          if ((gamecode << 8) == 'GPB\x00')
          {
            // LeafGreen v1.1 Japanese is undumped.
            // Therefore, it is unsupported.
            // I will make guesses at the offsets in the comments, but I will
            // not actually implement them until LeafGreen v1.1 is dumped.

            return false;
          }

          loadsave = (void(*)(char)) 0x80db529;
          // potential LG1.1 address: 0x80db4fd
          //mainloop = (void(*)()) 0x8000417;
          //titlemid = 0x8078987;
          //load_pokemon = (void(*)()) 0x804b9c5;

          break;
        }

        default:
        {
          return false; // unsupported version
        }
      }

      break;
    }

      /// --- Emerald ---
      // In Emerald, the saveblock pointer that isn't set up is saveblock1 (in
      // FR/LG it was saveblock3). The initial save loading code after the
      // copyright screen is also updated, now it sets up ASLR/crypto here before
      // loading the save.

    case 'DEPB': // Emerald German
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025A00;
      gSaveBlock2 = (pSaveBlock2) 0x2024A54;
      gSaveBlock3 = (pSaveBlock3) 0x2029808;
      *(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x8153075;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x816fdb5;
      //load_pokemon = (void(*)()) 0x8076dd5;

      break;
    }

    case 'FEPB': // Emerald French
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025A00;
      gSaveBlock2 = (pSaveBlock2) 0x2024A54;
      gSaveBlock3 = (pSaveBlock3) 0x2029808;
      *(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x815319d;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x816fedd;
      //load_pokemon = (void(*)()) 0x8076dd1;

      break;
    }

    case 'IEPB': // Emerald Italian
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025A00;
      gSaveBlock2 = (pSaveBlock2) 0x2024A54;
      gSaveBlock3 = (pSaveBlock3) 0x2029808;
      *(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x8153065;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x816fda5;
      //load_pokemon = (void(*)()) 0x8076dd5;

      break;
    }

    case 'SEPB': // Emerald Spanish
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025A00;
      gSaveBlock2 = (pSaveBlock2) 0x2024A54;
      gSaveBlock3 = (pSaveBlock3) 0x2029808;
      *(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x8153175;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x816feb5;
      //load_pokemon = (void(*)()) 0x8076dd1;

      break;
    }

    case 'EEPB': // Emerald English
    {
      gSaveBlock1 = (pSaveBlock1) 0x2025A00;
      gSaveBlock2 = (pSaveBlock2) 0x2024A54;
      gSaveBlock3 = (pSaveBlock3) 0x2029808;
      *(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x81534d1;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x817014d;
      //load_pokemon = (void(*)()) 0x8076dd5;

      break;
    }

    case 'JEPB': // Emerald Japanese
    {
      gSaveBlock1 = (pSaveBlock1) 0x20256A4;
      gSaveBlock2 = (pSaveBlock2) 0x20246F8;
      gSaveBlock3 = (pSaveBlock3) 0x20294AC;
      *(pSaveBlock1*)(0x3005aec) = gSaveBlock1;
      loadsave = (void(*)(char)) 0x815340d;
      //mainloop = (void(*)()) 0x800042b;
      //titlemid = 0x816ff45;
      //load_pokemon = (void(*)()) 0x80767dd;

      break;
    }

    default:
    {
      return false; // this game isn't supported
    }
  }

  loadsave(0);

  // now the save is loaded, we can do what we want with the loaded blocks.
  // first, we're going to want to decrypt the parts that are crypted, if
  // applicable.
  decryptSaveStructures(gSaveBlock1,gSaveBlock2,gSaveBlock3);

  gameData->SaveBlock1 = gSaveBlock1;
  gameData->SaveBlock2 = gSaveBlock2;
  gameData->SaveBlock3 = gSaveBlock3;
  gameData->baseStats = gBaseStats;
  gameData->expTables = gExpTables;
  gameData->natOrder = gNatOrder;

  return true;
}

void DecryptPokemon(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  CryptBoxPokemon(boxMon);
}

void DecryptBoxPokemon(struct BoxPokemon* pkm)
{
  CryptBoxPokemon(pkm);
}

void EncryptPokemon(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  EncryptBoxPokemon(boxMon);
}

void EncryptBoxPokemon(struct BoxPokemon* pkm)
{
  FixBoxPokemonChecksum(pkm);
  CryptBoxPokemon(pkm);
}

union PokemonSubstruct* GetPokemonSubstruct(struct Pokemon* pkm,u8 substructId)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  return GetBoxPokemonSubstruct(boxMon,substructId);
}

union PokemonSubstruct* GetBoxPokemonSubstruct(
    struct BoxPokemon* pkm,
    u8 substructId)
{
  if (substructId > 3)
  {
    return NULL;
  }

  u32 personality = pkm->personality;
  u32 modulo = (personality % 24);

  // Staring at the substruct indexes, I noticed the last two columns are the
  // reverse of the first two! that is, substructId==2 column is the reverse of
  // substructId==1, substructId==3 is the reverse of substructId==0.
  // At least that means there's no need to hardcode all four.
  u8 substruct_idxes[2][24] = {
    { 0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3, 1, 1, 2, 3, 2, 3 },
    { 1, 1, 2, 3, 2, 3, 0, 0, 0, 0, 0, 0, 2, 3, 1, 1, 3, 2, 2, 3, 1, 1, 3, 2 }
  };

  if (substructId < 2)
  {
    return &(pkm->secure.substructs[substruct_idxes[substructId][modulo]]);
  }

  return &(pkm->secure.substructs[
      substruct_idxes[3 - substructId][23 - modulo]]);
}

u16 CalculateBoxPokemonChecksum(struct BoxPokemon* pkm)
{
  u16 checksum = 0;

  union PokemonSubstruct* substructs[4] = {
    GetBoxPokemonSubstruct(pkm,0),
    GetBoxPokemonSubstruct(pkm,1),
    GetBoxPokemonSubstruct(pkm,2),
    GetBoxPokemonSubstruct(pkm,3)
  };

  for (int substruct = 0; substruct < 4; substruct++)
  {
    for (int i = 0; i < 6; i++)
    {
      checksum += substructs[substruct]->raw[i];
    }
  }

  return checksum;
}

void FixBoxPokemonChecksum(struct BoxPokemon* pkm)
{
  pkm->checksum = CalculateBoxPokemonChecksum(pkm);
}

struct PokemonSubstruct0* GetPokemonSubstruct0(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  return GetBoxPokemonSubstruct0(boxMon);
}

struct PokemonSubstruct0* GetBoxPokemonSubstruct0(struct BoxPokemon* pkm)
{
  return &(GetBoxPokemonSubstruct(pkm,0)->type0);
}

struct PokemonSubstruct1* GetPokemonSubstruct1(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  return GetBoxPokemonSubstruct1(boxMon);
}

struct PokemonSubstruct1* GetBoxPokemonSubstruct1(struct BoxPokemon* pkm)
{
  return &(GetBoxPokemonSubstruct(pkm,1)->type1);
}

struct PokemonSubstruct2* GetPokemonSubstruct2(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  return GetBoxPokemonSubstruct2(boxMon);
}

struct PokemonSubstruct2* GetBoxPokemonSubstruct2(struct BoxPokemon* pkm)
{
  return &(GetBoxPokemonSubstruct(pkm,2)->type2);
}

struct PokemonSubstruct3* GetPokemonSubstruct3(struct Pokemon* pkm)
{
  struct BoxPokemon* boxMon = &(pkm->box);

  return GetBoxPokemonSubstruct3(boxMon);
}

struct PokemonSubstruct3* GetBoxPokemonSubstruct3(struct BoxPokemon* pkm)
{
  return &(GetBoxPokemonSubstruct(pkm,3)->type3);
}
