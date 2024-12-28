#ifndef RENDERING_GRAPH_NODE_H
#define RENDERING_GRAPH_NODE_H

#include <PR/ultratypes.h>

#include "engine/graph_node.h"

#define MATRIX_STACK_SIZE 64
extern Mat4 gMatStack[MATRIX_STACK_SIZE];
extern Mat4 gMatStackPrev[MATRIX_STACK_SIZE];

extern f32 gProjectionMaxNearValue;
extern s16 gProjectionVanillaNearValue;
extern s16 gProjectionVanillaFarValue;

extern struct GrowingPool *gDisplayListHeap;
extern struct GraphNodeRoot *gCurGraphNodeRoot;
extern struct GraphNodeMasterList *gCurGraphNodeMasterList;
extern struct GraphNodePerspective *gCurGraphNodeCamFrustum;
extern struct GraphNodeCamera *gCurGraphNodeCamera;
extern struct GraphNodeObject *gCurGraphNodeObject;
extern struct GraphNodeHeldObject *gCurGraphNodeHeldObject;
extern u16 gAreaUpdateCounter;
extern struct Object* gCurGraphNodeProcessingObject;

// after processing an object, the type is reset to this
#define ANIM_TYPE_NONE                  0

// Not all parts have full animation: to save space, some animations only
// have xz, y, or no translation at all. All animations have rotations though
#define ANIM_TYPE_TRANSLATION           1
#define ANIM_TYPE_VERTICAL_TRANSLATION  2
#define ANIM_TYPE_LATERAL_TRANSLATION   3
#define ANIM_TYPE_NO_TRANSLATION        4

// Every animation includes rotation, after processing any of the above
// translation types the type is set to this
#define ANIM_TYPE_ROTATION              5

extern f32 gOverrideFOV;
extern f32 gOverrideNear;
extern f32 gOverrideFar;

void geo_process_node_and_siblings(struct GraphNode *firstNode);
void geo_process_root(struct GraphNodeRoot *node, Vp *b, Vp *c, s32 clearColor);
void interpolate_vectors(Vec3f res, Vec3f a, Vec3f b);
void interpolate_vectors_s16(Vec3s res, Vec3s a, Vec3s b);

struct ShadowInterp {
    Gfx*  gfx;
    Vec3f shadowPos;
    Vec3f shadowPosPrev;
    Vtx *verts;
    Gfx *displayList;
    struct GraphNodeShadow *node;
    f32 shadowScale;
    struct GraphNodeObject *obj;
};

#endif // RENDERING_GRAPH_NODE_H
