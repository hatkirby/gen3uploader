/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 *
 * Gen 3 proprietary encoding information from Bulbapedia:
 * https://bulbapedia.bulbagarden.net/wiki/Character_encoding_in_Generation_III
 */
#include "encoding.h"

const char charmap[] = {
	' ', '0',  '1',  '2',  '3',  '4', '5', '6', '7', '8', '9', '!', '?', '.', '-', ' ',
	' ', '\"', '\"', '\'', '\'', '*', '*', ' ', ',', ' ', '/', 'A', 'B', 'C', 'D', 'E',
	'F', 'G',  'H',  'I',  'J',  'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U',
	'V', 'W',  'X',  'Y',  'Z',  'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k',
	'l', 'm',  'n',  'o',  'p',  'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' '
};

char debugGen3Decode(u8 val)
{
	return charmap[val - 0xA0];
}
