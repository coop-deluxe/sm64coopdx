#include <stdio.h>
#include "../network.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;

void network_send_location_request_client(u8 destGlobalIndex, u8 srcGlobalIndex) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("client can't send a 'client location request'");
        return;
    }

    struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_client_location_request: dest np is invalid (global %d)", destGlobalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_REQUEST_CLIENT, true, false);
    packet_write(&p, &destGlobalIndex,       sizeof(u8));
    packet_write(&p, &destNp->currCourseNum, sizeof(s16));
    packet_write(&p, &destNp->currActNum,    sizeof(s16));
    packet_write(&p, &destNp->currLevelNum,  sizeof(s16));
    packet_write(&p, &destNp->currAreaIndex, sizeof(s16));

    struct NetworkPlayer* srcNp = network_player_from_global_index(srcGlobalIndex);
    if (srcNp == NULL || !srcNp->connected || !srcNp->currAreaSyncValid) {
        LOG_ERROR("network_send_client_location_request: source np is invalid (global %d)", srcGlobalIndex);
        return;
    }

    network_send_to(srcNp->localIndex, &p);
}

void network_receive_location_request_client(struct Packet* p) {
    if (gNetworkType == NT_SERVER) {
        LOG_ERROR("server is receiving a 'client location request'!");
        return;
    }

    u8 destGlobalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &destGlobalIndex, sizeof(u8));
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("Receiving 'client location request' with the wrong location!");
        return;
    }

    network_send_location_response(destGlobalIndex);
}
