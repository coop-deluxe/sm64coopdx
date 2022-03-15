#include <unistd.h>
#include "mods.h"
#include "mods_utils.h"
#include "pc/debuglog.h"

#define MOD_DIRECTORY "mods"

static struct Mods gLocalMods = { 0 };

void mods_clear(struct Mods* mods) {
    for (int i = 0; i < mods->modCount; i ++) {
        struct Mod* mod = &mods->entries[i];
        mod_clear(mod);
    }

    if (mods->entries != NULL) {
        free(mods->entries);
        mods->entries = NULL;
    }
    mods->modCount = 0;
}

static void mods_load(struct Mods* mods, char* modsBasePath) {
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
    mods_load(&gLocalMods, "./" MOD_DIRECTORY);
}

void mods_shutdown(void) {
    mods_clear(&gLocalMods);
}
