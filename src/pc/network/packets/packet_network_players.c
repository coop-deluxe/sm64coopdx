#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "behavior_data.h"
#include "game/behavior_actions.h"
#include "pc/debuglog.h"
#include "pc/configfile.h"
#include "pc/network/moderator_list.h"

static void network_send_to_network_players(u8 sendToLocalIndex) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    SOFT_ASSERT(sendToLocalIndex != 0);

    u8 connectedCount = network_player_connected_count();

    struct Packet p = { 0 };
    packet_init(&p, PACKET_NETWORK_PLAYERS, true, PLMT_NONE);
    packet_write(&p, &connectedCount, sizeof(u8));
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        u8 npType = gNetworkPlayers[i].type;
        if (npType == NPT_LOCAL) { npType = NPT_SERVER; }
        else if (i == sendToLocalIndex) { npType = NPT_LOCAL; }
        s64 networkId = gNetworkSystem->get_id(i);
        packet_write(&p, &npType,                                sizeof(u8));
        packet_write(&p, &gNetworkPlayers[i].globalIndex,        sizeof(u8));
        packet_write(&p, &gNetworkPlayers[i].currLevelAreaSeqId, sizeof(u16));
        packet_write(&p, &gNetworkPlayers[i].currCourseNum,      sizeof(s16));
        packet_write(&p, &gNetworkPlayers[i].currActNum,         sizeof(s16));
        packet_write(&p, &gNetworkPlayers[i].currLevelNum,       sizeof(s16));
        packet_write(&p, &gNetworkPlayers[i].currAreaIndex,      sizeof(s16));
        packet_write(&p, &gNetworkPlayers[i].currLevelSyncValid, sizeof(u8));
        packet_write(&p, &gNetworkPlayers[i].currAreaSyncValid,  sizeof(u8));
        packet_write(&p, &networkId,                             sizeof(s64));
        packet_write(&p, &gNetworkPlayers[i].modelIndex,         sizeof(u8));
        packet_write(&p, &gNetworkPlayers[i].palette,            sizeof(struct PlayerPalette));
        packet_write(&p, &gNetworkPlayers[i].name,               sizeof(u8) * MAX_CONFIG_STRING);
        packet_write(&p, &gNetworkPlayers[i].discordId,          sizeof(u8) * 64);
        LOG_INFO("send network player [%d == %d]", gNetworkPlayers[i].globalIndex, npType);
    }

    network_send_to(sendToLocalIndex, &p);
    LOG_INFO("sent list of %d network players to %d", connectedCount, sendToLocalIndex);
}

void network_send_network_players_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_NETWORK_PLAYERS_REQUEST, true, PLMT_NONE);
    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending network players request");
}

void network_receive_network_players_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    u8 localIndex = p->localIndex;
    if (localIndex == UNKNOWN_LOCAL_INDEX) {
        LOG_ERROR("Received network players request from unknown index");
        return;
    }
    network_send_to_network_players(localIndex);

    if (moderator_list_contains(gNetworkSystem->get_id_str(p->localIndex))) {
        LOG_INFO("sending moderator packet to localIndex: %d", p->localIndex);
        network_send_moderator(p->localIndex);
    }
}

void network_send_network_players(u8 exceptLocalIndex) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("sending list of network players to all");
    for (s32 i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        if (i == exceptLocalIndex) { continue; }
        network_send_to_network_players(i);
    }
}

void network_receive_network_players(struct Packet *p) {
    LOG_INFO("receiving list of network players");
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("received list of clients as a non-client");
        return;
    }
    u8 connectedCount = 0;
    packet_read(p, &connectedCount, sizeof(u8));
    for (s16 i = 0; i < connectedCount; i++) {
        u8 npType, globalIndex;
        u16 levelAreaSeqId;
        s16 courseNum, actNum, levelNum, areaIndex;
        u8 levelSyncValid, areaSyncValid;
        s64 networkId;
        u8 modelIndex;
        struct PlayerPalette palette;
        char playerName[MAX_CONFIG_STRING] = { 0 };
        char discordId[64] = { 0 };

        packet_read(p, &npType,         sizeof(u8));
        packet_read(p, &globalIndex,    sizeof(u8));
        packet_read(p, &levelAreaSeqId, sizeof(u16));
        packet_read(p, &courseNum,      sizeof(s16));
        packet_read(p, &actNum,         sizeof(s16));
        packet_read(p, &levelNum,       sizeof(s16));
        packet_read(p, &areaIndex,      sizeof(s16));
        packet_read(p, &levelSyncValid, sizeof(u8));
        packet_read(p, &areaSyncValid,  sizeof(u8));
        packet_read(p, &networkId,      sizeof(s64));
        packet_read(p, &modelIndex,     sizeof(u8));
        packet_read(p, &palette,        sizeof(struct PlayerPalette));
        packet_read(p, &playerName,     sizeof(u8) * MAX_CONFIG_STRING);
        packet_read(p, &discordId,      sizeof(u8) * 64);

        if (globalIndex >= MAX_PLAYERS) { continue; }

        u8 localIndex = network_player_connected(npType, globalIndex, modelIndex, &palette, playerName, discordId);
        LOG_INFO("received network player [%d == %d] (%d)", globalIndex, npType, localIndex);
        if (localIndex != UNKNOWN_GLOBAL_INDEX) {
            struct NetworkPlayer *np = &gNetworkPlayers[localIndex];
            if (localIndex != 0) {
                np->currLevelAreaSeqId = levelAreaSeqId;
                np->currLevelSyncValid = levelSyncValid;
                np->currAreaSyncValid = areaSyncValid;
                network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);
                LOG_INFO("received network player location (%d, %d, %d, %d)", courseNum, actNum, levelNum, areaIndex);
                if (gNetworkType == NT_CLIENT && globalIndex != 0 && localIndex != 0) {
                    gNetworkSystem->save_id(localIndex, networkId);
                }
            } else {
                np->modelIndex   = (modelIndex < CT_MAX) ? modelIndex : 0;
                np->palette      = palette;
                network_player_update_model(localIndex);
            }
        }
    }
}