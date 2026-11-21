#include <stdio.h>
#include "../network.h"
#include "pc/debuglog.h"
#include "pc/djui/djui.h"
#include "engine/math_util.h"

void network_send_global_chat_message(const char *message) {
    // get message length capped to the max chat message length
    u16 messageLength = min(strlen(message), MAX_CHAT_MSG_LENGTH - 1);

    // configure packet
    struct Packet p = { 0 };
    packet_init(&p, PACKET_GLOBAL_CHAT_MESSAGE, true, PLMT_NONE);
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, (char *)message, messageLength * sizeof(u8));

    // send off!
    network_send(&p);
}

void network_receive_global_chat_message(struct Packet *p) {
    u16 messageLength = 0;
    char message[MAX_CHAT_MSG_LENGTH] = { 0 };

    // read data
    packet_read(p, &messageLength, sizeof(u16));
    if (messageLength >= MAX_CHAT_MSG_LENGTH) { messageLength = MAX_CHAT_MSG_LENGTH - 1; }
    packet_read(p, message, messageLength * sizeof(u8));

    // show message
    djui_chat_message_create(message);
}
