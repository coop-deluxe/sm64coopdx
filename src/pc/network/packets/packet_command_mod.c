#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui_language.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/network/ban_list.h"
#include "pc/network/moderator_list.h"
#include "pc/debuglog.h"

void network_send_chat_command(u8 globalIndex, enum ChatConfirmCommand ccc) {
    if (!gNetworkPlayers[0].moderator) return;

    u8 cccType = ccc; struct Packet p = { 0 };
    LOG_INFO("sending chat command to host with type: %d", cccType);
    packet_init(&p, PACKET_COMMAND, false, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &cccType, sizeof(u8));
    network_send_to(gNetworkPlayerServer->localIndex, &p);
}

void network_receive_chat_command(struct Packet *p) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("recieved chat command as non server");
        return;
    }

    if (!moderator_list_contains(gNetworkSystem->get_id_str(p->localIndex))) {
        LOG_ERROR("recieved moderator command from non moderator");
        return;
    }
    u8 CCC; u8 player;
    packet_read(p, &player, sizeof(u8));
    packet_read(p, &CCC, sizeof(u8));

    if (CCC != CCC_KICK && CCC != CCC_BAN) {
        LOG_ERROR("recieved an invalid chat command: %d", CCC);
        return;
    }

    struct NetworkPlayer *np = &gNetworkPlayers[player];
    if (!np->connected) {
        LOG_ERROR("recieved player that isn't connected");
        return;
    }
    char message[256] = { 0 };
    if (CCC == CCC_KICK) {
        network_send_kick(np->localIndex, EKT_KICKED);
        snprintf(message, 256, "\\#fff982\\Kicked '%s%s\\#fff982\\'!", network_get_player_text_color_string(np->localIndex), np->name);
    }
    if (CCC == CCC_BAN) {
        network_send_kick(np->localIndex, EKT_BANNED);
        ban_list_add(gNetworkSystem->get_id_str(np->localIndex), false);
        snprintf(message, 256, "\\#fff982\\Banned '%s%s\\#fff982\\'!", network_get_player_text_color_string(np->localIndex), np->name);
    }
    network_player_disconnected(np->localIndex);
    djui_chat_message_create(message);
}

void network_send_moderator(u8 localIndex) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_MODERATOR, false, PLMT_NONE);
    network_send_to(localIndex, &p);
}

void network_receive_moderator(struct Packet *p) {
    if (gNetworkPlayers[0].moderator || (network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER)) return;
    gNetworkPlayers[0].moderator = true;
    djui_chat_message_create(DLANG(CHAT, MOD_GRANTED));
}
