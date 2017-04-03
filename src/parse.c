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

account *retrieve_account(xmlNode *article) {
  account *entry = (account *)malloc(sizeof(account));
  // malloc username and password
  entry->username = (char *)malloc(1);
  entry->password = (char *)malloc(1);
  entry->success = 0;
  entry->next = NULL;

  return entry;
}

void parse_webpage(webpage *web) {
  htmlDocPtr doc =
      htmlReadMemory(web->raw, web->length, web->URL, NULL, HTML_FLAGS);
  if (!doc) {
    print_error("parse_webpage::htmlReadMemory returned NULL.");
  } else {
    xmlNode *root_element = NULL;
    root_element = xmlDocGetRootElement(doc);
    printf("%s\n", root_element->name);
    print_element_names(root_element);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    web->first = NULL;
  }
}
