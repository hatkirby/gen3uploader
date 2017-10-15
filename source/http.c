/*
 * Copyright (C) 2008 Tantric
 * Copyright (C) 2012 Pedro Aguiar
 * Copyright (C) 2017 hatkirby
 *
 * Originally part of the WiiTweet project, which was distributed under the
 * GPL.
 */
#include "http.h"
#include <gccore.h>
#include <network.h>
#include <unistd.h>
#include <fcntl.h>
#include <ogcsys.h>
#include <ogc/lwp_watchdog.h>
#include <sys/errno.h>
#include <string.h>
#include <stdio.h>

#define TCP_CONNECT_TIMEOUT 	  4000
#define TCP_SEND_SIZE 		      (32 * 1024)
#define TCP_RECV_SIZE 		      (32 * 1024)
#define TCP_BLOCK_RECV_TIMEOUT 	4000
#define TCP_BLOCK_SEND_TIMEOUT 	4000
#define TCP_BLOCK_SIZE 		      1024
#define HTTP_TIMEOUT 		        10000
#define IOS_O_NONBLOCK		      0x04

static int tcpWrite(
  bool secure,
  void* firstParam,
  const u8* buffer,
  u32 length)
{
  int left = length;
  int sent = 0;
  int step = 0;

  u64 t = gettime();
  while (left)
  {
    if (ticks_to_millisecs(diff_ticks(t, gettime())) > TCP_BLOCK_SEND_TIMEOUT)
    {
      return HTTPR_ERR_TIMEOUT;
    }

    int block = left;
    if (block > TCP_SEND_SIZE)
    {
      block = TCP_SEND_SIZE;
    }

    int result;
    if (secure)
    {
      result = wolfSSL_write(*(WOLFSSL**)firstParam, buffer, block);
    } else {
      result = net_write(*(s32*)firstParam, buffer, block);
    }

    if ((result == 0) || (result == -56) || (result == -11))
    {
      usleep(20 * 1000);

      continue;
    }

    if (result < 0)
    {
      break;
    }

    sent += result;
    left -= result;
    buffer += result;
    usleep(1000);

    if ((sent / TCP_BLOCK_SIZE) > step)
    {
      t = gettime();
      step++;
    }
  }

  if (left == 0)
  {
    return HTTPR_OK;
  } else {
    return HTTPR_ERR_WRITE;
  }
}

static int tcpRead(
  bool secure,
  void* firstParam,
  char* buffer,
  u16 maxLength)
{
  u64 startTime = gettime();
  u16 cur = 0;

  while (cur < maxLength)
  {
    if (ticks_to_millisecs(diff_ticks(startTime, gettime())) > HTTP_TIMEOUT)
    {
      return HTTPR_ERR_TIMEOUT;
    }

    u32 result;
    if (secure)
    {
      result = wolfSSL_read(*(WOLFSSL**)firstParam, &buffer[cur], 1);
    } else {
      result = net_read(*(s32*)firstParam, &buffer[cur], 1);
    }

    if (result == -EAGAIN)
    {
      usleep(20 * 1000);

      continue;
    }

    if (result <= 0)
    {
      break;
    }

    if ((cur > 0) && (buffer[cur-1] == '\r') && (buffer[cur] == '\n'))
    {
      buffer[cur-1] = 0;

      return HTTPR_OK;
    }

    cur++;
    startTime = gettime();
    usleep(100);
  }

  return HTTPR_ERR_RECEIVE;
}

int submitToApi(
  const char* endpoint,
  WOLFSSL_CTX* sslContext,
  cJSON* data,
  const char* username,
  const char* token)
{
  // Form request body.
  cJSON* jRequestBody = cJSON_CreateObject();

  cJSON_AddItemToObject(jRequestBody, "game", data);

  const char* requestBody = cJSON_PrintUnformatted(jRequestBody);

  // Gather data from endpoint URL.
  char httpHost[64];
  char httpPath[256];
  int httpPort = 80;
  bool secure = false;

  if (!strncasecmp(endpoint, "https://", 8))
  {
    endpoint += 8;
    secure = true;
    httpPort = 443;
  } else if (!strncasecmp(endpoint, "http://", 7))
  {
    endpoint += 7;
  } else {
    return 10;
  }

  char* solidus = strchr(endpoint, '/');
  if ((solidus == NULL) || (solidus[0] == 0))
  {
    return 11;
  }

  char* colon = strchr(endpoint, ':');
  if (colon != NULL)
  {
    snprintf(httpHost, colon - endpoint + 1, "%s", endpoint);
    sscanf(colon + 1, "%d", &httpPort);
  } else {
    snprintf(httpHost, solidus - endpoint + 1, "%s", endpoint);
  }

  strcpy(httpPath, solidus);

  // Connect to endpoint.
  printf("Connecting...\n");

  s32 socket = net_socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
  if (socket < 0)
  {
    return HTTPR_ERR_CONNECT;
  }

  if (!secure)
  {
    int result = net_fcntl(socket, F_GETFL, 0);
    if (result < 0)
    {
      net_close(socket);

      return HTTPR_ERR_CONNECT;
    }

    if (net_fcntl(socket, F_SETFL, result | IOS_O_NONBLOCK))
    {
      net_close(socket);

      return HTTPR_ERR_CONNECT;
    }
  }

  struct sockaddr_in sa;
  memset(&sa, 0, sizeof(struct sockaddr_in));
  sa.sin_family = PF_INET;
  sa.sin_len = sizeof(struct sockaddr_in);
  sa.sin_port = htons(httpPort);

  struct in_addr inAddr;
  if ((strlen(httpHost) < 16) && (inet_aton(httpHost, &inAddr)))
  {
    sa.sin_addr.s_addr = inAddr.s_addr;
  } else {
    struct hostent* hp = net_gethostbyname(httpHost);
    if (!hp || (hp->h_addrtype != PF_INET))
    {
      return HTTPR_ERR_CONNECT;
    }

    memcpy(
      (char*) &sa.sin_addr,
      hp->h_addr_list[0],
      hp->h_length);
  }

  u64 time1 = ticks_to_secs(gettime());
  s32 connectResult;
  do
  {
    connectResult = net_connect(
      socket,
      (struct sockaddr*) &sa,
      sizeof(sa));

    if (ticks_to_secs(gettime()) - time1 > TCP_CONNECT_TIMEOUT*1000)
    {
      break;
    }
  } while (connectResult != -EISCONN);

  if (connectResult != -EISCONN)
  {
    net_close(socket);

    return HTTPR_ERR_CONNECT;
  }

  // Initialize SSL, if necessary.
  WOLFSSL* sslHandle = 0;
  if (secure)
  {
    sslHandle = wolfSSL_new(sslContext);
    if (sslHandle == NULL)
    {
      net_close(socket);

      return HTTPR_ERR_SSL;
    }

    wolfSSL_set_fd(sslHandle, socket);
  }

  // Send request.
  printf("Sending...\n");

  void* firstParam = 0;

  if (secure)
  {
    firstParam = &sslHandle;
  } else {
    firstParam = &socket;
  }

  char requestHeader[1024];
  char* r = requestHeader;
  r += sprintf(r, "POST %s HTTP/1.1\r\n", httpPath);
  r += sprintf(r, "Host: %s\r\n", httpHost);
  r += sprintf(r, "Content-Type: application/json\r\n");
  r += sprintf(r, "Content-Length: %d\r\n", strlen(requestBody));
  r += sprintf(r, "X-User-Login: %s\r\n", username);
  r += sprintf(r, "X-User-Token: %s\r\n", token);
  r += sprintf(r, "\r\n");

  int result = tcpWrite(
    secure,
    firstParam,
    (u8*) requestHeader,
    strlen(requestHeader));
  if (result != HTTPR_OK)
  {
    return result;
  }

  result = tcpWrite(
    secure,
    firstParam,
    (u8*) requestBody,
    strlen(requestBody));

  if (result != HTTPR_OK)
  {
    return result;
  }

  // Read response.
  char line[1024];
  int httpStatus = 404;
  while (!tcpRead(secure, firstParam, line, 1024))
  {
    if (!line[0])
    {
      break;
    }

    sscanf(line, "HTTP/1.%*u %u", &httpStatus);
  }

  if (httpStatus != 200)
  {
    return HTTPR_ERR_STATUS;
  }

  // Clean up.
  if (secure)
  {
    wolfSSL_free(sslHandle);
  }

  net_close(socket);

  cJSON_Delete(jRequestBody);

  return HTTPR_OK;
}
