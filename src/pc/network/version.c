#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
static char sLocalVersionString[MAX_VERSION_LENGTH] = { 0 };

char* get_version(void) {
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s %d.%d", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER);
    return sVersionString;
}

char* get_version_local(void) {
    snprintf(sLocalVersionString, MAX_LOCAL_VERSION_LENGTH, "%s %d.%d.%d", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, PATCH_VERSION_NUMBER);
    return sLocalVersionString;
}
