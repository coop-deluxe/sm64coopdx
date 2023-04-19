#include <stdio.h>
#include "version.h"
#include "version_text.h"
#include "types.h"

static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
static char sLocalVersionString[MAX_LOCAL_VERSION_LENGTH] = { 0 };

char* get_version(void) {
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s", VERSION_TEXT);
    return sVersionString;
}

char* get_version_local(void) {
    if (PATCH_VERSION_NUMBER <= 0) {
        return get_version();
    }
    snprintf(sLocalVersionString, MAX_LOCAL_VERSION_LENGTH, "%s.%d", VERSION_TEXT, PATCH_VERSION_NUMBER);
    return sLocalVersionString;
}
