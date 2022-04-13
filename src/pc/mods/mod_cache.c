#include <stdio.h>
#include "mod_cache.h"
#include "mods.h"
#include "mod.h"
#include "pc/debuglog.h"

#define MOD_CACHE_FILENAME "mod.cache"
#define MOD_CACHE_VERSION 1

struct ModCacheEntry* sModCacheHead = NULL;

static void mod_cache_remove_node(struct ModCacheEntry* node, struct ModCacheEntry* parent) {
    if (node == NULL) { return; }
    if (node == sModCacheHead) { sModCacheHead = node->next; }
    if (parent != NULL) { parent->next = node->next; }
    LOG_INFO("Removing node: %s", node->path);
    if (node->path) {
        free(node->path);
    }
    free(node);
}

void mod_cache_shutdown(void) {
    LOG_INFO("Shutting down mod cache.");
    while (sModCacheHead) {
        mod_cache_remove_node(sModCacheHead, NULL);
    }    
}

struct ModCacheEntry* mod_cache_get_from_hash(u8* dataHash) {
    struct ModCacheEntry* node = sModCacheHead;
    while (node != NULL) {
        if (!memcmp(node->dataHash, dataHash, 16)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

struct ModCacheEntry* mod_cache_get_from_path(const char* path) {
    struct ModCacheEntry* node = sModCacheHead;
    while (node != NULL) {
        if (!strcmp(node->path, path)) {
            return node;
        }
        node = node->next;
    }
    return NULL;
}

void mod_cache_add(u8* dataHash, const char* path) {
    if (mod_cache_get_from_hash(dataHash)) {
        return;
    }

    struct ModCacheEntry* node = calloc(1, sizeof(struct ModCacheEntry));
    memcpy(node->dataHash, dataHash, 16);
    node->path = (char*)path;
    node->next = NULL;

    if (sModCacheHead == NULL) {
        sModCacheHead = node;
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
        }

        prev = n;
        n = next;
    }
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
        return;
    }

    while (true) {
        u8 dataHash[16] = { 0 };
        u16 pathLen;

        if (fread(dataHash, sizeof(u8), 16, fp) == 0) {
            break;
        }
        fread(&pathLen, sizeof(u16), 1, fp);

        const char* path = calloc(pathLen + 1, sizeof(u8));
        fread((char*)path, sizeof(u8), pathLen + 1, fp);

        mod_cache_add(dataHash, path);
    }
    LOG_INFO("Loading mod cache complete");

    fclose(fp);
}

void mod_cache_save(void) {
    LOG_INFO("Saving mod cache");
    const char* filename = fs_get_write_path(MOD_CACHE_FILENAME);
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL) {
        LOG_ERROR("Failed to open mod cache save fp: %s", filename);
    }

    u16 version = MOD_CACHE_VERSION;
    fwrite(&version, sizeof(u16), 1, fp);

    struct ModCacheEntry* node = sModCacheHead;
    while (node != NULL) {
        fwrite(node->dataHash, sizeof(u8), 16, fp);
        u16 pathLen = strlen(node->path);
        fwrite(&pathLen, sizeof(u16), 1, fp);
        fwrite(node->path, sizeof(u8), pathLen + 1, fp);
        node = node->next;
    }

    fclose(fp);
}
