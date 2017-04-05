#include "parse.h"

void search_accounts(xmlNode *current, account **acc) {
  account **chase = acc;
  while (current) {
    if (current->type == XML_ELEMENT_NODE) {
      if (strcmp((char *)current->name, "article") == 0) {
        chase = &build_account(current, chase)->next;
        current = current->next;
        continue;
      }
      search_accounts(current->children, chase);
    }
    current = current->next;
  }
}

char *get_username(xmlNode *article) {
  char *username;
  xmlNode *current = article->children->children;

  while (current) {
    if (strcmp((char *)current->name, "dt") == 0) {
      xmlChar *label = xmlNodeGetContent(current);
      if (strcmp((char *)label, "Username:") == 0) {
        current = current->next->children;
        xmlChar *xusername = xmlNodeGetContent(current);
        size_t xlen = strlen((char *)xusername);
        username = (char *)malloc(xlen + sizeof(char));
        memcpy(username, xusername, xlen);
        username[xlen] = '\0';
        xmlFree(xusername);
        xmlFree(label);
        break;
      }
      xmlFree(label);
    }
    current = current->next;
  }

  return username;
}

char *get_password(xmlNode *article) {
  char *username;
  xmlNode *current = article->children->children;

  while (current) {
    if (strcmp((char *)current->name, "dt") == 0) {
      xmlChar *label = xmlNodeGetContent(current);
      if (strcmp((char *)label, "Password:") == 0) {
        current = current->next->children;
        xmlChar *xusername = xmlNodeGetContent(current);
        size_t xlen = strlen((char *)xusername);
        username = (char *)malloc(xlen + sizeof(char));
        memcpy(username, xusername, xlen);
        username[xlen] = '\0';
        xmlFree(xusername);
        xmlFree(label);
        break;
      }
      xmlFree(label);
    }
    current = current->next;
  }

  return username;
}

int get_success(xmlNode *article) {
  int success = 0;
  xmlNode *current = article->children->children;

  while (current) {
    if (strcmp((char *)current->name, "dd") == 0) {
      xmlChar *prop = xmlGetProp(current, (xmlChar *)"class");
      if (prop) {
        if (strcmp((char *)prop, "stats") == 0) {
          xmlChar *rate = xmlNodeGetContent(current->children->next->children);
          for (int i = 1; i <= 3; i++)
            if (rate[i] == '%') {
              rate[i] = '\0';
              break;
            }
          success = atoi((char *)rate);
          xmlFree(rate);
        }
        xmlFree(prop);
      }
    }
    current = current->next;
  }

  return success;
}

account *build_account(xmlNode *article, account **acc) {
  account *entry = (account *)malloc(sizeof(account));
  entry->username = get_username(article);
  entry->password = get_password(article);
  entry->success = get_success(article);
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
  }
}
