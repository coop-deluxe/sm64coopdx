#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"

void network_send_kick(enum KickReasonType kickReason) {
    u8 kickReasonType = kickReason;
    struct Packet p;
    packet_init(&p, PACKET_KICK, false, false);
    packet_write(&p, &kickReasonType, sizeof(u8));
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

    u8 kickReasonType;
    packet_read(p, &kickReasonType, sizeof(u8));
    enum KickReasonType kickReason = kickReasonType;

    switch (kickReason) {
        case EKT_FULL_PARTY: djui_show_popup("The party is full.");              break;
        default:             djui_show_popup("Host has closed the connection."); break;
    }
    network_shutdown();
}
