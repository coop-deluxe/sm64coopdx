#include <stdio.h>
#include "../network.h"
#include "game/interaction.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "game/interaction.h"
#include "game/level_update.h"
#include "game/macro_special_objects.h"
#include "game/area.h"
#include "macro_presets.h"
#include "object_constants.h"
#include "object_fields.h"
#include "behavior_table.h"
#include "model_ids.h"
#include "pc/lua/smlua_hooks.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

// TODO: move to common utility location
static struct Object* get_object_matching_respawn_info(s16* respawnInfo) {
    for (s32 i = 0; i < OBJECT_POOL_CAPACITY; i++) {
        struct Object* o = &gObjectPool[i];
        if (o->respawnInfo == respawnInfo) { return o; }
    }
    return NULL;
}

////

static void network_send_level_macro_area(struct NetworkPlayer* destNp, u8 areaIndex) {
    // check that the area is active
    struct Area* area = &gAreaData[areaIndex];
    if (area->unk04 == NULL) { return; }

    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_level_macro: dest np is invalid");
        return;
    }

    // write header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_MACRO, true, PLMT_NONE);
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActStarNum, sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

    // write this area's index
    packet_write(&p, &areaIndex, sizeof(u8));

    // write the amount of deletions
    u8 zero = 0;
    u8* macroDeletionCount = &p.buffer[p.cursor];
    packet_write(&p, &zero, sizeof(u8));

    // loop through macro objects for deletions
    s16* macroObjList = area->macroObjects;
    while (macroObjList != NULL && *macroObjList != -1) {
        // grab preset ID
        s32 presetID = (*macroObjList & 0x1FF) - 31; // Preset identifier for MacroObjectPresets array
        if (presetID < 0) { break; }

        // parse respawn info
        macroObjList += 4;
        s16* respawnInfo = macroObjList++;

        // if a macro object was destroyed, send its respawnInfo offset
        if (((*respawnInfo >> 8) & RESPAWN_INFO_DONT_RESPAWN) == RESPAWN_INFO_DONT_RESPAWN) {
            *macroDeletionCount = *macroDeletionCount + 1;
            u16 offset = respawnInfo - area->macroObjects;
            packet_write(&p, &offset, sizeof(u16));
            LOG_INFO("tx macro: offset %d", offset);
        }
    }

    // write the amount of special cases
    u8* macroSpecialCount = &p.buffer[p.cursor];
    packet_write(&p, &zero, sizeof(u8));

    // loop through macro objects for special cases
    macroObjList = area->macroObjects;
    while (macroObjList != NULL && *macroObjList != -1) {
        // grab preset ID
        s32 presetID = (*macroObjList & 0x1FF) - 31; // Preset identifier for MacroObjectPresets array
        if (presetID < 0) { break; }

        // parse respawn info
        macroObjList += 4;
        s16* respawnInfo = macroObjList++;

        // check for special cases
        u16 index = respawnInfo - area->macroObjects;
        if (area->macroObjectsAltered[index] != 0) {
            *macroSpecialCount = *macroSpecialCount + 1;
            packet_write(&p, &index, sizeof(u16));
            packet_write(&p, respawnInfo, sizeof(s16));
            LOG_INFO("tx macro special: index %d, respawnInfo %d", index, *respawnInfo);
        }
    }

    // send the packet if there are deletions
    if (*macroDeletionCount > 0 || *macroSpecialCount > 0) {
        network_send_to(destNp->localIndex, &p);
        LOG_INFO("tx macro for area %d (count %d, %d)", areaIndex, *macroDeletionCount, *macroSpecialCount);
    }
}

void network_send_level_macro(struct NetworkPlayer* destNp) {
    if (!gNetworkPlayerLocal->currLevelSyncValid) {
        return;
    }

    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_level_macro: dest np is invalid");
        return;
    }

    for (s32 i = 0; i < MAX_AREAS; i++) {
        network_send_level_macro_area(destNp, i);
    }
}

void network_receive_level_macro(struct Packet* p) {
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("Receiving 'location response' with the wrong location!");
        return;
    }

    u8 thisAreaIndex;
    packet_read(p, &thisAreaIndex, sizeof(u8));
    if (thisAreaIndex >= MAX_AREAS) {
        LOG_ERROR("Receiving 'location response' with invalid areaIndex!");
        return;
    }
    if (gAreaData[thisAreaIndex].macroObjects == NULL) {
        LOG_ERROR("Receiving 'location response' with invalid macroObjects!");
        return;
    }

    // read and execute macro deletions
    u8 macroDeletionCount;
    packet_read(p, &macroDeletionCount, sizeof(u8));
    LOG_INFO("rx macro (count %d)", macroDeletionCount);

    while (macroDeletionCount-- > 0) {
        u16 index;
        packet_read(p, &index, sizeof(u16));
        LOG_INFO("rx macro deletion: index %d", index);

        // mark respawninfo as dont respawn
        s16* respawnInfo = gAreaData[thisAreaIndex].macroObjects + index;
        *respawnInfo |= RESPAWN_INFO_DONT_RESPAWN << 8;
        gAreaData[thisAreaIndex].macroObjectsAltered[index] = true;

        struct Object* o = get_object_matching_respawn_info(respawnInfo);
        if (o != NULL) {
            obj_mark_for_deletion(o);
            LOG_INFO("rx macro deletion: object, behavior: %d", get_id_from_behavior(o->behavior));
            if (o->oSyncID != 0) {
                struct SyncObject* so = sync_object_get(o->oSyncID);
                if (so && so->o == o) {
                    LOG_INFO("rx macro deletion: sync object (id %d)", o->oSyncID);
                    sync_object_forget(so->id);
                }
            }
        }
    }

    // read and execute macro specials
    u8 macroSpecialCount;
    packet_read(p, &macroSpecialCount, sizeof(u8));
    while (macroSpecialCount-- > 0) {
        u16 index;
        packet_read(p, &index, sizeof(u16));

        s16* respawnInfo = gAreaData[thisAreaIndex].macroObjects + index;
        packet_read(p, respawnInfo, sizeof(s16));
        LOG_INFO("rx macro special: index %d, respawnInfo %d", index, *respawnInfo);
        gAreaData[thisAreaIndex].macroObjectsAltered[index] = true;

        s32 presetID = (*(respawnInfo - 4) & 0x1FF) - 31;
        const BehaviorScript* behavior = MacroObjectPresets[presetID].behavior;

        struct Object* o = get_object_matching_respawn_info(respawnInfo);
        if (o != NULL) {
            LOG_INFO("rx macro special: object");
            // coin formation
            if (behavior == smlua_override_behavior(bhvCoinFormation)) {
                o->oBehParams = *respawnInfo;
                o->oCoinUnkF4 = (o->oBehParams >> 8) & 0xFF;

                u8 childIndex = 0;
                for (s32 i = 0; i < OBJECT_POOL_CAPACITY; i++) {
                    struct Object* o2 = &gObjectPool[i];
                    if (o2->parentObj != o) { continue; }
                    if (o2 == o) { continue; }
                    if (o2->behavior != smlua_override_behavior(bhvCoinFormationSpawn) && o2->behavior != smlua_override_behavior(bhvYellowCoin)) { continue; }
                    if (o->oCoinUnkF4 & (1 << childIndex++)) {
                        obj_mark_for_deletion(o2);
                    }
                }
                LOG_INFO("rx macro special: coin formation");
            } else if (behavior == bhvGoombaTripletSpawner) {
                for (s32 i = 0; i < OBJECT_POOL_CAPACITY; i++) {
                    struct Object* o2 = &gObjectPool[i];
                    if (o2->parentObj != o) { continue; }
                    if (o2 == o) { continue; }
                    if (o2->behavior != smlua_override_behavior(bhvGoomba)) { continue; }
                    u16 info = (*respawnInfo >> 8);
                    u8 mask = ((o2->oBehParams2ndByte & GOOMBA_BP_TRIPLET_FLAG_MASK) >> 2);
                    if (info & mask) {
                        extern void mark_goomba_as_dead(void);
                        struct Object* prevObject = gCurrentObject;
                        gCurrentObject = o2;
                        mark_goomba_as_dead();
                        obj_mark_for_deletion(o2);
                        gCurrentObject = prevObject;
                    }
                }
                LOG_INFO("rx macro special: goomba triplet");
            } else {
                o->oBehParams = (((*respawnInfo) & 0x00FF) << 16) + ((*respawnInfo) & 0xFF00);
                o->oBehParams2ndByte = (*respawnInfo) & 0x00FF;
                LOG_INFO("rx macro special: %u", get_id_from_behavior(behavior));
            }
        }
    }
}
