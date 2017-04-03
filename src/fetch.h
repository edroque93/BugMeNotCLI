#ifndef FETCH_H
#define FETCH_H

#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *contents;
  size_t length;
} webpage;

size_t write_callback(void *ptr, size_t size, size_t nmeb, void *userdata);
char *fetch_webpage(char *url);

#endif
