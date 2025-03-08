#include <PR/ultratypes.h>

#include "area.h"
#include "engine/math_util.h"
#include "game_init.h"
#include "gfx_dimensions.h"
#include "main.h"
#include "memory.h"
#include "print.h"
#include "rendering_graph_node.h"
#include "shadow.h"
#include "sm64.h"
#include "game/level_update.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/utils/misc.h"
#include "pc/debuglog.h"
#include "game/skybox.h"
#include "game/first_person_cam.h"
#include "course_table.h"
#include "skybox.h"

/**
 * This file contains the code that processes the scene graph for rendering.
 * The scene graph is responsible for drawing everything except the HUD / text boxes.
 * First the root of the scene graph is processed when geo_process_root
 * is called from level_script.c. The rest of the tree is traversed recursively
 * using the function geo_process_node_and_siblings, which switches over all
 * geo node types and calls a specialized function accordingly.
 * The types are defined in engine/graph_node.h
 *
 * The scene graph typically looks like:
 * - Root (viewport)
 *  - Master list
 *   - Ortho projection
 *    - Background (skybox)
 *  - Master list
 *   - Perspective
 *    - Camera
 *     - <area-specific display lists>
 *     - Object parent
 *      - <group with 240 object nodes>
 *  - Master list
 *   - Script node (Cannon overlay)
 *
 */

#define DISPLAY_LIST_HEAP_SIZE 32000

f32 gProjectionMaxNearValue = 5;
s16 gProjectionVanillaNearValue = 100;
s16 gProjectionVanillaFarValue = 1000;

s16 gMatStackIndex;
Mat4 gMatStack[MATRIX_STACK_SIZE] = {};
Mat4 gMatStackPrev[MATRIX_STACK_SIZE] = {};
Mtx *gMatStackFixed[MATRIX_STACK_SIZE] = { 0 };
Mtx *gMatStackPrevFixed[MATRIX_STACK_SIZE] = { 0 };

s32 gCamSkipInterp = 0;
Vec3f gCamSkipInterpDisplacement = { 0 };

u8 sUsingCamSpace = FALSE;
Mtx sPrevCamTranf, sCurrCamTranf = {
    .m = {
        {1.0f, 0.0f, 0.0f, 0.0f},
        {0.0f, 1.0f, 0.0f, 0.0f},
        {0.0f, 0.0f, 1.0f, 0.0f},
        {0.0f, 0.0f, 0.0f, 1.0f}
    }
};

static Gfx obj_sanitize_gfx[] = {
    gsSPClearGeometryMode(G_TEXTURE_GEN),
    gsSPSetGeometryMode(G_LIGHTING),
    gsDPSetCombineMode(G_CC_SHADE, G_CC_SHADE),
    gsSPTexture(0xFFFF, 0xFFFF, 0, 0, G_OFF),
    gsDPSetAlphaCompare(G_AC_NONE),
    gsSPEndDisplayList(),
};

/**
 * Animation nodes have state in global variables, so this struct captures
 * the animation state so a 'context switch' can be made when rendering the
 * held object.
 */
struct GeoAnimState {
    /*0x00*/ u8 type;
    /*0x01*/ u8 enabled;
    /*0x02*/ s16 frame;
    /*0x04*/ f32 translationMultiplier;
    /*0x08*/ u16 *attribute;
    /*0x0C*/ struct Animation* anim;
    s16 prevFrame;
};

// For some reason, this is a GeoAnimState struct, but the current state consists
// of separate global variables. It won't match EU otherwise.
struct GeoAnimState gGeoTempState;

u8 gCurAnimType;
u8 gCurAnimEnabled;
s16 gCurrAnimFrame;
s16 gPrevAnimFrame;
f32 gCurAnimTranslationMultiplier;
u16 *gCurrAnimAttribute = NULL;
struct Animation *gCurAnim = NULL;

struct GrowingPool* gDisplayListHeap = NULL;

struct RenderModeContainer {
    u32 modes[8];
};

/* Rendermode settings for cycle 1 for all 8 layers. */
struct RenderModeContainer renderModeTable_1Cycle[2] = { { {
    G_RM_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_OPA_SURF,
    G_RM_AA_TEX_EDGE,
    G_RM_AA_XLU_SURF,
    G_RM_AA_XLU_SURF,
    G_RM_AA_XLU_SURF,
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF,
    G_RM_AA_ZB_OPA_SURF,
    G_RM_AA_ZB_OPA_DECAL,
    G_RM_AA_ZB_OPA_INTER,
    G_RM_AA_ZB_TEX_EDGE,
    G_RM_AA_ZB_XLU_SURF,
    G_RM_AA_ZB_XLU_DECAL,
    G_RM_AA_ZB_XLU_INTER,
    } } };

/* Rendermode settings for cycle 2 for all 8 layers. */
struct RenderModeContainer renderModeTable_2Cycle[2] = { { {
    G_RM_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_OPA_SURF2,
    G_RM_AA_TEX_EDGE2,
    G_RM_AA_XLU_SURF2,
    G_RM_AA_XLU_SURF2,
    G_RM_AA_XLU_SURF2,
    } },
    { {
    /* z-buffered */
    G_RM_ZB_OPA_SURF2,
    G_RM_AA_ZB_OPA_SURF2,
    G_RM_AA_ZB_OPA_DECAL2,
    G_RM_AA_ZB_OPA_INTER2,
    G_RM_AA_ZB_TEX_EDGE2,
    G_RM_AA_ZB_XLU_SURF2,
    G_RM_AA_ZB_XLU_DECAL2,
    G_RM_AA_ZB_XLU_INTER2,
    } } };

struct GraphNodeRoot *gCurGraphNodeRoot = NULL;
struct GraphNodeMasterList *gCurGraphNodeMasterList = NULL;
struct GraphNodePerspective *gCurGraphNodeCamFrustum = NULL;
struct GraphNodeCamera *gCurGraphNodeCamera = NULL;
struct GraphNodeObject *gCurGraphNodeObject = NULL;
struct GraphNodeHeldObject *gCurGraphNodeHeldObject = NULL;
u16 gAreaUpdateCounter = 0;

#ifdef F3DEX_GBI_2
LookAt lookAt;
#endif

static struct GraphNodePerspective *sPerspectiveNode = NULL;
static Gfx* sPerspectivePos   = NULL;
static Mtx* sPerspectiveMtx   = NULL;
static f32 sPerspectiveAspect = 0;

static Vp*  sViewport        = NULL;
static Gfx* sViewportPos     = NULL;
static Gfx* sViewportClipPos = NULL;
static Vp   sViewportPrev    = { 0 };
static Vp   sViewportInterp  = { 0 };

static struct GraphNodeBackground* sBackgroundNode = NULL;
Gfx* gBackgroundSkyboxGfx = NULL;
Vtx* gBackgroundSkyboxVerts[SKYBOX_TILES_Y][SKYBOX_TILES_X] = { 0 };
Mtx* gBackgroundSkyboxMtx = NULL;
struct GraphNodeRoot* sBackgroundNodeRoot = NULL;

#define MAX_SHADOW_NODES 128
struct ShadowInterp sShadowInterp[MAX_SHADOW_NODES] = { 0 };
struct ShadowInterp* gShadowInterpCurrent = NULL;
static u8 sShadowInterpCount = 0;

static struct GraphNodeCamera * sCameraNode = NULL;

struct {
    Gfx *pos;
    Mtx *mtx;
    Mtx *mtxPrev;
    void *displayList;
    Mtx interp;
    u8 usingCamSpace;
} gMtxTbl[6400];
s32 gMtxTblSize = 0;

struct Object* gCurGraphNodeProcessingObject = NULL;
struct MarioState* gCurGraphNodeMarioState = NULL;

f32 gOverrideFOV = 0;
f32 gOverrideNear = 0;
f32 gOverrideFar = 0;

void patch_mtx_before(void) {
    gMtxTblSize = 0;

    if (sPerspectiveNode != NULL) {
        sPerspectiveNode->prevFov = sPerspectiveNode->fov;
        sPerspectiveNode = NULL;
    }

    if (sViewport != NULL) {
        sViewportPrev    = *sViewport;
        sViewport        = NULL;
        sViewportPos     = NULL;
        sViewportClipPos = NULL;
    }

    if (sBackgroundNode != NULL) {
        vec3f_copy(sBackgroundNode->prevCameraPos, gLakituState.pos);
        vec3f_copy(sBackgroundNode->prevCameraFocus, gLakituState.focus);
        sBackgroundNode->prevCameraTimestamp = gGlobalTimer;
        sBackgroundNode = NULL;
        gBackgroundSkyboxGfx = NULL;
    }

    sShadowInterpCount = 0;
}

void patch_mtx_interpolated(f32 delta) {
    Mtx camTranfInv, prevCamTranfInv;

    if (sPerspectiveNode != NULL) {
        if (gCamSkipInterp) {
            sPerspectiveNode->prevFov = sPerspectiveNode->fov;
        }
        u16 perspNorm;
        f32 fovInterpolated = delta_interpolate_f32(sPerspectiveNode->prevFov, sPerspectiveNode->fov, delta);
        f32 near = MIN(sPerspectiveNode->near, gProjectionMaxNearValue);
        guPerspective(sPerspectiveMtx, &perspNorm, fovInterpolated, sPerspectiveAspect, get_first_person_enabled() ? 1 : not_zero(near, gOverrideNear), not_zero(sPerspectiveNode->far, gOverrideFar), 1.0f);
        gSPMatrix(sPerspectivePos, VIRTUAL_TO_PHYSICAL(sPerspectiveNode), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    }

    if (sViewportClipPos != NULL) {
        delta_interpolate_vec3s(sViewportInterp.vp.vtrans, sViewportPrev.vp.vtrans, sViewport->vp.vtrans, delta);
        delta_interpolate_vec3s(sViewportInterp.vp.vscale, sViewportPrev.vp.vscale, sViewport->vp.vscale, delta);

        Gfx *saved = gDisplayListHead;

        gDisplayListHead = sViewportClipPos;
        make_viewport_clip_rect(&sViewportInterp);
        gSPViewport(gDisplayListHead, VIRTUAL_TO_PHYSICAL(&sViewportInterp));

        gDisplayListHead = saved;
    }

    if (sBackgroundNode != NULL) {
        Vec3f posCopy;
        Vec3f focusCopy;
        struct GraphNodeRoot* rootCopy = gCurGraphNodeRoot;

        gCurGraphNodeRoot = sBackgroundNodeRoot;
        vec3f_copy(posCopy, gLakituState.pos);
        vec3f_copy(focusCopy, gLakituState.focus);
        if (gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
            delta_interpolate_vec3f(gLakituState.pos, sBackgroundNode->prevCameraPos, posCopy, delta);
            delta_interpolate_vec3f(gLakituState.focus, sBackgroundNode->prevCameraFocus, focusCopy, delta);
        }
        sBackgroundNode->fnNode.func(GEO_CONTEXT_RENDER, &sBackgroundNode->fnNode.node, NULL);

        vec3f_copy(gLakituState.pos, posCopy);
        vec3f_copy(gLakituState.focus, focusCopy);
        gCurGraphNodeRoot = rootCopy;
    }

    struct GraphNodeObject* savedObj = gCurGraphNodeObject;
    for (s32 i = 0; i < sShadowInterpCount; i++) {
        struct ShadowInterp* interp = &sShadowInterp[i];
        if (!interp->gfx) { continue; }
        gShadowInterpCurrent = interp;
        Vec3f posInterp;
        delta_interpolate_vec3f(posInterp, interp->shadowPosPrev, interp->shadowPos, delta);
        gCurGraphNodeObject = interp->obj;
        extern u8 gInterpolatingSurfaces;
        gInterpolatingSurfaces = true;
        gShadowInterpCurrent->gfx = create_shadow_below_xyz(posInterp[0], posInterp[1], posInterp[2], interp->shadowScale, interp->node->shadowSolidity, interp->node->shadowType);
        gInterpolatingSurfaces = false;
        gShadowInterpCurrent = NULL;
    }
    gCurGraphNodeObject = savedObj;

    // calculate outside of for loop to reduce overhead
    // technically this is improper use of mtxf functions, but coop doesn't target N64
    bool translateCamSpace = (gMtxTblSize > 0) && sCameraNode && (sCameraNode->matrixPtr != NULL) && (sCameraNode->matrixPtrPrev != NULL);
    if (translateCamSpace) {
        mtxf_inverse(camTranfInv.m, *sCameraNode->matrixPtr);
        mtxf_inverse(prevCamTranfInv.m, *sCameraNode->matrixPtrPrev);
    }

    for (s32 i = 0; i < gMtxTblSize; i++) {
        Mtx bufMtx, bufMtxPrev;

        memcpy(bufMtx.m, ((Mtx*) gMtxTbl[i].mtx)->m, sizeof(f32) * 4 * 4);
        memcpy(bufMtxPrev.m, ((Mtx*) gMtxTbl[i].mtxPrev)->m, sizeof(f32) * 4 * 4);

        Gfx *pos = gMtxTbl[i].pos;

        if (gMtxTbl[i].usingCamSpace && translateCamSpace) {
            // transform out of camera space so the matrix can interp in world space
            mtxf_mul(bufMtx.m, bufMtx.m, camTranfInv.m);
            mtxf_mul(bufMtxPrev.m, bufMtxPrev.m, prevCamTranfInv.m);
        }
        delta_interpolate_mtx(&gMtxTbl[i].interp, &bufMtxPrev, &bufMtx, delta);
        if (gMtxTbl[i].usingCamSpace) {
            // transform back to camera space, respecting camera interpolation
            Mtx camInterp;
            Vec3f posInterp, focusInterp;

            // use camera node's stored information to calculate interpolated camera transform
            delta_interpolate_vec3f(posInterp, sCameraNode->prevPos, sCameraNode->pos, delta);
            delta_interpolate_vec3f(focusInterp, sCameraNode->prevFocus, sCameraNode->focus, delta);
            mtxf_lookat(camInterp.m, posInterp, focusInterp, sCameraNode->roll);
            mtxf_to_mtx(&camInterp, camInterp.m);
            mtxf_mul(gMtxTbl[i].interp.m, gMtxTbl[i].interp.m, camInterp.m);
        }
        gSPMatrix(pos++, VIRTUAL_TO_PHYSICAL(&gMtxTbl[i].interp),
                  G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    }

    gCamSkipInterp = 0;
}

/**
 * Increments the matrix stack index and sets the matrixs at the new index.
 */
static u8 increment_mat_stack(void) {
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    Mtx *mtxPrev = alloc_display_list(sizeof(*mtxPrev));
    if (mtx == NULL || mtxPrev == NULL) {
        LOG_ERROR("Failed to allocate our matrices for the matrix stack.");
        return FALSE;
    }

    gMatStackIndex++;
    if (gMatStackIndex >= MATRIX_STACK_SIZE) {
        LOG_ERROR("Exceeded matrix stack size.");
        gMatStackIndex = MATRIX_STACK_SIZE - 1;
        return FALSE;
    }

    mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
    mtxf_to_mtx(mtxPrev, gMatStackPrev[gMatStackIndex]);
    gMatStackFixed[gMatStackIndex] = mtx;
    gMatStackPrevFixed[gMatStackIndex] = mtxPrev;
    return TRUE;
}

/**
 * Process a master list node.
 */
static void geo_process_master_list_sub(struct GraphNodeMasterList *node) {
    struct DisplayListNode *currList = NULL;
    s32 enableZBuffer = (node->node.flags & GRAPH_RENDER_Z_BUFFER) != 0;
    struct RenderModeContainer *modeList = &renderModeTable_1Cycle[enableZBuffer];
    struct RenderModeContainer *mode2List = &renderModeTable_2Cycle[enableZBuffer];

    // @bug This is where the LookAt values should be calculated but aren't.
    // As a result, environment mapping is broken on Fast3DEX2 without the
    // changes below.
#ifdef F3DEX_GBI_2
    Mtx lMtx;
    guLookAtReflect(&lMtx, &lookAt, 0, 0, 0, /* eye */ 0, 0, 1, /* at */ 1, 0, 0 /* up */);
#endif

    if (enableZBuffer != 0) {
        gDPPipeSync(gDisplayListHead++);
        gSPSetGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }

    for (s32 i = 0; i < GFX_NUM_MASTER_LISTS; i++) {
        if ((currList = node->listHeads[i]) != NULL) {
            gDPSetRenderMode(gDisplayListHead++, modeList->modes[i], mode2List->modes[i]);
            while (currList != NULL) {
                detect_and_skip_mtx_interpolation(&currList->transform, &currList->transformPrev);
                if ((u32) gMtxTblSize < sizeof(gMtxTbl) / sizeof(gMtxTbl[0])) {
                    gMtxTbl[gMtxTblSize].pos = gDisplayListHead;
                    gMtxTbl[gMtxTblSize].mtx = currList->transform;
                    gMtxTbl[gMtxTblSize].mtxPrev = currList->transformPrev;
                    gMtxTbl[gMtxTblSize].displayList = currList->displayList;
                    gMtxTbl[gMtxTblSize++].usingCamSpace = currList->usingCamSpace;
                }
                gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(currList->transformPrev),
                          G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
                gSPDisplayList(gDisplayListHead++, currList->displayList);
                currList = currList->next;
            }
        }
    }
    if (enableZBuffer != 0) {
        gDPPipeSync(gDisplayListHead++);
        gSPClearGeometryMode(gDisplayListHead++, G_ZBUFFER);
    }
}

/**
 * Appends the display list to one of the master lists based on the layer
 * parameter. Look at the RenderModeContainer struct to see the corresponding
 * render modes of layers.
 */
static void geo_append_display_list(void *displayList, s16 layer) {

#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif
    if (gCurGraphNodeMasterList != 0) {
        struct DisplayListNode *listNode = growing_pool_alloc(gDisplayListHeap, sizeof(struct DisplayListNode));

        listNode->transform = gMatStackFixed[gMatStackIndex];
        listNode->transformPrev = gMatStackPrevFixed[gMatStackIndex];
        listNode->displayList = displayList;
        listNode->next = 0;
        listNode->usingCamSpace = sUsingCamSpace;
        if (gCurGraphNodeMasterList->listHeads[layer] == 0) {
            gCurGraphNodeMasterList->listHeads[layer] = listNode;
        } else {
            gCurGraphNodeMasterList->listTails[layer]->next = listNode;
        }
        gCurGraphNodeMasterList->listTails[layer] = listNode;
    }
}

/**
 * Process the master list node.
 */
static void geo_process_master_list(struct GraphNodeMasterList *node) {
    if (gCurGraphNodeMasterList == NULL && node->node.children != NULL) {
        gCurGraphNodeMasterList = node;
        for (s32 i = 0; i < GFX_NUM_MASTER_LISTS; i++) {
            node->listHeads[i] = NULL;
        }
        geo_process_node_and_siblings(node->node.children);
        geo_process_master_list_sub(node);
        gCurGraphNodeMasterList = NULL;
    }
}

/**
 * Process an orthographic projection node.
 */
static void geo_process_ortho_projection(struct GraphNodeOrthoProjection *node) {
    if (node->node.children != NULL) {
        Mtx *mtx = alloc_display_list(sizeof(*mtx));
        if (mtx == NULL) { return; }
        f32 left   = ((gCurGraphNodeRoot->x - gCurGraphNodeRoot->width)  / 2.0f) * node->scale;
        f32 right  = ((gCurGraphNodeRoot->x + gCurGraphNodeRoot->width)  / 2.0f) * node->scale;
        f32 top    = ((gCurGraphNodeRoot->y - gCurGraphNodeRoot->height) / 2.0f) * node->scale;
        f32 bottom = ((gCurGraphNodeRoot->y + gCurGraphNodeRoot->height) / 2.0f) * node->scale;

        guOrtho(mtx, left, right, bottom, top, -2.0f, 2.0f, 1.0f);
        gSPPerspNormalize(gDisplayListHead++, 0xFFFF);
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a perspective projection node.
 */
static void geo_process_perspective(struct GraphNodePerspective *node) {
    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->fnNode.node.children == NULL) { return; }

    u16 perspNorm;
    Mtx *mtx = alloc_display_list(sizeof(*mtx));
    if (mtx == NULL) { return; }

    f32 divisor = (f32) gCurGraphNodeRoot->height;
    if (divisor == 0) { divisor = 1; }
#ifdef VERSION_EU
    f32 aspect = ((f32) gCurGraphNodeRoot->width / divisor) * 1.1f;
#else
    f32 aspect = (f32) gCurGraphNodeRoot->width / divisor;
#endif

    gProjectionVanillaNearValue = node->near;
    gProjectionVanillaFarValue = node->far;
    f32 near = MIN(node->near, gProjectionMaxNearValue);
    guPerspective(mtx, &perspNorm, node->prevFov, aspect, get_first_person_enabled() ? 1 : not_zero(near, gOverrideNear), not_zero(node->far, gOverrideFar), 1.0f);

    sPerspectiveNode = node;
    sPerspectiveMtx = mtx;
    sPerspectivePos = gDisplayListHead;
    sPerspectiveAspect = aspect;

    gSPPerspNormalize(gDisplayListHead++, perspNorm);
    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(mtx), G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);

    gCurGraphNodeCamFrustum = node;
    geo_process_node_and_siblings(node->fnNode.node.children);
    gCurGraphNodeCamFrustum = NULL;
}

/**
 * Process a level of detail node. From the current transformation matrix,
 * the perpendicular distance to the camera is extracted and the children
 * of this node are only processed if that distance is within the render
 * range of this node.
 */
static void geo_process_level_of_detail(struct GraphNodeLevelOfDetail *node) {
    // We assume modern hardware is powerful enough to draw the most detailed variant
    s16 distanceFromCam = 0;

    if (node->minDistance <= distanceFromCam && distanceFromCam < node->maxDistance) {
        if (node->node.children != 0) {
            geo_process_node_and_siblings(node->node.children);
        }
    }
}

/**
 * Process a switch case node. The node's selection function is called
 * if it is 0, and among the node's children, only the selected child is
 * processed next.
 */
static void geo_process_switch(struct GraphNodeSwitchCase *node) {
    struct GraphNode *selectedChild = node->fnNode.node.children;

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    for (s32 i = 0; selectedChild != NULL && node->selectedCase > i; i++) {
        selectedChild = selectedChild->next;
    }
    if (selectedChild != NULL) {
        geo_process_node_and_siblings(selectedChild);
    }
}

/**
 * Process a camera node.
 */
static void geo_process_camera(struct GraphNodeCamera *node) {
    Mat4 cameraTransform;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    Mtx *rollMtx = alloc_display_list(sizeof(*rollMtx));
    if (rollMtx == NULL) { return; }

    vec3f_copy(node->prevPos, node->pos);
    vec3f_copy(node->prevFocus, node->focus);

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    mtxf_rotate_xy(rollMtx, node->rollScreen);

    gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(rollMtx), G_MTX_PROJECTION | G_MTX_MUL | G_MTX_NOPUSH);

    mtxf_lookat(cameraTransform, node->pos, node->focus, node->roll);
    mtxf_mul(gMatStack[gMatStackIndex + 1], cameraTransform, gMatStack[gMatStackIndex]);

    if (gCamSkipInterp) {
        // apply prevpos camera offset
        vec3f_copy(node->prevPos, node->pos);
        vec3f_add(node->prevPos, gCamSkipInterpDisplacement);
        vec3f_copy(node->prevFocus, node->focus);
        vec3f_add(node->prevFocus, gCamSkipInterpDisplacement);
    }

    // save prevpos camera offset
    vec3f_copy(gCamSkipInterpDisplacement, node->prevPos);
    vec3f_sub(gCamSkipInterpDisplacement, node->pos);

    if (gGlobalTimer == node->prevTimestamp + 1 && gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
        mtxf_lookat(cameraTransform, node->prevPos, node->prevFocus, node->roll);
        mtxf_mul(gMatStackPrev[gMatStackIndex + 1], cameraTransform, gMatStackPrev[gMatStackIndex]);
    } else {
        mtxf_lookat(cameraTransform, node->pos, node->focus, node->roll);
        mtxf_mul(gMatStackPrev[gMatStackIndex + 1], cameraTransform, gMatStackPrev[gMatStackIndex]);
    }
    node->prevTimestamp = gGlobalTimer;
    sCameraNode = node;

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    // save the camera matrix
    if (gCamera) {
        mtxf_copy(gCamera->mtx, gMatStack[gMatStackIndex]);
    }

    if (node->fnNode.node.children != 0) {
        gCurGraphNodeCamera = node;
        sUsingCamSpace = TRUE;
        node->matrixPtr = &gMatStack[gMatStackIndex];
        node->matrixPtrPrev = &gMatStackPrev[gMatStackIndex];
        geo_process_node_and_siblings(node->fnNode.node.children);
        gCurGraphNodeCamera = NULL;
        sUsingCamSpace = FALSE;
    }
    gMatStackIndex--;
}

/**
 * Process a translation / rotation node. A transformation matrix based
 * on the node's translation and rotation is created and pushed on both
 * the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_translation_rotation(struct GraphNodeTranslationRotation *node) {
    Mat4 mtxf;
    Vec3f translation;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
    mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, gMatStackPrev[gMatStackIndex]);

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process a translation node. A transformation matrix based on the node's
 * translation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_translation(struct GraphNodeTranslation *node) {
    Mat4 mtxf;
    Vec3f translation;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    vec3s_to_vec3f(translation, node->translation);
    mtxf_rotate_zxy_and_translate(mtxf, translation, gVec3sZero);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
    mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, gMatStackPrev[gMatStackIndex]);

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process a rotation node. A transformation matrix based on the node's
 * rotation is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_rotation(struct GraphNodeRotation *node) {
    Mat4 mtxf;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, node->rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);

    if (gGlobalTimer == node->prevTimestamp + 1) {
        mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, node->prevRotation);
    } else {
        mtxf_rotate_zxy_and_translate(mtxf, gVec3fZero, node->rotation);
    }
    mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, gMatStackPrev[gMatStackIndex]);
    vec3s_copy(node->prevRotation, node->rotation);
    node->prevTimestamp = gGlobalTimer;

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process a scaling node. A transformation matrix based on the node's
 * scale is created and pushed on both the float and fixed point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_scale(struct GraphNodeScale *node) {
    Vec3f scaleVec;
    Vec3f prevScaleVec;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    vec3f_set(scaleVec, node->scale, node->scale, node->scale);
    mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], scaleVec);

    /* TODO: this fails because multiple player models reuse the same scalenode
    vec3f_set(prevScaleVec, node->prevScale, node->prevScale, node->prevScale);
    mtxf_scale_vec3f(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex], prevScaleVec);
    node->prevScale = node->scale;*/

    // just use the current scale for now
    vec3f_set(prevScaleVec, node->scale, node->scale, node->scale);
    mtxf_scale_vec3f(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex], scaleVec);

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process a billboard node. A transformation matrix is created that makes its
 * children face the camera, and it is pushed on the floating point and fixed
 * point matrix stacks.
 * For the rest it acts as a normal display list node.
 */
static void geo_process_billboard(struct GraphNodeBillboard *node) {
    Vec3f translation;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    s16 nextMatStackIndex = gMatStackIndex + 1;

    vec3s_to_vec3f(translation, node->translation);
    mtxf_billboard(gMatStack[nextMatStackIndex], gMatStack[gMatStackIndex], translation,
                   gCurGraphNodeCamera->roll);
    mtxf_billboard(gMatStackPrev[nextMatStackIndex], gMatStackPrev[gMatStackIndex], translation,
                   gCurGraphNodeCamera->roll);
    if (gCurGraphNodeHeldObject != NULL) {
        mtxf_scale_vec3f(gMatStack[nextMatStackIndex], gMatStack[nextMatStackIndex],
                         gCurGraphNodeHeldObject->objNode->header.gfx.scale);
        mtxf_scale_vec3f(gMatStackPrev[nextMatStackIndex], gMatStackPrev[nextMatStackIndex],
                         gCurGraphNodeHeldObject->objNode->header.gfx.scale);
    } else if (gCurGraphNodeObject != NULL) {
        mtxf_scale_vec3f(gMatStack[nextMatStackIndex], gMatStack[nextMatStackIndex],
                         gCurGraphNodeObject->scale);
        mtxf_scale_vec3f(gMatStackPrev[nextMatStackIndex], gMatStackPrev[nextMatStackIndex],
                         gCurGraphNodeObject->scale);
    } else {
        //LOG_ERROR("gCurGraphNodeObject and gCurGraphNodeHeldObject are both NULL!");
    }

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Process a display list node. It draws a display list without first pushing
 * a transformation on the stack, so all transformations are inherited from the
 * parent node. It processes its children if it has them.
 */
static void geo_process_display_list(struct GraphNodeDisplayList *node) {
    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a generated list. Instead of storing a pointer to a display list,
 * the list is generated on the fly by a function.
 */
static void geo_process_generated_list(struct GraphNodeGenerated *node) {
    if (node->fnNode.func != NULL) {
        Gfx *list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);

        if (list != NULL) {
            geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), node->fnNode.node.flags >> 8);
        }
    }
    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

/**
 * Process a background node. Tries to retrieve a background display list from
 * the function of the node. If that function is null or returns null, a black
 * rectangle is drawn instead.
 */
static void geo_process_background(struct GraphNodeBackground *node) {
    Gfx *list = NULL;

    if (node->fnNode.func != NULL) {
        Vec3f posCopy;
        Vec3f focusCopy;

        vec3f_copy(posCopy, gLakituState.pos);
        vec3f_copy(focusCopy, gLakituState.focus);
        if (gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
            vec3f_copy(gLakituState.pos, node->prevCameraPos);
            vec3f_copy(gLakituState.focus, node->prevCameraFocus);
            sBackgroundNode = node;
            sBackgroundNodeRoot = gCurGraphNodeRoot;
        }
        list = node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, NULL);
        vec3f_copy(gLakituState.pos, posCopy);
        vec3f_copy(gLakituState.focus, focusCopy);
    }

    if (list != NULL) {
        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(list), node->fnNode.node.flags >> 8);
    } else if (gCurGraphNodeMasterList != NULL) {
#ifndef F3DEX_GBI_2E
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 7);
#else
        Gfx *gfxStart = alloc_display_list(sizeof(Gfx) * 8);
#endif
        Gfx *gfx = gfxStart;
        if (gfx == NULL) { return; }

        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_FILL);
        gDPSetFillColor(gfx++, node->background);
        gDPFillRectangle(gfx++, GFX_DIMENSIONS_RECT_FROM_LEFT_EDGE(0), BORDER_HEIGHT,
        GFX_DIMENSIONS_RECT_FROM_RIGHT_EDGE(0) - 1, SCREEN_HEIGHT - BORDER_HEIGHT - 1);
        gDPPipeSync(gfx++);
        gDPSetCycleType(gfx++, G_CYC_1CYCLE);
        gSPEndDisplayList(gfx++);
        gReadOnlyBackground = -1;

        geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(gfxStart), 0);
    }
    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

static void anim_process(Vec3f translation, Vec3s rotation, u8 *animType, s16 animFrame, u16 **animAttribute) {
    if (*animType == ANIM_TYPE_TRANSLATION) {
        translation[0] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
        translation[1] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
        translation[2] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
        *animType = ANIM_TYPE_ROTATION;
    } else {
        if (*animType == ANIM_TYPE_LATERAL_TRANSLATION) {
            translation[0] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
            *animAttribute += 2;
            translation[2] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
            *animType = ANIM_TYPE_ROTATION;
        } else {
            if (*animType == ANIM_TYPE_VERTICAL_TRANSLATION) {
                *animAttribute += 2;
                translation[1] += retrieve_animation_value(gCurAnim, animFrame, animAttribute) * gCurAnimTranslationMultiplier;
                *animAttribute += 2;
                *animType = ANIM_TYPE_ROTATION;
            } else if (*animType == ANIM_TYPE_NO_TRANSLATION) {
                *animAttribute += 6;
                *animType = ANIM_TYPE_ROTATION;
            }
        }
    }

    if (*animType == ANIM_TYPE_ROTATION) {
        rotation[0] = retrieve_animation_value(gCurAnim, animFrame, animAttribute);
        rotation[1] = retrieve_animation_value(gCurAnim, animFrame, animAttribute);
        rotation[2] = retrieve_animation_value(gCurAnim, animFrame, animAttribute);
    }
}

/**
 * Render an animated part. The current animation state is not part of the node
 * but set in global variables. If an animated part is skipped, everything afterwards desyncs.
 */
static void geo_process_animated_part(struct GraphNodeAnimatedPart *node) {
    Mat4 matrix;
    Vec3s rotation;
    Vec3f translation;
    Vec3s rotationPrev;
    Vec3f translationPrev;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    u16 *animAttribute = gCurrAnimAttribute;
    u8 animType = gCurAnimType;

    vec3s_copy(rotation, gVec3sZero);
    vec3f_set(translation, node->translation[0], node->translation[1], node->translation[2]);

    vec3s_copy(rotationPrev, rotation);
    vec3f_copy(translationPrev, translation);

    anim_process(translationPrev, rotationPrev, &animType, gPrevAnimFrame, &animAttribute);
    anim_process(translation, rotation, &gCurAnimType, gCurrAnimFrame, &gCurrAnimAttribute);

    mtxf_rotate_xyz_and_translate(matrix, translation, rotation);
    mtxf_mul(gMatStack[gMatStackIndex + 1], matrix, gMatStack[gMatStackIndex]);

    mtxf_rotate_xyz_and_translate(matrix, translationPrev, rotationPrev);
    mtxf_mul(gMatStackPrev[gMatStackIndex + 1], matrix, gMatStackPrev[gMatStackIndex]);

    // Increment the matrix stack, If we fail to do so. Just return.
    if (!increment_mat_stack()) { return; }

    if (gCurGraphNodeMarioState != NULL) {
        Vec3f translated = { 0 };
        get_pos_from_transform_mtx(translated, gMatStack[gMatStackIndex], *gCurGraphNodeCamera->matrixPtr);
        gCurGraphNodeMarioState->minimumBoneY = fmin(gCurGraphNodeMarioState->minimumBoneY, translated[1] - gCurGraphNodeMarioState->marioObj->header.gfx.pos[1]);
    }
    if (node->displayList != NULL) {
        geo_append_display_list(node->displayList, node->node.flags >> 8);
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
    gMatStackIndex--;
}

/**
 * Initialize the animation-related global variables for the currently drawn
 * object's animation.
 */
void geo_set_animation_globals(struct AnimInfo *node, s32 hasAnimation) {
    struct Animation *anim = node->curAnim;

    if (hasAnimation) {
        node->animFrame = geo_update_animation_frame(node, &node->animFrameAccelAssist);
    }
    node->animTimer = gAreaUpdateCounter;
    if (anim->flags & ANIM_FLAG_HOR_TRANS) {
        gCurAnimType = ANIM_TYPE_VERTICAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_VERT_TRANS) {
        gCurAnimType = ANIM_TYPE_LATERAL_TRANSLATION;
    } else if (anim->flags & ANIM_FLAG_6) {
        gCurAnimType = ANIM_TYPE_NO_TRANSLATION;
    } else {
        gCurAnimType = ANIM_TYPE_TRANSLATION;
    }

    gCurrAnimFrame = node->animFrame;
    if (node->prevAnimPtr == anim && node->prevAnimID == node->animID &&
        gGlobalTimer == node->prevAnimFrameTimestamp + 1) {
        gPrevAnimFrame = node->prevAnimFrame;
    } else {
        gPrevAnimFrame = node->animFrame;
    }
    node->prevAnimPtr = anim;
    node->prevAnimID = node->animID;
    node->prevAnimFrame = node->animFrame;
    node->prevAnimFrameTimestamp = gGlobalTimer;

    gCurAnimEnabled = (anim->flags & ANIM_FLAG_5) == 0;
    gCurrAnimAttribute = segmented_to_virtual((void *) anim->index);
    gCurAnim = anim;

    if (anim->animYTransDivisor == 0) {
        gCurAnimTranslationMultiplier = 1.0f;
    } else {
        gCurAnimTranslationMultiplier = (f32) node->animYTrans / (f32) anim->animYTransDivisor;
    }
}

/**
 * Process a shadow node. Renders a shadow under an object offset by the
 * translation of the first animated component and rotated according to
 * the floor below it.
 */
static void geo_process_shadow(struct GraphNodeShadow *node) {
    Mat4 mtxf;
    Vec3f shadowPosPrev;
    Vec3f animOffset;
    f32 shadowScale;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    if (gCurGraphNodeCamera != NULL && gCurGraphNodeObject != NULL) {
        if (gCurGraphNodeHeldObject != NULL) {
            get_pos_from_transform_mtx(gCurGraphNodeObject->shadowPos, gMatStack[gMatStackIndex],
                                       *gCurGraphNodeCamera->matrixPtr);
            shadowScale = node->shadowScale;
        } else {
            if (!gCurGraphNodeObject->disableAutomaticShadowPos) {
                vec3f_copy(gCurGraphNodeObject->shadowPos, gCurGraphNodeObject->pos);
            }
            shadowScale = node->shadowScale * gCurGraphNodeObject->scale[0];
        }

        f32 objScale = 1.0f;
        if (gCurAnimEnabled) {
            if (gCurAnimType == ANIM_TYPE_TRANSLATION
                || gCurAnimType == ANIM_TYPE_LATERAL_TRANSLATION) {
                struct GraphNode *geo = node->node.children;
                if (geo != NULL && geo->type == GRAPH_NODE_TYPE_SCALE) {
                    objScale = ((struct GraphNodeScale *) geo)->scale;
                }
                animOffset[0] = retrieve_animation_value(gCurAnim, gCurrAnimFrame, &gCurrAnimAttribute) * gCurAnimTranslationMultiplier * objScale;
                animOffset[1] = 0.0f;
                gCurrAnimAttribute += 2;
                animOffset[2] = retrieve_animation_value(gCurAnim, gCurrAnimFrame, &gCurrAnimAttribute) * gCurAnimTranslationMultiplier * objScale;
                gCurrAnimAttribute -= 6;

                // simple matrix rotation so the shadow offset rotates along with the object
                f32 sinAng = sins(gCurGraphNodeObject->angle[1]);
                f32 cosAng = coss(gCurGraphNodeObject->angle[1]);

                gCurGraphNodeObject->shadowPos[0] += animOffset[0] * cosAng + animOffset[2] * sinAng;
                gCurGraphNodeObject->shadowPos[2] += -animOffset[0] * sinAng + animOffset[2] * cosAng;
            }
        }

        if (gCurGraphNodeHeldObject != NULL) {

            if (gGlobalTimer == gCurGraphNodeHeldObject->prevShadowPosTimestamp + 1) {
                vec3f_copy(shadowPosPrev, gCurGraphNodeHeldObject->prevShadowPos);
            } else {
                vec3f_copy(shadowPosPrev, gCurGraphNodeObject->shadowPos);
            }

            vec3f_copy(gCurGraphNodeHeldObject->prevShadowPos, gCurGraphNodeObject->shadowPos);
            gCurGraphNodeHeldObject->prevShadowPosTimestamp = gGlobalTimer;
        } else {
            if (gGlobalTimer == gCurGraphNodeObject->prevShadowPosTimestamp + 1 &&
                gGlobalTimer != gCurGraphNodeObject->skipInterpolationTimestamp &&
                gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
                vec3f_copy(shadowPosPrev, gCurGraphNodeObject->prevShadowPos);
            } else {
                vec3f_copy(shadowPosPrev, gCurGraphNodeObject->shadowPos);
            }
            vec3f_copy(gCurGraphNodeObject->prevShadowPos, gCurGraphNodeObject->shadowPos);
            gCurGraphNodeObject->prevShadowPosTimestamp = gGlobalTimer;
        }

        if (sShadowInterpCount < MAX_SHADOW_NODES) {
            struct ShadowInterp* interp = &sShadowInterp[sShadowInterpCount++];
            gShadowInterpCurrent = interp;
            interp->gfx = NULL;
            interp->node = node;
            interp->shadowScale = shadowScale;
            interp->obj = gCurGraphNodeObject;
            vec3f_copy(interp->shadowPos, gCurGraphNodeObject->shadowPos);
            vec3f_copy(interp->shadowPosPrev, shadowPosPrev);
        } else {
            gShadowInterpCurrent = NULL;
        }

        Gfx *shadowListPrev = create_shadow_below_xyz(shadowPosPrev[0], shadowPosPrev[1],
                                                      shadowPosPrev[2], shadowScale,
                                                      node->shadowSolidity, node->shadowType);

        if (gShadowInterpCurrent != NULL) {
            gShadowInterpCurrent->gfx = shadowListPrev;
        }

        if (gCurGraphNodeObject->shadowInvisible || (gCurGraphNodeObject == &gMarioState->marioObj->header.gfx && get_first_person_enabled())) {
            shadowListPrev = NULL;
        }

        if (shadowListPrev != NULL) {
            mtxf_translate(mtxf, gCurGraphNodeObject->shadowPos);
            mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, *gCurGraphNodeCamera->matrixPtr);
            mtxf_translate(mtxf, shadowPosPrev);
            mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, *gCurGraphNodeCamera->matrixPtrPrev);

            // Increment the matrix stack, If we fail to do so. Just return.
            if (!increment_mat_stack()) { return; }

            if (gShadowAboveWaterOrLava == TRUE) {
                geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(shadowListPrev), 4);
            } else if (gMarioOnIceOrCarpet == TRUE) {
                geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(shadowListPrev), 5);
            } else {
                geo_append_display_list((void *) VIRTUAL_TO_PHYSICAL(shadowListPrev), 6);
            }
            gMatStackIndex--;
        }
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Check whether an object is in view to determine whether it should be drawn.
 * This is known as frustum culling.
 * It checks whether the object is far away, very close / behind the camera,
 * or horizontally out of view. It does not check whether it is vertically
 * out of view. It assumes a sphere of 300 units around the object's position
 * unless the object has a culling radius node that specifies otherwise.
 *
 * The matrix parameter should be the top of the matrix stack, which is the
 * object's transformation matrix times the camera 'look-at' matrix. The math
 * is counter-intuitive, but it checks column 3 (translation vector) of this
 * matrix to determine where the origin (0,0,0) in object space will be once
 * transformed to camera space (x+ = right, y+ = up, z = 'coming out the screen').
 * In 3D graphics, you typically model the world as being moved in front of a
 * static camera instead of a moving camera through a static world, which in
 * this case simplifies calculations. Note that the perspective matrix is not
 * on the matrix stack, so there are still calculations with the fov to compute
 * the slope of the lines of the frustum.
 *
 *        z-
 *
 *  \     |     /
 *   \    |    /
 *    \   |   /
 *     \  |  /
 *      \ | /
 *       \|/
 *        C       x+
 *
 * Since (0,0,0) is unaffected by rotation, columns 0, 1 and 2 are ignored.
 */
static s32 obj_is_in_view(struct GraphNodeObject *node, Mat4 matrix) {
    if (!node || !gCurGraphNodeCamFrustum) { return FALSE; }

    if (node->node.flags & GRAPH_RENDER_INVISIBLE) {
        return FALSE;
    } else if (node->skipInViewCheck) {
        return TRUE;
    }

    // ! @bug The aspect ratio is not accounted for. When the fov value is 45,
    // the horizontal effective fov is actually 60 degrees, so you can see objects
    // visibly pop in or out at the edge of the screen.
    //
    // Half of the fov in in-game angle units instead of degrees.
    s16 halfFov = (gCurGraphNodeCamFrustum->fov / 2.0f + 1.0f) * 32768.0f / 180.0f + 0.5f;

    f32 divisor = coss(halfFov);
    if (divisor == 0) { divisor = 1; }
    f32 hScreenEdge = -matrix[3][2] * sins(halfFov) / divisor;
    // -matrix[3][2] is the depth, which gets multiplied by tan(halfFov) to get
    // the amount of units between the center of the screen and the horizontal edge
    // given the distance from the object to the camera.

    // This multiplication should really be performed on 4:3 as well,
    // but the issue will be more apparent on widescreen.
    hScreenEdge *= GFX_DIMENSIONS_ASPECT_RATIO;

    s16 cullingRadius = 300;
    struct GraphNode *geo = node->sharedChild;
    if (geo != NULL && geo->type == GRAPH_NODE_TYPE_CULLING_RADIUS) {
        cullingRadius = (f32)((struct GraphNodeCullingRadius *) geo)->cullingRadius; //! Why is there a f32 cast?
    }

    // Don't render if the object is close to or behind the camera
    if (matrix[3][2] > -100.0f + cullingRadius) {
        return FALSE;
    }

    //! This makes the HOLP not update when the camera is far away, and it
    //  makes PU travel safe when the camera is locked on the main map.
    //  If Mario were rendered with a depth over 65536 it would cause overflow
    //  when converting the transformation matrix to a fixed point matrix.
    if (matrix[3][2] < -20000.0f - cullingRadius) {
        return FALSE;
    }

    // Check whether the object is horizontally in view
    if (matrix[3][0] > hScreenEdge + cullingRadius) {
        return FALSE;
    }
    if (matrix[3][0] < -hScreenEdge - cullingRadius) {
        return FALSE;
    }
    return TRUE;
}

static void geo_sanitize_object_gfx() {
    geo_append_display_list(obj_sanitize_gfx, LAYER_OPAQUE);
    geo_append_display_list(obj_sanitize_gfx, LAYER_ALPHA);
    geo_append_display_list(obj_sanitize_gfx, LAYER_TRANSPARENT);
}

/**
 * Process an object node.
 */
static void geo_process_object(struct Object *node) {
    struct Object* lastProcessingObject = gCurGraphNodeProcessingObject;
    struct MarioState* lastMarioState = gCurGraphNodeMarioState;
    gCurGraphNodeProcessingObject = node;
    Mat4 mtxf;
    s32 hasAnimation = (node->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0;
    Vec3f scalePrev;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

    if (!node->header.gfx.inited) {
        node->header.gfx.inited = true;
        obj_update_gfx_pos_and_angle(node);
        vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
        vec3s_copy(node->header.gfx.prevAngle, node->header.gfx.angle);
    }

    if (node->hookRender) {
        smlua_call_event_hooks_object_param(HOOK_ON_OBJECT_RENDER, node);
    }

    if (node->header.gfx.node.flags & GRAPH_RENDER_PLAYER) {
        gCurGraphNodeMarioState = NULL;
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (gMarioStates[i].marioObj == node) {
                gCurGraphNodeMarioState = &gMarioStates[i];
                break;
            }
        }
        if (gCurGraphNodeMarioState != NULL) {
            gCurGraphNodeMarioState->minimumBoneY = 9999;
        }
    }

    bool noBillboard = (node->header.gfx.sharedChild && node->header.gfx.sharedChild->extraFlags & GRAPH_EXTRA_FORCE_3D);
    if (node->header.gfx.areaIndex == gCurGraphNodeRoot->areaIndex) {
        if (node->header.gfx.throwMatrix != NULL) {

            mtxf_mul(gMatStack[gMatStackIndex + 1], *node->header.gfx.throwMatrix,
                     gMatStack[gMatStackIndex]);

            if (gGlobalTimer == node->header.gfx.prevThrowMatrixTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp &&
                gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
                mtxf_copy(mtxf, node->header.gfx.prevThrowMatrix);
                mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, gMatStackPrev[gMatStackIndex]);
            } else {
                mtxf_mul(gMatStackPrev[gMatStackIndex + 1], (void *) node->header.gfx.throwMatrix, gMatStackPrev[gMatStackIndex]);
            }

            mtxf_copy(node->header.gfx.prevThrowMatrix, *node->header.gfx.throwMatrix);
            node->header.gfx.prevThrowMatrixTimestamp = gGlobalTimer;

        } else if (node->header.gfx.node.flags & GRAPH_RENDER_CYLBOARD && !noBillboard) {

            Vec3f posPrev;

            if (gGlobalTimer == node->header.gfx.prevTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp &&
                gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
                vec3f_copy(posPrev, node->header.gfx.prevPos);
            } else {
                vec3f_copy(posPrev, node->header.gfx.pos);
            }

            vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
            node->header.gfx.prevTimestamp = gGlobalTimer;
            mtxf_cylboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], node->header.gfx.pos, gCurGraphNodeCamera->roll);
            mtxf_cylboard(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex], posPrev, gCurGraphNodeCamera->roll);

        } else if (node->header.gfx.node.flags & GRAPH_RENDER_BILLBOARD && !noBillboard) {

            Vec3f posPrev;

            if (gGlobalTimer == node->header.gfx.prevTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp &&
                gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
                vec3f_copy(posPrev, node->header.gfx.prevPos);
            } else {
                vec3f_copy(posPrev, node->header.gfx.pos);
            }

            vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
            node->header.gfx.prevTimestamp = gGlobalTimer;
            mtxf_billboard(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex], node->header.gfx.pos, gCurGraphNodeCamera->roll);
            mtxf_billboard(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex], posPrev, gCurGraphNodeCamera->roll);

        } else {

            Vec3f posPrev;
            Vec3s anglePrev;

            if (gGlobalTimer == node->header.gfx.prevTimestamp + 1 &&
                gGlobalTimer != node->header.gfx.skipInterpolationTimestamp &&
                gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
                vec3f_copy(posPrev, node->header.gfx.prevPos);
                vec3s_copy(anglePrev, node->header.gfx.prevAngle);
            } else {
                vec3f_copy(posPrev, node->header.gfx.pos);
                vec3s_copy(anglePrev, node->header.gfx.angle);
            }

            vec3f_copy(node->header.gfx.prevPos, node->header.gfx.pos);
            vec3s_copy(node->header.gfx.prevAngle, node->header.gfx.angle);
            node->header.gfx.prevTimestamp = gGlobalTimer;
            mtxf_rotate_zxy_and_translate(mtxf, node->header.gfx.pos, node->header.gfx.angle);
            mtxf_mul(gMatStack[gMatStackIndex + 1], mtxf, gMatStack[gMatStackIndex]);
            mtxf_rotate_zxy_and_translate(mtxf, posPrev, anglePrev);
            mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mtxf, gMatStackPrev[gMatStackIndex]);
        }

        if (gGlobalTimer == node->header.gfx.prevScaleTimestamp + 1 &&
            gGlobalTimer != node->header.gfx.skipInterpolationTimestamp &&
            gGlobalTimer != gLakituState.skipCameraInterpolationTimestamp) {
            vec3f_copy(scalePrev, node->header.gfx.prevScale);
        } else {
            vec3f_copy(scalePrev, node->header.gfx.scale);
        }

        vec3f_copy(node->header.gfx.prevScale, node->header.gfx.scale);
        node->header.gfx.prevScaleTimestamp = gGlobalTimer;

        mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1],
                         node->header.gfx.scale);
        mtxf_scale_vec3f(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex + 1],
                         scalePrev);
        node->header.gfx.throwMatrix = &gMatStack[++gMatStackIndex];
        node->header.gfx.throwMatrixPrev = &gMatStackPrev[gMatStackIndex];
        node->header.gfx.cameraToObject[0] = gMatStack[gMatStackIndex][3][0];
        node->header.gfx.cameraToObject[1] = gMatStack[gMatStackIndex][3][1];
        node->header.gfx.cameraToObject[2] = gMatStack[gMatStackIndex][3][2];

        // FIXME: correct types
        if (node->header.gfx.animInfo.curAnim != NULL) {
            dynos_gfx_swap_animations(node);
            geo_set_animation_globals(&node->header.gfx.animInfo, hasAnimation);
            if (node->hookRender) smlua_call_event_hooks_object_param(HOOK_ON_OBJECT_ANIM_UPDATE, node);
            dynos_gfx_swap_animations(node);
        }
        if (obj_is_in_view(&node->header.gfx, gMatStack[gMatStackIndex])) {
            Mtx *mtx = alloc_display_list(sizeof(*mtx));
            Mtx *mtxPrev = alloc_display_list(sizeof(*mtxPrev));
            if (mtx == NULL || mtxPrev == NULL) { return; }

            mtxf_to_mtx(mtx, gMatStack[gMatStackIndex]);
            gMatStackFixed[gMatStackIndex] = mtx;
            mtxf_to_mtx(mtxPrev, gMatStackPrev[gMatStackIndex]);
            gMatStackPrevFixed[gMatStackIndex] = mtxPrev;

            if (node->header.gfx.sharedChild != NULL) {
                gCurGraphNodeObject = (struct GraphNodeObject *) node;
                node->header.gfx.sharedChild->parent = &node->header.gfx.node;
                geo_sanitize_object_gfx();
                geo_process_node_and_siblings(node->header.gfx.sharedChild);
                node->header.gfx.sharedChild->parent = NULL;
                gCurGraphNodeObject = NULL;
            }

            if (node->header.gfx.node.children != NULL) {
                geo_process_node_and_siblings(node->header.gfx.node.children);
            }

        } else {
            node->header.gfx.prevThrowMatrixTimestamp = 0;
            node->header.gfx.prevTimestamp = 0;
            node->header.gfx.prevScaleTimestamp = 0;
        }

        gMatStackIndex--;
        gCurAnimType = ANIM_TYPE_NONE;
        node->header.gfx.throwMatrix = NULL;
        node->header.gfx.throwMatrixPrev = NULL;
    }
    gCurGraphNodeProcessingObject = lastProcessingObject;
    gCurGraphNodeMarioState = lastMarioState;
}

/**
 * Process an object parent node. Temporarily assigns itself as the parent of
 * the subtree rooted at 'sharedChild' and processes the subtree, after which the
 * actual children are be processed. (in practice they are null though)
 */
static void geo_process_object_parent(struct GraphNodeObjectParent *node) {
    if (node->sharedChild != NULL) {
        node->sharedChild->parent = (struct GraphNode *) node;
        geo_process_node_and_siblings(node->sharedChild);
        node->sharedChild->parent = NULL;
    }
    if (node->node.children != NULL) {
        geo_process_node_and_siblings(node->node.children);
    }
}

/**
 * Process a held object node.
 */
void geo_process_held_object(struct GraphNodeHeldObject *node) {
    Mat4 mat;
    Vec3f translation;
    Vec3f scalePrev;

    // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
    if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) { LOG_ERROR("Preventing attempt to exceed the maximum size %i for our matrix stack with size of %i.", MATRIX_STACK_SIZE - 1, gMatStackIndex); return; }

#ifdef F3DEX_GBI_2
    gSPLookAt(gDisplayListHead++, &lookAt);
#endif

    if (node->fnNode.func != NULL) {
        node->fnNode.func(GEO_CONTEXT_RENDER, &node->fnNode.node, gMatStack[gMatStackIndex]);
    }
    if (node->objNode != NULL && node->objNode->header.gfx.sharedChild != NULL) {
        s32 hasAnimation = (node->objNode->header.gfx.node.flags & GRAPH_RENDER_HAS_ANIMATION) != 0;

        translation[0] = node->translation[0] / 4.0f;
        translation[1] = node->translation[1] / 4.0f;
        translation[2] = node->translation[2] / 4.0f;

        if (gGlobalTimer == node->objNode->header.gfx.prevScaleTimestamp + 1) {
            vec3f_copy(scalePrev, node->objNode->header.gfx.prevScale);
        } else {
            vec3f_copy(scalePrev, node->objNode->header.gfx.scale);
        }
        vec3f_copy(node->objNode->header.gfx.prevScale, node->objNode->header.gfx.scale);
        node->objNode->header.gfx.prevScaleTimestamp = gGlobalTimer;

        mtxf_translate(mat, translation);
        mtxf_copy(gMatStack[gMatStackIndex + 1], *gCurGraphNodeObject->throwMatrix);
        gMatStack[gMatStackIndex + 1][3][0] = gMatStack[gMatStackIndex][3][0];
        gMatStack[gMatStackIndex + 1][3][1] = gMatStack[gMatStackIndex][3][1];
        gMatStack[gMatStackIndex + 1][3][2] = gMatStack[gMatStackIndex][3][2];
        mtxf_mul(gMatStack[gMatStackIndex + 1], mat, gMatStack[gMatStackIndex + 1]);
        mtxf_scale_vec3f(gMatStack[gMatStackIndex + 1], gMatStack[gMatStackIndex + 1], node->objNode->header.gfx.scale);
        mtxf_copy(gMatStackPrev[gMatStackIndex + 1], (void *) gCurGraphNodeObject->throwMatrixPrev);
        gMatStackPrev[gMatStackIndex + 1][3][0] = gMatStackPrev[gMatStackIndex][3][0];
        gMatStackPrev[gMatStackIndex + 1][3][1] = gMatStackPrev[gMatStackIndex][3][1];
        gMatStackPrev[gMatStackIndex + 1][3][2] = gMatStackPrev[gMatStackIndex][3][2];
        mtxf_mul(gMatStackPrev[gMatStackIndex + 1], mat, gMatStackPrev[gMatStackIndex + 1]);
        mtxf_scale_vec3f(gMatStackPrev[gMatStackIndex + 1], gMatStackPrev[gMatStackIndex + 1],
                         scalePrev);

        if (node->fnNode.func != NULL) {
            node->fnNode.func(GEO_CONTEXT_HELD_OBJ, &node->fnNode.node, (struct DynamicPool *) gMatStack[gMatStackIndex + 1]);
        }

        // Increment the matrix stack, If we fail to do so. Just return.
        if (!increment_mat_stack()) { return; }

        gGeoTempState.type = gCurAnimType;
        gGeoTempState.enabled = gCurAnimEnabled;
        gGeoTempState.frame = gCurrAnimFrame;
        gGeoTempState.translationMultiplier = gCurAnimTranslationMultiplier;
        gGeoTempState.attribute = gCurrAnimAttribute;
        gGeoTempState.anim = gCurAnim;
        gGeoTempState.prevFrame = gPrevAnimFrame;
        gCurAnimType = 0;
        gCurGraphNodeHeldObject = (void *) node;
        if (node->objNode->header.gfx.animInfo.curAnim != NULL) {
            dynos_gfx_swap_animations(node->objNode);
            geo_set_animation_globals(&node->objNode->header.gfx.animInfo, hasAnimation);
            if (node->objNode->hookRender) smlua_call_event_hooks_object_param(HOOK_ON_OBJECT_ANIM_UPDATE, node->objNode);
            dynos_gfx_swap_animations(node->objNode);
        }

        geo_sanitize_object_gfx();
        geo_process_node_and_siblings(node->objNode->header.gfx.sharedChild);
        gCurGraphNodeHeldObject = NULL;
        gCurAnimType = gGeoTempState.type;
        gCurAnimEnabled = gGeoTempState.enabled;
        gCurrAnimFrame = gGeoTempState.frame;
        gCurAnimTranslationMultiplier = gGeoTempState.translationMultiplier;
        gCurrAnimAttribute = gGeoTempState.attribute;
        gCurAnim = gGeoTempState.anim;
        gPrevAnimFrame = gGeoTempState.prevFrame;
        gMatStackIndex--;
    }

    if (node->fnNode.node.children != NULL) {
        geo_process_node_and_siblings(node->fnNode.node.children);
    }
}

/**
 * Processes the children of the given GraphNode if it has any
 */
void geo_try_process_children(struct GraphNode *node) {
    if (node->children != NULL) {
        geo_process_node_and_siblings(node->children);
    }
}

#define MAX_GRAPH_NODE_DEPTH 5000
/**
 * Process a generic geo node and its siblings.
 * The first argument is the start node, and all its siblings will
 * be iterated over.
 */
void geo_process_node_and_siblings(struct GraphNode *firstNode) {
    s16 iterateChildren = TRUE;
    struct GraphNode *curGraphNode = firstNode;
    if (curGraphNode == NULL) { return; }
    u32 depthSanity = 0;

    struct GraphNode *parent = curGraphNode->parent;

    // In the case of a switch node, exactly one of the children of the node is
    // processed instead of all children like usual
    if (parent != NULL) {
        iterateChildren = (parent->type != GRAPH_NODE_TYPE_SWITCH_CASE);

        if (parent->hookProcess) smlua_call_event_hooks_graph_node_and_int_param(HOOK_ON_GEO_PROCESS_CHILDREN, parent, gMatStackIndex);
    }

    do {
        if (curGraphNode == NULL) {
            LOG_ERROR("Graph Node null!");
            break;
        }

        if (curGraphNode->_guard1 != GRAPH_NODE_GUARD || curGraphNode->_guard2 != GRAPH_NODE_GUARD) {
            LOG_ERROR("Graph Node corrupted!");
            break;
        }

        // Sanity check our stack index, If we above or equal to our stack size. Return to prevent OOB\.
        if ((gMatStackIndex + 1) >= MATRIX_STACK_SIZE) {
            LOG_ERROR("Graph Node matrix stack overflow!");
            break;
        }

        // Break out of endless loops
        if (++depthSanity > MAX_GRAPH_NODE_DEPTH) {
            LOG_ERROR("Graph Node too deep!");
            break;
        }

        if (curGraphNode->flags & GRAPH_RENDER_ACTIVE) {
            if (curGraphNode->hookProcess) smlua_call_event_hooks_graph_node_and_int_param(HOOK_BEFORE_GEO_PROCESS, curGraphNode, gMatStackIndex);
            if (curGraphNode->flags & GRAPH_RENDER_CHILDREN_FIRST) {
                geo_try_process_children(curGraphNode);
            } else {
                switch (curGraphNode->type) {
                    case GRAPH_NODE_TYPE_ORTHO_PROJECTION:
                        geo_process_ortho_projection((struct GraphNodeOrthoProjection *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_PERSPECTIVE:
                        geo_process_perspective((struct GraphNodePerspective *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_MASTER_LIST:
                        geo_process_master_list((struct GraphNodeMasterList *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_LEVEL_OF_DETAIL:
                        geo_process_level_of_detail((struct GraphNodeLevelOfDetail *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_SWITCH_CASE:
                        geo_process_switch((struct GraphNodeSwitchCase *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_CAMERA:
                        geo_process_camera((struct GraphNodeCamera *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_TRANSLATION_ROTATION:
                        geo_process_translation_rotation(
                            (struct GraphNodeTranslationRotation *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_TRANSLATION:
                        geo_process_translation((struct GraphNodeTranslation *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_ROTATION:
                        geo_process_rotation((struct GraphNodeRotation *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_OBJECT:
                        geo_process_object((struct Object *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_ANIMATED_PART:
                        geo_process_animated_part((struct GraphNodeAnimatedPart *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_BILLBOARD:
                        geo_process_billboard((struct GraphNodeBillboard *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_DISPLAY_LIST:
                        geo_process_display_list((struct GraphNodeDisplayList *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_SCALE:
                        geo_process_scale((struct GraphNodeScale *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_SHADOW:
                        geo_process_shadow((struct GraphNodeShadow *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_OBJECT_PARENT:
                        geo_process_object_parent((struct GraphNodeObjectParent *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_GENERATED_LIST:
                        geo_process_generated_list((struct GraphNodeGenerated *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_BACKGROUND:
                        geo_process_background((struct GraphNodeBackground *) curGraphNode);
                        break;
                    case GRAPH_NODE_TYPE_HELD_OBJ:
                        geo_process_held_object((struct GraphNodeHeldObject *) curGraphNode);
                        break;
                    default:
                        geo_try_process_children((struct GraphNode *) curGraphNode);
                        break;
                }
            }
            if (curGraphNode->hookProcess) smlua_call_event_hooks_graph_node_and_int_param(HOOK_ON_GEO_PROCESS, curGraphNode, gMatStackIndex + 1);
        } else {
            if (curGraphNode && curGraphNode->type == GRAPH_NODE_TYPE_OBJECT) {
                ((struct GraphNodeObject *) curGraphNode)->throwMatrix = NULL;
            }
        }
    } while (iterateChildren && curGraphNode && (curGraphNode = curGraphNode->next) != firstNode);
}

static void geo_clear_interp_variables(void) {
    sPerspectiveNode = NULL;
    sPerspectivePos   = NULL;
    sPerspectiveMtx   = NULL;
    sPerspectiveAspect = 0;

    sViewport        = NULL;
    sViewportPos     = NULL;
    sViewportClipPos = NULL;

    sBackgroundNode = NULL;
    gBackgroundSkyboxGfx = NULL;
    memset(gBackgroundSkyboxVerts, 0, sizeof(Vtx*) * SKYBOX_TILES_Y * SKYBOX_TILES_X);
    gBackgroundSkyboxMtx = NULL;
    sBackgroundNodeRoot = NULL;

    gShadowInterpCurrent = NULL;
    sShadowInterpCount = 0;

    sCameraNode = NULL;
    gMtxTblSize = 0;
    gCurGraphNodeProcessingObject = NULL;
    gCurGraphNodeMarioState = NULL;
}

/**
 * Process a root node. This is the entry point for processing the scene graph.
 * The root node itself sets up the viewport, then all its children are processed
 * to set up the projection and draw display lists.
 */
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor) {
    // clear interp stuff
    geo_clear_interp_variables();

    if (node->node.flags & GRAPH_RENDER_ACTIVE) {
        gDisplayListHeap = growing_pool_init(gDisplayListHeap, DISPLAY_LIST_HEAP_SIZE);

        Vp *viewport = alloc_display_list(sizeof(*viewport));
        if (viewport == NULL) { return; }

        Mtx *initialMatrix = alloc_display_list(sizeof(*initialMatrix));
        if (initialMatrix == NULL) { return; }

        gMatStackIndex = 0;
        gCurAnimType = 0;
        vec3s_set(viewport->vp.vtrans, node->x * 4, node->y * 4, 511);
        vec3s_set(viewport->vp.vscale, node->width * 4, node->height * 4, 511);

        if (b != NULL) {
            clear_frame_buffer(clearColor);

            sViewportClipPos = gDisplayListHead;
            make_viewport_clip_rect(&sViewportPrev);

            *viewport = *b;
        } else if (c != NULL) {
            clear_frame_buffer(clearColor);
            make_viewport_clip_rect(c);
        }

        mtxf_identity(gMatStack[gMatStackIndex]);
        mtxf_to_mtx(initialMatrix, gMatStack[gMatStackIndex]);
        gMatStackFixed[gMatStackIndex] = initialMatrix;

        sViewport = viewport;
        sViewportPos = gDisplayListHead;

        // vvv 60 FPS PATCH vvv
        mtxf_identity(gMatStackPrev[gMatStackIndex]);
        gMatStackPrevFixed[gMatStackIndex] = initialMatrix;
        // ^^^              ^^^

        gSPViewport(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(&sViewportPrev));
        gSPMatrix(gDisplayListHead++, VIRTUAL_TO_PHYSICAL(gMatStackFixed[gMatStackIndex]), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

        gCurGraphNodeRoot = node;
        if (node->node.children != NULL) {
            geo_process_node_and_siblings(node->node.children);
        }

        gCurGraphNodeRoot = NULL;
    }
}