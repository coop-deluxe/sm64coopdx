#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
#ifdef UNSTABLE_BRANCH
#define VERSION_TEXT "unst "
#else
#define VERSION_TEXT "beta "
#endif

char* get_version(void) {
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d", VERSION_TEXT, VERSION_NUMBER);
    return sVersionString;
}