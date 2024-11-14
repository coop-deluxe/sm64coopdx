#include <stdio.h>
#include <unistd.h>
#define DISABLE_MODULE_LOG 1
#include "pc/gfx/gfx_pc.h"
#include "pc/debuglog.h"
#include "mod_cache.h"
#include "mods.h"
#include "mod.h"
#include "mods_utils.h"
#include "pc/utils/md5.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/loading.h"

#define MOD_CACHE_FILENAME "mod.cache"
#define MOD_CACHE_VERSION 7
#define MD5_BUFFER_SIZE 1024

static struct ModCacheEntry* sModCacheEntries = NULL;
static size_t sModCacheLength = 0;
static size_t sModLengthCapacity = 0;

static void mod_cache_remove_node(struct ModCacheEntry* node) {
    if (node->path) {
        free(node->path);
        node->path = NULL;
    }
    if (node != &sModCacheEntries[sModCacheLength - 1])
        memcpy(node, &sModCacheEntries[sModCacheLength - 1], sizeof(struct ModCacheEntry));
    sModCacheLength--;
}

void mod_cache_shutdown(void) {
    LOG_INFO("Shutting down mod cache.");
    sModCacheLength = 0;
    sModLengthCapacity = 0;
    free(sModCacheEntries);
    sModCacheEntries = NULL;
}

void mod_cache_md5(const char* inPath, u8* outDataPath) {
    char cpath[SYS_MAX_PATH] = { 0 };
    u8 buffer[MD5_BUFFER_SIZE] = { 0 };

    for (u8 i = 0; i < 16; i++) {
        outDataPath[i] = 0;
    }

    MD5_CTX ctx = { 0 };
    MD5_Init(&ctx);

    snprintf(cpath, SYS_MAX_PATH-1, "%s", inPath);

    if (strlen(cpath) == 0) {
        LOG_ERROR("Failed to retrieve path");
        return;
    }

    normalize_path(cpath);

    // open file pointer
    FILE* fp = fopen(cpath, "rb");
    if (fp == NULL) {
        LOG_ERROR("Failed to open filepointer for mod hashing: '%s'.", cpath);
        return;
    }

    // read bytes and md5 them
    size_t readBytes = 0;
    do {
        readBytes = fread(buffer, sizeof(u8), MD5_BUFFER_SIZE, fp);
        MD5_Update(&ctx, buffer, readBytes);
    } while (readBytes >= MD5_BUFFER_SIZE);

    // close file pointer
    fclose(fp);

    // finish computing
    MD5_Final(outDataPath, &ctx);
}

static u64 mod_cache_fnv1a(const char* str) {
    u64 hash = 0xCBF29CE484222325;
    while (*str) {
        hash *= 0x100000001B3;
        hash ^= *str++;
    }
    return hash;
}

static bool mod_cache_is_valid(struct ModCacheEntry* node) {
    if (node == NULL || node->path == NULL || strlen(node->path) == 0) {
        return false;
    }
    u8 dataHash[16] = { 0 };
    mod_cache_md5(node->path, dataHash);
    return !memcmp(node->dataHash, dataHash, 16);
}

struct ModCacheEntry* mod_cache_get_from_hash(u8* dataHash) {
    if (dataHash == NULL) { return NULL; }
    for (size_t i = 0; i < sModCacheLength;) {
        struct ModCacheEntry* node = &sModCacheEntries[i];
        if (!memcmp(node->dataHash, dataHash, 16)) {
            if (mod_cache_is_valid(node)) {
                return node;
            } else {
                mod_cache_remove_node(node);
                continue;
            }
        }
        i++;
    }
    return NULL;
}

struct ModCacheEntry* mod_cache_get_from_path(const char* path, bool validate) {
    if (path == NULL || strlen(path) == 0) { return NULL; }
    u64 pathHash = mod_cache_fnv1a(path);
    for (size_t i = 0; i < sModCacheLength;) {
        struct ModCacheEntry* node = &sModCacheEntries[i];
        if (node->pathHash == pathHash && !strcmp(node->path, path)) {
            if (!validate) {
                return node;
            } else if (mod_cache_is_valid(node)) {
                return node;
            } else {
                mod_cache_remove_node(node);
                continue;
            }
        }
        i++;
    }
    return NULL;
}

void mod_cache_add_internal(u8* dataHash, u64 lastLoaded, char* inPath) {
    char* path = strdup(inPath);

    // sanity check
    if (path == NULL || strlen(path) == 0) {
        LOG_ERROR("Invalid path");
        free(path);
        return;
    }
    if (!fs_sys_file_exists(path)) {
        LOG_ERROR("File does not exist: %s", path);
        free(path);
        return;
    }
    normalize_path((char*)path);
    u64 pathHash = mod_cache_fnv1a(path);

    bool foundNonZero = false;
    for (u8 i = 0; i < 16; i++) {
        if (dataHash[i] != 0) {
            foundNonZero = true;
            break;
        }
    }
    if (!foundNonZero) {
        LOG_ERROR("Hash was all zeros for path '%s'", path);
        free(path);
        return;
    }

    if (sModCacheEntries == NULL) {
        sModLengthCapacity = 16;
        sModCacheLength = 0;
        sModCacheEntries = calloc(sModLengthCapacity, sizeof(struct ModCacheEntry));
    } else if (sModCacheLength == sModLengthCapacity) {
        sModLengthCapacity *= 2;
        sModCacheEntries = realloc(sModCacheEntries, sizeof(struct ModCacheEntry) * sModLengthCapacity);
    }

    struct ModCacheEntry node = {};
    memcpy(node.dataHash, dataHash, sizeof(u8) * 16);
    if (lastLoaded == 0) { lastLoaded = clock(); }
    node.lastLoaded = lastLoaded;
    node.path = (char*)path;
    node.pathHash = pathHash;

    for (size_t i = 0; i < sModCacheLength;) {
        struct ModCacheEntry* n = &sModCacheEntries[i];

        // found old hash, remove it
        if (n->pathHash == pathHash && !strcmp(n->path, path)) {
            LOG_INFO("Removing old node: %s", node->path);
            mod_cache_remove_node(n);
        } else {
            i++;
        }
    }
    memcpy(&sModCacheEntries[sModCacheLength++], &node, sizeof(node));
}

void mod_cache_add(struct Mod* mod, struct ModFile* file, bool useFilePath) {
    // sanity check
    if (mod == NULL || file == NULL) {
        LOG_ERROR("Could not add to cache, mod or file is null");
        return;
    }

    // if we already have a cached path, don't do anything
    if (file->cachedPath != NULL) {
        return;
    }

    // build the path
    char modFilePath[SYS_MAX_PATH] = { 0 };
    if (!concat_path(modFilePath, mod->basePath, file->relativePath)) {
        LOG_ERROR("Could not concat mod file path");
        return;
    }

    // set path
    normalize_path(modFilePath);
    file->cachedPath = strdup(modFilePath);

    // if we already have the filepath, don't MD5 it again
    struct ModCacheEntry* entry = mod_cache_get_from_path(file->cachedPath, false);
    if (useFilePath && entry) {
        memcpy(file->dataHash, entry->dataHash, 16);
        mod_cache_add_internal(file->dataHash, 0, (char*)file->cachedPath);
        return;
    }

    // hash and cache
    mod_cache_md5(file->cachedPath, file->dataHash);
    mod_cache_add_internal(file->dataHash, 0, (char*)file->cachedPath);
}

void mod_cache_update(struct Mod* mod, struct ModFile* file) {
    // sanity check
    if (mod == NULL || file == NULL) {
        LOG_ERROR("Could not add to cache, mod or file is null");
        return;
    }

    // build the path
    char modFilePath[SYS_MAX_PATH] = { 0 };
    if (!concat_path(modFilePath, mod->basePath, file->relativePath)) {
        LOG_ERROR("Could not concat mod file path");
        return;
    }

    // set path
    normalize_path(modFilePath);
    file->cachedPath = strdup(modFilePath);

    // hash and cache
    mod_cache_md5(file->cachedPath, file->dataHash);
    mod_cache_add_internal(file->dataHash, 0, (char*)file->cachedPath);
}

void mod_cache_load(void) {
    LOADING_SCREEN_MUTEX(loading_screen_set_segment_text("Loading Mod Cache"));

    mod_cache_shutdown();
    LOG_INFO("Loading mod cache");

    const char* filename = fs_get_write_path(MOD_CACHE_FILENAME);
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        LOG_INFO("Could not open mod cache load fp: %s", filename);
        return;
    }

    u16 version;
    fread(&version, sizeof(u16), 1, fp);
    if (version != MOD_CACHE_VERSION) {
        fclose(fp);
        LOG_INFO("Mod cache version mismatch");
        mods_delete_tmp();
        return;
    }
    u8 marked = 0;
    fread(&marked, sizeof(u8), 1, fp);
    if (marked != 0) {
        gfx_shutdown();
    }

    u16 count = 0;
    while (true) {
        u8 dataHash[16] = { 0 };
        u64 lastLoaded = 0;
        u16 pathLen;

        if (fread(dataHash, sizeof(u8), 16, fp) == 0) {
            break;
        }

        fread(&lastLoaded, sizeof(u64), 1, fp);
        fread(&pathLen, sizeof(u16), 1, fp);

        char* path = calloc(pathLen + 1, sizeof(char));
        fread((char*)path, sizeof(char), pathLen + 1, fp);

        mod_cache_add_internal(dataHash, lastLoaded, (char*)path);

        free((void*)path);
        count++;
    }
    LOG_INFO("Loading mod cache complete");

    fclose(fp);
}

extern u64* gBehaviorOffset;
void mod_cache_save(void) {
    LOG_INFO("Saving mod cache");
    const char* filename = fs_get_write_path(MOD_CACHE_FILENAME);

    if (filename == NULL || strlen(filename) == 0) {
        LOG_ERROR("Failed to get filename for mod cache");
        return;
    }

    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        LOG_ERROR("Failed to open mod cache save fp: %s", filename);
        return;
    }

    u16 version = MOD_CACHE_VERSION;
    fwrite(&version, sizeof(u16), 1, fp);
    u8 t = *gBehaviorOffset != 0;
    fwrite(&t, sizeof(u8), 1, fp);

    for (size_t i = 0; i < sModCacheLength; i++) {
        struct ModCacheEntry* node = &sModCacheEntries[i];
        if (node->path == NULL) { continue; }
        u16 pathLen = strlen(node->path);
        if (pathLen == 0) { continue; }

        fwrite(node->dataHash, sizeof(u8), 16, fp);
        fwrite(&node->lastLoaded, sizeof(u64), 1, fp);
        fwrite(&pathLen, sizeof(u16), 1, fp);
        fwrite(node->path, sizeof(u8), pathLen + 1, fp);
    }

    fclose(fp);
}
