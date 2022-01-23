#ifndef MOD_LIST_H
#define MOD_LIST_H

#include <stdio.h>
#include "PR/ultratypes.h"
#include <types.h>
#include <stdbool.h>

#define MOD_PATH "./mods"

struct ModListEntry {
    char* name;
    FILE* fp;
    char path[PATH_MAX];
    size_t size;
    u64 curOffset;
    bool tmp;
    bool complete;
};
extern struct ModListEntry* gModEntries;
extern u16 gModEntryCount;
extern u64 gModTotalSize;

void mod_list_alloc(u16 count);
void mod_list_add(u16 index, char* name, size_t size, bool tmpFile);

void mod_list_load(void);
void mod_list_clear(void);

void mod_list_init(void);
void mod_list_shutdown(void);

#endif