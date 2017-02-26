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
	// HoF-warp example payload!
	
	// Structure offsets are different between R/S, FR/LG, and Emerald.
	// The beginning of the structures are the same but do NOT take shortcuts here, it's not good practise.
	// If you want to support multiple games, make specific checks for games, use the right structure for each game.
	SaveBlock1_RS* sb1rs = &SaveBlock1->rs;
	SaveBlock1_FRLG* sb1frlg = &SaveBlock1->frlg;
	SaveBlock1_E* sb1e = &SaveBlock1->e;
	if (GAME_FRLG) {
		sb1frlg->location.mapGroup = 1; // generic indoors?
		sb1frlg->location.mapNum = 80; // Hall of Fame
		// set coords to the same place that the champions' room script sets them to
		sb1frlg->location.x = sb1frlg->pos.x = 5;
		sb1frlg->location.y = sb1frlg->pos.y = 12;
		sb1frlg->mapDataId = 0xDA; // from HoF map-header
		sb1frlg->location.warpId = 0xff;
		// make sure the HoF script doesn't crash, which it will do if 0 pokémon
		if (sb1frlg->playerPartyCount == 0) {
			sb1frlg->playerPartyCount = 1;
			// this isn't enough, the heal animation recalculates the party count ignoring empty spots
			// so let's hack together one. i don't care about it becoming a bad egg at all.
			sb1frlg->playerParty[0].box.personality++;
		}
		return;
	} else if (GAME_RS) {
		sb1rs->location.mapGroup = 16; // Ever Grande City
		sb1rs->location.mapNum = 11; // Hall of Fame
		// set coords to the same place that the champions' room script sets them to
		sb1rs->location.x = sb1rs->pos.x = 7;
		sb1rs->location.y = sb1rs->pos.y = 16;
		sb1rs->mapDataId = 299; // from HoF map-header
		sb1rs->location.warpId = 0xff;
		// make sure the HoF script doesn't crash, which it will do if 0 pokémon
		if (sb1rs->playerPartyCount == 0) {
			sb1rs->playerPartyCount = 1;
			// this isn't enough, the heal animation recalculates the party count ignoring empty spots
			// so let's hack together one. i don't care about it becoming a bad egg at all.
			sb1rs->playerParty[0].box.personality++;
		}
		return;
	} else if (GAME_EM) {
		sb1e->location.mapGroup = 16; // Ever Grande City
		sb1e->location.mapNum = 11; // Hall of Fame
		// set coords to the same place that the champions' room script sets them to
		sb1e->location.x = sb1e->pos.x = 7;
		sb1e->location.y = sb1e->pos.y = 16;
		sb1e->mapDataId = 298; // from HoF map-header
		sb1e->location.warpId = 0xff;
		// make sure the HoF script doesn't crash, which it will do if 0 pokémon
		if (sb1e->playerPartyCount == 0) {
			sb1e->playerPartyCount = 1;
			// this isn't enough, the heal animation recalculates the party count ignoring empty spots
			// so let's hack together one. i don't care about it becoming a bad egg at all.
			sb1e->playerParty[0].box.personality++;
		}
		return;
	}
}