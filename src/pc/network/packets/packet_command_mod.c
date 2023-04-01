#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/network/ban_list.h"
#include "pc/network/moderator_list.h"

bool gIsModerator = false;

void network_send_chat_command(u8 globalIndex, enum ChatConfirmCommand ccc) {
    if (gIsModerator) {
        u8 cccType = ccc;
        struct Packet p = { 0 };
        packet_init(&p, PACKET_COMMAND, false, PLMT_NONE);
        packet_write(&p, &globalIndex, sizeof(u8));
        packet_write(&p, &cccType, sizeof(u8));
        network_send_to(gNetworkPlayerServer->localIndex, &p);
    }
}

void network_recieve_chat_command(struct Packet *p) {
    if (!moderator_list_contains(gNetworkSystem->get_id_str(p->localIndex))) {
        return;
    }
    enum ChatConfirmCommand CCC;
    u8 player;
    packet_read(p, &player, sizeof(u8));
    packet_read(p, &CCC, sizeof(u8));
    if (gNetworkType == NT_SERVER && CCC == CCC_KICK) {
        struct NetworkPlayer *np = &gNetworkPlayers[player];
        if (!np->connected) {
            return;
        }
        network_send_kick(np->localIndex, EKT_KICKED);
        network_player_disconnected(np->localIndex);
        char message[256] = { 0 };
        snprintf(message, 256, "\\#fff982\\Kicked '%s%s\\#fff982\\'!",
                 network_get_player_text_color_string(np->localIndex), np->name);
        djui_chat_message_create(message);
    }
    if (gNetworkType == NT_SERVER && CCC == CCC_BAN) {
        struct NetworkPlayer *np = &gNetworkPlayers[player];
        if (!np->connected) {
            return;
        }
        network_send_kick(np->localIndex, EKT_BANNED);
        ban_list_add(gNetworkSystem->get_id_str(np->localIndex), false);
        network_player_disconnected(np->localIndex);
        char message[256] = { 0 };
        snprintf(message, 256, "\\#fff982\\Banned '%s%s\\#fff982\\'!",
                 network_get_player_text_color_string(np->localIndex), np->name);
        djui_chat_message_create(message);
    }
}

void network_send_moderator(u8 localIndex) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_MODERATOR, false, PLMT_NONE);
    network_send_to(localIndex, &p);
}

void network_recieve_moderator(struct Packet *p) {
    if ((gIsModerator) || (network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER)) {
        return;
    }

    gIsModerator = true;
    djui_chat_message_create(DLANG(CHAT, MOD_GRANTED));
}