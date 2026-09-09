#include <sys/stat.h>
#include "mod.h"
#include "mods.h"
#include "mods_utils.h"
#include "mod_cache.h"
#include "data/dynos.c.h"
#include "pc/utils/misc.h"
#include "pc/utils/md5.h"
#include "pc/debuglog.h"
#include "pc/fs/fmem.h"
#include "pc/lua/smlua_cobject.h"
#include <stdint.h>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/stat.h>
#endif

const char *MOD_FILE_CACHEABLE_EXTENSIONS[] = {
    ".lua", ".luac",                    // script
    ".txt", ".json", ".ini", ".sav",    // text
    ".bin", ".col",                     // actors
    ".bhv",                             // behaviors
    ".tex",                             // textures
    ".lvl",                             // levels
    ".m64", ".aiff", ".mp3", ".ogg",    // audio
    NULL
};

size_t mod_get_lua_size(struct Mod* mod) {
    if (!mod) { return 0; }
    size_t size = 0;

    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        if (!(path_ends_with(file->relativePath, ".lua") || path_ends_with(file->relativePath, ".luac"))) { continue; }
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

    // get mod file index
    s32 fileIndex = (file - &mod->files[0]);
    if (fileIndex < 0 || fileIndex >= mod->fileCount) { fileIndex = 0; }

    // Add to custom actors
    LOG_INFO("Activating DynOS bin: '%s', '%s'", file->cachedPath, geoName);
    dynos_add_actor_custom(mod->index, fileIndex, file->cachedPath, geoName);
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
        file->modifiedTimestamp = fs_sys_get_modified_time(file->cachedPath);
        mod_cache_add(mod, file, false);

        // forcefully update md5 hash
        if (gNetworkType == NT_SERVER) {
            mod_cache_update(mod, file);
        }

        if (path_ends_with(file->relativePath, ".bin")) {
            mod_activate_bin(mod, file);
        }
        if (path_ends_with(file->relativePath, ".col")) {
            mod_activate_col(file);
        }
        if (path_ends_with(file->relativePath, ".lvl")) {
            mod_activate_lvl(mod, file);
        }
        if (path_ends_with(file->relativePath, ".bhv")) {
            mod_activate_bhv(mod, file);
        }
        if (path_ends_with(file->relativePath, ".tex")) {
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

    if (mod->customObjectFields != NULL) {
        growing_array_free(&mod->customObjectFields);
    }

    if (mod->filePatterns != NULL) {
        for (size_t i = 0; i < mod->filePatterns->count; i++) {
            free((char*)mod->filePatterns->patterns[i]);
        }
        free(mod->filePatterns);
        mod->filePatterns = NULL;
    }

    mod->fileCount = 0;
    mod->fileCapacity = 0;
    mod->size = 0;
    free(mod);
}


static struct ModFilePatterns *mod_parse_file_patterns(const char *input) {
    if (!input || !*input) { return NULL; }

    struct ModFilePatterns *fp = calloc(1, sizeof(struct ModFilePatterns));
    if (!fp) { return NULL; }

    // prepare buffer for tokenization
    char str[MOD_FILE_PATTERNS_SIZE] = { 0 };
    snprintf(str, sizeof(str), "%s", input);

    char *token = strtok(str, ",");
    bool blacklistToken = true;

    while (token != NULL) {
        // leading spaces
        while (isspace((u8)*token)) { token++; }

        // trailing spaces
        char *end = token + strlen(token);
        while (end > token && isspace((u8)*(end - 1))) {
            *--end = '\0';
        }

        if (*token != '\0') {
            if (blacklistToken) {
                fp->blacklist = (!strcmp(token, "true"));
                blacklistToken = false;
            } else if (fp->count < MOD_FILE_PATTERNS_MAX) {
                // allocate a copy for pattern
                size_t len = strlen(token) + 1;
                char *pattern = calloc(len, sizeof(char));
                if (pattern) {
                    memcpy(pattern, token, len);
                    fp->patterns[fp->count++] = pattern;
                }
            }
        }
        token = strtok(NULL, ",");
    }

    return fp;
}

static void mod_extract_fields(struct Mod* mod) {
    // initialize fields
    mod->name[0] = 0;
    mod->incompatible = NULL;
    mod->category = NULL;
    mod->description = NULL;
    mod->filePatterns = NULL;
    mod->pausable = true;
    mod->ignoreScriptWarnings = false;

    // resolve path
    char path[SYS_MAX_PATH] = { 0 };
    const char* targetFile = mod->isDirectory ? "main.lua" : mod->relativePath;

    if (!concat_path(path, mod->basePath, (char*)targetFile)) {
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

    // read line-by-line
    #define BUFFER_SIZE MAX(MAX(MOD_NAME_SIZE, MOD_INCOMPATIBLE_SIZE), MAX(MOD_FILE_PATTERNS_SIZE, MOD_DESCRIPTION_SIZE))
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
        if (!mod->name[0] && (extracted = extract_lua_field("-- name:", buffer))) {
            if (snprintf(mod->name, MOD_NAME_SIZE, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod name field '%s'", mod->name);
            }
        } else if (mod->incompatible == NULL && (extracted = extract_lua_field("-- incompatible:", buffer))) {
            mod->incompatible = calloc(MOD_INCOMPATIBLE_SIZE, sizeof(char));
            if (snprintf(mod->incompatible, MOD_INCOMPATIBLE_SIZE, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod incompatible field '%s'", mod->incompatible);
            }
        } else if (mod->category == NULL && (extracted = extract_lua_field("-- category:", buffer))) {
            mod->category = calloc(MOD_CATEGORY_SIZE, sizeof(char));
            if (snprintf(mod->category, MOD_CATEGORY_SIZE, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod category field '%s'", mod->category);
            }
        } else if (mod->description == NULL && (extracted = extract_lua_field("-- description:", buffer))) {
            mod->description = calloc(MOD_DESCRIPTION_SIZE, sizeof(char));
            if (snprintf(mod->description, MOD_DESCRIPTION_SIZE, "%s", extracted) < 0) {
                LOG_INFO("Truncated mod description field '%s'", mod->description);
            }
        } else if (mod->filePatterns == NULL && (extracted = extract_lua_field("-- unrestricted-extensions:", buffer))) {
            mod->filePatterns = mod_parse_file_patterns(extracted);
        } else if ((extracted = extract_lua_field("-- pausable:", buffer))) {
            mod->pausable = !strcmp(extracted, "true");
        } else if ((extracted = extract_lua_field("-- ignore-script-warnings:", buffer))) {
            mod->ignoreScriptWarnings = !strcmp(extracted, "true");
        }
    }

    fclose(f);
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
    char normPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(normPath, sizeof(normPath), "%s", relativePath) < 0) {
        LOG_ERROR("Failed to copy relative path for normalization: %s", relativePath);
    }

    normalize_path(normPath);

    if (snprintf(file->relativePath, SYS_MAX_PATH - 1, "%s", normPath) < 0) {
        LOG_ERROR("Failed to remember relative path '%s'", normPath);
        return NULL;
    }

    // figure out full path
    char fullPath[SYS_MAX_PATH] = { 0 };
    if (!mod_file_full_path(fullPath, mod, file)) {
        LOG_ERROR("Failed to concat path: '%s' + '%s'", mod->basePath, normPath);
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

bool mod_check_file_cacheable(const char *path) {
    if (!path) return false;
    char normPath[SYS_MAX_PATH] = { 0 };
    if (snprintf(normPath, sizeof(normPath), "%s", path) < 0) {
        LOG_ERROR("Failed to copy path for normalization: %s", path);
    }

    normalize_path(normPath);

    const char *lastSlash = strrchr(normPath, *PATH_SEPARATOR);
    const char *lastDot = strrchr(normPath, '.');
    if (lastDot != NULL && (lastSlash == NULL || lastDot > lastSlash)) {
        for (const char **ext = MOD_FILE_CACHEABLE_EXTENSIONS; *ext; ext++) {
            if (strcasecmp(lastDot, *ext) == 0) {
                return true;
            }
        }
    }
    return false;
}

static bool mod_matches_pattern(char *relativePath, char *pattern) {
    if (!relativePath || !pattern || !*pattern) { return false; }

    // check for pattern after the .
    if (pattern[0] == '.' && strchr(pattern, '*') == NULL && strchr(pattern, *PATH_SEPARATOR) == NULL) {
        return path_ends_with(relativePath, pattern);
    }

    // check for pattern after the *.
    if (pattern[0] == '*' && pattern[1] == '.' && strchr(pattern + 2, '*') == NULL && strchr(pattern + 2, *PATH_SEPARATOR) == NULL) {
        return path_ends_with(relativePath, pattern + 1);
    }

    // literal strings
    if (strchr(pattern, '*') == NULL && strchr(pattern, '?') == NULL) {
        if (str_ends_with(pattern, PATH_SEPARATOR)) {
            return str_starts_with(relativePath, pattern);
        }
        return path_ends_with_filepath(relativePath, pattern);
    }

    // complex wildcards
    char pathBuffer[SYS_MAX_PATH] = { 0 };
    snprintf(pathBuffer, sizeof(pathBuffer), "%s", pattern);

    // append "*" to match contents inside folder
    if (str_ends_with(pathBuffer, PATH_SEPARATOR)) {
        strncat(pathBuffer, "*", sizeof(pathBuffer) - strlen(pathBuffer) - 1);
    }

    // wildcard match for full relativePath
    if (wildcard_match(pathBuffer, relativePath)) {
        return true;
    }

    // match files in the root if **/file
    char patternBuffer[SYS_MAX_PATH] = { 0 };
    snprintf(patternBuffer, sizeof(patternBuffer), "**%s", PATH_SEPARATOR);
    if (str_starts_with(pathBuffer, patternBuffer)) {
        if (wildcard_match(pathBuffer + 3, relativePath)) { return true; }
    }

    // match file name only
    return wildcard_match(pathBuffer, path_basename(relativePath));
}

static bool mod_load_files_dir(struct Mod* mod, char* fullPath, const char* subDir, bool recursive) {

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
                closedir(d);
                return false;
            }
        } else {
            if (snprintf(relativePath, SYS_MAX_PATH - 1, "%s", dir->d_name) < 0) {
                LOG_ERROR("Could not concat %s path!", subDir);
                closedir(d);
                return false;
            }
        }

        normalize_path(relativePath);

        // Check if this is a directory
        struct stat st = { 0 };
        if (recursive && stat(path, &st) == 0 && S_ISDIR(st.st_mode)) {
            // Skip . and .. directories
            if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
                continue;
            }

            // Recursively process subdirectory
            if (!mod_load_files_dir(mod, fullPath, relativePath, recursive)) {
                closedir(d);
                return false;
            }
            continue;
        }

        // only consider certain file types
        bool blacklist = (mod->filePatterns != NULL && mod->filePatterns->blacklist);
        bool matched = false;
        if (mod->filePatterns != NULL) {
            for (size_t i = 0; i < mod->filePatterns->count; i++) {
                char pattern[SYS_MAX_PATH] = { 0 };
                if (snprintf(pattern, SYS_MAX_PATH - 1, "%s", mod->filePatterns->patterns[i]) < 0) {
                    LOG_ERROR("Could not concat %s pattern!", mod->filePatterns->patterns[i]);
                    closedir(d);
                    return false;
                }

                normalize_path(pattern);

                if (mod_matches_pattern(relativePath, pattern)) {
                    matched = true;
                    break;
                }
            }
        }

        bool allowedFile = false;
        if (blacklist) {
            // blacklist
            allowedFile = !matched;
        } else {
            // whitelist, cacheable extensions are networked regardless of matching
            allowedFile = matched || mod_check_file_cacheable(relativePath);
        }
        if (!allowedFile) { continue; }

        // allocate file
        struct ModFile* file = mod_allocate_file(mod, relativePath);
        if (file == NULL) {
            closedir(d);
            return false;
        }
    }

    closedir(d);
    return true;
}

static bool mod_load_files(struct Mod* mod, char* fullPath) {
    if (!mod->isDirectory) {
        // read single file mods
        return (mod_allocate_file(mod, mod->relativePath) != NULL);
    } else {
        // read folder mods
        return (mod_load_files_dir(mod, fullPath, "", true));
    }
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

bool mod_refresh_files(struct Mod* mod) {
    if (!mod) { return false; }

    // clear files
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

    if (mod->files != NULL) {
        free(mod->files);
        mod->files = NULL;
    }

    mod->fileCount = 0;
    mod->fileCapacity = 0;
    mod->size = 0;

    // generate packs
    dynos_generate_mod_pack(mod->basePath);

    // read files
    if (!mod_load_files(mod, mod->basePath)) {
        LOG_ERROR("Failed to load mod files for '%s'", mod->name);
        return false;
    }

    // set loading order
    mod_set_loading_order(mod);

    // update cache
    for (int i = 0; i < mod->fileCount; i++) {
        struct ModFile* file = &mod->files[i];
        mod_cache_add(mod, file, true);
    }

    return true;
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
    if (path_ends_with(modName, ".lua")) {
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

    // extract fields
    mod_extract_fields(mod);

    // read files
    if (!mod_load_files(mod, fullPath)) {
        LOG_ERROR("Failed to load mod files for '%s'", modName);
        return false;
    }

    // set loading order
    mod_set_loading_order(mod);

    // set name
    if (!mod->name[0]) {
        if (snprintf(mod->name, MOD_NAME_SIZE, "%s", modName) < 0) {
            LOG_INFO("Truncated mod name field '%s'", mod->name);
        }
    }

    // set category
    if (mod->category == NULL) {
        char modNameNoColor[MOD_NAME_SIZE];
        djui_text_get_uncolored_string(modNameNoColor, MOD_NAME_SIZE, mod->name);
        if (strstr(modNameNoColor, "[CS]") == modNameNoColor) {
            mod->category = strdup("cs");
        }
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
