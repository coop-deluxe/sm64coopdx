#ifndef MOD_LIST_H
#define MOD_LIST_H

#include <stdio.h>
#include "PR/ultratypes.h"
#include <types.h>
#include <stdbool.h>

#define MOD_PATH "./mods"

#pragma pack(1)
struct ModListEntry {
    char* name;
    FILE* fp;
    char path[PATH_MAX];
    size_t size;
    u64 curOffset;
    u16 remoteIndex;
    bool tmp;
    bool complete;
    bool enabled;
};

#pragma pack(1)
struct ModTable {
    struct ModListEntry* entries;
    u16 entryCount;
    u8 isRemote;
    u64 totalSize;
};

extern struct ModTable gModTableLocal;
extern struct ModTable gModTableRemote;

void mod_list_add_tmp(u16 index, u16 remoteIndex, char* name, size_t size);
void mod_table_clear(struct ModTable* table);
void mod_list_alloc(struct ModTable* table, u16 count);

void mod_list_init(void);
void mod_list_shutdown(void);

#endif