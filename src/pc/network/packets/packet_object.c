#include <stdio.h>
#include <limits.h>
#include "../network.h"
#include "../reservation_area.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_data.h"
#include "behavior_table.h"
#include "src/game/memory.h"
#include "src/game/object_helpers.h"
#include "src/game/obj_behaviors.h"
#include "src/game/object_list_processor.h"
#include "src/game/area.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

struct SyncObject gSyncObjects[MAX_SYNC_OBJECTS] = { 0 };
struct Packet sLastSyncEntReliablePacket[MAX_SYNC_OBJECTS] = { 0 };
u8 sNextSyncId = 0;

struct Packet* get_last_sync_ent_reliable_packet(u8 syncId) {
    return &sLastSyncEntReliablePacket[syncId];
}

void forget_ent_reliable_packet(struct Object* o) {
    u8 syncId = o->oSyncID;
    if (gSyncObjects[syncId].o == o) {
        sLastSyncEntReliablePacket[syncId].error = true;
    }
}

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

// todo: move this to somewhere more general
static float player_distance(struct MarioState* marioState, struct Object* o) {
    if (marioState->marioObj == NULL) { return 0; }
    f32 mx = marioState->marioObj->header.gfx.pos[0] - o->oPosX;
    f32 my = marioState->marioObj->header.gfx.pos[1] - o->oPosY;
    f32 mz = marioState->marioObj->header.gfx.pos[2] - o->oPosZ;
    mx *= mx;
    my *= my;
    mz *= mz;
    return sqrt(mx + my + mz);
}

static bool should_own_object(struct SyncObject* so) {
    // always own objects in credit sequence
    if (gCurrActStarNum == 99) { return true; }

    // check for override
    u8 shouldOverride = FALSE;
    u8 shouldOwn = FALSE;
    if (so->override_ownership != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        so->override_ownership(&shouldOverride, &shouldOwn);
        gCurrentObject = tmp;
        if (shouldOverride) { return shouldOwn; }
    }

    if (gMarioStates[0].heldByObj == so->o) { return true; }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (gMarioStates[i].heldByObj == so->o) { return false; }
    }
    if (so->o->oHeldState == HELD_HELD && so->o->heldByPlayerIndex == 0) { return true; }
    for (int i = 0; i < MAX_PLAYERS; i++) {
        if (i != 0 && !is_player_active(&gMarioStates[i])) { continue; }
        if (player_distance(&gMarioStates[0], so->o) > player_distance(&gMarioStates[i], so->o)) { return false; }
    }
    if (so->o->oHeldState == HELD_HELD && so->o->heldByPlayerIndex != 0) { return false; }
    return true;
}

void network_override_object(u8 syncId, struct Object* o) {
    gSyncObjects[syncId].o = o;
}

struct SyncObject* network_init_object(struct Object *o, float maxSyncDistance) {
    // generate new sync ID
    network_set_sync_id(o);

    // set default values for sync object
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    so->o = o;
    so->maxSyncDistance = maxSyncDistance;
    so->owned = false;
    so->clockSinceUpdate = clock_elapsed();
    so->extraFieldCount = 0;
    so->lastReliablePacketIsStale = false;
    so->rememberLastReliablePacket = true;
    so->behavior = (BehaviorScript*)o->behavior;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        so->rxEventId[i] = 0;
    }
    so->txEventId = 0;
    so->fullObjectSync = false;
    so->hasStandardFields = (maxSyncDistance >= 0);
    so->minUpdateRate = 0.33f;
    so->maxUpdateRate = 0.00f;
    so->ignore_if_true = NULL;
    so->on_received_pre = NULL;
    so->on_received_post = NULL;
    so->on_sent_pre = NULL;
    so->on_sent_post = NULL;
    so->override_ownership = NULL;
    so->on_forget = NULL;
    so->syncDeathEvent = true;
    so->randomSeed = (u16)(o->oSyncID * 7951);
    memset(so->extraFields, 0, sizeof(void*) * MAX_SYNC_OBJECT_FIELDS);

    sLastSyncEntReliablePacket[o->oSyncID].error = true;

    return so;
}

void network_init_object_field(struct Object *o, void* field) {
    SOFT_ASSERT(o->oSyncID != 0);
    // remember to synchronize this extra field
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    u8 index = so->extraFieldCount++;
    so->extraFields[index] = field;
}

bool network_owns_object(struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so == NULL) { return false; }

    // check for override
    u8 shouldOverride = FALSE;
    u8 shouldOwn = FALSE;
    if (so->override_ownership != NULL) {
        extern struct Object* gCurrentObject;
        struct Object* tmp = gCurrentObject;
        gCurrentObject = so->o;
        so->override_ownership(&shouldOverride, &shouldOwn);
        gCurrentObject = tmp;
        if (shouldOverride) { return shouldOwn; }
    }

    return so->owned;
}

bool network_sync_object_initialized(struct Object* o) {
    if (o->oSyncID == 0) { return false; }
    if (gSyncObjects[o->oSyncID].behavior == NULL) { return false; }
    return true;
}

void network_clear_sync_objects(void) {
    sNextSyncId = 0;
    network_on_init_area();
    for (u16 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        network_forget_sync_object(&gSyncObjects[i]);
    }
}

u8 network_find_cached_sync_id(struct Object* o) {
    u8 behaviorId = get_id_from_behavior(o->behavior);
    for (int i = 1; i < 256; i++) {
        if (gSyncObjects[i].o != NULL) { continue; }
        u8 cachedBehaviorId = gCurrentArea->cachedBehaviors[i];
        if (cachedBehaviorId != behaviorId) { continue; }

        f32 dist = dist_between_object_and_point(o, gCurrentArea->cachedPositions[i][0], gCurrentArea->cachedPositions[i][1], gCurrentArea->cachedPositions[i][2]);
        if (dist > 1) { continue; }
        //LOG_INFO("get cached sync id for %02X: %d", behaviorId, i);
        return i;
    }
    return 0;
}

void network_set_sync_id(struct Object* o) {
    if (o->oSyncID != 0) { return; }

    u8 syncId = 0;
    if (!gNetworkAreaLoaded) {
        syncId = network_find_cached_sync_id(o);
        if (syncId == 0) {
            // while loading, just fill in sync ids from 1 to MAX_SYNC_OBJECTS
            for (int i = 1; i < MAX_SYNC_OBJECTS; i++) {
                sNextSyncId++;
                sNextSyncId = sNextSyncId % RESERVED_IDS_SYNC_OBJECT_OFFSET;
                if (gSyncObjects[sNextSyncId].o != NULL) { continue; }
                syncId = sNextSyncId;
                break;
            }
            // cache this object's id
            gCurrentArea->cachedBehaviors[syncId] = get_id_from_behavior(o->behavior);
            gCurrentArea->cachedPositions[syncId][0] = o->oPosX;
            gCurrentArea->cachedPositions[syncId][1] = o->oPosY;
            gCurrentArea->cachedPositions[syncId][2] = o->oPosZ;
            //LOG_INFO("set cached sync id for %02X: %d", gCurrentArea->cachedBehaviors[syncId], syncId);
        }
    } else {
        // no longer loading, require reserved id
        syncId = reservation_area_local_grab_id();
    }

    SOFT_ASSERT(syncId != 0);
    SOFT_ASSERT(gSyncObjects[syncId].o == NULL);

    o->oSyncID = syncId;

    if (gNetworkAreaLoaded) {
        LOG_INFO("set sync id for object w/behavior %d", get_id_from_behavior(o->behavior));
    }

    SOFT_ASSERT(o->oSyncID < MAX_SYNC_OBJECTS);
}

// ----- header ----- //

static void packet_write_object_header(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    u16 behaviorId = get_id_from_behavior(o->behavior);

    packet_write(p, &gNetworkPlayerLocal->globalIndex, sizeof(u8));
    packet_write(p, &o->oSyncID, sizeof(u32));
    packet_write(p, &so->txEventId, sizeof(u16));
    packet_write(p, &so->randomSeed, sizeof(u16));
    packet_write(p, &behaviorId, sizeof(u16));
}

static bool allowable_behavior_change(struct SyncObject* so, BehaviorScript* behavior) {
    struct Object* o = so->o;

    // bhvPenguinBaby can be set to bhvSmallPenguin
    bool oBehaviorPenguin = (o->behavior == segmented_to_virtual(bhvPenguinBaby) || o->behavior == segmented_to_virtual(bhvSmallPenguin));
    bool inBehaviorPenguin = (behavior == segmented_to_virtual(bhvPenguinBaby) || behavior == segmented_to_virtual(bhvSmallPenguin));
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
    if (syncId == 0 || syncId >= MAX_SYNC_OBJECTS) {
        LOG_ERROR("invalid SyncID: %d", syncId);
        return NULL;
    }

    // extract object, sanity check
    struct Object* o = gSyncObjects[syncId].o;
    if (o == NULL) {
        LOG_ERROR("invalid SyncObject for %d", syncId);
        return NULL;
    }

    // retrieve SyncObject, check if we should update using callback
    struct SyncObject* so = &gSyncObjects[syncId];
    extern struct Object* gCurrentObject;
    struct Object* tmp = gCurrentObject;
    gCurrentObject = o;
    if ((so->ignore_if_true != NULL) && ((*so->ignore_if_true)() != FALSE)) {
        gCurrentObject = tmp;
        return NULL;
    }
    gCurrentObject = tmp;
    so->clockSinceUpdate = clock_elapsed();

    // make sure this is the newest event possible
    u16 eventId = 0;
    packet_read(p, &eventId, sizeof(u16));
    if (so->rxEventId[*fromLocalIndex] > eventId && (u16)abs(eventId - so->rxEventId[*fromLocalIndex]) < USHRT_MAX / 2) {
        return NULL;
    }
    so->rxEventId[*fromLocalIndex] = eventId;

    // update the random seed
    packet_read(p, &so->randomSeed, sizeof(u16));

    // make sure the behaviors match
    u16 behaviorId;
    packet_read(p, &behaviorId, sizeof(u16));

    BehaviorScript* behavior = (BehaviorScript*)get_behavior_from_id(behaviorId);
    if (behavior == NULL) {
        LOG_ERROR("unable to find behavior %04X for id %d", behaviorId, syncId);
        return NULL;
    } if (o->behavior != behavior && !allowable_behavior_change(so, behavior)) {
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", syncId, get_id_from_behavior(o->behavior), get_id_from_behavior(behavior));
        return NULL;
    }

    return so;
}

// ----- full sync ----- //

static void packet_write_object_full_sync(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (!so->fullObjectSync) { return; }

    // write all of raw data
    packet_write(p, o->rawData.asU32, sizeof(u32) * 80);
}

static void packet_read_object_full_sync(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (!so->fullObjectSync) { return; }

    // read all of raw data
    packet_read(p, o->rawData.asU32, sizeof(u32) * 80);
}

// ----- standard fields ----- //

static void packet_write_object_standard_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
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
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
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
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // write the count
    packet_write(p, &so->extraFieldCount, sizeof(u8));

    // write the extra field
    for (u8 i = 0; i < so->extraFieldCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        packet_write(p, so->extraFields[i], sizeof(u32));
    }
}

static void packet_read_object_extra_fields(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) { return; }

    // read the count and sanity check
    u8 extraFieldsCount = 0;
    packet_read(p, &extraFieldsCount, sizeof(u8));
    if (extraFieldsCount != so->extraFieldCount) {
        return;
    }

    // read the extra fields
    for (u8 i = 0; i < extraFieldsCount; i++) {
        SOFT_ASSERT(so->extraFields[i] != NULL);
        packet_read(p, so->extraFields[i], sizeof(u32));
    }
}

// ----- only death ----- //

static void packet_write_object_only_death(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }
    packet_write(p, &o->activeFlags, sizeof(s16));
}

static void packet_read_object_only_death(struct Packet* p, struct Object* o) {
    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so->maxSyncDistance != SYNC_DISTANCE_ONLY_DEATH) { return; }
    s16 activeFlags;
    packet_read(p, &activeFlags, sizeof(u16));
    if (activeFlags == ACTIVE_FLAG_DEACTIVATED) {
        // flag the object as dead, the behavior is responsible for clean up
        so->o->oSyncDeath = 1;
        network_forget_sync_object(so);
    }
}

// ----- main send/receive ----- //

void network_send_object(struct Object* o) {
    if (gNetworkType == NT_NONE || gNetworkPlayerLocal == NULL) { return; }

    // sanity check SyncObject
    if (!network_sync_object_initialized(o)) { return; }
    if (o->behavior == bhvRespawner) { return; }

    struct SyncObject* so = &gSyncObjects[o->oSyncID];
    if (so == NULL) { return; }
    if (o != so->o) {
        LOG_ERROR("object mismatch for %d", o->oSyncID);
        return;
    }
    if (o->behavior != so->behavior && !allowable_behavior_change(so, so->behavior)) {
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", o->oSyncID, get_id_from_behavior(o->behavior), get_id_from_behavior(so->behavior));
        network_forget_sync_object(so);
        return;
    }

    bool reliable = (o->activeFlags == ACTIVE_FLAG_DEACTIVATED || so->maxSyncDistance == SYNC_DISTANCE_ONLY_EVENTS);
    network_send_object_reliability(o, reliable);
}

void network_send_object_reliability(struct Object* o, bool reliable) {
    if (gNetworkPlayerLocal == NULL || !gNetworkPlayerLocal->currAreaSyncValid) { return; }
    // prevent sending objects during credits sequence
    if (gCurrActStarNum == 99) { return; }
    // sanity check SyncObject
    if (!network_sync_object_initialized(o)) { return; }
    u8 syncId = o->oSyncID;
    struct SyncObject* so = &gSyncObjects[syncId];
    if (so == NULL) { return; }
    if (o != so->o) {
        LOG_ERROR("object mismatch for %d", syncId);
        return;
    }
    if (o->behavior != so->behavior && !allowable_behavior_change(so, so->behavior)) {
        LOG_ERROR("behavior mismatch for %d: %04X vs %04X", syncId, get_id_from_behavior(o->behavior), get_id_from_behavior(so->behavior));
        network_forget_sync_object(so);
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
        network_forget_sync_object(so);
        if (gNetworkType == NT_SERVER) {
            reservation_area_release(gNetworkPlayerLocal, syncId);
        } else {
            network_send_reservation_release(syncId);
        }
    } else if (so->rememberLastReliablePacket) {
        // remember packet
        packet_duplicate(&p, &sLastSyncEntReliablePacket[syncId]);
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
    if (so == NULL) { return; }
    struct Object* o = so->o;
    if (!network_sync_object_initialized(o)) { return; }

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
        network_forget_sync_object(so);
    } else if (p->reliable) {
        // remember packet
        packet_duplicate(p, &sLastSyncEntReliablePacket[o->oSyncID]);
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
    if (o != NULL) {
        Vec3f deltaPos = { 0 };
        deltaPos[0] = o->oPosX - oldPos[0];
        deltaPos[2] = o->oPosY - oldPos[1];
        deltaPos[1] = o->oPosZ - oldPos[2];
        for (int i = 0; i < MAX_PLAYERS; i++) {
            if (!is_player_active(&gMarioStates[i])) { continue; }
            if (gMarioStates[i].marioObj->platform != o) { continue; }
            for (int j = 0; j < 3; j++) { gMarioStates[i].pos[j] += deltaPos[j]; }
        }
    }

}

void network_forget_sync_object(struct SyncObject* so) {
    // invalidate last packet sent
    if (so != NULL && so->o != NULL && so->o->oSyncID < RESERVED_IDS_SYNC_OBJECT_OFFSET) {
        u8 syncId = so->o->oSyncID;
        struct SyncObject* so2 = &gSyncObjects[syncId];
        if (so == so2) {
            sLastSyncEntReliablePacket[syncId].error = true;
        }
        area_remove_sync_ids_add(syncId);
    }

    if (so->on_forget != NULL) {
        struct Object* lastObject = gCurrentObject;
        gCurrentObject = so->o;
        so->on_forget();
        gCurrentObject = lastObject;
    }

    so->o = NULL;
    so->behavior = NULL;
    so->owned = false;
}

void network_update_objects(void) {
    if (gNetworkAreaLoaded && delayedPacketObjectHead != NULL) {
        network_delayed_packet_object_execute();
    }

#ifdef DEVELOPMENT
    static f32 lastDebugSync = 0;
    if (clock_elapsed() - lastDebugSync >= 1) {
        network_send_debug_sync();
        lastDebugSync = clock_elapsed();
    }
#endif

    for (u32 i = 1; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so->o == NULL) { continue; }

        // check for stale sync object
        if (so->o->oSyncID != i) {
            LOG_ERROR("sync id mismatch: %d vs %d (behavior %d)", so->o->oSyncID, i, get_id_from_behavior(so->o->behavior));
            network_forget_sync_object(so);
            continue;
        }

        // check if we should be the one syncing this object
        so->owned = should_own_object(so);
        if (!so->owned) { continue; }

        // check for 'only death' event
        if (so->maxSyncDistance == SYNC_DISTANCE_ONLY_DEATH) {
            if (so->o->activeFlags != ACTIVE_FLAG_DEACTIVATED) { continue; }
            network_send_object(gSyncObjects[i].o);
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
            network_send_object(gSyncObjects[i].o);
        }
    }

}
