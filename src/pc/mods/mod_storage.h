#ifndef MOD_STORAGE_H
#define MOD_STORAGE_H

#include "mod.h"

#define MAX_KEYS 255
#define MAX_KEY_VALUE_LENGTH 64
#define SAVE_DIRECTORY "sav"
#define SAVE_EXTENSION ".sav"

bool mod_storage_save(const char *key, const char *value);
const char *mod_storage_load(const char *key);

#endif
