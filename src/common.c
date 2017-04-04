#include "common.h"

int compare_accounts(const void *a, const void *b) {
  return ((account *)*((long *)a))->success -
         ((account *)*((long *)a))->success;
}

void sort_accounts(webpage *web) {
  size_t count = 0;
  size_t actual = 4;
  account **entries = (account **)malloc(actual * sizeof(account *));
  account *p = web->first;
  while (p) {
    entries[count++] = p;
    if (count == actual) {
      actual <<= 1;
      entries = (account **)realloc(entries, actual * sizeof(account *));
    }
    p = p->next;
  }
  entries = (account **)realloc(entries, (count + 1) * sizeof(account *));
  qsort(entries, count, sizeof(account *), compare_accounts);
  entries[count] = NULL;
  web->sorted = entries;
}

void free_chain(account *node) {
  if (node) {
    free_chain((account *)node->next);
    if (node->username)
      free(node->username);
    if (node->password)
      free(node->password);
    free(node);
  }
}

void free_memory(webpage *web) {
  free_chain(web->first);
  free(web->raw);
  free(web->sorted);
}

void print_error(char *msg) { fprintf(stderr, "%s\n", msg); }
