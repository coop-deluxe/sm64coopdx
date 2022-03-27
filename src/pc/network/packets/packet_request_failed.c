#include <stdio.h>
#include "../network.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_request_failed(struct NetworkPlayer *toNp, u8 requestType) {
    if (gNetworkType == NT_SERVER && toNp == gNetworkPlayerLocal) {
        struct NetworkPlayer *np = gNetworkPlayerLocal;
        if (requestType == 0 && !np->currLevelSyncValid) {
            LOG_INFO("re-requesting level");
            network_send_change_level();
        } else if (requestType == 1 && (!np->currAreaSyncValid || !np->currLevelSyncValid)) {
            LOG_INFO("re-requesting area");
            network_send_change_area();
        }
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_REQUEST_FAILED, true, PLMT_NONE);
    packet_write(&p, &requestType, sizeof(u8));

    network_send_to(toNp->localIndex, &p);
    LOG_INFO("tx request failed");
}

void network_receive_request_failed(struct Packet *p) {
    LOG_INFO("rx request failed");

    u8 requestType;
    packet_read(p, &requestType, sizeof(u8));

    struct NetworkPlayer *np = gNetworkPlayerLocal;
    if (requestType == 0 && !np->currLevelSyncValid) {
        LOG_INFO("re-requesting level");
        network_send_change_level();
    } else if (requestType == 1 && (!np->currAreaSyncValid || !np->currLevelSyncValid)) {
        LOG_INFO("re-requesting area");
        network_send_change_area();
    }
}
