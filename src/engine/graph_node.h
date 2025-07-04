#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <PR/ultratypes.h>
#include <PR/gbi.h>

#include "types.h"
#include "game/memory.h"
#undef near
#undef far

#define GRAPH_RENDER_ACTIVE         (1 << 0)
#define GRAPH_RENDER_CHILDREN_FIRST (1 << 1)
#define GRAPH_RENDER_BILLBOARD      (1 << 2)
#define GRAPH_RENDER_Z_BUFFER       (1 << 3)
#define GRAPH_RENDER_INVISIBLE      (1 << 4)
#define GRAPH_RENDER_HAS_ANIMATION  (1 << 5)
#define GRAPH_RENDER_CYLBOARD       (1 << 6)
#define GRAPH_RENDER_PLAYER         (1 << 7)

// Extra, custom, flags
#define GRAPH_EXTRA_FORCE_3D        (1 << 0)

// Whether the node type has a function pointer of type GraphNodeFunc
#define GRAPH_NODE_TYPE_FUNCTIONAL            0x100

// Type used for Bowser and an unused geo function in obj_behaviors.c
#define GRAPH_NODE_TYPE_400                   0x400

// The discriminant for different types of geo nodes
#define GRAPH_NODE_TYPE_ROOT                  0x001
#define GRAPH_NODE_TYPE_ORTHO_PROJECTION      0x002
#define GRAPH_NODE_TYPE_PERSPECTIVE          (0x003 | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_MASTER_LIST           0x004
#define GRAPH_NODE_TYPE_START                 0x00A
#define GRAPH_NODE_TYPE_LEVEL_OF_DETAIL       0x00B
#define GRAPH_NODE_TYPE_SWITCH_CASE          (0x00C | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_CAMERA               (0x014 | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_TRANSLATION_ROTATION  0x015
#define GRAPH_NODE_TYPE_TRANSLATION           0x016
#define GRAPH_NODE_TYPE_ROTATION              0x017
#define GRAPH_NODE_TYPE_OBJECT                0x018
#define GRAPH_NODE_TYPE_ANIMATED_PART         0x019
#define GRAPH_NODE_TYPE_BILLBOARD             0x01A
#define GRAPH_NODE_TYPE_DISPLAY_LIST          0x01B
#define GRAPH_NODE_TYPE_SCALE                 0x01C
#define GRAPH_NODE_TYPE_SHADOW                0x028
#define GRAPH_NODE_TYPE_OBJECT_PARENT         0x029
#define GRAPH_NODE_TYPE_GENERATED_LIST       (0x02A | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_BACKGROUND           (0x02C | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_HELD_OBJ             (0x02E | GRAPH_NODE_TYPE_FUNCTIONAL)
#define GRAPH_NODE_TYPE_CULLING_RADIUS        0x02F

// The number of master lists. A master list determines the order and render
// mode with which display lists are drawn.
#define GFX_NUM_MASTER_LISTS 8

// Passed as first argument to a GraphNodeFunc to give information about in
// which context it was called and what it is expected to do.
#define GEO_CONTEXT_CREATE        0 // called when node is created from a geo command
#define GEO_CONTEXT_RENDER        1 // called from rendering_graph_node.c
#define GEO_CONTEXT_AREA_UNLOAD   2 // called when unloading an area
#define GEO_CONTEXT_AREA_LOAD     3 // called when loading an area
#define GEO_CONTEXT_AREA_INIT     4 // called when initializing the 8 areas
#define GEO_CONTEXT_HELD_OBJ      5 // called when processing a GraphNodeHeldObj

// The signature for a function stored in a geo node
// The context argument depends on the callContext:
// - for GEO_CONTEXT_CREATE it is the DynamicPool from which the node was allocated
// - for GEO_CONTEXT_RENDER or GEO_CONTEXT_HELD_OBJ it is the top of the float matrix stack with type Mat4
// - for GEO_CONTEXT_AREA_* it is the root geo node
typedef Gfx *(*GraphNodeFunc)(s32 callContext, struct GraphNode *node, void *context);

/** An extension of a graph node that includes a function pointer.
 *  Many graph node types have an update function that gets called
 *  when they are processed.
 */
struct FnGraphNode
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ GraphNodeFunc func;
    u32 luaTokenIndex; // reference to lua function resolved during geo_process_lua_function (1-indexed)
};

/** The very root of the geo tree. Specifies the viewport.
 */
struct GraphNodeRoot
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ u8 areaIndex;
    /*0x15*/ s8 unk15; // ?
    /*0x16*/ s16 x;
    /*0x18*/ s16 y;
    /*0x1A*/ s16 width; // half width, 160
    /*0x1C*/ s16 height; // half height
    /*0x1E*/ s16 numViews; // number of entries in mystery array
    /*0x20*/ struct GraphNode **views;
};

/** A node that sets up an orthographic projection based on the global
 *  root node. Used to draw the skybox image.
 */
struct GraphNodeOrthoProjection
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ f32 scale;
};

/** A node that sets up a perspective projection. Used for drawing the
 *  game world. It does not set up the camera position, that is done by
 *  the child of this node, which has type GraphNodeCamera.
 */
struct GraphNodePerspective
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ s32 unused;
    /*0x1C*/ f32 fov;   // horizontal field of view in degrees
    /*0x20*/ s16 near;  // near clipping plane
    /*0x22*/ s16 far;   // far clipping plane
    f32 prevFov;
    f32 prevTimestamp;
};

/** An entry in the master list. It is a linked list of display lists
 *  carrying a transformation matrix.
 */
struct DisplayListNode
{
    Mtx *transform;
    Mtx *transformPrev;
    Gfx *displayList;
    struct DisplayListNode *next;
    u8 usingCamSpace;
};

/** GraphNode that manages the 8 top-level display lists that will be drawn
 *  Each list has its own render mode, so for example water is drawn in a
 *  different master list than opaque objects.
 *  It also sets the z-buffer on before rendering and off after.
 */
struct GraphNodeMasterList
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ struct DisplayListNode *listHeads[GFX_NUM_MASTER_LISTS];
    /*0x34*/ struct DisplayListNode *listTails[GFX_NUM_MASTER_LISTS];
};

/** Simply used as a parent to group multiple children.
 *  Does not have any additional functionality.
 */
struct GraphNodeStart
{
    /*0x00*/ struct GraphNode node;
};

/** GraphNode that only renders its children if the current transformation matrix
 *  has a z-translation (in camera space) greater than minDistance and less than
 *  maxDistance.
 *  Usage examples: Mario has three level's of detail: Normal, low-poly arms only, and fully low-poly
 *  The tower in Whomp's fortress has two levels of detail.
 */
struct GraphNodeLevelOfDetail
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ s16 minDistance;
    /*0x16*/ s16 maxDistance;
};

/** GraphNode that renders exactly one of its children.
 *  Which one is rendered is determined by the field 'selectedCase'
 *  which is set in the node's function.
 *  Usage examples: room visibility, coin animation, blinking, Mario's power-up / hand pose / cap
 */
struct GraphNodeSwitchCase
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ s32 unused;
    /*0x1C*/ s16 parameter;
    /*0x1E*/ s16 selectedCase;
};

/**
 * GraphNode that specifies the location and aim of the camera.
 * When the roll is 0, the up vector is (0, 1, 0).
 */
struct GraphNodeCamera
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ union {
        // When the node is created, a mode is assigned to the node.
        // Later in geo_camera_main a Camera is allocated,
        // the mode is passed to the struct, and the field is overridden
        // by a pointer to the struct. Gotta save those 4 bytes.
        s32 mode;
        struct Camera *camera;
    } config;
    /*0x1C*/ Vec3f pos;
    /*0x28*/ Vec3f focus;
    Vec3f prevPos;
    Vec3f prevFocus;
    u32 prevTimestamp;
    /*0x34*/ Mat4 *matrixPtr; // pointer to look-at matrix of this camera as a Mat4
    Mat4 *matrixPtrPrev;
    /*0x38*/ s16 roll; // roll in look at matrix. Doesn't account for light direction unlike rollScreen.
    /*0x3A*/ s16 rollScreen; // rolls screen while keeping the light direction consistent
};

/** GraphNode that translates and rotates its children.
 *  Usage example: wing cap wings.
 *  There is a dprint function that sets the translation and rotation values
 *  based on the ENEMYINFO array.
 *  The display list can be null, in which case it won't draw anything itself.
 */
struct GraphNodeTranslationRotation
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ Vec3s translation;
    /*0x1E*/ Vec3s rotation;
};

/** GraphNode that translates itself and its children.
 *  Usage example: SUPER MARIO logo letters in debug level select.
 *  The display list can be null, in which case it won't draw anything itself.
 */
struct GraphNodeTranslation
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ Vec3s translation;
    u8 pad1E[2];
};

/** GraphNode that rotates itself and its children.
 *  Usage example: Mario torso / head rotation. Its parameters are dynamically
 *  set by a parent script node in that case.
 *  The display list can be null, in which case it won't draw anything itself.
 */
struct GraphNodeRotation
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ Vec3s rotation;
    Vec3s prevRotation;
    u32 prevTimestamp;
};

/** GraphNode part that transforms itself and its children based on animation
 *  data. This animation data is not stored in the node itself but in global
 *  variables that are set when object nodes are processed if the object has
 *  animation.
 *  Used for Mario, enemies and anything else with animation data.
 *  The display list can be null, in which case it won't draw anything itself.
 */
struct GraphNodeAnimatedPart
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ Vec3s translation;
};

/** A GraphNode that draws a display list rotated in a way to always face the
 *  camera. Note that if the entire object is a billboard (like a coin or 1-up)
 *  then it simply sets the billboard flag for the entire object, this node is
 *  used for billboard parts (like a chuckya or goomba body).
 */
struct GraphNodeBillboard
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ Vec3s translation;
};

/** A GraphNode that simply draws a display list without doing any
 *  transformation beforehand. It does inherit the parent's transformation.
 */
struct GraphNodeDisplayList
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
};

/** GraphNode part that scales itself and its children.
 *  Usage example: Mario's fist or shoe, which grows when attacking. This can't
 *  be done with an animated part sine animation data doesn't support scaling.
 *  Note that many scaling animations (like a goomba getting stomped) happen on
 *  the entire object. This node is only used when a single part needs to be scaled.
 *  There is also a level command that scales the entire level, used for THI.
 *  The display list can be null, in which case it won't draw anything itself.
 */
struct GraphNodeScale
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ Gfx *displayList;
    /*0x18*/ f32 scale;
    /*????*/ f32 prevScale;
};

/** GraphNode that draws a shadow under an object.
 *  Every object starts with a shadow node.
 *  The shadow type determines the shape (round or rectangular), vertices (4 or 9)
 *  and other features.
 */
struct GraphNodeShadow
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ s16 shadowScale; // diameter (when a circle) or side (when a square) of shadow
    /*0x16*/ u8 shadowSolidity; // opacity of shadow, 255 = opaque
    /*0x17*/ u8 shadowType; // see ShadowType enum in shadow.h
};

/** GraphNode that contains as its sharedChild a group node containing all
 *  object nodes.
 */
struct GraphNodeObjectParent
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ struct GraphNode *sharedChild;
};

/** GraphNode that draws display lists not directly in memory but generated by
 *  a function.
 *  Used for wobbling paintings, water, environment effects.
 *  It might not draw anything, it could also just update something.
 *  For example: there is a node that stops water flow when the game is paused.
 *  The parameter field gives extra context info. For shifting sand or paintings,
 *  it can determine which texture to use.
 */
struct GraphNodeGenerated
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ u32 parameter; // extra context for the function
};

/** GraphNode that draws a background image or a rectangle of a color.
 *  Drawn in an orthographic projection, used for skyboxes.
 */
struct GraphNodeBackground
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ s32 unused;
    /*0x1C*/ s32 background; // background ID, or rgba5551 color if fnNode.func is null
    Vec3f prevCameraPos;
    Vec3f prevCameraFocus;
    u32 prevCameraTimestamp;
};

/** Renders the object that Mario is holding.
 */
struct GraphNodeHeldObject
{
    /*0x00*/ struct FnGraphNode fnNode;
    /*0x18*/ s32 playerIndex;
    /*0x1C*/ struct Object *objNode;
    /*0x20*/ Vec3s translation;
    Vec3f prevShadowPos;
    u32 prevShadowPosTimestamp;
};

/** A node that allows an object to specify a different culling radius than the
 *  default one of 300. For this to work, it needs to be a direct child of the
 *  object node. Used for very large objects, such as shock wave rings that Bowser
 *  creates, tornadoes, the big eel.
 */
struct GraphNodeCullingRadius
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ s16 cullingRadius; // specifies the 'sphere radius' for purposes of frustum culling
    u8 pad1E[2];
};

extern struct GraphNodeMasterList *gCurGraphNodeMasterList;
extern struct GraphNodePerspective *gCurGraphNodeCamFrustum;
extern struct GraphNodeCamera *gCurGraphNodeCamera;
extern struct GraphNodeHeldObject *gCurGraphNodeHeldObject;
extern u16 gAreaUpdateCounter;

extern struct GraphNode *gCurRootGraphNode;
extern struct GraphNode *gCurGraphNodeList[];

extern s16 gCurGraphNodeIndex;

void init_scene_graph_node_links(struct GraphNode *graphNode, s32 type);

struct GraphNodeRoot *init_graph_node_root(struct DynamicPool *pool, struct GraphNodeRoot *graphNode,
                                           s16 areaIndex, s16 x, s16 y, s16 width, s16 height);
struct GraphNodeOrthoProjection *init_graph_node_ortho_projection(struct DynamicPool *pool, struct GraphNodeOrthoProjection *graphNode, f32 scale);
struct GraphNodePerspective *init_graph_node_perspective(struct DynamicPool *pool, struct GraphNodePerspective *graphNode,
                                                         f32 fov, s16 near, s16 far, GraphNodeFunc nodeFunc, s32 unused);
struct GraphNodeStart *init_graph_node_start(struct DynamicPool *pool, struct GraphNodeStart *graphNode);
struct GraphNodeMasterList *init_graph_node_master_list(struct DynamicPool *pool, struct GraphNodeMasterList *graphNode, s16 on);
struct GraphNodeLevelOfDetail *init_graph_node_render_range(struct DynamicPool *pool, struct GraphNodeLevelOfDetail *graphNode,
                                                            s16 minDistance, s16 maxDistance);
struct GraphNodeSwitchCase *init_graph_node_switch_case(struct DynamicPool *pool, struct GraphNodeSwitchCase *graphNode,
                                                        s16 parameter, s16 selectedCase, GraphNodeFunc nodeFunc, s32 unused);
struct GraphNodeCamera *init_graph_node_camera(struct DynamicPool *pool, struct GraphNodeCamera *graphNode,
                                               f32 *pos, f32 *focus, GraphNodeFunc func, s32 mode);
struct GraphNodeTranslationRotation *init_graph_node_translation_rotation(struct DynamicPool *pool, struct GraphNodeTranslationRotation *graphNode,
                                                                          s32 drawingLayer, void *displayList, Vec3s translation, Vec3s rotation);
struct GraphNodeTranslation *init_graph_node_translation(struct DynamicPool *pool, struct GraphNodeTranslation *graphNode,
                                                         s32 drawingLayer, void *displayList, Vec3s translation);
struct GraphNodeRotation *init_graph_node_rotation(struct DynamicPool *pool, struct GraphNodeRotation *graphNode,
                                                   s32 drawingLayer, void *displayList, Vec3s rotation);
struct GraphNodeScale *init_graph_node_scale(struct DynamicPool *pool, struct GraphNodeScale *graphNode,
                                             s32 drawingLayer, void *displayList, f32 scale);
struct GraphNodeObject *init_graph_node_object(struct DynamicPool *pool, struct GraphNodeObject *graphNode,
                                               struct GraphNode *sharedChild, Vec3f pos, Vec3s angle, Vec3f scale);
struct GraphNodeCullingRadius *init_graph_node_culling_radius(struct DynamicPool *pool, struct GraphNodeCullingRadius *graphNode, s16 radius);
struct GraphNodeAnimatedPart *init_graph_node_animated_part(struct DynamicPool *pool, struct GraphNodeAnimatedPart *graphNode,
                                                            s32 drawingLayer, void *displayList, Vec3s translation);
struct GraphNodeBillboard *init_graph_node_billboard(struct DynamicPool *pool, struct GraphNodeBillboard *graphNode,
                                                     s32 drawingLayer, void *displayList, Vec3s translation);
struct GraphNodeDisplayList *init_graph_node_display_list(struct DynamicPool *pool, struct GraphNodeDisplayList *graphNode,
                                                          s32 drawingLayer, void *displayList);
struct GraphNodeShadow *init_graph_node_shadow(struct DynamicPool *pool, struct GraphNodeShadow *graphNode,
                                               s16 shadowScale, u8 shadowSolidity, u8 shadowType);
struct GraphNodeObjectParent *init_graph_node_object_parent(struct DynamicPool *pool, struct GraphNodeObjectParent *sp1c,
                                                            struct GraphNode *sharedChild);
struct GraphNodeGenerated *init_graph_node_generated(struct DynamicPool *pool, struct GraphNodeGenerated *sp1c,
                                                     GraphNodeFunc gfxFunc, s32 parameter);
struct GraphNodeBackground *init_graph_node_background(struct DynamicPool *pool, struct GraphNodeBackground *sp1c,
                                                       u16 background, GraphNodeFunc backgroundFunc, u8 extended);
struct GraphNodeHeldObject *init_graph_node_held_object(struct DynamicPool *pool, struct GraphNodeHeldObject *sp1c,
                                                        struct Object *objNode, Vec3s translation,
                                                        GraphNodeFunc nodeFunc, s32 playerIndex);
struct GraphNode *geo_add_child(struct GraphNode *parent, struct GraphNode *childNode);
struct GraphNode* geo_remove_child_from_parent(struct GraphNode* parent, struct GraphNode* graphNode);
struct GraphNode *geo_remove_child(struct GraphNode *graphNode);
struct GraphNode *geo_make_first_child(struct GraphNode *newFirstChild);
struct GraphNode *geo_find_shared_child(struct GraphNode *graphNode);

void geo_call_global_function_nodes_helper(struct GraphNode *graphNode, s32 callContext);
void geo_call_global_function_nodes(struct GraphNode *graphNode, s32 callContext);

void geo_reset_object_node(struct GraphNodeObject *graphNode);
void geo_obj_init(struct GraphNodeObject *graphNode, void *sharedChild, Vec3f pos, Vec3s angle);
void geo_obj_init_spawninfo(struct GraphNodeObject *graphNode, struct SpawnInfo *spawn);
void geo_obj_init_animation(struct GraphNodeObject *graphNode, const struct Animation * const anim);
void geo_obj_init_animation_accel(struct GraphNodeObject *graphNode, const struct Animation * const anim, u32 animAccel);

s32 retrieve_animation_index(s32 frame, u16 **attributes);
s16 retrieve_animation_value(struct Animation *animation, s32 frame, u16 **attributes);

s16 geo_update_animation_frame(struct AnimInfo *obj, s32 *accelAssist);
void geo_retreive_animation_translation(struct GraphNodeObject *obj, Vec3f position);

struct GraphNodeRoot *geo_find_root(struct GraphNode *graphNode);

// graph_node_manager
s16 *read_vec3s_to_vec3f(Vec3f, s16 *src);
s16 *read_vec3s(Vec3s dst, s16 *src);
s16 *read_vec3s_angle(Vec3s dst, s16 *src);
void register_scene_graph_node(struct GraphNode *graphNode);

#endif // GRAPH_NODE_H
