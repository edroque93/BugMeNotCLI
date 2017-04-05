#include "fetch.h"

size_t write_callback(void *ptr, size_t size, size_t nmeb, void *userdata) {
  webpage *stream = (webpage *)userdata;
  size_t rsize = size * nmeb;

  if (rsize) {
    stream->raw = (char *)realloc(stream->raw, stream->length + rsize + 1);
    memcpy(stream->raw + stream->length, ptr, rsize);
    stream->length += rsize;
    stream->raw[stream->length] = 0;
  }

  return rsize;
}

void fetch_webpage(webpage *web) {
  web->raw = NULL;
  web->length = 0;

  CURLcode error = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (error) {
    print_error("fetch_webpage::curl_global_init returned error.");
  }
  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL, web->URL);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, web);
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);
  curl_global_cleanup();
}
