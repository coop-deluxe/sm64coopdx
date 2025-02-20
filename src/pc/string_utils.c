#include "string_utils.h"
#include <string.h>
#include <stdlib.h>

#ifdef __SWITCH__

char *strdup(const char *str) {
  size_t size = strlen(str);
  char *nstr = malloc(size * sizeof(char));
  strcpy(nstr, str);
  return nstr;
}

#endif