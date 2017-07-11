/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef _LINK_H_
#define _LINK_H_

#include <gba.h>

void initializeLink();
void waitForAck();
void sendS32(s32 val);
void sendU32(u32 val);

#endif
