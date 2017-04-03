#include "parse.h"

void search_accounts(xmlNode *current, account **acc) {
  account **chase = acc;
  for (; current; current = current->next) {
    if (current->type == XML_ELEMENT_NODE) {
      if (strcmp((char *)current->name, "article") == 0) {
        printf("%s\n", current->name);
        chase = &build_account(current, chase)->next;
      }
      search_accounts(current->children, chase);
    }
  }
}

account *build_account(xmlNode *article, account **acc) {
  account *entry = (account *)malloc(sizeof(account));
  entry->username = (char *)malloc(1);
  entry->password = (char *)malloc(1);
  entry->success = 0;
  entry->next = NULL;
  *acc = entry;

  return entry;
}

void parse_webpage(webpage *web) {
  htmlDocPtr doc =
      htmlReadMemory(web->raw, web->length, web->URL, NULL, HTML_FLAGS);
  if (!doc) {
    print_error("parse_webpage::htmlReadMemory returned NULL.");
  } else {
    search_accounts(xmlDocGetRootElement(doc), &web->first);
    xmlFreeDoc(doc);
    xmlCleanupParser();
    web->first = NULL;
  }
}
