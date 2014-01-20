#ifndef _CRYPT_H_
#define _CRYPT_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char *encoding_table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
static char *decoding_table = NULL;
static int mod_table[] = { 0, 2, 1 };

char *rot13(const char *str);
char *rot47(const char *str);

char *base64_encode(const char *data);
char *base64_decode(const char *data);

#endif