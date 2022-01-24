#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>
#include "mod_list.h"
#include "pc/fs/fs.h"
#include "pc/debuglog.h"

#define MAX_SESSION_CHARS 7

struct ModTable gModTableLocal  = { .entries = NULL, .entryCount = 0, .totalSize = 0, .isRemote = false };
struct ModTable gModTableRemote = { .entries = NULL, .entryCount = 0, .totalSize = 0, .isRemote = true  };

static char sTmpSession[MAX_SESSION_CHARS] = { 0 };
static char sTmpPath[PATH_MAX] = { 0 };

static bool acceptable_file(char* string) {
    string = strrchr(string, '.');
    return (string != NULL && !strcmp(string, ".lua"));
}


static void mod_list_delete_tmp(void) {
    struct dirent* dir;
    DIR* d = opendir(sTmpPath);
    if (!d) { closedir(d); return; }

    static char path[PATH_MAX] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
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

    snprintf(entry->path, PATH_MAX - 1, "%s/%s-%s", sTmpPath, sTmpSession, name);
    entry->fp = fopen(entry->path, "wb");

    entry->remoteIndex = remoteIndex;
    entry->complete = false;
    entry->enabled = true;

}

static void mod_list_add_local(u16 index, const char* path, char* name) {
    if (!acceptable_file(name)) { return; }

    struct ModTable* table = &gModTableLocal;
    if (mod_list_contains(table, name)) { return; }

    struct ModListEntry* entry = &table->entries[index];
    entry->name = strdup(name);

    snprintf(entry->path, PATH_MAX - 1, "%s/%s", path, name);
    entry->fp = fopen(entry->path, "rb");

    fseek(entry->fp, 0, SEEK_END);
    entry->size = ftell(entry->fp);
    table->totalSize += entry->size;
    fseek(entry->fp, 0, SEEK_SET);

    entry->complete = true;
    entry->enabled = false;
}

void mod_table_clear(struct ModTable* table) {
    for (int i = 0; i < table->entryCount; i++) {
        struct ModListEntry* entry = &table->entries[i];
        if (entry->name != NULL) {
            free(entry->name);
            entry->name = NULL;
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

    u16 index = 0;
    if (table->entries == NULL) {
        if (count == 0) { closedir(d); return; }
        mod_list_alloc(table, count);
    } else {
        index = table->entryCount;
        table->entryCount += count;
        table->entries = (struct ModListEntry*)realloc(table->entries, table->entryCount * sizeof(struct ModListEntry));
    }

    rewinddir(d);

    LOG_INFO("Loading mods:");
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
        if (mod_list_contains(table, dir->d_name)) { continue; }
        LOG_INFO("    %s", dir->d_name);
        mod_list_add_local(index++, path, dir->d_name);
    }

    closedir(d);
}

void mod_list_init(void) {
    snprintf(sTmpSession, MAX_SESSION_CHARS, "%06X", (u32)(rand() % 0xFFFFFF));
    snprintf(sTmpPath, PATH_MAX - 1, "%s", fs_get_write_path("tmp"));
    if (!fs_sys_dir_exists(sTmpPath)) { fs_sys_mkdir(sTmpPath); }

    char userModPath[PATH_MAX] = { 0 };
    snprintf(userModPath, PATH_MAX - 1, "%s", fs_get_write_path("mods"));
    if (!fs_sys_dir_exists(userModPath)) { fs_sys_mkdir(userModPath); }

    mod_table_clear(&gModTableLocal);
    mod_list_load_local(userModPath);
    mod_list_load_local(MOD_PATH);
}

void mod_list_shutdown(void) {
    mod_table_clear(&gModTableLocal);
    mod_table_clear(&gModTableRemote);
    mod_list_delete_tmp();
}
