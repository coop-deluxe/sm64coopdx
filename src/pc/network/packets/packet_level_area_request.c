#include <stdio.h>
#include "../network.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_level_area_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp) {
    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        // requesting server's level area, send it immediately
        network_send_level(fromNp, true);
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_AREA_REQUEST, true, PLMT_NONE);
    packet_write(&p, &fromNp->globalIndex,       sizeof(u8));
    packet_write(&p, &fromNp->currCourseNum,     sizeof(s16));
    packet_write(&p, &fromNp->currActNum,        sizeof(s16));
    packet_write(&p, &fromNp->currLevelNum,      sizeof(s16));
    packet_write(&p, &fromNp->currAreaIndex,     sizeof(s16));
    network_send_to(toNp->localIndex, &p);
    LOG_INFO("tx level area request");
}

void network_receive_level_area_request(struct Packet* p) {
    LOG_INFO("rx level area request");

    u8 globalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &courseNum,   sizeof(s16));
    packet_read(p, &actNum,      sizeof(s16));
    packet_read(p, &levelNum,    sizeof(s16));
    packet_read(p, &areaIndex,   sizeof(s16));

    struct NetworkPlayer* toNp = network_player_from_global_index(globalIndex);
    if (toNp == NULL || toNp->localIndex == UNKNOWN_LOCAL_INDEX || !toNp->connected) {
        LOG_ERROR("Receiving level area request from inactive player!");
        if (toNp != NULL) { network_send_request_failed(toNp, 1); }
        return;
    }

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("rx level area request: received an improper location");
        if (toNp != NULL) { network_send_request_failed(toNp, 1); }
        return;
    }

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np == NULL || !np->currAreaSyncValid || !np->currLevelSyncValid) {
        LOG_ERROR("rx level area request: received when we're not synchronized");
        if (toNp != NULL) { network_send_request_failed(toNp, 1); }
        return;
    }

    // send level area
    network_send_level(toNp, true);
}
