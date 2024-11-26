#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
static char sOnlineVersionString[MAX_VERSION_LENGTH] = { 0 };

const char* get_version(void) {
#if defined(VERSION_US)
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s", SM64COOPDX_VERSION);
#else
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s %s", SM64COOPDX_VERSION, VERSION_REGION);
#endif
    return sVersionString;
}