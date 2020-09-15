#include <stdio.h>
#include "../network.h"
#include "game/chat.h"

static u8 localChatId = 1;

// two-player hack: the remoteChatIds stuff is only valid for the one remote player
// will need to be extended if MAX_PLAYERS is ever increased
#define MAX_CHAT_IDS 16
static u8 remoteChatIds[MAX_CHAT_IDS] = { 0 };
static u8 onRemoteChatId = 0;

void network_send_chat(char* message) {
    u16 messageLength = strlen(message);
    struct Packet p;
    packet_init(&p, PACKET_CHAT, true);
    packet_write(&p, &localChatId, sizeof(u8));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, message, messageLength * sizeof(u8));

    network_send(&p);
    localChatId++;
}

void network_receive_chat(struct Packet* p) {
    u8 remoteChatId = 0;
    u16 remoteMessageLength = 0;
    char remoteMessage[255] = { 0 };

    packet_read(p, &remoteChatId, sizeof(u8));
    packet_read(p, &remoteMessageLength, sizeof(u16));
    if (remoteMessageLength > 255) { remoteMessageLength = 254; }
    packet_read(p, &remoteMessage, remoteMessageLength * sizeof(u8));

    // check if remote chat id has already been seen
    for (u16 i = 0; i < MAX_CHAT_IDS; i++) {
        if (remoteChatIds[i] == remoteChatId) {
            // we already saw this message!
            return;
        }
    }

    // cache the seen id
    remoteChatIds[onRemoteChatId] = remoteChatId;
    onRemoteChatId = (onRemoteChatId + 1) % MAX_CHAT_IDS;

    // add the message
    chat_add_message(remoteMessage, FALSE);

    return;
}
