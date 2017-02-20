/*
 * Example Gen3-multiboot payload by slipstream/RoL 2017.
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * main.c: setup, call payload, return gracefully back to game
 */
#include <gba.h>
#include "payload.h"

void call_into_middle_of_titlescreen_func(u32 addr,u32 stackspace);

int main(void) {
	// check the ROM code, make sure this game is supported.
	u8* ROM = (u8*) 0x8000000;
	
	u32 gamecode = (*(u32*)(&ROM[0xAC]));
	
	void(*loadsave)(char a1);
	void(*mainloop)();
	pSaveBlock1 gSaveBlock1;
	pSaveBlock2 gSaveBlock2;
	pSaveBlock3 gSaveBlock3;
	u32 titlemid = 0;
	// get the address of the save loading function.
	switch (gamecode) {
		// --- R/S ---
		case 'DVXA': // Ruby German
		case 'DPXA': // Sapphire German
			// TODO: detect debug ROM?
			gSaveBlock1 = (pSaveBlock1) 0x2025734;
			gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
			gSaveBlock3 = (pSaveBlock3) 0x20300A0;
			loadsave = (void(*)(char)) 0x8126249; // same for v1.0 + v1.1
			mainloop = (void(*)()) 0x80003D9;
			break;
		case 'FVXA': // Ruby French
		case 'FPXA': // Sapphire French
			gSaveBlock1 = (pSaveBlock1) 0x2025734;
			gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
			gSaveBlock3 = (pSaveBlock3) 0x20300A0;
			loadsave = (void(*)(char)) 0x8126351; // same for v1.0 + v1.1
			mainloop = (void(*)()) 0x80003D9;
			break;
		case 'IVXA': // Ruby Italian
		case 'IPXA': // Sapphire Italian
			gSaveBlock1 = (pSaveBlock1) 0x2025734;
			gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
			gSaveBlock3 = (pSaveBlock3) 0x20300A0;
			loadsave = (void(*)(char)) 0x8126249; // same for v1.0 + v1.1
			mainloop = (void(*)()) 0x80003D9;
			break;
		case 'SVXA': // Ruby Spanish
		case 'SPXA': // Sapphire Spanish
			gSaveBlock1 = (pSaveBlock1) 0x2025734;
			gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
			gSaveBlock3 = (pSaveBlock3) 0x20300A0;
			loadsave = (void(*)(char)) 0x8126349; // same for v1.0 + v1.1
			mainloop = (void(*)()) 0x80003D9;
			break;
		case 'EVXA': // Ruby English
		case 'EPXA': // Sapphire English
			gSaveBlock1 = (pSaveBlock1) 0x2025734;
			gSaveBlock2 = (pSaveBlock2) 0x2024EA4;
			gSaveBlock3 = (pSaveBlock3) 0x20300A0;
			mainloop = (void(*)()) 0x80002A5;
			switch (ROM[0xBC]) { // version number
				case 0:
					loadsave = (void(*)(char)) 0x8125EC9;
					break;
				case 1:
				case 2:
					loadsave = (void(*)(char)) 0x8125EE9;
					break;
				default:
					return 0; // unsupported version
			}
			break;
		case 'JVXA': // Ruby Japanese
		case 'JPXA': // Sapphire Japanese
			gSaveBlock1 = (pSaveBlock1) 0x2025494;
			gSaveBlock2 = (pSaveBlock2) 0x2024C04;
			gSaveBlock3 = (pSaveBlock3) 0x202FDBC;
			loadsave = (void(*)(char)) 0x8120d05; // same for v1.0 + v1.1
			mainloop = (void(*)()) 0x80002A9;
			break;
		/// --- FR/LG ---
		// In FR/LG, the function that initialises the save-block pointers to default does not set up saveblock3.
		// Which will need to be set up before loading the save if we want boxed Pokémon to not disappear.
		// Oh, and loadsave() offset is different between FR and LG...
		case 'DRPB': // FireRed German
		case 'DGPB': // LeafGreen German
			gSaveBlock1 = (pSaveBlock1) 0x202552C;
			gSaveBlock2 = (pSaveBlock2) 0x2024588;
			gSaveBlock3 = (pSaveBlock3) 0x2029314;
			*(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
			loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da721 : 0x80da6f5 );
			mainloop = (void(*)()) 0x8000425;
			titlemid = 0x80791df;
			break;
		case 'FRPB': // FireRed French
		case 'FGPB': // LeafGreen French
			gSaveBlock1 = (pSaveBlock1) 0x202552C;
			gSaveBlock2 = (pSaveBlock2) 0x2024588;
			gSaveBlock3 = (pSaveBlock3) 0x2029314;
			*(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
			loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da7e1 : 0x80da7b5 );
			mainloop = (void(*)()) 0x8000417;
			titlemid = 0x807929f;
			break;
		case 'IRPB': // FireRed Italian
		case 'IGPB': // LeafGreen Italian
			gSaveBlock1 = (pSaveBlock1) 0x202552C;
			gSaveBlock2 = (pSaveBlock2) 0x2024588;
			gSaveBlock3 = (pSaveBlock3) 0x2029314;
			*(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
			loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da721 : 0x80da6f5 );
			mainloop = (void(*)()) 0x8000425;
			titlemid = 0x80791cb;
			break;
		case 'SRPB': // FireRed Spanish
		case 'SGPB': // LeafGreen Spanish
			gSaveBlock1 = (pSaveBlock1) 0x202552C;
			gSaveBlock2 = (pSaveBlock2) 0x2024588;
			gSaveBlock3 = (pSaveBlock3) 0x2029314;
			*(pSaveBlock3*)(0x3004f60) = gSaveBlock3;
			loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da809 : 0x80da7dd );
			mainloop = (void(*)()) 0x8000417;
			titlemid = 0x80792b3;
			break;
		case 'ERPB': // FireRed English
		case 'EGPB': // LeafGreen English
			gSaveBlock1 = (pSaveBlock1) 0x202552C;
			gSaveBlock2 = (pSaveBlock2) 0x2024588;
			gSaveBlock3 = (pSaveBlock3) 0x2029314;
			*(pSaveBlock3*)(0x3005010) = gSaveBlock3;
			switch (ROM[0xBC]) { // version number
				case 0:
					loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da4fd : 0x80da4d1 );
					mainloop = (void(*)()) 0x800041b;
					titlemid = 0x807927b;
					break;
				case 1:
					loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80da511 : 0x80da4e5 );
					mainloop = (void(*)()) 0x8000429;
					titlemid = 0x807928f;
					break;
				default:
					return 0; // unsupported version
			}
			break;
		case 'JRPB': // FireRed Japanese
		case 'JGPB': // LeafGreen Japanese
			gSaveBlock1 = (pSaveBlock1) 0x202548C;
			gSaveBlock2 = (pSaveBlock2) 0x20244E8;
			gSaveBlock3 = (pSaveBlock3) 0x202924C;
			*(pSaveBlock3*)(0x3005050) = gSaveBlock3;
			switch (ROM[0xBC]) { // version number
				case 0:
					loadsave = (void(*)(char)) ( (gamecode << 8) == 'RPB\x00' ? 0x80db4e5 : 0x80db4b9 );
					mainloop = (void(*)()) 0x800041b;
					titlemid = ( (gamecode << 8) == 'RPB\x00' ? 0x8078a0d : 0x8078a0f );
					break;
				case 1:
					if ((gamecode << 8) == 'GPB\x00') {
						// LeafGreen v1.1 Japanese is undumped.
						// Therefore, it is unsupported.
						// I will make guesses at the offsets in the comments, but I will not actually implement them until LeafGreen v1.1 is dumped.
						return 0;
					}
					loadsave = (void(*)(char)) 0x80db529; // potential LG1.1 address: 0x80db4fd
					mainloop = (void(*)()) 0x8000417;
					titlemid = 0x8078987; // potential LG1.1 address: 0x8078989
					break;
				default:
					return 0; // unsupported version
			}
			break;
		/// --- Emerald ---
		// In Emerald, the saveblock pointer that isn't set up is saveblock1 (in FR/LG it was saveblock3).
		// The initial save loading code after the copyright screen is also updated, now it sets up ASLR/crypto here before loading the save.
		case 'DEPB': // Emerald German
			gSaveBlock1 = (pSaveBlock1) 0x2025A00;
			gSaveBlock2 = (pSaveBlock2) 0x2024A54;
			gSaveBlock3 = (pSaveBlock3) 0x2029808;
			*(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x8153075;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x816fdb5;
			break;
		case 'FEPB': // Emerald French
			gSaveBlock1 = (pSaveBlock1) 0x2025A00;
			gSaveBlock2 = (pSaveBlock2) 0x2024A54;
			gSaveBlock3 = (pSaveBlock3) 0x2029808;
			*(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x815319d;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x816fedd;
			break;
		case 'IEPB': // Emerald Italian
			gSaveBlock1 = (pSaveBlock1) 0x2025A00;
			gSaveBlock2 = (pSaveBlock2) 0x2024A54;
			gSaveBlock3 = (pSaveBlock3) 0x2029808;
			*(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x8153065;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x816fda5;
			break;
		case 'SEPB': // Emerald Spanish
			gSaveBlock1 = (pSaveBlock1) 0x2025A00;
			gSaveBlock2 = (pSaveBlock2) 0x2024A54;
			gSaveBlock3 = (pSaveBlock3) 0x2029808;
			*(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x8153175;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x816feb5;
			break;
		case 'EEPB': // Emerald English
			gSaveBlock1 = (pSaveBlock1) 0x2025A00;
			gSaveBlock2 = (pSaveBlock2) 0x2024A54;
			gSaveBlock3 = (pSaveBlock3) 0x2029808;
			*(pSaveBlock1*)(0x3005d8c) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x81534d1;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x817014d;
			break;
		case 'JEPB': // Emerald Japanese
			gSaveBlock1 = (pSaveBlock1) 0x20256A4;
			gSaveBlock2 = (pSaveBlock2) 0x20246F8;
			gSaveBlock3 = (pSaveBlock3) 0x20294AC;
			*(pSaveBlock1*)(0x3005aec) = gSaveBlock1;
			loadsave = (void(*)(char)) 0x815340d;
			mainloop = (void(*)()) 0x800042b;
			titlemid = 0x816ff45;
			break;
		default:
			return 0; // this game isn't supported
	}
	loadsave(0);
	// now the save is loaded, we can do what we want with the loaded blocks.
	// time to call the payload.
	payload(gSaveBlock1,gSaveBlock2,gSaveBlock3);
	// In FR/LG/Emerald, just returning to the game is unwise.
	// The game reloads the savefile.
	// In FR/LG, this is done at the title screen after setting ASLR/saveblock-crypto up. (probably because at initial save-load, SaveBlock3 ptr isn't set up lol)
	// So, better bypass the title screen and get the game to return directly to the Continue/New Game screen.
	// In Emerald, the save reload happens after the Continue option was chosen, so we have no choice but to bypass everything and get the game to go straight to the overworld.
	// Easiest way to do this is to call into the middle of the function we want, using an ASM wrapper to set up the stack.
	// Here goes...
	if (titlemid) {
		// Function reserves an extra 4 bytes of stack space in FireRed, and none in Emerald.
		call_into_middle_of_titlescreen_func(titlemid,((gamecode << 8) == 'EPB\x00' ? 0 : 4));
	}
	// Now we've done what we want, time to return to the game.
	// Can't just return, the game will reload the save.
	// So let's just call the main-loop directly ;)
	// turn the sound back on before we head back to the game
	*(vu16 *)(REG_BASE + 0x84) = 0x8f;
	// re-enable interrupts
	REG_IME = 1;
	mainloop();
	// Anything past here will not be executed.
	return 0;
}


