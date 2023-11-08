/*
 * All credit goes to https://github.com/jesusyoshi54
 * also known as scuttlebugraiser, the creator of RM2C
 * Created for the project https://github.com/jesusyoshi54/sm64ex-alo for RM2C support
 * https://github.com/jesusyoshi54/sm64ex-alo/blob/master/src/game/behaviors/texscroll.inc.c
 */

#include <math.h>
#include "engine/math_util.h"
#include "src/game/scroll_targets.h"
#include "pc/pc_main.h"
#include "pc/utils/misc.h"

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

// typedef struct {
    // float		  ob[3];	/* x, y, z */
    // unsigned short flag;
    // short		  tc[2];	/* texture coord */
    // signed char	  n[3];	/* normal */
    // unsigned char  a;      /* alpha  */
// } Vtx_tn;

// typedef union {
    // Vtx_t		  v;  /* Use this one for colors  */
    // Vtx_tn         n;  /* Use this one for normals */
    // long long int  force_structure_alignment;
// } Vtx;

static void shift_UV_JUMP(s32 vtxIndex, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    Vtx* *verts = get_scroll_targets(vtxIndex);
    u16 i;

    if (verts == NULL) {
        return;
    }

    if (verts[0]->n.flag++ <= cycle) {
        return;
    }

    verts[0]->n.flag = 0;

    if (bhv < SCROLL_UV_X) {
        for (i = 0; i < vertcount; i++) {
            verts[i]->n.ob[MIN(bhv, 2)] += speed;
        }
    } else {
        for (i = 0; i < vertcount; i++) {
            verts[i]->n.tc[MIN(bhv-SCROLL_UV_X, 1)] += speed;
        }
    }
}

static void shift_UV_NORMAL(u32 vtxIndex, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    u16 overflownum = 0x1000;
    Vtx* *verts = get_scroll_targets(vtxIndex);
    u16 correction = 0;
    u16 i;

    if (verts == NULL) {
        return;
    }

    if (bhv < SCROLL_UV_X) {
        if (verts[0]->n.flag >= cycle) {
            correction = verts[0]->n.flag * speed;
            verts[0]->n.flag = 0;
        }

        for (i = 0; i < vertcount; i++) {
            if (correction == 0) {
                verts[i]->n.ob[MIN(bhv, 2)] += speed;
            } else {
                verts[i]->n.ob[MIN(bhv, 2)] -= correction;
            }
        }
    } else {
        if (verts[0]->n.flag * absi(speed) > overflownum) {
            correction = overflownum * signum_positive(speed);
            verts[0]->n.flag = 0;
        }

        for (i = 0; i < vertcount; i++) {
            if (correction == 0) {
                verts[i]->n.tc[MIN(bhv-SCROLL_UV_X, 1)] += speed;
            } else {
                verts[i]->n.tc[MIN(bhv-SCROLL_UV_X, 1)] -= correction;
            }
        }
    }

    if (correction == 0) {
        verts[0]->n.flag++;
    }
}

static void shift_UV_SINE(u32 vtxIndex, u16 vertcount, s16 speed, u16 bhv, u16 cycle) {
    Vtx* *verts = get_scroll_targets(vtxIndex);
    u32 i;

    if (verts == NULL) {
        return;
    }

    if (bhv < SCROLL_UV_X) {
        for (i = 0; i < vertcount; i++) {
            verts[i]->n.ob[MIN(bhv, 2)] += sins(verts[0]->n.flag) * speed;
        }
    } else {
        for (i = 0; i < vertcount; i++) {
            verts[i]->n.tc[MIN(bhv-SCROLL_UV_X, 1)] += (u16) (sins(verts[0]->n.flag) * speed);
        }
    }
    verts[0]->n.flag += cycle * 0x23;
}

/*
 * Scroll parameters are took from the object's properties:
 *   Xpos = speed
 *   Ypos = scrolling behavior/axis
 *   Zpos = vertices amount
 *   Xrot = offset (unused)
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
    u32 vtxIndex = (u32) o->oBehParams;

    // Check for invalid scrolling behavior
    if (bhv == 3 || bhv > SCROLL_UV_Y) {
        return;
    }

    switch (scrollType) {
        case MODE_SCROLL_UV:
            shift_UV_NORMAL(vtxIndex, vertCount, speed, bhv, cycle);
            break;
        case MODE_SCROLL_SINE:
            shift_UV_SINE(vtxIndex, vertCount, speed, bhv, cycle);
            break;
        case MODE_SCROLL_JUMP:
            shift_UV_JUMP(vtxIndex, vertCount, speed, bhv, cycle);
            break;
        default:
            break;
    }
}
