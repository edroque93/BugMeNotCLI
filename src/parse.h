#ifndef PARSE_H
#define PARSE_H

#include "common.h"
#include <libxml/HTMLparser.h>
#include <string.h>

#define HTML_FLAGS                                                             \
  (HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING |           \
   HTML_PARSE_NONET)

void search_accounts(xmlNode *current, account **acc);
char *get_username(xmlNode *article);
int get_success(xmlNode *article);
account *build_account(xmlNode *article, account **acc);
void parse_webpage(webpage *web);

#endif
