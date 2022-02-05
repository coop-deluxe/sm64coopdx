#ifndef MOD_LIST_H
#define MOD_LIST_H

#include <stdio.h>
#include "PR/ultratypes.h"
#include <types.h>
#include <stdbool.h>
#include <limits.h>

#define MOD_PATH "./mods"

struct ModListEntry {
    char* name;
    FILE* fp;
    char path[PATH_MAX];
    size_t size;
    u64 curOffset;
    u16 remoteIndex;
    char* displayName;
    char* incompatible;
    char* description;
    bool tmp;
    bool complete;
    bool enabled;
    bool selectable;
};

struct ModTable {
    struct ModListEntry* entries;
    u16 entryCount;
    u8 isRemote;
    u64 totalSize;
};

extern struct ModTable gModTableLocal;
extern struct ModTable gModTableRemote;
extern struct ModTable* gModTableCurrent;

void mod_list_add_tmp(u16 index, u16 remoteIndex, char* name, size_t size);
void mod_list_extract_lua_fields(struct ModListEntry* entry);
void mod_table_clear(struct ModTable* table);
void mod_list_alloc(struct ModTable* table, u16 count);

void mod_list_update_selectable(void);

void mod_list_init(void);
void mod_list_shutdown(void);

#endif