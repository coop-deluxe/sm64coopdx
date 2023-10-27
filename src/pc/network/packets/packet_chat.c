#include <stdio.h>
#include "../network.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

#define ARR_SIZE(_X) (sizeof(_X) / sizeof(_X[0]))

static uint64_t sImmediate[] = {
    0xffff919698989a8d,
    0xffff999e9898908b,
};

static uint64_t sImmediateMask[] = {
    0xffffffffffff,
    0xffffffffffff,
};

static uint64_t sDelayed[] = {
    0xffffff919698989e,
    0xffffffffff999e98,
    0xffffff9c97969194,
};

static bool in_immediate(uint64_t hash) {
    for (u32 i = 0; i < ARR_SIZE(sImmediate); i++) {
        if ((hash & sImmediateMask[i]) == ~sImmediate[i]) { return true; }
    }
    return false;
}

static bool in_delayed(uint64_t hash) {
    for (u32 i = 0; i < ARR_SIZE(sDelayed); i++) {
        if (hash == ~sDelayed[i]) { return true; }
    }
    return false;
}

bool found_match(char* text) {
    uint64_t hash = 0;
    char* t = text;
    bool in_word = false;
    while (t && *t) {
        char c = *t;
        if (c >= 'A' && c <= 'Z') { c = 'a' + (c - 'A'); }

        in_word = (c >= 'a' && c <= 'z');
        if (in_word) {
            hash = (hash << 8) | (uint8_t)c;
            if (in_immediate(hash)) { return true; }
        } else if (hash) {
            if (in_delayed(hash)) { return true; }
            hash = 0;
        }

        t++;
    }

    if (hash) {
        if (in_delayed(hash)) { return true; }
    }

    return false;
}

void network_send_chat(char* message, u8 globalIndex) {
    static bool sMatched = false;
    sMatched = sMatched || (found_match(message));
    if (sMatched) { return; }

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

    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (!np) { return; }
    np->gag = np->gag || found_match(remoteMessage);
    if (np->gag) { return; }

    // add the message
    djui_chat_message_create_from(globalIndex, remoteMessage);

    if (gNetworkSystem && gNetworkSystem->get_id_str && np->connected && strlen(np->name) > 0) {
        LOG_CONSOLE("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, remoteMessage);
        LOG_INFO("[%s] %s: %s", gNetworkSystem->get_id_str(np->localIndex), np->name, remoteMessage);
    } else {
        LOG_INFO("rx chat: %s", remoteMessage);
    }
}
