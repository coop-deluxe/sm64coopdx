#ifndef MOD_H
#define MOD_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"

#define MOD_NAME_MAX_LENGTH 64
#define MOD_INCOMPATIBLE_MAX_LENGTH 256
#define MOD_CATEGORY_MAX_LENGTH 64
#define MOD_DESCRIPTION_MAX_LENGTH 800
#define MOD_FILE_PATTERNS_MAX_LENGTH 1024

#define MOD_NAME_SIZE (MOD_NAME_MAX_LENGTH + 1)
#define MOD_INCOMPATIBLE_SIZE (MOD_INCOMPATIBLE_MAX_LENGTH + 1)
#define MOD_CATEGORY_SIZE (MOD_CATEGORY_MAX_LENGTH + 1)
#define MOD_DESCRIPTION_SIZE (MOD_DESCRIPTION_MAX_LENGTH + 1)
#define MOD_FILE_PATTERNS_SIZE (MOD_FILE_PATTERNS_MAX_LENGTH + 1)

#define MOD_FILE_PATTERNS_MAX 256

struct Mods;

extern const char *MOD_FILE_CACHEABLE_EXTENSIONS[];

struct ModFile {
    char relativePath[SYS_MAX_PATH];
    size_t size;
    u64 modifiedTimestamp;
    bool isLoadedLuaModule;

    FILE* fp;
    u64 wroteBytes;
    u8 dataHash[16];
    char* cachedPath;
};

struct ModFilePatterns {
    bool blacklist;
    const char *patterns[MOD_FILE_PATTERNS_MAX];
    size_t count;
};

struct Mod {
    char name[MOD_NAME_SIZE];
    char* incompatible;
    char* category;
    char* description;
    char relativePath[SYS_MAX_PATH];
    char basePath[SYS_MAX_PATH];
    struct ModFile* files;
    struct ModFilePatterns* filePatterns;
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
    u16 customBehaviorIndex;
    struct GrowingArray *customObjectFields;
};

size_t mod_get_lua_size(struct Mod* mod);
void mod_activate(struct Mod* mod);
void mod_clear(struct Mod* mod);
bool mod_refresh_files(struct Mod* mod);
bool mod_load(struct Mods* mods, char* basePath, char* modName);

#endif