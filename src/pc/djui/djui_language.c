#include <stdio.h>
#include "djui_unicode.h"
#include "pc/ini.h"
#include "pc/platform.h"
#include "pc/mods/mods.h"
#include "pc/mods/mods_utils.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_popup.h"

static ini_t* sLang = NULL;

bool djui_language_init(char* lang) {
    // free old ini
    if (sLang != NULL) {
        ini_free(sLang);
        sLang = NULL;
    }

    // construct path
    char path[SYS_MAX_PATH] = "";
    if (!lang || lang[0] == '\0') { lang = "English"; }
    snprintf(path, SYS_MAX_PATH, "%s/lang/%s.ini", sys_resource_path(), lang);

    // load
    sLang = ini_load(path);

    return sLang != NULL;
}

char* djui_language_get(const char *section, const char *key) {
    if (!sLang) { return (char*)key; }
    char* value = (char*)ini_get(sLang, section, key);
    if (!value) { return (char*)key; }
    return value;
}

char* djui_language_find_key(const char* section, const char* value) {
    if (!sLang) return NULL;
    return (char*)ini_find_key(sLang, section, value);
}

void djui_language_replace(char* src, char* dst, int size, char key, char* value) {
    char tmpChar[10] = { 0 };
    char* c = src;
    char* o = dst;
    while (*c != '\0') {
        if (*c == key) {
            snprintf(o, size - (o - dst), "%s", value);
        } else {
            djui_unicode_get_char(c, tmpChar);
            snprintf(o, size - (o - dst), "%s", tmpChar);
        }
        o = &dst[strlen(dst)];
        c = djui_unicode_next_char(c);
    }
}

void djui_language_replace2(char* src, char* dst, int size, char key1, char* value1, char key2, char* value2) {
    char tmpChar[10] = { 0 };
    char* c = src;
    char* o = dst;
    while (*c != '\0') {
        if (*c == key1) {
            snprintf(o, size - (o - dst), "%s", value1);
        } else if (*c == key2) {
            snprintf(o, size - (o - dst), "%s", value2);
        } else {
            djui_unicode_get_char(c, tmpChar);
            snprintf(o, size - (o - dst), "%s", tmpChar);
        }
        o = &dst[strlen(dst)];
        c = djui_unicode_next_char(c);
    }
}