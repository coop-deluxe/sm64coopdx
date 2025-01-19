#include <unistd.h>
#include "mods.h"
#include "mods_utils.h"
#include "mod_cache.h"
#include "data/dynos.c.h"
#include "pc/debuglog.h"
#include "pc/loading.h"
#include "pc/fs/fmem.h"
#include "pc/pc_main.h"
#include "pc/utils/misc.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

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

    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
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

u16 mods_get_enabled_count(void) {
    u16 enabled = 0;

    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
        if (!gLocalMods.entries[i]->enabled) { continue; }
        enabled++;
    }

    return enabled;
}

u16 mods_get_character_select_count(void) {
    u16 enabled = 0;

    for (u16 i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        if (mod->enabled && mod->category && strcmp(mod->category, "cs") == 0) {
            enabled++;
        }
    }

    return enabled;
}

bool mods_get_all_pausable(void) {
    bool pausable = true;

    for (u16 i = 0; i < gActiveMods.entryCount; i++) {
        if (!gActiveMods.entries[i]->pausable) {
            pausable = false;
            break;
        }
    }

    return pausable;
}

static void mods_local_store_enabled(void) {
    assert(sLocalEnabledPaths == NULL);
    struct LocalEnabledPath* prev = NULL;
    struct Mods* mods = &gLocalMods;

    for (u16 i = 0; i < mods->entryCount; i ++) {
        if (!mods->entries[i]->enabled) { continue; }

        struct LocalEnabledPath* n = calloc(1, sizeof(struct LocalEnabledPath));
        n->relativePath = sys_strdup(mods->entries[i]->relativePath);
        if (!prev) {
            sLocalEnabledPaths = n;
        } else {
            prev->next = n;
        }
        prev = n;
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
    if (!fs_sys_dir_exists(tmpPath)) {
        fs_sys_mkdir(tmpPath);
#if defined(_WIN32) || defined(_WIN64)
        SetFileAttributesA(tmpPath, FILE_ATTRIBUTE_HIDDEN);
#endif
    }

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
            char* name = str_remove_color_codes(mod->name);
            char* name2 = str_remove_color_codes(mod2->name);
            if (strcmp(name, name2) < 0) {
                mods->entries[i] = mod2;
                mods->entries[j] = mod;
                mod = mods->entries[i];
            }
            free(name);
            free(name2);
        }
    }
}

static u32 mods_count_directory(char* modsBasePath) {
    struct dirent* dir = NULL;
    DIR* d = opendir(modsBasePath);
    u32 pathCount = 0;
    while ((dir = readdir(d)) != NULL) pathCount++;
    closedir(d);
    return pathCount;
}

static void mods_load(struct Mods* mods, char* modsBasePath, UNUSED bool isUserModPath) {
    LOADING_SCREEN_MUTEX(snprintf(gCurrLoadingSegment.str, 256, "Generating DynOS Packs In %s Mod Path:\n\\#808080\\%s", isUserModPath ? "User" : "Local", modsBasePath));

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
    if (!fs_sys_dir_exists(modsBasePath)) {
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
    UNUSED f32 count = (f32) mods_count_directory(modsBasePath);

    LOADING_SCREEN_MUTEX(
        loading_screen_reset_progress_bar();
        snprintf(gCurrLoadingSegment.str, 256, "Loading Mods In %s Mod Path:\n\\#808080\\%s", isUserModPath ? "User" : "Local", modsBasePath);
    );

    // iterate
    char path[SYS_MAX_PATH] = { 0 };
    for (u32 i = 0; (dir = readdir(d)) != NULL; ++i) {

        // sanity check / fill path[]
        if (!directory_sanity_check(dir, modsBasePath, path)) { continue; }

        LOADING_SCREEN_MUTEX(snprintf(gCurrLoadingSegment.str, 256, "Loading Mod:\n\\#808080\\%s/%s", modsBasePath, dir->d_name));

        // load the mod
        if (!mod_load(mods, modsBasePath, dir->d_name)) {
            break;
        }

        LOADING_SCREEN_MUTEX(gCurrLoadingSegment.percentage = (f32) i / count);
    }

    closedir(d);
    LOADING_SCREEN_MUTEX(gCurrLoadingSegment.percentage = 1);
}

void mods_refresh_local(void) {
    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Refreshing Mod Cache"));
    if (gGameInited) { mods_local_store_enabled(); }

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
    if (hasUserPath) { mods_load(&gLocalMods, userModPath, true); }

    char defaultModsPath[SYS_MAX_PATH] = { 0 };
    snprintf(defaultModsPath, SYS_MAX_PATH, "%s/%s", sys_resource_path(), MOD_DIRECTORY);
    mods_load(&gLocalMods, defaultModsPath, false);

    // sort
    mods_sort(&gLocalMods);

    // calculate total size
    gLocalMods.size = 0;
    for (int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        gLocalMods.size += mod->size;
    }

    if (gGameInited) { mods_local_restore_enabled(); }
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
                    f_close(file->fp);
                    f_delete(file->fp);
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
    mods_clear(&gActiveMods);
    mods_clear(&gRemoteMods);
    mods_clear(&gLocalMods);
}
