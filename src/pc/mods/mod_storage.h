#ifndef MOD_STORAGE_H
#define MOD_STORAGE_H

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_KEYS 512
#define MAX_KEY_VALUE_LENGTH 256
#define SAVE_DIRECTORY "sav"
#define SAVE_EXTENSION ".sav"

bool mod_storage_save(const char* key, const char* value);
bool mod_storage_save_number(const char* key, double value);
bool mod_storage_save_bool(const char* key, bool value);

const char *mod_storage_load(const char* key);
double mod_storage_load_number(const char* key);
bool mod_storage_load_bool(const char* key);

bool mod_storage_remove(const char* key);
bool mod_storage_clear(void);

#ifdef __cplusplus
}
#endif

#endif // MOD_STORAGE_H
