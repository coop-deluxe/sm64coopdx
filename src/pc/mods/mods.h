#ifndef MODS_H
#define MODS_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"
#include "mod.h"

#define MAX_MOD_SIZE (2 * 1048576) // 2MB

struct Mods {
    struct Mod** entries;
    u16 entryCount;
    size_t size;
};

extern struct Mods gLocalMods;
extern struct Mods gRemoteMods;
extern struct Mods gActiveMods;

void mods_activate(struct Mods* mods);
void mods_clear(struct Mods* mods);
void mods_init(void);
void mods_shutdown(void);

#endif