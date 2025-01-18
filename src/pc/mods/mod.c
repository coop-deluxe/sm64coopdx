#include "mod.h"
#include "mods.h"
#include "mods_utils.h"
#include "mod_cache.h"
#include "data/dynos.c.h"
#include "pc/utils/misc.h"
#include "pc/utils/md5.h"
#include "pc/debuglog.h"
#include "pc/fs/fmem.h"

size_t mod_get_lua_size(struct Mod* mod) {
    if (!mod) { return 0; }
    size_t size = 0;

    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        if (!(str_ends_with(file->relativePath, ".lua") || str_ends_with(file->relativePath, ".luac"))) { continue; }
        size += file->size;
    }

    return size;
}

static void mod_activate_bin(struct Mod* mod, struct ModFile* file) {
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
    dynos_add_actor_custom(mod->index, file->cachedPath, geoName);
}

static void mod_activate_col(struct ModFile* file) {
    // copy col name
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

static void mod_activate_tex(struct ModFile* file) {
    // copy tex name
    char texName[64] = { 0 };
    if (snprintf(texName, 63, "%s", path_basename(file->relativePath)) < 0) {
        LOG_ERROR("Truncated tex name");
        return;
    }

    // remove '.tex'
    char* g = texName;
    while (*g != '\0') {
        if (*g == '.') {
            *g = '\0';
            break;
        }
        g++;
    }

    // Add to custom actors
    LOG_INFO("Activating DynOS tex: '%s', '%s'", file->cachedPath, texName);
    dynos_add_texture(file->cachedPath, texName);
}

static void mod_activate_lvl(struct Mod* mod, struct ModFile* file) {
    // copy lvl name
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

static void mod_activate_bhv(struct Mod *mod, struct ModFile *file) {
    // copy bhv name
    char bhvName[64] = { 0 };
    if (snprintf(bhvName, 63, "%s", path_basename(file->relativePath)) < 0) {
        LOG_ERROR("Truncated bhv name");
        return;
    }

    // remove '.bhv'
    char *g = bhvName;
    while (*g != '\0') {
        if (*g == '.') {
            *g = '\0';
            break;
        }
        g++;
    }

    // Add to levels
    LOG_INFO("Activating DynOS bhv: '%s', '%s'", file->cachedPath, bhvName);
    dynos_add_behavior(mod->index, file->cachedPath, bhvName);
}

void mod_activate(struct Mod* mod) {
    // activate dynos models
    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        mod_cache_add(mod, file, false);

        // forcefully update md5 hash
        if (gNetworkType == NT_SERVER) {
            mod_cache_update(mod, file);
        }

        if (str_ends_with(file->relativePath, ".bin")) {
            mod_activate_bin(mod, file);
        }
        if (str_ends_with(file->relativePath, ".col")) {
            mod_activate_col(file);
        }
        if (str_ends_with(file->relativePath, ".lvl")) {
            mod_activate_lvl(mod, file);
        }
        if (str_ends_with(file->relativePath, ".bhv")) {
            mod_activate_bhv(mod, file);
        }
        if (str_ends_with(file->relativePath, ".tex")) {
            mod_activate_tex(file);
        }
    }
}

void mod_clear(struct Mod* mod) {
    if (!mod) { return; }

    if (mod->files) {
        for (int j = 0; j < mod->fileCount; j++) {
            struct ModFile* file = &mod->files[j];
            if (file->fp != NULL) {
                f_close(file->fp);
                f_delete(file->fp);
                file->fp = NULL;
            }
            if (file->cachedPath != NULL) {
                free((char*)file->cachedPath);
                file->cachedPath = NULL;
            }
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

    if (mod->category != NULL) {
        free(mod->category);
        mod->category = NULL;
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
    mod->fileCapacity = 0;
    mod->size = 0;
    free(mod);
}

static struct ModFile* mod_allocate_file(struct Mod* mod, char* relativePath) {
    // actual allocation
    if (mod->fileCount == mod->fileCapacity) {
        mod->fileCapacity = (mod->fileCapacity == 0) ? 16 : (mod->fileCapacity * 2);
        mod->files = realloc(mod->files, sizeof(struct ModFile) * mod->fileCapacity);
        if (mod->files == NULL) {
            LOG_ERROR("Failed to allocate file: '%s'", relativePath);
            return NULL;
        }
    }
    u16 fileIndex = mod->fileCount++;

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

static bool mod_load_files_dir(struct Mod* mod, char* fullPath, const char* subDir, const char** fileTypes) {

    // concat directory
    char dirPath[SYS_MAX_PATH] = { 0 };
    if (!concat_path(dirPath, fullPath, (char*)subDir)) {
        LOG_ERROR("Could not concat directory '%s' + '%s'", fullPath, subDir);
        return false;
    }

    // open subdirectory
    struct dirent* dir = NULL;
    DIR* d = opendir(dirPath);
    if (!d) { return true; }

    // iterate subdirectory
    char path[SYS_MAX_PATH] = { 0 };
    char relativePath[SYS_MAX_PATH] = { 0 };
    while ((dir = readdir(d)) != NULL) {
        // sanity check / fill path[]
        if (!directory_sanity_check(dir, dirPath, path)) { continue; }

        if (strlen(subDir) > 0) {
            if (snprintf(relativePath, SYS_MAX_PATH - 1, "%s/%s", subDir, dir->d_name) < 0) {
                LOG_ERROR("Could not concat %s path!", subDir);
                return false;
            }
        } else {
            if (snprintf(relativePath, SYS_MAX_PATH - 1, "%s", dir->d_name) < 0) {
                LOG_ERROR("Could not concat %s path!", subDir);
                return false;
            }
        }

        // only consider certain file types
        bool fileTypeMatch = false;
        const char** ft = fileTypes;
        while (*ft != NULL) {
            if (str_ends_with(path, (char*)*ft)) {
                fileTypeMatch = true;
            }
            ft++;
        }
        if (!fileTypeMatch) { continue; }

        // allocate file
        struct ModFile* file = mod_allocate_file(mod, relativePath);
        if (file == NULL) {
            return false;
        }
    }

    closedir(d);
    return true;
}

static bool mod_load_files(struct Mod* mod, char* modName, char* fullPath) {
    // read single lua file
    if (!mod->isDirectory) {
        return (mod_allocate_file(mod, modName) != NULL);
    }

    // deal with mod directory
    {
        const char* fileTypes[] = { ".lua", ".luac", NULL };
        if (!mod_load_files_dir(mod, fullPath, "", fileTypes)) { return false; }
    }

    // deal with actors directory
    {
        const char* fileTypes[] = { ".bin", ".col", NULL };
        if (!mod_load_files_dir(mod, fullPath, "actors", fileTypes)) { return false; }
    }

    // deal with behaviors directory
    {
        const char* fileTypes[] = { ".bhv", NULL };
        if (!mod_load_files_dir(mod, fullPath, "data", fileTypes)) { return false; }
    }

    // deal with textures directory
    {
        const char* fileTypes[] = { ".tex", NULL };
        if (!mod_load_files_dir(mod, fullPath, "textures", fileTypes)) { return false; }
    }

    // deal with levels directory
    {
        const char* fileTypes[] = { ".lvl", NULL };
        if (!mod_load_files_dir(mod, fullPath, "levels", fileTypes)) { return false; }
    }

    // deal with sound directory
    {
        const char* fileTypes[] = { ".m64", ".mp3", ".aiff", ".ogg", NULL };
        if (!mod_load_files_dir(mod, fullPath, "sound", fileTypes)) { return false; }
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
    mod->category = NULL;
    mod->description = NULL;
    mod->pausable = true;
    mod->ignoreScriptWarnings = false;

    // read line-by-line
    #define BUFFER_SIZE MAX(MAX(MOD_NAME_MAX_LENGTH, MOD_INCOMPATIBLE_MAX_LENGTH), MOD_DESCRIPTION_MAX_LENGTH)
    char buffer[BUFFER_SIZE] = { 0 };
    while (!feof(f)) {
        file_get_line(buffer, BUFFER_SIZE, f);

        // no longer in header
        if (buffer[0] != '-' || buffer[1] != '-') {
            fclose(f);
            return;
        }

        // extract the field
        char* extracted = NULL;
        if (mod->name == NULL && (extracted = extract_lua_field("-- name:", buffer))) {
            mod->name = calloc(MOD_NAME_MAX_LENGTH + 1, sizeof(char));
            if (snprintf(mod->name, MOD_NAME_MAX_LENGTH, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod name field '%s'", mod->name);
            }
        } else if (mod->incompatible == NULL && (extracted = extract_lua_field("-- incompatible:", buffer))) {
            mod->incompatible = calloc(MOD_INCOMPATIBLE_MAX_LENGTH + 1, sizeof(char));
            if (snprintf(mod->incompatible, MOD_INCOMPATIBLE_MAX_LENGTH, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod incompatible field '%s'", mod->incompatible);
            }
        } else if (mod->category == NULL && (extracted = extract_lua_field("-- category:", buffer))) {
            mod->category = calloc(MOD_CATEGORY_MAX_LENGTH + 1, sizeof(char));
            if (snprintf(mod->category, MOD_CATEGORY_MAX_LENGTH, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod category field '%s'", mod->category);
            }
        } else if (mod->description == NULL && (extracted = extract_lua_field("-- description:", buffer))) {
            mod->description = calloc(MOD_DESCRIPTION_MAX_LENGTH + 1, sizeof(char));
            if (snprintf(mod->description, MOD_DESCRIPTION_MAX_LENGTH, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod description field '%s'", mod->description);
            }
        } else if ((extracted = extract_lua_field("-- pausable:", buffer))) {
            mod->pausable = !strcmp(extracted, "true");
        } else if ((extracted = extract_lua_field("-- ignore-script-warnings:", buffer))) {
            mod->ignoreScriptWarnings = !strcmp(extracted, "true");
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

    bool isDirectory = fs_sys_dir_exists(fullPath);

    // make sure mod is valid
    if (str_ends_with(modName, ".lua")) {
        valid = true;
    } else if (fs_sys_dir_exists(fullPath)) {
        char tmpPath[SYS_MAX_PATH] = { 0 };
        if (!concat_path(tmpPath, fullPath, "main.lua")) {
            LOG_ERROR("Failed to concat path '%s' + '%s'", fullPath, "main.lua");
            return true;
        }
        valid = fs_sys_path_exists(tmpPath);
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

    // set category
    if (mod->category == NULL) {
        char *modNameNoColor = str_remove_color_codes(mod->name);
        if (strstr(modNameNoColor, "[CS]") == modNameNoColor) {
            mod->category = strdup("cs");
        }
        free(modNameNoColor);
    }

    // print
    // LOG_INFO("    %s", mod->name);
    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        mod_cache_add(mod, file, true);
        // LOG_INFO("      - %s", file->relativePath);
    }

    return true;
}
