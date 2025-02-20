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

// ----- header ----- //

static void packet_write_object_header(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    u32 behaviorId = get_id_from_behavior(o->behavior);

    packet_write(p, &gNetworkPlayerLocal->globalIndex, sizeof(u8));
    packet_write(p, &o->oSyncID, sizeof(u32));
    packet_write(p, &so->txEventId, sizeof(u16));
    packet_write(p, &so->randomSeed, sizeof(u16));
    packet_write(p, &behaviorId, sizeof(u32));
}

static bool allowable_behavior_change(struct SyncObject* so, BehaviorScript* behavior) {
    struct Object* o = so->o;

    // bhvPenguinBaby can be set to bhvSmallPenguin
    bool oBehaviorPenguin = (o->behavior == segmented_to_virtual(smlua_override_behavior(bhvPenguinBaby)) || o->behavior == segmented_to_virtual(smlua_override_behavior(bhvSmallPenguin)));
    bool inBehaviorPenguin = (behavior == segmented_to_virtual(smlua_override_behavior(bhvPenguinBaby)) || behavior == segmented_to_virtual(smlua_override_behavior(bhvSmallPenguin)));
    bool allow = (oBehaviorPenguin && inBehaviorPenguin);

    if (!allow) { return false; }

    so->behavior = behavior;
    so->o->behavior = behavior;
    return true;
}

static struct SyncObject* packet_read_object_header(struct Packet* p, u8* fromLocalIndex) {
    // figure out where the packet came from
    u8 fromGlobalIndex = 0;
    packet_read(p, &fromGlobalIndex, sizeof(u8));
    struct NetworkPlayer* np = network_player_from_global_index(fromGlobalIndex);
    *fromLocalIndex = (np != NULL) ? np->localIndex : p->localIndex;

    // get sync ID, sanity check
    u32 syncId = 0;
    packet_read(p, &syncId, sizeof(u32));
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) {
        LOG_ERROR("invalid SyncID: %d", syncId);
        return NULL;
    }

    // extract object, sanity check
    struct Object* o = so->o;
    if (o == NULL) {
        LOG_ERROR("invalid SyncObject for %d", syncId);
        return NULL;
    }

    // retrieve SyncObject, check if we should update using callback
    extern struct Object* gCurrentObject;
    struct Object* tmp = gCurrentObject;
    gCurrentObject = o;
    if ((so->ignore_if_true != NULL) && ((*so->ignore_if_true)() != FALSE)) {
        gCurrentObject = tmp;
        LOG_INFO("ignored sync object due to callback");
        return NULL;
    }
    gCurrentObject = tmp;
    so->clockSinceUpdate = clock_elapsed();

    // make sure this is the newest event possible
    u16 eventId = 0;
    packet_read(p, &eventId, sizeof(u16));
    if (so->rxEventId[*fromLocalIndex] > eventId && (u16)abs(eventId - so->rxEventId[*fromLocalIndex]) < USHRT_MAX / 2) {
        LOG_INFO("ignored sync object due to eventId");
        return NULL;
    }
    so->rxEventId[*fromLocalIndex] = eventId;

    // update the random seed
    packet_read(p, &so->randomSeed, sizeof(u16));

    // make sure the behaviors match
    u32 behaviorId;
    packet_read(p, &behaviorId, sizeof(u32));

    BehaviorScript* behavior = (BehaviorScript*)get_behavior_from_id(behaviorId);
    BehaviorScript* lBehavior = (BehaviorScript*)smlua_override_behavior(behavior);
    if (behavior == NULL) {
        LOG_ERROR("unable to find behavior %04X for id %d", behaviorId, syncId);
        return NULL;
    } if (o->behavior != behavior && o->behavior != lBehavior && !allowable_behavior_change(so, behavior)) {
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", syncId, get_id_from_behavior(o->behavior), get_id_from_behavior(behavior));
        return NULL;
    }

    return so;
}

// ----- full sync ----- //

static void packet_write_object_full_sync(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->fullObjectSync) { return; }

    // write all of raw data
    packet_write(p, o->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
}

static void packet_read_object_full_sync(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so || !so->fullObjectSync) { return; }

    // read all of raw data
    packet_read(p, o->rawData.asU32, sizeof(u32) * OBJECT_NUM_FIELDS);
}

// ----- standard fields ----- //

static void packet_write_object_standard_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->fullObjectSync) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS) { return; }
    if (!so->hasStandardFields) { return; }

    // write the standard fields
    packet_write(p, &o->oPosX, sizeof(u32) * 7);
    packet_write(p, &o->oAction, sizeof(u32));
    packet_write(p, &o->oPrevAction, sizeof(u32));
    packet_write(p, &o->oSubAction, sizeof(u32));
    packet_write(p, &o->oInteractStatus, sizeof(u32));
    packet_write(p, &o->oHeldState, sizeof(u32));
    packet_write(p, &o->oMoveAngleYaw, sizeof(u32));
    packet_write(p, &o->oTimer, sizeof(u32));
    packet_write(p, &o->activeFlags, sizeof(s16));
    packet_write(p, &o->header.gfx.node.flags, sizeof(s16));
    packet_write(p, &o->oIntangibleTimer, sizeof(s32));
}

static void packet_read_object_standard_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->fullObjectSync) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS) { return; }
    if (!so->hasStandardFields) { return; }

    // read the standard fields
    packet_read(p, &o->oPosX, sizeof(u32) * 7);
    packet_read(p, &o->oAction, sizeof(u32));
    packet_read(p, &o->oPrevAction, sizeof(u32));
    packet_read(p, &o->oSubAction, sizeof(u32));
    packet_read(p, &o->oInteractStatus, sizeof(u32));
    packet_read(p, &o->oHeldState, sizeof(u32));
    packet_read(p, &o->oMoveAngleYaw, sizeof(u32));
    packet_read(p, &o->oTimer, sizeof(u32));
    packet_read(p, &o->activeFlags, sizeof(u16));
    packet_read(p, &o->header.gfx.node.flags, sizeof(s16));
    packet_read(p, &o->oIntangibleTimer, sizeof(s32));
}

// ----- extra fields ----- //

static void packet_write_object_extra_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // write the count
    packet_write(p, &so->extraFieldCount, sizeof(u8));

    // write the extra field
    for (u8 i = 0; i < so->extraFieldCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        packet_write(p, so->extraFields[i], so->extraFieldsSize[i] / 8);
    }
}

static void packet_read_object_extra_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // read the count and sanity check
    u8 extraFieldsCount = 0;
    packet_read(p, &extraFieldsCount, sizeof(u8));
    if (extraFieldsCount != so->extraFieldCount) {
        LOG_ERROR("mismatching extra fields count");
        return;
    }

    // read the extra fields
    for (u8 i = 0; i < extraFieldsCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        packet_read(p, so->extraFields[i], so->extraFieldsSize[i] / 8);
    }
}

// ----- only death ----- //

static void packet_write_object_only_death(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }
    packet_write(p, &o->activeFlags, sizeof(s16));
}

static void packet_read_object_only_death(struct Packet* p, struct Object* o) {
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }
    s16 activeFlags;
    packet_read(p, &activeFlags, sizeof(u16));
    if (activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        // flag the object as dead, the behavior is responsible for clean up
        so->o->oSyncDeath = 1;
        sync_object_forget(so->id);
    }
}

// ----- main send/receive ----- //

void network_send_object(struct Object* o) {
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
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", o->oSyncID, get_id_from_behavior(o->behavior), get_id_from_behavior(so->behavior));
        sync_object_forget(so->id);
        return;
    }

    bool reliable = (o->activeFlags == ACTIVE_FLAG_DEACTIVATED || so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS);
    network_send_object_reliability(o, reliable);
}

void network_send_object_reliability(struct Object* o, bool reliable) {
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
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", syncId, get_id_from_behavior(o->behavior), get_id_from_behavior(so->behavior));
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
    network_send(&p);

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
    // prevent receiving objects during credits sequence
    if (gCurrActStarNum == 99) { return; }

    // delay any objects received while we're loading the area
    if (!gNetworkAreaLoaded) {
        network_delayed_packet_object_remember(p);
        return;
    }

    // read the header and sanity check the packet
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

    // make sure no one can update an object we're holding
    if (gMarioStates[0].heldObj == o) { return; }

    // save old pos for platform displacement
    Vec3f oldPos = { 0 };
    oldPos[0] = o->oPosX;
    oldPos[1] = o->oPosY;
    oldPos[2] = o->oPosZ;

    // trigger on-received callback
    if (so->on_received_pre != NULL && so->o != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        (*so->on_received_pre)(fromLocalIndex);
        gCurrentObject = tmp;
    }

    // read the rest of the packet data
    packet_read_object_full_sync(p, o);
    packet_read_object_standard_fields(p, o);
    packet_read_object_extra_fields(p, o);
    packet_read_object_only_death(p, o);

    // deactivated
    if (o->activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        o->oSyncDeath = 1; // Force oSyncDeath if deactivated
        sync_object_forget(so->id);
    } else if (p->reliable) {
        // remember packet
        packet_duplicate(p, &so->lastReliablePacket);
    }

    // trigger on-received callback
    if (so->on_received_post != NULL && so->o != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        (*so->on_received_post)(fromLocalIndex);
        gCurrentObject = tmp;
    }

    // apply platform displacement
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
            if (so->o->activeFlags != ACTIVE_FLAG_DEACTIVATED) { // check if object was just deleted
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
