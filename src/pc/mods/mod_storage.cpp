#include "mod_storage.h"

#include <iostream>
#include <fstream>
#include <string>
#include "pc/mini.h"

extern "C" {
#include "pc/platform.h"
#include "pc/mods/mod.h"
#include "pc/lua/smlua.h"
#include "pc/mods/mods_utils.h"
#include "pc/fs/fs.h"
#include "pc/debuglog.h"
}

#define C_FIELD extern "C"

static void strdelete(char* string, const char* substr) {
    // i is used to loop through the string
    u16 i = 0;

    // store the lengths of the string and substr
    u16 string_length = strlen(string);
    u16 substr_length = strlen(substr);

    // loop through starting at the first index
    while (i < string_length) {
        // if we find the substr at the current index, delete it
        if (strstr(&string[i], substr) == &string[i]) {
            // determine the string's new length after removing the substr occurrence
            string_length -= substr_length;
            // shift forward the remaining characters in the string after the substr
            // occurrence by the length of substr, effectively removing it!
            for (u16 j = i; j < string_length; j++) {
                string[j] = string[j + substr_length];
            }
        } else {
            i++;
        }
    }

    string[i] = '\0';
}

bool char_valid(const char* buffer, bool isKey) {
    if (buffer[0] == '\0') { return false; }

    while (*buffer != '\0') {
        if (*buffer >= ' ' && !(isKey && (*buffer == '[' || *buffer == ']' || *buffer == '='))) {
            buffer++;
            continue;
        }
        return false;
    }

    return true;
}

void mod_storage_get_filename(char* dest) {
    const char* path = fs_get_write_path(SAVE_DIRECTORY); // get user path
    snprintf(dest, SYS_MAX_PATH - 1, "%s/%s", path, gLuaActiveMod->relativePath); // append sav folder
    strdelete(dest, ".lua"); // delete ".lua" from sav name
    strcat(dest, SAVE_EXTENSION); // append SAVE_EXTENSION
    normalize_path(dest); // fix any out of place slashes
}

C_FIELD bool mod_storage_save(const char* key, const char* value) {
    if (gLuaActiveMod == NULL) { return false; }
    if (strlen(key) > MAX_KEY_VALUE_LENGTH || strlen(value) > MAX_KEY_VALUE_LENGTH) { return false; }
    if (!char_valid(key, true) || !char_valid(value, false)) { return false; }

    char filename[SYS_MAX_PATH] = { 0 };
    mod_storage_get_filename(filename);

    // ensure savPath exists
    const char* savPath = fs_get_write_path(SAVE_DIRECTORY);
    if (!fs_sys_dir_exists(savPath)) { fs_sys_mkdir(savPath); }

    mINI::INIFile file(filename);
    mINI::INIStructure ini;
    file.read(ini);

    if (ini["storage"].size() > MAX_KEYS) { return false; }

    ini["storage"][key] = value;

    file.write(ini);
    file.generate(ini);

    return true;
}

C_FIELD bool mod_storage_save_number(const char* key, f32 value) {
    // Store string results in a temporary buffer
    // this assumes mod_storage_load will only ever be called by Lua
    static char str[MAX_KEY_VALUE_LENGTH];
    if (floor(value) == value) {
        snprintf(str, MAX_KEY_VALUE_LENGTH, "%lld", (s64)value);
    } else {
        snprintf(str, MAX_KEY_VALUE_LENGTH, "%f", value);
    }

    return mod_storage_save(key, str);
}

C_FIELD bool mod_storage_save_bool(const char* key, bool value) {
    return mod_storage_save(key, value ? "true" : "false");
}

C_FIELD const char* mod_storage_load(const char* key) {
    if (gLuaActiveMod == NULL) { return NULL; }
    if (strlen(key) > MAX_KEY_VALUE_LENGTH) { return NULL; }
    if (!char_valid(key, true)) { return NULL; }

    char filename[SYS_MAX_PATH] = { 0 };
    mod_storage_get_filename(filename);
    if (!fs_sys_path_exists(filename)) { return NULL; }

    mINI::INIFile file(filename);
    mINI::INIStructure ini;
    file.read(ini);

    std::string str = ini["storage"][key];
    if (str.empty()) { return NULL; }

    // Store string results in a temporary buffer
    // this assumes mod_storage_load will only ever be called by Lua
    static char value[MAX_KEY_VALUE_LENGTH];
    snprintf(value, MAX_KEY_VALUE_LENGTH, "%s", str.c_str());
    return value;
}

C_FIELD f32 mod_storage_load_number(const char* key) {
    const char* value = mod_storage_load(key);
    if (value == NULL) { return 0; }

    return std::strtof(value, nullptr);
}

C_FIELD bool mod_storage_load_bool(const char* key) {
    const char* value = mod_storage_load(key);
    if (value == NULL) { return false; }

    return !strcmp(value, "true");
}

C_FIELD bool mod_storage_exists(const char* key) {
    if (gLuaActiveMod == NULL) { return false; }
    if (strlen(key) > MAX_KEY_VALUE_LENGTH) { return false; }
    if (!char_valid(key, true)) { return false; }

    char filename[SYS_MAX_PATH] = { 0 };
    mod_storage_get_filename(filename);
    if (!fs_sys_path_exists(filename)) { return false; }

    mINI::INIFile file(filename);
    mINI::INIStructure ini;
    file.read(ini);

    return ini["storage"].has(key);
}

C_FIELD bool mod_storage_remove(const char* key) {
    if (gLuaActiveMod == NULL) { return false; }
    if (strlen(key) > MAX_KEY_VALUE_LENGTH) { return false; }
    if (!char_valid(key, true)) { return false; }

    char filename[SYS_MAX_PATH] = { 0 };
    mod_storage_get_filename(filename);
    if (!fs_sys_path_exists(filename)) { return false; }

    mINI::INIFile file(filename);
    mINI::INIStructure ini;
    file.read(ini);

    if (ini["storage"].remove(key)) {
        file.write(ini);
        file.generate(ini);
        return true;
    }

    return false;
}

C_FIELD bool mod_storage_clear(void) {
    if (gLuaActiveMod == NULL) { return false; }

    char filename[SYS_MAX_PATH] = { 0 };
    mod_storage_get_filename(filename);
    if (!fs_sys_path_exists(filename)) { return false; }

    mINI::INIFile file(filename);
    mINI::INIStructure ini;
    file.read(ini);

    if (ini["storage"].size() == 0) { return false; }

    ini["storage"].clear();

    file.write(ini);
    file.generate(ini);

    return true;
}
