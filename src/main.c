#include "common.h"
#include "fetch.h"
#include "parse.h"

int main() {
  webpage web = {.URL = "http://bugmenot.com/view/9gag.com"};
  fetch_webpage(&web);
  parse_webpage(&web);
  // printf("%s\n", web.raw);

  free_memory(&web);

  return 0;
}
