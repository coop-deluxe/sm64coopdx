#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };

char* get_version(void) {
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s %d.%d", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER);
    return sVersionString;
}