/*
 * Copyright (C) 2017 Scott Norton
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#include "basestats.h"

enum {
    GROWTH_MEDIUM_FAST,
    GROWTH_ERRATIC,
    GROWTH_FLUCTUATING,
    GROWTH_MEDIUM_SLOW,
    GROWTH_FAST,
    GROWTH_SLOW
};

const struct SmallBaseStats gSmallBaseStats[] = {
    { // ??????????
    }, {
        // Bulbasaur
        45, 49, 49, 45, 65, 65,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Ivysaur
        60, 62, 63, 60, 80, 80,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Venusaur
        80, 82, 83, 80, 100, 100,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Charmander
        39, 52, 43, 65, 60, 50,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Charmeleon
        58, 64, 58, 80, 80, 65,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Charizard
        78, 84, 78, 100, 109, 85,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Squirtle
        44, 48, 65, 43, 50, 64,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Wartortle
        59, 63, 80, 58, 65, 80,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Blastoise
        79, 83, 100, 78, 85, 105,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Caterpie
        45, 30, 35, 45, 20, 20,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Metapod
        50, 20, 55, 30, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Butterfree
        60, 45, 50, 70, 80, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Weedle
        40, 35, 30, 50, 20, 20,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Kakuna
        45, 25, 50, 35, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Beedrill
        65, 80, 40, 75, 45, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Pidgey
        40, 45, 40, 56, 35, 35,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Pidgeotto
        63, 60, 55, 71, 50, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Pidgeot
        83, 80, 75, 91, 70, 70,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Rattata
        30, 56, 35, 72, 25, 35,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Raticate
        55, 81, 60, 97, 50, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Spearow
        40, 60, 30, 70, 31, 31,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Fearow
        65, 90, 65, 100, 61, 61,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Ekans
        35, 60, 44, 55, 40, 54,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Arbok
        60, 85, 69, 80, 65, 79,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Pikachu
        35, 55, 30, 90, 50, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Raichu
        60, 90, 55, 100, 90, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Sandshrew
        50, 75, 85, 40, 20, 30,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Sandslash
        75, 100, 110, 65, 45, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Nidoran♀
        55, 47, 52, 41, 40, 40,
        254, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nidorina
        70, 62, 67, 56, 55, 55,
        254, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nidoqueen
        90, 82, 87, 76, 75, 85,
        254, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nidoran♂
        46, 57, 40, 50, 40, 40,
        0, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nidorino
        61, 72, 57, 65, 55, 55,
        0, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nidoking
        81, 92, 77, 85, 85, 75,
        0, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Clefairy
        70, 45, 48, 35, 60, 65,
        191, // gender
        GROWTH_FAST
    }, { // Clefable
        95, 70, 73, 60, 85, 90,
        191, // gender
        GROWTH_FAST
    }, { // Vulpix
        38, 41, 40, 65, 50, 65,
        191, // gender
        GROWTH_MEDIUM_FAST
    }, { // Ninetales
        73, 76, 75, 100, 81, 100,
        191, // gender
        GROWTH_MEDIUM_FAST
    }, { // Jigglypuff
        115, 45, 20, 20, 45, 25,
        191, // gender
        GROWTH_FAST
    }, { // Wigglytuff
        140, 70, 45, 45, 75, 50,
        191, // gender
        GROWTH_FAST
    }, { // Zubat
        40, 45, 35, 55, 30, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Golbat
        75, 80, 70, 90, 65, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Oddish
        45, 50, 55, 30, 75, 65,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Gloom
        60, 65, 70, 40, 85, 75,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Vileplume
        75, 80, 85, 50, 100, 90,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Paras
        35, 70, 55, 25, 45, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Parasect
        60, 95, 80, 30, 60, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Venonat
        60, 55, 50, 45, 40, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Venomoth
        70, 65, 60, 90, 90, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Diglett
        10, 55, 25, 95, 35, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Dugtrio
        35, 80, 50, 120, 50, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Meowth
        40, 45, 35, 90, 40, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Persian
        65, 70, 60, 115, 65, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Psyduck
        50, 52, 48, 55, 65, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Golduck
        80, 82, 78, 85, 95, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Mankey
        40, 80, 35, 70, 35, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Primeape
        65, 105, 60, 95, 60, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Growlithe
        55, 70, 45, 60, 70, 50,
        63, // gender
        GROWTH_SLOW
    }, { // Arcanine
        90, 110, 80, 95, 100, 80,
        63, // gender
        GROWTH_SLOW
    }, { // Poliwag
        40, 50, 40, 90, 40, 40,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Poliwhirl
        65, 65, 65, 90, 50, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Poliwrath
        90, 85, 95, 70, 70, 90,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Abra
        25, 20, 15, 90, 105, 55,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Kadabra
        40, 35, 30, 105, 120, 70,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Alakazam
        55, 50, 45, 120, 135, 85,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Machop
        70, 80, 50, 35, 35, 35,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Machoke
        80, 100, 70, 45, 50, 60,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Machamp
        90, 130, 80, 55, 65, 85,
        63, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Bellsprout
        50, 75, 35, 40, 70, 30,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Weepinbell
        65, 90, 50, 55, 85, 45,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Victreebel
        80, 105, 65, 70, 100, 60,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Tentacool
        40, 40, 35, 70, 50, 100,
        127, // gender
        GROWTH_SLOW
    }, { // Tentacruel
        80, 70, 65, 100, 80, 120,
        127, // gender
        GROWTH_SLOW
    }, { // Geodude
        40, 80, 100, 20, 30, 30,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Graveler
        55, 95, 115, 35, 45, 45,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Golem
        80, 110, 130, 45, 55, 65,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Ponyta
        50, 85, 55, 90, 65, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Rapidash
        65, 100, 70, 105, 80, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Slowpoke
        90, 65, 65, 15, 40, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Slowbro
        95, 75, 110, 30, 100, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Magnemite
        25, 35, 70, 45, 95, 55,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Magneton
        50, 60, 95, 70, 120, 70,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Farfetch'd
        52, 65, 55, 60, 58, 62,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Doduo
        35, 85, 45, 75, 35, 35,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Dodrio
        60, 110, 70, 100, 60, 60,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Seel
        65, 45, 55, 45, 45, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Dewgong
        90, 70, 80, 70, 70, 95,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Grimer
        80, 80, 50, 25, 40, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Muk
        105, 105, 75, 50, 65, 100,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Shellder
        30, 65, 100, 40, 45, 25,
        127, // gender
        GROWTH_SLOW
    }, { // Cloyster
        50, 95, 180, 70, 85, 45,
        127, // gender
        GROWTH_SLOW
    }, { // Gastly
        30, 35, 30, 80, 100, 35,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Haunter
        45, 50, 45, 95, 115, 55,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Gengar
        60, 65, 60, 110, 130, 75,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Onix
        35, 45, 160, 70, 30, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Drowzee
        60, 48, 45, 42, 43, 90,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Hypno
        85, 73, 70, 67, 73, 115,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Krabby
        30, 105, 90, 50, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Kingler
        55, 130, 115, 75, 50, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Voltorb
        40, 30, 50, 100, 55, 55,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Electrode
        60, 50, 70, 140, 80, 80,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Exeggcute
        60, 40, 80, 40, 60, 45,
        127, // gender
        GROWTH_SLOW
    }, { // Exeggutor
        95, 95, 85, 55, 125, 65,
        127, // gender
        GROWTH_SLOW
    }, { // Cubone
        50, 50, 95, 35, 40, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Marowak
        60, 80, 110, 45, 50, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Hitmonlee
        50, 120, 53, 87, 35, 110,
        0, // gender
        GROWTH_MEDIUM_FAST
    }, { // Hitmonchan
        50, 105, 79, 76, 35, 110,
        0, // gender
        GROWTH_MEDIUM_FAST
    }, { // Lickitung
        90, 55, 75, 30, 60, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Koffing
        40, 65, 95, 35, 60, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Weezing
        65, 90, 120, 60, 85, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Rhyhorn
        80, 85, 95, 25, 30, 30,
        127, // gender
        GROWTH_SLOW
    }, { // Rhydon
        105, 130, 120, 40, 45, 45,
        127, // gender
        GROWTH_SLOW
    }, { // Chansey
        250, 5, 5, 50, 35, 105,
        254, // gender
        GROWTH_FAST
    }, { // Tangela
        65, 55, 115, 60, 100, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Kangaskhan
        105, 95, 80, 90, 40, 80,
        254, // gender
        GROWTH_MEDIUM_FAST
    }, { // Horsea
        30, 40, 70, 60, 70, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Seadra
        55, 65, 95, 85, 95, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Goldeen
        45, 67, 60, 63, 35, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Seaking
        80, 92, 65, 68, 65, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Staryu
        30, 45, 55, 85, 70, 55,
        255, // gender
        GROWTH_SLOW
    }, { // Starmie
        60, 75, 85, 115, 100, 85,
        255, // gender
        GROWTH_SLOW
    }, { // Mr. mime
        40, 45, 65, 90, 100, 120,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Scyther
        70, 110, 80, 105, 55, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Jynx
        65, 50, 35, 95, 115, 95,
        254, // gender
        GROWTH_MEDIUM_FAST
    }, { // Electabuzz
        65, 83, 57, 105, 95, 85,
        63, // gender
        GROWTH_MEDIUM_FAST
    }, { // Magmar
        65, 95, 57, 93, 100, 85,
        63, // gender
        GROWTH_MEDIUM_FAST
    }, { // Pinsir
        65, 125, 100, 85, 55, 70,
        127, // gender
        GROWTH_SLOW
    }, { // Tauros
        75, 100, 95, 110, 40, 70,
        0, // gender
        GROWTH_SLOW
    }, { // Magikarp
        20, 10, 55, 80, 15, 20,
        127, // gender
        GROWTH_SLOW
    }, { // Gyarados
        95, 125, 79, 81, 60, 100,
        127, // gender
        GROWTH_SLOW
    }, { // Lapras
        130, 85, 80, 60, 85, 95,
        127, // gender
        GROWTH_SLOW
    }, { // Ditto
        48, 48, 48, 48, 48, 48,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Eevee
        55, 55, 50, 55, 45, 65,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Vaporeon
        130, 65, 60, 65, 110, 95,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Jolteon
        65, 65, 60, 130, 110, 95,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Flareon
        65, 130, 60, 65, 95, 110,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Porygon
        65, 60, 70, 40, 85, 75,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Omanyte
        35, 40, 100, 35, 90, 55,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Omastar
        70, 60, 125, 55, 115, 70,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Kabuto
        30, 80, 90, 55, 55, 45,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Kabutops
        60, 115, 105, 80, 65, 70,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Aerodactyl
        80, 105, 65, 130, 60, 75,
        31, // gender
        GROWTH_SLOW
    }, { // Snorlax
        160, 110, 65, 30, 65, 110,
        31, // gender
        GROWTH_SLOW
    }, { // Articuno
        90, 85, 100, 85, 95, 125,
        255, // gender
        GROWTH_SLOW
    }, { // Zapdos
        90, 90, 85, 100, 125, 90,
        255, // gender
        GROWTH_SLOW
    }, { // Moltres
        90, 100, 90, 90, 125, 85,
        255, // gender
        GROWTH_SLOW
    }, { // Dratini
        41, 64, 45, 50, 50, 50,
        127, // gender
        GROWTH_SLOW
    }, { // Dragonair
        61, 84, 65, 70, 70, 70,
        127, // gender
        GROWTH_SLOW
    }, { // Dragonite
        91, 134, 95, 80, 100, 100,
        127, // gender
        GROWTH_SLOW
    }, { // Mewtwo
        106, 110, 90, 130, 154, 90,
        255, // gender
        GROWTH_SLOW
    }, { // Mew
        100, 100, 100, 100, 100, 100,
        255, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Chikorita
        45, 49, 65, 45, 49, 65,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Bayleef
        60, 62, 80, 60, 63, 80,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Meganium
        80, 82, 100, 80, 83, 100,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Cyndaquil
        39, 52, 43, 65, 60, 50,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Quilava
        58, 64, 58, 80, 80, 65,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Typhlosion
        78, 84, 78, 100, 109, 85,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Totodile
        50, 65, 64, 43, 44, 48,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Croconaw
        65, 80, 80, 58, 59, 63,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Feraligatr
        85, 105, 100, 78, 79, 83,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Sentret
        35, 46, 34, 20, 35, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Furret
        85, 76, 64, 90, 45, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Hoothoot
        60, 30, 30, 50, 36, 56,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Noctowl
        100, 50, 50, 70, 76, 96,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Ledyba
        40, 20, 30, 55, 40, 80,
        127, // gender
        GROWTH_FAST
    }, { // Ledian
        55, 35, 50, 85, 55, 110,
        127, // gender
        GROWTH_FAST
    }, { // Spinarak
        40, 60, 40, 30, 40, 40,
        127, // gender
        GROWTH_FAST
    }, { // Ariados
        70, 90, 70, 40, 60, 60,
        127, // gender
        GROWTH_FAST
    }, { // Crobat
        85, 90, 80, 130, 70, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Chinchou
        75, 38, 38, 67, 56, 56,
        127, // gender
        GROWTH_SLOW
    }, { // Lanturn
        125, 58, 58, 67, 76, 76,
        127, // gender
        GROWTH_SLOW
    }, { // Pichu
        20, 40, 15, 60, 35, 35,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Cleffa
        50, 25, 28, 15, 45, 55,
        191, // gender
        GROWTH_FAST
    }, { // Igglybuff
        90, 30, 15, 15, 40, 20,
        191, // gender
        GROWTH_FAST
    }, { // Togepi
        35, 20, 65, 20, 40, 65,
        31, // gender
        GROWTH_FAST
    }, { // Togetic
        55, 40, 85, 40, 80, 105,
        31, // gender
        GROWTH_FAST
    }, { // Natu
        40, 50, 45, 70, 70, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Xatu
        65, 75, 70, 95, 95, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Mareep
        55, 40, 40, 35, 65, 45,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Flaaffy
        70, 55, 55, 45, 80, 60,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Ampharos
        90, 75, 75, 55, 115, 90,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Bellossom
        75, 80, 85, 50, 90, 100,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Marill
        70, 20, 50, 40, 20, 50,
        127, // gender
        GROWTH_FAST
    }, { // Azumarill
        100, 50, 80, 50, 50, 80,
        127, // gender
        GROWTH_FAST
    }, { // Sudowoodo
        70, 100, 115, 30, 30, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Politoed
        90, 75, 75, 70, 90, 100,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Hoppip
        35, 35, 40, 50, 35, 55,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Skiploom
        55, 45, 50, 80, 45, 65,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Jumpluff
        75, 55, 70, 110, 55, 85,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Aipom
        55, 70, 55, 85, 40, 55,
        127, // gender
        GROWTH_FAST
    }, { // Sunkern
        30, 30, 30, 30, 30, 30,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Sunflora
        75, 75, 55, 30, 105, 85,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Yanma
        65, 65, 45, 95, 75, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Wooper
        55, 45, 45, 15, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Quagsire
        95, 85, 85, 35, 65, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Espeon
        65, 65, 60, 110, 130, 95,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Umbreon
        95, 65, 110, 65, 60, 130,
        31, // gender
        GROWTH_MEDIUM_FAST
    }, { // Murkrow
        60, 85, 42, 91, 85, 42,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Slowking
        95, 75, 80, 30, 100, 110,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Misdreavus
        60, 60, 60, 85, 85, 85,
        127, // gender
        GROWTH_FAST
    }, { // Unown
        48, 72, 48, 48, 72, 48,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Wobbuffet
        190, 33, 58, 33, 33, 58,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Girafarig
        70, 80, 65, 85, 90, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Pineco
        50, 65, 90, 15, 35, 35,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Forretress
        75, 90, 140, 40, 60, 60,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Dunsparce
        100, 70, 70, 45, 65, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Gligar
        65, 75, 105, 85, 35, 65,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Steelix
        75, 85, 200, 30, 55, 65,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Snubbull
        60, 80, 50, 30, 40, 40,
        191, // gender
        GROWTH_FAST
    }, { // Granbull
        90, 120, 75, 45, 60, 60,
        191, // gender
        GROWTH_FAST
    }, { // Qwilfish
        65, 95, 75, 85, 55, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Scizor
        70, 130, 100, 65, 55, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Shuckle
        20, 10, 230, 5, 10, 230,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Heracross
        80, 125, 75, 85, 40, 95,
        127, // gender
        GROWTH_SLOW
    }, { // Sneasel
        55, 95, 55, 115, 35, 75,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Teddiursa
        60, 80, 50, 40, 50, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Ursaring
        90, 130, 75, 55, 75, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Slugma
        40, 40, 40, 20, 70, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Magcargo
        50, 50, 120, 30, 80, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Swinub
        50, 50, 40, 50, 30, 30,
        127, // gender
        GROWTH_SLOW
    }, { // Piloswine
        100, 100, 80, 50, 60, 60,
        127, // gender
        GROWTH_SLOW
    }, { // Corsola
        55, 55, 85, 35, 65, 85,
        191, // gender
        GROWTH_FAST
    }, { // Remoraid
        35, 65, 35, 65, 65, 35,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Octillery
        75, 105, 75, 45, 105, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Delibird
        45, 55, 45, 75, 65, 45,
        127, // gender
        GROWTH_FAST
    }, { // Mantine
        65, 40, 70, 70, 80, 140,
        127, // gender
        GROWTH_SLOW
    }, { // Skarmory
        65, 80, 140, 70, 40, 70,
        127, // gender
        GROWTH_SLOW
    }, { // Houndour
        45, 60, 30, 65, 80, 50,
        127, // gender
        GROWTH_SLOW
    }, { // Houndoom
        75, 90, 50, 95, 110, 80,
        127, // gender
        GROWTH_SLOW
    }, { // Kingdra
        75, 95, 95, 85, 95, 95,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Phanpy
        90, 60, 60, 40, 40, 40,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Donphan
        90, 120, 120, 50, 60, 60,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Porygon2
        85, 80, 90, 60, 105, 95,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Stantler
        73, 95, 62, 85, 85, 65,
        127, // gender
        GROWTH_SLOW
    }, { // Smeargle
        55, 20, 35, 75, 20, 45,
        127, // gender
        GROWTH_FAST
    }, { // Tyrogue
        35, 35, 35, 35, 35, 35,
        0, // gender
        GROWTH_MEDIUM_FAST
    }, { // Hitmontop
        50, 95, 95, 70, 35, 110,
        0, // gender
        GROWTH_MEDIUM_FAST
    }, { // Smoochum
        45, 30, 15, 65, 85, 65,
        254, // gender
        GROWTH_MEDIUM_FAST
    }, { // Elekid
        45, 63, 37, 95, 65, 55,
        63, // gender
        GROWTH_MEDIUM_FAST
    }, { // Magby
        45, 75, 37, 83, 70, 55,
        63, // gender
        GROWTH_MEDIUM_FAST
    }, { // Miltank
        95, 80, 105, 100, 40, 70,
        254, // gender
        GROWTH_SLOW
    }, { // Blissey
        255, 10, 10, 55, 75, 135,
        254, // gender
        GROWTH_FAST
    }, { // Raikou
        90, 85, 75, 115, 115, 100,
        255, // gender
        GROWTH_SLOW
    }, { // Entei
        115, 115, 85, 100, 90, 75,
        255, // gender
        GROWTH_SLOW
    }, { // Suicune
        100, 75, 115, 85, 90, 115,
        255, // gender
        GROWTH_SLOW
    }, { // Larvitar
        50, 64, 50, 41, 45, 50,
        127, // gender
        GROWTH_SLOW
    }, { // Pupitar
        70, 84, 70, 51, 65, 70,
        127, // gender
        GROWTH_SLOW
    }, { // Tyranitar
        100, 134, 110, 61, 95, 100,
        127, // gender
        GROWTH_SLOW
    }, { // Lugia
        106, 90, 130, 110, 90, 154,
        255, // gender
        GROWTH_SLOW
    }, { // Ho-Oh
        106, 130, 90, 90, 110, 154,
        255, // gender
        GROWTH_SLOW
    }, { // Celebi
        100, 100, 100, 100, 100, 100,
        255, // gender
        GROWTH_MEDIUM_SLOW
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // ?
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Treecko
        40, 45, 35, 70, 65, 55,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Grovyle
        50, 65, 45, 95, 85, 65,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Sceptile
        70, 85, 65, 120, 105, 85,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Torchic
        45, 60, 40, 45, 70, 50,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Combusken
        60, 85, 60, 55, 85, 60,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Blaziken
        80, 120, 70, 80, 110, 70,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Mudkip
        50, 70, 50, 40, 50, 50,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Marshtomp
        70, 85, 70, 50, 60, 70,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Swampert
        100, 110, 90, 60, 85, 90,
        31, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Poochyena
        35, 55, 35, 35, 30, 30,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Mightyena
        70, 90, 70, 70, 60, 60,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Zigzagoon
        38, 30, 41, 60, 30, 41,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Linoone
        78, 70, 61, 100, 50, 61,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Wurmple
        45, 45, 35, 20, 20, 30,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Silcoon
        50, 35, 55, 15, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Beautifly
        60, 70, 50, 65, 90, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Cascoon
        50, 35, 55, 15, 25, 25,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Dustox
        60, 50, 70, 65, 50, 90,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Lotad
        40, 30, 30, 30, 40, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Lombre
        60, 50, 50, 50, 60, 70,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Ludicolo
        80, 70, 70, 70, 90, 100,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Seedot
        40, 40, 50, 30, 30, 30,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nuzleaf
        70, 70, 40, 60, 60, 40,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Shiftry
        90, 100, 60, 80, 90, 60,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Nincada
        31, 45, 90, 40, 30, 30,
        127, // gender
        GROWTH_ERRATIC
    }, { // Ninjask
        61, 90, 45, 160, 50, 50,
        127, // gender
        GROWTH_ERRATIC
    }, { // Shedinja
        1, 90, 45, 40, 30, 30,
        255, // gender
        GROWTH_ERRATIC
    }, { // Taillow
        40, 55, 30, 85, 30, 30,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Swellow
        60, 85, 60, 125, 50, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Shroomish
        60, 40, 60, 35, 40, 60,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Breloom
        60, 130, 80, 70, 60, 60,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Spinda
        60, 60, 60, 60, 60, 60,
        127, // gender
        GROWTH_FAST
    }, { // Wingull
        40, 30, 30, 85, 55, 30,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Pelipper
        60, 50, 100, 65, 85, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Surskit
        40, 30, 32, 65, 50, 52,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Masquerain
        70, 60, 62, 60, 80, 82,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Wailmer
        130, 70, 35, 60, 70, 35,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Wailord
        170, 90, 45, 60, 90, 45,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Skitty
        50, 45, 45, 50, 35, 35,
        191, // gender
        GROWTH_FAST
    }, { // Delcatty
        70, 65, 65, 70, 55, 55,
        191, // gender
        GROWTH_FAST
    }, { // Kecleon
        60, 90, 70, 40, 60, 120,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Baltoy
        40, 40, 55, 55, 40, 70,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Claydol
        60, 70, 105, 75, 70, 120,
        255, // gender
        GROWTH_MEDIUM_FAST
    }, { // Nosepass
        30, 45, 135, 30, 45, 90,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Torkoal
        70, 85, 140, 20, 85, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Sableye
        50, 75, 75, 50, 65, 65,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Barboach
        50, 48, 43, 60, 46, 41,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Whiscash
        110, 78, 73, 60, 76, 71,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Luvdisc
        43, 30, 55, 97, 40, 65,
        191, // gender
        GROWTH_FAST
    }, { // Corphish
        43, 80, 65, 35, 50, 35,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Crawdaunt
        63, 120, 85, 55, 90, 55,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Feebas
        20, 15, 20, 80, 10, 55,
        127, // gender
        GROWTH_ERRATIC
    }, { // Milotic
        95, 60, 79, 81, 100, 125,
        127, // gender
        GROWTH_ERRATIC
    }, { // Carvanha
        45, 90, 20, 65, 65, 20,
        127, // gender
        GROWTH_SLOW
    }, { // Sharpedo
        70, 120, 40, 95, 95, 40,
        127, // gender
        GROWTH_SLOW
    }, { // Trapinch
        45, 100, 45, 10, 45, 45,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Vibrava
        50, 70, 50, 70, 50, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Flygon
        80, 100, 80, 100, 80, 80,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Makuhita
        72, 60, 30, 25, 20, 30,
        63, // gender
        GROWTH_FLUCTUATING
    }, { // Hariyama
        144, 120, 60, 50, 40, 60,
        63, // gender
        GROWTH_FLUCTUATING
    }, { // Electrike
        40, 45, 40, 65, 65, 40,
        127, // gender
        GROWTH_SLOW
    }, { // Manectric
        70, 75, 60, 105, 105, 60,
        127, // gender
        GROWTH_SLOW
    }, { // Numel
        60, 60, 40, 35, 65, 45,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Camerupt
        70, 100, 70, 40, 105, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Spheal
        70, 40, 50, 25, 55, 50,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Sealeo
        90, 60, 70, 45, 75, 70,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Walrein
        110, 80, 90, 65, 95, 90,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Cacnea
        50, 85, 40, 35, 85, 40,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Cacturne
        70, 115, 60, 55, 115, 60,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Snorunt
        50, 50, 50, 50, 50, 50,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Glalie
        80, 80, 80, 80, 80, 80,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Lunatone
        70, 55, 65, 70, 95, 85,
        255, // gender
        GROWTH_FAST
    }, { // Solrock
        70, 95, 85, 70, 55, 65,
        255, // gender
        GROWTH_FAST
    }, { // Azurill
        50, 20, 40, 20, 20, 40,
        191, // gender
        GROWTH_FAST
    }, { // Spoink
        60, 25, 35, 60, 70, 80,
        127, // gender
        GROWTH_FAST
    }, { // Grumpig
        80, 45, 65, 80, 90, 110,
        127, // gender
        GROWTH_FAST
    }, { // Plusle
        60, 50, 40, 95, 85, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Minun
        60, 40, 50, 95, 75, 85,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Mawile
        50, 85, 85, 50, 55, 55,
        127, // gender
        GROWTH_FAST
    }, { // Meditite
        30, 40, 55, 60, 40, 55,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Medicham
        60, 60, 75, 80, 60, 75,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Swablu
        45, 40, 60, 50, 40, 75,
        127, // gender
        GROWTH_ERRATIC
    }, { // Altaria
        75, 70, 90, 80, 70, 105,
        127, // gender
        GROWTH_ERRATIC
    }, { // Wynaut
        95, 23, 48, 23, 23, 48,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Duskull
        20, 40, 90, 25, 30, 90,
        127, // gender
        GROWTH_FAST
    }, { // Dusclops
        40, 70, 130, 25, 60, 130,
        127, // gender
        GROWTH_FAST
    }, { // Roselia
        50, 60, 45, 65, 100, 80,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Slakoth
        60, 60, 60, 30, 35, 35,
        127, // gender
        GROWTH_SLOW
    }, { // Vigoroth
        80, 80, 80, 90, 55, 55,
        127, // gender
        GROWTH_SLOW
    }, { // Slaking
        150, 160, 100, 100, 95, 65,
        127, // gender
        GROWTH_SLOW
    }, { // Gulpin
        70, 43, 53, 40, 43, 53,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Swalot
        100, 73, 83, 55, 73, 83,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Tropius
        99, 68, 83, 51, 72, 87,
        127, // gender
        GROWTH_SLOW
    }, { // Whismur
        64, 51, 23, 28, 51, 23,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Loudred
        84, 71, 43, 48, 71, 43,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Exploud
        104, 91, 63, 68, 91, 63,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Clamperl
        35, 64, 85, 32, 74, 55,
        127, // gender
        GROWTH_ERRATIC
    }, { // Huntail
        55, 104, 105, 52, 94, 75,
        127, // gender
        GROWTH_ERRATIC
    }, { // Gorebyss
        55, 84, 105, 52, 114, 75,
        127, // gender
        GROWTH_ERRATIC
    }, { // Absol
        65, 130, 60, 75, 75, 60,
        127, // gender
        GROWTH_MEDIUM_SLOW
    }, { // Shuppet
        44, 75, 35, 45, 63, 33,
        127, // gender
        GROWTH_FAST
    }, { // Banette
        64, 115, 65, 65, 83, 63,
        127, // gender
        GROWTH_FAST
    }, { // Seviper
        73, 100, 60, 65, 100, 60,
        127, // gender
        GROWTH_FLUCTUATING
    }, { // Zangoose
        73, 115, 60, 90, 60, 60,
        127, // gender
        GROWTH_ERRATIC
    }, { // Relicanth
        100, 90, 130, 55, 45, 65,
        31, // gender
        GROWTH_SLOW
    }, { // Aron
        50, 70, 100, 30, 40, 40,
        127, // gender
        GROWTH_SLOW
    }, { // Lairon
        60, 90, 140, 40, 50, 50,
        127, // gender
        GROWTH_SLOW
    }, { // Aggron
        70, 110, 180, 50, 60, 60,
        127, // gender
        GROWTH_SLOW
    }, { // Castform
        70, 70, 70, 70, 70, 70,
        127, // gender
        GROWTH_MEDIUM_FAST
    }, { // Volbeat
        65, 73, 55, 85, 47, 75,
        0, // gender
        GROWTH_ERRATIC
    }, { // Illumise
        65, 47, 55, 85, 73, 75,
        254, // gender
        GROWTH_FLUCTUATING
    }, { // Lileep
        66, 41, 77, 23, 61, 87,
        31, // gender
        GROWTH_ERRATIC
    }, { // Cradily
        86, 81, 97, 43, 81, 107,
        31, // gender
        GROWTH_ERRATIC
    }, { // Anorith
        45, 95, 50, 75, 40, 50,
        31, // gender
        GROWTH_ERRATIC
    }, { // Armaldo
        75, 125, 100, 45, 70, 80,
        31, // gender
        GROWTH_ERRATIC
    }, { // Ralts
        28, 25, 25, 40, 45, 35,
        127, // gender
        GROWTH_SLOW
    }, { // Kirlia
        38, 35, 35, 50, 65, 55,
        127, // gender
        GROWTH_SLOW
    }, { // Gardevoir
        68, 65, 65, 80, 125, 115,
        127, // gender
        GROWTH_SLOW
    }, { // Bagon
        45, 75, 60, 50, 40, 30,
        127, // gender
        GROWTH_SLOW
    }, { // Shelgon
        65, 95, 100, 50, 60, 50,
        127, // gender
        GROWTH_SLOW
    }, { // Salamence
        95, 135, 80, 100, 110, 80,
        127, // gender
        GROWTH_SLOW
    }, { // Beldum
        40, 55, 80, 30, 35, 60,
        255, // gender
        GROWTH_SLOW
    }, { // Metang
        60, 75, 100, 50, 55, 80,
        255, // gender
        GROWTH_SLOW
    }, { // Metagross
        80, 135, 130, 70, 95, 90,
        255, // gender
        GROWTH_SLOW
    }, { // Regirock
        80, 100, 200, 50, 50, 100,
        255, // gender
        GROWTH_SLOW
    }, { // Regice
        80, 50, 100, 50, 100, 200,
        255, // gender
        GROWTH_SLOW
    }, { // Registeel
        80, 75, 150, 50, 75, 150,
        255, // gender
        GROWTH_SLOW
    }, { // Kyogre
        100, 100, 90, 90, 150, 140,
        255, // gender
        GROWTH_SLOW
    }, { // Groudon
        100, 150, 140, 90, 100, 90,
        255, // gender
        GROWTH_SLOW
    }, { // Rayquaza
        105, 150, 90, 95, 150, 90,
        255, // gender
        GROWTH_SLOW
    }, { // Latias
        80, 80, 90, 110, 110, 130,
        254, // gender
        GROWTH_SLOW
    }, { // Latios
        80, 90, 80, 110, 130, 110,
        0, // gender
        GROWTH_SLOW
    }, { // Jirachi
        100, 100, 100, 100, 100, 100,
        255, // gender
        GROWTH_SLOW
    }, { // Deoxys
        50, 150, 50, 150, 150, 50,
        255, // gender
        GROWTH_SLOW
    }, { // Chimecho
        65, 50, 70, 65, 95, 80,
        127, // gender
        GROWTH_FAST
    }
};
