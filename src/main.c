#include "common.h"
#include "fetch.h"
#include "parse.h"

int main(int argc, char **argv) {
  char *url = (char *)malloc(strlen(baseURL) + strlen(argv[1]) + 1);
  strcpy(url, baseURL);
  strcat(url, argv[1]);

  webpage web = {.URL = url};

  fetch_webpage(&web);
  parse_webpage(&web);
  sort_accounts(&web);

  account *best = web.sorted[0];
  if (best) {
    printf("Username: %s\nPassword: %s\nSuccess:  %d%%\n", best->username, best->password,
           best->success);
  }

  free_memory(&web);

  return 0;
}
