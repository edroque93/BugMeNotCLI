#include "fetch.h"

int main() {
  char *web = fetch_webpage("http://bugmenot.com/view/linkedin.com");
  printf("%s\n", web);
  free(web);

  return 0;
}
