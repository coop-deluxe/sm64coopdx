#pragma once
#define DLANG(_SECTION, _KEY) djui_language_get(#_SECTION, #_KEY)

bool djui_language_init(char* lang);
char* djui_language_get(const char *section, const char *key);
void djui_language_replace(char* src, char* dst, int size, char key, char* value);
void djui_language_replace2(char* src, char* dst, int size, char key1, char* value1, char key2, char* value2);
