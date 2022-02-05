#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mod_list.h"
#include "pc/fs/fs.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"

#define MAX_SESSION_CHARS 7

struct ModTable gModTableLocal  = { .entries = NULL, .entryCount = 0, .totalSize = 0, .isRemote = false };
struct ModTable gModTableRemote = { .entries = NULL, .entryCount = 0, .totalSize = 0, .isRemote = true  };
struct ModTable* gModTableCurrent = &gModTableLocal;

static char sTmpSession[MAX_SESSION_CHARS] = { 0 };
static char sTmpPath[PATH_MAX] = { 0 };

static bool acceptable_file(char* string) {
    if (strchr(string, '/') != NULL)  { return false; }
    if (strchr(string, '\\') != NULL) { return false; }
    string = strrchr(string, '.');
    return (string != NULL && !strcmp(string, ".lua"));
}

static void mod_list_delete_tmp(void) {
    struct dirent* dir;
    DIR* d = opendir(sTmpPath);
    if (!d) { closedir(d); return; }

    static char path[PATH_MAX] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        snprintf(path, PATH_MAX - 1, "%s/%s", sTmpPath, dir->d_name);
        if (!fs_sys_file_exists(path)) { continue; }

#if defined(_WIN32)
        // replace slashes
        char* p = path;
        while (*p) {
            if (*p == '/') { *p = '\\'; }
            p++;
        }
#endif
        if (unlink(path) == -1) {
            LOG_ERROR("Failed to remove tmp file '%s'", path);
        }
    }

    closedir(d);
}

////////////////////////////////////////////////

static bool mod_list_contains(struct ModTable* table, char* name) {
    for (int i = 0; i < table->entryCount; i++) {
        struct ModListEntry* entry = &table->entries[i];
        if (entry->name == NULL) { continue; }
        if (!strcmp(entry->name, name)) { return true; }
    }
    return false;
}

void mod_list_add_tmp(u16 index, u16 remoteIndex, char* name, size_t size) {
    if (!acceptable_file(name)) { return; }

    struct ModTable* table = &gModTableRemote;
    if (mod_list_contains(table, name)) { return; }

    struct ModListEntry* entry = &table->entries[index];
    entry->name = name;
    entry->size = size;
    table->totalSize += size;

    char sanitizedName[PATH_MAX] = { 0 };
    char* n = name;
    char* s = sanitizedName;
    while (*n != '\0') {
        if (*n >= 'a' && *n <= 'z') { *s = *n; s++; }
        if (*n >= 'A' && *n <= 'Z') { *s = *n; s++; }
        if (*n >= '0' && *n <= '9') { *s = *n; s++; }
        if (*n == '_' || *n == '-' || *n == '.') { *s = *n; s++; }
        n++;
    }

    snprintf(entry->path, PATH_MAX - 1, "%s/%s-%u-%s", sTmpPath, sTmpSession, index, sanitizedName);
    entry->fp = fopen(entry->path, "wb");

    entry->remoteIndex = remoteIndex;
    entry->complete = false;
    entry->enabled = true;
    entry->selectable = false;
}

static char* extract_lua_field(char* fieldName, char* buffer) {
    size_t length = strlen(fieldName);
    if (strncmp(fieldName, buffer, length) == 0) {
        char* s = &buffer[length];
        while (*s == ' ' || *s == '\t') { s++; }
        return s;
    }
    return NULL;
}

void mod_list_extract_lua_fields(struct ModListEntry* entry) {
    FILE* f = entry->fp;
    char buffer[512] = { 0 };

    entry->displayName = NULL;
    entry->incompatible = NULL;
    entry->description = NULL;

    fseek(entry->fp, 0, SEEK_SET);

    while (!feof(f)) {
        file_get_line(buffer, 512, f);

        // no longer in header
        if (buffer[0] != '-' || buffer[1] != '-') {
            return;
        }

        // extract the field
        char* extracted = NULL;
        if (entry->displayName == NULL && (extracted = extract_lua_field("-- name:", buffer))) {
            entry->displayName = calloc(33, sizeof(char));
            snprintf(entry->displayName, 32, "%s", extracted);
        } else if (entry->incompatible == NULL && (extracted = extract_lua_field("-- incompatible:", buffer))) {
            entry->incompatible = calloc(257, sizeof(char));
            snprintf(entry->incompatible, 256, "%s", extracted);
        } else if (entry->description == NULL && (extracted = extract_lua_field("-- description:", buffer))) {
            entry->description = calloc(513, sizeof(char));
            snprintf(entry->description, 512, "%s", extracted);
        }
    }

}

static void mod_list_add_local(u16 index, const char* path, char* name) {
    if (!acceptable_file(name)) { return; }

    struct ModTable* table = &gModTableLocal;
    if (mod_list_contains(table, name)) { return; }

    struct ModListEntry* entry = &table->entries[index];
    entry->name = strdup(name);

    snprintf(entry->path, PATH_MAX - 1, "%s/%s", path, name);
    entry->fp = fopen(entry->path, "rb");

    mod_list_extract_lua_fields(entry);

    fseek(entry->fp, 0, SEEK_END);
    entry->size = ftell(entry->fp);
    table->totalSize += entry->size;
    fseek(entry->fp, 0, SEEK_SET);

    entry->remoteIndex = index;
    entry->complete = true;
    entry->enabled = false;
    entry->selectable = true;
}

void mod_table_clear(struct ModTable* table) {
    for (int i = 0; i < table->entryCount; i++) {
        struct ModListEntry* entry = &table->entries[i];
        if (entry->name != NULL) {
            free(entry->name);
            entry->name = NULL;
        }

        if (entry->displayName != NULL) {
            free(entry->displayName);
            entry->displayName = NULL;
        }

        if (entry->incompatible != NULL) {
            free(entry->incompatible);
            entry->incompatible = NULL;
        }

        if (entry->description != NULL) {
            free(entry->description);
            entry->description = NULL;
        }

        if (entry->fp != NULL) {
            fclose(entry->fp);
            entry->fp = NULL;
        }
        entry->size = 0;
    }

    if (table->entries != NULL) {
        free(table->entries);
        table->entries = NULL;
    }

    table->entryCount = 0;
    table->totalSize = 0;
}

void mod_list_alloc(struct ModTable* table, u16 count) {
    mod_table_clear(table);
    table->entryCount = count;
    table->entries = (struct ModListEntry*)calloc(count, sizeof(struct ModListEntry));
}

static bool mod_list_incompatible_match(struct ModListEntry* a, struct ModListEntry* b) {
    if (a->incompatible == NULL || b->incompatible == NULL) {
        return false;
    }
    if (strlen(a->incompatible) == 0 || strlen(b->incompatible) == 0) {
        return false;
    }

    char* ai = a->incompatible;
    char* bi = b->incompatible;
    char* atoken = NULL;
    char* btoken = NULL;
    char* arest = NULL;
    char* brest = NULL;

    for (atoken = strtok_r(ai, " ", &arest); atoken != NULL; atoken = strtok_r(NULL, " ", &arest)) {
        for (btoken = strtok_r(bi, " ", &brest); btoken != NULL; btoken = strtok_r(NULL, " ", &brest)) {
            if (!strcmp(atoken, btoken)) {
                return true;
            }
        }
    }

    return false;
}

void mod_list_update_selectable(void) {
    // reset selectable value
    for (int i = 0; i < gModTableLocal.entryCount; i++) {
        struct ModListEntry* entry = &gModTableLocal.entries[i];
        entry->selectable = true;
    }

    // figure out which ones to deselect
    for (int i = 0; i < gModTableLocal.entryCount; i++) {
        struct ModListEntry* entry = &gModTableLocal.entries[i];
        if (entry->enabled) { continue; }

        for (int j = 0; j < gModTableLocal.entryCount; j++) {
            if (j == i) { continue; }
            struct ModListEntry* entry2 = &gModTableLocal.entries[j];
            if (!entry2->enabled) { continue; }

            if (mod_list_incompatible_match(entry, entry2)) {
                entry->selectable = false;
                break;
            }
        }
    }
}

static void mod_list_load_local(const char* path) {
    if (!fs_sys_dir_exists(path)) { return; }
    struct ModTable* table = &gModTableLocal;

    struct dirent* dir;
    DIR* d = opendir(path);
    if (!d) { return; }

    u16 count = 0;
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
        if (mod_list_contains(table, dir->d_name)) { continue; }
        count++;
    }

    u16 totalCount = table->entryCount;
    u16 index = 0;
    if (table->entries == NULL) {
        if (count == 0) { closedir(d); return; }
        mod_list_alloc(table, count);
    } else {
        index = table->entryCount;
        totalCount += count;
        table->entries = (struct ModListEntry*)realloc(table->entries, totalCount * sizeof(struct ModListEntry));
    }

    rewinddir(d);

    LOG_INFO("Loading mods:");
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
        if (mod_list_contains(table, dir->d_name)) { continue; }
        LOG_INFO("    %s", dir->d_name);
        mod_list_add_local(index++, path, dir->d_name);
        if (index > table->entryCount) { table->entryCount = index; }
    }

    closedir(d);
}

void mod_list_init(void) {
    gModTableCurrent = &gModTableLocal;
    srand(time(0));
    snprintf(sTmpSession, MAX_SESSION_CHARS, "%06X", (u32)(rand() % 0xFFFFFF));
    snprintf(sTmpPath, PATH_MAX - 1, "%s", fs_get_write_path("tmp"));
    if (!fs_sys_dir_exists(sTmpPath)) { fs_sys_mkdir(sTmpPath); }

    char userModPath[PATH_MAX] = { 0 };
    snprintf(userModPath, PATH_MAX - 1, "%s", fs_get_write_path("mods"));
    if (!fs_sys_dir_exists(userModPath)) { fs_sys_mkdir(userModPath); }

    mod_table_clear(&gModTableLocal);
    mod_list_load_local(userModPath);
    mod_list_load_local(MOD_PATH);

    mod_list_update_selectable();
}

void mod_list_shutdown(void) {
    mod_table_clear(&gModTableLocal);
    mod_table_clear(&gModTableRemote);
    mod_list_delete_tmp();
}
