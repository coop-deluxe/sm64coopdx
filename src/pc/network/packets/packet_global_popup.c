#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

void network_send_global_popup(const char* message, int lines) {
    // get message length
    u16 messageLength = strlen(message);

    // configure packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_GLOBAL_POPUP, true, PLMT_NONE);
    packet_write(&p, &lines, sizeof(int));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, (char*)message, messageLength * sizeof(u8));
    
    // send the packet
    network_send(&p);
}

void network_receive_global_popup(struct Packet* p) {
    
    u16 messageLength = 0;
    char message[256] = { 0 };
    int lines;

    // read data
    packet_read(p, &lines, sizeof(int));
    packet_read(p, &messageLength, sizeof(u16));
    if (messageLength >= 255) { messageLength = 255; }
    packet_read(p, message, messageLength * sizeof(u8));
    // show popup
    djui_popup_create(message, lines);

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (gNetworkSystem && gNetworkSystem->get_id_str && np->connected && strlen(np->name) > 0) {
        LOG_CONSOLE("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
        LOG_INFO("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
    } else {
        LOG_INFO("rx popup: %s", message);
    }
}