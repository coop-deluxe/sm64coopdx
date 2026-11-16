#include <stdio.h>
#include "../network.h"
#include "pc/lua/smlua_hooks.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_sync_valid(struct NetworkPlayer* toNp, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex, bool informServer) {
    bool wasSyncValid = (toNp->currLevelSyncValid && toNp->currAreaSyncValid);

    // set the NetworkPlayers sync valid
    toNp->currLevelSyncValid = true;
    toNp->currAreaSyncValid  = true;

    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        // the player is the server, no need to send sync valid
        gNetworkAreaSyncing = false;

        // call hooks
        if (!wasSyncValid) {
            network_player_update_course_level(toNp, courseNum, actNum, levelNum, areaIndex);
            smlua_call_event_hooks(HOOK_ON_SYNC_VALID);
        }
        return;
    }

    u8 myGlobalIndex = gNetworkPlayerLocal->globalIndex;
    u8 forGlobalIndex = toNp->globalIndex;
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SYNC_VALID, true, PLMT_NONE);
    packet_write_int16(&p, courseNum);
    packet_write_int16(&p, actNum);
    packet_write_int16(&p, levelNum);
    packet_write_int16(&p, areaIndex);
    packet_write_uint8(&p, myGlobalIndex);
    packet_write_uint8(&p, forGlobalIndex);
    network_send_to((informServer ? gNetworkPlayerServer->localIndex : toNp->localIndex), &p);
    packet_clear(&p);

    LOG_INFO("tx sync valid");
}

void network_receive_sync_valid(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * 2) + (sizeof(s16) * 4));
    
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);
    u8 fromGlobalIndex = packet_read_uint8(p);
    u8 forGlobalIndex = packet_read_uint8(p);

    LOG_INFO("rx sync valid: from global %d, for global %d", fromGlobalIndex, forGlobalIndex);

    bool isOurSyncValid = (forGlobalIndex == gNetworkPlayerLocal->globalIndex);
    if (isOurSyncValid) {
        extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
        if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || (areaIndex != gCurrAreaIndex && areaIndex != -1)) {
            LOG_ERROR("rx sync valid: received an improper location");
            return;
        }
    }

    struct NetworkPlayer* np = network_player_from_global_index(forGlobalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving sync valid from inactive player!");
        return;
    }

    bool wasSyncValid = (np->currLevelSyncValid && np->currAreaSyncValid);
    np->currLevelSyncValid = true;
    np->currAreaSyncValid = true;

    if (isOurSyncValid && !wasSyncValid) {
        network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);
        smlua_call_event_hooks(HOOK_ON_SYNC_VALID);
    }

    // inform server
    if (gNetworkType != NT_SERVER && fromGlobalIndex != gNetworkPlayerServer->globalIndex) {
        LOG_INFO("informing server of sync valid");
        network_send_sync_valid(np, courseNum, actNum, levelNum, areaIndex, true);
    }

    // we're no longer syncing
    gNetworkAreaSyncing = false;
}
