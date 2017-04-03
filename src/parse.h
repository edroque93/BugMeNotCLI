#ifndef PARSE_H
#define PARSE_H

#include "common.h"
#include <libxml/HTMLparser.h>

#define HTML_FLAGS                                                             \
  (HTML_PARSE_NOBLANKS | HTML_PARSE_NOERROR | HTML_PARSE_NOWARNING |           \
   HTML_PARSE_NONET)

void print_element_names(xmlNode *node);
void parse_webpage(webpage *web);

#endif
