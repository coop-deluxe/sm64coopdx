#include "mod.h"
#include "mods.h"
#include "mods_utils.h"
#include "mod_cache.h"
#include "data/dynos.c.h"
#include "pc/utils/misc.h"
#include "pc/utils/md5.h"
#include "pc/debuglog.h"

static void mod_activate_bin(struct ModFile* file) {
    // copy geo name
    char geoName[64] = { 0 };
    if (snprintf(geoName, 63, "%s", path_basename(file->relativePath)) < 0) {
        LOG_ERROR("Truncated geo name");
        return;
    }

    // remove '.bin'
    char* g = geoName;
    while (*g != '\0') {
        if (*g == '.') {
            *g = '\0';
            break;
        }
        g++;
    }

    // Add to custom actors
    LOG_INFO("Activating DynOS bin: '%s', '%s'", file->cachedPath, geoName);
    dynos_add_actor_custom(file->cachedPath, geoName);
}

static void mod_activate_col(struct ModFile* file) {
    // copy geo name
    char colName[64] = { 0 };
    if (snprintf(colName, 63, "%s", path_basename(file->relativePath)) < 0) {
        LOG_ERROR("Truncated col name");
        return;
    }

    // remove '.col'
    char* g = colName;
    while (*g != '\0') {
        if (*g == '.') {
            *g = '\0';
            break;
        }
        g++;
    }

    // Add to custom actors
    LOG_INFO("Activating DynOS col: '%s', '%s'", file->cachedPath, colName);
    dynos_add_collision(file->cachedPath, colName);
}

static void mod_activate_lvl(struct Mod* mod, struct ModFile* file) {
    // copy geo name
    char lvlName[64] = { 0 };
    if (snprintf(lvlName, 63, "%s", path_basename(file->relativePath)) < 0) {
        LOG_ERROR("Truncated lvl name");
        return;
    }

    // remove '.lvl'
    char* g = lvlName;
    while (*g != '\0') {
        if (*g == '.') {
            *g = '\0';
            break;
        }
        g++;
    }

    // Add to levels
    LOG_INFO("Activating DynOS lvl: '%s', '%s'", file->cachedPath, lvlName);
    dynos_add_level(mod->index, file->cachedPath, lvlName);
}

void mod_activate(struct Mod* mod) {
    // activate dynos models
    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        mod_cache_add(mod, file);
        if (str_ends_with(file->relativePath, ".bin")) {
            mod_activate_bin(file);
        }
        if (str_ends_with(file->relativePath, ".col")) {
            mod_activate_col(file);
        }
        if (str_ends_with(file->relativePath, ".lvl")) {
            mod_activate_lvl(mod, file);
        }
    }
}

void mod_clear(struct Mod* mod) {
    for (int j = 0; j < mod->fileCount; j++) {
        struct ModFile* file = &mod->files[j];
        if (file->fp != NULL) {
            fclose(file->fp);
            file->fp = NULL;
        }
        if (file->cachedPath != NULL) {
            free((char*)file->cachedPath);
            file->cachedPath = NULL;
        }
    }

    if (mod->name != NULL) {
        free(mod->name);
        mod->name = NULL;
    }

    if (mod->incompatible != NULL) {
        free(mod->incompatible);
        mod->incompatible = NULL;
    }

    if (mod->description != NULL) {
        free(mod->description);
        mod->description = NULL;
    }

    if (mod->files != NULL) {
        free(mod->files);
        mod->files = NULL;
    }

    mod->fileCount = 0;
    mod->size = 0;
    free(mod);
}

static struct ModFile* mod_allocate_file(struct Mod* mod, char* relativePath) {
    // actual allocation
    u16 fileIndex = mod->fileCount++;
    mod->files = realloc(mod->files, sizeof(struct ModFile) * mod->fileCount);
    if (mod->files == NULL) {
        LOG_ERROR("Failed to allocate file: '%s'", relativePath);
        return NULL;
    }

    // clear memory
    struct ModFile* file = &mod->files[fileIndex];
    memset(file, 0, sizeof(struct ModFile));

    // set relative path
    if (snprintf(file->relativePath, SYS_MAX_PATH - 1, "%s", relativePath) < 0) {
        LOG_ERROR("Failed to remember relative path '%s'", relativePath);
        return NULL;
    }

    // figure out full path
    char fullPath[SYS_MAX_PATH] = { 0 };
    if (!mod_file_full_path(fullPath, mod, file)) {
        LOG_ERROR("Failed to concat path: '%s' + '%s'", mod->basePath, relativePath);
        return NULL;
    }

    // open file
    FILE* f = fopen(fullPath, "rb");
    if (f == NULL) {
        LOG_ERROR("Failed to open '%s'", fullPath);
        return NULL;
    }

    // get size
    fseek(f, 0, SEEK_END);
    file->size = ftell(f);
    mod->size += file->size;

    // close file
    fclose(f);

    return file;
}

static bool mod_load_files(struct Mod* mod, char* modName, char* fullPath) {
    // read single lua file
    if (!mod->isDirectory) {
        return (mod_allocate_file(mod, modName) != NULL);
    }

    // deal with mod directory
    {
        // open mod directory
        struct dirent* dir = NULL;
        DIR* d = opendir(fullPath);
        if (!d) {
            LOG_ERROR("Could not open directory '%s'", fullPath);
            return false;
        }

        // iterate mod directory
        char path[SYS_MAX_PATH] = { 0 };
        while ((dir = readdir(d)) != NULL) {
            // sanity check / fill path[]
            if (!directory_sanity_check(dir, fullPath, path)) { continue; }

            // only consider lua files
            if (!str_ends_with(path, ".lua")) {
                continue;
            }

            // allocate file
            struct ModFile* file = mod_allocate_file(mod, dir->d_name);
            if (file == NULL) { return false; }
        }

        closedir(d);
    }

    // deal with actors directory
    {
        // concat actors directory
        char actorsPath[SYS_MAX_PATH] = { 0 };
        if (!concat_path(actorsPath, fullPath, "actors")) {
            LOG_ERROR("Could not concat directory '%s' + '%s'", fullPath, "actors");
            return false;
        }

        // open actors directory
        struct dirent* dir = NULL;
        DIR* d = opendir(actorsPath);
        if (d) {
            // iterate mod directory
            char path[SYS_MAX_PATH] = { 0 };
            char relativePath[SYS_MAX_PATH] = { 0 };
            while ((dir = readdir(d)) != NULL) {
                // sanity check / fill path[]
                if (!directory_sanity_check(dir, actorsPath, path)) { continue; }
                if (snprintf(relativePath, SYS_MAX_PATH - 1, "actors/%s", dir->d_name) < 0) {
                    LOG_ERROR("Could not concat actor path!");
                    return false;
                }

                // only consider bin, and col files
                if (!str_ends_with(path, ".bin") && !str_ends_with(path, ".col")) {
                    continue;
                }

                // allocate file
                struct ModFile* file = mod_allocate_file(mod, relativePath);
                if (file == NULL) { return false; }
            }

            closedir(d);
        }
    }

    // deal with levels directory
    {
        // concat levels directory
        char levelsPath[SYS_MAX_PATH] = { 0 };
        if (!concat_path(levelsPath, fullPath, "levels")) {
            LOG_ERROR("Could not concat directory '%s' + '%s'", fullPath, "levels");
            return false;
        }

        // open levels directory
        struct dirent* dir = NULL;
        DIR* d = opendir(levelsPath);
        if (d) {
            // iterate mod directory
            char path[SYS_MAX_PATH] = { 0 };
            char relativePath[SYS_MAX_PATH] = { 0 };
            while ((dir = readdir(d)) != NULL) {
                // sanity check / fill path[]
                if (!directory_sanity_check(dir, levelsPath, path)) { continue; }
                if (snprintf(relativePath, SYS_MAX_PATH - 1, "levels/%s", dir->d_name) < 0) {
                    LOG_ERROR("Could not concat level path!");
                    return false;
                }

                // only consider lvl files
                if (!str_ends_with(path, ".lvl")) {
                    continue;
                }

                // allocate file
                struct ModFile* file = mod_allocate_file(mod, relativePath);
                if (file == NULL) { return false; }
            }

            closedir(d);
        }
    }

    // deal with sound directory
    {
        // concat sound directory
        char soundPath[SYS_MAX_PATH] = { 0 };
        if (!concat_path(soundPath, fullPath, "sound")) {
            LOG_ERROR("Could not concat directory '%s' + '%s'", fullPath, "sound");
            return false;
        }

        // open sound directory
        struct dirent* dir = NULL;
        DIR* d = opendir(soundPath);
        if (d) {
            // iterate mod directory
            char path[SYS_MAX_PATH] = { 0 };
            char relativePath[SYS_MAX_PATH] = { 0 };
            while ((dir = readdir(d)) != NULL) {
                // sanity check / fill path[]
                if (!directory_sanity_check(dir, soundPath, path)) { continue; }
                if (snprintf(relativePath, SYS_MAX_PATH - 1, "sound/%s", dir->d_name) < 0) {
                    LOG_ERROR("Could not concat sound path!");
                    return false;
                }

                // only consider m64 files
                if (!str_ends_with(path, ".m64")) {
                    continue;
                }

                // allocate file
                struct ModFile* file = mod_allocate_file(mod, relativePath);
                if (file == NULL) { return false; }
            }

            closedir(d);
        }
    }
    return true;
}

static void mod_set_loading_order(struct Mod* mod) {
    if (mod->fileCount <= 1) {
        return;
    }

    // TODO: add a way to specify the loading order of a mod's files?

    // By default, this is the alphabetical order on relative path
    for (s32 i = 1; i < mod->fileCount; ++i) {
        struct ModFile file = mod->files[i];
        for (s32 j = 0; j < i; ++j) {
            if (strcmp(file.relativePath, mod->files[j].relativePath) < 0) {
                memmove(mod->files + j + 1, mod->files + j, sizeof(struct ModFile) * (i - j));
                memcpy(mod->files + j, &file, sizeof(struct ModFile));
                break;
            }
        }
    }
}

static void mod_extract_fields(struct Mod* mod) {
    // get full path
    char path[SYS_MAX_PATH] = { 0 };
    char* relativePath = NULL;
    if (mod->isDirectory) {
        for (int i = 0; i < mod->fileCount; i++) {
            struct ModFile* file = &mod->files[i];
            if (!strcmp(file->relativePath, "main.lua")) {
                relativePath = file->relativePath;
            }
        }
    } else {
        relativePath = mod->files[0].relativePath;
    }

    if (relativePath == NULL || !concat_path(path, mod->basePath, relativePath)) {
        LOG_ERROR("Failed to find main lua file.");
        return;
    }

    // open file
    FILE* f = fopen(path, "rb");
    if (f == NULL) {
        LOG_ERROR("Failed to open '%s'", path);
        return;
    }
    fseek(f, 0, SEEK_SET);

    // default to null
    mod->name = NULL;
    mod->incompatible = NULL;
    mod->description = NULL;

    // read line-by-line
    char buffer[512] = { 0 };
    while (!feof(f)) {
        file_get_line(buffer, 512, f);

        // no longer in header
        if (buffer[0] != '-' || buffer[1] != '-') {
            return;
        }

        // extract the field
        char* extracted = NULL;
        if (mod->name == NULL && (extracted = extract_lua_field("-- name:", buffer))) {
            mod->name = calloc(33, sizeof(char));
            if (snprintf(mod->name, 32, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod name field '%s'", mod->name);
            }
        } else if (mod->incompatible == NULL && (extracted = extract_lua_field("-- incompatible:", buffer))) {
            mod->incompatible = calloc(257, sizeof(char));
            if (snprintf(mod->incompatible, 256, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod incompatible field '%s'", mod->incompatible);
            }
        } else if (mod->description == NULL && (extracted = extract_lua_field("-- description:", buffer))) {
            mod->description = calloc(513, sizeof(char));
            if (snprintf(mod->description, 512, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod description field '%s'", mod->description);
            }
        }
    }

    // close file
    fclose(f);
}

bool mod_load(struct Mods* mods, char* basePath, char* modName) {
    bool valid = false;

    char fullPath[SYS_MAX_PATH] = { 0 };
    if (!concat_path(fullPath, basePath, modName)) {
        LOG_ERROR("Failed to concat path '%s' + '%s'", basePath, modName);
        return true;
    }

    bool isDirectory = is_directory(fullPath);

    // make sure mod is valid
    if (str_ends_with(modName, ".lua")) {
        valid = true;
    } else if (is_directory(fullPath)) {
        char tmpPath[SYS_MAX_PATH] = { 0 };
        if (!concat_path(tmpPath, fullPath, "main.lua")) {
            LOG_ERROR("Failed to concat path '%s' + '%s'", fullPath, "main.lua");
            return true;
        }
        valid = path_exists(tmpPath);
    }

    if (!valid) {
        LOG_ERROR("Found invalid mod '%s'", fullPath);
        return true;
    }

    // make sure mod is unique
    for (int i = 0; i < mods->entryCount; i++) {
        struct Mod* compareMod = mods->entries[i];
        if (!strcmp(compareMod->relativePath, modName)) {
            return true;
        }
    }

    // allocate mod
    u16 modIndex = mods->entryCount++;
    mods->entries = realloc(mods->entries, sizeof(struct Mod*) * mods->entryCount);
    if (mods->entries == NULL) {
        LOG_ERROR("Failed to allocate entries!");
        mods_clear(mods);
        return false;
    }
    mods->entries[modIndex] = calloc(1, sizeof(struct Mod));
    struct Mod* mod = mods->entries[modIndex];
    if (mod == NULL) {
        LOG_ERROR("Failed to allocate mod!");
        mods_clear(mods);
        return false;
    }

    // set paths
    char* cpyPath = isDirectory ? fullPath : basePath;
    if (snprintf(mod->basePath, SYS_MAX_PATH - 1, "%s", cpyPath) < 0) {
        LOG_ERROR("Failed to remember mod path '%s'!", cpyPath);
        mods_clear(mods);
        return false;
    }
    if (snprintf(mod->relativePath, SYS_MAX_PATH - 1, "%s", modName) < 0) {
        LOG_ERROR("Failed to remember mod path '%s'!", modName);
        mods_clear(mods);
        return false;
    }

    // set directory
    mod->isDirectory = isDirectory;

    // read files
    if (!mod_load_files(mod, modName, fullPath)) {
        LOG_ERROR("Failed to load mod files for '%s'", modName);
        return false;
    }

    // set loading order
    mod_set_loading_order(mod);

    // extract fields
    mod_extract_fields(mod);

    // set name
    if (mod->name == NULL) {
        mod->name = strdup(modName);
    }

    // print
    LOG_INFO("    %s", mod->name);
    if (isDirectory) {
        for (int i = 0; i < mod->fileCount; i++) {
            struct ModFile* file = &mod->files[i];
            mod_cache_add(mod, file);
            LOG_INFO("      - %s", file->relativePath);
        }
    }

    return true;
}
