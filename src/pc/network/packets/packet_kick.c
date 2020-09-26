#include <stdio.h>
#include "../network.h"
#include "menu/custom_menu_system.h"
#include "pc/debuglog.h"

void network_send_kick(enum KickReasonType kickReason) {
    struct Packet p;
    packet_init(&p, PACKET_KICK, false, false);
    packet_write(&p, &kickReason, sizeof(enum KickReasonType));
    network_send_to(0, &p);
}

void network_receive_kick(struct Packet* p) {
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("Kicking non-client... refuse!");
        return;
    }

    if (network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER) {
        LOG_ERROR("Kick came from non-server... refuse!");
        return;
    }

    enum KickReasonType kickReason;
    packet_read(p, &kickReason, sizeof(enum KickReasonType));
    switch (kickReason) {
        case EKT_FULL_PARTY: custom_menu_error("The party is full.");              break;
        default:             custom_menu_error("Host has closed the connection."); break;
    }
    network_shutdown();
}
