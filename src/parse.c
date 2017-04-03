#include "parse.h"

void print_element_names(xmlNode *node) {
  xmlNode *cur_node = NULL;

  for (cur_node = node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      printf("%s\n", cur_node->name);
    }

    print_element_names(cur_node->children);
  }
}

void parse_webpage(webpage *web) {
  htmlDocPtr doc =
      htmlReadMemory(web->raw, web->length, web->URL, NULL, HTML_FLAGS);
  if (doc == NULL) {
    print_error("parse_webpage::htmlReadMemory returned NULL.");
  } else {
    xmlNode *root_element = NULL;
    root_element = xmlDocGetRootElement(doc);
    printf("%s\n", root_element->name);
    print_element_names(root_element);
    xmlFreeDoc(doc);
    xmlCleanupParser();
  }
}
