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
    packet_write_uint8(&p, fromNp->globalIndex);
    packet_write_int16(&p, fromNp->currCourseNum);
    packet_write_int16(&p, fromNp->currActNum);
    packet_write_int16(&p, fromNp->currLevelNum);
    packet_write_int16(&p, fromNp->currAreaIndex);
    network_send_to(toNp->localIndex, &p);
    packet_clear(&p);
    LOG_INFO("tx level area request");
}

void network_receive_level_area_request(struct Packet* p) {
    LOG_INFO("rx level area request");
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + (sizeof(s16) * 4));

    u8 globalIndex = packet_read_uint8(p);
    s16 courseNum = packet_read_int16(p);
    s16 actNum = packet_read_int16(p);
    s16 levelNum = packet_read_int16(p);
    s16 areaIndex = packet_read_int16(p);

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
