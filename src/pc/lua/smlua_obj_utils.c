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