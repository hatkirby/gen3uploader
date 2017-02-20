/*
 * Example Gen3-multiboot payload by slipstream/RoL 2017.
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * payload.c: place where user payload should go :)
 */

#include <gba.h>
#include "payload.h"

// Your payload code should obviously go into the body of this, the payload function.
void payload(pSaveBlock1 SaveBlock1,pSaveBlock2 SaveBlock2,pSaveBlock3 SaveBlock3) {
	// This example payload will modify the first character of the player's name.
	// It will change to 'z'. You can see the character encoding table here: http://bulbapedia.bulbagarden.net/wiki/Character_encoding_in_Generation_III
	SaveBlock2[0] = 0xee; // 'z'
}