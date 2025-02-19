#include <stdio.h>
#include "../network.h"
#include "game/area.h"
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
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

// TODO: move to common utility location
static struct Object* get_object_matching_respawn_info(u32* respawnInfo) {
    for (s32 i = 0; i < OBJECT_POOL_CAPACITY; i++) {
        struct Object* o = &gObjectPool[i];
        if (o->respawnInfo == respawnInfo) { return o; }
    }
    return NULL;
}

////

static void network_send_level_spawn_info_area(struct NetworkPlayer* destNp, u8 areaIndex) {
    // check that the area is active
    struct Area* area = &gAreaData[areaIndex];
    if (area->unk04 == NULL) { return; }

    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_level_spawn_info_area: dest np is invalid");
        return;
    }

    // write header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_SPAWN_INFO, true, PLMT_NONE);
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActStarNum, sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

    // write this area's index
    packet_write(&p, &areaIndex, sizeof(u8));

    // write the amount of deletions
    u8 zero = 0;
    u8* spawnInfoDeletionCount = &p.buffer[p.cursor];
    packet_write(&p, &zero, sizeof(u8));

    // loop through spawn infos
    struct SpawnInfo* spawnInfo = area->objectSpawnInfos;
    u16 spawnInfoIndex = 0;

    while (spawnInfo != NULL) {
        // if a spawn info object was destroyed, send its spawn info index
        if (((spawnInfo->behaviorArg >> 8) & RESPAWN_INFO_DONT_RESPAWN) == RESPAWN_INFO_DONT_RESPAWN) {
            *spawnInfoDeletionCount = *spawnInfoDeletionCount + 1;
            packet_write(&p, &spawnInfoIndex, sizeof(u16));
            LOG_INFO("tx spawn info deletion: index %d", spawnInfoIndex);
        }

        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }

    // send the packet if there are deletions
    if (*spawnInfoDeletionCount > 0) {
        network_send_to(destNp->localIndex, &p);
        LOG_INFO("tx spawn info for area %d (count %d)", areaIndex, *spawnInfoDeletionCount);
    }
}

void network_send_level_spawn_info(struct NetworkPlayer* destNp) {
    if (!gNetworkPlayerLocal->currAreaSyncValid) {
        return;
    }

    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_level_spawn_info: dest np is invalid");
        return;
    }

    for (s32 i = 0; i < MAX_AREAS; i++) {
        network_send_level_spawn_info_area(destNp, i);
    }
}

void network_receive_level_spawn_info(struct Packet* p) {
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("Receiving 'location response' with the wrong location!");
        return;
    }

    u8 thisAreaIndex, spawnInfoDeletionCount;
    packet_read(p, &thisAreaIndex, sizeof(u8));
    packet_read(p, &spawnInfoDeletionCount, sizeof(u8));
    LOG_INFO("rx spawn info (count %d)", spawnInfoDeletionCount);
    if (spawnInfoDeletionCount <= 0) { return; }
    if (thisAreaIndex >= MAX_AREAS) {
        LOG_ERROR("Receiving 'location response' with invalid areaIndex!");
        return;
    }

    struct SpawnInfo* spawnInfo = gAreaData[thisAreaIndex].objectSpawnInfos;
    u16 spawnInfoIndex = 0;

    u16 spawnInfoDeleteIndex;
    packet_read(p, &spawnInfoDeleteIndex, sizeof(u16));

    while (spawnInfo != NULL && spawnInfoDeletionCount > 0) {
        if (spawnInfoIndex == spawnInfoDeleteIndex) {
            u32* respawnInfo = &spawnInfo->behaviorArg;
            struct Object* o = get_object_matching_respawn_info(respawnInfo);
            if (o != NULL) {
                obj_mark_for_deletion(o);
                LOG_INFO("rx spawn info deletion: object");
                if (o->oSyncID != 0) {
                    struct SyncObject* so = sync_object_get(o->oSyncID);
                    if (so && so->o == o) {
                        sync_object_forget(so->id);
                        LOG_INFO("rx spawn info deletion: sync object");
                    }
                }
            }
            spawnInfoDeletionCount--;
            packet_read(p, &spawnInfoDeleteIndex, sizeof(u16));
        }

        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }
}
