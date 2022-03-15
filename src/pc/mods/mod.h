#ifndef MOD_H
#define MOD_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"

struct Mods;

struct ModFile {
    char relativePath[SYS_MAX_PATH];
};

struct Mod {
    char* name;
    char* incompatible;
    char* description;
    char relativePath[SYS_MAX_PATH];
    char basePath[SYS_MAX_PATH];
    struct ModFile* files;
    u16 fileCount;
    bool isDirectory;
    bool enabled;
};

void mod_clear(struct Mod* mod);
bool mod_load(struct Mods* mods, char* basePath, char* modName);

#endif