#include "common.h"
#include "fetch.h"
#include "parse.h"

int main() {
  webpage web = {.URL = "http://bugmenot.com/view/9gag.com"};
  fetch_webpage(&web);
  parse_webpage(&web);

  account *p = web.first;
  while (p) {
    printf("%s, %s, %d\n", p->username, p->password, p->success);
    p = p->next;
  }

  free_memory(&web);

  return 0;
}
