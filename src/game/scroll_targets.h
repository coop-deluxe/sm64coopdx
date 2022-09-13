/*
 * All credit goes to https://github.com/jesusyoshi54
 * also known as scuttlebugraiser, the creator of RM2C
 * Created for the project https://github.com/jesusyoshi54/sm64ex-alo for RM2C support
 * https://github.com/jesusyoshi54/sm64ex-alo/blob/master/src/game/ScrollTargets.inc.c
 */

#include <PR/ultratypes.h>
#include "sm64.h"
#include "types.h"

Vtx* *get_scroll_targets(u32 id);
void add_vtx_scroll_target(u32 id, Vtx *vtx, u32 size);
void free_vtx_scroll_targets(void);
