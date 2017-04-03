#include <curl/curl.h>
//#include <libxml/tree.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *contents;
  int length;
} webpage;

size_t write_callback(void *ptr, size_t size, size_t nmeb, void *userdata) {
  webpage *stream = (webpage *)userdata;
  size_t rsize = size * nmeb;

  if (rsize) {
    if (!stream->contents) {
      stream->contents = (char *)malloc(rsize + 1);
    } else {
      stream->contents =
          (char *)realloc(stream->contents, stream->length + rsize + 1);
    }
    memcpy(stream->contents + stream->length, ptr, rsize);
    stream->length += rsize;
    stream->contents[stream->length] = 0;
  }

  return rsize;
}

int main() {
  webpage web = {.contents = NULL};

  CURL *handle = curl_easy_init();
  curl_easy_setopt(handle, CURLOPT_URL,
                   "http://bugmenot.com/view/linkedin.com");
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(handle, CURLOPT_WRITEDATA, &web);
  curl_easy_perform(handle);
  curl_easy_cleanup(handle);

  printf("%s\n", web.contents);

  return 0;
}
