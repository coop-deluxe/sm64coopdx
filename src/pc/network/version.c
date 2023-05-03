#include <stdio.h>
#include "version.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
static char sLocalVersionString[MAX_LOCAL_VERSION_LENGTH] = { 0 };

char* get_version(void) {
    if (MINOR_VERSION_NUMBER > 0) {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s %d.%d %s", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, VERSION_REGION);
    } else {
        snprintf(sVersionString, MAX_VERSION_LENGTH, "%s %d %s", VERSION_TEXT, VERSION_NUMBER, VERSION_REGION);
    }
    return sVersionString;
}

char* get_version_local(void) {
    if (PATCH_VERSION_NUMBER <= 0) {
        return get_version();
    }
    snprintf(sLocalVersionString, MAX_LOCAL_VERSION_LENGTH, "%s %d.%d.%d %s", VERSION_TEXT, VERSION_NUMBER, MINOR_VERSION_NUMBER, PATCH_VERSION_NUMBER, VERSION_REGION);
    return sLocalVersionString;
}
