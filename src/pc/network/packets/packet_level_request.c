#include <stdio.h>
#include "../network.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_level_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp) {
    gNetworkRequestLocationTimer = 0;
    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        // requesting server's level, send it immediately
        network_send_level(fromNp, false);
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_REQUEST, true, PLMT_NONE);
    packet_write(&p, &fromNp->globalIndex,       sizeof(u8));
    packet_write(&p, &fromNp->currCourseNum,     sizeof(s16));
    packet_write(&p, &fromNp->currActNum,        sizeof(s16));
    packet_write(&p, &fromNp->currLevelNum,      sizeof(s16));
    network_send_to(toNp->localIndex, &p);
    LOG_INFO("tx level request");
}

void network_receive_level_request(struct Packet* p) {
    LOG_INFO("rx level request");

    u8 globalIndex;
    s16 courseNum, actNum, levelNum;
    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &courseNum,   sizeof(s16));
    packet_read(p, &actNum,      sizeof(s16));
    packet_read(p, &levelNum,    sizeof(s16));

    struct NetworkPlayer* toNp = network_player_from_global_index(globalIndex);
    if (toNp == NULL || toNp->localIndex == UNKNOWN_LOCAL_INDEX || !toNp->connected) {
        LOG_ERROR("Receiving level request from inactive player!");
        if (toNp != NULL) { network_send_request_failed(toNp, 0); }
        return;
    }

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum) {
        LOG_ERROR("rx level request: received an improper location");
        if (toNp != NULL) { network_send_request_failed(toNp, 0); }
        return;
    }

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np == NULL || !np->currLevelSyncValid) {
        LOG_ERROR("rx level request: received when we're not synchronized");
        if (toNp != NULL) { network_send_request_failed(toNp, 0); }
        return;
    }

    // send level
    network_send_level(toNp, false);
}
