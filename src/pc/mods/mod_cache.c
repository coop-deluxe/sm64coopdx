#include <stdio.h>
#include <unistd.h>
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"
#include "mod_cache.h"
#include "mods.h"
#include "mod.h"
#include "mods_utils.h"
#include "pc/utils/md5.h"

#define MOD_CACHE_FILENAME "mod.cache"
#define MOD_CACHE_VERSION 6
#define MD5_BUFFER_SIZE 1024

struct ModCacheEntry* sModCacheHead = NULL;

static void mod_cache_remove_node(struct ModCacheEntry* node, struct ModCacheEntry* parent) {
    if (node == NULL) { return; }
    if (node == sModCacheHead) { sModCacheHead = node->next; }
    if (parent != NULL) { parent->next = node->next; }
    //LOG_INFO("Removing node: %s", node->path);
    if (node->path) {
        free(node->path);
        node->path = NULL;
    }
    free(node);
}

void mod_cache_shutdown(void) {
    LOG_INFO("Shutting down mod cache.");
    while (sModCacheHead) {
        mod_cache_remove_node(sModCacheHead, NULL);
    }    
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
    struct ModCacheEntry* node = sModCacheHead;
    struct ModCacheEntry* prev = NULL;
    while (node != NULL) {
        struct ModCacheEntry* next = node->next;
        if (!memcmp(node->dataHash, dataHash, 16)) {
            if (mod_cache_is_valid(node)) {
                return node;
            } else {
                mod_cache_remove_node(node, prev);
            }
        }
        prev = node;
        node = next;
    }
    return NULL;
}

struct ModCacheEntry* mod_cache_get_from_path(const char* path, bool validate) {
    if (path == NULL || strlen(path) == 0) { return NULL; }
    struct ModCacheEntry* node = sModCacheHead;
    struct ModCacheEntry* prev = NULL;
    while (node != NULL) {
        struct ModCacheEntry* next = node->next;
        if (!strcmp(node->path, path)) {
            if (!validate) {
                return node;
            } else if (mod_cache_is_valid(node)) {
                return node;
            } else {
                mod_cache_remove_node(node, prev);
            }
        }
        prev = node;
        node = next;
    }
    return NULL;
}

void mod_cache_add_internal(u8* dataHash, u64 lastLoaded, const char* path) {
    // sanity check
    if (path == NULL || strlen(path) == 0) {
        LOG_ERROR("Invalid path");
        return;
    }
    if (!fs_sys_file_exists(path)) {
        LOG_ERROR("File does not exist: %s", path);
        return;
    }
    normalize_path((char*)path);

    bool foundNonZero = false;
    for (u8 i = 0; i < 16; i++) {
        if (dataHash[i] != 0) {
            foundNonZero = true;
            break;
        }
    }
    if (!foundNonZero) {
        LOG_ERROR("Hash was all zeros for path '%s'", path);
        return;
    }

    struct ModCacheEntry* node = calloc(1, sizeof(struct ModCacheEntry));
    memcpy(node->dataHash, dataHash, sizeof(u8) * 16);
    if (lastLoaded == 0) { lastLoaded = clock(); }
    node->lastLoaded = lastLoaded;
    node->path = (char*)path;
    node->next = NULL;

    if (sModCacheHead == NULL) {
        sModCacheHead = node;
        LOG_INFO("Added head: %s", node->path);
        return;
    }

    struct ModCacheEntry* n = sModCacheHead;
    struct ModCacheEntry* prev = NULL;
    while (n != NULL) {
        struct ModCacheEntry* next = n->next;

        // found end of list, add it
        if (next == NULL) {
            LOG_INFO("Added node: %s", node->path);
            if (n != node) { n->next = node; }
            return;
        }

        // found old hash, remove it
        if (!strcmp(n->path, path)) {
            LOG_INFO("Removing old node: %s", node->path);
            mod_cache_remove_node(n, prev);
        } else {
            prev = n;
        }

        n = next;
    }

    LOG_ERROR("Did not add node for some reason?");
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
        mod_cache_add_internal(file->dataHash, 0, strdup(file->cachedPath));
        return;
    }

    // hash and cache
    mod_cache_md5(file->cachedPath, file->dataHash);
    mod_cache_add_internal(file->dataHash, 0, strdup(file->cachedPath));
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
    mod_cache_add_internal(file->dataHash, 0, strdup(file->cachedPath));
}

void mod_cache_load(void) {
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

        const char* path = calloc(pathLen + 1, sizeof(u8));
        fread((char*)path, sizeof(u8), pathLen + 1, fp);

        mod_cache_add_internal(dataHash, lastLoaded, path);
        count++;
    }
    LOG_INFO("Loading mod cache complete");

    fclose(fp);
}

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

    struct ModCacheEntry* node = sModCacheHead;
    while (node != NULL) {
        struct ModCacheEntry* next = node->next;
        if (node->path == NULL) { goto iterate; }
        u16 pathLen = strlen(node->path);
        if (pathLen == 0) { goto iterate; }

        fwrite(node->dataHash, sizeof(u8), 16, fp);
        fwrite(&node->lastLoaded, sizeof(u64), 1, fp);
        fwrite(&pathLen, sizeof(u16), 1, fp);
        fwrite(node->path, sizeof(u8), pathLen + 1, fp);
iterate:
        node = next;
    }

    fclose(fp);
}
