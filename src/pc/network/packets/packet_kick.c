#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "pc/utils/misc.h"

f32 sLastReconnectTime = -9999999;
f32 sLastNotifyTime = -9999999;

void network_send_kick(u8 localIndex, enum KickReasonType kickReason) {
    u8 kickReasonType = kickReason;
    struct Packet p = { 0 };
    packet_init(&p, PACKET_KICK, true, PLMT_NONE);
    p.keepSendingAfterDisconnect = (kickReason == EKT_REJOIN);
    packet_write_uint8(&p, kickReasonType);
    network_send_to(localIndex, &p);
    packet_clear(&p);
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
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8));

    enum KickReasonType kickReason = packet_read_uint8(p);

    f32 now = clock_elapsed();
    if ((now - sLastNotifyTime) > 3) {
        sLastNotifyTime = now;
        switch (kickReason) {
            case EKT_FULL_PARTY: djui_popup_create(DLANG(NOTIF, DISCONNECT_FULL),   1); break;
            case EKT_KICKED:     djui_popup_create(DLANG(NOTIF, DISCONNECT_KICK),   1); break;
            case EKT_BANNED:     djui_popup_create(DLANG(NOTIF, DISCONNECT_BAN),    1); break;
            default:             djui_popup_create(DLANG(NOTIF, DISCONNECT_CLOSED), 1); break;
        }
    }

    if (kickReason == EKT_REJOIN) {
        if ((now - sLastReconnectTime) > 3) {
            sLastReconnectTime = now;
            network_reconnect_begin();
            djui_popup_create(DLANG(NOTIF, DISCONNECT_REJOIN), 1);
        }
    } else {
        network_shutdown(false, false, false, false);
    }
}
