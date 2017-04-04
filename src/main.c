#include "common.h"
#include "fetch.h"
#include "parse.h"

int compare(const void *a, const void *b) {
  account *A = (account *) *((int *)a);
  account *B = (account *) *((int *)b);
  //printf("Comparing %s vs %s, %d - %d\n", A->username, B->username, A->success, B->success);
  return B->success - A->success;
}

int main() {
  webpage web = {.URL = "http://bugmenot.com/view/9gag.com"};
  fetch_webpage(&web);
  parse_webpage(&web);

  size_t count = 0;
  size_t actual = 4;
  account **entries = (account **)malloc(actual * sizeof(account *));
  account *p = web.first;
  while (p) {
    
    entries[count++] = p;
    if (count == actual) {
      actual <<= 1;
      entries = (account **)realloc(entries, actual * sizeof(account *));
    }
    p = p->next;
  }

  entries = (account **)realloc(entries, count * sizeof(account *));


  qsort(entries, count, sizeof(account *), compare);

  for (int i = 0; i < count; i++) {
    printf("%p, %s, %s, %d\n", entries[i], entries[i]->username, entries[i]->password, entries[i]->success);
  }

  free(entries);
  free_memory(&web);

  return 0;
}
