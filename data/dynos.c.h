#ifndef DYNOS_C_H
#define DYNOS_C_H
#ifndef __cplusplus

#include "dynos.h"

void *dynos_update_cmd         (void *cmd);
void  dynos_update_gfx         ();
void  dynos_update_opt         (void *pad);
s32   dynos_gfx_import_texture (void **output, void *ptr, s32 tile, void *grapi, void **hashmap, void *pool, s32 *poolpos, s32 poolsize);
void  dynos_gfx_swap_animations(void *ptr);

#ifdef COOP
bool dynos_warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
#endif

#endif
#endif
