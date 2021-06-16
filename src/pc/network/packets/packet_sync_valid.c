#include <stdio.h>
#include "../network.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_sync_valid(struct NetworkPlayer* toNp) {
    // set the NetworkPlayers sync valid
    toNp->currLevelSyncValid = true;
    toNp->currAreaSyncValid  = true;

    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        // the player is the server, no need to send sync valid
        gNetworkAreaSyncing = false;

        // but we do need to send level area inform
        network_send_level_area_inform(toNp);
        return;
    }

    u8 myGlobalIndex = gNetworkPlayerLocal->globalIndex;
    struct Packet p;
    packet_init(&p, PACKET_SYNC_VALID, true, false);
    packet_write(&p, &toNp->currCourseNum, sizeof(s16));
    packet_write(&p, &toNp->currActNum,    sizeof(s16));
    packet_write(&p, &toNp->currLevelNum,  sizeof(s16));
    packet_write(&p, &toNp->currAreaIndex, sizeof(s16));
    packet_write(&p, &myGlobalIndex,       sizeof(u8));
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
        if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
            LOG_ERROR("rx sync valid: received an improper location");
            return;
        }
    }

    struct NetworkPlayer* np = (gNetworkType != NT_SERVER) ? gNetworkPlayerLocal : &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving sync valid from inactive player!");
        return;
    }

    np->currLevelSyncValid = true;
    np->currAreaSyncValid = true;

    // inform server
    if (fromGlobalIndex != gNetworkPlayerServer->globalIndex) {
        LOG_INFO("informing server of sync valid");
        network_send_sync_valid(gNetworkPlayerServer);
    }

    // inform everyone that this player is valid
    if (gNetworkType == NT_SERVER) {
        network_send_level_area_inform(np);
    }

    // we're no longer syncing
    gNetworkAreaSyncing = false;
}
