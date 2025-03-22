#ifndef _STRING_UTILS_H
#define _STRING_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "sm64.h"

#ifdef __SWITCH__
char *strdup(const char *str);
#endif

#ifdef __cplusplus
}
#endif

#endif // _STRING_UTILS_H