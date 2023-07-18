#ifndef MOD_STORAGE_C_H
#define MOD_STORAGE_C_H
#ifdef __cplusplus

#define MAX_KEYS 512
#define MAX_KEY_VALUE_LENGTH 64
#define SAVE_DIRECTORY "sav"
#define SAVE_EXTENSION ".sav"

bool Mod_Storage_Save(const char *key, const char *value);
bool Mod_Storage_Save_Number(const char* key, double value);
bool Mod_Storage_Save_Bool(const char* key, bool value);

const char *Mod_Storage_Load(const char *key);
double Mod_Storage_Load_Number(const char *key);
bool Mod_Storage_Load_Bool(const char *key);

bool Mod_Storage_Clear(void);

#endif
#endif