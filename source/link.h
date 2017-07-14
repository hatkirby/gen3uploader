/*
 * Copyright (C) 2017 hatkirby
 *
 * This software may be modified and distributed under the terms
 * of the MIT license.  See the LICENSE file for details.
 */
#ifndef _LINK_H_
#define _LINK_H_

#include <gccore.h>

void initLink();

u32 recv();
void send(u32 msg);

u32 getMsg();
void getMsgArr(u32* arr, int len);
void sendMsg(u32 msg);

void waitForGBA();
void waitForBIOS();
void waitForGame();
void waitForAck();

#endif
