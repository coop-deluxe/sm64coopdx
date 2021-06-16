#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "behavior_data.h"
#include "src/game/behavior_actions.h"
#include "pc/debuglog.h"

static void network_send_to_network_players(u8 sendToLocalIndex) {
    assert(gNetworkType == NT_SERVER);
    assert(sendToLocalIndex != 0);

    u8 connectedCount = network_player_connected_count();

    struct Packet p;
    packet_init(&p, PACKET_NETWORK_PLAYERS, true, false);
    packet_write(&p, &connectedCount, sizeof(u8));
    for (int i = 0; i < MAX_PLAYERS; i++) {
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
        LOG_INFO("send network player [%d == %d]", gNetworkPlayers[i].globalIndex, npType);
    }

    network_send_to(sendToLocalIndex, &p);
    LOG_INFO("sent list of %d network players to %d", connectedCount, sendToLocalIndex);
}

void network_send_network_players(void) {
    assert(gNetworkType == NT_SERVER);
    LOG_INFO("sending list of network players to all");
    for (int i = 1; i < MAX_PLAYERS; i++) {
        if (!gNetworkPlayers[i].connected) { continue; }
        network_send_to_network_players(i);
    }
}

void network_receive_network_players(struct Packet* p) {
    LOG_INFO("receiving list of network players");
    if (gNetworkType != NT_CLIENT) {
        LOG_ERROR("received list of clients as a non-client");
        return;
    }
    u8 connectedCount = 0;
    packet_read(p, &connectedCount, sizeof(u8));
    for (int i = 0; i < connectedCount; i++) {
        u8 npType, globalIndex;
        u16 levelAreaSeqId;
        s16 courseNum, actNum, levelNum, areaIndex;
        u8 levelSyncValid, areaSyncValid;
        s64 networkId;
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

        u8 localIndex = network_player_connected(npType, globalIndex);
        LOG_INFO("received network player [%d == %d] (%d)", globalIndex, npType, localIndex);
        if (localIndex != UNKNOWN_GLOBAL_INDEX && localIndex != 0) {
            struct NetworkPlayer* np = &gNetworkPlayers[localIndex];
            np->currLevelAreaSeqId = levelAreaSeqId;
            np->currCourseNum      = courseNum;
            np->currActNum         = actNum;
            np->currLevelNum       = levelNum;
            np->currAreaIndex      = areaIndex;
            np->currLevelSyncValid = levelSyncValid;
            np->currAreaSyncValid  = areaSyncValid;
            LOG_INFO("received network player location (%d, %d, %d, %d)", courseNum, actNum, levelNum, areaIndex);
            if (gNetworkType == NT_CLIENT && globalIndex != 0 && localIndex != 0) {
                gNetworkSystem->save_id(localIndex, networkId);
            }
        }
    }
}