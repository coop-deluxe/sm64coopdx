#include "types.h"
#include "sync_object.h"
#include "network.h"
#include "behavior_table.h"
#include "object_constants.h"
#include "object_fields.h"
#include "game/area.h"
#include "game/object_list_processor.h"
#include "game/obj_behaviors.h"
#include "game/object_helpers.h"
#include "pc/debuglog.h"
#include "pc/utils/misc.h"
#include "data/dynos_cmap.cpp.h"
#include "pc/debug_context.h"

static void* sSoMap = NULL;

#define FORGET_TIMEOUT 10

struct SyncObjectForgetEntry {
    struct SyncObject* so;
    s32 forgetTimer;
    struct SyncObjectForgetEntry* next;
};
struct SyncObjectForgetEntry* sForgetList = NULL;

static u32 sNextSyncId = SYNC_ID_BLOCK_SIZE / 2;
static bool sFreeingAll = false;

  ////////////
 // system //
////////////

void sync_objects_init_system(void) {
    sSoMap = hmap_create(true);
}

static bool sync_objects_forget_list_contains(struct SyncObject* so) {
    struct SyncObjectForgetEntry* entry = sForgetList;
    while (entry) {
        struct SyncObjectForgetEntry* next = entry->next;
        if (entry->so == so) {
            return true;
        }
        entry = next;
    }
    return false;
}

void sync_objects_update(void) {
    struct SyncObjectForgetEntry* prev = NULL;
    struct SyncObjectForgetEntry* entry = sForgetList;
    while (entry) {
        struct SyncObjectForgetEntry* next = entry->next;
        if (entry->forgetTimer == FORGET_TIMEOUT) {
            struct SyncObject* currentSo = sync_object_get(entry->so->id);
            if (currentSo == entry->so) {
                hmap_del(sSoMap, entry->so->id);
            }
        }

        if (entry->forgetTimer-- <= 0) {
            if (prev) {
                prev->next = next;
            } else {
                sForgetList = next;
            }
            //LOG_INFO("Freeing sync object %u : %s\n", entry->so->id, get_behavior_name_from_id(get_id_from_behavior(entry->so->behavior)));
            free(entry->so);
            free(entry);

        } else {
            prev = entry;
        }

        entry = next;
    }
}

void sync_objects_clear(void) {
    sNextSyncId = SYNC_ID_BLOCK_SIZE / 2;
    network_on_init_area();

    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        sync_object_forget(so->id);
    }
    hmap_clear(sSoMap);
}

void sync_object_forget(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    if (!so) { return; }
    if (so->forgetting) { return; }

    // invalidate last packet sent
    if (so != NULL && so->o != NULL && so->o->oSyncID < SYNC_ID_BLOCK_SIZE) {
        u32 syncId2 = so->o->oSyncID;
        struct SyncObject* so2 = sync_object_get(syncId2);
        if (so == so2) {
            so->lastReliablePacket.error = true;
        }
        area_remove_sync_ids_add(syncId2);
    }

    if (so->on_forget != NULL && so->o) {
        struct Object* lastObject = gCurrentObject;
        gCurrentObject = so->o;
        so->on_forget();
        gCurrentObject = lastObject;
    }

    if (so->o) {
        so->o->oSyncID = 0;
    }

    so->forgetting = true;

    // add it to a list to free later
    s32 forgetCount = 1;
    struct SyncObjectForgetEntry* newEntry = calloc(1, sizeof(struct SyncObjectForgetEntry));
    newEntry->so = so;
    newEntry->forgetTimer = FORGET_TIMEOUT;
    if (sForgetList == NULL) {
        sForgetList = newEntry;
    } else {
        struct SyncObjectForgetEntry* entry = sForgetList;
        while (entry->next != NULL) {
            entry = entry->next;
            forgetCount++;
        }
        entry->next = newEntry;
    }
    //LOG_INFO("Scheduling sync object to free %u : %s\n", so->id, get_behavior_name_from_id(get_id_from_behavior(so->behavior)));

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

    if (o->coopFlags & COOP_OBJ_FLAG_INITIALIZED) {
        return so;
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
    so->ctx = 0;
    if (!hadSyncId) {
        so->extendedModelId = 0xFFFF;
    }
    so->randomSeed = (u16)(o->oSyncID * 7951);
    memset(so->extraFields, 0, sizeof(void*) * MAX_SYNC_OBJECT_FIELDS);
    memset(so->extraFieldsSize, 0, sizeof(u8) * MAX_SYNC_OBJECT_FIELDS);

    so->lastReliablePacket.error = true;
    o->coopFlags |= COOP_OBJ_FLAG_INITIALIZED;

    return so;
}

void sync_object_init_field(struct Object *o, void* field) {
    if (o->coopFlags & COOP_OBJ_FLAG_NON_SYNC) { return; }
    if (o->oSyncID == 0) { return; }

    // remember to synchronize this extra field
    struct SyncObject* so = sync_object_get(o->oSyncID);
    if (!so) { return; }
    u32 index = so->extraFieldCount++;
    if (so->extraFieldCount >= MAX_SYNC_OBJECT_FIELDS) {
        so->extraFieldCount = MAX_SYNC_OBJECT_FIELDS - 1;
        LOG_ERROR("Sync Object %u tried to set too many extra fields!", o->oSyncID);
        return;
    }
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
    if (so->extraFieldCount >= MAX_SYNC_OBJECT_FIELDS) {
        so->extraFieldCount = MAX_SYNC_OBJECT_FIELDS - 1;
        LOG_ERROR("Sync Object %u tried to set too many extra fields!", o->oSyncID);
        return;
    }
    so->extraFields[index] = field;
    so->extraFieldsSize[index] = size;
}

  /////////////
 // getters //
/////////////

struct SyncObject* sync_object_get(u32 syncId) {
    if (syncId == 0) { return NULL; }
    return hmap_get(sSoMap, syncId);
}

struct SyncObject* sync_object_get_first(void) {
    return hmap_begin(sSoMap);
}

struct SyncObject* sync_object_get_next(void) {
    return hmap_next(sSoMap);
}

struct Object* sync_object_get_object(u32 syncId) {
    struct SyncObject* so = sync_object_get(syncId);
    return so ? so->o : NULL;
}

bool sync_object_is_initialized(u32 syncId) {
    if (syncId == 0) { return false; }
    struct SyncObject* so = sync_object_get(syncId);
    if (so == NULL || so->o == NULL) { return false; }
    return so->o->coopFlags & COOP_OBJ_FLAG_INITIALIZED;
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
        if (i != 0 && !is_player_in_local_area(&gMarioStates[i])) { continue; }
        if (player_distance(&gMarioStates[0], so->o) > player_distance(&gMarioStates[i], so->o)) { return false; }
    }

    if (so->o->oHeldState == HELD_HELD && so->o->heldByPlayerIndex != 0) { return false; }

    return true;
}

u32 sync_object_get_available_local_id(void) {
    u32 startId = (gNetworkPlayers[0].globalIndex + 1) * SYNC_ID_BLOCK_SIZE;
    u32 endId = startId + SYNC_ID_BLOCK_SIZE;
    for (u32 id = startId; id < endId; id++) {
        struct SyncObject* so = sync_object_get(id);
        if (so) { continue; }
        return id;
    }
    return 0;
}

bool sync_object_set_id(struct Object* o) {
    u32 syncId = o->oSyncID;
    u8 ctx = o->ctx;

    if (syncId == 0) {
        if (!gNetworkAreaLoaded) {
            // check if we should set our id based on our parent
            if (o->parentObj != NULL && o->parentObj->oSyncID > 0 && (o->parentObj->oSyncID % 10) == 0) {
                for (s32 i = 0; i < 10; i++) {
                    u32 tSyncId = o->parentObj->oSyncID + i;
                    struct SyncObject* so = sync_object_get(tSyncId);
                    if (so && so->o != NULL) { continue; }
                    syncId = tSyncId;
                    break;
                }
            }

            // while loading, just fill in sync ids from 1 to SYNC_ID_BLOCK_SIZE
            if (syncId == 0) {
                for (s32 i = 1; i < SYNC_ID_BLOCK_SIZE; i++) {
                    sNextSyncId++;
                    sNextSyncId = sNextSyncId % SYNC_ID_BLOCK_SIZE;
                    struct SyncObject* so = sync_object_get(sNextSyncId);
                    if (so && so->o != NULL) { continue; }
                    syncId = sNextSyncId;
                    break;
                }
            }
        } else {
            // no longer loading, require reserved id
            syncId = sync_object_get_available_local_id();
        }
    }

    if (syncId == 0 || !ctx) {
        o->oSyncID = 0;
        LOG_ERROR("failed to set sync id for object w/behavior %d (set_sync_id) %u", get_id_from_behavior(o->behavior), gNetworkAreaLoaded);
        return !ctx;
    }

    struct SyncObject* so = sync_object_get(syncId);

    if (!so) {
        so = calloc(1, sizeof(struct SyncObject));
        so->extendedModelId = 0xFFFF;
        hmap_put(sSoMap, syncId, so);
        //LOG_INFO("Allocated sync object @ %u, size %ld", syncId, (long int)hmap_len(sSoMap));
    } else if (so->o != o) {
        LOG_INFO("Already exists...");
    }

    if (!so) {
        LOG_ERROR("failed to set sync id (o) for object w/behavior %d (set_sync_id) %u, ctx %u", get_id_from_behavior(o->behavior), gNetworkAreaLoaded, ctx);
        return false;
    }

    so->id = syncId;
    so->o = o;
    so->behavior = (BehaviorScript*) o->behavior;
    so->ctx = ctx;
    o->oSyncID = syncId;

    if (gNetworkAreaLoaded) {
        LOG_INFO("set sync id for object w/behavior %d, ctx %u", get_id_from_behavior(o->behavior), ctx);
    }

    return true;
}
