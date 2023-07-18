#include "mod_storage.cpp.h"
extern "C" {

bool mod_storage_save(const char *key, const char *value) {
    return Mod_Storage_Save(key, value);
}

bool mod_storage_save_number(const char *key, double value) {
    return Mod_Storage_Save_Number(key, value);
}

bool mod_storage_save_bool(const char *key, bool value) {
    return Mod_Storage_Save_Bool(key, value);
}


const char *mod_storage_load(const char *key) {
    return Mod_Storage_Load(key);
}

double mod_storage_load_number(const char *key) {
    return Mod_Storage_Load_Number(key);
}

bool mod_storage_load_bool(const char *key) {
    return Mod_Storage_Load_Bool(key);
}


bool mod_storage_clear(void) {
    return Mod_Storage_Clear();
}

}