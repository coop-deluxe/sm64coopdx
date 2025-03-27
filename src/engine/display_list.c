#include "display_list.h"

// Get the size of a display list by iterating
// until gsSPEndDisplayList or gsSPBranchList is found
u32 gfx_get_size(const Gfx* gfx) {
    for (u32 i = 0;;) {
        u32 op = (gfx + i)->words.w0 >> 24;
        u32 cmdSize = 1;
        switch (op) {
            case G_DL:
                if (C0(gfx + i, 16, 1) == G_DL_NOPUSH) { return i + 1; } // For displaylists that end with branches (jumps)
                break;
            case G_ENDDL:
                return i + 1;
            case G_TEXRECT:
            case G_TEXRECTFLIP:
                cmdSize = 3;
                break;
            case G_FILLRECT:
                cmdSize = 2;
                break;
        }
        i += cmdSize;
    }
}
