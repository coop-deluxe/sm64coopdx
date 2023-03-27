#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

void network_send_chat(char* message, u8 globalIndex) {
    u16 messageLength = strlen(message);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHAT, true, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, message, messageLength * sizeof(u8));
    network_send(&p);
}

void network_receive_chat(struct Packet* p) {
    u16 remoteMessageLength = 0;
    char remoteMessage[256] = { 0 };
    u8 globalIndex;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &remoteMessageLength, sizeof(u16));
    if (remoteMessageLength >= 255) { remoteMessageLength = 255; }
    packet_read(p, &remoteMessage, remoteMessageLength * sizeof(u8));

    // anti spoof
    if (packet_spoofed(p, globalIndex)) {
        LOG_ERROR("rx spoofed chat");
        return;
    }

    // add the message
    djui_chat_message_create_from(globalIndex, remoteMessage);
    LOG_INFO("rx chat: %s", remoteMessage);
}
