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
    // Check that the area is active
    if (areaIndex >= MAX_AREAS) {
        LOG_ERROR("network_send_level_spawn_info_area: area index is invalid");
        return;
    }
    struct Area* area = &gAreaData[areaIndex];
    if (area->root == NULL) { return; }

    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_level_spawn_info_area: dest np is invalid");
        return;
    }

    // Write header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_SPAWN_INFO, true, PLMT_NONE);
    packet_write_int16(&p, gCurrCourseNum);
    packet_write_int16(&p, gCurrActStarNum);
    packet_write_int16(&p, gCurrLevelNum);
    packet_write_int16(&p, gCurrAreaIndex);

    // Write this areas index
    packet_write_uint8(&p, areaIndex);

    // Write the amount of deletions
    u32 cursorPosition = datagram_length(&p.dg);
    u8 spawnInfoDeletionCount = 0;
    packet_write_uint8(&p, 0);

    // Loop through spawn infos
    struct SpawnInfo* spawnInfo = area->objectSpawnInfos;
    u16 spawnInfoIndex = 0;

    while (spawnInfo != NULL) {
        // If a spawn info object was destroyed, Send its spawn info index.
        if (((spawnInfo->behaviorArg >> 8) & RESPAWN_INFO_DONT_RESPAWN) == RESPAWN_INFO_DONT_RESPAWN) {
            spawnInfoDeletionCount += 1;
            packet_write_uint16(&p, spawnInfoIndex);
            LOG_INFO("tx spawn info deletion: index %d", spawnInfoIndex);
        }

        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }
    
    u32 restoreCursorPosition = datagram_cursor_position(&p.dg);
    datagram_seek(&p.dg, cursorPosition);
    packet_write_uint8(&p, spawnInfoDeletionCount);
    datagram_seek(&p.dg, restoreCursorPosition);

    // send the packet if there are deletions
    if (spawnInfoDeletionCount > 0) {
        network_send_to(destNp->localIndex, &p);
        LOG_INFO("tx spawn info for area %d (count %d)", areaIndex, spawnInfoDeletionCount);
    }
    packet_clear(&p);
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
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * 2) + sizeof(u16) + (sizeof(s16) * 4));
    
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);

    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("Receiving 'location response' with the wrong location!");
        return;
    }
    
    u8 thisAreaIndex = packet_read_uint8(p);
    u8 spawnInfoDeletionCount = packet_read_uint8(p);
    LOG_INFO("rx spawn info (count %d)", spawnInfoDeletionCount);
    if (spawnInfoDeletionCount <= 0) { return; }
    if (thisAreaIndex >= MAX_AREAS) {
        LOG_ERROR("Receiving 'location response' with invalid areaIndex!");
        return;
    }

    struct SpawnInfo* spawnInfo = gAreaData[thisAreaIndex].objectSpawnInfos;
    u16 spawnInfoIndex = 0;
    u16 spawnInfoDeleteIndex = packet_read_uint16(p);

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
            spawnInfoDeleteIndex = packet_read_uint16(p);
        }

        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }
}
