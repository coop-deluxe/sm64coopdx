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
    packet_write_uint8(&p, connectedCount);
    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        u8 npType = gNetworkPlayers[i].type;
        if (npType == NPT_LOCAL) { npType = NPT_SERVER; }
        else if (i == sendToLocalIndex) { npType = NPT_LOCAL; }
        s64 networkId = gNetworkSystem->get_id(i);
        packet_write_uint8(&p, npType);
        packet_write_uint8(&p, gNetworkPlayers[i].globalIndex);
        packet_write_uint16(&p, gNetworkPlayers[i].currLevelAreaSeqId);
        packet_write_int16(&p, gNetworkPlayers[i].currCourseNum);
        packet_write_int16(&p, gNetworkPlayers[i].currActNum);
        packet_write_int16(&p, gNetworkPlayers[i].currLevelNum);
        packet_write_int16(&p, gNetworkPlayers[i].currAreaIndex);
        packet_write_uint8(&p, gNetworkPlayers[i].currLevelSyncValid);
        packet_write_uint8(&p, gNetworkPlayers[i].currAreaSyncValid);
        packet_write_int64(&p, networkId);
        packet_write_uint8(&p, gNetworkPlayers[i].modelIndex);
        packet_write(&p, &gNetworkPlayers[i].palette, sizeof(struct PlayerPalette));
        packet_write(&p, &gNetworkPlayers[i].name, sizeof(u8) * MAX_CONFIG_STRING);
        packet_write(&p, &gNetworkPlayers[i].discordId, sizeof(u8) * 64);
        LOG_INFO("send network player [%d == %d]", gNetworkPlayers[i].globalIndex, npType);
    }

    network_send_to(sendToLocalIndex, &p);
    packet_clear(&p);
    LOG_INFO("sent list of %d network players to %d", connectedCount, sendToLocalIndex);
}

void network_send_network_players_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_NETWORK_PLAYERS_REQUEST, true, PLMT_NONE);
    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    packet_clear(&p);
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
    if (p == NULL) { return; }

    LOG_INFO("receiving list of network players");
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("received list of clients as a non-client");
        return;
    }
    if (network_player_any_connected() && gNetworkPlayers[p->localIndex].type != NPT_SERVER) {
        LOG_ERROR("list of clients came from non-server... refuse!");
        return;
    }
    u8 connectedCount = packet_read_uint8(p);
    for (s16 i = 0; i < connectedCount; i++) {
        u8 npType = packet_read_uint8(p);
        u8 globalIndex = packet_read_uint8(p);
        u16 levelAreaSeqId = packet_read_uint16(p);
        s16 courseNum = packet_read_int16(p);
        s16 actNum = packet_read_int16(p);
        s16 levelNum = packet_read_int16(p);
        s16 areaIndex = packet_read_int16(p);
        u8 levelSyncValid = packet_read_uint8(p);
        u8 areaSyncValid = packet_read_uint8(p);
        s64 networkId = packet_read_int64(p);
        u8 modelIndex = packet_read_uint8(p);
        
        struct PlayerPalette palette;
        packet_read(p, &palette, sizeof(struct PlayerPalette));
        
        char playerName[MAX_CONFIG_STRING] = { 0 };
        packet_read(p, &playerName, sizeof(u8) * MAX_CONFIG_STRING);
        
        char discordId[64] = { 0 };
        packet_read(p, &discordId, sizeof(u8) * 64);

        if (globalIndex >= MAX_PLAYERS) { continue; }

        u8 localIndex = network_player_connected(npType, globalIndex, modelIndex, &palette, playerName, discordId);
        LOG_INFO("received network player [%d == %d] (%d)", globalIndex, npType, localIndex);
        if (localIndex == UNKNOWN_GLOBAL_INDEX) { continue; }

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