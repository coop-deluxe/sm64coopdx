#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "pc/utils/misc.h"

f32 lastReconnectTime = -9999999;

void network_send_kick(u8 localIndex, enum KickReasonType kickReason) {
    u8 kickReasonType = kickReason;
    struct Packet p = { 0 };
    packet_init(&p, PACKET_KICK, true, PLMT_NONE);
    p.keepSendingAfterDisconnect = (kickReason == EKT_REJOIN);
    packet_write(&p, &kickReasonType, sizeof(u8));
    network_send_to(localIndex, &p);
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
        case EKT_FULL_PARTY: djui_popup_create("\\#ffa0a0\\Disconnected:\\#c8c8c8\\ The party is full.", 1);              break;
        case EKT_KICKED:     djui_popup_create("\\#ffa0a0\\Disconnected:\\#c8c8c8\\ The server kicked you.", 1);          break;
        case EKT_BANNED:     djui_popup_create("\\#ffa0a0\\Disconnected:\\#c8c8c8\\ The server banned you.", 1);          break;
        case EKT_REJOIN:     djui_popup_create("\\#ffa0a0\\Disconnected:\\#c8c8c8\\ Rejoining...", 1);                    break;
        default:             djui_popup_create("\\#ffa0a0\\Disconnected:\\#c8c8c8\\ Host has closed the connection.", 1); break;
    }

    if (kickReason == EKT_REJOIN) {
        f32 now = clock_elapsed();
        if ((now - lastReconnectTime) > 3) {
            lastReconnectTime = now;
            network_reconnect_begin();
        }
    } else {
        network_shutdown(false, false, false);
    }
}
