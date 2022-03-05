#include "types.h"
#include "object_constants.h"
#include "object_fields.h"
#include "src/game/object_helpers.h"

#include "smlua.h"
#include "smlua_obj_utils.h"
#include "smlua_model_utils.h"
#include "pc/debuglog.h"

static struct Object* spawn_object_internal(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction, bool doSync) {
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

    if (doSync && !network_set_sync_id(obj)) {
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

    obj->createdThroughNetwork = true;

    if (objSetupFunction != 0) {
        lua_State* L = gLuaState;
        lua_rawgeti(L, LUA_REGISTRYINDEX, objSetupFunction);
        smlua_push_object(L, LOT_OBJECT, obj);
        if (0 != lua_pcall(L, 1, 0, 0)) {
            LOG_LUA("Failed to call the callback: %u, %s", objSetupFunction, lua_tostring(L, -1));
            smlua_logline();
        }
    }

    if (doSync) {
        struct SyncObject* so = &gSyncObjects[obj->oSyncID];
        so->extendedModelId = modelId;
        so->o = obj;

        struct Object* spawn_objects[] = { obj };
        u32 models[] = { loadedModelId };
        network_send_spawn_objects(spawn_objects, models, 1);
    }

    return obj;
}

struct Object* spawn_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z, LuaFunction objSetupFunction) {
    spawn_object_internal(behaviorId, modelId, x, y, z, objSetupFunction, true);
}

// this is too dangerous for now
struct Object* spawn_non_sync_object(enum BehaviorId behaviorId, enum ModelExtendedId modelId, f32 x, f32 y, f32 z) {
    spawn_object_internal(behaviorId, modelId, x, y, z, 0, false);
}

s32 obj_has_behavior_id(struct Object *o, enum BehaviorId behaviorId) {
    const BehaviorScript *behavior = get_behavior_from_id(behaviorId);
    return o->behavior == behavior;
}

s32 obj_has_model_extended(struct Object *o, enum ModelExtendedId modelId) {
    struct GraphNode *model = gLoadedGraphNodes[smlua_model_util_load(modelId)];
    return o->header.gfx.sharedChild == model;
}

void obj_set_model_extended(struct Object *o, enum ModelExtendedId modelId) {
    o->header.gfx.sharedChild = gLoadedGraphNodes[smlua_model_util_load(modelId)];
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
