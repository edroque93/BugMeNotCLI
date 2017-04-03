#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

typedef struct account {
  char *username;
  char *password;
  int success;
  struct account *next;
} account;

typedef struct webpage {
  char *URL;
  char *raw;
  size_t length;
  struct account *first;
} webpage;

void free_chain(account *node);
void free_memory(webpage *web);
void print_error(char *msg);

#endif
