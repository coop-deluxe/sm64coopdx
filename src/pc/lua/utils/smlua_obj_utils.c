#include "types.h"
#include "object_constants.h"
#include "object_fields.h"
#include "src/game/object_helpers.h"
#include "src/game/interaction.h"
#include "engine/math_util.h"

#include "pc/lua/smlua.h"
#include "smlua_obj_utils.h"
#include "smlua_model_utils.h"
#include "pc/debuglog.h"

static struct Object* spawn_object_internal(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction, bool doSync) {
    if (doSync) {
        // prevent spawning objects before area is synchronized
        if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return NULL; }
    }

    const BehaviorScript* behavior = get_behavior_from_id(behaviorId);
    if (behavior == NULL) {
        LOG_ERROR("failed to find behavior %u", behaviorId);
        return NULL;
    }

    u8 loadedModelId = smlua_model_util_load(modelId);
    if (loadedModelId == 0xFF) {
        LOG_ERROR("failed to load model  %u", modelId);
        return NULL;
    }

    struct Object* obj = spawn_object(gMarioStates[0].marioObj, loadedModelId, behavior);

    if (obj == NULL) {
        LOG_ERROR("failed to allocate object");
        return NULL;
    }

    if (doSync && !sync_object_set_id(obj)) {
        obj->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        LOG_ERROR("failed to set sync id");
        return NULL;
    }

    obj->parentObj = obj;

    obj->oPosX = x;
    obj->oPosY = y;
    obj->oPosZ = z;

    obj->oHomeX = x;
    obj->oHomeY = y;
    obj->oHomeZ = z;

    obj->coopFlags = COOP_OBJ_FLAG_LUA;
    if (!doSync) { obj->coopFlags |= COOP_OBJ_FLAG_NON_SYNC; }

    if (objSetupFunction != 0) {
        lua_State* L = gLuaState;
        lua_rawgeti(L, LUA_REGISTRYINDEX, objSetupFunction);
        smlua_push_object(L, LOT_OBJECT, obj);
        if (0 != smlua_pcall(L, 1, 0, 0)) {
            LOG_LUA("Failed to call the object setup callback: %u", objSetupFunction);
        }
    }

    struct SyncObject* so = sync_object_get(obj->oSyncID);
    if (doSync && so) {
        so->extendedModelId = modelId;
        so->o = obj;
        so->behavior = (BehaviorScript*) behavior;

        struct Object* spawn_objects[] = { obj };
        u32 models[] = { loadedModelId };
        network_send_spawn_objects(spawn_objects, models, 1);
    }

    return obj;
}

struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction) {
    return spawn_object_internal(behaviorId, modelId, x, y, z, objSetupFunction, true);
}

struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction) {
    return spawn_object_internal(behaviorId, modelId, x, y, z, objSetupFunction, false);
}

s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId) {
    const BehaviorScript *behavior = get_behavior_from_id(behaviorId);
    return o->behavior == smlua_override_behavior(behavior);
}

s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId) {
    struct GraphNode *model = gLoadedGraphNodes[smlua_model_util_load(modelId)];
    return o->header.gfx.sharedChild == model;
}

void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId) {
    obj_set_model(o, smlua_model_util_load(modelId));
}

Trajectory* get_trajectory(const char* name) {
    return dynos_level_get_trajectory(name);
}

//
// Helpers to iterate through the object table
//

struct Object *obj_get_first(enum ObjectList objList) {
    if (gObjectLists && objList >= 0 && objList < NUM_OBJ_LISTS) {
        struct Object *head = (struct Object *) &gObjectLists[objList];
        struct Object *obj = (struct Object *) head->header.next;
        if (obj != head) {
            return obj;
        }
    }
    return NULL;
}

struct Object *obj_get_first_with_behavior_id(enum BehaviorId behaviorId) {
    const BehaviorScript* behavior = get_behavior_from_id(behaviorId);
    behavior = smlua_override_behavior(behavior);
    if (behavior) {
        enum ObjectList objList = get_object_list_from_behavior(behavior);
        for (struct Object *obj = obj_get_first(objList); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                return obj;
            }
        }
    }
    return NULL;
}

struct Object *obj_get_first_with_behavior_id_and_field_s32(enum BehaviorId behaviorId, s32 fieldIndex, s32 value) {
    const BehaviorScript* behavior = get_behavior_from_id(behaviorId);
    behavior = smlua_override_behavior(behavior);
    if (behavior) {
        enum ObjectList objList = get_object_list_from_behavior(behavior);
        for (struct Object *obj = obj_get_first(objList); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj->OBJECT_FIELD_S32(fieldIndex) == value) {
                return obj;
            }
        }
    }
    return NULL;
}

struct Object *obj_get_first_with_behavior_id_and_field_f32(enum BehaviorId behaviorId, s32 fieldIndex, f32 value) {
    const BehaviorScript* behavior = get_behavior_from_id(behaviorId);
    behavior = smlua_override_behavior(behavior);
    if (behavior) {
        enum ObjectList objList = get_object_list_from_behavior(behavior);
        for (struct Object *obj = obj_get_first(objList); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj->OBJECT_FIELD_F32(fieldIndex) == value) {
                return obj;
            }
        }
    }
    return NULL;
}

struct Object *obj_get_nearest_object_with_behavior_id(struct Object *o, enum BehaviorId behaviorId) {
    f32 minDist = 0x20000;
    const BehaviorScript *behavior = get_behavior_from_id(behaviorId);
    behavior = smlua_override_behavior(behavior);
    struct Object *closestObj = NULL;
    
    if (behavior) {
        enum ObjectList objList = get_object_list_from_behavior(behavior);
        for (struct Object *obj = obj_get_first(objList); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                f32 objDist = dist_between_objects(o, obj);
                if (objDist < minDist) {
                    closestObj = obj;
                    minDist = objDist;
                }
            }
        }
    }
    return closestObj;
}

s32 obj_count_objects_with_behavior_id(enum BehaviorId behaviorId) {
    const BehaviorScript *behavior = get_behavior_from_id(behaviorId);
    behavior = smlua_override_behavior(behavior);
    s32 count = 0;
    
    if (behavior) {
        enum ObjectList objList = get_object_list_from_behavior(behavior);
        for (struct Object *obj = obj_get_first(objList); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == behavior) { count++; }
        }
    }
    
    return count;
}

struct Object *obj_get_next(struct Object *o) {
    if (gObjectLists && o) {
        enum ObjectList objList = get_object_list_from_behavior(o->behavior);
        struct Object *head = (struct Object *) &gObjectLists[objList];
        struct Object *next = (struct Object *) o->header.next;
        if (next != head) {
            return next;
        }
    }
    return NULL;
}

struct Object *obj_get_next_with_same_behavior_id(struct Object *o) {
    if (o) {
        for (struct Object *obj = obj_get_next(o); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == o->behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED) {
                return obj;
            }
        }
    }
    return NULL;
}

struct Object *obj_get_next_with_same_behavior_id_and_field_s32(struct Object *o, s32 fieldIndex, s32 value) {
    if (o) {
        for (struct Object *obj = obj_get_next(o); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == o->behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj->OBJECT_FIELD_S32(fieldIndex) == value) {
                return obj;
            }
        }
    }
    return NULL;
}

struct Object *obj_get_next_with_same_behavior_id_and_field_f32(struct Object *o, s32 fieldIndex, f32 value) {
    if (o) {
        for (struct Object *obj = obj_get_next(o); obj != NULL; obj = obj_get_next(obj)) {
            if (obj->behavior == o->behavior && obj->activeFlags != ACTIVE_FLAG_DEACTIVATED && obj->OBJECT_FIELD_F32(fieldIndex) == value) {
                return obj;
            }
        }
    }
    return NULL;
}

struct SpawnParticlesInfo* obj_get_temp_spawn_particles_info(enum ModelExtendedId modelId) {
    static struct SpawnParticlesInfo sTmpSpi = { 0 };
    memset(&sTmpSpi, 0, sizeof(struct SpawnParticlesInfo));

    u8 loadedModelId = smlua_model_util_load(modelId);
    if (loadedModelId == 0xFF) {
        LOG_ERROR("failed to load model  %u", modelId);
        return NULL;
    }
    sTmpSpi.model = loadedModelId;

    return &sTmpSpi;
}

struct ObjectHitbox* get_temp_object_hitbox(void) {
    static struct ObjectHitbox sTmpHitbox = { 0 };
    memset(&sTmpHitbox, 0, sizeof(struct ObjectHitbox));
    return &sTmpHitbox;
}

bool obj_is_attackable(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return ((o->oInteractType & INTERACT_KOOPA) != 0 ||
            (o->oInteractType & INTERACT_BOUNCE_TOP) != 0 ||
            (o->oInteractType & INTERACT_BOUNCE_TOP2) != 0 ||
            (o->oInteractType & INTERACT_HIT_FROM_BELOW) != 0);
}

bool obj_is_breakable_object(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return (obj_has_behavior_id(o, id_bhvBreakableBox) == 1 ||
            obj_has_behavior_id(o, id_bhvBreakableBoxSmall) == 1 ||
            obj_has_behavior_id(o, id_bhvHiddenObject) == 1 ||
            obj_has_behavior_id(o, id_bhvJumpingBox) == 1);
}

bool obj_is_bully(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return (o->oInteractType & INTERACT_BULLY) != 0;
}

bool obj_is_coin(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return (o->oInteractType & INTERACT_COIN) != 0;
}

bool obj_is_exclamation_box(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return obj_has_behavior_id(o, id_bhvExclamationBox) == 1 && o->oAction == 2;
}

bool obj_is_grabbable(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return (o->oInteractType & INTERACT_GRABBABLE) != 0 && (o->oInteractionSubtype & INT_SUBTYPE_NOT_GRABBABLE) == 0;
}

bool obj_is_mushroom_1up(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return (o->header.gfx.node.flags & GRAPH_RENDER_INVISIBLE) == 0 && (
            obj_has_behavior_id(o, id_bhv1Up) == 1 ||
            obj_has_behavior_id(o, id_bhv1upJumpOnApproach) == 1 ||
            obj_has_behavior_id(o, id_bhv1upRunningAway) == 1 ||
            obj_has_behavior_id(o, id_bhv1upSliding) == 1 ||
            obj_has_behavior_id(o, id_bhv1upWalking) == 1 ||
            obj_has_behavior_id(o, id_bhvHidden1up) == 1 ||
            obj_has_behavior_id(o, id_bhvHidden1upInPole) == 1 ||
            obj_has_behavior_id(o, id_bhvHidden1upInPoleSpawner) == 1 ||
            obj_has_behavior_id(o, id_bhvHidden1upInPoleTrigger) == 1 ||
            obj_has_behavior_id(o, id_bhvHidden1upTrigger) == 1);
}

bool obj_is_secret(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return obj_has_behavior_id(o, id_bhvHiddenStarTrigger) == 1;
}

bool obj_is_valid_for_interaction(struct Object *o) {
    if (o == NULL) { return FALSE; }
    
    return o->activeFlags != ACTIVE_FLAG_DEACTIVATED && o->oIntangibleTimer == 0 && (o->oInteractStatus & INT_STATUS_INTERACTED) == 0;
}

bool obj_check_hitbox_overlap(struct Object *o1, struct Object *o2) {
    if (o1 == NULL || o2 == NULL) { return FALSE; }
    
    f32 o1H = max(o1->hitboxHeight, o1->hurtboxHeight);
    f32 o1R = max(o1->hitboxRadius, o1->hurtboxRadius);
    f32 o2H = max(o2->hitboxHeight, o2->hurtboxHeight);
    f32 o2R = max(o2->hitboxRadius, o2->hurtboxRadius);
    
    f32 r2 = sqr(o1R + o2R);
    f32 d2 = sqr(o1->oPosX - o2->oPosX) + sqr(o1->oPosZ - o2->oPosZ);
    if (d2 > r2) return FALSE;
    f32 hb1lb = o1->oPosY - o1->hitboxDownOffset;
    f32 hb1ub = hb1lb + o1H;
    f32 hb2lb = o2->oPosY - o2->hitboxDownOffset;
    f32 hb2ub = hb2lb + o2H;
    f32 hbsoh = o1H + o2H;
    if ((hb2ub - hb1lb) > hbsoh || (hb1ub - hb2lb) > hbsoh) return FALSE;
    return TRUE;
}

bool obj_check_overlap_with_hitbox_params(struct Object *o, f32 x, f32 y, f32 z, f32 h, f32 r, f32 d) {
    if (o == NULL) { return FALSE; }
    
    f32 oH = max(o->hitboxHeight, o->hurtboxHeight);
    f32 oR = max(o->hitboxRadius, o->hurtboxRadius);
    
    f32 r2 = sqr(oR + r);
    f32 d2 = sqr(o->oPosX - x) + sqr(o->oPosZ - z);
    if (d2 > r2) return FALSE;
    f32 hb1lb = o->oPosY - o->hitboxDownOffset;
    f32 hb1ub = hb1lb + oH;
    f32 hb2lb = y - d;
    f32 hb2ub = hb2lb + h;
    f32 hbsoh = oH + h;
    if ((hb2ub - hb1lb) > hbsoh || (hb1ub - hb2lb) > hbsoh) return FALSE;
    return TRUE;
}

void obj_set_vel(struct Object *o, f32 vx, f32 vy, f32 vz) {
    if (o == NULL) { return; }
    
    o->oVelX = vx;
    o->oVelY = vy;
    o->oVelZ = vz;
}

void obj_move_xyz(struct Object *o, f32 dx, f32 dy, f32 dz) {
    if (o == NULL) { return; }
    
    o->oPosX += dx;
    o->oPosY += dy;
    o->oPosZ += dz;
}

void set_whirlpools(f32 x, f32 y, f32 z, s16 strength, s16 area, s32 index) {
    static struct Whirlpool whirlpool;

    gAreas[area].whirlpools[index] = &whirlpool;
    gAreas[area].whirlpools[index]->pos[0] = x;
    gAreas[area].whirlpools[index]->pos[1] = y;
    gAreas[area].whirlpools[index]->pos[2] = z;
    gAreas[area].whirlpools[index]->strength = strength;
}
