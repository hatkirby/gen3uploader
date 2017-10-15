/*
 * Copyright (C) 2008 Tantric
 * Copyright (C) 2012 Pedro Aguiar
 * Copyright (C) 2017 hatkirby
 *
 * Originally part of the WiiTweet project, which was distributed under the
 * GPL.
 */
#ifndef HTTP_H_A46C206E
#define HTTP_H_A46C206E

#include "cJSON.h"
#include <wolfssl/options.h>
#include <wolfssl/ssl.h>

typedef enum {
	HTTPR_OK,
	HTTPR_ERR_CONNECT,
	HTTPR_ERR_TIMEOUT,
  HTTPR_ERR_WRITE,
  HTTPR_ERR_RECEIVE,
  HTTPR_ERR_SSL,
  HTTPR_ERR_STATUS
} http_res;

/**
 * Submits a JSON request to a web service. Takes ownership of the cJSON object.
 */
int submitToApi(
  const char* endpoint,
  WOLFSSL_CTX* sslContext,
  cJSON* data,
  const char* username,
  const char* token);

#endif /* end of include guard: HTTP_H_A46C206E */
