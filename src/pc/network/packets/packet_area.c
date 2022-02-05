#include <stdio.h>
#include "../network.h"
#include "../reservation_area.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/object_helpers.h"
#include "game/object_list_processor.h"
#include "behavior_table.h"
#include "object_constants.h"
#include "object_fields.h"
#include "model_ids.h"
#include "pc/utils/misc.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

u8 sRemoveSyncIds[RESERVED_IDS_SYNC_OBJECT_OFFSET] = { 0 };
u8 sRemoveSyncIdsIndex = 0;

void area_remove_sync_ids_add(u8 syncId) {
    if (syncId >= RESERVED_IDS_SYNC_OBJECT_OFFSET) { return; }
    for (int i = 0; i < sRemoveSyncIdsIndex; i++) {
        if (sRemoveSyncIds[i] == syncId) { return; }
    }
    sRemoveSyncIds[sRemoveSyncIdsIndex++] = syncId;
}

void area_remove_sync_ids_clear(void) {
    sRemoveSyncIdsIndex = 0;
}

/////////////////////////////////////////////////

void network_send_area(struct NetworkPlayer* toNp) {
    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    bool levelControlTimerRunning = level_control_timer_running();
    bool levelControlTimerVisible = (gHudDisplay.flags & HUD_DISPLAY_FLAG_TIMER) ? 1 : 0;

    packet_ordered_begin();
    {
        struct Packet p = { 0 };
        packet_init(&p, PACKET_AREA, true, PLMT_NONE);

        // level location
        packet_write(&p, &gCurrCourseNum,  sizeof(s16));
        packet_write(&p, &gCurrActStarNum, sizeof(s16));
        packet_write(&p, &gCurrLevelNum,   sizeof(s16));
        packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

        // area variables
        packet_write(&p, &gNetworkAreaTimer, sizeof(u32));
        packet_write(&p, gEnvironmentLevels, sizeof(s32));

        // level control timer
        packet_write(&p, &levelControlTimerVisible, sizeof(u8));
        packet_write(&p, &levelControlTimerRunning, sizeof(u8));
        packet_write(&p, &gControlTimerStartNat,    sizeof(u32));
        packet_write(&p, &gControlTimerStopNat,     sizeof(u32));

        // write sync id removals
        packet_write(&p, &sRemoveSyncIdsIndex, sizeof(u8));
        for (int i = 0; i < sRemoveSyncIdsIndex; i++) {
            packet_write(&p, &sRemoveSyncIds[i], sizeof(u8));
            LOG_INFO("tx remove sync id %d", sRemoveSyncIds[i]);
        }

        // count respawners and write
        u8 respawnerCount = 0;
        for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
            struct SyncObject* so = &gSyncObjects[i];
            if (so == NULL || so->o == NULL || so->o->behavior != bhvRespawner) { continue; }
            respawnerCount++;
        }
        packet_write(&p, &respawnerCount, sizeof(u8));

        // write respawners
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

        // send area packet
        network_send_to(toNp->localIndex, &p);

        // send non-static objects
        for (int i = RESERVED_IDS_SYNC_OBJECT_OFFSET; i < MAX_SYNC_OBJECTS; i++) {
            struct SyncObject* so = &gSyncObjects[i];
            if (so == NULL || so->o == NULL || so->o->oSyncID != (u32)i) { continue; }
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
            network_send_spawn_objects_to(toNp->localIndex, spawn_objects, models, 1);
            LOG_INFO("tx non-static");
        }

        // send last reliable ent packet
        for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
            struct SyncObject* so = &gSyncObjects[i];
            if (so == NULL || so->o == NULL) { continue; }
            if (so->lastReliablePacketIsStale) { continue; }
            struct Packet* entPacket = get_last_sync_ent_reliable_packet(i);
            if (entPacket->error) { continue; }
            struct Packet p2 = { 0 };
            packet_duplicate(entPacket, &p2);
            network_send_to(toNp->localIndex, &p2);
        }

        // send sync valid
        network_send_sync_valid(toNp, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
    }
    packet_ordered_end();

    LOG_INFO("tx area");
}

void network_receive_area(struct Packet* p) {
    LOG_INFO("rx area");

    // read level location
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum,   sizeof(s16));
    packet_read(p, &actNum,      sizeof(s16));
    packet_read(p, &levelNum,    sizeof(s16));
    packet_read(p, &areaIndex,   sizeof(s16));

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("rx area: received an improper location");
        return;
    }

    // read area variables
    packet_read(p, &gNetworkAreaTimer, sizeof(u32));
    gNetworkAreaTimerClock = clock_elapsed_ticks() - gNetworkAreaTimer;
    packet_read(p, gEnvironmentLevels, sizeof(s32));

    // read control timer variables
    bool levelControlTimerRunning = false;
    bool levelControlTimerVisible = false;
    packet_read(p, &levelControlTimerVisible, sizeof(u8));
    packet_read(p, &levelControlTimerRunning, sizeof(u8));
    if (levelControlTimerVisible) {
        level_control_timer(TIMER_CONTROL_SHOW);
    }
    if (levelControlTimerRunning) {
        level_control_timer(TIMER_CONTROL_START);
    }
    packet_read(p, &gControlTimerStartNat, sizeof(u32));
    packet_read(p, &gControlTimerStopNat,  sizeof(u32));

    // read removed sync ids
    area_remove_sync_ids_clear();
    packet_read(p, &sRemoveSyncIdsIndex, sizeof(u8));
    for (int i = 0; i < sRemoveSyncIdsIndex; i++) {
        packet_read(p, &sRemoveSyncIds[i], sizeof(u8));
        struct SyncObject* so = &gSyncObjects[sRemoveSyncIds[i]];
        if (so->o != NULL) {
            so->o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }
        network_forget_sync_object(so);
        LOG_INFO("rx remove sync id %d", sRemoveSyncIds[i]);
    }

    // read respawner count
    u8 respawnerCount = 0;
    packet_read(p, &respawnerCount, sizeof(u8));

    // read respawners
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
        if (syncId < RESERVED_IDS_SYNC_OBJECT_OFFSET) {
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
}
