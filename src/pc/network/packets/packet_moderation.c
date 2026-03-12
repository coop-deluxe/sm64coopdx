#include <stdio.h>
#include "../network.h"
#include "../moderation.h"
#include "pc/debuglog.h"

bool sValidActions[MODERATION_ACTION_COUNT] = {
    [MODERATION_ACTION_KICK] = true,
    [MODERATION_ACTION_BAN] = true
};

void network_send_moderation_action(u8 action, u8 localIndex, char* reason, bool permanent) {
    SOFT_ASSERT(gNetworkType != NT_SERVER);
    if (!gNetworkPlayerLocal->moderator && localIndex != 0) {
        LOG_ERROR("Tried to send moderation action as a non-moderator!");
        return;
    }
    struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
    if (!np->connected) {
        LOG_ERROR("Moderator tried to perform moderation on a disconnected player!");
    }
    if (np->moderator && localIndex != 0) {
        LOG_ERROR("Moderator tried to perform moderation on another moderator!");
        return;
    }

    if (!sValidActions[action]) {
        LOG_ERROR("Tried to send unimplemented action to the server!");
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_MODERATION_ACTION, false, PLMT_NONE);
    packet_write(&p, &action, sizeof(u8));
    packet_write(&p, &np->globalIndex, sizeof(u8));
    u16 reasonLength = 0;
    if (reason) {
        u16 reasonLength = strlen(reason);
        packet_write(&p, &reasonLength, sizeof(u16));
        packet_write(&p, reason, sizeof(u8) * reasonLength);
    } else {
        packet_write(&p, &reasonLength, sizeof(u16));
    }
    packet_write(&p, &permanent, sizeof(bool));

    network_send_to(gNetworkPlayerServer->localIndex, &p);
}

void network_receive_moderation_action(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    enum ModerationActions action = MODERATION_ACTION_COUNT;
    u8 globalIndex = 0;
    u16 reasonLength = 0;
    char reason[MAX_REASON_LENGTH] = { 0 };
    bool permanent = false;

    packet_read(p, &action, sizeof(u8));
    if (!sValidActions[action]) {
        LOG_ERROR("Received an invalid moderation action from a moderator!");
        return;
    }

    packet_read(p, &globalIndex, sizeof(u8));
    if (globalIndex >= MAX_PLAYERS) {
        LOG_ERROR("Received an out of range global index from a moderator!");
        return;
    }
    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (!np->connected) {
        LOG_ERROR("Network player received from moderator is not connected!");
        return;
    }

    packet_read(p, &reasonLength, sizeof(u16));
    if (reasonLength >= MAX_REASON_LENGTH) reasonLength = MAX_REASON_LENGTH - 1;
    packet_read(p, reason, sizeof(u8) * reasonLength);
    packet_read(p, &permanent, sizeof(bool));

    switch (action) {
        case MODERATION_ACTION_KICK: network_kick_player(np->localIndex, reason);           break;
        case MODERATION_ACTION_BAN:  network_ban_player(np->localIndex, reason, permanent); break;
        default: break;
    }
}