#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *URL;
  char *raw;
  size_t length;
} webpage;

void free_webpage(webpage *web);
void print_error(char *msg);

#endif
