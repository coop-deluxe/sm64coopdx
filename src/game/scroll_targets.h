/*
 * All credit goes to https://github.com/jesusyoshi54
 * also known as scuttlebugraiser, the creator of RM2C
 * Created for the project https://github.com/jesusyoshi54/sm64ex-alo for RM2C support
 * https://github.com/jesusyoshi54/sm64ex-alo/blob/master/src/game/ScrollTargets.inc.c
 */

#include <PR/ultratypes.h>
#include "sm64.h"
#include "types.h"

/* SCROLLING BHVS */
#define SCROLL_X 0
#define SCROLL_Y 1
#define SCROLL_Z 2
#define SCROLL_UV_X 4
#define SCROLL_UV_Y 5

/* SCROLLING TYPES */
#define MODE_SCROLL_UV 0
#define MODE_SCROLL_SINE 1
#define MODE_SCROLL_JUMP 2

/*
 * A scroll target is basically just a bunch of Vtx to
 * apply a movement to. Each scroll targets have an id.
 * The id is what the behavior is using to know which
 * vertices to move.
 */
struct ScrollTarget {
    u32 id;
    u32 size;
    Vtx* *vertices;

    bool hasOffset;
    bool hasInterpInit;
    bool needInterp;
    f32 *interpF32;
    f32 *prevF32;
    s16 *interpS16;
    s16 *prevS16;
    u16 bhv;
};

struct ScrollTarget *get_scroll_targets(u32 id, u16 size, u16 offset);
void add_vtx_scroll_target(u32 id, Vtx *vtx, u32 size, bool hasOffset);
void free_vtx_scroll_targets(void);
