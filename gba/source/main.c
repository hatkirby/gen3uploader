/*
 * Example Gen3-multiboot payload by slipstream/RoL 2017.
 * Supports only English Ruby, v1.0-1.2.
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include <gba.h>

int main(void) {
	// check the ROM code, make sure this game is supported.
	char* ROM = 0x8000000;
	
	if ((*(u32*)(&ROM[0xAC])) != 'EVXA') return 0; // Pokémon Ruby english, nothing else supported!
	
	void(*loadsave)(char a1);
	// get the address of the save loading function.
	switch (ROM[0xBC]) { // version number
		case 0:
			loadsave = 0x8125EC9;
			break;
		case 1:
		case 2:
			loadsave = 0x8125EE9;
			break;
		default:
			return 0; //bail out
	}
	loadsave(0);
	// now the save is loaded, we can do what we want with the loaded blocks.
	// here as a small PoC, changing first letter of player name to 'z'.
	u8* gSaveBlock2 = 0x2024EA4;
	gSaveBlock2[0] = 0xee; // 'z'
	// Now we've done what we want, time to return to the game.
	// Can't just return, the game will reload the save.
	// So let's just call the main-loop directly ;)
	void(*mainloop)() = 0x80002A5;
	// turn the sound back on before we head back to the game
	*(vu16 *)(REG_BASE + 0x84) = 0x8f;
	mainloop();
	// Anything past here will not be executed.
	return 0;
}


