#include <unistd.h>
#include "mods.h"
#include "mods_utils.h"
#include "mod_cache.h"
#include "data/dynos.c.h"
#include "pc/debuglog.h"

#define MAX_SESSION_CHARS 7

struct Mods gLocalMods = { 0 };
struct Mods gRemoteMods = { 0 };
struct Mods gActiveMods = { 0 };

char gRemoteModsBasePath[SYS_MAX_PATH] = { 0 };

struct LocalEnabledPath {
    char* relativePath;
    struct LocalEnabledPath* next;
};

struct LocalEnabledPath* sLocalEnabledPaths = NULL;

void mods_get_main_mod_name(char* destination, u32 maxSize) {
    struct Mod* picked = NULL;
    size_t pickedSize = 0;

    for (unsigned int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        if (!mod->enabled) { continue; }
        size_t size = mod_get_lua_size(mod);
        if (size > pickedSize) {
            picked = mod;
            pickedSize = size;
        }
    }

    snprintf(destination, maxSize, "%s", picked ? picked->name : "Super Mario 64");
}

static void mods_local_store_enabled(void) {
    assert(sLocalEnabledPaths == NULL);
    struct LocalEnabledPath* prev = NULL;
    struct Mods* mods = &gLocalMods;

    for (int i = 0; i < mods->entryCount; i ++) {
        if (!mods->entries[i]->enabled) { continue; }

        struct LocalEnabledPath* n = calloc(1, sizeof(struct LocalEnabledPath));
        n->relativePath = sys_strdup(mods->entries[i]->relativePath);
        if (!prev) {
            sLocalEnabledPaths = n;
        } else {
            prev->next = n;
        }
    }
}

static void mods_local_restore_enabled(void) {
    struct LocalEnabledPath* n = sLocalEnabledPaths;
    while (n) {
        struct LocalEnabledPath* next = n->next;
        mods_enable(n->relativePath);
        free(n->relativePath);
        free(n);
        n = next;
    }
    sLocalEnabledPaths = NULL;
}

bool mods_generate_remote_base_path(void) {
    srand(time(0));

    // ensure tmpPath exists
    char tmpPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(tmpPath, SYS_MAX_PATH - 1, "%s", fs_get_write_path(TMP_DIRECTORY)) < 0) {
        LOG_ERROR("Failed to concat tmp path");
        return false;
    }
    if (!fs_sys_dir_exists(tmpPath)) { fs_sys_mkdir(tmpPath); }

    // generate session
    char session[MAX_SESSION_CHARS + 1] = { 0 };
    if (snprintf(session, MAX_SESSION_CHARS, "%06X", (u32)(rand() % 0xFFFFFF)) < 0) {
        LOG_ERROR("Failed to generate session");
        return false;
    }

    // combine
    if (!concat_path(gRemoteModsBasePath, tmpPath, session)) {
        LOG_ERROR("Failed to combine session path");
        return false;
    }

    return true;
}

void mods_activate(struct Mods* mods) {
    mods_clear(&gActiveMods);

    // count enabled
    u16 enabledCount = 0;
    for (int i = 0; i < mods->entryCount; i++) {
        struct Mod* mod = mods->entries[i];
        if (mod->enabled) { enabledCount++; }
    }

    // allocate
    gActiveMods.entries = calloc(enabledCount, sizeof(struct Mod*));
    if (gActiveMods.entries == NULL) {
        LOG_ERROR("Failed to allocate active mods table!");
        return;
    }

    // copy enabled entries
    gActiveMods.entryCount = 0;
    gActiveMods.size = 0;
    for (int i = 0; i < mods->entryCount; i++) {
        struct Mod* mod = mods->entries[i];
        if (mod->enabled) {
            mod->index = gActiveMods.entryCount;
            gActiveMods.entries[gActiveMods.entryCount++] = mod;
            gActiveMods.size += mod->size;
            mod_activate(mod);
        }
    }

    mod_cache_save();
}

static void mods_sort(struct Mods* mods) {
    if (mods->entryCount <= 1) {
        return;
    }

    // By default, this is the alphabetical order on name
    for (s32 i = 1; i < mods->entryCount; ++i) {
        struct Mod* mod = mods->entries[i];
        for (s32 j = 0; j < i; ++j) {
            struct Mod* mod2 = mods->entries[j];
            if (strcmp(mod->name, mod2->name) < 0) {
                mods->entries[i] = mod2;
                mods->entries[j] = mod;
                mod = mods->entries[i];
            }
        }
    }
}

static void mods_load(struct Mods* mods, char* modsBasePath) {
    // generate bins
    dynos_generate_packs(modsBasePath);

    // sanity check
    if (modsBasePath == NULL) {
        LOG_ERROR("Trying to load from NULL path!");
        return;
    }

    // make the path normal
    normalize_path(modsBasePath);

    // check for existence
    if (!is_directory(modsBasePath)) {
        LOG_ERROR("Could not find directory '%s'", modsBasePath);
    }

    LOG_INFO("Loading mods in '%s':", modsBasePath);

    // open directory
    struct dirent* dir = NULL;
    DIR* d = opendir(modsBasePath);
    if (!d) {
        LOG_ERROR("Could not open directory '%s'", modsBasePath);
        return;
    }

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, modsBasePath, path)) { continue; }

        // load the mod
        if (!mod_load(mods, modsBasePath, dir->d_name)) {
            break;
        }
    }

    closedir(d);

}

void mods_refresh_local(void) {
    mods_local_store_enabled();

    // figure out user path
    bool hasUserPath = true;
    char userModPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(userModPath, SYS_MAX_PATH - 1, "%s", fs_get_write_path(MOD_DIRECTORY)) < 0) {
        hasUserPath = false;
    }
    if (!fs_sys_dir_exists(userModPath)) {
        hasUserPath = fs_sys_mkdir(userModPath);
    }

    // clear mods
    mods_clear(&gLocalMods);

    // load mods
    if (hasUserPath) { mods_load(&gLocalMods, userModPath); }

    const char* exePath = path_to_executable();
    char defaultModsPath[SYS_MAX_PATH] = { 0 };
    path_get_folder((char*)exePath, defaultModsPath);
    strncat(defaultModsPath, MOD_DIRECTORY, SYS_MAX_PATH-1);
    mods_load(&gLocalMods, defaultModsPath);

    // sort
    mods_sort(&gLocalMods);

    // calculate total size
    gLocalMods.size = 0;
    for (int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        gLocalMods.size += mod->size;
    }

    mods_local_restore_enabled();
}

void mods_enable(char* relativePath) {
    if (!relativePath) { return; }

    for (unsigned int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        if (!strcmp(relativePath, mod->relativePath)) {
            mod->enabled = true;
            break;
        }
    }
}

void mods_init(void) {
    // load mod cache
    mod_cache_load();
    mods_refresh_local();
}

void mods_clear(struct Mods* mods) {
    if (mods == &gActiveMods) {
        // don't clear the mods of gActiveMods since they're a copy
        // just close all file pointers
        for (int i = 0; i < mods->entryCount; i ++) {
            struct Mod* mod = mods->entries[i];
            for (int j = 0; j < mod->fileCount; j++) {
                struct ModFile* file = &mod->files[j];
                if (file->fp != NULL) {
                    fclose(file->fp);
                    file->fp = NULL;
                }
            }
        }
    } else {
        // clear mods of gLocalMods and gRemoteMods
        for (int i = 0; i < mods->entryCount; i ++) {
            struct Mod* mod = mods->entries[i];
            mod_clear(mod);
            mods->entries[i] = NULL;
        }
    }

    // cleanup entries
    if (mods->entries != NULL) {
        free(mods->entries);
        mods->entries = NULL;
    }

    // cleanup params
    mods->entryCount = 0;
    mods->size = 0;
}

void mods_shutdown(void) {
    mod_cache_save();
    mod_cache_shutdown();
    mods_clear(&gRemoteMods);
    mods_clear(&gActiveMods);
    mods_clear(&gLocalMods);
}
