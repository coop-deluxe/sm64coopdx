#include <stdio.h>
#include "../network.h"
#include "../reservation_area.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/object_helpers.h"
#include "behavior_table.h"
#include "object_constants.h"
#include "object_fields.h"
#include "model_ids.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_area(struct NetworkPlayer* toNp) {
    extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;

    packet_ordered_begin();
    {
        struct Packet p;
        packet_init(&p, PACKET_AREA, true, false);

        // level location
        packet_write(&p, &gCurrCourseNum, sizeof(s16));
        packet_write(&p, &gCurrActNum,    sizeof(s16));
        packet_write(&p, &gCurrLevelNum,  sizeof(s16));
        packet_write(&p, &gCurrAreaIndex, sizeof(s16));

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
            struct Packet* entPacket = get_last_sync_ent_reliable_packet(i);
            if (entPacket->error) { continue; }
            struct Packet p2 = { 0 };
            packet_duplicate(entPacket, &p2);
            network_send_to(toNp->localIndex, &p2);
        }

        // send sync valid
        network_send_sync_valid(toNp);
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

    extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum;
    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("rx area: received an improper location");
        return;
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
