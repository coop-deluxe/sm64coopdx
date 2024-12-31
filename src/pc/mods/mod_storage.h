#ifndef MOD_STORAGE_H
#define MOD_STORAGE_H

#include <PR/ultratypes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_KEYS 4096
#define MAX_KEY_VALUE_LENGTH 1024
#define SAVE_DIRECTORY "sav"
#define SAVE_EXTENSION ".sav"

/* |description|Saves a `key` corresponding to a string `value` to mod storage|descriptionEnd| */
bool mod_storage_save(const char* key, const char* value);
/* |description|Saves a `key` corresponding to a float `value` to mod storage|descriptionEnd| */
bool mod_storage_save_number(const char* key, f32 value);
/* |description|Saves a `key` corresponding to a bool `value` to mod storage|descriptionEnd| */
bool mod_storage_save_bool(const char* key, bool value);

/* |description|Loads a string `value` from a `key` in mod storage|descriptionEnd| */
const char *mod_storage_load(const char* key);
/* |description|Loads a float `value` from a `key` in mod storage|descriptionEnd| */
f32 mod_storage_load_number(const char* key);
/* |description|Loads a bool `value` from a `key` in mod storage|descriptionEnd| */
bool mod_storage_load_bool(const char* key);

/* |description|Checks if a `key` is in mod storage|descriptionEnd| */
bool mod_storage_exists(const char* key);
/* |description|Removes a `key` from mod storage|descriptionEnd| */
bool mod_storage_remove(const char* key);
/* |description|Clears the mod's data from mod storage|descriptionEnd| */
bool mod_storage_clear(void);

#ifdef __cplusplus
}
#endif

#endif // MOD_STORAGE_H
