#include <PR/ultratypes.h>

#include "sm64.h"
#include "area.h"
#include "behavior_actions.h"
#include "behavior_data.h"
#include "camera.h"
#include "debug.h"
#include "dialog_ids.h"
#include "engine/behavior_script.h"
#include "engine/geo_layout.h"
#include "engine/math_util.h"
#include "engine/surface_collision.h"
#include "game_init.h"
#include "hardcoded.h"
#include "helper_macros.h"
#include "ingame_menu.h"
#include "interaction.h"
#include "level_table.h"
#include "level_update.h"
#include "mario.h"
#include "mario_actions_cutscene.h"
#include "memory.h"
#include "obj_behaviors.h"
#include "object_helpers.h"
#include "object_list_processor.h"
#include "rendering_graph_node.h"
#include "spawn_object.h"
#include "spawn_sound.h"
#include "pc/network/network.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/lua/utils/smlua_camera_utils.h"
#include "first_person_cam.h"

u8 (*gContinueDialogFunction)(void) = NULL;
struct Object* gContinueDialogFunctionObject = NULL;

s8 D_8032F0A0[] = { -8, 8, -4, 4 };
s16 D_8032F0A4[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80 };
static s8 sLevelsWithRooms[] = { LEVEL_BBH, LEVEL_CASTLE, LEVEL_HMC, -1 };

#define o gCurrentObject

s32 clear_move_flag(u32 *bitSet, s32 flag) {
    if (*bitSet & flag) {
        *bitSet &= flag ^ 0xFFFFFFFF;
        return TRUE;
    } else {
        return FALSE;
    }
}

Gfx *geo_update_projectile_pos_from_parent(s32 callContext, UNUSED struct GraphNode *node, Mat4 mtx) {
    Mat4 sp20;
    struct Object *sp1C;

    if (callContext == GEO_CONTEXT_RENDER) {
        sp1C = (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer
        if (sp1C->prevObj) {
            create_transformation_from_matrices(sp20, mtx, *gCurGraphNodeCamera->matrixPtr);
            obj_update_pos_from_parent_transformation(sp20, sp1C->prevObj);
            obj_set_gfx_pos_from_pos(sp1C->prevObj);
        }
    }
    return NULL;
}

Gfx *geo_update_layer_transparency(s32 callContext, struct GraphNode *node, UNUSED void *context) {
    Gfx *dlStart, *dlHead;
    struct Object *objectGraphNode;
    struct GraphNodeGenerated *currentGraphNode;
    UNUSED struct GraphNodeGenerated *sp2C;
    s32 objectOpacity;

    dlStart = NULL;

    if (callContext == GEO_CONTEXT_RENDER) {
        objectGraphNode = (struct Object *) gCurGraphNodeObject;
        currentGraphNode = (struct GraphNodeGenerated *) node;
        sp2C = (struct GraphNodeGenerated *) node;

        if (gCurGraphNodeHeldObject) {
            objectGraphNode = gCurGraphNodeHeldObject->objNode;
        }

        objectOpacity = objectGraphNode->oOpacity;
        dlStart = alloc_display_list(sizeof(Gfx) * 3);
        if (dlStart == NULL) { return NULL; }

        dlHead = dlStart;

        if (objectOpacity == 0xFF) {
            if (currentGraphNode->parameter == 20) {
                currentGraphNode->fnNode.node.flags =
                0x600 | (currentGraphNode->fnNode.node.flags & 0xFF);
            } else {
                currentGraphNode->fnNode.node.flags =
                0x100 | (currentGraphNode->fnNode.node.flags & 0xFF);
            }

            if (currentGraphNode->parameter != 30) {
                objectGraphNode->oAnimState = 0;
            }
        } else {
            if (currentGraphNode->parameter == 20) {
                currentGraphNode->fnNode.node.flags =
                0x600 | (currentGraphNode->fnNode.node.flags & 0xFF);
            } else {
                currentGraphNode->fnNode.node.flags =
                0x500 | (currentGraphNode->fnNode.node.flags & 0xFF);
            }

            if (currentGraphNode->parameter != 30) {
                objectGraphNode->oAnimState = 1;
            }

#ifdef VERSION_JP
            if (currentGraphNode->parameter == 10) {
                if (gDebugInfo[DEBUG_PAGE_ENEMYINFO][3]) {
                    gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
                }
            } else {
                if (objectGraphNode->activeFlags & ACTIVE_FLAG_DITHERED_ALPHA) {
                    gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
                }
            }
#else // gDebugInfo accesses were removed in all non-JP versions.
            if (objectOpacity == 0 && segmented_to_virtual(smlua_override_behavior(bhvBowser)) == objectGraphNode->behavior) {
                objectGraphNode->oAnimState = 2;
            }
            // the debug info check was removed in US. so we need to
            // perform the only necessary check instead of the debuginfo
            // one.
            if (currentGraphNode->parameter != 10) {
                if (objectGraphNode->activeFlags & ACTIVE_FLAG_DITHERED_ALPHA) {
                    gDPSetAlphaCompare(dlHead++, G_AC_DITHER);
                }
            }
#endif
        }

        gDPSetEnvColor(dlHead++, 255, 255, 255, objectOpacity);
        gSPEndDisplayList(dlHead);
    }

    return dlStart;
}

/**
 * @bug Every geo function declares the 3 parameters of callContext, node, and
 * the matrix array. This one (see also geo_switch_area) doesn't. When executed,
 * the node function executor passes the 3rd argument to a function that doesn't
 * declare it. This is undefined behavior, but harmless in practice due to the
 * o32 calling convention.
 */
#ifdef AVOID_UB
Gfx *geo_switch_anim_state(s32 callContext, struct GraphNode *node, UNUSED void *context) {
#else
Gfx *geo_switch_anim_state(s32 callContext, struct GraphNode *node) {
#endif
    struct Object *obj;
    struct GraphNodeSwitchCase *switchCase;

    if (callContext == GEO_CONTEXT_RENDER) {
        obj = (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer

        // move to a local var because GraphNodes are passed in all geo functions.
        // cast the pointer.
        switchCase = (struct GraphNodeSwitchCase *) node;

        if (gCurGraphNodeHeldObject != NULL) {
            obj = gCurGraphNodeHeldObject->objNode;
        }

        // if the case is greater than the number of cases, set to 0 to avoid overflowing
        // the switch.
        if (obj->oAnimState >= switchCase->numCases) {
            obj->oAnimState = 0;
        }

        // assign the case number for execution.
        switchCase->selectedCase = obj->oAnimState;
    }

    return NULL;
}

//! @bug Same issue as geo_switch_anim_state.
#ifdef AVOID_UB
Gfx *geo_switch_area(s32 callContext, struct GraphNode *node, UNUSED void *context) {
#else
Gfx *geo_switch_area(s32 callContext, struct GraphNode *node) {
#endif
    s16 sp26;
    struct Surface *sp20;
    UNUSED struct Object *sp1C =
        (struct Object *) gCurGraphNodeObject; // TODO: change global type to Object pointer
    struct GraphNodeSwitchCase *switchCase = (struct GraphNodeSwitchCase *) node;

    if (callContext == GEO_CONTEXT_RENDER) {
        if (gMarioObject == NULL) {
            switchCase->selectedCase = 0;
        } else {
            gFindFloorIncludeSurfaceIntangible = TRUE;

            find_floor(gMarioObject->oPosX, gMarioObject->oPosY, gMarioObject->oPosZ, &sp20);
            if (sp20) {
                gMarioCurrentRoom = sp20->room;
                gMarioStates[0].currentRoom = gMarioCurrentRoom;
                sp26 = sp20->room - 1;
                print_debug_top_down_objectinfo("areainfo %d", sp20->room);

                if (sp26 >= 0) {
                    switchCase->selectedCase = sp26;
                }
            }

            // display both sides of door
            gDoorCurrentRoom = 0;
            for (s32 i = 0; i < MAX_PLAYERS; i++) {
                struct MarioState* m = &gMarioStates[i];
                if (!is_player_active(m)) { continue; }

                struct Object* door = m ? m->interactObj : NULL;
                if (door == NULL) { continue; }
                if (door->oInteractType != INTERACT_DOOR) { continue; }
                if (door->oAction == 0) { continue; }
                if (door->oDoorUnkF8 < 60 && gDoorAdjacentRooms[door->oDoorUnkF8][0] != gMarioCurrentRoom && gDoorAdjacentRooms[door->oDoorUnkF8][1] != gMarioCurrentRoom) { continue; }

                find_floor(door->oHomeX, door->oHomeY, door->oHomeZ, &sp20);
                if (!sp20) { continue; }

                sp26 = sp20->room - 1;
                if (sp26 == 0) { continue; }

                gDoorCurrentRoom = sp20->room;
                switchCase->selectedCase = sp26;
                break;
            }
        }
    } else {
        switchCase->selectedCase = 0;
    }

    return NULL;
}

Gfx *geo_choose_area_ext(UNUSED s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    struct GraphNodeSwitchCase *switchCase;
    switchCase = (struct GraphNodeSwitchCase *) node;
    switchCase->selectedCase = sWarpDest.areaIdx-1;
    return NULL;
}

void obj_update_pos_from_parent_transformation(Mat4 a0, struct Object *a1) {
    if (a1 == NULL) { return; }
    f32 spC = a1->oParentRelativePosX;
    f32 sp8 = a1->oParentRelativePosY;
    f32 sp4 = a1->oParentRelativePosZ;

    a1->oPosX = spC * a0[0][0] + sp8 * a0[1][0] + sp4 * a0[2][0] + a0[3][0];
    a1->oPosY = spC * a0[0][1] + sp8 * a0[1][1] + sp4 * a0[2][1] + a0[3][1];
    a1->oPosZ = spC * a0[0][2] + sp8 * a0[1][2] + sp4 * a0[2][2] + a0[3][2];
}

void obj_apply_scale_to_matrix(struct Object *obj, Mat4 dst, Mat4 src) {
    if (obj == NULL) { return; }
    dst[0][0] = src[0][0] * obj->header.gfx.scale[0];
    dst[1][0] = src[1][0] * obj->header.gfx.scale[1];
    dst[2][0] = src[2][0] * obj->header.gfx.scale[2];
    dst[3][0] = src[3][0];

    dst[0][1] = src[0][1] * obj->header.gfx.scale[0];
    dst[1][1] = src[1][1] * obj->header.gfx.scale[1];
    dst[2][1] = src[2][1] * obj->header.gfx.scale[2];
    dst[3][1] = src[3][1];

    dst[0][2] = src[0][2] * obj->header.gfx.scale[0];
    dst[1][2] = src[1][2] * obj->header.gfx.scale[1];
    dst[2][2] = src[2][2] * obj->header.gfx.scale[2];
    dst[3][2] = src[3][2];

    dst[0][3] = src[0][3];
    dst[1][3] = src[1][3];
    dst[2][3] = src[2][3];
    dst[3][3] = src[3][3];
}

void create_transformation_from_matrices(Mat4 a0, Mat4 a1, Mat4 a2) {
    f32 spC, sp8, sp4;

    spC = a2[3][0] * a2[0][0] + a2[3][1] * a2[0][1] + a2[3][2] * a2[0][2];
    sp8 = a2[3][0] * a2[1][0] + a2[3][1] * a2[1][1] + a2[3][2] * a2[1][2];
    sp4 = a2[3][0] * a2[2][0] + a2[3][1] * a2[2][1] + a2[3][2] * a2[2][2];

    a0[0][0] = a1[0][0] * a2[0][0] + a1[0][1] * a2[0][1] + a1[0][2] * a2[0][2];
    a0[0][1] = a1[0][0] * a2[1][0] + a1[0][1] * a2[1][1] + a1[0][2] * a2[1][2];
    a0[0][2] = a1[0][0] * a2[2][0] + a1[0][1] * a2[2][1] + a1[0][2] * a2[2][2];

    a0[1][0] = a1[1][0] * a2[0][0] + a1[1][1] * a2[0][1] + a1[1][2] * a2[0][2];
    a0[1][1] = a1[1][0] * a2[1][0] + a1[1][1] * a2[1][1] + a1[1][2] * a2[1][2];
    a0[1][2] = a1[1][0] * a2[2][0] + a1[1][1] * a2[2][1] + a1[1][2] * a2[2][2];

    a0[2][0] = a1[2][0] * a2[0][0] + a1[2][1] * a2[0][1] + a1[2][2] * a2[0][2];
    a0[2][1] = a1[2][0] * a2[1][0] + a1[2][1] * a2[1][1] + a1[2][2] * a2[1][2];
    a0[2][2] = a1[2][0] * a2[2][0] + a1[2][1] * a2[2][1] + a1[2][2] * a2[2][2];

    a0[3][0] = a1[3][0] * a2[0][0] + a1[3][1] * a2[0][1] + a1[3][2] * a2[0][2] - spC;
    a0[3][1] = a1[3][0] * a2[1][0] + a1[3][1] * a2[1][1] + a1[3][2] * a2[1][2] - sp8;
    a0[3][2] = a1[3][0] * a2[2][0] + a1[3][1] * a2[2][1] + a1[3][2] * a2[2][2] - sp4;

    a0[0][3] = 0;
    a0[1][3] = 0;
    a0[2][3] = 0;
    a0[3][3] = 1.0f;
}

void obj_set_held_state(struct Object *obj, const BehaviorScript *heldBehavior) {
    if (obj == NULL) { return; }
    obj->parentObj = o;

    if (obj->oFlags & OBJ_FLAG_HOLDABLE) {
        if (heldBehavior == smlua_override_behavior(bhvCarrySomething3)) {
            obj->oHeldState = HELD_HELD;
        }

        if (heldBehavior == smlua_override_behavior(bhvCarrySomething5)) {
            obj->oHeldState = HELD_THROWN;
            obj->heldByPlayerIndex = 0;
        }

        if (heldBehavior == smlua_override_behavior(bhvCarrySomething4)) {
            obj->oHeldState = HELD_DROPPED;
            obj->heldByPlayerIndex = 0;
        }
    } else {
        obj->curBhvCommand = segmented_to_virtual(smlua_override_behavior(heldBehavior));
        obj->bhvStackIndex = 0;
    }
}

f32 lateral_dist_between_objects(struct Object *obj1, struct Object *obj2) {
    if (obj1 == NULL || obj2 == NULL) { return 0; }
    f32 dx = obj1->oPosX - obj2->oPosX;
    f32 dz = obj1->oPosZ - obj2->oPosZ;

    return sqrtf(dx * dx + dz * dz);
}

f32 dist_between_objects(struct Object *obj1, struct Object *obj2) {
    if (obj1 == NULL || obj2 == NULL) { return 0; }
    f32 dx = obj1->oPosX - obj2->oPosX;
    f32 dy = obj1->oPosY - obj2->oPosY;
    f32 dz = obj1->oPosZ - obj2->oPosZ;

    return sqrtf(dx * dx + dy * dy + dz * dz);
}

f32 dist_between_object_and_point(struct Object *obj, f32 pointX, f32 pointY, f32 pointZ) {
    if (obj == NULL) { return 0; }
    f32 dx = (f32)obj->oPosX - pointX;
    f32 dy = (f32)obj->oPosY - pointY;
    f32 dz = (f32)obj->oPosZ - pointZ;

    return sqrtf(dx * dx + dy * dy + dz * dz);
}

void cur_obj_forward_vel_approach_upward(f32 target, f32 increment) {
    if (!o) { return; }
    if (o->oForwardVel >= target) {
        o->oForwardVel = target;
    } else {
        o->oForwardVel += increment;
    }
}

s32 approach_f32_signed(f32 *value, f32 target, f32 increment) {
    if (value == NULL) { return 0; }
    s32 reachedTarget = FALSE;

    *value += increment;

    if (increment >= 0.0f) {
        if (*value > target) {
            *value = target;
            reachedTarget = TRUE;
        }
    } else {
        if (*value < target) {
            *value = target;
            reachedTarget = TRUE;
        }
    }

    return reachedTarget;
}

f32 approach_f32_symmetric(f32 value, f32 target, f32 increment) {
    f32 dist;

    if ((dist = target - value) >= 0.0f) {
        if (dist > increment) {
            value += increment;
        } else {
            value = target;
        }
    } else {
        if (dist < -increment) {
            value -= increment;
        } else {
            value = target;
        }
    }

    return value;
}

s16 approach_s16_symmetric(s16 value, s16 target, s16 increment) {
    s16 dist = target - value;

    if (dist >= 0) {
        if (dist > increment) {
            value += increment;
        } else {
            value = target;
        }
    } else {
        if (dist < -increment) {
            value -= increment;
        } else {
            value = target;
        }
    }

    return value;
}

s32 cur_obj_rotate_yaw_toward(s16 target, s16 increment) {
    if (!o) { return 0; }
    s16 startYaw;

    startYaw = (s16) o->oMoveAngleYaw;
    o->oMoveAngleYaw = approach_s16_symmetric(o->oMoveAngleYaw, target, increment);

    if ((o->oAngleVelYaw = (s16)((s16) o->oMoveAngleYaw - startYaw)) == 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s16 obj_angle_to_object(struct Object *obj1, struct Object *obj2) {
    if (obj1 == NULL || obj2 == NULL) { return 0; }

    f32 z1, x1, z2, x2;
    s16 angle;

    z1 = obj1->oPosZ; z2 = obj2->oPosZ; // ordering of instructions..
    x1 = obj1->oPosX; x2 = obj2->oPosX;

    angle = atan2s(z2 - z1, x2 - x1);
    return angle;
}

s16 obj_pitch_to_object(struct Object* obj, struct Object* target) {
    if (obj == NULL) { return 0; }
    if (!target) { return 0; }
    f32 a, b, c, d;
    a = target->oPosX - obj->oPosX;
    c = target->oPosZ - obj->oPosZ;
    a = sqrtf(a * a + c * c);

    b = -obj->oPosY;
    d = -target->oPosY;

    return atan2s(a, d - b);
}

s16 obj_angle_to_point(struct Object *obj, f32 pointX, f32 pointZ) {
    if (obj == NULL) { return 0; }
    f32 z1, x1, z2, x2;
    s16 angle;

    z1 = obj->oPosZ; z2 = pointZ; //ordering of instructions..
    x1 = obj->oPosX; x2 = pointX;

    angle = atan2s(z2 - z1, x2 - x1);
    return angle;
}

s16 obj_turn_toward_object(struct Object *obj, struct Object *target, s16 angleIndex, s16 turnAmount) {
    if (obj == NULL || target == NULL || !o) { return 0; }
    f32 a, b, c, d;
    UNUSED s32 unused;
    s16 targetAngle = 0;
    s16 startAngle = 0;

    switch (angleIndex) {
        case O_MOVE_ANGLE_PITCH_INDEX:
        case O_FACE_ANGLE_PITCH_INDEX:
            a = target->oPosX - obj->oPosX;
            c = target->oPosZ - obj->oPosZ;
            a = sqrtf(a * a + c * c);

            b = -obj->oPosY;
            d = -target->oPosY;

            targetAngle = atan2s(a, d - b);
            break;

        case O_MOVE_ANGLE_YAW_INDEX:
        case O_FACE_ANGLE_YAW_INDEX:
            a = obj->oPosZ;
            c = target->oPosZ;
            b = obj->oPosX;
            d = target->oPosX;

            targetAngle = atan2s(c - a, d - b);
            break;
    }

    startAngle = o->rawData.asU32[angleIndex];
    o->rawData.asU32[angleIndex] = approach_s16_symmetric(startAngle, targetAngle, turnAmount);
    return targetAngle;
}

void obj_set_parent_relative_pos(struct Object *obj, s16 relX, s16 relY, s16 relZ) {
    if (obj == NULL) { return; }
    
    obj->oParentRelativePosX = relX;
    obj->oParentRelativePosY = relY;
    obj->oParentRelativePosZ = relZ;
}

void obj_set_pos(struct Object *obj, s16 x, s16 y, s16 z) {
    if (obj == NULL) { return; }
    
    obj->oPosX = x;
    obj->oPosY = y;
    obj->oPosZ = z;
}

void obj_set_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll) {
    if (obj == NULL) { return; }
    
    obj->oFaceAnglePitch = pitch;
    obj->oFaceAngleYaw = yaw;
    obj->oFaceAngleRoll = roll;

    obj->oMoveAnglePitch = pitch;
    obj->oMoveAngleYaw = yaw;
    obj->oMoveAngleRoll = roll;
}

void obj_set_move_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll) {
    if (obj == NULL) { return; }
    
    obj->oMoveAnglePitch = pitch;
    obj->oMoveAngleYaw = yaw;
    obj->oMoveAngleRoll = roll;
}

void obj_set_face_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll) {
    if (obj == NULL) { return; }
    
    obj->oFaceAnglePitch = pitch;
    obj->oFaceAngleYaw = yaw;
    obj->oFaceAngleRoll = roll;
}

void obj_set_gfx_angle(struct Object *obj, s16 pitch, s16 yaw, s16 roll) {
    if (obj == NULL) { return; }
    
    obj->header.gfx.angle[0] = pitch;
    obj->header.gfx.angle[1] = yaw;
    obj->header.gfx.angle[2] = roll;
}

void obj_set_gfx_pos(struct Object *obj, f32 x, f32 y, f32 z) {
    if (obj == NULL) { return; }
    
    obj->header.gfx.pos[0] = x;
    obj->header.gfx.pos[1] = y;
    obj->header.gfx.pos[2] = z;
}

void obj_set_gfx_scale(struct Object *obj, f32 x, f32 y, f32 z) {
    if (obj == NULL) { return; }
    
    obj->header.gfx.scale[0] = x;
    obj->header.gfx.scale[1] = y;
    obj->header.gfx.scale[2] = z;
}

/*
 * Spawns an object at an absolute location with a specified angle.
 */
struct Object *spawn_object_abs_with_rot(struct Object *parent, s16 uselessArg, u32 model,
                                         const BehaviorScript *behavior,
                                         s16 x, s16 y, s16 z, s16 rx, s16 ry, s16 rz) {
    // 'uselessArg' is unused in the function spawn_object_at_origin()
    struct Object *newObj = spawn_object_at_origin(parent, uselessArg, model, behavior);
    if (newObj == NULL) { return NULL; }
    obj_set_pos(newObj, x, y, z);
    obj_set_angle(newObj, rx, ry, rz);

    return newObj;
}

/*
 * Spawns an object relative to the parent with a specified angle... is what it is supposed to do.
 * The rz argument is never used, and the z offset is used for z-rotation instead. This is most likely
 * a copy-paste typo by one of the programmers.
 */
struct Object *spawn_object_rel_with_rot(struct Object *parent, u32 model, const BehaviorScript *behavior,
                                         s16 xOff, s16 yOff, s16 zOff, s16 rx, s16 ry, UNUSED s16 rz) {
    struct Object *newObj = spawn_object_at_origin(parent, 0, model, behavior);
    if (newObj == NULL) { return NULL; }
    newObj->oFlags |= OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT;
    obj_set_parent_relative_pos(newObj, xOff, yOff, zOff);
    obj_set_angle(newObj, rx, ry, zOff); // Nice typo you got there Nintendo.

    return newObj;
}

struct Object *spawn_obj_with_transform_flags(struct Object *sp20, s32 model, const BehaviorScript *sp28) {
    struct Object *sp1C = spawn_object(sp20, model, sp28);
    if (sp1C == NULL) { return NULL; }
    sp1C->oFlags |= OBJ_FLAG_0020 | OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM;
    return sp1C;
}

struct Object *spawn_water_droplet(struct Object *parent, struct WaterDropletParams *params) {
    f32 randomScale;
    struct Object *newObj = spawn_object(parent, params->model, params->behavior);
    if (newObj == NULL) { return NULL; }

    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE) {
        newObj->oMoveAngleYaw = random_u16();
    }

    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE_INCR_PLUS_8000) {
        newObj->oMoveAngleYaw = (s16)(newObj->oMoveAngleYaw + 0x8000)
                                + (s16) random_f32_around_zero(params->moveAngleRange);
    }

    if (params->flags & WATER_DROPLET_FLAG_RAND_ANGLE_INCR) {
        newObj->oMoveAngleYaw =
            (s16) newObj->oMoveAngleYaw + (s16) random_f32_around_zero(params->moveAngleRange);
    }

    if (params->flags & WATER_DROPLET_FLAG_SET_Y_TO_WATER_LEVEL) {
        newObj->oPosY = find_water_level(newObj->oPosX, newObj->oPosZ);
    }

    if (params->flags & WATER_DROPLET_FLAG_RAND_OFFSET_XZ) {
        obj_translate_xz_random(newObj, params->moveRange);
    }

    if (params->flags & WATER_DROPLET_FLAG_RAND_OFFSET_XYZ) {
        obj_translate_xyz_random(newObj, params->moveRange);
    }

    newObj->oForwardVel = random_float() * params->randForwardVelScale + params->randForwardVelOffset;
    newObj->oVelY = random_float() * params->randYVelScale + params->randYVelOffset;

    randomScale = random_float() * params->randSizeScale + params->randSizeOffset;
    obj_scale(newObj, randomScale);

    return newObj;
}

struct Object *spawn_object_at_origin(struct Object *parent, UNUSED s32 unusedArg, u32 model,
                                      const BehaviorScript *behavior) {
    struct Object *obj;
    const BehaviorScript *behaviorAddr;

    behaviorAddr = segmented_to_virtual(behavior);
    obj = create_object(behaviorAddr);
    if (obj == NULL) { return NULL; }

    obj->parentObj = parent;
    if (parent) {
        obj->header.gfx.areaIndex = parent->header.gfx.areaIndex;
        obj->header.gfx.activeAreaIndex = parent->header.gfx.areaIndex;
    }
    obj->globalPlayerIndex = 0;

    geo_obj_init((struct GraphNodeObject *) &obj->header.gfx, dynos_model_get_geo(model), gVec3fZero, gVec3sZero);
    smlua_call_event_hooks_object_model_param(HOOK_OBJECT_SET_MODEL, obj, model);

    return obj;
}

struct Object *spawn_object(struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);
    if (obj == NULL) { return NULL; }

    obj_copy_pos_and_angle(obj, parent);

    return obj;
}

struct Object *try_to_spawn_object(s16 offsetY, f32 scale, struct Object *parent, s32 model,
                                   const BehaviorScript *behavior) {
    struct Object *obj;

    if (gFreeObjectList.next != NULL) {
        obj = spawn_object(parent, model, behavior);
        if (obj == NULL) { return NULL; }
        obj->oPosY += offsetY;
        obj_scale(obj, scale);
        return obj;
    } else {
        return NULL;
    }
}

struct Object *spawn_object_with_scale(struct Object *parent, s32 model, const BehaviorScript *behavior, f32 scale) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);
    if (obj == NULL) { return NULL; }

    obj_copy_pos_and_angle(obj, parent);
    obj_scale(obj, scale);

    return obj;
}

void obj_build_relative_transform(struct Object *obj) {
    obj_build_transform_from_pos_and_angle(obj, O_PARENT_RELATIVE_POS_INDEX, O_FACE_ANGLE_INDEX);
    obj_translate_local(obj, O_POS_INDEX, O_PARENT_RELATIVE_POS_INDEX);
}

struct Object *spawn_object_relative(s16 behaviorParam, s16 relativePosX, s16 relativePosY, s16 relativePosZ,
                                     struct Object *parent, s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_at_origin(parent, 0, model, behavior);
    if (obj == NULL) { return NULL; }

    obj_copy_pos_and_angle(obj, parent);
    obj_set_parent_relative_pos(obj, relativePosX, relativePosY, relativePosZ);
    obj_build_relative_transform(obj);

    obj->oBehParams2ndByte = behaviorParam;
    obj->oBehParams = (behaviorParam & 0xFF) << 16;

    return obj;
}

struct Object *spawn_object_relative_with_scale(s16 behaviorParam, s16 relativePosX, s16 relativePosY,
                                                s16 relativePosZ, f32 scale, struct Object *parent,
                                                s32 model, const BehaviorScript *behavior) {
    struct Object *obj = spawn_object_relative(behaviorParam, relativePosX, relativePosY, relativePosZ,
                                               parent, model, behavior);
    if (obj == NULL) { return NULL; }
    obj_scale(obj, scale);

    return obj;
}

void cur_obj_move_using_vel(void) {
    if (!o) { return; }
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;
}

void obj_copy_graph_y_offset(struct Object *dst, struct Object *src) {
    if (!dst || !src) { return; }
    dst->oGraphYOffset = src->oGraphYOffset;
}

void obj_copy_pos_and_angle(struct Object *dst, struct Object *src) {
    obj_copy_pos(dst, src);
    obj_copy_angle(dst, src);
}

void obj_copy_pos(struct Object *dst, struct Object *src) {
    if (!dst || !src) { return; }
    dst->oPosX = src->oPosX;
    dst->oPosY = src->oPosY;
    dst->oPosZ = src->oPosZ;
}

void obj_copy_angle(struct Object *dst, struct Object *src) {
    if (!dst || !src) { return; }
    dst->oMoveAnglePitch = src->oMoveAnglePitch;
    dst->oMoveAngleYaw = src->oMoveAngleYaw;
    dst->oMoveAngleRoll = src->oMoveAngleRoll;

    dst->oFaceAnglePitch = src->oFaceAnglePitch;
    dst->oFaceAngleYaw = src->oFaceAngleYaw;
    dst->oFaceAngleRoll = src->oFaceAngleRoll;
}

void obj_set_gfx_pos_from_pos(struct Object *obj) {
    if (!obj) { return; }
    obj->header.gfx.pos[0] = obj->oPosX;
    obj->header.gfx.pos[1] = obj->oPosY;
    obj->header.gfx.pos[2] = obj->oPosZ;
}

void obj_init_animation(struct Object *obj, s32 animIndex) {
    if (!o || !obj) { return; }
    struct AnimationTable *animations = o->oAnimations;
    if (animations && (u32)animIndex < animations->count) {
        geo_obj_init_animation(&obj->header.gfx, animations->anims[animIndex]);
    }
}

/**
 * Multiply a vector by a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
void linear_mtxf_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v) {
    s32 i;
    for (i = 0; i < 3; i++) {
        dst[i] = m[0][i] * v[0] + m[1][i] * v[1] + m[2][i] * v[2];
    }
}

/**
 * Multiply a vector by the transpose of a matrix of the form
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | ? ? ? 0 |
 * | 0 0 0 1 |
 * i.e. a matrix representing a linear transformation over 3 space.
 */
void linear_mtxf_transpose_mul_vec3f(Mat4 m, Vec3f dst, Vec3f v) {
    s32 i;
    for (i = 0; i < 3; i++) {
        dst[i] = m[i][0] * v[0] + m[i][1] * v[1] + m[i][2] * v[2];
    }
}

void obj_apply_scale_to_transform(struct Object *obj) {
    if (obj == NULL) { return; }
    f32 scaleX = obj->header.gfx.scale[0];
    f32 scaleY = obj->header.gfx.scale[1];
    f32 scaleZ = obj->header.gfx.scale[2];

    obj->transform[0][0] *= scaleX;
    obj->transform[0][1] *= scaleX;
    obj->transform[0][2] *= scaleX;

    obj->transform[1][0] *= scaleY;
    obj->transform[1][1] *= scaleY;
    obj->transform[1][2] *= scaleY;

    obj->transform[2][0] *= scaleZ;
    obj->transform[2][1] *= scaleZ;
    obj->transform[2][2] *= scaleZ;
}

void obj_copy_scale(struct Object *dst, struct Object *src) {
    if (dst == NULL || src == NULL) { return; }
    dst->header.gfx.scale[0] = src->header.gfx.scale[0];
    dst->header.gfx.scale[1] = src->header.gfx.scale[1];
    dst->header.gfx.scale[2] = src->header.gfx.scale[2];
}

void obj_scale_xyz(struct Object *obj, f32 xScale, f32 yScale, f32 zScale) {
    if (obj == NULL) { return; }
    obj->header.gfx.scale[0] = xScale;
    obj->header.gfx.scale[1] = yScale;
    obj->header.gfx.scale[2] = zScale;
}

void obj_scale(struct Object *obj, f32 scale) {
    if (obj == NULL) { return; }
    obj->header.gfx.scale[0] = scale;
    obj->header.gfx.scale[1] = scale;
    obj->header.gfx.scale[2] = scale;
}

void cur_obj_scale(f32 scale) {
    if (!o) { return; }
    o->header.gfx.scale[0] = scale;
    o->header.gfx.scale[1] = scale;
    o->header.gfx.scale[2] = scale;
}

void cur_obj_init_animation(s32 animIndex) {
    if (!o) { return; }
    struct AnimationTable *animations = o->oAnimations;
    if (animations && (u32)animIndex < animations->count) {
        geo_obj_init_animation(&o->header.gfx, animations->anims[animIndex]);
    }
}

void cur_obj_init_animation_with_sound(s32 animIndex) {
    if (!o) { return; }
    struct AnimationTable *animations = o->oAnimations;
    if (animations && (u32)animIndex < animations->count) {
        geo_obj_init_animation(&o->header.gfx, animations->anims[animIndex]);
    }
    o->oSoundStateID = animIndex;
}

void obj_init_animation_with_accel_and_sound(struct Object *obj, s32 animIndex, f32 accel) {
    if (!o) { return; }
    if (obj != NULL) {
        struct AnimationTable *animations = o->oAnimations;
        if (animations && (u32)animIndex < animations->count) {
            s32 animAccel = (s32)(accel * 65536.0f);
            geo_obj_init_animation_accel(&obj->header.gfx, animations->anims[animIndex], animAccel);
        }
        obj->oSoundStateID = animIndex;
    }
}

void cur_obj_init_animation_with_accel_and_sound(s32 animIndex, f32 accel) {
    if (!o) { return; }
    struct AnimationTable *animations = o->oAnimations;
    if (animations && (u32)animIndex < animations->count) {
        s32 animAccel = (s32)(accel * 65536.0f);
        geo_obj_init_animation_accel(&o->header.gfx, animations->anims[animIndex], animAccel);
    }
    o->oSoundStateID = animIndex;
}

void obj_init_animation_with_sound(struct Object *obj, const struct AnimationTable* animations, s32 animIndex) {
    if (obj == NULL) { return; }
    if (animations && (u32)animIndex < animations->count) {
        geo_obj_init_animation(&obj->header.gfx, animations->anims[animIndex]);
    }
    obj->oSoundStateID = animIndex;
}

void cur_obj_enable_rendering_and_become_tangible(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
    obj->oIntangibleTimer = 0;
}

void cur_obj_enable_rendering(void) {
    if (!o) { return; }
    o->header.gfx.node.flags |= GRAPH_RENDER_ACTIVE;
}

void cur_obj_disable_rendering_and_become_intangible(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
    obj->oIntangibleTimer = -1;
}

void cur_obj_disable_rendering(void) {
    if (!o) { return; }
    o->header.gfx.node.flags &= ~GRAPH_RENDER_ACTIVE;
}

void cur_obj_unhide(void) {
    if (!o) { return; }
    o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
}

void cur_obj_hide(void) {
    if (!o) { return; }
    o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
}

void cur_obj_set_pos_relative(struct Object *other, f32 dleft, f32 dy, f32 dforward) {
    if (!o) { return; }
    if (other == NULL) { return; }
    f32 facingZ = coss(other->oMoveAngleYaw);
    f32 facingX = sins(other->oMoveAngleYaw);

    f32 dz = dforward * facingZ - dleft * facingX;
    f32 dx = dforward * facingX + dleft * facingZ;

    o->oMoveAngleYaw = other->oMoveAngleYaw;

    o->oPosX = other->oPosX + dx;
    o->oPosY = other->oPosY + dy;
    o->oPosZ = other->oPosZ + dz;
}

void cur_obj_set_pos_relative_to_parent(f32 dleft, f32 dy, f32 dforward) {
    if (!o) { return; }
    cur_obj_set_pos_relative(o->parentObj, dleft, dy, dforward);
}

void cur_obj_enable_rendering_2(void) {
    cur_obj_enable_rendering();
}

void cur_obj_unused_init_on_floor(void) {
    if (!o) { return; }
    cur_obj_enable_rendering();

    o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    if (o->oPosY < gLevelValues.floorLowerLimitMisc) {
        cur_obj_set_pos_relative_to_parent(0, 0, -70);
        o->oPosY = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    }
}

void obj_set_face_angle_to_move_angle(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->oFaceAnglePitch = obj->oMoveAnglePitch;
    obj->oFaceAngleYaw = obj->oMoveAngleYaw;
    obj->oFaceAngleRoll = obj->oMoveAngleRoll;
}

u32 get_object_list_from_behavior(const BehaviorScript *behavior) {
    if (!behavior) { return OBJ_LIST_DEFAULT; }
    u32 objectList;

    // If the first behavior command is "begin", then get the object list header
    // from there
    if (behavior && (behavior[0] >> 24) == 0) {
        objectList = (behavior[0] >> 16) & 0xFFFF;
    } else {
        objectList = OBJ_LIST_DEFAULT;
    }

    return objectList;
}

struct Object *cur_obj_nearest_object_with_behavior(const BehaviorScript *behavior) {
    if (!behavior) { return NULL; }
    struct Object *obj;
    f32 dist;

    obj = cur_obj_find_nearest_object_with_behavior(behavior, &dist);

    return obj;
}

f32 cur_obj_dist_to_nearest_object_with_behavior(const BehaviorScript *behavior) {
    if (!behavior) { return 0; }
    struct Object *obj;
    f32 dist;

    obj = cur_obj_find_nearest_object_with_behavior(behavior, &dist);
    if (obj == NULL) {
        dist = 15000.0f;
    }

    return dist;
}

struct Object* cur_obj_find_nearest_pole(void) {
    struct Object* closestObj = NULL;
    struct Object* obj;
    struct ObjectNode* listHead;
    f32 minDist = 0x20000;

    listHead = &gObjectLists[OBJ_LIST_POLELIKE];
    obj = (struct Object*) listHead->next;

    while (obj != (struct Object*) listHead) {
        if (obj->oInteractType & INTERACT_POLE) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                f32 objDist = dist_between_objects(o, obj);
                if (objDist < minDist) {
                    closestObj = obj;
                    minDist = objDist;
                }
            }
        }
        obj = (struct Object*) obj->header.next;
    }

    return closestObj;
}

struct Object *cur_obj_find_nearest_object_with_behavior(const BehaviorScript *behavior, f32 *dist) {
    if (!behavior || !dist) { return NULL; }

    behavior = smlua_override_behavior(behavior);
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);
    struct Object *closestObj = NULL;
    struct Object *obj;
    struct ObjectNode *listHead;
    f32 minDist = 0x20000;
    u32 objList = get_object_list_from_behavior(behaviorAddr);
    if (objList >= NUM_OBJ_LISTS) { return NULL; }

    listHead = &gObjectLists[objList];
    obj = (struct Object *) listHead->next;

    while (obj && obj != (struct Object *) listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                f32 objDist = dist_between_objects(o, obj);
                if (objDist < minDist) {
                    closestObj = obj;
                    minDist = objDist;
                }
            }
        }
        obj = (struct Object *) obj->header.next;
    }

    *dist = minDist;
    return closestObj;
}

u16 cur_obj_count_objects_with_behavior(const BehaviorScript* behavior, f32 dist) {
    if (!behavior) { return 0; }
    behavior = smlua_override_behavior(behavior);
    u16 numObjs = 0;
    uintptr_t* behaviorAddr = segmented_to_virtual(behavior);
    struct Object* obj;
    struct ObjectNode* listHead;

    u32 objList = get_object_list_from_behavior(behaviorAddr);
    if (objList >= NUM_OBJ_LISTS) { return 0; }

    listHead = &gObjectLists[objList];
    obj = (struct Object*)listHead->next;

    while (obj && obj != (struct Object*)listHead) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj != o) {
                f32 objDist = dist_between_objects(o, obj);
                if (objDist < dist) {
                    numObjs++;
                }
            }
        }
        obj = (struct Object*)obj->header.next;
    }

    return numObjs;
}

struct Object *find_unimportant_object(void) {
    struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_UNIMPORTANT];
    struct ObjectNode *obj = listHead->next;

    if (listHead == obj) {
        obj = NULL;
    }

    return (struct Object *) obj;
}

s32 count_unimportant_objects(void) {
    struct ObjectNode *listHead = &gObjectLists[OBJ_LIST_UNIMPORTANT];
    struct ObjectNode *obj = listHead->next;
    s32 count = 0;

    while (obj && listHead != obj) {
        count++;
        obj = obj->next;
    }

    return count;
}

s32 count_objects_with_behavior(const BehaviorScript *behavior) {
    if (!behavior) { return 0; }
    behavior = smlua_override_behavior(behavior);
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);

    u32 objList = get_object_list_from_behavior(behaviorAddr);
    if (objList >= NUM_OBJ_LISTS) { return 0; }

    struct ObjectNode *listHead = &gObjectLists[objList];
    struct ObjectNode *obj = listHead->next;
    s32 count = 0;

    while (obj && listHead != obj) {
        if (((struct Object *) obj)->behavior == behaviorAddr) {
            count++;
        }

        obj = obj->next;
    }

    return count;
}

struct Object *find_object_with_behavior(const BehaviorScript *behavior) {
    behavior = smlua_override_behavior(behavior);
    uintptr_t *behaviorAddr = segmented_to_virtual(behavior);

    u32 objList = get_object_list_from_behavior(behaviorAddr);
    if (objList >= NUM_OBJ_LISTS) { return 0; }

    struct ObjectNode *listHead = &gObjectLists[objList];
    struct ObjectNode *obj = listHead->next;

    while (listHead != obj) {
        if (((struct Object *) obj)->behavior == behaviorAddr) {
            return (struct Object *)obj;
        }

        obj = obj->next;
    }

    return NULL;
}

struct Object *cur_obj_find_nearby_held_actor(const BehaviorScript *behavior, f32 maxDist) {
    behavior = smlua_override_behavior(behavior);
    const BehaviorScript *behaviorAddr = segmented_to_virtual(behavior);
    struct ObjectNode *listHead;
    struct Object *obj;
    struct Object *foundObj;

    listHead = &gObjectLists[OBJ_LIST_GENACTOR];
    obj = (struct Object *) listHead->next;
    foundObj = NULL;

    while ((struct Object *) listHead != obj) {
        if (obj->behavior == behaviorAddr) {
            if (obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                // This includes the dropped and thrown states. By combining instant
                // release, this allows us to activate mama penguin remotely
                if (obj->oHeldState != HELD_FREE) {
                    if (dist_between_objects(o, obj) < maxDist) {
                        foundObj = obj;
                        break;
                    }
                }
            }
        }

        obj = (struct Object *) obj->header.next;
    }

    return foundObj;
}

void cur_obj_reset_timer_and_subaction(void) {
    if (!o) { return; }
    o->oTimer = 0;
    o->oSubAction = 0;
}

void cur_obj_change_action(s32 action) {
    if (!o) { return; }
    o->oAction = action;
    o->oPrevAction = action;
    cur_obj_reset_timer_and_subaction();
}

void cur_obj_set_vel_from_mario_vel(struct MarioState* m, f32 f12, f32 f14) {
    if (!o) { return; }
    if (!m) { return; }
    f32 sp4 = m->forwardVel;
    f32 sp0 = f12 * f14;

    if (sp4 < sp0) {
        o->oForwardVel = sp0;
    } else {
        o->oForwardVel = sp4 * f14;
    }
}

BAD_RETURN(s16) cur_obj_reverse_animation(void) {
    if (!o) { return; }
    if (o->header.gfx.animInfo.animFrame >= 0) {
        o->header.gfx.animInfo.animFrame--;
    }
}

BAD_RETURN(s32) cur_obj_extend_animation_if_at_end(void) {
    if (!o) { return; }
    s32 sp4 = o->header.gfx.animInfo.animFrame;
    s32 sp0 = o->header.gfx.animInfo.curAnim ? o->header.gfx.animInfo.curAnim->loopEnd - 2 : 0;

    if (sp4 == sp0) o->header.gfx.animInfo.animFrame--;
}

s32 cur_obj_check_if_near_animation_end(void) {
    if (!o) { return 0; }
    u32 animFlags = o->header.gfx.animInfo.curAnim ? (s32) o->header.gfx.animInfo.curAnim->flags : 0;
    s32 animFrame = o->header.gfx.animInfo.animFrame;
    s32 nearLoopEnd = o->header.gfx.animInfo.curAnim ? o->header.gfx.animInfo.curAnim->loopEnd - 2 : 0;
    s32 isNearEnd = FALSE;

    if (animFlags & ANIM_FLAG_NOLOOP && nearLoopEnd + 1 == animFrame) {
        isNearEnd = TRUE;
    }

    if (animFrame == nearLoopEnd) {
        isNearEnd = TRUE;
    }

    return isNearEnd;
}

s32 cur_obj_check_if_at_animation_end(void) {
    if (!o) { return 0; }
    s32 animFrame = o->header.gfx.animInfo.animFrame;
    s32 lastFrame = o->header.gfx.animInfo.curAnim ? o->header.gfx.animInfo.curAnim->loopEnd - 1 : 0;

    if (animFrame == lastFrame) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 cur_obj_check_anim_frame(s32 frame) {
    if (!o) { return 0; }
    s32 animFrame = o->header.gfx.animInfo.animFrame;

    if (animFrame == frame) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 cur_obj_check_anim_frame_in_range(s32 startFrame, s32 rangeLength) {
    if (!o) { return 0; }
    s32 animFrame = o->header.gfx.animInfo.animFrame;

    if (animFrame >= startFrame && animFrame < startFrame + rangeLength) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 cur_obj_check_frame_prior_current_frame(s16 *a0) {
    if (!o) { return 0; }
    s16 sp6 = o->header.gfx.animInfo.animFrame;

    while (*a0 != -1) {
        if (*a0 == sp6) {
            return TRUE;
        }

        a0++;
    }

    return FALSE;
}

s32 mario_is_in_air_action(struct MarioState* m) {
    if (!m) { return 0; }
    if (m->action & ACT_FLAG_AIR) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 mario_is_dive_sliding(struct MarioState* m) {
    if (!m) { return 0; }
    if (m->action == ACT_DIVE_SLIDE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void cur_obj_set_y_vel_and_animation(f32 sp18, s32 sp1C) {
    if (!o) { return; }
    o->oVelY = sp18;
    cur_obj_init_animation_with_sound(sp1C);
}

void cur_obj_unrender_and_reset_state(s32 sp18, s32 sp1C) {
    if (!o) { return; }
    cur_obj_become_intangible();
    cur_obj_disable_rendering();

    if (sp18 >= 0) {
        cur_obj_init_animation_with_sound(sp18);
    }

    o->oAction = sp1C;
}

void cur_obj_move_after_thrown_or_dropped(f32 forwardVel, f32 velY) {
    if (!o) { return; }
    o->oMoveFlags = 0;
    o->oFloorHeight = find_floor_height(o->oPosX, o->oPosY + 160.0f, o->oPosZ);

    if (o->oFloorHeight > o->oPosY) {
        o->oPosY = o->oFloorHeight;
    } else if (o->oFloorHeight < gLevelValues.floorLowerLimitMisc) {
        //! OoB failsafe
        if (gMarioObject) {
            obj_copy_pos(o, gMarioObject);
        }
        o->oFloorHeight = find_floor_height(o->oPosX, o->oPosY, o->oPosZ);
    }

    o->oForwardVel = forwardVel;
    o->oVelY = velY;

    if (o->oForwardVel != 0) {
        cur_obj_move_y(/*gravity*/ -4.0f, /*bounciness*/ -0.1f, /*buoyancy*/ 2.0f);
    }
}

void cur_obj_get_thrown_or_placed(f32 forwardVel, f32 velY, s32 thrownAction) {
    if (!o) { return; }
    if (o->behavior == segmented_to_virtual(smlua_override_behavior(bhvBowser))) {
        // Interestingly, when bowser is thrown, he is offset slightly to
        // Mario's right
        cur_obj_set_pos_relative_to_parent(-41.684f, 85.859f, 321.577f);
    } else {
    }

    cur_obj_become_tangible();
    cur_obj_enable_rendering();

    o->oHeldState = HELD_FREE;

    if ((o->oInteractionSubtype & INT_SUBTYPE_HOLDABLE_NPC) || forwardVel == 0.0f) {
        cur_obj_move_after_thrown_or_dropped(0.0f, 0.0f);
    } else {
        o->oAction = thrownAction;
        cur_obj_move_after_thrown_or_dropped(forwardVel, velY);
    }

    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (so && so->owned) {
        network_send_object(o);
    }
}

void cur_obj_get_dropped(void) {
    if (!o) { return; }
    cur_obj_become_tangible();
    cur_obj_enable_rendering();

    o->oHeldState = HELD_FREE;
    cur_obj_move_after_thrown_or_dropped(0.0f, 0.0f);

    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (so && so->owned) {
        network_send_object(o);
    }
}

void cur_obj_set_model(s32 modelID) {
    obj_set_model(o, modelID);
}

void obj_set_model(struct Object* obj, s32 modelID) {
    obj->header.gfx.sharedChild = dynos_model_get_geo(modelID);
    dynos_actor_override(obj, (void*)&obj->header.gfx.sharedChild);
    smlua_call_event_hooks_object_model_param(HOOK_OBJECT_SET_MODEL, obj, modelID);
}

void mario_set_flag(s32 flag) {
    gMarioStates[0].flags |= flag;
}

s32 cur_obj_clear_interact_status_flag(s32 flag) {
    if (!o) { return 0; }
    if (o->oInteractStatus & flag) {
        o->oInteractStatus &= flag ^ ~(0);
        return TRUE;
    }
    return FALSE;
}

/**
 * Mark an object to be unloaded at the end of the frame.
 */
void obj_mark_for_deletion(struct Object *obj) {
    //! This clears all activeFlags. Since some of these flags disable behavior,
    //  setting it to 0 could potentially enable unexpected behavior. After an
    //  object is marked for deletion, it still updates on that frame (I think),
    //  so this is worth looking into.
    if (obj != NULL) {
        obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
    }
}

void cur_obj_disable(void) {
    cur_obj_disable_rendering();
    cur_obj_hide();
    cur_obj_become_intangible();
}

void cur_obj_become_intangible(void) {
    if (!o) { return; }
    // When the timer is negative, the object is intangible and the timer
    // doesn't count down
    o->oIntangibleTimer = -1;
}

void cur_obj_become_tangible(void) {
    if (!o) { return; }
    o->oIntangibleTimer = 0;
}

void obj_become_tangible(struct Object *obj) {
    if (!obj) { return; }
    obj->oIntangibleTimer = 0;
}

void cur_obj_update_floor_height(void) {
    if (!o) { return; }
    struct Surface *floor;
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
}

struct Surface *cur_obj_update_floor_height_and_get_floor(void) {
    if (!o) { return NULL; }
    struct Surface *floor;
    o->oFloorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);
    return floor;
}

void apply_drag_to_value(f32 *value, f32 dragStrength) {
    f32 decel;

    if (*value != 0) {
        //! Can overshoot if |*value| > 1/(dragStrength * 0.0001)
        decel = (*value) * (*value) * (dragStrength * 0.0001L);

        if (*value > 0) {
            *value -= decel;
            if (*value < 0.001L) {
                *value = 0;
            }
        } else {
            *value += decel;
            if (*value > -0.001L) {
                *value = 0;
            }
        }
    }
}

void cur_obj_apply_drag_xz(f32 dragStrength) {
    if (!o) { return; }
    apply_drag_to_value(&o->oVelX, dragStrength);
    apply_drag_to_value(&o->oVelZ, dragStrength);
}

s32 cur_obj_move_xz(f32 steepSlopeNormalY, s32 careAboutEdgesAndSteepSlopes) {
    if (!o) { return 0; }
    struct Surface *intendedFloor = NULL;

    f32 intendedX = o->oPosX + o->oVelX;
    f32 intendedZ = o->oPosZ + o->oVelZ;

    f32 intendedFloorHeight = find_floor(intendedX, o->oPosY, intendedZ, &intendedFloor);
    f32 deltaFloorHeight = intendedFloorHeight - o->oFloorHeight;

    UNUSED f32 unused;
    UNUSED f32 ny;

    o->oMoveFlags &= ~OBJ_MOVE_HIT_EDGE;

    if (o->oRoom != -1 && intendedFloor != NULL) {
        if (intendedFloor->room != 0 && o->oRoom != intendedFloor->room && intendedFloor->room != 18) {
            // Don't leave native room
            return FALSE;
        }
    }

    if (intendedFloorHeight < gLevelValues.floorLowerLimitMisc) {
        // Don't move into OoB
        o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
        return FALSE;
    } else if (deltaFloorHeight < 5.0f) {
        if (!careAboutEdgesAndSteepSlopes) {
            // If we don't care about edges or steep slopes, okay to move
            o->oPosX = intendedX;
            o->oPosZ = intendedZ;
            return TRUE;
        } else if (deltaFloorHeight < -50.0f && (o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
            // Don't walk off an edge
            o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
            return FALSE;
        } else if (intendedFloor != NULL && intendedFloor->normal.y > steepSlopeNormalY) {
            // Allow movement onto a slope, provided it's not too steep
            o->oPosX = intendedX;
            o->oPosZ = intendedZ;
            return TRUE;
        } else {
            // We are likely trying to move onto a steep downward slope
            o->oMoveFlags |= OBJ_MOVE_HIT_EDGE;
            return FALSE;
        }
    } else if (intendedFloor != NULL && ((ny = intendedFloor->normal.y) > steepSlopeNormalY || o->oPosY > intendedFloorHeight)) {
        // Allow movement upward, provided either:
        // - The target floor is flat enough (e.g. walking up stairs)
        // - We are above the target floor (most likely in the air)
        o->oPosX = intendedX;
        o->oPosZ = intendedZ;
        //! Returning FALSE but moving anyway (not exploitable; return value is
        //  never used)
    }

    // We are likely trying to move onto a steep upward slope
    return FALSE;
}

void cur_obj_move_update_underwater_flags(void) {
    if (!o) { return; }
    f32 decelY = (f32)(sqrtf(o->oVelY * o->oVelY) * (o->oDragStrength * 7.0f)) / 100.0L;

    if (o->oVelY > 0) {
        o->oVelY -= decelY;
    } else {
        o->oVelY += decelY;
    }

    if (o->oPosY < o->oFloorHeight) {
        o->oPosY = o->oFloorHeight;
        o->oMoveFlags |= OBJ_MOVE_UNDERWATER_ON_GROUND;
    } else {
        o->oMoveFlags |= OBJ_MOVE_UNDERWATER_OFF_GROUND;
    }
}

void cur_obj_move_update_ground_air_flags(UNUSED f32 gravity, f32 bounciness) {
    if (!o) { return; }
    o->oMoveFlags &= ~OBJ_MOVE_BOUNCE;

    if (o->oPosY < o->oFloorHeight) {
        // On the first frame that we touch the ground, set OBJ_MOVE_LANDED.
        // On subsequent frames, set OBJ_MOVE_ON_GROUND
        if (!(o->oMoveFlags & OBJ_MOVE_ON_GROUND)) {
            if (clear_move_flag(&o->oMoveFlags, OBJ_MOVE_LANDED)) {
                o->oMoveFlags |= OBJ_MOVE_ON_GROUND;
            } else {
                o->oMoveFlags |= OBJ_MOVE_LANDED;
            }
        }

        o->oPosY = o->oFloorHeight;

        if (o->oVelY < 0.0f) {
            o->oVelY *= bounciness;
        }

        if (o->oVelY > 5.0f) {
            //! This overestimates since velY could be > 5 here
            //! without bounce (e.g. jump into misa).
            o->oMoveFlags |= OBJ_MOVE_BOUNCE;
        }
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_LANDED;
        if (clear_move_flag(&o->oMoveFlags, OBJ_MOVE_ON_GROUND)) {
            o->oMoveFlags |= OBJ_MOVE_LEFT_GROUND;
        }
    }

    o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
}

f32 cur_obj_move_y_and_get_water_level(f32 gravity, f32 buoyancy) {
    if (!o) { return 0; }
    f32 waterLevel;

    o->oVelY += gravity + buoyancy;
    if (o->oVelY < -78.0f) {
        o->oVelY = -78.0f;
    }

    o->oPosY += o->oVelY;
    if (o->activeFlags & ACTIVE_FLAG_UNK10) {
        waterLevel = gLevelValues.floorLowerLimit;
    } else {
        waterLevel = find_water_level(o->oPosX, o->oPosZ);
    }

    return waterLevel;
}

void cur_obj_move_y(f32 gravity, f32 bounciness, f32 buoyancy) {
    if (!o) { return; }
    f32 waterLevel;

    o->oMoveFlags &= ~OBJ_MOVE_LEFT_GROUND;

    if (o->oMoveFlags & OBJ_MOVE_AT_WATER_SURFACE) {
        if (o->oVelY > 5.0f) {
            o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
            o->oMoveFlags |= OBJ_MOVE_LEAVING_WATER;
        }
    }

    if (!(o->oMoveFlags & OBJ_MOVE_MASK_IN_WATER)) {
        waterLevel = cur_obj_move_y_and_get_water_level(gravity, 0.0f);
        if (o->oPosY > waterLevel) {
            //! We only handle floor collision if the object does not enter
            //  water. This allows e.g. coins to clip through floors if they
            //  enter water on the same frame.
            cur_obj_move_update_ground_air_flags(gravity, bounciness);
        } else {
            o->oMoveFlags |= OBJ_MOVE_ENTERED_WATER;
            o->oMoveFlags &= ~OBJ_MOVE_MASK_ON_GROUND;
        }
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_ENTERED_WATER;

        waterLevel = cur_obj_move_y_and_get_water_level(gravity, buoyancy);
        if (o->oPosY < waterLevel) {
            cur_obj_move_update_underwater_flags();
        } else {
            if (o->oPosY < o->oFloorHeight) {
                o->oPosY = o->oFloorHeight;
                o->oMoveFlags &= ~OBJ_MOVE_MASK_IN_WATER;
            } else {
                o->oPosY = waterLevel;
                o->oVelY = 0.0f;
                o->oMoveFlags &= ~(OBJ_MOVE_UNDERWATER_OFF_GROUND | OBJ_MOVE_UNDERWATER_ON_GROUND);
                o->oMoveFlags |= OBJ_MOVE_AT_WATER_SURFACE;
            }
        }
    }

    if (o->oMoveFlags & (OBJ_MOVE_MASK_ON_GROUND | OBJ_MOVE_AT_WATER_SURFACE
        | OBJ_MOVE_UNDERWATER_OFF_GROUND)) {
        o->oMoveFlags &= ~OBJ_MOVE_IN_AIR;
    } else {
        o->oMoveFlags |= OBJ_MOVE_IN_AIR;
    }
}

static void stub_obj_helpers_1(void) {
}

void cur_obj_unused_resolve_wall_collisions(f32 offsetY, f32 radius) {
    if (!o) { return; }
    if (radius > 0.1L) {
        f32_find_wall_collision(&o->oPosX, &o->oPosY, &o->oPosZ, offsetY, radius);
    }
}

s16 abs_angle_diff(s16 x0, s16 x1) {
    s16 diff = x1 - x0;

    if (diff == -0x8000) {
        diff = -0x7FFF;
    }

    if (diff < 0) {
        diff = -diff;
    }

    return diff;
}

void cur_obj_move_xz_using_fvel_and_yaw(void) {
    if (!o) { return; }
    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);

    o->oPosX += o->oVelX;
    o->oPosZ += o->oVelZ;
}

void cur_obj_move_y_with_terminal_vel(void) {
    if (!o) { return; }
    if (o->oVelY < -70.0f) {
        o->oVelY = -70.0f;
    }

    o->oPosY += o->oVelY;
}

void cur_obj_compute_vel_xz(void) {
    if (!o) { return; }
    o->oVelX = o->oForwardVel * sins(o->oMoveAngleYaw);
    o->oVelZ = o->oForwardVel * coss(o->oMoveAngleYaw);
}

f32 increment_velocity_toward_range(f32 value, f32 center, f32 zeroThreshold, f32 increment) {
    f32 relative;
    if ((relative = value - center) > 0) {
        if (relative < zeroThreshold) {
            return 0.0f;
        } else {
            return -increment;
        }
    } else {
        if (relative > -zeroThreshold) {
            return 0.0f;
        } else {
            return increment;
        }
    }
}

s32 obj_check_if_collided_with_object(struct Object *obj1, struct Object *obj2) {
    if (obj1 == NULL) { return FALSE; }
    s32 i;
    for (i = 0; i < obj1->numCollidedObjs; i++) {
        if (obj1->collidedObjs[i] == obj2) {
            return TRUE;
        }
    }

    return FALSE;
}

void cur_obj_set_behavior(const BehaviorScript *behavior) {
    if (!o) { return; }
    o->behavior = segmented_to_virtual(behavior);
}

void obj_set_behavior(struct Object *obj, const BehaviorScript *behavior) {
    if (!obj) { return; }
    obj->behavior = segmented_to_virtual(behavior);
}

s32 cur_obj_has_behavior(const BehaviorScript *behavior) {
    if (!o) { return 0; }
    behavior = smlua_override_behavior(behavior);
    if (o->behavior == segmented_to_virtual(behavior)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 obj_has_behavior(struct Object *obj, const BehaviorScript *behavior) {
    if (!obj || !behavior) { return FALSE; }
    behavior = smlua_override_behavior(behavior);
    if (obj->behavior == segmented_to_virtual(behavior)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

f32 cur_obj_lateral_dist_from_obj_to_home(struct Object *obj) {
    if (!o) { return 0; }
    f32 dist;
    f32 dx = o->oHomeX - obj->oPosX;
    f32 dz = o->oHomeZ - obj->oPosZ;

    dist = sqrtf(dx * dx + dz * dz);
    return dist;
}

f32 cur_obj_lateral_dist_from_mario_to_home(void) {
    if (!o) { return 0; }
    struct Object* player = nearest_player_to_object(o);
    if (!player) { return 10000; }
    f32 dist;
    f32 dx = o->oHomeX - player->oPosX;
    f32 dz = o->oHomeZ - player->oPosZ;

    dist = sqrtf(dx * dx + dz * dz);
    return dist;
}

f32 cur_obj_lateral_dist_to_home(void) {
    if (!o) { return 0; }
    f32 dist;
    f32 dx = o->oHomeX - o->oPosX;
    f32 dz = o->oHomeZ - o->oPosZ;

    dist = sqrtf(dx * dx + dz * dz);
    return dist;
}

s32 cur_obj_outside_home_square(f32 halfLength) {
    if (!o) { return 0; }
    if (o->oHomeX - halfLength > o->oPosX) {
        return TRUE;
    }

    if (o->oHomeX + halfLength < o->oPosX) {
        return TRUE;
    }

    if (o->oHomeZ - halfLength > o->oPosZ) {
        return TRUE;
    }

    if (o->oHomeZ + halfLength < o->oPosZ) {
        return TRUE;
    }

    return FALSE;
}

s32 cur_obj_outside_home_rectangle(f32 minX, f32 maxX, f32 minZ, f32 maxZ) {
    if (!o) { return 0; }
    if (o->oHomeX + minX > o->oPosX) {
        return TRUE;
    }

    if (o->oHomeX + maxX < o->oPosX) {
        return TRUE;
    }

    if (o->oHomeZ + minZ > o->oPosZ) {
        return TRUE;
    }

    if (o->oHomeZ + maxZ < o->oPosZ) {
        return TRUE;
    }

    return FALSE;
}

void cur_obj_set_pos_to_home(void) {
    if (!o) { return; }
    o->oPosX = o->oHomeX;
    o->oPosY = o->oHomeY;
    o->oPosZ = o->oHomeZ;
    o->header.gfx.skipInterpolationTimestamp = gGlobalTimer;
}

void cur_obj_set_pos_to_home_and_stop(void) {
    if (!o) { return; }
    cur_obj_set_pos_to_home();

    o->oForwardVel = 0;
    o->oVelY = 0;
}

void cur_obj_shake_y(f32 amount) {
    if (!o) { return; }
    //! Technically could cause a bit of drift, but not much
    if (o->oTimer % 2 == 0) {
        o->oPosY += amount;
    } else {
        o->oPosY -= amount;
    }
}

void cur_obj_start_cam_event(UNUSED struct Object *obj, s32 cameraEvent) {
    gPlayerCameraState->cameraEvent = (s16) cameraEvent;
    gSecondCameraFocus = o;
}

void set_mario_interact_hoot_if_in_range(UNUSED s32 sp0, UNUSED s32 sp4, f32 sp8) {
    if (!o || !gMarioObject) { return; }
    if (o->oDistanceToMario < sp8) {
        gMarioObject->oInteractStatus = INT_STATUS_HOOT_GRABBED_BY_MARIO;
    }
}

void obj_set_billboard(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
}

void obj_set_cylboard(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->header.gfx.node.flags |= GRAPH_RENDER_CYLBOARD;
}

void cur_obj_set_billboard_if_vanilla_cam(void) {
    if (!o) { return; }
    if (camera_config_is_free_cam_enabled() || get_first_person_enabled()) {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_BILLBOARD;
        o->header.gfx.node.flags |= GRAPH_RENDER_CYLBOARD;
    } else {
        o->header.gfx.node.flags &= ~GRAPH_RENDER_CYLBOARD;
        o->header.gfx.node.flags |= GRAPH_RENDER_BILLBOARD;
    }
}

void obj_set_hitbox_radius_and_height(struct Object *o, f32 radius, f32 height) {
    if (o == NULL) { return; }
    
    o->hitboxRadius = radius;
    o->hitboxHeight = height;
}

void obj_set_hurtbox_radius_and_height(struct Object *o, f32 radius, f32 height) {
    if (o == NULL) { return; }
    
    o->hurtboxRadius = radius;
    o->hurtboxHeight = height;
}

void cur_obj_set_hitbox_radius_and_height(f32 radius, f32 height) {
    if (!o) { return; }
    o->hitboxRadius = radius;
    o->hitboxHeight = height;
}

void cur_obj_set_hurtbox_radius_and_height(f32 radius, f32 height) {
    if (!o) { return; }
    o->hurtboxRadius = radius;
    o->hurtboxHeight = height;
}

void obj_spawn_loot_coins(struct Object *obj, s32 numCoins, f32 sp30,
                                    const BehaviorScript *coinBehavior,
                                    s16 posJitter, s16 model) {
    if (obj == NULL) { return; }
    s32 i;
    f32 spawnHeight;
    struct Surface *floor;
    struct Object *coin;

    spawnHeight = find_floor(obj->oPosX, obj->oPosY, obj->oPosZ, &floor);
    if (obj->oPosY - spawnHeight > 100.0f) {
        spawnHeight = obj->oPosY;
    }

    for (i = 0; i < numCoins; i++) {
        if (obj->oNumLootCoins <= 0) {
            break;
        }

        obj->oNumLootCoins--;

        coin = spawn_object(obj, model, coinBehavior);
        if (coin == NULL) { return; }
        obj_translate_xz_random(coin, posJitter);
        coin->oPosY = spawnHeight;
        coin->oCoinUnk110 = sp30;
    }
}

void obj_spawn_loot_blue_coins(struct Object *obj, s32 numCoins, f32 sp28, s16 posJitter) {
    obj_spawn_loot_coins(obj, numCoins, sp28, bhvBlueCoinJumping, posJitter, MODEL_BLUE_COIN);
}

void obj_spawn_loot_yellow_coins(struct Object *obj, s32 numCoins, f32 sp28) {
    obj_spawn_loot_coins(obj, numCoins, sp28, bhvSingleCoinGetsSpawned, 0, MODEL_YELLOW_COIN);
}

void cur_obj_spawn_loot_coin_at_mario_pos(struct MarioState* m) {
    struct Object *coin;
    if (!m) { return; }
    if (o && o->oNumLootCoins <= 0) {
        return;
    }

    if (o) {
        o->oNumLootCoins--;
    }

    coin = spawn_object(o, MODEL_YELLOW_COIN, bhvSingleCoinGetsSpawned);
    if (coin == NULL) { return; }
    coin->oVelY = 30.0f;

    obj_copy_pos(coin, m->marioObj);
}

f32 cur_obj_abs_y_dist_to_home(void) {
    if (!o) { return 0; }
    f32 dist = o->oHomeY - o->oPosY;

    if (dist < 0) {
        dist = -dist;
    }

    return dist;
}

s32 cur_obj_advance_looping_anim(void) {
    if (!o) { return 0; }
    s32 animFrame = o->header.gfx.animInfo.animFrame;
    s32 loopEnd = o->header.gfx.animInfo.curAnim ? o->header.gfx.animInfo.curAnim->loopEnd : 1;
    s32 result;

    if (animFrame < 0) {
        animFrame = 0;
    } else if (loopEnd - 1 == animFrame) {
        animFrame = 0;
    } else {
        animFrame++;
    }
    if (loopEnd == 0) { loopEnd = 1; }
    result = (animFrame << 16) / loopEnd;

    return result;
}

s32 cur_obj_detect_steep_floor(s16 steepAngleDegrees) {
    if (!o) { return 0; }
    struct Surface *intendedFloor;
    f32 intendedX, intendedFloorHeight, intendedZ;
    f32 deltaFloorHeight;
    f32 steepNormalY = coss((s16)(steepAngleDegrees * (0x10000 / 360)));

    if (o->oForwardVel != 0.0f) {
        intendedX = o->oPosX + o->oVelX;
        intendedZ = o->oPosZ + o->oVelZ;
        intendedFloorHeight = find_floor(intendedX, o->oPosY, intendedZ, &intendedFloor);
        deltaFloorHeight = intendedFloorHeight - o->oFloorHeight;

        if (intendedFloorHeight < gLevelValues.floorLowerLimitMisc) {
            o->oWallAngle = o->oMoveAngleYaw + 0x8000;
            return 2;
        } else if (intendedFloor && intendedFloor->normal.y < steepNormalY && deltaFloorHeight > 0
                   && intendedFloorHeight > o->oPosY) {
            o->oWallAngle = atan2s(intendedFloor->normal.z, intendedFloor->normal.x);
            return 1;
        } else {
            return 0;
        }
    }

    return 0;
}

s32 cur_obj_resolve_wall_collisions(void) {
    if (!o) { return 0; }
    s32 numCollisions;
    struct Surface *wall;
    struct WallCollisionData collisionData;

    f32 offsetY = 10.0f;
    f32 radius = o->oWallHitboxRadius;

    if (radius > 0.1L) {
        collisionData.offsetY = offsetY;
        collisionData.radius = radius;
        collisionData.x = (s16) o->oPosX;
        collisionData.y = (s16) o->oPosY;
        collisionData.z = (s16) o->oPosZ;

        numCollisions = find_wall_collisions(&collisionData);
        if (numCollisions != 0) {
            o->oPosX = collisionData.x;
            o->oPosY = collisionData.y;
            o->oPosZ = collisionData.z;
            wall = collisionData.walls[collisionData.numWalls - 1];

            o->oWallAngle = atan2s(wall->normal.z, wall->normal.x);
            if (abs_angle_diff(o->oWallAngle, o->oMoveAngleYaw) > 0x4000) {
                return TRUE;
            } else {
                return FALSE;
            }
        }
    }

    return FALSE;
}

void cur_obj_update_floor(void) {
    if (!o) { return; }
    struct Surface *floor = cur_obj_update_floor_height_and_get_floor();
    o->oFloor = floor;

    if (floor != NULL) {
        if (floor->type == SURFACE_BURNING) {
            o->oMoveFlags |= OBJ_MOVE_ABOVE_LAVA;
        }
#ifndef VERSION_JP
        else if (floor->type == SURFACE_DEATH_PLANE) {
            //! This misses SURFACE_VERTICAL_WIND (and maybe SURFACE_WARP)
            o->oMoveFlags |= OBJ_MOVE_ABOVE_DEATH_BARRIER;
        }
#endif

        o->oFloorType = floor->type;
        o->oFloorRoom = floor->room;
    } else {
        o->oFloorType = 0;
        o->oFloorRoom = 0;
    }
}

void cur_obj_update_floor_and_resolve_wall_collisions(s16 steepSlopeDegrees) {
    if (!o) { return; }
#ifdef VERSION_JP
    o->oMoveFlags &= ~OBJ_MOVE_ABOVE_LAVA;
#else
    o->oMoveFlags &= ~(OBJ_MOVE_ABOVE_LAVA | OBJ_MOVE_ABOVE_DEATH_BARRIER);
#endif

    if (o->activeFlags & (ACTIVE_FLAG_FAR_AWAY | ACTIVE_FLAG_IN_DIFFERENT_ROOM)) {
        cur_obj_update_floor();
        o->oMoveFlags &= ~(OBJ_MOVE_HIT_WALL | OBJ_MOVE_MASK_IN_WATER);

        if (o->oPosY > o->oFloorHeight) {
            o->oMoveFlags |= OBJ_MOVE_IN_AIR;
        }
    } else {
        o->oMoveFlags &= ~OBJ_MOVE_HIT_WALL;
        if (cur_obj_resolve_wall_collisions()) {
            o->oMoveFlags |= OBJ_MOVE_HIT_WALL;
        }

        cur_obj_update_floor();

        if (o->oPosY > o->oFloorHeight) {
            o->oMoveFlags |= OBJ_MOVE_IN_AIR;
        }

        if (cur_obj_detect_steep_floor(steepSlopeDegrees)) {
            o->oMoveFlags |= OBJ_MOVE_HIT_WALL;
        }
    }
}

void cur_obj_update_floor_and_walls(void) {
    cur_obj_update_floor_and_resolve_wall_collisions(60);
}

void cur_obj_move_standard(s16 steepSlopeAngleDegrees) {
    if (!o) { return; }
    f32 gravity = o->oGravity;
    f32 bounciness = o->oBounciness;
    f32 buoyancy = o->oBuoyancy;
    f32 dragStrength = o->oDragStrength;
    f32 steepSlopeNormalY;
    s32 careAboutEdgesAndSteepSlopes = FALSE;
    s32 negativeSpeed = FALSE;

    //! Because some objects allow these active flags to be set but don't
    //  avoid updating when they are, we end up with "partial" updates, where
    //  an object's internal state will be updated, but it doesn't move.
    //  This allows numerous glitches and is typically referred to as
    //  deactivation (though this term has a different meaning in the code).
    //  Objects that do this will be marked with //PARTIAL_UPDATE.
    if (!(o->activeFlags & (ACTIVE_FLAG_FAR_AWAY | ACTIVE_FLAG_IN_DIFFERENT_ROOM))) {
        if (steepSlopeAngleDegrees < 0) {
            // clang-format off
            careAboutEdgesAndSteepSlopes = TRUE; steepSlopeAngleDegrees = -steepSlopeAngleDegrees;
            // clang-format on
        }

        steepSlopeNormalY = coss(steepSlopeAngleDegrees * (0x10000 / 360));

        cur_obj_compute_vel_xz();
        cur_obj_apply_drag_xz(dragStrength);

        cur_obj_move_xz(steepSlopeNormalY, careAboutEdgesAndSteepSlopes);
        cur_obj_move_y(gravity, bounciness, buoyancy);

        if (o->oForwardVel < 0.0f) {
            negativeSpeed = TRUE;
        }
        o->oForwardVel = sqrtf(sqr(o->oVelX) + sqr(o->oVelZ));
        if (negativeSpeed == TRUE) {
            o->oForwardVel = -o->oForwardVel;
        }
    }
}

s32 cur_obj_within_12k_bounds(void) {
    if (!o) { return 0; }
    if (o->oPosX < -12000.0f || 12000.0f < o->oPosX) {
        return FALSE;
    }

    if (o->oPosY < -12000.0f || 12000.0f < o->oPosY) {
        return FALSE;
    }

    if (o->oPosZ < -12000.0f || 12000.0f < o->oPosZ) {
        return FALSE;
    }

    return TRUE;
}

void cur_obj_move_using_vel_and_gravity(void) {
    if (!o) { return; }
    //if (cur_obj_within_12k_bounds()) {
        o->oPosX += o->oVelX;
        o->oPosZ += o->oVelZ;
        o->oVelY += o->oGravity; //! No terminal velocity
        o->oPosY += o->oVelY;
    //}
}

void cur_obj_move_using_fvel_and_gravity(void) {
    cur_obj_compute_vel_xz();
    cur_obj_move_using_vel_and_gravity(); //! No terminal velocity
}

void obj_set_pos_relative(struct Object *obj, struct Object *other, f32 dleft, f32 dy,
                             f32 dforward) {
    if (!obj || !other) { return; }
    f32 facingZ = coss(other->oMoveAngleYaw);
    f32 facingX = sins(other->oMoveAngleYaw);

    f32 dz = dforward * facingZ - dleft * facingX;
    f32 dx = dforward * facingX + dleft * facingZ;

    obj->oMoveAngleYaw = other->oMoveAngleYaw;

    obj->oPosX = other->oPosX + dx;
    obj->oPosY = other->oPosY + dy;
    obj->oPosZ = other->oPosZ + dz;
}

s16 cur_obj_angle_to_home(void) {
    if (!o) { return 0; }
    s16 angle;
    f32 dx = o->oHomeX - o->oPosX;
    f32 dz = o->oHomeZ - o->oPosZ;

    angle = atan2s(dz, dx);
    return angle;
}

void obj_set_gfx_pos_at_obj_pos(struct Object *obj1, struct Object *obj2) {
    if (!obj1 || !obj2) { return; }
    obj1->header.gfx.pos[0] = obj2->oPosX;
    obj1->header.gfx.pos[1] = obj2->oPosY + obj2->oGraphYOffset;
    obj1->header.gfx.pos[2] = obj2->oPosZ;

    obj1->header.gfx.angle[0] = obj2->oMoveAnglePitch & 0xFFFF;
    obj1->header.gfx.angle[1] = obj2->oMoveAngleYaw & 0xFFFF;
    obj1->header.gfx.angle[2] = obj2->oMoveAngleRoll & 0xFFFF;
}

/**
 * Transform the vector at localTranslateIndex into the object's local
 * coordinates, and then add it to the vector at posIndex.
 */
void obj_translate_local(struct Object *obj, s16 posIndex, s16 localTranslateIndex) {
    if (obj == NULL) { return; }
    f32 dx = obj->rawData.asF32[localTranslateIndex + 0];
    f32 dy = obj->rawData.asF32[localTranslateIndex + 1];
    f32 dz = obj->rawData.asF32[localTranslateIndex + 2];

    obj->rawData.asF32[posIndex + 0] +=
        obj->transform[0][0] * dx + obj->transform[1][0] * dy + obj->transform[2][0] * dz;
    obj->rawData.asF32[posIndex + 1] +=
        obj->transform[0][1] * dx + obj->transform[1][1] * dy + obj->transform[2][1] * dz;
    obj->rawData.asF32[posIndex + 2] +=
        obj->transform[0][2] * dx + obj->transform[1][2] * dy + obj->transform[2][2] * dz;
}

void obj_build_transform_from_pos_and_angle(struct Object *obj, s16 posIndex, s16 angleIndex) {
    if (obj == NULL) { return; }
    f32 translate[3];
    s16 rotation[3];

    translate[0] = obj->rawData.asF32[posIndex + 0];
    translate[1] = obj->rawData.asF32[posIndex + 1];
    translate[2] = obj->rawData.asF32[posIndex + 2];

    rotation[0] = obj->rawData.asS32[angleIndex + 0];
    rotation[1] = obj->rawData.asS32[angleIndex + 1];
    rotation[2] = obj->rawData.asS32[angleIndex + 2];

    mtxf_rotate_zxy_and_translate(obj->transform, translate, rotation);
}

void obj_set_throw_matrix_from_transform(struct Object *obj) {
    if (obj == NULL) { return; }
    if (obj->oFlags & OBJ_FLAG_0020) {
        obj_build_transform_from_pos_and_angle(obj, O_POS_INDEX, O_FACE_ANGLE_INDEX);
        obj_apply_scale_to_transform(obj);
    }

    obj->header.gfx.throwMatrix = &obj->transform;

    //! Sets scale of gCurrentObject instead of obj. Not exploitable since this
    //  function is only called with obj = gCurrentObject
    cur_obj_scale(1.0f);
}

void obj_build_transform_relative_to_parent(struct Object *obj) {
    if (obj == NULL) { return; }
    struct Object *parent = obj->parentObj;
    if (!parent) { return; }

    obj_build_transform_from_pos_and_angle(obj, O_PARENT_RELATIVE_POS_INDEX, O_FACE_ANGLE_INDEX);
    obj_apply_scale_to_transform(obj);
    mtxf_mul(obj->transform, obj->transform, parent->transform);

    obj->oPosX = obj->transform[3][0];
    obj->oPosY = obj->transform[3][1];
    obj->oPosZ = obj->transform[3][2];

    obj->header.gfx.throwMatrix = &obj->transform;

    //! Sets scale of gCurrentObject instead of obj. Not exploitable since this
    //  function is only called with obj = gCurrentObject
    cur_obj_scale(1.0f);
}

void obj_create_transform_from_self(struct Object *obj) {
    if (obj == NULL) { return; }
    obj->oFlags &= ~OBJ_FLAG_TRANSFORM_RELATIVE_TO_PARENT;
    obj->oFlags |= OBJ_FLAG_SET_THROW_MATRIX_FROM_TRANSFORM;

    obj->transform[3][0] = obj->oPosX;
    obj->transform[3][1] = obj->oPosY;
    obj->transform[3][2] = obj->oPosZ;
}

void cur_obj_rotate_move_angle_using_vel(void) {
    if (!o) { return; }
    o->oMoveAnglePitch += o->oAngleVelPitch;
    o->oMoveAngleYaw += o->oAngleVelYaw;
    o->oMoveAngleRoll += o->oAngleVelRoll;
}

void cur_obj_rotate_face_angle_using_vel(void) {
    if (!o) { return; }
    o->oFaceAnglePitch += o->oAngleVelPitch;
    o->oFaceAngleYaw += o->oAngleVelYaw;
    o->oFaceAngleRoll += o->oAngleVelRoll;
}

void cur_obj_set_face_angle_to_move_angle(void) {
    if (!o) { return; }
    o->oFaceAnglePitch = o->oMoveAnglePitch;
    o->oFaceAngleYaw = o->oMoveAngleYaw;
    o->oFaceAngleRoll = o->oMoveAngleRoll;
}

s32 cur_obj_follow_path(UNUSED s32 unusedArg) {
    if (!o) { return 0; }
    struct Waypoint *startWaypoint;
    struct Waypoint *lastWaypoint;
    struct Waypoint *targetWaypoint;
    f32 prevToNextX, prevToNextY, prevToNextZ;
    UNUSED s32 sp2C;
    f32 objToNextXZ;
    f32 objToNextX, objToNextY, objToNextZ;

    if (o == NULL) { return PATH_NONE; }

    if (o->oPathedPrevWaypointFlags == 0) {
        o->oPathedPrevWaypoint = o->oPathedStartWaypoint;
        o->oPathedPrevWaypointFlags = WAYPOINT_FLAGS_INITIALIZED;
    }

    startWaypoint = o->oPathedStartWaypoint;
    lastWaypoint = o->oPathedPrevWaypoint;

    if (!startWaypoint) { return PATH_NONE; }

    // sanity check waypoints
    if (lastWaypoint == NULL) { lastWaypoint = startWaypoint; }
    struct Waypoint* tmpWaypoint = (lastWaypoint + 1);
    if (tmpWaypoint == NULL) { tmpWaypoint = lastWaypoint; }

    if (tmpWaypoint && tmpWaypoint->flags != WAYPOINT_FLAGS_END) {
        targetWaypoint = tmpWaypoint;
    } else {
        targetWaypoint = startWaypoint;
    }

    if (lastWaypoint == NULL) { return PATH_NONE; }
    if (targetWaypoint == NULL) { return PATH_NONE; }

    o->oPathedPrevWaypointFlags = lastWaypoint->flags | WAYPOINT_FLAGS_INITIALIZED;

    prevToNextX = targetWaypoint->pos[0] - lastWaypoint->pos[0];
    prevToNextY = targetWaypoint->pos[1] - lastWaypoint->pos[1];
    prevToNextZ = targetWaypoint->pos[2] - lastWaypoint->pos[2];

    objToNextX = targetWaypoint->pos[0] - o->oPosX;
    objToNextY = targetWaypoint->pos[1] - o->oPosY;
    objToNextZ = targetWaypoint->pos[2] - o->oPosZ;
    objToNextXZ = sqrtf(sqr(objToNextX) + sqr(objToNextZ));

    o->oPathedTargetYaw = atan2s(objToNextZ, objToNextX);
    o->oPathedTargetPitch = atan2s(objToNextXZ, -objToNextY);

    // If dot(prevToNext, objToNext) <= 0 (i.e. reached other side of target waypoint)
    if (prevToNextX * objToNextX + prevToNextY * objToNextY + prevToNextZ * objToNextZ <= 0.0f) {
        o->oPathedPrevWaypoint = targetWaypoint;
        struct Waypoint* tmpWaypoint2 = (targetWaypoint + 1);
        if (tmpWaypoint2 == NULL) { tmpWaypoint2 = targetWaypoint; }
        if (tmpWaypoint2 && tmpWaypoint2->flags == WAYPOINT_FLAGS_END) {
            return PATH_REACHED_END;
        } else {
            return PATH_REACHED_WAYPOINT;
        }
    }

    return PATH_NONE;
}

void chain_segment_init(struct ChainSegment *segment) {
    if (!o) { return; }
    if (segment == NULL) { return; }
    segment->posX = 0.0f;
    segment->posY = 0.0f;
    segment->posZ = 0.0f;

    segment->pitch = 0;
    segment->yaw = 0;
    segment->roll = 0;
}

f32 random_f32_around_zero(f32 diameter) {
    return random_float() * diameter - diameter / 2;
}

void obj_scale_random(struct Object *obj, f32 rangeLength, f32 minScale) {
    f32 scale = random_float() * rangeLength + minScale;
    obj_scale_xyz(obj, scale, scale, scale);
}

void obj_translate_xyz_random(struct Object *obj, f32 rangeLength) {
    if (obj == NULL) { return; }
    obj->oPosX += random_float() * rangeLength - rangeLength * 0.5f;
    obj->oPosY += random_float() * rangeLength - rangeLength * 0.5f;
    obj->oPosZ += random_float() * rangeLength - rangeLength * 0.5f;
}

void obj_translate_xz_random(struct Object *obj, f32 rangeLength) {
    if (obj == NULL) { return; }
    obj->oPosX += random_float() * rangeLength - rangeLength * 0.5f;
    obj->oPosZ += random_float() * rangeLength - rangeLength * 0.5f;
}

void obj_build_vel_from_transform(struct Object *a0) {
    if (a0 == NULL) { return; }
    f32 spC = a0->oUnkC0;
    f32 sp8 = a0->oUnkBC;
    f32 sp4 = a0->oForwardVel;

    a0->oVelX = a0->transform[0][0] * spC + a0->transform[1][0] * sp8 + a0->transform[2][0] * sp4;
    a0->oVelY = a0->transform[0][1] * spC + a0->transform[1][1] * sp8 + a0->transform[2][1] * sp4;
    a0->oVelZ = a0->transform[0][2] * spC + a0->transform[1][2] * sp8 + a0->transform[2][2] * sp4;
}

void cur_obj_set_pos_via_transform(void) {
    if (!o) { return; }
    obj_build_transform_from_pos_and_angle(o, O_PARENT_RELATIVE_POS_INDEX, O_MOVE_ANGLE_INDEX);
    obj_build_vel_from_transform(o);
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;
}

s16 cur_obj_reflect_move_angle_off_wall(void) {
    if (!o) { return 0; }
    s16 angle = o->oWallAngle - ((s16) o->oMoveAngleYaw - (s16) o->oWallAngle) + 0x8000;
    return angle;
}

void cur_obj_spawn_particles(struct SpawnParticlesInfo *info) {
    if (info == NULL) { return; }
    struct Object *particle;
    s32 i;
    f32 scale;
    s32 numParticles = info->count;

    // If there are a lot of objects already, limit the number of particles
    if (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY * 150 / 240) && numParticles > 10) {
        numParticles = 10;
    }
    

    // We're close to running out of object slots, so don't spawn particles at
    // all
    if (gPrevFrameObjectCount > (OBJECT_POOL_CAPACITY * 210 / 240)) {
        numParticles = 0;
    }

    for (i = 0; i < numParticles; i++) {
        scale = random_float() * (info->sizeRange * 0.1f) + info->sizeBase * 0.1f;

        particle = spawn_object(o, info->model, bhvWhitePuffExplosion);
        if (particle == NULL) { return; }

        particle->oBehParams2ndByte = info->behParam;
        particle->oMoveAngleYaw = random_u16();
        particle->oGravity = info->gravity;
        particle->oDragStrength = info->dragStrength;

        particle->oPosY += info->offsetY;
        particle->oForwardVel = random_float() * info->forwardVelRange + info->forwardVelBase;
        particle->oVelY = random_float() * info->velYRange + info->velYBase;

        obj_scale_xyz(particle, scale, scale, scale);
    }
}

void obj_set_hitbox(struct Object *obj, struct ObjectHitbox *hitbox) {
    if (obj == NULL || hitbox == NULL) { return; }
    if (!(obj->oFlags & OBJ_FLAG_30)) {
        obj->oFlags |= OBJ_FLAG_30;

        obj->oInteractType = hitbox->interactType;
        obj->oDamageOrCoinValue = hitbox->damageOrCoinValue;
        obj->oHealth = hitbox->health;
        obj->oNumLootCoins = hitbox->numLootCoins;

        cur_obj_become_tangible();
    }

    obj->hitboxRadius = obj->header.gfx.scale[0] * hitbox->radius;
    obj->hitboxHeight = obj->header.gfx.scale[1] * hitbox->height;
    obj->hurtboxRadius = obj->header.gfx.scale[0] * hitbox->hurtboxRadius;
    obj->hurtboxHeight = obj->header.gfx.scale[1] * hitbox->hurtboxHeight;
    obj->hitboxDownOffset = obj->header.gfx.scale[1] * hitbox->downOffset;
}

s32 signum_positive(s32 x) {
    if (x >= 0) {
        return 1;
    } else {
        return -1;
    }
}

f32 absf(f32 x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

s32 absi(s32 x) {
    if (x >= 0) {
        return x;
    } else {
        return -x;
    }
}

s32 cur_obj_wait_then_blink(s32 timeUntilBlinking, s32 numBlinks) {
    if (!o) { return 0; }
    s32 done = FALSE;
    s32 timeBlinking;

    if (o->oTimer >= timeUntilBlinking) {
        if ((timeBlinking = o->oTimer - timeUntilBlinking) % 2 != 0) {
            o->header.gfx.node.flags |= GRAPH_RENDER_INVISIBLE;
            if (timeBlinking / 2 > numBlinks) {
                done = TRUE;
            }
        } else {
            o->header.gfx.node.flags &= ~GRAPH_RENDER_INVISIBLE;
        }
    }

    return done;
}

s32 cur_obj_is_mario_ground_pounding_platform(void) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (!gMarioStates[i].marioObj) { continue; }
        if (gMarioStates[i].marioObj->platform == o) {
            u32 interaction = determine_interaction(&gMarioStates[i], o);
            if ((gMarioStates[i].action == ACT_GROUND_POUND_LAND) || (interaction & INT_GROUND_POUND && interaction & INT_LUA)) {
                return TRUE;
            }
        }
    }

    return FALSE;
}

void spawn_mist_particles(void) {
    spawn_mist_particles_variable(0, 0, 46.0f);
}

void spawn_mist_particles_with_sound(u32 sp18) {
    spawn_mist_particles_variable(0, 0, 46.0f);
    create_sound_spawner(sp18);
}

void cur_obj_push_mario_away(f32 radius) {
    if (!o) { return; }
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct Object* player = gMarioStates[i].marioObj;
        if (!player) { continue; }
        f32 marioRelX = player->oPosX - o->oPosX;
        f32 marioRelZ = player->oPosZ - o->oPosZ;
        f32 marioDist = sqrtf(sqr(marioRelX) + sqr(marioRelZ));

        if (marioDist < radius) {
            //! If this function pushes Mario out of bounds, it will trigger Mario's
            //  oob failsafe
            gMarioStates[i].pos[0] += (radius - marioDist) / radius * marioRelX;
            gMarioStates[i].pos[2] += (radius - marioDist) / radius * marioRelZ;
        }
    }
}

void cur_obj_push_mario_away_from_cylinder(f32 radius, f32 extentY) {
    if (!o) { return; }
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct Object* player = gMarioStates[i].marioObj;
        if (!player) { continue; }
        f32 marioRelY = player->oPosY - o->oPosY;

        if (marioRelY < 0.0f) {
            marioRelY = -marioRelY;
        }

        if (marioRelY >= extentY) { continue; }

        f32 marioRelX = player->oPosX - o->oPosX;
        f32 marioRelZ = player->oPosZ - o->oPosZ;
        f32 marioDist = sqrtf(sqr(marioRelX) + sqr(marioRelZ));

        if (marioDist < radius) {
            //! If this function pushes Mario out of bounds, it will trigger Mario's
            //  oob failsafe
            gMarioStates[i].pos[0] += (radius - marioDist) / radius * marioRelX;
            gMarioStates[i].pos[2] += (radius - marioDist) / radius * marioRelZ;
        }
    }
}

void bhv_dust_smoke_loop(void) {
    if (!o) { return; }
    o->oPosX += o->oVelX;
    o->oPosY += o->oVelY;
    o->oPosZ += o->oVelZ;

    if (o->oSmokeTimer == 10) {
        obj_mark_for_deletion(o);
    }

    o->oSmokeTimer++;
}

static void stub_obj_helpers_2(void) {
}

s32 cur_obj_set_direction_table(s8 *a0) {
    if (!o) { return 0; }
    o->oToxBoxMovementPattern = a0;
    o->oToxBoxMovementStep = 0;

    return *(s8 *) o->oToxBoxMovementPattern;
}

s32 cur_obj_progress_direction_table(void) {
    if (!o) { return 0; }
    s8 ret;
    s8 *table = o->oToxBoxMovementPattern;
    s32 index = o->oToxBoxMovementStep + 1;
    if (!table) { return 0; }

    s32 tableLength = 0;
    while (table[tableLength] != -1 && tableLength < 150) {
        tableLength++;
    }

    if (tableLength < 0 || index < 0 || tableLength >= 150 || index >= tableLength) {
        ret = table[0];
        o->oToxBoxMovementStep = 0;
        LOG_ERROR("Exceeded direction table! tableLength %d, index %d\n", tableLength, index);
    } else if (table[index] != -1) {
        ret = table[index];
        o->oToxBoxMovementStep++;
    } else {
        ret = table[0];
        o->oToxBoxMovementStep = 0;
    }

    return ret;
}

void stub_obj_helpers_3(UNUSED s32 sp0, UNUSED s32 sp4) {
}

void cur_obj_scale_over_time(s32 a0, s32 a1, f32 sp10, f32 sp14) {
    if (!o) { return; }
    f32 sp4 = sp14 - sp10;
    f32 sp0 = (f32) o->oTimer / a1;

    if (a0 & 0x01) {
        o->header.gfx.scale[0] = sp4 * sp0 + sp10;
    }

    if (a0 & 0x02) {
        o->header.gfx.scale[1] = sp4 * sp0 + sp10;
    }

    if (a0 & 0x04) {
        o->header.gfx.scale[2] = sp4 * sp0 + sp10;
    }
}

void cur_obj_set_pos_to_home_with_debug(void) {
    if (!o) { return; }
    o->oPosX = o->oHomeX + gDebugInfo[5][0];
    o->oPosY = o->oHomeY + gDebugInfo[5][1];
    o->oPosZ = o->oHomeZ + gDebugInfo[5][2];
    cur_obj_scale(gDebugInfo[5][3] / 100.0f + 1.0l);
}

void stub_obj_helpers_4(void) {
}

s32 cur_obj_is_mario_on_platform(void) {
    if (gMarioObject && gMarioObject->platform == o) {
        return TRUE;
    }
    return FALSE;
}

s32 cur_obj_is_any_player_on_platform(void) {
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        if (gMarioStates[i].marioObj == NULL) { continue; }
        if (gMarioStates[i].marioObj->platform == o) {
            return TRUE;
        }
    }
    return FALSE;
}

s32 cur_obj_shake_y_until(s32 cycles, s32 amount) {
    if (!o) { return 0; }
    if (o->oTimer % 2 != 0) {
        o->oPosY -= amount;
    } else {
        o->oPosY += amount;
    }

    if (o->oTimer == cycles * 2) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 cur_obj_move_up_and_down(s32 a0) {
    if (!o) { return 0; }
    if (a0 >= 4 || a0 < 0) {
        return TRUE;
    }

    o->oPosY += D_8032F0A0[a0];
    return FALSE;
}

void cur_obj_call_action_function(void (*actionFunctions[])(void), uint32_t actionFunctionsLength) {
    if (!o) { return; }
    if (!actionFunctions) { return; }
    if ((uint32_t)o->oAction >= actionFunctionsLength) { return; }
    void (*actionFunction)(void) = actionFunctions[o->oAction];
    if (!actionFunction) { return; }
    actionFunction();
}

struct Object *spawn_star_with_no_lvl_exit(s32 sp20, s32 sp24) {
    if (!o) { return NULL; }
    struct Object *sp1C = spawn_object(o, MODEL_STAR, bhvSpawnedStarNoLevelExit);
    if (sp1C == NULL) { return NULL; }
    sp1C->oSparkleSpawnUnk1B0 = sp24;
    sp1C->oBehParams = o->oBehParams;
    sp1C->oBehParams2ndByte = sp20;

    return sp1C;
}

// old unused initializer for 2d star spawn behavior.
// uses behavior parameters not used in the current sparkle code.
void spawn_base_star_with_no_lvl_exit(void) {
    spawn_star_with_no_lvl_exit(0, 0);
}

s32 bit_shift_left(s32 a0) {
    return BHV_ARR(D_8032F0A4, a0, s16);
}

s32 cur_obj_mario_far_away(void) {
    if (!o) { return 0; }
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!is_player_active(&gMarioStates[i])) { continue; }
        struct Object* player = gMarioStates[i].marioObj;
        if (!player) { continue; }
        f32 dx = o->oHomeX - player->oPosX;
        f32 dy = o->oHomeY - player->oPosY;
        f32 dz = o->oHomeZ - player->oPosZ;
        f32 marioDistToHome = sqrtf(dx * dx + dy * dy + dz * dz);
        if (marioDistToHome <= 2000.0f) { return FALSE; }
    }
    return (o->oDistanceToMario > 2000.0f);
}

s32 is_mario_moving_fast_or_in_air(s32 speedThreshold) {
    struct MarioState* marioState = nearest_mario_state_to_object(o);
    if (!marioState) {
        return FALSE;
    }

    if (marioState->forwardVel > speedThreshold) {
        return TRUE;
    }

    if (marioState->action & ACT_FLAG_AIR) {
        return TRUE;
    } else {
        return FALSE;
    }
}

s32 is_item_in_array(s8 item, s8 *array) {
    while (*array != -1) {
        if (*array == item) {
            return TRUE;
        }

        array++;
    }

    return FALSE;
}

static void stub_obj_helpers_5(void) {
}

void bhv_init_room(void) {
    if (!o) { return; }
    struct Surface *floor;
    f32 floorHeight;

    if (is_item_in_array(gCurrLevelNum, sLevelsWithRooms)) {
        floorHeight = find_floor(o->oPosX, o->oPosY, o->oPosZ, &floor);

        if (floor != NULL) {
            if (floor->room != 0) {
                o->oRoom = floor->room;
            } else {
                // Floor probably belongs to a platform object. Try looking
                // underneath it
                find_floor(o->oPosX, floorHeight - 100.0f, o->oPosZ, &floor);
                if (floor != NULL) {
                    //! Technically possible that the room could still be 0 here
                    o->oRoom = floor->room;
                }
            }
        }
    } else {
        o->oRoom = -1;
    }
}

void cur_obj_enable_rendering_if_mario_in_room(void) {
    if (!o) { return; }
    if (o->oRoom == -1) { return; }
    if (gMarioCurrentRoom == 0) { return; }

    u8 marioInRoom = FALSE;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (gMarioStates[i].currentRoom != 0) {
            s16 currentRoom = gMarioStates[i].currentRoom;
            if (currentRoom == o->oRoom) {
                marioInRoom = TRUE;
            } else if (gDoorAdjacentRooms[currentRoom][0] == o->oRoom) {
                marioInRoom = TRUE;
            } else if (gDoorAdjacentRooms[currentRoom][1] == o->oRoom) {
                marioInRoom = TRUE;
            }
        }
    }

    u8 inViewOfOpenDoor = (gDoorCurrentRoom != 0)
                       && (gDoorAdjacentRooms[gDoorCurrentRoom][0] == o->oRoom || gDoorAdjacentRooms[gDoorCurrentRoom][1] == o->oRoom);

    if (marioInRoom || inViewOfOpenDoor) {
        cur_obj_enable_rendering();
        o->activeFlags &= ~ACTIVE_FLAG_IN_DIFFERENT_ROOM;
        gNumRoomedObjectsInMarioRoom++;
    } else {
        cur_obj_disable_rendering();
        o->activeFlags |= ACTIVE_FLAG_IN_DIFFERENT_ROOM;
        gNumRoomedObjectsNotInMarioRoom++;
    }
}

s32 cur_obj_set_hitbox_and_die_if_attacked(struct ObjectHitbox *hitbox, s32 deathSound, s32 noLootCoins) {
    if (!o) { return 0; }
    s32 interacted = FALSE;

    obj_set_hitbox(o, hitbox);

    if (noLootCoins) {
        o->oNumLootCoins = 0;
    }

    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        if (o->oInteractStatus & INT_STATUS_WAS_ATTACKED) {
            spawn_mist_particles();
            obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
            obj_mark_for_deletion(o);
            create_sound_spawner(deathSound);
        } else {
            interacted = TRUE;
        }
    }

    o->oInteractStatus = 0;
    return interacted;
}


void obj_explode_and_spawn_coins(f32 sp18, s32 sp1C) {
    if (!o) { return; }
    spawn_mist_particles_variable(0, 0, sp18);
    spawn_triangle_break_particles(30, 138, 3.0f, 4);
    obj_mark_for_deletion(o);

    if (sp1C == 1) {
        obj_spawn_loot_yellow_coins(o, o->oNumLootCoins, 20.0f);
    } else if (sp1C == 2) {
        obj_spawn_loot_blue_coins(o, o->oNumLootCoins, 20.0f, 150);
    }
}

void obj_set_collision_data(struct Object *obj, const void *segAddr) {
    obj->collisionData = segmented_to_virtual(segAddr);
}

void cur_obj_if_hit_wall_bounce_away(void) {
    if (!o) { return; }
    if (o->oMoveFlags & OBJ_MOVE_HIT_WALL) {
        o->oMoveAngleYaw = o->oWallAngle;
    }
}

s32 cur_obj_hide_if_mario_far_away_y(f32 distY) {
    if (!o) { return 0; }
    if (!gMarioStates[0].marioObj) { return FALSE; }
    if (absf(o->oPosY - gMarioStates[0].marioObj->oPosY) < distY * draw_distance_scalar()) {
        cur_obj_unhide();
        return FALSE;
    }
    cur_obj_hide();
    return TRUE;
}

Gfx *geo_offset_klepto_held_object(s32 callContext, struct GraphNode *node, UNUSED Mat4 mtx) {
    if (callContext == GEO_CONTEXT_RENDER) {
        ((struct GraphNodeTranslationRotation *) node->next)->translation[0] = 300;
        ((struct GraphNodeTranslationRotation *) node->next)->translation[1] = 300;
        ((struct GraphNodeTranslationRotation *) node->next)->translation[2] = 0;
    }

    return NULL;
}

s32 geo_offset_klepto_debug(s32 callContext, struct GraphNode *a1, UNUSED s32 sp8) {
    if (callContext == GEO_CONTEXT_RENDER) {
        ((struct GraphNode_802A45E4 *) a1->next)->unk18 = gDebugInfo[4][0];
        ((struct GraphNode_802A45E4 *) a1->next)->unk1A = gDebugInfo[4][1];
        ((struct GraphNode_802A45E4 *) a1->next)->unk1C = gDebugInfo[4][2];
        ((struct GraphNode_802A45E4 *) a1->next)->unk1E = gDebugInfo[4][3];
        ((struct GraphNode_802A45E4 *) a1->next)->unk20 = gDebugInfo[4][4];
        ((struct GraphNode_802A45E4 *) a1->next)->unk22 = gDebugInfo[4][5];
    }

    return 0;
}

s32 obj_is_hidden(struct Object *obj) {
    if (!obj) { return 0; }
    if (obj->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void enable_time_stop(void) {
    gTimeStopState |= TIME_STOP_ENABLED;
}

void enable_time_stop_if_alone(void) {
    if (network_player_connected_count() > 1) {
        return;
    }
    gTimeStopState |= TIME_STOP_ENABLED;
}

void disable_time_stop(void) {
    gTimeStopState &= ~TIME_STOP_ENABLED;
}

void set_time_stop_flags(s32 flags) {
    gTimeStopState |= flags;
}

void set_time_stop_flags_if_alone(s32 flags) {
    if (network_player_connected_count() > 1) {
        return;
    }
    gTimeStopState |= flags;
}

void clear_time_stop_flags(s32 flags) {
    gTimeStopState = gTimeStopState & (flags ^ 0xFFFFFFFF);
}

s32 cur_obj_can_mario_activate_textbox(struct MarioState* m, f32 radius, f32 height, UNUSED s32 unused) {
    if (!o || !m) { return 0; }
    if (!m->visibleToEnemies) { return FALSE; }
    if (o->oDistanceToMario < 1500.0f) {
        f32 latDistToMario = lateral_dist_between_objects(o, m->marioObj);
        UNUSED s16 angleFromMario = obj_angle_to_object(m->marioObj, o);

        if (latDistToMario < radius && o->oPosY < m->marioObj->oPosY + 160.0f
            && m->marioObj->oPosY < o->oPosY + height && !(m->action & ACT_FLAG_AIR)
            && mario_ready_to_speak(m)) {
            return TRUE;
        }
    }

    return FALSE;
}

s32 cur_obj_can_mario_activate_textbox_2(struct MarioState* m, f32 radius, f32 height) {
    // The last argument here is unused. When this function is called directly the argument is always set to 0x7FFF.
    return cur_obj_can_mario_activate_textbox(m, radius, height, 0x1000);
}

void cur_obj_end_dialog(struct MarioState* m, s32 dialogFlags, s32 dialogResult) {
    if (!o || !m) { return; }
    if (m->playerIndex != 0) { return; }

    o->oDialogResponse = dialogResult;
    o->oDialogState++;

    if (!(dialogFlags & DIALOG_UNK1_FLAG_4)) {
        set_mario_npc_dialog(m, 0, NULL);
    }
}

s32 cur_obj_update_dialog(struct MarioState* m, s32 actionArg, s32 dialogFlags, s32 dialogID, UNUSED s32 unused, u8 (*inContinueDialogFunction)(void)) {
    if (!o || !m) { return 0; }
    s32 dialogResponse = 0;
    UNUSED s32 doneTurning = TRUE;

    if (m->playerIndex != 0) { return 0; }

    switch (o->oDialogState) {
#ifdef VERSION_JP
        case DIALOG_UNK1_ENABLE_TIME_STOP:
            //! We enable time stop even if Mario is not ready to speak. This
            //  allows us to move during time stop as long as Mario never enters
            //  an action that can be interrupted with text.
            if (m->health >= 0x100) {
                gTimeStopState |= TIME_STOP_ENABLED;
                o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
            }
            break;
#else
        case DIALOG_UNK1_ENABLE_TIME_STOP:
            // Patched :(
            // Wait for Mario to be ready to speak, and then enable time stop
            if (mario_ready_to_speak(m) || m->action == ACT_READING_NPC_DIALOG) {
                //gTimeStopState |= TIME_STOP_ENABLED;
                //o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
            } else {
                break;
            }
            // Fall through so that Mario's action is interrupted immediately
            // after time is stopped
#endif

        case DIALOG_UNK1_INTERRUPT_MARIO_ACTION:
            if (set_mario_npc_dialog(m, actionArg, inContinueDialogFunction) == 2) {
                o->oDialogState++;
            }
            break;

        case DIALOG_UNK1_BEGIN_DIALOG:
            if (dialogFlags & DIALOG_UNK1_FLAG_RESPONSE) {
                create_dialog_box_with_response(dialogID);
            } else if (dialogFlags & DIALOG_UNK1_FLAG_DEFAULT) {
                create_dialog_box(dialogID);
            }
            o->oDialogState++;
            break;

        case DIALOG_UNK1_AWAIT_DIALOG:
            if (dialogFlags & DIALOG_UNK1_FLAG_RESPONSE) {
                if (gDialogResponse != 0) {
                    cur_obj_end_dialog(m, dialogFlags, gDialogResponse);
                }
            } else if (dialogFlags & DIALOG_UNK1_FLAG_DEFAULT) {
                if (get_dialog_id() == -1) {
                    cur_obj_end_dialog(m, dialogFlags, 3);
                }
            } else {
                cur_obj_end_dialog(m, dialogFlags, 3);
            }
            break;

        case DIALOG_UNK1_DISABLE_TIME_STOP:
            if (m->action != ACT_READING_NPC_DIALOG || (dialogFlags & DIALOG_UNK1_FLAG_4)) {
                gTimeStopState &= ~TIME_STOP_ENABLED;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                dialogResponse = o->oDialogResponse;
                o->oDialogState = DIALOG_UNK1_ENABLE_TIME_STOP;
            }
            break;

        default:
            o->oDialogState = DIALOG_UNK1_ENABLE_TIME_STOP;
            break;
    }

    return dialogResponse;
}

s32 cur_obj_update_dialog_with_cutscene(struct MarioState* m, s32 actionArg, s32 dialogFlags, s32 cutsceneTable, s32 dialogID, u8 (*inContinueDialogFunction)(void)) {
    if (!o || !m) { return 0; }
    s32 dialogResponse = 0;
    s32 doneTurning = TRUE;

    if (m->playerIndex != 0) { return 0; }
    if (!m->visibleToEnemies) { return FALSE; }

    switch (o->oDialogState) {
#ifdef VERSION_JP
        case DIALOG_UNK2_ENABLE_TIME_STOP:
            //! We enable time stop even if Mario is not ready to speak. This
            //  allows us to move during time stop as long as Mario never enters
            //  an action that can be interrupted with text.
            if (m->health >= 0x0100) {
                //gTimeStopState |= TIME_STOP_ENABLED;
                //o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
                o->oDialogResponse = 0;
            }
            break;
#else
        case DIALOG_UNK2_ENABLE_TIME_STOP:
            // Wait for Mario to be ready to speak, and then enable time stop
            if (mario_ready_to_speak(m) || m->action == ACT_READING_NPC_DIALOG) {
                //gTimeStopState |= TIME_STOP_ENABLED;
                //o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
                o->oDialogState++;
                o->oDialogResponse = 0;
            } else {
                break;
            }
            // Fall through so that Mario's action is interrupted immediately
            // after time is stopped
#endif

        case DIALOG_UNK2_TURN_AND_INTERRUPT_MARIO_ACTION:
            if (dialogFlags & DIALOG_UNK2_FLAG_0) {
                doneTurning = cur_obj_rotate_yaw_toward(obj_angle_to_object(o, m->marioObj), 0x800);
                if (o->oDialogResponse >= 33) {
                    doneTurning = TRUE;
                }
            }

            if (set_mario_npc_dialog(m, actionArg, inContinueDialogFunction) == 2 && doneTurning) {
                o->oDialogResponse = 0;
                o->oDialogState++;
            } else {
                o->oDialogResponse++;
            }
            break;

        case DIALOG_UNK2_AWAIT_DIALOG:
            if (cutsceneTable == CUTSCENE_CAP_SWITCH_PRESS) {
                if ((o->oDialogResponse = cutscene_object_without_dialog(cutsceneTable, o)) != 0) {
                    o->oDialogState++;
                }
            } else {
                if ((o->oDialogResponse = cutscene_object_with_dialog(cutsceneTable, o, dialogID)) != 0) {
                    o->oDialogState++;
                }
            }
            break;

        case DIALOG_UNK2_END_DIALOG:
            if (dialogFlags & DIALOG_UNK2_LEAVE_TIME_STOP_ENABLED) {
                dialogResponse = o->oDialogResponse;
                o->oDialogState = DIALOG_UNK2_ENABLE_TIME_STOP;
            } else if (m->action != ACT_READING_NPC_DIALOG) {
                gTimeStopState &= ~TIME_STOP_ENABLED;
                o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
                dialogResponse = o->oDialogResponse;
                o->oDialogState = DIALOG_UNK2_ENABLE_TIME_STOP;
            } else {
                set_mario_npc_dialog(m, 0, NULL);
            }
            break;
    }

    return dialogResponse;
}

s32 cur_obj_has_model(u16 modelID) {
    if (!o) { return 0; }
    struct GraphNode* node = dynos_model_get_geo(modelID);
    if (o->header.gfx.sharedChild == node) {
        return TRUE;
    } else if (o->header.gfx.sharedChild && node && o->header.gfx.sharedChild->georef == node->georef) {
        return TRUE;
    } else {
        return FALSE;
    }
}

void cur_obj_align_gfx_with_floor(void) {
    if (!o) { return; }
    struct Surface *floor;
    Vec3f floorNormal;
    Vec3f position;

    position[0] = o->oPosX;
    position[1] = o->oPosY;
    position[2] = o->oPosZ;

    find_floor(position[0], position[1], position[2], &floor);
    if (floor != NULL) {
        floorNormal[0] = floor->normal.x;
        floorNormal[1] = floor->normal.y;
        floorNormal[2] = floor->normal.z;

        mtxf_align_terrain_normal(o->transform, floorNormal, position, o->oFaceAngleYaw);
        o->header.gfx.throwMatrix = &o->transform;
    }
}

s32 mario_is_within_rectangle(s16 minX, s16 maxX, s16 minZ, s16 maxZ) {
    if (!gMarioObject) { return FALSE; }
    if (gMarioObject->oPosX < minX || maxX < gMarioObject->oPosX) {
        return FALSE;
    }

    if (gMarioObject->oPosZ < minZ || maxZ < gMarioObject->oPosZ) {
        return FALSE;
    }

    return TRUE;
}

void cur_obj_shake_screen(s32 shake) {
    if (!o) { return; }
    set_camera_shake_from_point(shake, o->oPosX, o->oPosY, o->oPosZ);
}

s32 obj_attack_collided_from_other_object(struct Object *obj) {
    if (obj == NULL) { return FALSE; }
    s32 numCollidedObjs;
    struct Object *other;
    s32 touchedOtherObject = FALSE;

    numCollidedObjs = obj->numCollidedObjs;
    if (numCollidedObjs != 0) {
        other = obj->collidedObjs[0];

        if (!(other->oInteractType & INTERACT_PLAYER)) {
            other->oInteractStatus |= ATTACK_PUNCH | INT_STATUS_WAS_ATTACKED | INT_STATUS_INTERACTED
                                      | INT_STATUS_TOUCHED_BOB_OMB;
            touchedOtherObject = TRUE;
        }
    }

    return touchedOtherObject;
}

s32 cur_obj_was_attacked_or_ground_pounded(void) {
    if (!o) { return 0; }
    s32 attacked = FALSE;

    if ((o->oInteractStatus & INT_STATUS_INTERACTED)
        && (o->oInteractStatus & INT_STATUS_WAS_ATTACKED)) {
        attacked = TRUE;
    }

    if (cur_obj_is_mario_ground_pounding_platform()) {
        attacked = TRUE;
    }

    o->oInteractStatus = 0;
    return attacked;
}

void obj_copy_behavior_params(struct Object *dst, struct Object *src) {
    if (dst == NULL || src == NULL) { return; }
    dst->oBehParams = src->oBehParams;
    dst->oBehParams2ndByte = src->oBehParams2ndByte;
}

void cur_obj_init_animation_and_anim_frame(s32 animIndex, s32 animFrame) {
    if (!o) { return; }
    cur_obj_init_animation_with_sound(animIndex);
    o->header.gfx.animInfo.animFrame = animFrame;
}

s32 cur_obj_init_animation_and_check_if_near_end(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    return cur_obj_check_if_near_animation_end();
}

void cur_obj_init_animation_and_extend_if_at_end(s32 animIndex) {
    cur_obj_init_animation_with_sound(animIndex);
    cur_obj_extend_animation_if_at_end();
}

s32 cur_obj_check_grabbed_mario(void) {
    if (!o) { return 0; }
    if (o->oInteractStatus & INT_STATUS_GRABBED_MARIO) {
        o->oKingBobombUnk88 = 1;
        cur_obj_become_intangible();
        return TRUE;
    }

    return FALSE;
}

s32 player_performed_grab_escape_action(void) {
    static s32 grabReleaseState;
    s32 result = FALSE;

    if (gPlayer1Controller->stickMag < 30.0f) {
        grabReleaseState = 0;
    }

    if (grabReleaseState == 0 && gPlayer1Controller->stickMag > 40.0f) {
        grabReleaseState = 1;
        result = TRUE;
    }

    if (gPlayer1Controller->buttonPressed & A_BUTTON) {
        result = TRUE;
    }

    return result;
}

void cur_obj_unused_play_footstep_sound(s32 animFrame1, s32 animFrame2, s32 sound) {
    if (cur_obj_check_anim_frame(animFrame1) || cur_obj_check_anim_frame(animFrame2)) {
        cur_obj_play_sound_2(sound);
    }
}

void enable_time_stop_including_mario(void) {
    gTimeStopState |= TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS;
    if (o) {
        o->activeFlags |= ACTIVE_FLAG_INITIATED_TIME_STOP;
    }
}

void disable_time_stop_including_mario(void) {
    gTimeStopState &= ~(TIME_STOP_ENABLED | TIME_STOP_MARIO_AND_DOORS);
    if (o) {
        o->activeFlags &= ~ACTIVE_FLAG_INITIATED_TIME_STOP;
    }
}

s32 cur_obj_check_interacted(void) {
    if (!o) { return 0; }
    if (o->oInteractStatus & INT_STATUS_INTERACTED) {
        o->oInteractStatus = 0;
        return TRUE;
    } else {
        return FALSE;
    }
}

void cur_obj_spawn_loot_blue_coin(void) {
    if (o && o->oNumLootCoins >= 5) {
        spawn_object(o, MODEL_BLUE_COIN, bhvMrIBlueCoin);
        o->oNumLootCoins -= 5;
    }
}

#ifndef VERSION_JP
void cur_obj_spawn_star_at_y_offset(f32 targetX, f32 targetY, f32 targetZ, f32 offsetY) {
    if (!o) { return; }
    f32 objectPosY = o->oPosY;
    o->oPosY += offsetY + gDebugInfo[5][0];
    spawn_default_star(targetX, targetY, targetZ);
    o->oPosY = objectPosY;
}
#endif

void cur_obj_set_home_once(void) {
    if (!o) { return; }
    if (o->setHome) { return; }
    o->setHome = TRUE;
    o->oHomeX = o->oPosX;
    o->oHomeY = o->oPosY;
    o->oHomeZ = o->oPosZ;
}

s32 get_trajectory_length(Trajectory* trajectory) {
    if (!trajectory) { return 0; }
    s32 count = 0;
    s16* c = trajectory;
    while (*c != -1) {
        count++;
        c += 4;
    }
    return count;
}