#include <stdio.h>
#include "version.h"
#include "types.h"

static u16 sVersionInteger = 1;
static char sVersionString[MAX_VERSION_LENGTH] = { 0 };
#define VERSION_TEXT "beta "

char* get_version(void) {
    snprintf(sVersionString, MAX_VERSION_LENGTH, "%s%d", VERSION_TEXT, sVersionInteger);
    return sVersionString;
}