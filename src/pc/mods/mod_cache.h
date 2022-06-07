#ifndef MOD_CACHE_H

#include "types.h"
#include "mod.h"

struct ModCacheEntry {
    u8 dataHash[16];
    u64 lastLoaded;
    char* path;
    struct ModCacheEntry* next;
};

void mod_cache_shutdown(void);
struct ModCacheEntry* mod_cache_get_from_hash(u8* dataHash);
struct ModCacheEntry* mod_cache_get_from_path(const char* path, bool validate);
void mod_cache_add(struct Mod* mod, struct ModFile* modFile, bool useFilePath);
void mod_cache_update(struct Mod* mod, struct ModFile* file);
void mod_cache_load(void);
void mod_cache_save(void);

#endif