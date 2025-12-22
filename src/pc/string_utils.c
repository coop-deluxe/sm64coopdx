#include "string_utils.h"
#include <string.h>
#include <stdlib.h>

#ifdef __SWITCH__

char *strdup(const char *str) {
  size_t size = strlen(str);
  char *nstr = malloc((size + 1) * sizeof(char));
  strcpy(nstr, str);
  nstr[size] = 0;
  return nstr;
}

#endif