#ifndef MODS_H
#define MODS_H

#include <PR/ultratypes.h>
#include "types.h"
#include "pc/platform.h"
#include "mod.h"

#define MAX_MOD_SIZE (35 * 1048576) // 35MB
// Direct connections may exceed MAX_MOD_SIZE. The client still trusts the
// advertised size when it allocates download bookkeeping, so keep a hard cap.
#define MAX_DIRECT_MOD_SIZE ((u64)2 * 1024 * 1048576) // 2 GiB
#define MOD_DIRECTORY "mods"
#define TMP_DIRECTORY ".tmp"

struct Mods {
    struct Mod** entries;
    u16 entryCount;
    size_t size;
};

extern struct Mods gLocalMods;
extern struct Mods gRemoteMods;
extern struct Mods gActiveMods;

extern char gRemoteModsBasePath[];

void mods_get_main_mod_name(char* destination, u32 maxSize);
u16  mods_get_enabled_count(void);
bool mods_get_all_pausable(void);
bool mods_generate_remote_base_path(void);
void mods_activate(struct Mods* mods);
void mods_clear(struct Mods* mods);
void mods_delete_folder(char* path);
void mods_refresh_local(void);
void mods_enable(char* relativePath);
void mods_init(void);
void mods_shutdown(void);

#endif