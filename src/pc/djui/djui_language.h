#pragma once
#define DLANG(_SECTION, _KEY) djui_language_get(#_SECTION, #_KEY)

void djui_language_init(char* filename);
char* djui_language_get(const char *section, const char *key);
