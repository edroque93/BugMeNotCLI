#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdlib.h>

extern const char *baseURL;

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
  account **sorted;
} webpage;

int compare_accounts(const void *a, const void *b);
void sort_accounts(webpage *web);
void free_chain(account *node);
void free_memory(webpage *web);
void print_error(char *msg);

#endif
