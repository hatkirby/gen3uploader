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

const char* charmap[] = {
  " ",            // space
  "\xe3\x81\x82", // hiragana letter a
  "\xe3\x81\x84", // hiragana letter i
  "\xe3\x81\x86", // hiragana letter u
  "\xe3\x81\x88", // hiragana letter e
  "\xe3\x81\x8a", // hiragana letter o
  "\xe3\x81\x8b", // hiragana letter ka
  "\xe3\x81\x8d", // hiragana letter ki
  "\xe3\x81\x8f", // hiragana letter ku
  "\xe3\x81\x91", // hiragana letter ke
  "\xe3\x81\x93", // hiragana letter ko
  "\xe3\x81\x95", // hiragana letter sa
  "\xe3\x81\x97", // hiragana letter si
  "\xe3\x81\x99", // hiragana letter su
  "\xe3\x81\x9b", // hiragana letter se
  "\xe3\x81\x9d", // hiragana letter so
  "\xe3\x81\x9f", // hiragana letter ta
  "\xe3\x81\xa1", // hiragana letter ti
  "\xe3\x81\xa4", // hiragana letter tu
  "\xe3\x81\xa6", // hiragana letter te
  "\xe3\x81\xa8", // hiragana letter to
  "\xe3\x81\xaa", // hiragana letter na
  "\xe3\x81\xab", // hiragana letter ni
  "\xe3\x81\xac", // hiragana letter nu
  "\xe3\x81\xad", // hiragana letter ne
  "\xe3\x81\xae", // hiragana letter no
  "\xe3\x81\xaf", // hiragana letter ha
  "\xe3\x81\xb2", // hiragana letter hi
  "\xe3\x81\xb5", // hiragana letter hu
  "\xe3\x81\xb8", // hiragana letter he
  "\xe3\x81\xbb", // hiragana letter ho
  "\xe3\x81\xbe", // hiragana letter ma
  "\xe3\x81\xbf", // hiragana letter mi
  "\xe3\x82\x80", // hiragana letter mu
  "\xe3\x82\x81", // hiragana letter me
  "\xe3\x82\x82", // hiragana letter mo
  "\xe3\x82\x84", // hiragana letter ya
  "\xe3\x82\x86", // hiragana letter yu
  "\xe3\x82\x88", // hiragana letter yo
  "\xe3\x82\x89", // hiragana letter ra
  "\xe3\x82\x8a", // hiragana letter ri
  "\xe3\x82\x8b", // hiragana letter ru
  "\xe3\x82\x8c", // hiragana letter re
  "\xe3\x82\x8d", // hiragana letter ro
  "\xe3\x82\x8f", // hiragana letter wa
  "\xe3\x82\x92", // hiragana letter wo
  "\xe3\x82\x93", // hiragana letter n
  "\xe3\x81\x81", // hiragana letter small a
  "\xe3\x81\x83", // hiragana letter small i
  "\xe3\x81\x85", // hiragana letter small u
  "\xe3\x81\x87", // hiragana letter small e
  "\xe3\x81\x89", // hiragana letter small o
  "\xe3\x82\x83", // hiragana letter small ya
  "\xe3\x82\x85", // hiragana letter small yu
  "\xe3\x82\x87", // hiragana letter small yo
  "\xe3\x81\x8c", // hiragana letter ga
  "\xe3\x81\x8e", // hiragana letter gi
  "\xe3\x81\x90", // hiragana letter gu
  "\xe3\x81\x92", // hiragana letter ge
  "\xe3\x81\x94", // hiragana letter go
  "\xe3\x81\x96", // hiragana letter za
  "\xe3\x81\x98", // hiragana letter zi
  "\xe3\x81\x9a", // hiragana letter zu
  "\xe3\x81\x9c", // hiragana letter ze
  "\xe3\x81\x9e", // hiragana letter zo
  "\xe3\x81\xa0", // hiragana letter da
  "\xe3\x81\xa2", // hiragana letter di
  "\xe3\x81\xa5", // hiragana letter du
  "\xe3\x81\xa7", // hiragana letter de
  "\xe3\x81\xa9", // hiragana letter do
  "\xe3\x81\xb0", // hiragana letter ba
  "\xe3\x81\xb3", // hiragana letter bi
  "\xe3\x81\xb6", // hiragana letter bu
  "\xe3\x81\xb9", // hiragana letter be
  "\xe3\x81\xbc", // hiragana letter bo
  "\xe3\x81\xb1", // hiragana letter pa
  "\xe3\x81\xb4", // hiragana letter pi
  "\xe3\x81\xb7", // hiragana letter pu
  "\xe3\x81\xba", // hiragana letter pe
  "\xe3\x81\xbd", // hiragana letter po
  "\xe3\x81\xa3", // hiragana letter small tu
  "\xe3\x82\xa2", // katakana letter a
  "\xe3\x82\xa4", // katakana letter i
  "\xe3\x82\xa6", // katakana letter u
  "\xe3\x82\xa8", // katakana letter e
  "\xe3\x82\xaa", // katakana letter o
  "\xe3\x82\xab", // katakana letter ka
  "\xe3\x82\xad", // katakana letter ki
  "\xe3\x82\xaf", // katakana letter ku
  "\xe3\x82\xb1", // katakana letter ke
  "\xe3\x82\xb3", // katakana letter ko
  "\xe3\x82\xb5", // katakana letter sa
  "\xe3\x82\xb7", // katakana letter si
  "\xe3\x82\xb9", // katakana letter su
  "\xe3\x82\xbb", // katakana letter se
  "\xe3\x82\xbd", // katakana letter so
  "\xe3\x82\xbf", // katakana letter ta
  "\xe3\x83\x81", // katakana letter ti
  "\xe3\x83\x84", // katakana letter tu
  "\xe3\x83\x86", // katakana letter te
  "\xe3\x83\x88", // katakana letter to
  "\xe3\x83\x8a", // katakana letter na
  "\xe3\x83\x8b", // katakana letter ni
  "\xe3\x83\x8c", // katakana letter nu
  "\xe3\x83\x8d", // katakana letter ne
  "\xe3\x83\x8e", // katakana letter no
  "\xe3\x83\x8f", // katakana letter ha
  "\xe3\x83\x92", // katakana letter hi
  "\xe3\x83\x95", // katakana letter hu
  "\xe3\x83\x98", // katakana letter he
  "\xe3\x83\x9b", // katakana letter ho
  "\xe3\x83\x9e", // katakana letter ma
  "\xe3\x83\x9f", // katakana letter mi
  "\xe3\x83\xa0", // katakana letter mu
  "\xe3\x83\xa1", // katakana letter me
  "\xe3\x83\xa2", // katakana letter mo
  "\xe3\x83\xa4", // katakana letter ya
  "\xe3\x83\xa6", // katakana letter yu
  "\xe3\x83\xa8", // katakana letter yo
  "\xe3\x83\xa9", // katakana letter ra
  "\xe3\x83\xaa", // katakana letter ri
  "\xe3\x83\xab", // katakana letter ru
  "\xe3\x83\xac", // katakana letter re
  "\xe3\x83\xad", // katakana letter ro
  "\xe3\x83\xaf", // katakana letter wa
  "\xe3\x83\xb2", // katakana letter wo
  "\xe3\x83\xb3", // katakana letter n
  "\xe3\x82\xa1", // katakana letter small a
  "\xe3\x82\xa3", // katakana letter small i
  "\xe3\x82\xa5", // katakana letter small u
  "\xe3\x82\xa7", // katakana letter small e
  "\xe3\x82\xa9", // katakana letter small o
  "\xe3\x83\xa3", // katakana letter small ya
  "\xe3\x83\xa5", // katakana letter small yu
  "\xe3\x83\xa7", // katakana letter small yo
  "\xe3\x82\xac", // katakana letter ga
  "\xe3\x82\xae", // katakana letter gi
  "\xe3\x82\xb0", // katakana letter gu
  "\xe3\x82\xb2", // katakana letter ge
  "\xe3\x82\xb4", // katakana letter go
  "\xe3\x82\xb6", // katakana letter za
  "\xe3\x82\xb8", // katakana letter zi
  "\xe3\x82\xba", // katakana letter zu
  "\xe3\x82\xbc", // katakana letter ze
  "\xe3\x82\xbe", // katakana letter zo
  "\xe3\x83\x80", // katakana letter da
  "\xe3\x83\x82", // katakana letter di
  "\xe3\x83\x85", // katakana letter du
  "\xe3\x83\x87", // katakana letter de
  "\xe3\x83\x89", // katakana letter do
  "\xe3\x83\x90", // katakana letter ba
  "\xe3\x83\x93", // katakana letter bi
  "\xe3\x83\x96", // katakana letter bu
  "\xe3\x83\x99", // katakana letter be
  "\xe3\x83\x9c", // katakana letter bo
  "\xe3\x83\x91", // katakana letter pa
  "\xe3\x83\x94", // katakana letter pi
  "\xe3\x83\x97", // katakana letter pu
  "\xe3\x83\x9a", // katakana letter pe
  "\xe3\x83\x9d", // katakana letter po
  "\xe3\x83\x83", // katakana letter small tu
  "0",            // arabic numeral zero
  "1",            // arabic numeral one
  "2",            // arabic numeral two
  "3",            // arabic numeral three
  "4",            // arabic numeral four
  "5",            // arabic numeral five
  "6",            // arabic numeral six
  "7",            // arabic numeral seven
  "8",            // arabic numeral eight
  "9",            // arabic numeral nine
  0,              // exclamation mark [varies]
  0,              // question mark [varies]
  0,              // period [varies]
  0,              // hyphen [varies]
  "\xe3\x83\xbb", // interpunct
  "\xe2\x80\xa6", // ellipsis
  0,              // left double quotation mark [varies]
  0,              // right double quotation mark [varies]
  0,              // left single quotation mark [varies]
  0,              // right single quotation mark [varies]
  "\xe2\x99\x82", // mars astrological sign
  "\xe2\x99\x80", // venus astrological sign
  0,              // unused
  ",",            // comma
  0,              // unused
  "/",            // forward slash
  "A",            // uppercase latin letter a
  "B",            // uppercase latin letter b
  "C",            // uppercase latin letter c
  "D",            // uppercase latin letter d
  "E",            // uppercase latin letter e
  "F",            // uppercase latin letter f
  "G",            // uppercase latin letter g
  "H",            // uppercase latin letter h
  "I",            // uppercase latin letter i
  "J",            // uppercase latin letter j
  "K",            // uppercase latin letter k
  "L",            // uppercase latin letter l
  "M",            // uppercase latin letter m
  "N",            // uppercase latin letter n
  "O",            // uppercase latin letter o
  "P",            // uppercase latin letter p
  "Q",            // uppercase latin letter q
  "R",            // uppercase latin letter r
  "S",            // uppercase latin letter s
  "T",            // uppercase latin letter t
  "U",            // uppercase latin letter u
  "V",            // uppercase latin letter v
  "W",            // uppercase latin letter w
  "X",            // uppercase latin letter x
  "Y",            // uppercase latin letter y
  "Z",            // uppercase latin letter z
  "a",            // lowercase latin letter a
  "b",            // lowercase latin letter b
  "c",            // lowercase latin letter c
  "d",            // lowercase latin letter d
  "e",            // lowercase latin letter e
  "f",            // lowercase latin letter f
  "g",            // lowercase latin letter g
  "h",            // lowercase latin letter h
  "i",            // lowercase latin letter i
  "j",            // lowercase latin letter j
  "k",            // lowercase latin letter k
  "l",            // lowercase latin letter l
  "m",            // lowercase latin letter m
  "n",            // lowercase latin letter n
  "o",            // lowercase latin letter o
  "p",            // lowercase latin letter p
  "q",            // lowercase latin letter q
  "r",            // lowercase latin letter r
  "s",            // lowercase latin letter s
  "t",            // lowercase latin letter t
  "u",            // lowercase latin letter u
  "v",            // lowercase latin letter v
  "w",            // lowercase latin letter w
  "x",            // lowercase latin letter x
  "y",            // lowercase latin letter y
  "z",            // lowercase latin letter z
  0,              // unused
  0,              // unused
  "\xc3\x84",     // uppercase latin letter a with diaeresis
  "\xc3\x96",     // uppercase latin letter o with diaeresis
  "\xc3\x9c",     // uppercase latin letter u with diaeresis
  "\xc3\xa4",     // lowercase latin letter a with diaeresis
  "\xc3\xb6",     // lowercase latin letter o with diaeresis
  "\xc3\xbc"      // lowercase latin letter u with diaeresis
};

/**
 * Converts a string encoded with the propietary gen 3 character encoding into
 * a UTF-8 encoded string. The function will read the input buffer until either
 * the max length has been reached, or an 0xFF has been found. The output buffer
 * must be at least one plus three times the max length in size.
 */
void decodePokemonCharset(
  const u8* input,
  int maxLength,
  char* output,
  enum PokemonLanguage language)
{
  for (int i=0; i<maxLength; i++)
  {
    char cur = *input;
    input++;

    if (cur == 0xff)
    {
      break;
    }

    const char* next = 0;

    if (cur == 0xab)
    {
      // fullwidth exclamation mark
      if (language == Japanese)
      {
        next = "\xef\xbc\x81";
      }
      // exclamation mark
      else {
        next = "!";
      }
    } else if (cur == 0xac)
    {
      // fullwidth question mark
      if (language == Japanese)
      {
        next = "\xef\xbc\x9f";
      }
      // question mark
      else {
        next = "?";
      }
    } else if (cur == 0xad)
    {
      // ideographic full stop
      if (language == Japanese)
      {
        next = "\xe3\x80\x82";
      }
      // period
      else {
        next = ".";
      }
    } else if (cur == 0xae)
    {
      // katakana-hiragana prolonged sound mark
      if (language == Japanese)
      {
        next = "\xe3\x83\xbc";
      }
      // hyphen
      else {
        next = "-";
      }
    } else if (cur == 0xb1)
    {
      // left white corner bracket
      if (language == Japanese)
      {
        next = "\xe3\x80\x8e";
      }
      // double low-9 quotation mark
      else if (language == German)
      {
        next = "\xe2\x80\x9e";
      }
      // left double angle quotation mark
      else if (language == French)
      {
        next = "\xc2\xab";
      }
      // left double quotation mark
      else {
        next = "\xe2\x80\x9c";
      }
    } else if (cur == 0xb2)
    {
      // right white corner bracket
      if (language == Japanese)
      {
        next = "\xe3\x80\x8f";
      }
      // left double quotation mark
      else if (language == German)
      {
        next = "\xe2\x80\x9c";
      }
      // right double angle quotation mark
      else if (language == French)
      {
        next = "\xc2\xbb";
      }
      // right double quotation mark
      else {
        next = "\xe2\x80\x9d";
      }
    } else if (cur == 0xb3)
    {
      // left corner bracket
      if (language == Japanese)
      {
        next = "\xe3\x80\x8c";
      }
      // left single quotation mark
      else {
        next = "\xe2\x80\x98";
      }
    } else if (cur == 0xb4)
    {
      // right corner bracket
      if (language == Japanese)
      {
        next = "\xe3\x80\x8d";
      }
      // right single quotation mark
      else {
        next = "\xe2\x80\x99";
      }
    } else {
      next = charmap[(int)cur];
    }

    for (; *next != 0; next++)
    {
      *output++ = *next;
    }
  }

  *output = 0;
}
