#ifndef FETCH_H
#define FETCH_H

#include "common.h"
#include <curl/curl.h>
#include <string.h>

size_t write_callback(void *ptr, size_t size, size_t nmeb, void *userdata);
void fetch_webpage(webpage *web);

#endif
