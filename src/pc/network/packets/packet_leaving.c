#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"

void network_send_leaving(u8 globalIndex) {
    if (gNetworkPlayerLocal == NULL) {
        LOG_ERROR("Local network player not initialized.");
        return;
    }

    if (gNetworkType != NT_SERVER) {
        if (gNetworkPlayerServer == NULL) {
            LOG_ERROR("Server network player not initialized.");
            return;
        }

        globalIndex = gNetworkPlayerLocal->globalIndex;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEAVING, true, PLMT_NONE);
    packet_write_uint8(&p, globalIndex);
    if (gNetworkType == NT_SERVER) {
        network_send(&p);
    } else {
        network_send_to(gNetworkPlayerServer->localIndex, &p);
    }
    LOG_INFO("Sending leaving event for %d", globalIndex);
    packet_clear(&p);
}

void network_receive_leaving(struct Packet* p) {
    if (gNetworkType != NT_SERVER && network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER) {
        LOG_ERROR("Leaving came from non-server... refuse!");
        return;
    }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8));

    u8 globalIndex = packet_read_uint8(p);

    LOG_INFO("Received leaving event for %d", globalIndex);
    network_player_disconnected(globalIndex);
}
