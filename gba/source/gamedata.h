/*
 * Copyright (C) 2017 hatkirby
 * Copyright (C) 2017 slipstream/RoL
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef _GAMEDATA_H_
#define _GAMEDATA_H_

#include <gba.h>
#include "saveblocks.h"

#define GAME_RUBY (((*(u32*)(0x80000AC)) << 8) == 'VXA\x00')
#define GAME_SAPP (((*(u32*)(0x80000AC)) << 8) == 'PXA\x00')
#define GAME_RS   ((GAME_RUBY) || (GAME_SAPP))
#define GAME_FR   (((*(u32*)(0x80000AC)) << 8) == 'RPB\x00')
#define GAME_LG   (((*(u32*)(0x80000AC)) << 8) == 'GPB\x00')
#define GAME_FRLG ((GAME_FR) || (GAME_LG))
#define GAME_EM   (((*(u32*)(0x80000AC)) << 8) == 'EPB\x00')

#define LANG_JAPAN ((*(u8*)(0x80000AF)) == 'J')

typedef const u32 (*ExperienceTables)[101];

struct GameData {
  pSaveBlock1 SaveBlock1;
  pSaveBlock2 SaveBlock2;
  pSaveBlock3 SaveBlock3;
};

bool initSaveData(struct GameData* gameData);

/**
 * Decrypts the substructures of a Pokémon structure, so they can be viewed or
 * modified easily.
 *
 * Remember to call EncryptPokemon() afterwards.
 *
 * @param pkm   The Pokémon to decrypt the substructures of.
 */
void DecryptPokemon(struct Pokemon* pkm);

/**
 * Decrypts the substructures of a core Pokémon structure, so they can be viewed
 * or modified easily.
 *
 * Used by DecryptPokemon().
 *
 * Remember to call EncryptPokemon() afterwards.
 *
 * @param pkm   The BoxPokemon to decrypt the substructures of.
 */
void DecryptBoxPokemon(struct BoxPokemon* pkm);

/**
 * Encrypts the substructures of a Pokémon structure, and fixes the checksum.
 *
 * Must be used after DecryptPokemon() has been called, otherwise the Pokémon
 * you decrypted and forgot to re-encrypt will become a Bad Egg.
 *
 * @param pkm   The Pokémon to encrypt the substructures and fix
 *              the checksum of.
 */
void EncryptPokemon(struct Pokemon* pkm);

/**
 * Encrypts the substructures of a core Pokémon structure, and fixes the
 * checksum.
 *
 * Must be used after DecryptBoxPokemon() has been called, otherwise the Pokémon
 * you decrypted and forgot to re-encrypt will become a Bad Egg.
 *
 * @param pkm   The BoxPokemon to encrypt the substructures and fix the checksum
 *              of.
 */
void EncryptBoxPokemon(struct BoxPokemon* pkm);

/**
 * Gets a substructure of a Pokémon structure.
 *
 * Call DecryptPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm           The Pokemon to get a substructure of.
 * @param substructId   The substructure to get.
 *
 * @return The substructure.
 */
union PokemonSubstruct* GetPokemonSubstruct(struct Pokemon* pkm,u8 substructId);

/**
 * Gets a substructure of a core Pokémon structure.
 *
 * Call DecryptBoxPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm           The Pokemon to get a substructure of.
 * @param substructId   The substructure to get.
 *
 * @return The substructure.
 */
union PokemonSubstruct* GetBoxPokemonSubstruct(
    struct BoxPokemon* pkm,
    u8 substructId);

/**
 * Gets the checksum of a core Pokémon structure.
 *
 * @param pkm   The BoxPokemon to calculate the checksum of.
 *
 * @return The checksum.
 */
u16 CalculateBoxPokemonChecksum(struct BoxPokemon* pkm);

/**
 * Fixes the checksum of a core Pokémon structure.
 *
 * @param pkm   The BoxPokemon to fix the checksum of.
 */
void FixBoxPokemonChecksum(struct BoxPokemon* pkm);

/**
 * Gets the zeroth substructure ("Growth") of a Pokémon structure.
 *
 * Call DecryptPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The Pokémon to get a substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct0* GetPokemonSubstruct0(struct Pokemon* pkm);

/**
 * Gets the zeroth substructure ("Growth") of a core Pokémon structure.
 *
 * Call DecryptBoxPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The BoxPokemon to get the substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct0* GetBoxPokemonSubstruct0(struct BoxPokemon* pkm);

/**
 * Gets the first substructure ("Attacks") of a Pokémon structure.
 *
 * Call DecryptPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The Pokémon to get a substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct1* GetPokemonSubstruct1(struct Pokemon* pkm);

/**
 * Gets the first substructure ("Attacks") of a core Pokémon structure.
 *
 * Call DecryptBoxPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The BoxPokemon to get the substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct1* GetBoxPokemonSubstruct1(struct BoxPokemon* pkm);

/**
 * Gets the second substructure ("EVs & Condition") of a Pokémon structure.
 *
 * Call DecryptPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The Pokémon to get a substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct2* GetPokemonSubstruct2(struct Pokemon* pkm);

/**
 * Gets the second substructure ("EVs & Condition") of a core Pokémon structure.
 *
 * Call DecryptBoxPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The BoxPokemon to get the substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct2* GetBoxPokemonSubstruct2(struct BoxPokemon* pkm);

/**
 * Gets the third substructure ("Miscellaneous") of a Pokémon structure.
 *
 * Call DecryptPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The Pokémon to get a substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct3* GetPokemonSubstruct3(struct Pokemon* pkm);

/**
 * Gets the third substructure ("Miscellaneous") of a core Pokémon structure.
 *
 * Call DecryptBoxPokemon() first or the substructure data will be encrypted.
 *
 * @param pkm   The BoxPokemon to get the substructure of.
 *
 * @return The substructure.
 */
struct PokemonSubstruct3* GetBoxPokemonSubstruct3(struct BoxPokemon* pkm);

#endif
