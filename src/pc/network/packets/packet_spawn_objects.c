#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "game/object_helpers.h"
#include "game/area.h"
#include "behavior_data.h"
#include "behavior_table.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_model_utils.h"
#include "pc/lua/utils/smlua_obj_utils.h"
#include "pc/crash_handler.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

#define MAX_SPAWN_OBJECTS_PER_PACKET 8

#pragma pack(1)
struct SpawnObjectData {
    u8 ctx;
    u32 parentId;
    u32 model;
    u32 behaviorId;
    s16 activeFlags;
    s32 rawData[OBJECT_NUM_FIELDS];
    u8 setHome;
    u8 globalPlayerIndex;
    u16 extendedModelId;
    u8 extraFieldCount;
};
#pragma pack()

static u32 generate_parent_id(struct Object* objects[], u8 onIndex, bool sanitize) {
    struct Object* o = objects[onIndex];
    if (!o) { return (u32)-1; }

    // special case if the parent is itself
    if (o->parentObj == o) { return (u32)-1; }

    if (onIndex == 0) {
        if (!o->parentObj) {
            return (u32)-1;
        }
        if (sanitize && o->parentObj->oSyncID == 0) {
            return (u32)-1;
        }
        SOFT_ASSERT_RETURN(o->parentObj->oSyncID != 0, (u32)-1);
        return (u32)o->parentObj->oSyncID;
    }

    for (u8 i = onIndex; i != (u8)-1; i--) {
        if (o->parentObj == objects[i]) { return i; }
    }

    SOFT_ASSERT_RETURN(false, (u32)-1);
}

void network_send_spawn_objects(struct Object* objects[], u32 models[], u8 objectCount) {
    network_send_spawn_objects_to(PACKET_DESTINATION_BROADCAST, objects, models, objectCount);
}

void network_send_spawn_objects_to(u8 sendToLocalIndex, struct Object* objects[], u32 models[], u8 objectCount) {
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) {
        LOG_ERROR("failed: area sync invalid");
        return;
    }

    if (objectCount == 0) {
        LOG_ERROR("Tried to send 0 objects");
        return;
    }

    SOFT_ASSERT(objectCount < MAX_SPAWN_OBJECTS_PER_PACKET);
    // prevent sending spawn objects during credits
    if (gCurrActStarNum == 99) {
        LOG_ERROR("failed: in credits");
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_SPAWN_OBJECTS, true, PLMT_AREA);

    // objects
    packet_write(&p, &objectCount, sizeof(u8));

    for (u8 i = 0; i < objectCount; i++) {
        struct Object* o = objects[i];
        if (!o || !o->ctx) {
            LOG_ERROR("Tried to send null object");
            return;
        }

        u32 model = models[i];
        u32 parentId = generate_parent_id(objects, i, true);
        u32 behaviorId = get_id_from_behavior(o->behavior);
        struct SyncObject* so = sync_object_get(o->oSyncID);
        u16 extendedModelId = (so && so->o == o)
                            ? so->extendedModelId
                            : 0xFFFF;
        packet_write(&p, &o->ctx, sizeof(u8));
        packet_write(&p, &parentId, sizeof(u32));
        packet_write(&p, &model, sizeof(u32));
        packet_write(&p, &behaviorId, sizeof(u32));
        packet_write(&p, &o->activeFlags, sizeof(s16));
        packet_write(&p, o->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
        packet_write(&p, &o->header.gfx.scale[0], sizeof(f32));
        packet_write(&p, &o->header.gfx.scale[1], sizeof(f32));
        packet_write(&p, &o->header.gfx.scale[2], sizeof(f32));
        packet_write(&p, &o->setHome, sizeof(u8));
        packet_write(&p, &o->globalPlayerIndex, sizeof(u8));
        packet_write(&p, &extendedModelId, sizeof(u16));
    }

    if (sendToLocalIndex == PACKET_DESTINATION_BROADCAST) {
        network_send(&p);
        if (objects[0] && objects[0]->behavior) {
            LOG_INFO("tx spawn objects (BROADCAST) | %u", get_id_from_behavior(objects[0]->behavior));
        }
    } else {
        network_send_to(sendToLocalIndex, &p);
        if (objects[0] && objects[0]->behavior) {
            LOG_INFO("tx spawn objects to %d | %u", gNetworkPlayers[sendToLocalIndex].globalIndex, get_id_from_behavior(objects[0]->behavior));
        }
    }
}

void network_receive_spawn_objects(struct Packet* p) {
    // prevent receiving spawn objects during credits
    if (gCurrActStarNum == 99) {
        LOG_ERROR("rx failed: in credits");
        return;
    }

    u8 objectCount = 0;
    packet_read(p, &objectCount, sizeof(u8));

    struct Object* spawned[MAX_SPAWN_OBJECTS_PER_PACKET] = { 0 };
    for (u8 i = 0; i < objectCount; i++) {
        struct SpawnObjectData data = { 0 };
        Vec3f scale = { 0 };
        u8 ctx = 0;
        packet_read(p, &ctx, sizeof(u8));
        packet_read(p, &data.parentId, sizeof(u32));
        packet_read(p, &data.model, sizeof(u32));
        packet_read(p, &data.behaviorId, sizeof(u32));
        packet_read(p, &data.activeFlags, sizeof(s16));
        packet_read(p, &data.rawData, sizeof(u32) * OBJECT_NUM_FIELDS);
        packet_read(p, &scale[0], sizeof(f32));
        packet_read(p, &scale[1], sizeof(f32));
        packet_read(p, &scale[2], sizeof(f32));
        packet_read(p, &data.setHome, sizeof(u8));
        packet_read(p, &data.globalPlayerIndex, sizeof(u8));
        packet_read(p, &data.extendedModelId, sizeof(u16));

        char* id = "unknown";
        char* name = "unknown";
        if (gNetworkSystem && p->localIndex) {
            id = gNetworkSystem->get_id_str(p->localIndex);
            name = gNetworkPlayers[p->localIndex].name;
        }

        const char *bhvName = get_behavior_name_from_id(data.behaviorId);

        // Don't overwrite existing sync objects
        {
            u32 syncID = data.rawData[0x04]; // o->oSyncID
            struct SyncObject *so = sync_object_get(syncID);
            if (so && so->o) {
                if (so->o->behavior == get_behavior_from_id(data.behaviorId)) {
                    LOG_ERROR("recieved duplicate sync object with id %d from %s (%s)", syncID, name, id);
                } else {
                    LOG_ERROR("recieved duplicate sync object with id %d with different behavior %s from %s (%s)", syncID, bhvName, name, id);
                }
                continue;
            }
        }

        LOG_INFO("rx spawn object %s from %s (%s)", bhvName, name, id);
        LOG_CONSOLE("rx spawn object %s from %s\\#dcdcdc\\ (%s)", bhvName, name, id);
        snprintf(gLastRemoteBhv, 256, "%s %s (%s)", bhvName, name, id);

        struct Object* parentObj = NULL;
        if (data.parentId == (u32)-1) {
            // this object is it's own parent, set it to a known object temporarily
            parentObj = gMarioStates[0].marioObj;
        } else {

            // this object has a known parent
            struct SyncObject* parentSo = sync_object_get(data.parentId);
            if (i == 0 && !parentSo) {
                LOG_ERROR("Invalid spawn object parentId: %u", data.parentId);
                return;
            }

            parentObj = (i == 0)
                      ? parentSo->o
                      : spawned[data.parentId];

            if (parentObj == NULL) {
                // failed to find parent, make it it's own parent
                // may cause issues, but we want it to spawn!
                LOG_ERROR("ERROR: failed to find spawn object's parent (%d)!", data.parentId);
                parentObj = gMarioStates[0].marioObj;
                data.parentId = (u32)-1;
            }
        }

        if (parentObj == NULL) {
            LOG_ERROR("ERROR: failed to attach to mario!");
            return;
        }

        // load extended model
        if (data.extendedModelId != 0xFFFF) {
            u16 loadedModelId = smlua_model_util_load(data.extendedModelId);
            data.model = loadedModelId;
        }

        void* behavior = (void*)get_behavior_from_id(data.behaviorId);
        struct Object* o = NULL;
        if (ctx) { o = spawn_object(parentObj, data.model, behavior); }
        if (o == NULL) {
            LOG_ERROR("ERROR: failed to allocate object!");
            return;
        }

        o->ctx = ctx;
        o->globalPlayerIndex = data.globalPlayerIndex;
        o->coopFlags |= COOP_OBJ_FLAG_NETWORK;
        o->setHome = data.setHome;

        memcpy(o->rawData.asU32, data.rawData, sizeof(u32) * OBJECT_NUM_FIELDS);

        o->header.gfx.scale[0] = scale[0];
        o->header.gfx.scale[1] = scale[1];
        o->header.gfx.scale[2] = scale[2];

        // correct the temporary parent with the object itself
        if (data.parentId == (u32)-1) { o->parentObj = o; }

        if (o->oSyncID != 0) {
            // check if they've allocated one of their reserved sync objects
            struct SyncObject* so = sync_object_get(o->oSyncID);
            if (!so) {
                sync_object_set_id(o);
                so = sync_object_get(o->oSyncID);
            }
            if (so) {
                so->o = o;
                so->behavior = behavior;
                so->extendedModelId = data.extendedModelId;
                so->txEventId = 0;
                for (s32 j = 0; j < MAX_PLAYERS; j++) {
                    so->rxEventId[j] = 0;
                }
            } else {
                LOG_ERROR("Invalid spawn object sync id: %u", o->oSyncID);
                return;
            }
        }

        spawned[i] = o;
    }
}
