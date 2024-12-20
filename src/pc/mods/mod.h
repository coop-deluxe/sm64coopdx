#ifndef MOD_H
#define MOD_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"

#define MOD_NAME_MAX_LENGTH 64
#define MOD_INCOMPATIBLE_MAX_LENGTH 256
#define MOD_CATEGORY_MAX_LENGTH 64
#define MOD_DESCRIPTION_MAX_LENGTH 800

struct Mods;

struct ModFile {
    char relativePath[SYS_MAX_PATH];
    size_t size;

    FILE* fp;
    u64 wroteBytes;
    u8 dataHash[16];
    char* cachedPath;
};

struct Mod {
    char* name;
    char* incompatible;
    char* category;
    char* description;
    char relativePath[SYS_MAX_PATH];
    char basePath[SYS_MAX_PATH];
    struct ModFile* files;
    s32 index;
    u16 fileCount;
    u16 fileCapacity;
    bool isDirectory;
    bool enabled;
    bool selectable;
    bool renderBehindHud;
    bool pausable;
    bool ignoreScriptWarnings;
    bool showedScriptWarning;
    size_t size;
    u8 customBehaviorIndex;
};

size_t mod_get_lua_size(struct Mod* mod);
void mod_activate(struct Mod* mod);
void mod_clear(struct Mod* mod);
bool mod_load(struct Mods* mods, char* basePath, char* modName);

#endif