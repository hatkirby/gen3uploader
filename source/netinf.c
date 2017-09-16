/*
 * Copyright (C) 2008 Tantric
 * Copyright (C) 2012 Pedro Aguiar
 * Copyright (C) 2017 hatkirby
 *
 * Originally part of the WiiTweet project, which was distributed under the
 * GPL.
 */
#include "netinf.h"
#include <gccore.h>
#include <network.h>
#include <ogc/lwp_watchdog.h>
#include <sys/errno.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

static bool networkInit = false;
static lwp_t networkThread = LWP_THREAD_NULL;
static u8 netStack[32768] ATTRIBUTE_ALIGN(32);
static char wiiIP[16] = {0};
static bool netHalt = false;

static void* interface(void* arg)
{
  static bool prevInit = false;

  while (!netHalt)
  {
    int retry = 5;
    int result = -1;

    while ((retry > 0) && (!netHalt))
    {
      if (prevInit)
      {
        net_deinit();

        for (int i=0; (i<400) && !netHalt; i++)
        {
          if (net_get_status() != -EBUSY)
          {
            usleep(2000);
            net_wc24cleanup();
            prevInit = false;
            usleep(20000);

            break;
          }

          usleep(20000);
        }
      }

      usleep(2000);

      if (net_init_async(NULL, NULL))
      {
        sleep(1);

        retry--;

        continue;
      }

      result = net_get_status();
      for (int wait = 400; (wait > 0) && (result == -EBUSY) && !netHalt; wait++)
      {
        usleep(20000);

        result = net_get_status();
      }

      if (result == 0)
      {
        break;
      }

      retry--;

      usleep(2000);
    }

    if (result == 0)
    {
      struct in_addr hostip;
      hostip.s_addr = net_gethostip();

      if (hostip.s_addr)
      {
        strcpy(wiiIP, inet_ntoa(hostip));
        networkInit = true;
        prevInit = true;
      }
    }

    if (!netHalt)
    {
      LWP_SuspendThread(networkThread);
    }
  }

  return NULL;
}

static void startNetworkThread()
{
  netHalt = false;

  if (networkThread == LWP_THREAD_NULL)
  {
    LWP_CreateThread(&networkThread, interface, NULL, netStack, 8192, 40);
  } else {
    LWP_ResumeThread(networkThread);
  }
}

static void stopNetworkThread()
{
  if ((networkThread == LWP_THREAD_NULL)
    || (!LWP_ThreadIsSuspended(networkThread)))
  {
    return;
  }

  netHalt = true;

  LWP_ResumeThread(networkThread);
  LWP_JoinThread(networkThread, NULL);

  networkThread = LWP_THREAD_NULL;
}

bool initializeNetwork()
{
  stopNetworkThread();

  if (networkInit && (net_gethostip() > 0))
  {
    return true;
  }

  networkInit = false;

  printf("Initializing network...\n");

  u64 start = gettime();
  startNetworkThread();

  while (!LWP_ThreadIsSuspended(networkThread))
  {
    usleep(50 * 1000);

    if (diff_sec(start, gettime()) > 10)
    {
      break;
    }
  }

  return networkInit;
}
