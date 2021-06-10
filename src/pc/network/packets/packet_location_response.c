#include <stdio.h>
#include "../network.h"
#include "game/interaction.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/macro_special_objects.h"
#include "object_constants.h"
#include "object_fields.h"
#include "behavior_table.h"
#include "model_ids.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

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

    // level variables
    packet_write(&p, &gMarioStates[0].numCoins, sizeof(s16));
    packet_write(&p, &gPssSlideStarted, sizeof(u8));
    packet_write(&p, &gHudDisplay.timer, sizeof(u16));

    // respawners
    u8 respawnerCount = 0;
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL || so->o->behavior != bhvRespawner) { continue; }
        respawnerCount++;
    }

    packet_write(&p, &respawnerCount, sizeof(u8));
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        struct SyncObject* so = &gSyncObjects[i];
        if (so == NULL || so->o == NULL || so->o->behavior != bhvRespawner) { continue; }
        u32 behaviorToRespawn = get_id_from_behavior(so->o->oRespawnerBehaviorToRespawn);
        packet_write(&p, &so->o->oPosX, sizeof(f32));
        packet_write(&p, &so->o->oPosY, sizeof(f32));
        packet_write(&p, &so->o->oPosZ, sizeof(f32));
        packet_write(&p, &so->o->oBehParams, sizeof(s32));
        packet_write(&p, &so->o->oRespawnerModelToRespawn, sizeof(s32));
        packet_write(&p, &so->o->oRespawnerMinSpawnDist, sizeof(f32));
        packet_write(&p, &behaviorToRespawn, sizeof(s32));
        packet_write(&p, &so->o->oSyncID, sizeof(u32));
        LOG_INFO("tx respawner");
    }

    network_send_to(destNp->localIndex, &p);

    // send macro deletions
    network_send_macro_deletions(destGlobalIndex);

    // send spawn info
    network_send_spawn_info_deletions(destGlobalIndex);

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
        LOG_INFO("tx non-static");
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

    LOG_INFO("tx location response");
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

    u8 pssSlideStarted;
    u16 hudDisplayTimer;
    packet_read(p, &pssSlideStarted, sizeof(u8));
    packet_read(p, &hudDisplayTimer, sizeof(u16));
    if (pssSlideStarted) {
        level_control_timer(TIMER_CONTROL_SHOW);
        level_control_timer(TIMER_CONTROL_START);
        gPssSlideStarted = TRUE;
        gHudDisplay.timer = hudDisplayTimer;
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

        struct SyncObject* so = &gSyncObjects[syncId];

        LOG_INFO("rx respawner");
        if (so->staticLevelSpawn) {
            struct Object* respawner = spawn_object_abs_with_rot(gMarioStates[0].marioObj, 0, MODEL_NONE, bhvRespawner, posX, posY, posZ, 0, 0, 0);
            respawner->parentObj = respawner;
            respawner->oBehParams = behParams;
            respawner->oRespawnerModelToRespawn = respawnerModelToRespawn;
            respawner->oRespawnerMinSpawnDist = respawnerMinSpawnDist;
            respawner->oRespawnerBehaviorToRespawn = get_behavior_from_id(behaviorToRespawn);
            respawner->oSyncID = syncId;

            struct Object* o = so->o;
            o->oSyncID = 0;
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;

            so->o = respawner;
            LOG_INFO("rx respawner replaced!");
        }
    }

    gMarioStates[0].numCoins = numCoins;
    gNetworkPlayerLocal->currAreaSyncValid = true;

    if (gNetworkType != NT_SERVER) {
        network_send_level_area_valid(0);
    }
    LOG_INFO("rx location response");
}