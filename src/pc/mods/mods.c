#include <unistd.h>
#include "mods.h"
#include "mods_utils.h"
#include "data/dynos_coop.c.h"
#include "pc/debuglog.h"

#define MOD_DIRECTORY "mods"
#define MAX_SESSION_CHARS 7

struct Mods gLocalMods = { 0 };
struct Mods gRemoteMods = { 0 };
struct Mods gActiveMods = { 0 };

char gRemoteModsBasePath[SYS_MAX_PATH] = { 0 };

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

    // make directory
    if (!fs_sys_dir_exists(gRemoteModsBasePath)) { fs_sys_mkdir(gRemoteModsBasePath); }
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
    for (int i = 0; i < mods->entryCount; i++) {
        struct Mod* mod = mods->entries[i];
        if (mod->enabled) {
            gActiveMods.entries[gActiveMods.entryCount++] = mod;
            mod_activate(mod);
        }
    }

    // open file pointers
    if (mods != &gRemoteMods) {
        for (int i = 0; i < gActiveMods.entryCount; i++) {
            struct Mod* mod = gActiveMods.entries[i];
            for (int j = 0; j < mod->fileCount; j++) {
                struct ModFile* file = &mod->files[j];

                char fullPath[SYS_MAX_PATH] = { 0 };
                if (!mod_file_full_path(fullPath, mod, file)) {
                    LOG_ERROR("Failed to concat path: '%s' + '%s'", mod->basePath, file->relativePath);
                    continue;
                }

                file->fp = fopen(fullPath, "rb");
                if (file->fp == NULL) {
                    LOG_ERROR("Failed to open file '%s'", fullPath);
                    continue;
                }

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

void mods_init(void) {
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
    char defaultModsPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(defaultModsPath, SYS_MAX_PATH - 1, "%s", "./" MOD_DIRECTORY) >= 0) {
        mods_load(&gLocalMods, defaultModsPath);
    }

    // calculate total size
    gLocalMods.size = 0;
    for (int i = 0; i < gLocalMods.entryCount; i++) {
        struct Mod* mod = gLocalMods.entries[i];
        gLocalMods.size += mod->size;
    }
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
    mods_clear(&gRemoteMods);
    mods_clear(&gActiveMods);
    mods_clear(&gLocalMods);
    mods_delete_tmp();
}
