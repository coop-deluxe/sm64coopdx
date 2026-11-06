#include <stdio.h>
#include "../network.h"
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
#include "pc/lua/smlua_hooks.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

u32 sRemoveSyncIds[SYNC_ID_BLOCK_SIZE] = { 0 };
u32 sRemoveSyncIdsIndex = 0;

void area_remove_sync_ids_add(u32 syncId) {
    if (syncId >= SYNC_ID_BLOCK_SIZE) { return; }
    for (u32 i = 0; i < sRemoveSyncIdsIndex; i++) {
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

        // Level Location
        packet_write_int16(&p, gCurrCourseNum);
        packet_write_int16(&p, gCurrActStarNum);
        packet_write_int16(&p, gCurrLevelNum);
        packet_write_int16(&p, gCurrAreaIndex);

        // Area Variables
        packet_write_uint32(&p, gNetworkAreaTimer);
        packet_write_uint32(&p, gNetworkAreaRandomSeed);
        packet_write_int32(&p, gEnvironmentLevels[0]); // Only syncs WDW water level. Would this cause problems for mods?

        // Level Control Timer
        packet_write_bool(&p, levelControlTimerVisible);
        packet_write_bool(&p, levelControlTimerRunning);
        packet_write_uint32(&p, gControlTimerStartNat);
        packet_write_uint32(&p, gControlTimerStopNat);

        // Write Sync ID removals
        packet_write_uint32(&p, sRemoveSyncIdsIndex);
        for (u32 i = 0; i < sRemoveSyncIdsIndex; i++) {
            packet_write_uint32(&p, sRemoveSyncIds[i]);
            LOG_INFO("tx remove sync id %d", sRemoveSyncIds[i]);
        }

        // Count our respawners.
        u16 respawnerCount = 0;

        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            if (so->o != NULL && so->o->behavior == smlua_override_behavior(bhvRespawner)) {
                respawnerCount++;
            }
        }
        
        // Write the amount of respawners.
        packet_write_uint16(&p, respawnerCount);

        // Write all of our respawners.
        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            if (so == NULL || so->o == NULL || so->o->behavior != smlua_override_behavior(bhvRespawner)) { continue; }
            u32 behaviorToRespawn = get_id_from_behavior(so->o->oRespawnerBehaviorToRespawn);
            packet_write_float32(&p, so->o->oPosX);
            packet_write_float32(&p, so->o->oPosY);
            packet_write_float32(&p, so->o->oPosZ);
            packet_write_int32(&p, so->o->oBehParams);
            packet_write_int32(&p, so->o->oRespawnerModelToRespawn);
            packet_write_float32(&p, so->o->oRespawnerMinSpawnDist);
            packet_write_uint32(&p, behaviorToRespawn);
            packet_write_uint32(&p, so->o->oSyncID);
            LOG_INFO("tx respawner");
        }

        // Send the Area Packet
        network_send_to(toNp->localIndex, &p);
        
        packet_clear(&p);

        // Send all of our objects
        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            if (so == NULL || so->o == NULL || so->o->oSyncID != so->id) { continue; }
            if (so->o->behavior == smlua_override_behavior(bhvRespawner)) { continue; }

            // Static objects have deterministic sync ids based on their spawn order,
            // So we send an update packet rather than a spawn packet for them.
            if (so->id < SYNC_ID_BLOCK_SIZE) {
                network_send_object_reliability_to(toNp->localIndex, so->o, true);

                LOG_INFO("tx static");
            } else {
                struct Object* spawn_objects[] = { so->o };

                // Find the model
                u32 model = dynos_model_get_id_from_graph_node(so->o->header.gfx.sharedChild);

                u32 models[] = { model };
                network_send_spawn_objects_to(toNp->localIndex, spawn_objects, models, 1);
                LOG_INFO("tx non-static");
            }
        }

        // Send last reliable ent packet
        for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
            if (so == NULL || so->o == NULL) { continue; }
            if (so->lastReliablePacketIsStale) { continue; }
            struct Packet* entPacket = sync_object_get_last_reliable_packet(so->id);
            if (datagram_has_error(&entPacket->dg)) { continue; }
            struct Packet p2 = { 0 };
            packet_duplicate(entPacket, &p2);
            network_send_to(toNp->localIndex, &p2);
            packet_clear(&p2);
        }

        // Send sync valid
        network_send_sync_valid(toNp, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex, false);
    }
    packet_ordered_end();

    LOG_INFO("tx area");
}

void network_receive_area(struct Packet* p) {
    LOG_INFO("rx area");

    if (p == NULL) {
        LOG_ERROR("rx area: The packet was NULL, Failed to receive the area.");
        return;
    }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= 2 + (sizeof(u16) * 1) + (sizeof(s16) * 4) + (sizeof(s32) * 1) + (sizeof(u32) * 5));

    // Read the Level Location.
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("rx area: received an improper location");
        return;
    }

    // Read the Area variables
    gNetworkAreaTimer = packet_read_uint32(p);
    gNetworkAreaRandomSeed = packet_read_uint32(p);

    gNetworkAreaTimerClock = clock_elapsed_ticks() - gNetworkAreaTimer;
    gEnvironmentLevels[0] = packet_read_int32(p);
    if (gCurrLevelNum == LEVEL_WDW && gEnvironmentRegions != NULL && gEnvironmentRegionsLength > 6) {
        gEnvironmentRegions[6] = gEnvironmentLevels[0];
    }

    // Read the Control Timer variables
    bool levelControlTimerRunning = packet_read_bool(p);
    bool levelControlTimerVisible = packet_read_bool(p);
    if (levelControlTimerVisible) {
        level_control_timer(TIMER_CONTROL_SHOW);
    }
    if (levelControlTimerRunning) {
        level_control_timer(TIMER_CONTROL_START);
    }
    gControlTimerStartNat = packet_read_uint32(p);
    gControlTimerStopNat = packet_read_uint32(p);

    // Read all of the removed sync ids,m
    area_remove_sync_ids_clear();
    sRemoveSyncIdsIndex = packet_read_uint32(p);
    if (sRemoveSyncIdsIndex >= SYNC_ID_BLOCK_SIZE) {
        LOG_ERROR("rx area: invalid number of sync ids to remove: %u", sRemoveSyncIdsIndex);
        sRemoveSyncIdsIndex = SYNC_ID_BLOCK_SIZE - 1;
    }
    for (u32 i = 0; i < sRemoveSyncIdsIndex; i++) {
        sRemoveSyncIds[i] = packet_read_uint32(p);
        struct SyncObject* so = sync_object_get(sRemoveSyncIds[i]);
        if (!so) { continue; }

        if (so->o != NULL) {
            so->o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }

        sync_object_forget(so->id);
        LOG_INFO("rx remove sync id %d", sRemoveSyncIds[i]);
    }

    // Read the respawner count
    u16 respawnerCount = packet_read_uint16(p);

    // Read of all the respawners.
    for (s32 i = 0; i < respawnerCount; i++) {
        f32 posX = packet_read_float32(p);
        f32 posY = packet_read_float32(p);
        f32 posZ = packet_read_float32(p);
        s32 behParams = packet_read_int32(p);
        s32 respawnerModelToRespawn = packet_read_int32(p);
        f32 respawnerMinSpawnDist = packet_read_float32(p);
        u32 behaviorToRespawn = packet_read_uint32(p);
        u32 syncId = packet_read_uint32(p);

        struct SyncObject* so = sync_object_get(syncId);
        if (so == NULL) {
            LOG_ERROR("rx area: Sync object was NULL, Skipping respawner.");
            LOG_DEBUG("rx area debug: Sync Object DEBUG:\n\n \
                       POS X: %f\n \
                       POS Y: %f\n \
                       POS Z: %f\n \
                       BEHAVIOR PARAMS: 0x%X\n \
                       RESPAWN MODEL: %i\n \
                       MIN RESPAWN DIST: %f\n \
                       RESPAWN BEHAVIOR: %u\n \
                       SYNC ID: %u\n\n",
                       posX, posY, posZ, behParams, respawnerModelToRespawn,
                       respawnerMinSpawnDist, behaviorToRespawn, syncId);
            continue;
        }

        LOG_INFO("rx respawner");
        if (syncId >= SYNC_ID_BLOCK_SIZE) { continue; }
          
        struct Object* respawner = spawn_object_abs_with_rot(gMarioStates[0].marioObj, 0, MODEL_NONE, bhvRespawner, posX, posY, posZ, 0, 0, 0);
        if (respawner != NULL) {
            respawner->parentObj = respawner;
            respawner->oBehParams = behParams;
            respawner->oRespawnerModelToRespawn = respawnerModelToRespawn;
            respawner->oRespawnerMinSpawnDist = respawnerMinSpawnDist;
            respawner->oRespawnerBehaviorToRespawn = get_behavior_from_id(behaviorToRespawn);
            respawner->oSyncID = syncId;
        }

        struct Object* o = so->o;
        if (o != NULL) {
            o->oSyncID = 0;
            o->activeFlags = ACTIVE_FLAG_DEACTIVATED;
        }

        if (respawner != NULL) { so->o = respawner; }
        LOG_INFO("rx respawner replaced!");
    }
}
