#include "common.h"

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
  free(web->raw);
  if (web->first)
    free_chain(web->first);
}

void print_error(char *msg) { fprintf(stderr, "%s\n", msg); }
