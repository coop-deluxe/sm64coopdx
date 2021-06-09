#include <stdio.h>
#include "../network.h"
#include "menu/custom_menu_system.h"
#include "game/interaction.h"
#include "game/object_list_processor.h"
#include "object_constants.h"
#include "object_fields.h"
#include "game/object_helpers.h"
#include "behavior_table.h"
#include "model_ids.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;

#define MAX_STATIC_SPAWN_REMOVAL 256
u8 sStaticSpawnRemoval[MAX_STATIC_SPAWN_REMOVAL] = { 0 };
u8 sStaticSpawnRemovalIndex = 0;

#define MAX_COIN_COLLECTION 128
u8 sCoinCollection[MAX_STATIC_SPAWN_REMOVAL] = { 0 };
u8 sCoinCollectionIndex = 0;

void coin_collection_remember(u8 coinId) {
    sCoinCollection[sCoinCollectionIndex++] = coinId;
    if (sStaticSpawnRemovalIndex >= MAX_COIN_COLLECTION) { sStaticSpawnRemovalIndex = MAX_COIN_COLLECTION - 1; }
}

void coin_collection_clear(void) {
    sCoinCollectionIndex = 0;
}

void static_spawn_removal_remember(u8 syncId) {
    sStaticSpawnRemoval[sStaticSpawnRemovalIndex++] = syncId;
    if (sStaticSpawnRemovalIndex == 0) { sStaticSpawnRemovalIndex = MAX_STATIC_SPAWN_REMOVAL - 1; }
}

void static_spawn_removal_clear(void) {
    sStaticSpawnRemovalIndex = 0;
}

struct NetworkPlayer* get_network_player_from_valid_location(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected)                 { continue; }
        if (!np->currAreaSyncValid)         { continue; }
        if (np->currCourseNum != courseNum) { continue; }
        if (np->currActNum    != actNum)    { continue; }
        if (np->currLevelNum  != levelNum)  { continue; }
        if (np->currAreaIndex != areaIndex) { continue; }
        return np;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void network_send_location_request(void) {
    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* np = get_network_player_from_valid_location(gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex);
        if (np == NULL) {
            gNetworkPlayerLocal->currAreaSyncValid = true;
            return;
        }
        network_send_client_location_request(gNetworkPlayerLocal->globalIndex, np->globalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_REQUEST, true, false);
    packet_write(&p, &gCurrCourseNum,     sizeof(s16));
    packet_write(&p, &gCurrActNum,        sizeof(s16));
    packet_write(&p, &gCurrLevelNum,      sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,     sizeof(s16));
    network_send_to(0, &p);
}

void network_receive_location_request(struct Packet* p) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("non-server is receiving a location request!");
        return;
    }

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving location request from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    np->currCourseNum     = courseNum;
    np->currActNum        = actNum;
    np->currLevelNum      = levelNum;
    np->currAreaIndex     = areaIndex;
    np->currAreaSyncValid = false;

    struct NetworkPlayer* np2 = get_network_player_from_valid_location(courseNum, actNum, levelNum, areaIndex);
    if (np2 == NULL) {
        network_send_level_area_valid(np->globalIndex);
    } else if (np2 == gNetworkPlayerLocal) {
        network_send_location_response(np->globalIndex);
    } else {
        network_send_client_location_request(np->globalIndex, np2->globalIndex);
    }
}

///////////////////////////////////////////////////////////////////////////////

void network_send_client_location_request(u8 destGlobalIndex, u8 srcGlobalIndex) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("client can't send a 'client location request'");
        return;
    }
    
    struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_client_location_request: dest np is invalid (global %d)", destGlobalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_CLIENT_LOCATION_REQUEST, true, false);
    packet_write(&p, &destGlobalIndex,       sizeof(u8));
    packet_write(&p, &destNp->currCourseNum, sizeof(s16));
    packet_write(&p, &destNp->currActNum,    sizeof(s16));
    packet_write(&p, &destNp->currLevelNum,  sizeof(s16));
    packet_write(&p, &destNp->currAreaIndex, sizeof(s16));

    struct NetworkPlayer* srcNp = network_player_from_global_index(srcGlobalIndex);
    if (srcNp == NULL || !srcNp->connected || !srcNp->currAreaSyncValid) {
        LOG_ERROR("network_send_client_location_request: source np is invalid (global %d)", srcGlobalIndex);
        return;
    }

    network_send_to(srcNp->localIndex, &p);
}

void network_receive_client_location_request(struct Packet* p) {
    if (gNetworkType == NT_SERVER) {
        LOG_ERROR("server is receiving a 'client location request'!");
        return;
    }

    u8 destGlobalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &destGlobalIndex, sizeof(u8));
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("Receiving 'client location request' with the wrong location!");
        return;
    }

    network_send_location_response(destGlobalIndex);
}

///////////////////////////////////////////////////////////////////////////////

void network_send_location_response(u8 destGlobalIndex) {
    if (!gNetworkPlayerLocal->currAreaSyncValid) {
        LOG_ERROR("my area is invalid");
        return;
    }

    struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_location_response: dest np is invalid");
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_RESPONSE, true, false);
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActNum,     sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

    packet_write(&p, &gMarioStates[0].numCoins, sizeof(s16));

    // static spawn removal
    packet_write(&p, &sStaticSpawnRemovalIndex, sizeof(u8));
    for (int i = 0; i < sStaticSpawnRemovalIndex; i++) {
        packet_write(&p, &sStaticSpawnRemoval[i], sizeof(u8));
    }

    // coin collection
    packet_write(&p, &sCoinCollectionIndex, sizeof(u8));
    for (int i = 0; i < sCoinCollectionIndex; i++) {
        packet_write(&p, &sCoinCollection[i], sizeof(u8));
    }

    // respawners
    u8 respawnerCount = 0;
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL || so->behavior != bhvRespawner) { continue; }
        respawnerCount++;
    }

    packet_write(&p, &respawnerCount, sizeof(u8));
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL || so->behavior != bhvRespawner) { continue; }
        u32 behaviorToRespawn = get_id_from_behavior(so->o->oRespawnerBehaviorToRespawn);
        packet_write(&p, &so->o->oPosX, sizeof(f32));
        packet_write(&p, &so->o->oPosY, sizeof(f32));
        packet_write(&p, &so->o->oPosZ, sizeof(f32));
        packet_write(&p, &so->o->oBehParams, sizeof(s32));
        packet_write(&p, &so->o->oRespawnerModelToRespawn, sizeof(s32));
        packet_write(&p, &so->o->oRespawnerMinSpawnDist, sizeof(f32));
        packet_write(&p, &behaviorToRespawn, sizeof(s32));
        packet_write(&p, &so->o->oSyncID, sizeof(u32));
    }

    network_send_to(destNp->localIndex, &p);

    // send non-static objects
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL || so->o->oSyncID != i) { continue; }
        if (so->staticLevelSpawn) { continue; }
        if (so->o->behavior == bhvRespawner) { continue; }
        struct Object* spawn_objects[] = { so->o };

        // TODO: move find model to a utility file/function
        // find model
        u32 model = 0;
        for (int j = 0; j < 256; j++) {
            if (so->o->header.gfx.sharedChild == gLoadedGraphNodes[j]) {
                model = j;
                break;
            }
        }

        u32 models[] = { model };
        network_send_spawn_objects_to(destNp->localIndex, spawn_objects, models, 1);
    }

    // send last reliable ent packet
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL) { continue; }
        struct Packet* entPacket = get_last_sync_ent_reliable_packet(i);
        if (entPacket->error) { continue; }
        struct Packet p2 = { 0 };
        packet_duplicate(entPacket, &p2);
        network_send_to(destNp->localIndex, &p2);
    }
}

void network_receive_location_response(struct Packet* p) {
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("Receiving 'location response' with the wrong location!");
        return;
    }

    if (gNetworkPlayerLocal->currAreaSyncValid) {
        LOG_ERROR("Receiving 'location response' when our location is already valid!");
        return;
    }

    s16 numCoins;
    packet_read(p, &numCoins, sizeof(s16));

    u8 staticSpawnRemovals;
    static_spawn_removal_clear();

    // read static spawn removals
    packet_read(p, &staticSpawnRemovals, sizeof(u8));
    for (int i = 0; i < staticSpawnRemovals; i++) {
        u8 syncId;
        packet_read(p, &syncId, sizeof(u8));
        struct SyncObject* so = &gSyncObjects[syncId];
        if (so != NULL) {
            if (so->o != NULL) {
                obj_mark_for_deletion(so->o);
            }
            network_forget_sync_object(so);
        }
    }

    // read coin collections
    packet_read(p, &sCoinCollectionIndex, sizeof(u8));
    for (int i = 0; i < sCoinCollectionIndex; i++) {
        packet_read(p, &sCoinCollection[i], sizeof(u8));
    }

    // collect the coins
    for (int i = 0; i < OBJECT_POOL_CAPACITY; i++) {
        struct Object* o = &gObjectPool[i];
        if (o->activeFlags & ACTIVE_FLAG_DEACTIVATED) { continue; }
        if (!is_behavior_a_coin(o->behavior))         { continue; }
        for (int j = 0; j < sCoinCollectionIndex; j++) {
            if (o->oCoinID == sCoinCollection[j]) {
                o->oInteractStatus = INT_STATUS_INTERACTED;
            }
        }
    }

    // read respawners
    u8 respawnerCount = 0;
    packet_read(p, &respawnerCount, sizeof(u8));

    for (int i = 0; i < respawnerCount; i++) {
        f32 posX, posY, posZ;
        packet_read(p, &posX, sizeof(f32));
        packet_read(p, &posY, sizeof(f32));
        packet_read(p, &posZ, sizeof(f32));

        s32 behParams, respawnerModelToRespawn;
        packet_read(p, &behParams, sizeof(s32));
        packet_read(p, &respawnerModelToRespawn, sizeof(s32));

        f32 respawnerMinSpawnDist;
        packet_read(p, &respawnerMinSpawnDist, sizeof(f32));

        u32 behaviorToRespawn, syncId;
        packet_read(p, &behaviorToRespawn, sizeof(u32));
        packet_read(p, &syncId, sizeof(u32));

        struct Object* respawner = spawn_object_abs_with_rot(gMarioStates[0].marioObj, 0, MODEL_NONE, bhvRespawner, posX, posY, posZ, 0, 0, 0);
        respawner->parentObj = respawner;
        respawner->oBehParams = behParams;
        respawner->oRespawnerModelToRespawn = respawnerModelToRespawn;
        respawner->oRespawnerMinSpawnDist = respawnerMinSpawnDist;
        respawner->oRespawnerBehaviorToRespawn = get_behavior_from_id(behaviorToRespawn);
        respawner->oSyncID = syncId;

        network_forget_sync_object(&gSyncObjects[syncId]);
        network_init_object(respawner, SYNC_DISTANCE_ONLY_EVENTS);
    }

    gMarioStates[0].numCoins = numCoins;
    gNetworkPlayerLocal->currAreaSyncValid = true;

    if (gNetworkType != NT_SERVER) {
        network_send_level_area_valid(0);
    }
}