#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };

const char* get_version(void) {
#if defined(VERSION_US)
    if (PATCH_VERSION_NUMBER > 0) {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d.%d.%d", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, PATCH_VERSION_NUMBER);
    } else {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d.%d", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER);
    }
#else
    if (PATCH_VERSION_NUMBER > 0) {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d.%d.%d %s", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, PATCH_VERSION_NUMBER, VERSION_REGION);
    } else {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d.%d %s", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, VERSION_REGION);
    }
#endif
    return sVersionString;
}
