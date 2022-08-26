#include "scroll_targets.h"

Vtx *gScrollTargets[1024];

static int startIndex[128];
static int lastIndex = 0;

Vtx* *get_scroll_targets(u32 id) {
    return &gScrollTargets[startIndex[id]];
}

void add_vtx_scroll_target(u32 id, Vtx *vtx, u32 size) {
    if (startIndex[id] == -1) {
        startIndex[id] = lastIndex;
    }

    for (u32 i = 0; i < size; ++i) {
        gScrollTargets[lastIndex++] = &vtx[i];
    }
}

void init_vtx_scroll_targets(void) {
    for (int i = 0; i < 128; ++i) {
        startIndex[i] = -1;
    }
    lastIndex = 0;
}
