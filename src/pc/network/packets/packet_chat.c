#include <stdio.h>
#include "../network.h"
#include "game/chat.h"

void network_send_chat(char* message) {
    u16 messageLength = strlen(message);
    struct Packet p;
    packet_init(&p, PACKET_CHAT, true, false);
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, message, messageLength * sizeof(u8));
    network_send(&p);
}

void network_receive_chat(struct Packet* p) {
    u16 remoteMessageLength = 0;
    char remoteMessage[255] = { 0 };

    packet_read(p, &remoteMessageLength, sizeof(u16));
    if (remoteMessageLength > 255) { remoteMessageLength = 254; }
    packet_read(p, &remoteMessage, remoteMessageLength * sizeof(u8));

    // add the message
    chat_add_message(remoteMessage, CMT_REMOTE);
}
