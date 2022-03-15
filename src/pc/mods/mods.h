#ifndef MODS_H
#define MODS_H

#include "PR/ultratypes.h"
#include <types.h>
#include "src/pc/platform.h"
#include "mod.h"

struct Mods {
    struct Mod* entries;
    u16 modCount;
};

void mods_clear(struct Mods* mods);
void mods_init(void);
void mods_shutdown(void);

#endif