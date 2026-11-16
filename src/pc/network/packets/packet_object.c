#include <stdio.h>
#include <limits.h>
#include "../network.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_data.h"
#include "behavior_table.h"
#include "game/memory.h"
#include "game/object_helpers.h"
#include "game/obj_behaviors.h"
#include "game/object_list_processor.h"
#include "game/area.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

struct DelayedPacketObject {
    struct Packet p;
    struct DelayedPacketObject* next;
};

struct DelayedPacketObject* delayedPacketObjectHead = NULL;
struct DelayedPacketObject* delayedPacketObjectTail = NULL;

void network_delayed_packet_object_remember(struct Packet* p) {
    struct DelayedPacketObject* node = calloc(1, sizeof(struct DelayedPacketObject));
    packet_duplicate(p, &node->p);
    node->next = NULL;
    LOG_INFO("saving delayed object");

    if (delayedPacketObjectHead == NULL) {
        delayedPacketObjectHead = node;
        delayedPacketObjectTail = node;
    } else {
        delayedPacketObjectTail->next = node;
        delayedPacketObjectTail = node;
    }
}

void network_delayed_packet_object_execute(void) {
    struct DelayedPacketObject* node = delayedPacketObjectHead;
    while (node != NULL) {
        struct DelayedPacketObject* next = node->next;
        LOG_INFO("executing delayed object");
        network_receive_object(&node->p);
        free(node);
        node = next;
    }
    delayedPacketObjectHead = NULL;
    delayedPacketObjectTail = NULL;
}

// ----- Header ----- //

static void packet_write_object_header(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    
    u32 behaviorId = get_id_from_behavior(o->behavior);
    
    packet_write_uint8(p, gNetworkPlayerLocal->globalIndex);
    packet_write_uint32(p, o->oSyncID);
    packet_write_uint16(p, so->txEventId);
    packet_write_uint16(p, so->randomSeed);
    packet_write_uint32(p, behaviorId);
}

static bool allowable_behavior_change(struct SyncObject* so, BehaviorScript* behavior) {
    struct Object* o = so->o;

    // bhvPenguinBaby can be set to bhvSmallPenguin
    bool oBehaviorPenguin = (o->behavior == smlua_override_behavior(bhvPenguinBaby) || o->behavior == smlua_override_behavior(bhvSmallPenguin));
    bool inBehaviorPenguin = (behavior == smlua_override_behavior(bhvPenguinBaby) || behavior == smlua_override_behavior(bhvSmallPenguin));

    // bhvCoinFormationSpawn can be set to bhvYellowCoin
    bool oBehaviorCoin = (o->behavior == smlua_override_behavior(bhvCoinFormationSpawn) || o->behavior == smlua_override_behavior(bhvYellowCoin));
    bool inBehaviorCoin = (behavior == smlua_override_behavior(bhvCoinFormationSpawn) || behavior == smlua_override_behavior(bhvYellowCoin));

    bool allow = (oBehaviorPenguin && inBehaviorPenguin) || (oBehaviorCoin && inBehaviorCoin);
    if (!allow) { return false; }

    so->behavior = behavior;
    so->o->behavior = behavior;
    return true;
}

static struct SyncObject* packet_read_object_header(struct Packet* p, u8* fromLocalIndex) {
    if (p == NULL || fromLocalIndex == NULL) { return NULL; }
  
    // Figure out where the packet came from
    u8 fromGlobalIndex = packet_read_uint8(p);
    struct NetworkPlayer* np = network_player_from_global_index(fromGlobalIndex);
    *fromLocalIndex = (np != NULL) ? np->localIndex : p->localIndex;

    // Get sync ID, sanity check
    u32 syncId = packet_read_uint32(p);
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) {
        LOG_ERROR("Invalid SyncID: %d", syncId);
        return NULL;
    }

    // Extract object, Sanity check
    struct Object* o = so->o;
    if (o == NULL) {
        LOG_ERROR("Invalid SyncObject for %d", syncId);
        return NULL;
    }

    // Retrieve SyncObject, Check if we should update using callback
    extern struct Object* gCurrentObject;
    struct Object* tmp = gCurrentObject;
    gCurrentObject = o;
    if ((so->ignore_if_true != NULL) && ((*so->ignore_if_true)() != FALSE)) {
        gCurrentObject = tmp;
        LOG_INFO("Ignored sync object due to callback");
        return NULL;
    }
    gCurrentObject = tmp;
    so->clockSinceUpdate = clock_elapsed();

    // Make sure this is the newest event possible
    u16 eventId = packet_read_uint16(p);
    if (so->rxEventId[*fromLocalIndex] > eventId && (u16)abs(eventId - so->rxEventId[*fromLocalIndex]) < USHRT_MAX / 2) {
        LOG_INFO("Ignored sync object due to eventId");
        return NULL;
    }
    so->rxEventId[*fromLocalIndex] = eventId;

    // Update the random seed
    so->randomSeed = packet_read_uint16(p);

    // Make sure the behaviors match
    u32 behaviorId = packet_read_uint32(p);

    BehaviorScript* behavior = (BehaviorScript*)get_behavior_from_id(behaviorId);
    BehaviorScript* lBehavior = (BehaviorScript*)smlua_override_behavior(behavior);
    if (behavior == NULL) {
        LOG_ERROR("Unable to find behavior %04X for id %d", behaviorId, syncId);
        return NULL;
    }
    if (o->behavior != behavior && o->behavior != lBehavior && !allowable_behavior_change(so, behavior)) {
        enum BehaviorId objBehaviorId = get_id_from_behavior(o->behavior);
        enum BehaviorId inBehaviorId = get_id_from_behavior(behavior);
        LOG_ERROR(
            "During read behavior mismatch for %d: %04X (%s) vs %04X (%s)", syncId,
            objBehaviorId, get_behavior_name_from_id(objBehaviorId),
            inBehaviorId,  get_behavior_name_from_id(inBehaviorId)
        );
        return NULL;
    }

    return so;
}

// ----- Full Sync ----- //

static void packet_write_object_full_sync(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->fullObjectSync) { return; }

    // Write all of raw data
    packet_write(p, o->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
}

static void packet_read_object_full_sync(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u32) * OBJECT_NUM_FIELDS);
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->fullObjectSync) { return; }

    // Read all of raw data
    packet_read(p, o->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
}

// ----- Standard Fields ----- //

static void packet_write_object_standard_fields(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->hasStandardFields || so->fullObjectSync) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS) { return; }

    // Write the standard fields
    packet_write_float32(p, o->oPosX);
    packet_write_float32(p, o->oPosY);
    packet_write_float32(p, o->oPosZ);
    packet_write_float32(p, o->oVelX);
    packet_write_float32(p, o->oVelY);
    packet_write_float32(p, o->oVelZ);
    packet_write_float32(p, o->oForwardVel);
    packet_write_uint32(p, o->oAction);
    packet_write_uint32(p, o->oPrevAction);
    packet_write_uint32(p, o->oSubAction);
    packet_write_uint32(p, o->oInteractStatus);
    packet_write_uint32(p, o->oHeldState);
    packet_write_uint32(p, o->oMoveAngleYaw);
    packet_write_uint32(p, o->oTimer);
    packet_write_uint16(p, o->activeFlags);
    packet_write_int16(p, o->header.gfx.node.flags);
    packet_write_int32(p, o->oIntangibleTimer);
}

static void packet_read_object_standard_fields(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u16) + sizeof(s16) + sizeof(s32) + (sizeof(u32) * 7) * (sizeof(f32) * 7));
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->hasStandardFields || so->fullObjectSync) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS) { return; }

    // Read the standard fields
    o->oPosX = packet_read_float32(p);
    o->oPosY = packet_read_float32(p);
    o->oPosZ = packet_read_float32(p);
    o->oVelX = packet_read_float32(p);
    o->oVelY = packet_read_float32(p);
    o->oVelZ = packet_read_float32(p);
    o->oForwardVel = packet_read_float32(p);
    o->oAction = packet_read_uint32(p);
    o->oPrevAction = packet_read_uint32(p);
    o->oSubAction = packet_read_uint32(p);
    o->oInteractStatus = packet_read_uint32(p);
    o->oHeldState = packet_read_uint32(p);
    o->oMoveAngleYaw = packet_read_uint32(p);
    o->oTimer = packet_read_uint32(p);
    o->activeFlags = packet_read_uint16(p);
    o->header.gfx.node.flags = packet_read_int16(p);
    o->oIntangibleTimer = packet_read_int32(p);
}

// ----- Extra Fields ----- //

static void packet_write_object_extra_fields(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // Write the count
    packet_write_uint8(p, so->extraFieldCount);

    // Write the extra field
    for (u8 i = 0; i < so->extraFieldCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        packet_write(p, so->extraFields[i], so->extraFieldsSizeBytes[i]);
    }
}

static void packet_read_object_extra_fields(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8));
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // Read the count and sanity check
    u8 extraFieldsCount = packet_read_uint8(p);
    if (extraFieldsCount != so->extraFieldCount) {
        LOG_ERROR("mismatching extra fields count");
        return;
    }

    // Read the extra fields
    for (u8 i = 0; i < extraFieldsCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        SOFT_ASSERT(packet_get_remaining_size(p) >= so->extraFieldsSizeBytes[i]);
        packet_read(p, so->extraFields[i], so->extraFieldsSizeBytes[i]);
    }
}

// ----- Only Death ----- //

static void packet_write_object_only_death(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }

    packet_write_int16(p, o->activeFlags);
}

static void packet_read_object_only_death(struct Packet* p, struct Object* o) {
    if (p == NULL || o == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(s16));
    
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }
    
    s16 activeFlags = packet_read_int16(p);
    if (activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        // Flag the object as dead, The behavior of the object is responsible for clean up
        so->o->oSyncDeath = 1;
        sync_object_forget(so->id);
    }
}

// ----- Main Send/Receive ----- //

void network_send_object(struct Object* o) {
    network_send_object_to(PACKET_DESTINATION_BROADCAST, o);
}

void network_send_object_to(u8 sendToLocalIndex, struct Object* o) {
    if (gNetworkType == NT_NONE || gNetworkPlayerLocal == NULL) { return; }

    // sanity check SyncObject
    if (!sync_object_is_initialized(o->oSyncID)) {
        //LOG_ERROR("tried to send uninitialized sync obj");
        return;
    }
    if (o->behavior == smlua_override_behavior(bhvRespawner)) {
        LOG_INFO("tried to send respawner sync obj");
        return;
    }

    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (so == NULL) { LOG_ERROR("tried to send null sync obj"); return; }
    if (o != so->o) {
        LOG_ERROR("object mismatch for %d", o->oSyncID);
        return;
    }
    if (o->behavior != so->behavior && !allowable_behavior_change(so, so->behavior)) {
        enum BehaviorId objBehaviorId = get_id_from_behavior(o->behavior);
        enum BehaviorId soBehaviorId = get_id_from_behavior(so->behavior);
        LOG_ERROR(
            "during send behavior mismatch for %d: %04X (%s) vs %04X (%s)", o->oSyncID,
            objBehaviorId, get_behavior_name_from_id(objBehaviorId),
            soBehaviorId,  get_behavior_name_from_id(soBehaviorId)
        );
        sync_object_forget(so->id);
        return;
    }

    bool reliable = (o->activeFlags == ACTIVE_FLAG_DEACTIVATED || so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS);
    network_send_object_reliability_to(sendToLocalIndex, o, reliable);
}

void network_send_object_reliability(struct Object* o, bool reliable) {
    network_send_object_reliability_to(PACKET_DESTINATION_BROADCAST, o, reliable);
}

void network_send_object_reliability_to(u8 sendToLocalIndex, struct Object* o, bool reliable) {
    // don't send sync objects while area sync is invalid
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) {
        return;
    }
    // prevent sending objects during credits sequence
    if (gCurrActStarNum == 99) { return; }

    // sanity check SyncObject
    if (!sync_object_is_initialized(o->oSyncID)) {
        //LOG_ERROR("tried to send uninitialized sync obj");
        return;
    }

    u32 syncId = o->oSyncID;
    struct SyncObject* so = sync_object_get(syncId);
    if (so == NULL) {
        LOG_ERROR("tried to send null sync obj");
        return;
    }
    if (o != so->o) {
        LOG_ERROR("object mismatch for %d", syncId);
        return;
    }
    if (o->behavior != so->behavior && !allowable_behavior_change(so, so->behavior)) {
        enum BehaviorId objBehaviorId = get_id_from_behavior(o->behavior);
        enum BehaviorId soBehaviorId = get_id_from_behavior(so->behavior);
        LOG_ERROR(
            "during send reliability behavior mismatch for %d: %04X (%s) vs %04X (%s)", syncId,
            objBehaviorId, get_behavior_name_from_id(objBehaviorId),
            soBehaviorId,  get_behavior_name_from_id(soBehaviorId)
        );
        sync_object_forget(so->id);
        return;
    }

    // trigger on_sent_pre callback
    if (so->on_sent_pre != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        so->on_sent_pre();
        gCurrentObject = tmp;
    }

    // always send a new event ID
    so->txEventId++;
    so->clockSinceUpdate = clock_elapsed();

    // write the packet data
    struct Packet p = { 0 };
    packet_init(&p, PACKET_OBJECT, reliable, PLMT_AREA);
    packet_write_object_header(&p, o);
    packet_write_object_full_sync(&p, o);
    packet_write_object_standard_fields(&p, o);
    packet_write_object_extra_fields(&p, o);
    packet_write_object_only_death(&p, o);

    // check for object death
    if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        sync_object_forget(so->id);
    } else if (so->rememberLastReliablePacket) {
        // remember packet
        packet_duplicate(&p, &so->lastReliablePacket);
    }

    // send the packet out
    if (sendToLocalIndex == PACKET_DESTINATION_BROADCAST) {
        network_send(&p);
    } else {
        network_send_to(sendToLocalIndex, &p);
    }
    packet_clear(&p);

    // trigger on_sent_post callback
    if (so->on_sent_post != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        so->on_sent_post();
        gCurrentObject = tmp;
    }
}

void network_receive_object(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Prevent receiving objects during credits sequence
    if (gCurrActStarNum == 99) { return; }

    // Delay any objects received while we're loading the area
    if (!gNetworkAreaLoaded) {
        network_delayed_packet_object_remember(p);
        return;
    }

    // Read the header and sanity check the packet
    u8 fromLocalIndex = 0;
    struct SyncObject* so = packet_read_object_header(p, &fromLocalIndex);
    if (so == NULL) {
        LOG_ERROR("received null sync object");
        return;
    }
    struct Object* o = so->o;
    if (!sync_object_is_initialized(o->oSyncID)) {
        LOG_ERROR("received uninitialized sync object");
        return;
    }

    // Make sure no one can update an object we're holding
    if (gMarioStates[0].heldObj == o) { return; }

    // Save old pos for platform displacement
    Vec3f oldPos = { 0 };
    oldPos[0] = o->oPosX;
    oldPos[1] = o->oPosY;
    oldPos[2] = o->oPosZ;

    // Trigger on-received callback
    if (so->on_received_pre != NULL && so->o != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        (*so->on_received_pre)(fromLocalIndex);
        gCurrentObject = tmp;
    }

    // Read the rest of the packet data
    packet_read_object_full_sync(p, o);
    packet_read_object_standard_fields(p, o);
    packet_read_object_extra_fields(p, o);
    packet_read_object_only_death(p, o);

    // Deactivated
    if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        o->oSyncDeath = 1; // Force oSyncDeath if deactivated
        sync_object_forget(so->id);
    } else if (p->reliable) {
        // Remember packet
        packet_duplicate(p, &so->lastReliablePacket);
    }

    // Trigger on-received callback
    if (so->on_received_post != NULL && so->o != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        (*so->on_received_post)(fromLocalIndex);
        gCurrentObject = tmp;
    }

    // Apply platform displacement
    if (o != NULL && o->collisionData) {
        Vec3f deltaPos = { 0 };
        deltaPos[0] = o->oPosX - oldPos[0];
        deltaPos[2] = o->oPosY - oldPos[1];
        deltaPos[1] = o->oPosZ - oldPos[2];
        for (s32 i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (!gMarioStates[i].marioObj || gMarioStates[i].marioObj->platform != o) { continue; }
            for (s32 j = 0; j < 3; j++) { gMarioStates[i].pos[j] += deltaPos[j]; }
        }
    }

}

void network_update_objects(void) {
    if (gNetworkAreaLoaded && delayedPacketObjectHead != NULL) {
        network_delayed_packet_object_execute();
    }

#ifdef DEVELOPMENT
    static f32 lastDebugSync = 0;
    if (clock_elapsed() - lastDebugSync >= 5) {
        network_send_debug_sync();
        lastDebugSync = clock_elapsed();
    }
#endif

    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        if (!so || !so->o) { continue; }

        // check for stale sync object
        if (so->o->oSyncID != so->id) {
            // check if object was deleted
            if (so->o->activeFlags != ACTIVE_FLAG_DEACTIVATED &&
                so->o->behavior == so->behavior // a new object may be in this slot
            ) {
                enum BehaviorId bhvId = get_id_from_behavior(so->o->behavior);
                const char* bhvName = get_behavior_name_from_id(bhvId);
                LOG_ERROR("sync id mismatch: %d vs %d (behavior %s, %d)", so->o->oSyncID, so->id, bhvName != NULL ? bhvName : "NULL", bhvId);
            }
            sync_object_forget(so->id);
            continue;
        }

        // check if we should be the one syncing this object
        so->owned = sync_object_should_own(so->id);
        if (!so->owned) { continue; }

        // check for 'only death' event
        if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) {
            if (so->o->activeFlags != ACTIVE_FLAG_DEACTIVATED) { continue; }
            network_send_object(so->o);
            continue;
        }

        // calculate the update rate
        float dist = player_distance(&gMarioStates[0], so->o);
        if (so->maxSyncDistance != SYNC_DISTANCE_INFINITE && dist > so->maxSyncDistance) { continue; }
        float updateRate = dist / 1000.0f;
        if (gMarioStates[0].heldObj == so->o) { updateRate = 0.33f; }

        // set max and min update rate
        if (so->maxUpdateRate > 0 && updateRate < so->maxUpdateRate) { updateRate = so->maxUpdateRate; }
        if (updateRate < so->minUpdateRate) { updateRate = so->minUpdateRate; }

        // see if we should update
        float timeSinceUpdate = (clock_elapsed() - so->clockSinceUpdate);
        if (timeSinceUpdate < updateRate) { continue; }

        // update!
        bool inCredits = (gCurrActStarNum == 99);
        if (network_player_any_connected() && !inCredits) {
            network_send_object(so->o);
        }
    }

}
