#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *username;
  char *password;
  int success;
  struct account *next;
} account;

typedef struct {
  char *URL;
  char *raw;
  size_t length;
  account *first;
} webpage;

void free_chain(account *node);
void free_memory(webpage *web);
void print_error(char *msg);

#endif
