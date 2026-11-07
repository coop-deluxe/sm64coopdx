#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

void network_send_global_popup(const char* message, s32 lines) {
    // Get message length
    u16 messageLength = strlen(message);
    if (messageLength >= 255) { messageLength = 255; }

    // Configure packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_GLOBAL_POPUP, true, PLMT_NONE);
    packet_write_int32(&p, lines);
    packet_write_uint16(&p, messageLength);
    packet_write(&p, (char*)message, messageLength * sizeof(u8));

    // Send the packet
    network_send(&p);
    
    packet_clear(&p);
}

void network_receive_global_popup(struct Packet* p) {
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(s32) + sizeof(u16));

    char message[256] = { 0 };

    // Read data
    s32 lines = packet_read_int32(p);
    u16 messageLength = packet_read_uint16(p);
    if (messageLength >= 255) { messageLength = 255; }
    packet_read(p, message, messageLength * sizeof(u8));
    
    // Show popup
    djui_popup_create(message, lines);

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (gNetworkSystem && gNetworkSystem->get_id_str && np->connected && strlen(np->name) > 0) {
        LOG_CONSOLE("[%s] %s\\#\\: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
        LOG_INFO("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, message);
    } else {
        LOG_INFO("rx popup: %s", message);
    }
}