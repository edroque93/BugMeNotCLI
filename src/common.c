#include "common.h"

void free_chain(account *node) {
    printf("Libero...\n");
  while (node->next) {
    free_chain((account *)node->next);
    free(node->next);
  }
  if (node->username)
    free(node->username);
  if (node->password)
    free(node->password);
}

void free_memory(webpage *web) {
  free(web->raw);
  if (web->first)
    free_chain(web->first);
}

void print_error(char *msg) { fprintf(stderr, "%s\n", msg); }
