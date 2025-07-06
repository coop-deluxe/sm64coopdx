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

static struct {
    struct Object **buffer;
    u32 count;
    u32 capacity;
} sMirrorObjects = {0};

static struct Object *allocate_mirror_object() {

    // Increase capacity if needed
    if (sMirrorObjects.count == sMirrorObjects.capacity) {
        u32 newCapacity = MAX(sMirrorObjects.capacity * 2, 64);
        sMirrorObjects.buffer = realloc(sMirrorObjects.buffer, newCapacity * sizeof(struct Object *));
        memset(sMirrorObjects.buffer + sMirrorObjects.capacity, 0, (newCapacity - sMirrorObjects.capacity) * sizeof(struct Object *));
        sMirrorObjects.capacity = newCapacity;
    }

    // Create new object if slot is empty
    struct Object *obj = sMirrorObjects.buffer[sMirrorObjects.count];
    if (!obj) {
        obj = sMirrorObjects.buffer[sMirrorObjects.count] = calloc(1, sizeof(struct Object));
    }

    // Increase object count
    sMirrorObjects.count++;
    return obj;
}

static struct Object *get_mirror_object(struct Object *mirror, struct Object *obj) {
    struct Object *mirrorObj = allocate_mirror_object();
    if (!mirrorObj) {
        return NULL;
    }

    // For the interpolation to work on mirror objects, they need to get the same object pointer everytime,
    // in order to reuse their previous frame non-interpolated values.
    // That's why sMirrorObjects is a strictly growing array, it ensures that allocate_mirror_object()
    // will always return the same pointer at a given index, without clearing memory.
    // This works most of the time, since the order of processing objects is deterministic.
    // In case a mirror object doesn't retrieve its previous state, just clear the memory to disable
    // interpolation this frame.

    bool isMirrorObject = geo_is_mirror_object(obj);
    if ((isMirrorObject && mirrorObj->oMirrorObjRealObj != obj->oMirrorObjRealObj) ||
        (!isMirrorObject && mirrorObj->oMirrorObjRealObj != obj)) {
        memset(mirrorObj, 0, sizeof(struct Object));
    }

    struct GraphNodeObject *mirrorNode = &mirrorObj->header.gfx;
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
    *mirrorObj = *obj;

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
    mirrorObj->behavior = bhvMirrorObject;
    mirrorObj->oMirrorObjPrevObj = obj;
    mirrorObj->oMirrorObjRealObj = isMirrorObject ? obj->oMirrorObjRealObj : obj;
    mirrorObj->oMirrorObjMirror = mirror;
    mirrorObj->oMirrorObjInvertCulling = isMirrorObject ? !obj->oMirrorObjInvertCulling : TRUE;
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

static bool mirror_check_range(struct Object *mirror, struct Object *obj) {
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

static bool mirror_check_direction(struct Object *mirror, struct Object *obj) {
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

OPTIMIZE_O3 static bool mirror_check_duplicate(struct Object *obj) {

    // First reflection cannot be a duplicate
    if (obj->oMirrorObjPrevObj == obj->oMirrorObjRealObj) {
        return false;
    }

    struct GraphNodeObject *node = &obj->header.gfx;
    for (u32 i = 0; i != sMirrorObjects.count - 1; ++i) {
        struct Object *mirrorObj = sMirrorObjects.buffer[i];
        struct GraphNodeObject *mirrorNode = &mirrorObj->header.gfx;

        // Not the same real object
        if (mirrorObj->oMirrorObjRealObj != obj->oMirrorObjRealObj) {
            continue;
        }

        // Scale check
        // Inverted scales: not a duplicate
        if (node->scale[0] * mirrorNode->scale[0] < 0.f ||
            node->scale[1] * mirrorNode->scale[1] < 0.f) {
            continue;
        }

        // Angle check
        // Different yaws: not a duplicate
        if (abs(node->angle[1] - mirrorNode->angle[1]) > 0x10) {
            continue;
        }

        // Position check
        // Same position: it's a duplicate
        // Use squared distance for faster iteration
        Vec3f diff; vec3f_dif(diff, node->pos, mirrorNode->pos);
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
    if (!mirror_check_range(mirror, obj)) {
        return;
    }

    // If obj is a mirror object, perform extra checks
    if (geo_is_mirror_object(obj)) {

        // A mirror cannot reflect the same object twice in a row
        if (obj->oMirrorObjMirror == mirror) {
            return;
        }

        // Check the direction of the reflection
        if (!mirror_check_direction(mirror, obj)) {
            return;
        }
    }

    struct Object *mirrorObj = get_mirror_object(mirror, obj);
    if (mirrorObj) {
        struct GraphNodeObject *mirrorNode = &mirrorObj->header.gfx;

        mirror_transform(mirror, mirrorNode->pos, mirrorNode->angle, mirrorNode->scale);
        vec3f_copy(&mirrorObj->oPosX, mirrorNode->pos);

        // Don't render duplicated mirror objects
        if (!mirror_check_duplicate(mirrorObj)) {
            geo_invert_culling(mirrorObj->oMirrorObjInvertCulling);
            geo_process_object(mirrorObj);
            geo_invert_culling(!mirrorObj->oMirrorObjInvertCulling);
        }
    }
}

void geo_process_mirrors(struct Object *obj) {

    // Reject inactive objects
    // Invisible objects can still be mirrored (for example to make an object visible only in the mirror)
    if (!(obj->header.gfx.node.flags & GRAPH_RENDER_ACTIVE) || obj->header.gfx.sharedChild == NULL) {
        return;
    }

    // Reject mirrors and camera lakitu
    if (obj->behavior == bhvMirror ||
        obj->behavior == bhvCameraLakitu ||
        (obj->behavior == bhvCloud && obj->parentObj && obj->parentObj->behavior == bhvCameraLakitu) ||
        (obj->behavior == bhvCloudPart && obj->parentObj && obj->parentObj->behavior == bhvCloud && obj->parentObj->parentObj && obj->parentObj->parentObj->behavior == bhvCameraLakitu)) {
        return;
    }

    // Reject reflection above limit
    u8 numReflections = 0;
    for (struct Object *mirrorObj = obj; geo_is_mirror_object(mirrorObj); mirrorObj = mirrorObj->oMirrorObjPrevObj) {
        numReflections++;
    }
    if (numReflections >= gBehaviorValues.MirrorsMaxReflections) {
        return;
    }

    // Process mirrors
    struct Object *mirror = obj_get_first_with_behavior_id(id_bhvMirror);
    while (mirror) {
        geo_process_mirror(mirror, obj);
        mirror = obj_get_next_with_same_behavior_id(mirror);
    }
}

void geo_reset_mirrors() {
    sMirrorObjects.count = 0;
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
    return obj && obj->behavior == bhvMirrorObject;
}

void geo_invert_culling(bool invert) {
    static Gfx sObjCullInvertGfx[2][2] = {
        { gsSPClearGeometryMode(G_CULL_INVERT_EXT), gsSPEndDisplayList() },
        { gsSPSetGeometryMode(G_CULL_INVERT_EXT), gsSPEndDisplayList() },
    };
    for (s16 layer = 0; layer != 8; ++layer) {
        geo_append_display_list(sObjCullInvertGfx[invert], layer);
    }
}
