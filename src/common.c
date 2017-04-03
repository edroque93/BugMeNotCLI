#include "common.h"

void free_webpage(webpage *web) { free(web->raw); }

void print_error(char *msg) { fprintf(stderr, "%s\n", msg); }
