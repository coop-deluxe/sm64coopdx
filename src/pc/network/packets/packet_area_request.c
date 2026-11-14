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
    packet_write_uint8(&p, fromNp->globalIndex);
    packet_write_int16(&p, fromNp->currCourseNum);
    packet_write_int16(&p, fromNp->currActNum);
    packet_write_int16(&p, fromNp->currLevelNum);
    packet_write_int16(&p, fromNp->currAreaIndex);
    network_send_to(toNp->localIndex, &p);
    packet_clear(&p);
    LOG_INFO("tx area request");
}

void network_receive_area_request(struct Packet* p) {
    LOG_INFO("rx area request");
    
    if (p == NULL) {
        LOG_ERROR("rx area: The packet was NULL, Failed to handle the area request.");
        return;
    }
    
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
