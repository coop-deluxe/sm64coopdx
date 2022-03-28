#include <stdio.h>
#include "../network.h"
#include "pc/lua/smlua_hooks.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_sync_valid(struct NetworkPlayer* toNp, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
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
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SYNC_VALID, true, PLMT_NONE);
    packet_write(&p, &courseNum,     sizeof(s16));
    packet_write(&p, &actNum,        sizeof(s16));
    packet_write(&p, &levelNum,      sizeof(s16));
    packet_write(&p, &areaIndex,     sizeof(s16));
    packet_write(&p, &myGlobalIndex, sizeof(u8));
    network_send_to(toNp->localIndex, &p);

    LOG_INFO("tx sync valid");
}

void network_receive_sync_valid(struct Packet* p) {
    LOG_INFO("rx sync valid");

    s16 courseNum, actNum, levelNum, areaIndex;
    u8 fromGlobalIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));
    packet_read(p, &fromGlobalIndex, sizeof(u8));

    if (gNetworkType != NT_SERVER) {
        extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
        if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || (areaIndex != gCurrAreaIndex && areaIndex != -1)) {
            LOG_ERROR("rx sync valid: received an improper location");
            return;
        }
    }

    struct NetworkPlayer* np = (gNetworkType != NT_SERVER) ? gNetworkPlayerLocal : &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving sync valid from inactive player!");
        return;
    }

    bool wasSyncValid = (np->currLevelSyncValid && np->currAreaSyncValid);
    np->currLevelSyncValid = true;
    np->currAreaSyncValid = true;

    if (np == gNetworkPlayerLocal && !wasSyncValid) {
        network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);
        smlua_call_event_hooks(HOOK_ON_SYNC_VALID);
    }

    // inform server
    if (fromGlobalIndex != gNetworkPlayerServer->globalIndex) {
        LOG_INFO("informing server of sync valid");
        network_send_sync_valid(gNetworkPlayerServer, courseNum, actNum, levelNum, areaIndex);
    }

    // we're no longer syncing
    gNetworkAreaSyncing = false;
}
