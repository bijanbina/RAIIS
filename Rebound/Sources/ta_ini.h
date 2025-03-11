/**
 * Copyright (c) 2016 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See `ini.c` for details.
 */

#ifndef TA_INI_H
#define TA_INI_H

#define INI_VERSION "0.1.1"

typedef struct TaINI TaINI;

TaINI*  ini_load(const char *filename);
void    ini_free(TaINI *ini);
char   *ini_get(TaINI *ini, const char *section, const char *key);
int     ini_sget(TaINI *ini, const char *section, const char *key,
                 const char *scanfmt, void *dst);
int     ini_getRemoteId();

#endif
