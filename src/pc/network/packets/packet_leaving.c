#include <stdio.h>
#include "../network.h"
#include "pc/log.h"

void network_send_leaving(u8 globalIndex) {
    log_context_begin(LOG_CTX_NETWORK);
    if (gNetworkPlayerLocal == NULL) {
        LOG_ERROR_VERBOSE("Local network player not initialized.");
        log_context_end(LOG_CTX_NETWORK);
        return;
    }

    if (gNetworkType != NT_SERVER) {
        if (gNetworkPlayerServer == NULL) {
            LOG_ERROR_VERBOSE("Server network player not initialized.");
            log_context_end(LOG_CTX_NETWORK);
            return;
        }

        globalIndex = gNetworkPlayerLocal->globalIndex;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEAVING, true, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(u8));
    if (gNetworkType == NT_SERVER) {
        network_send(&p);
    } else {
        network_send_to(gNetworkPlayerServer->localIndex, &p);
    }
    LOG_DEBUG_VERBOSE("Sending leaving event for %d", globalIndex);
    log_context_end(LOG_CTX_NETWORK);
}

void network_receive_leaving(struct Packet* p) {
    if (gNetworkType != NT_SERVER && network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER) {
        LOG_ERROR("Leaving came from non-server... refuse!");
        return;
    }

    u8 globalIndex = 0;
    packet_read(p, &globalIndex, sizeof(u8));

    LOG_DEBUG_VERBOSE("Received leaving event for %d", globalIndex);
    network_player_disconnected(globalIndex);
}
