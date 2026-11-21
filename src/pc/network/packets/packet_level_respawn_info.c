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

#define ERR_COULD_NOT_FIND_OBJECT ((u16)-1)

// TODO: These respawn info changes REALLY need to be batched and sent on a timer instead of immediately.
//       currently when collecting coins a flood of packets gets sent out when there is no immediate need
//       to know when a coin is collected in a different area.
//       Ideally this logic would be combined into packet_level_macro and packet_level_spawn_info without
//       being bolted on top like this.

static s16* get_respawn_info_from_macro_offset(u16 areaIndex, u16 macroOffset) {
    // loop through macro objects for santiziation
    u16 index = 0;
    s16* macroObjList = gAreaData[areaIndex].macroObjects;
    while (macroObjList != NULL && *macroObjList != -1) {
        macroObjList += 4;
        s16* respawnInfo = macroObjList++;
        if (macroOffset == index) {
            return respawnInfo;
        }
        index++;
    }

    return NULL;
}

static u32* get_respawn_info_from_spawn_info_index(u16 areaIndex, u16 fromSpawnInfoIndex) {
    struct SpawnInfo* spawnInfo = gAreaData[areaIndex].objectSpawnInfos;
    u16 spawnInfoIndex = 0;

    while (spawnInfo != NULL) {
        if (spawnInfoIndex == fromSpawnInfoIndex) {
            return &spawnInfo->behaviorArg;
        }

        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }

    return NULL;
}

static u16 get_macro_offset_of_object(struct Object* o) {
    // loop through macro objects to find object
    s16* macroObjList = gCurrentArea->macroObjects;
    u16 index = 0;
    while (macroObjList != NULL && *macroObjList != -1) {
        // grab preset ID
        s32 presetID = (*macroObjList & 0x1FF) - 31; // Preset identifier for MacroObjectPresets array
        if (presetID < 0) { break; }

        // parse respawn info
        macroObjList += 4;
        s16* respawnInfo = macroObjList++;

        if (o->respawnInfo == respawnInfo) {
            return index;
        }
        index++;
    }

    return ERR_COULD_NOT_FIND_OBJECT;
}

static u16 get_spawn_info_index_of_object(struct Object* o) {
    // loop through spawn infos to find object
    struct SpawnInfo* spawnInfo = gCurrentArea->objectSpawnInfos;
    u16 spawnInfoIndex = 0;

    while (spawnInfo != NULL) {
        // if a spawn info object was destroyed, send its spawn info index
        if (&spawnInfo->behaviorArg == o->respawnInfo) {
            return spawnInfoIndex;
        }
        spawnInfo = spawnInfo->next;
        spawnInfoIndex++;
    }

    return ERR_COULD_NOT_FIND_OBJECT;
}

////

void network_send_level_respawn_info(struct Object* o, u8 respawnInfoBits) {
    if (gNetworkType == NT_NONE || gNetworkPlayerLocal == NULL) { return; }

    // Make sure our area is valid
    if (!gNetworkPlayerLocal->currAreaSyncValid) {
        return;
    }

    // Make sure we can find the object
    u16 macroOffset    = get_macro_offset_of_object(o);
    u16 spawnInfoIndex = get_spawn_info_index_of_object(o);
    if (macroOffset == ERR_COULD_NOT_FIND_OBJECT && spawnInfoIndex == ERR_COULD_NOT_FIND_OBJECT) {
        LOG_INFO("could not find object in macro or spawn info");
        return;
    }
    bool isMacroObject = (macroOffset != ERR_COULD_NOT_FIND_OBJECT);

    // Write header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_RESPAWN_INFO, true, PLMT_NONE);
    packet_write_int16(&p, gCurrCourseNum);
    packet_write_int16(&p, gCurrActStarNum);
    packet_write_int16(&p, gCurrLevelNum);
    packet_write_int16(&p, gCurrAreaIndex);

    // Write object info
    packet_write_uint8(&p, isMacroObject);
    packet_write_uint16(&p, isMacroObject ? macroOffset : spawnInfoIndex);
    packet_write_uint8(&p, respawnInfoBits);

    // Send the packet
    if (gNetworkType == NT_SERVER) {
        // Broadcast
        for (s32 i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected)                      { continue; }
            if (!np->currLevelSyncValid)             { continue; }
            if (np->currCourseNum != gCurrCourseNum) { continue; }
            if (np->currActNum != gCurrActStarNum)   { continue; }
            if (np->currLevelNum != gCurrLevelNum)   { continue; }
            if (np == gNetworkPlayerLocal)           { continue; }
            struct Packet p2 = { 0 };
            packet_duplicate(&p, &p2);
            network_send_to(np->localIndex, &p2);
            packet_clear(&p2);
            LOG_INFO("tx level respawn info to %d", np->globalIndex);
        }
    } else {
        network_send_to(gNetworkPlayerServer->localIndex, &p);
        LOG_INFO("tx level respawn info to %d", gNetworkPlayerServer->globalIndex);
    }
    packet_clear(&p);
}

void network_receive_level_respawn_info(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u16) + (sizeof(u8) * 2) + (sizeof(s16) * 4));
    
    LOG_INFO("rx level respawn info");

    // Read header
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);
    if (areaIndex >= MAX_AREAS) {
        LOG_ERROR("network_receive_level_respawn_info: Received area index is invalid");
        return;
    }

    // Read object info
    bool isMacroObject = packet_read_uint8(p);
    u16 offsetOrIndex = packet_read_uint16(p);
    u8 respawnInfoBits = packet_read_uint8(p);

    bool levelMismatch = (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum);
    if (gNetworkType == NT_SERVER) {
        // ensure we got the info from a valid player
        struct NetworkPlayer* npFrom = &gNetworkPlayers[p->localIndex];
        if (npFrom == NULL || npFrom->localIndex == UNKNOWN_LOCAL_INDEX || !npFrom->connected) {
            LOG_ERROR("Receiving 'level respawn info' from inactive player!");
            return;
        }

        // broadcast this change to the other players in that level
        for (s32 i = 1; i < MAX_PLAYERS; i++) {
            struct NetworkPlayer* np = &gNetworkPlayers[i];
            if (!np->connected) { continue; }
            if (!np->currLevelSyncValid) { continue; }
            if (np->currCourseNum != courseNum) { continue; }
            if (np->currActNum != actNum) { continue; }
            if (np->currLevelNum != levelNum) { continue; }
            if (np == npFrom) { continue; }
            struct Packet p2 = { 0 };
            packet_duplicate(p, &p2);
            network_send_to(np->localIndex, &p2);
            packet_clear(&p2);
        }

        // do not have the server apply the changes unless their level matches
        if (levelMismatch) { return; }
    } else if (levelMismatch) {
        LOG_ERROR("Receiving 'level respawn info' with the wrong location!");
        return;
    }

    if (isMacroObject) {
        s16* respawnInfo = get_respawn_info_from_macro_offset(areaIndex, offsetOrIndex);
        if (respawnInfo == NULL) {
            LOG_ERROR("Could not find respawn info from macro offset");
            return;
        }
        // apply the change
        *respawnInfo |= respawnInfoBits << 8;
    } else {
        u32* respawnInfo = get_respawn_info_from_spawn_info_index(areaIndex, offsetOrIndex);
        if (respawnInfo == NULL) {
            LOG_ERROR("Could not find respawn info from spawn info index");
            return;
        }
        // apply the change
        *respawnInfo |= respawnInfoBits << 8;
    }
    LOG_INFO("rx level respawn info (success!)");
}
