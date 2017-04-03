#include "fetch.h"

size_t write_callback(void *ptr, size_t size, size_t nmeb, void *userdata) {
  webpage *stream = (webpage *)userdata;
  size_t rsize = size * nmeb;

  if (rsize) {
    stream->contents =
        (char *)realloc(stream->contents, stream->length + rsize + 1);
    memcpy(stream->contents + stream->length, ptr, rsize);
    stream->length += rsize;
    stream->contents[stream->length] = 0;
  }

  return rsize;
}

char *fetch_webpage(char *url) {
  webpage web = {.contents = NULL, .length = 0};

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, url);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &web);
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);

  return web.contents;
}
