/*
 * All credit goes to https://github.com/jesusyoshi54
 * also known as scuttlebugraiser, the creator of RM2C
 * Created for the project https://github.com/jesusyoshi54/sm64ex-alo for RM2C support
 * https://github.com/jesusyoshi54/sm64ex-alo/blob/master/src/game/behaviors/texscroll.inc.c
 */

#include <math.h>
#include "engine/math_util.h"
#include "game/scroll_targets.h"
#include "pc/pc_main.h"
#include "pc/utils/misc.h"

static inline void shift_UV_JUMP(struct ScrollTarget *scroll, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    Vtx* *verts = scroll->vertices;
    u16 i;

    if (verts[0]->n.flag++ <= cycle) {
        return;
    }

    verts[0]->n.flag = 0;

    if (bhv < SCROLL_UV_X) {
        for (i = 0; i < vertcount; i++) {
            scroll->interpF32[i] += speed;
        }
    } else {
        for (i = 0; i < vertcount; i++) {
            scroll->interpS16[i] += speed;
        }
    }
}

static inline void shift_UV_NORMAL(struct ScrollTarget *scroll, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    Vtx* *verts = scroll->vertices;
    u16 overflownum = 0x1000;
    u16 correction = 0;
    u16 i;

    if (bhv < SCROLL_UV_X) {
        if (verts[0]->n.flag >= cycle) {
            correction = verts[0]->n.flag * speed;
            verts[0]->n.flag = 0;
        }

        for (i = 0; i < vertcount; i++) {
            if (correction == 0) {
                scroll->interpF32[i] += speed;
            } else {
                scroll->interpF32[i] -= correction;
            }
        }
    } else {
        if (verts[0]->n.flag * absi(speed) > overflownum) {
            correction = overflownum * signum_positive(speed);
            verts[0]->n.flag = 0;
        }

        for (i = 0; i < vertcount; i++) {
            if (correction == 0) {
                scroll->interpS16[i] += speed;
            } else {
                scroll->interpS16[i] -= correction;
            }
        }
    }

    if (correction == 0) {
        verts[0]->n.flag++;
    } else {
        if (bhv < SCROLL_UV_X) {
            for (i = 0; i < vertcount; i++) {
                scroll->prevF32[i] = scroll->interpF32[i];
            }
        } else {
            for (i = 0; i < vertcount; i++) {
                scroll->prevS16[i] = scroll->interpS16[i];
            }
        }
    }
}

static inline void shift_UV_SINE(struct ScrollTarget *scroll, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    Vtx* *verts = scroll->vertices;
    u32 i;

    if (bhv < SCROLL_UV_X) {
        for (i = 0; i < vertcount; i++) {
            scroll->interpF32[i] += sins(verts[0]->n.flag) * speed;
        }
    } else {
        for (i = 0; i < vertcount; i++) {
            scroll->interpS16[i] += (u16) (sins(verts[0]->n.flag) * speed);
        }
    }
    verts[0]->n.flag += cycle * 0x23;
}

/*
 * Scroll parameters are took from the object's properties:
 *   Xpos = speed
 *   Ypos = scrolling behavior/axis
 *   Zpos = vertices amount
 *   Xrot = offset
 *   Yrot = scrolling type
 *   Zrot = cycle
 *   Behavior param = scroll target index
 */
void uv_update_scroll(void) {
    if (!o) { return; }
    s16 speed = (s16) o->oPosX;
    u16 bhv = (u16) o->oPosY;
    u16 vertCount = (u16) o->oPosZ;
    u16 scrollType = (u16) round(o->oFaceAngleYaw * 180.0 / 0x8000);
    u16 cycle = (u16) round(o->oFaceAngleRoll * 180.0 / 0x8000);
    u16 offset = (u16) round(o->oFaceAnglePitch * 180.0 / 0x8000);
    u32 vtxIndex = (u32) o->oBehParams;

    // Check for invalid scrolling behavior
    if (bhv == 3 || bhv > SCROLL_UV_Y) { return; }

    struct ScrollTarget *scroll = get_scroll_targets(vtxIndex, vertCount, offset);
    if (!scroll || !scroll->vertices) { return; }

    Vtx* *verts = scroll->vertices;

    // Init interpolation
    if (!scroll->hasInterpInit) {
        scroll->hasInterpInit = true;
        scroll->bhv = bhv;
        if (bhv < SCROLL_UV_X) {
            scroll->interpF32 = calloc(scroll->size, sizeof(f32));
            scroll->prevF32 = calloc(scroll->size, sizeof(f32));

            u8 bhvIndex = MIN(bhv, 2);
            for (u16 k = 0; k < scroll->size; k++) {
                scroll->interpF32[k] = verts[k]->n.ob[bhvIndex];
            }
        } else {
            scroll->interpS16 = calloc(scroll->size, sizeof(s16));
            scroll->prevS16 = calloc(scroll->size, sizeof(s16));

            u8 bhvIndex = MIN(bhv-SCROLL_UV_X, 1);
            for (u16 k = 0; k < scroll->size; k++) {
                scroll->interpS16[k] = verts[k]->n.tc[bhvIndex];
            }
        }
    }

    // Prepare for interpolation
    if (bhv < SCROLL_UV_X) {
        u8 bhvIndex = MIN(bhv, 2);
        for (u16 i = 0; i < scroll->size; i++) {
            scroll->prevF32[i] = verts[i]->n.ob[bhvIndex];
        }
    } else {
        u8 bhvIndex = MIN(bhv-SCROLL_UV_X, 1);
        for (u16 i = 0; i < scroll->size; i++) {
            scroll->prevS16[i] = verts[i]->n.tc[bhvIndex];
        }
    }
    scroll->needInterp = true;

    switch (scrollType) {
        case MODE_SCROLL_UV:
            shift_UV_NORMAL(scroll, vertCount, speed, bhv, cycle);
            break;
        case MODE_SCROLL_SINE:
            shift_UV_SINE(scroll, vertCount, speed, bhv, cycle);
            break;
        case MODE_SCROLL_JUMP:
            shift_UV_JUMP(scroll, vertCount, speed, bhv, cycle);
            break;
    }
}
