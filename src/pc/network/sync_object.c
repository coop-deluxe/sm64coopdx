#include "types.h"
#include "sync_object.h"
#include "network.h"
#include "behavior_table.h"
#include "object_constants.h"
#include "object_fields.h"
#include "reservation_area.h"
#include "game/area.h"
#include "game/object_list_processor.h"
#include "game/obj_behaviors.h"
#include "game/object_helpers.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"

#define MAX_SYNC_OBJECTS 256 // note: increasing this requires code to be rewritten

struct SyncObject sSyncObjects[MAX_SYNC_OBJECTS] = { 0 };
static u32 sNextSyncId = 0;
static u32 sIterateSyncId = 0;

  ////////////
 // system //
////////////

void sync_objects_clear(void) {
    sNextSyncId = 0;
    network_on_init_area();
    for (u32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        sync_object_forget(i);
    }
}

void sync_object_forget(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return; }

    // invalidate last packet sent
    if (so != NULL && so->o != NULL && so->o->oSyncID < RESERVED_IDS_SYNC_OBJECT_OFFSET) {
        u32 syncId2 = so->o->oSyncID;
        struct SyncObject* so2 = sync_object_get(syncId2);
        if (so == so2) {
            so->lastReliablePacket.error = true;
        }
        area_remove_sync_ids_add(syncId2);
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

void sync_object_forget_last_reliable_packet(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return; }
    so->lastReliablePacket.error = true;
}

struct SyncObject* sync_object_init(struct Object *o, float maxSyncDistance) {
    if (!o) { return NULL; }

    if (o->coopFlags & COOP_OBJ_FLAG_NON_SYNC) {
        return NULL;
    }

    bool hadSyncId = (o->oSyncID != 0);
    // generate new sync ID
    if (!sync_object_set_id(o)) {
        LOG_ERROR("failed to set sync id for object w/behavior %d (init_object)", get_id_from_behavior(o->behavior));
        o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        return NULL;
    }
    u32 id = o->oSyncID;

    // set default values for sync object
    struct SyncObject* so = sync_object_get(id);
    if (!so) {
        LOG_ERROR("Failed to get sync object in init");
        return NULL;
    }
    so->id = id;
    so->o = o;
    so->maxSyncDistance = maxSyncDistance;
    so->owned = false;
    so->clockSinceUpdate = clock_elapsed();
    so->extraFieldCount = 0;
    so->lastReliablePacketIsStale = false;
    so->rememberLastReliablePacket = true;
    so->behavior = (BehaviorScript*)o->behavior;
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
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
    if (!hadSyncId) {
        so->extendedModelId = 0xFFFF;
    }
    so->randomSeed = (u16)(o->oSyncID * 7951);
    memset(so->extraFields, 0, sizeof(void*) * MAX_SYNC_OBJECT_FIELDS);
    memset(so->extraFieldsSize, 0, sizeof(u8) * MAX_SYNC_OBJECT_FIELDS);

    so->lastReliablePacket.error = true;

    return so;
}

void sync_object_init_field(struct Object *o, void* field) {
    if (o->coopFlags & COOP_OBJ_FLAG_NON_SYNC) { return; }
    if (o->oSyncID == 0) { return; }

    // remember to synchronize this extra field
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    u32 index = so->extraFieldCount++;
    if (so->extraFieldCount >= MAX_SYNC_OBJECT_FIELDS) { return; }
    so->extraFields[index] = field;
    so->extraFieldsSize[index] = 32;
}

void sync_object_init_field_with_size(struct Object *o, void* field, u8 size) {
    if (o->coopFlags & COOP_OBJ_FLAG_NON_SYNC) { return; }
    if (o->oSyncID == 0) { return; }

    SOFT_ASSERT(size == 8 || size == 16 || size == 32 || size == 64);

    // remember to synchronize this extra field
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    u32 index = so->extraFieldCount++;
    if (so->extraFieldCount >= MAX_SYNC_OBJECT_FIELDS) { return; }
    so->extraFields[index] = field;
    so->extraFieldsSize[index] = size;
}

  /////////////
 // getters //
/////////////

struct SyncObject* sync_object_get(u32 syncId) {
    if (syncId >= MAX_SYNC_OBJECTS) { return NULL; }
    return &sSyncObjects[syncId];
}

struct SyncObject* sync_object_get_first(void) {
    sIterateSyncId = 0;
    return &sSyncObjects[sIterateSyncId];
}

struct SyncObject* sync_object_get_first_non_static(void) {
    sIterateSyncId = RESERVED_IDS_SYNC_OBJECT_OFFSET;
    return &sSyncObjects[sIterateSyncId];
}

struct SyncObject* sync_object_get_next(void) {
    sIterateSyncId++;
    if (sIterateSyncId >= MAX_SYNC_OBJECTS) { return NULL; }
    return &sSyncObjects[sIterateSyncId];
}

struct Object* sync_object_get_object(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    return so ? so->o : NULL;
}

bool sync_object_is_initialized(u32 syncId) {
    if (syncId == 0) { return false; }
    struct SyncObject* so = sync_object_get(syncId);
    if (so == NULL || so->behavior == NULL) { return false; }
    return true;
}

bool sync_object_is_owned_locally(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
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

struct Packet* sync_object_get_last_reliable_packet(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return NULL; }
    return &so->lastReliablePacket;
}

  /////////////
 // setters //
/////////////

void sync_object_override_object(u32 syncId, struct Object* o) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return; }
    so->o = o;
}

  ///////////
 // utils //
///////////

// todo: move this to somewhere more general
float player_distance(struct MarioState* marioState, struct Object* o) {
    if (marioState->marioObj == NULL) { return 0; }
    f32 mx = marioState->marioObj->header.gfx.pos[0] - o->oPosX;
    f32 my = marioState->marioObj->header.gfx.pos[1] - o->oPosY;
    f32 mz = marioState->marioObj->header.gfx.pos[2] - o->oPosZ;
    mx *= mx;
    my *= my;
    mz *= mz;
    return sqrt(mx + my + mz);
}

bool sync_object_should_own(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return false; }

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

    // own held objects
    if (gMarioStates[0].heldByObj == so->o) { return true; }

    // don't own other held objects
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (gMarioStates[i].heldByObj == so->o) { return false; }
    }

    if (so->o->oHeldState == HELD_HELD && so->o->heldByPlayerIndex == 0) { return true; }

    // check distance
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (i != 0 && !is_player_active(&gMarioStates[i])) { continue; }
        if (player_distance(&gMarioStates[0], so->o) > player_distance(&gMarioStates[i], so->o)) { return false; }
    }

    if (so->o->oHeldState == HELD_HELD && so->o->heldByPlayerIndex != 0) { return false; }

    return true;
}

static u32 sync_object_find_cached_id(struct Object* o) {
    u32 behaviorId = get_id_from_behavior(o->behavior);
    for (s32 i = 1; i < 256; i++) {
        struct SyncObject* so = sync_object_get(i);
        if (!so) { continue; }
        if (so->o != NULL) { continue; }
        u32 cachedBehaviorId = gCurrentArea->cachedBehaviors[i];
        if (cachedBehaviorId != behaviorId) { continue; }

        f32 dist = dist_between_object_and_point(o, gCurrentArea->cachedPositions[i][0], gCurrentArea->cachedPositions[i][1], gCurrentArea->cachedPositions[i][2]);
        if (dist > 1) { continue; }
        return i;
    }
    return 0;
}

bool sync_object_set_id(struct Object* o) {
    // check for existing id
    if (o->oSyncID != 0) { return true; }

    u32 syncId = 0;
    if (!gNetworkAreaLoaded) {
        syncId = sync_object_find_cached_id(o);
        if (syncId == 0) {
            // while loading, just fill in sync ids from 1 to MAX_SYNC_OBJECTS
            for (s32 i = 1; i < MAX_SYNC_OBJECTS; i++) {
                sNextSyncId++;
                sNextSyncId = sNextSyncId % RESERVED_IDS_SYNC_OBJECT_OFFSET;
                struct SyncObject* so = sync_object_get(sNextSyncId);
                if (!so || so->o != NULL) { continue; }
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

    if (syncId == 0) {
        LOG_ERROR("failed to set sync id for object w/behavior %d (set_sync_id) %u", get_id_from_behavior(o->behavior), gNetworkAreaLoaded);
        return false;
    }
    
    struct SyncObject* so = sync_object_get(syncId);
    if (!so || so->o != NULL) {
        LOG_ERROR("failed to set sync id (o) for object w/behavior %d (set_sync_id) %u", get_id_from_behavior(o->behavior), gNetworkAreaLoaded);
        return false;
    }

    o->oSyncID = syncId;

    if (gNetworkAreaLoaded) {
        LOG_INFO("set sync id for object w/behavior %d", get_id_from_behavior(o->behavior));
    }

    SOFT_ASSERT_RETURN(o->oSyncID < MAX_SYNC_OBJECTS, false);
    return true;
}
