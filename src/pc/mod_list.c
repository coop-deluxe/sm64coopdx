#include <dirent.h>
#include <stdlib.h>
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

void mod_list_add(u16 index, char* name, size_t size, bool tmpFile) {
    if (!acceptable_file(name)) { return; }
    struct ModTable* table = tmpFile ? &gModTableRemote : &gModTableLocal;

    struct ModListEntry* entry = &table->entries[index];
    entry->name = name;
    entry->size = size;
    table->totalSize += size;

    if (tmpFile) {
        snprintf(entry->path, PATH_MAX - 1, "%s/%s-%s", sTmpPath, sTmpSession, name);
    }
    else {
        snprintf(entry->path, PATH_MAX - 1, "%s/%s", MOD_PATH, name);
    }

    entry->fp = fopen(entry->path, tmpFile ? "wb" : "rb");

    if (!tmpFile) {
        fseek(entry->fp, 0, SEEK_END);
        entry->size = ftell(entry->fp);
        fseek(entry->fp, 0, SEEK_SET);
    }

    entry->complete = !tmpFile;
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

static void mod_list_load_local(void) {
    struct dirent* dir;
    DIR* d = opendir(MOD_PATH);
    if (!d) { closedir(d); return; }

    u16 count = 0;
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
        count++;
    }

    mod_list_alloc(&gModTableLocal, count);

    rewinddir(d);
    u16 index = 0;

    LOG_INFO("Loading mods:");
    while ((dir = readdir(d)) != NULL) {
        if (!acceptable_file(dir->d_name)) { continue; }
        LOG_INFO("    %s", dir->d_name);
        mod_list_add(index++, strdup(dir->d_name), 0, false);
    }

    closedir(d);
}

void mod_list_init(void) {
    snprintf(sTmpSession, MAX_SESSION_CHARS, "%06X", (u32)(rand() % 0xFFFFFF));
    snprintf(sTmpPath, PATH_MAX - 1, "%s", fs_get_write_path("tmp"));
    if (!fs_sys_dir_exists(sTmpPath)) { fs_sys_mkdir(sTmpPath); }
    mod_list_load_local();
}

void mod_list_shutdown(void) {
    mod_table_clear(&gModTableLocal);
    mod_table_clear(&gModTableRemote);
    mod_list_delete_tmp();
}
