#include <stdio.h>
#include "djui_unicode.h"
#include "pc/ini.h"
#include "pc/platform.h"

ini_t* sLang = NULL;

void djui_language_init(char* filename) {
    char path[SYS_MAX_PATH] = "";
    snprintf(path, SYS_MAX_PATH, "%s/lang/%s", sys_exe_path(), filename);
    sLang = ini_load(path);
}

char* djui_language_get(const char *section, const char *key) {
    if (!sLang) { return "???"; }
    char* value = (char*)ini_get(sLang, section, key);
    if (!value) { return "???"; }
    return value;
}