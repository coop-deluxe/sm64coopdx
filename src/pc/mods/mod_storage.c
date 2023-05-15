#include "mod_storage.h"

#include <stdio.h>
#include "pc/platform.h"
#include "pc/configini.h" // for writing
#include "pc/ini.h" // for parsing
#include "pc/lua/smlua.h"
#include "pc/mods/mods_utils.h"
#include "pc/debuglog.h"

void strdelete(char string[], char substr[]) {
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

bool char_valid(char* buffer) {
    if (buffer[0] == '\0') { return false; }
    while (*buffer != '\0') {
        if ((*buffer >= 'a' && *buffer <= 'z') || (*buffer >= 'A' && *buffer <= 'Z') || (*buffer >= '0' && *buffer <= '9') || *buffer == '_' || *buffer == '.' || *buffer == '-') {
            buffer++;
            continue;
        }
        return false;
    }
    return true;
}

u32 key_count(char* filename) {
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL) { return 0; }

    u32 lines = 1;
    char c;
    do {
        c = fgetc(file);
        if (c == '\n') { lines++; }
    } while (c != EOF);

    fclose(file);
    
    return lines - 4;
}

void mod_storage_get_filename(char* dest) {
    const char *path = sys_user_path(); // get base sm64ex-coop appdata dir
    snprintf(dest, SYS_MAX_PATH - 1, "%s/sav/%s", path, gLuaActiveMod->relativePath); // append sav folder
    strdelete(dest, ".lua"); // delete ".lua" from sav name
    strcat(dest, SAVE_EXTENSION); // append SAVE_EXTENSION
    normalize_path(dest); // fix any out of place slashes
}

bool mod_storage_save(const char *key, const char *value) {
    if (strlen(key) > MAX_KEY_VALUE_LENGTH || strlen(value) > MAX_KEY_VALUE_LENGTH) {
        LOG_LUA_LINE("Too long of a key and or value for mod_storage_save()");
        return false;
    }
    if (!char_valid((char *)key) || !char_valid((char *)value)) {
        LOG_LUA_LINE("Invalid key and or value passed to mod_storage_save()");
        return false;
    }

    FILE *file;
    Config *cfg = NULL;
    char *filename;
    filename = (char *)malloc((SYS_MAX_PATH - 1) * sizeof(char));
    mod_storage_get_filename(filename);

    // ensure savPath exists
    char savPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(savPath, SYS_MAX_PATH - 1, "%s", fs_get_write_path(SAVE_DIRECTORY)) < 0) {
        LOG_ERROR("Failed to concat sav path");
        free(filename);
        return false;
    }
    if (!fs_sys_dir_exists(savPath)) { fs_sys_mkdir(savPath); }

    bool exists = path_exists(filename);
    file = fopen(filename, exists ? "r+" : "w");
    cfg = ConfigNew();
    if (exists) {
        if (ConfigReadFile(filename, &cfg) != CONFIG_OK) {
            ConfigFree(cfg);
            fclose(file);
            free(filename);
            return false;
        }
        if (key_count(filename) > MAX_KEYS) {
            LOG_LUA_LINE("Tried to save more than MAX_KEYS with mod_storage_save()");
            ConfigFree(cfg);
            fclose(file);
            free(filename);
            return false;
        }
    }

    ConfigRemoveKey(cfg, "storage", key);
    ConfigAddString(cfg, "storage", key, value);

    ConfigPrint(cfg, file);
    ConfigFree(cfg);
    fclose(file);
    free(filename);

    return true;
}

const char *mod_storage_load(const char *key) {
    if (strlen(key) > MAX_KEY_VALUE_LENGTH) {
        LOG_LUA_LINE("Too long of a key for mod_storage_load()");
        return NULL;
    }
    if (!char_valid((char *)key)) {
        LOG_LUA_LINE("Invalid key passed to mod_storage_save()");
        return NULL;
    }

    char *filename;
    filename = (char *)malloc((SYS_MAX_PATH - 1) * sizeof(char));
    mod_storage_get_filename(filename);
    static char value[MAX_KEY_VALUE_LENGTH];
    ini_t *storage;

    if (!path_exists(filename)) {
        free(filename);
        return NULL;
    }

    storage = ini_load(filename);
    if (storage == NULL) {
        ini_free(storage);
        free(filename);
        return NULL;
    }
    snprintf(value, MAX_KEY_VALUE_LENGTH, "%s", ini_get(storage, "storage", key));

    ini_free(storage);
    free(filename);

    if (strstr(value, "(null)") != NULL) { return NULL; }

    return value;
}
