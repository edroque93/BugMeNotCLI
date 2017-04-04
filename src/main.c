#include "common.h"
#include "fetch.h"
#include "parse.h"

int compare(const void *a, const void *b) {
  return ((account *)*((long *)a))->success -
         ((account *)*((long *)a))->success;
}

int main() {
  webpage web = {.URL = "http://bugmenot.com/view/9gag.com"};

  fetch_webpage(&web);
  parse_webpage(&web);
  sort_accounts(&web);

  account **a = web.sorted;
  for (int i = 0; a[i]; i++) {
    printf("%d\n", a[i]->success);
  }

  free_memory(&web);

  return 0;
}
