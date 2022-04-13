#ifndef MOD_H
#define MOD_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"

struct Mods;

struct ModFile {
    char relativePath[SYS_MAX_PATH];
    size_t size;

    FILE* fp;
    u64 curOffset;
    bool complete;
};

struct Mod {
    char* name;
    char* incompatible;
    char* description;
    char relativePath[SYS_MAX_PATH];
    char basePath[SYS_MAX_PATH];
    struct ModFile* files;
    s32 index;
    u16 fileCount;
    bool isDirectory;
    bool enabled;
    bool selectable;
    size_t size;
    u8 dataHash[16];
    bool hashProcessed;
    bool loadedFromCache;
};

void mod_activate(struct Mod* mod);
void mod_clear(struct Mod* mod);
bool mod_load(struct Mods* mods, char* basePath, char* modName);
void mod_md5_hash(struct Mod* mod);
void mod_load_from_cache(struct Mod* mod);

#endif