#include "mirror.h"

#include "behavior_data.h"
#include "object_constants.h"
#include "object_fields.h"

#include "src/engine/math_util.h"
#include "src/game/hardcoded.h"
#include "src/game/object_helpers.h"
#include "src/game/object_list_processor.h"
#include "src/game/rendering_graph_node.h"
#include "src/pc/lua/smlua.h"
#include "src/pc/lua/utils/smlua_obj_utils.h"

  /////////////////////
 // Mirror behavior //
/////////////////////

//
// Mirror oBehParams bits:
// AAAAAAAA AAABBBBB BBBBBBCC CCCCCCCC
//
//     +-------+------+--------------------+--------+---------------+
//     | shift | bits | field              | factor |     max       |
// +---+-------+------+--------------------+--------+---------------+
// | A |   21  |  11  | oMirrorWidth       |    10  | 2047 -> 20470 |
// | B |   10  |  11  | oMirrorHeight      |    10  | 2047 -> 20470 |
// | C |    0  |  10  | oMirrorMaxDistance |    10  | 1023 -> 10230 |
// +---+-------+------+--------------------+--------+---------------+
//
// For example:
//
//   oMirrorWidth = 1500
//   oMirrorHeight = 850
//   oMirrorMaxDistance = 600
//
// gives:
//
//   oBehParams = (
//     (((1500 / 10) & 0x7FF) << 21) |
//     ((( 850 / 10) & 0x7FF) << 10) |
//     ((( 600 / 10) & 0x3FF) <<  0)
//   )
//
// For usage in OBJECT macro, copy paste this as behavior params and change the oMirror values:
//
// ((((oMirrorWidth / 10) & 0x7FF) << 21) | (((oMirrorHeight / 10) & 0x7FF) << 10) | (((oMirrorMaxDistance / 10) & 0x3FF) << 0))
//
// oMirrorType is automatically set by the behavior script.
// Make sure to use bhvHorizontalMirror and bhvVerticalMirror (NOT bhvMirror) in level script.
//

void bhv_mirror_init(void) {
    struct Object *o = gCurrentObject;
    o->oMirrorWidth = _SHIFTR(o->oBehParams, 21, 11) * 10.f;
    o->oMirrorHeight = _SHIFTR(o->oBehParams, 10, 11) * 10.f;
    o->oMirrorMaxDistance = _SHIFTR(o->oBehParams, 0, 10) * 10.f;
    cur_obj_set_behavior(bhvMirror);
    cur_obj_hide();
}

  ////////////////////
 // Mirror objects //
////////////////////

struct MirrorObject {
    struct Object obj[1];
    struct Object *mirror;
    struct MirrorObject *next;
    struct MirrorObject *children;
    u8 reflection;
    bool rendered;
};

static struct GrowingArray *sMirrorObjectPool = NULL;
static struct MirrorObject *sMirrorObjects[OBJECT_POOL_CAPACITY] = {[0 ... OBJECT_POOL_CAPACITY - 1] = NULL};

INLINE static s32 get_object_slot(struct Object *obj) {
    if (obj < gObjectPool || obj >= gObjectPool + OBJECT_POOL_CAPACITY) {
        return -1;
    }
    return (s32) (obj - gObjectPool);
}

static struct MirrorObject *allocate_mirror_object() {

    // Allocate pool
    if (!sMirrorObjectPool) {
        sMirrorObjectPool = growing_array_init(sMirrorObjectPool, 0x100);
    }

    // Find a free slot in the pool
    for (u32 i = 0; i != sMirrorObjectPool->count; ++i) {
        struct MirrorObject *mobj = sMirrorObjectPool->buffer[i];
        if (mobj->mirror == NULL) {
            return mobj;
        }
    }

    // Create new item
    return growing_array_alloc(sMirrorObjectPool, sizeof(struct MirrorObject));
}

static struct MirrorObject *find_mirror_object(struct Object *mirror, struct Object *obj) {
    struct MirrorObject *firstMirrorObj = NULL;

    // Real object
    if (!geo_is_mirror_object(obj)) {
        s32 slot = get_object_slot(obj);
        if (slot == -1) {
            return NULL;
        }

        firstMirrorObj = sMirrorObjects[slot];

        // If there is no mirror object for this real object, create a new list
        if (!firstMirrorObj) {
            struct MirrorObject *mirrorObj = allocate_mirror_object();
            if (!mirrorObj) {
                return NULL;
            }

            mirrorObj->mirror = mirror;
            mirrorObj->next = NULL;
            mirrorObj->children = NULL;
            mirrorObj->reflection = 1;
            mirrorObj->rendered = false;
            sMirrorObjects[slot] = mirrorObj;
            return mirrorObj;
        }
    }

    // Mirror object
    else {
        struct MirrorObject *mirrorObjRef = obj->oMirrorObjRef;
        firstMirrorObj = mirrorObjRef->children;

        // If there is no mirror object for this reflection, create a new list
        if (!firstMirrorObj) {
            struct MirrorObject *mirrorObj = allocate_mirror_object();
            if (!mirrorObj) {
                return NULL;
            }

            mirrorObj->mirror = mirror;
            mirrorObj->next = NULL;
            mirrorObj->children = NULL;
            mirrorObj->reflection = mirrorObjRef->reflection + 1;
            mirrorObj->rendered = false;
            mirrorObjRef->children = mirrorObj;
            return mirrorObj;
        }
    }

    // Find the mirror object corresponding to mirror
    struct MirrorObject *lastMirrorObj = firstMirrorObj;
    for (struct MirrorObject *mirrorObj = firstMirrorObj; mirrorObj != NULL; lastMirrorObj = mirrorObj, mirrorObj = mirrorObj->next) {
        if (mirrorObj->mirror == mirror) {
            return mirrorObj;
        }
    }

    // No mirror object for this mirror, create a new item
    struct MirrorObject *mirrorObj = allocate_mirror_object();
    if (!mirrorObj) {
        return NULL;
    }

    mirrorObj->mirror = mirror;
    mirrorObj->next = NULL;
    lastMirrorObj->next = mirrorObj;
    mirrorObj->children = NULL;
    mirrorObj->reflection = lastMirrorObj->reflection;
    mirrorObj->rendered = false;
    return mirrorObj;
}

static struct MirrorObject *get_mirror_object(struct Object *mirror, struct Object *obj) {
    struct MirrorObject *mirrorObj = find_mirror_object(mirror, obj);
    if (!mirrorObj) {
        return NULL;
    }

    // Check behavior
    // If it's not the same, the original object has changed from the last frame,
    // so reset all object fields to restart interpolation
    if (mirrorObj->obj->behavior != obj->behavior) {
        memset(mirrorObj->obj, 0, sizeof(mirrorObj->obj));
    }

    struct GraphNodeObject *mirrorNode = &mirrorObj->obj->header.gfx;
    struct AnimInfo *mirrorAnimInfo = &mirrorNode->animInfo;

    // Backup interpolation fields
    Mat4 prevThrowMatrix; mtxf_copy(prevThrowMatrix, mirrorNode->prevThrowMatrix);
    Vec3s prevAngle; vec3s_copy(prevAngle, mirrorNode->prevAngle);
    Vec3f prevPos; vec3f_copy(prevPos, mirrorNode->prevPos);
    Vec3f prevShadowPos; vec3f_copy(prevShadowPos, mirrorNode->prevShadowPos);
    Vec3f prevScale; vec3f_copy(prevScale, mirrorNode->prevScale);
    u32 prevTimestamp = mirrorNode->prevTimestamp;
    u32 prevShadowPosTimestamp = mirrorNode->prevShadowPosTimestamp;
    u32 prevScaleTimestamp = mirrorNode->prevScaleTimestamp;
    u32 prevThrowMatrixTimestamp = mirrorNode->prevThrowMatrixTimestamp;
    u32 skipInterpolationTimestamp = mirrorNode->skipInterpolationTimestamp;
    struct Animation *prevAnimPtr = mirrorAnimInfo->prevAnimPtr;
    s16 prevAnimID = mirrorAnimInfo->prevAnimID;
    s16 prevAnimFrame = mirrorAnimInfo->prevAnimFrame;
    u32 prevAnimFrameTimestamp = mirrorAnimInfo->prevAnimFrameTimestamp;

    // Copy object
    *mirrorObj->obj = *obj;

    // Restore interpolation fields
    mtxf_copy(mirrorNode->prevThrowMatrix, prevThrowMatrix);
    vec3s_copy(mirrorNode->prevAngle, prevAngle);
    vec3f_copy(mirrorNode->prevPos, prevPos);
    vec3f_copy(mirrorNode->prevShadowPos, prevShadowPos);
    vec3f_copy(mirrorNode->prevScale, prevScale);
    mirrorNode->prevTimestamp = prevTimestamp;
    mirrorNode->prevShadowPosTimestamp = prevShadowPosTimestamp;
    mirrorNode->prevScaleTimestamp = prevScaleTimestamp;
    mirrorNode->prevThrowMatrixTimestamp = prevThrowMatrixTimestamp;
    mirrorNode->skipInterpolationTimestamp = skipInterpolationTimestamp;
    mirrorAnimInfo->prevAnimPtr = prevAnimPtr;
    mirrorAnimInfo->prevAnimID = prevAnimID;
    mirrorAnimInfo->prevAnimFrame = prevAnimFrame;
    mirrorAnimInfo->prevAnimFrameTimestamp = prevAnimFrameTimestamp;

    // Mirror object
    bool isMirrorObject = geo_is_mirror_object(obj);
    mirrorObj->obj->curBhvCommand = bhvMirrorObject;
    mirrorObj->obj->oMirrorObjPrevObj = obj;
    mirrorObj->obj->oMirrorObjRealObj = isMirrorObject ? obj->oMirrorObjRealObj : obj;
    mirrorObj->obj->oMirrorObjMirror = mirror;
    mirrorObj->obj->oMirrorObjInvertCulling = isMirrorObject ? !obj->oMirrorObjInvertCulling : TRUE;
    mirrorObj->obj->oMirrorObjRef = mirrorObj;
    mirrorNode->throwMatrix = NULL;
    return mirrorObj;
}

static void mirror_transform(struct Object *mirror, Vec3f pos, Vec3s angle, Vec3f scale) {
    switch (mirror->oMirrorType) {
        case MIRROR_TYPE_VERTICAL: {

            // Mirror Y position
            if (pos) {
                pos[1] = 2 * mirror->oPosY - pos[1];
            }

            // Invert pitch (up becomes down)
            if (angle) {
                angle[0] *= -1;
            }

            // Invert Y scale (up becomes down)
            if (scale) {
                scale[1] *= -1;
            }
        } break;

        case MIRROR_TYPE_HORIZONTAL: {

            // Mirror XZ position
            if (pos) {
                Vec2f mirrorNormal = {
                    sins(mirror->oFaceAngleYaw),
                    coss(mirror->oFaceAngleYaw)
                };
                Vec2f mirrorDir = {
                    coss(mirror->oFaceAngleYaw),
                    -sins(mirror->oFaceAngleYaw)
                };
                Vec2f mirrorToPos = {
                    pos[0] - mirror->oPosX,
                    pos[2] - mirror->oPosZ,
                };
                f32 x = vec2f_dot(mirrorToPos, mirrorDir);
                f32 y = vec2f_dot(mirrorToPos, mirrorNormal);
                pos[0] = mirror->oPosX + mirrorDir[0] * x - mirrorNormal[0] * y;
                pos[2] = mirror->oPosZ + mirrorDir[1] * x - mirrorNormal[1] * y;
            }

            // Mirror yaw, invert roll (left becomes right)
            if (angle) {
                angle[1] = 2 * (mirror->oFaceAngleYaw + 0x4000) - angle[1];
                angle[2] *= -1;
            }

            // Invert X scale (left becomes right)
            if (scale) {
                scale[0] *= -1;
            }
        } break;
    }
}

static bool mirror_is_in_range(struct Object *mirror, struct Object *obj) {
    switch (mirror->oMirrorType) {
        case MIRROR_TYPE_VERTICAL: {

            // Distance check
            if (fabs(obj->oPosY - mirror->oPosY) > mirror->oMirrorMaxDistance) {
                return false;
            }

            // Height check
            Vec2f dirMirrorToObj = {
                obj->oPosX - mirror->oPosX,
                obj->oPosZ - mirror->oPosZ
            };
            Vec2f mirrorHeightAxis = {
                sins(mirror->oFaceAngleYaw),
                coss(mirror->oFaceAngleYaw)
            };
            f32 dotHeight = vec2f_dot(dirMirrorToObj, mirrorHeightAxis);
            if (fabs(dotHeight) > mirror->oMirrorHeight / 2.f) {
                return false;
            }

            // Width check
            Vec2f mirrorWidthAxis = {
                sins(mirror->oFaceAngleYaw + 0x4000),
                coss(mirror->oFaceAngleYaw + 0x4000)
            };
            f32 dotWidth = vec2f_dot(dirMirrorToObj, mirrorWidthAxis);
            if (fabs(dotWidth) > mirror->oMirrorWidth / 2.f) {
                return false;
            }

            return true;
        }

        case MIRROR_TYPE_HORIZONTAL: {

            // Height check
            if (fabs(obj->oPosY - mirror->oPosY) > mirror->oMirrorHeight / 2.f) {
                return false;
            }

            // Width check
            Vec2f dirMirrorToObj = {
                obj->oPosX - mirror->oPosX,
                obj->oPosZ - mirror->oPosZ
            };
            Vec2f mirrorWidthAxis = {
                sins(mirror->oFaceAngleYaw + 0x4000),
                coss(mirror->oFaceAngleYaw + 0x4000)
            };
            f32 dotWidth = vec2f_dot(dirMirrorToObj, mirrorWidthAxis);
            if (fabs(dotWidth) > mirror->oMirrorWidth / 2.f) {
                return false;
            }

            // Distance check
            Vec2f mirrorNormal = {
                sins(mirror->oFaceAngleYaw),
                coss(mirror->oFaceAngleYaw)
            };
            f32 dotNormal = vec2f_dot(dirMirrorToObj, mirrorNormal);
            if (fabs(dotNormal) > mirror->oMirrorMaxDistance) {
                return false;
            }

            return true;
        }
    }
    return false;
}

static bool mirror_is_direction_valid(struct Object *mirror, struct Object *obj) {
    struct Object *real = obj->oMirrorObjRealObj;
    switch (mirror->oMirrorType) {
        case MIRROR_TYPE_VERTICAL: {
            return (mirror->oPosY - obj->oPosY) * (mirror->oPosY - real->oPosY) > 0.f;
        }

        case MIRROR_TYPE_HORIZONTAL: {
            Vec2f mirrorNormal = {
                sins(mirror->oFaceAngleYaw),
                coss(mirror->oFaceAngleYaw)
            };
            Vec2f dirObjToMirror = {
                mirror->oPosX - obj->oPosX,
                mirror->oPosZ - obj->oPosZ
            };
            Vec2f dirRealToMirror = {
                mirror->oPosX - real->oPosX,
                mirror->oPosZ - real->oPosZ
            };
            return vec2f_dot(dirObjToMirror, mirrorNormal) * vec2f_dot(dirRealToMirror, mirrorNormal) > 0.f;
        }
    }
    return false;
}

OPTIMIZE_O3 static bool mirror_is_duplicate(struct Object *obj, Vec3f pos, Vec3s angle, Vec3f scale) {
    for (u32 i = 0; i != sMirrorObjectPool->count; ++i) {
        struct MirrorObject *mirrorObj = sMirrorObjectPool->buffer[i];
        struct GraphNodeObject *mirrorNode = &mirrorObj->obj->header.gfx;

        // Not an actual mirror object (free slot)
        if (!mirrorObj->mirror) {
            continue;
        }

        // Not rendered yet, cannot count as a duplicate
        if (!mirrorObj->rendered) {
            continue;
        }

        // Not the same real object
        if (obj != mirrorObj->obj->oMirrorObjRealObj) {
            continue;
        }

        // Scale check
        // Inverted scales: not a duplicate
        if (scale[0] * mirrorNode->scale[0] < 0.f ||
            scale[1] * mirrorNode->scale[1] < 0.f) {
            continue;
        }

        // Angle check
        // Different yaws: not a duplicate
        if (abs(angle[1] - mirrorNode->angle[1]) > 0x10) {
            continue;
        }

        // Position check
        // Same position: it's a duplicate
        // Use squared distance for faster iteration
        Vec3f diff; vec3f_dif(diff, pos, mirrorNode->pos);
        if (vec3f_dot(diff, diff) < 4.f) {
            return true;
        }
    }
    return false;
}

static void geo_process_mirror(struct Object *mirror, struct Object *obj) {

    // Reject inactive mirrors
    if (!(mirror->header.gfx.node.flags & GRAPH_RENDER_ACTIVE)) {
        return;
    }

    // Reject invalid mirrors
    switch (mirror->oMirrorType) {
        case MIRROR_TYPE_VERTICAL:
        case MIRROR_TYPE_HORIZONTAL: break;
        default: return;
    }

    // Reject objects out of range
    if (!mirror_is_in_range(mirror, obj)) {
        return;
    }

    // If obj is a mirror object, perform extra checks
    if (geo_is_mirror_object(obj)) {

        // A mirror cannot reflect the same object twice in a row
        if (obj->oMirrorObjMirror == mirror) {
            return;
        }

        // Check the direction of the reflection
        if (!mirror_is_direction_valid(mirror, obj)) {
            return;
        }
    }

    // Apply mirror transform
    Vec3f pos; vec3f_copy(pos, obj->header.gfx.pos);
    Vec3s angle; vec3s_copy(angle, obj->header.gfx.angle);
    Vec3f scale; vec3f_copy(scale, obj->header.gfx.scale);
    mirror_transform(mirror, pos, angle, scale);

    // Check duplicate
    // First reflection cannot be a duplicate
    if (geo_is_mirror_object(obj) && mirror_is_duplicate(obj->oMirrorObjRealObj, pos, angle, scale)) {
        return;
    }

    // Create and process mirror object
    struct MirrorObject *mirrorObj = get_mirror_object(mirror, obj);
    if (!mirrorObj) {
        return;
    }

    vec3f_copy(mirrorObj->obj->header.gfx.pos, pos);
    vec3s_copy(mirrorObj->obj->header.gfx.angle, angle);
    vec3f_copy(mirrorObj->obj->header.gfx.scale, scale);
    vec3f_copy(&mirrorObj->obj->oPosX, pos);
    mirrorObj->rendered = true;

    geo_invert_culling(mirrorObj->obj->oMirrorObjInvertCulling);
    geo_process_object(mirrorObj->obj);
    geo_invert_culling(!mirrorObj->obj->oMirrorObjInvertCulling);
}

void geo_process_mirrors(struct Object *obj) {

    // Reject inactive objects
    // Invisible objects can still be mirrored (for example to make an object visible only in the mirror)
    if (!(obj->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) || obj->header.gfx.sharedChild == NULL) {
        return;
    }

    // Reject mirrors, lights and camera lakitu
    if (obj->behavior == bhvMirror ||
        obj->behavior == bhvPointLight ||
        obj->behavior == bhvAmbientLight ||
        obj->behavior == bhvCameraLakitu ||
        (obj->behavior == bhvCloud && obj->parentObj && obj->parentObj->behavior == bhvCameraLakitu) ||
        (obj->behavior == bhvCloudPart && obj->parentObj && obj->parentObj->behavior == bhvCloud && obj->parentObj->parentObj && obj->parentObj->parentObj->behavior == bhvCameraLakitu)) {
        return;
    }

    // Reject reflection above limit
    if (gBehaviorValues.MirrorsMaxReflections == 0) {
        return;
    }
    if (geo_is_mirror_object(obj)) {
        struct MirrorObject *mirrorObjRef = obj->oMirrorObjRef;
        if (mirrorObjRef->reflection >= gBehaviorValues.MirrorsMaxReflections) {
            return;
        }
    }

    // Process mirrors
    struct Object *mirror = obj_get_first_with_behavior_id(id_bhvMirror);
    while (mirror) {
        geo_process_mirror(mirror, obj);
        mirror = obj_get_next_with_same_behavior_id(mirror);
    }
}

static void geo_unload_mirror_object(struct MirrorObject *mirrorObj) {
    if (!mirrorObj) {
        return;
    }

    geo_unload_mirror_object(mirrorObj->children);
    geo_unload_mirror_object(mirrorObj->next);
    memset(mirrorObj, 0, sizeof(*mirrorObj));
}

void geo_unload_mirror_objects(struct Object *obj) {
    s32 slot = get_object_slot(obj);
    if (slot == -1) {
        return;
    }

    geo_unload_mirror_object(sMirrorObjects[slot]);
    sMirrorObjects[slot] = NULL;
}

void geo_unload_all_mirror_objects() {
    if (!sMirrorObjectPool) {
        return;
    }

    growing_array_free(&sMirrorObjectPool);
    memset(sMirrorObjects, 0, sizeof(sMirrorObjects));
}

void geo_reset_mirrors() {
    if (!sMirrorObjectPool) {
        return;
    }

    // Shrink buffer if the last objects are unused
    // Reduces the amount of objects to check in mirror_is_duplicate
    for (u32 i = sMirrorObjectPool->count; i > 0; --i) {
        struct MirrorObject *mirrorObj = sMirrorObjectPool->buffer[i - 1];
        if (mirrorObj->mirror) {
            break;
        }
        sMirrorObjectPool->count--;
    }

    // Unset rendered flag
    for (u32 i = 0; i != sMirrorObjectPool->count; ++i) {
        struct MirrorObject *mirrorObj = sMirrorObjectPool->buffer[i];
        mirrorObj->rendered = false;
    }
}

// Backwards recursion to apply the transforms from the first to the last reflection
static void mirror_transform_shadow(struct Object *obj, Vec3f pos, Vec3f scale) {
    if (geo_is_mirror_object(obj->oMirrorObjPrevObj)) {
        mirror_transform_shadow(obj->oMirrorObjPrevObj, pos, scale);
    }
    mirror_transform(obj->oMirrorObjMirror, pos, NULL, scale);
}

f32 geo_process_shadow_apply_mirror_transform(struct GraphNodeObject *node, Vec3f outScale) {
    vec3f_copy(outScale, gVec3fOne);

    struct Object *mirrorObj = (struct Object *) node;
    if (geo_is_mirror_object(mirrorObj)) {

        // HACK: Shadow code is a hell to work with...
        // As a result, sticking a shadow to a ceiling is incredibly hard,
        // so just don't render the shadow for vertically mirrored objects.
        if (node->scale[1] < 0.f) {
            return 0.f;
        }

        // At this point in geo processing, manual shadowPos is at the real object position.
        // We need to apply all mirrors transforms to get the reflected shadow position.
        if (!gCurGraphNodeHeldObject && node->disableAutomaticShadowPos) {
            mirror_transform_shadow(mirrorObj, node->shadowPos, outScale);
        } else {
            mirror_transform_shadow(mirrorObj, NULL, outScale);
        }
    }
    return 1.f;
}

bool geo_is_mirror_object(struct Object *obj) {
    return obj && obj->curBhvCommand == bhvMirrorObject;
}

static bool sGeoIsCullingInverted = false;

bool geo_is_culling_inverted() {
    return sGeoIsCullingInverted;
}

void geo_invert_culling(bool invert) {
    static Gfx sObjCullInvertGfx[2][2] = {
        { gsSPClearGeometryMode(G_CULL_INVERT_EXT), gsSPEndDisplayList() },
        { gsSPSetGeometryMode(G_CULL_INVERT_EXT), gsSPEndDisplayList() },
    };
    for (s16 layer = 0; layer != 8; ++layer) {
        geo_append_display_list(sObjCullInvertGfx[invert], layer);
    }
    sGeoIsCullingInverted = invert;
}
