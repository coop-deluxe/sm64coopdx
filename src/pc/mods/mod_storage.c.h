#ifndef MOD_STORAGE_C_H
#define MOD_STORAGE_C_H

bool mod_storage_save(const char *key, const char *value);
bool mod_storage_save_number(const char *key, double value);
bool mod_storage_save_bool(const char *key, bool value);

const char *mod_storage_load(const char *key);
double mod_storage_load_number(const char *key);
bool mod_storage_load_bool(const char *key);

bool mod_storage_clear(void);

#endif
