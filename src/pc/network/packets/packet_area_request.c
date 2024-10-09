#include <stdio.h>
#include "../network.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_area_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp) {
    gNetworkRequestLocationTimer = 0;
    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        // requesting server's area, send it immediately
        network_send_area(fromNp);
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_AREA_REQUEST, true, PLMT_NONE);
    packet_write(&p, &fromNp->globalIndex,       sizeof(u8));
    packet_write(&p, &fromNp->currCourseNum,     sizeof(s16));
    packet_write(&p, &fromNp->currActNum,        sizeof(s16));
    packet_write(&p, &fromNp->currLevelNum,      sizeof(s16));
    packet_write(&p, &fromNp->currAreaIndex,     sizeof(s16));
    network_send_to(toNp->localIndex, &p);
    LOG_INFO("tx area request");
}

void network_receive_area_request(struct Packet* p) {
    LOG_INFO("rx area request");

    u8 globalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &courseNum,   sizeof(s16));
    packet_read(p, &actNum,      sizeof(s16));
    packet_read(p, &levelNum,    sizeof(s16));
    packet_read(p, &areaIndex,   sizeof(s16));

    struct NetworkPlayer* toNp = network_player_from_global_index(globalIndex);
    if (toNp == NULL || toNp->localIndex == UNKNOWN_LOCAL_INDEX || !toNp->connected) {
        LOG_ERROR("Receiving area request from inactive player!");
        return;
    }

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("rx area request: received an improper location");
        return;
    }

    // send area
    network_send_area(toNp);
}
