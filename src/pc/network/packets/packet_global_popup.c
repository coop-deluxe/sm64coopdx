#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "engine/math_util.h"

void network_send_global_popup(const char *message, int lines) {
    // get message length capped to max popup message length
    u16 messageLength = min(strlen(message), MAX_GLOBAL_POPUP_MESSAGE_LENGTH - 1);

    // configure packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_GLOBAL_POPUP, true, PLMT_NONE);
    packet_write(&p, &lines, sizeof(int));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, (char *)message, messageLength * sizeof(u8));

    // send the packet
    network_send(&p);
}

void network_receive_global_popup(struct Packet *p) {
    u16 messageLength = 0;
    char message[MAX_GLOBAL_POPUP_MESSAGE_LENGTH] = { 0 };
    int lines;

    // read data
    packet_read(p, &lines, sizeof(int));
    packet_read(p, &messageLength, sizeof(u16));
    if (messageLength >= MAX_GLOBAL_POPUP_MESSAGE_LENGTH) { messageLength = MAX_GLOBAL_POPUP_MESSAGE_LENGTH - 1; }
    packet_read(p, message, messageLength * sizeof(u8));

    // show popup
    djui_popup_create(message, lines);

    // log popup creation
    struct NetworkPlayer *np = &gNetworkPlayers[p->localIndex];
    if (gNetworkSystem && gNetworkSystem->get_id_str && np->connected && strlen(np->name) > 0) {
        LOG_CONSOLE("[%s] %s\\#\\: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
        LOG_INFO("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
    } else {
        LOG_INFO("rx popup: %s", message);
    }
}
