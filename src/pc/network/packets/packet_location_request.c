#include <stdio.h>
#include "../network.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;

void network_send_location_request(void) {
    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* np = get_network_player_from_valid_location(gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex);
        if (np == NULL) {
            gNetworkPlayerLocal->currAreaSyncValid = true;
            return;
        }
        network_send_location_request_client(gNetworkPlayerLocal->globalIndex, np->globalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_REQUEST, true, false);
    packet_write(&p, &gCurrCourseNum,     sizeof(s16));
    packet_write(&p, &gCurrActNum,        sizeof(s16));
    packet_write(&p, &gCurrLevelNum,      sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,     sizeof(s16));
    network_send_to(0, &p);
}

void network_receive_location_request(struct Packet* p) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("non-server is receiving a location request!");
        return;
    }

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving location request from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    np->currCourseNum     = courseNum;
    np->currActNum        = actNum;
    np->currLevelNum      = levelNum;
    np->currAreaIndex     = areaIndex;
    np->currAreaSyncValid = false;

    struct NetworkPlayer* np2 = get_network_player_from_valid_location(courseNum, actNum, levelNum, areaIndex);
    if (np2 == NULL) {
        network_send_level_area_valid(np->globalIndex);
    } else if (np2 == gNetworkPlayerLocal) {
        network_send_location_response(np->globalIndex);
    } else {
        network_send_location_request_client(np->globalIndex, np2->globalIndex);
    }
}
