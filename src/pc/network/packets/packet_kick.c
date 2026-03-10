#include <stdio.h>
#include "../network.h"
#include "../moderation.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "pc/utils/misc.h"

f32 sLastReconnectTime = -9999999;
f32 sLastNotifyTime = -9999999;

void network_create_kick_popup(enum KickReasonType kickReason, char* reason) {
    char* text = NULL;

    switch (kickReason) {
        case EKT_FULL_PARTY:
            text = DLANG(NOTIF, DISCONNECT_FULL);
            break;
        case EKT_KICKED:
            if (reason && reason[0] != '\0') {
                text = DLANG(NOTIF, DISCONNECT_KICK_REASON);
            } else {
                text = DLANG(NOTIF, DISCONNECT_KICK);
            }
            break;
        case EKT_BANNED:
            if (reason && reason[0] != '\0') {
                text = DLANG(NOTIF, DISCONNECT_BAN_REASON);
            } else {
                text = DLANG(NOTIF, DISCONNECT_BAN);
            }
            break;
        default:
            text = DLANG(NOTIF, DISCONNECT_CLOSED);
            break;
    }

    char popupText[512] = { 0 };
    djui_language_replace(text, popupText, 512, '@', reason);
    djui_popup_create_auto_scaling(popupText, 1);
}

void network_send_kick(u8 localIndex, enum KickReasonType kickReason, char* reason) {
    u8 kickReasonType = kickReason;
    struct Packet p = { 0 };
    packet_init(&p, PACKET_KICK, true, PLMT_NONE);
    p.keepSendingAfterDisconnect = (kickReason == EKT_REJOIN);
    packet_write(&p, &kickReasonType, sizeof(u8));
    if (reason) {
        u16 reasonLength = strlen(reason);
        if (reasonLength >= MAX_REASON_LENGTH) reasonLength = MAX_REASON_LENGTH - 1;
        packet_write(&p, &reasonLength, sizeof(u16));
        packet_write(&p, reason, sizeof(u8) * reasonLength);
    } else {
        u16 reasonLength = 0;
        packet_write(&p, &reasonLength, sizeof(u16));
    }
    network_send_to(localIndex, &p);
}

void network_receive_kick(struct Packet* p) {
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("Kicking non-client... refuse!");
        return;
    }

    if (network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER && !gNetworkPlayers[p->localIndex].moderator) {
        LOG_ERROR("Kick came from non-server and non-moderator... refuse!");
        return;
    }

    u8 kickReasonType;
    u16 reasonLength = 0;
    char reason[MAX_REASON_LENGTH] = { 0 };
    packet_read(p, &kickReasonType, sizeof(u8));
    enum KickReasonType kickReason = kickReasonType;
    packet_read(p, &reasonLength, sizeof(u16));
    if (reasonLength >= MAX_REASON_LENGTH) reasonLength = MAX_REASON_LENGTH - 1;
    if (reasonLength > 0) packet_read(p, reason, sizeof(u8) * reasonLength);

    f32 now = clock_elapsed();
    if ((now - sLastNotifyTime) > 3) {
        sLastNotifyTime = now;
        network_create_kick_popup(kickReasonType, reason);
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
