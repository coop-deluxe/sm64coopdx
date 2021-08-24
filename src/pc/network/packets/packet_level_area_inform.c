#include <stdio.h>
#include "../network.h"
#include "level_table.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

static u16 sLevelAreaInformSeq[MAX_PLAYERS][MAX_PLAYERS] = { 0 };

void network_send_level_area_inform(struct NetworkPlayer* np) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    for (int i = 1; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np2 = &gNetworkPlayers[i];
        if (!np2->connected) { continue; }
        if (np2->localIndex == np->localIndex) { continue; }

        u16 seq = ++sLevelAreaInformSeq[np->globalIndex][i];

        struct Packet p;
        packet_init(&p, PACKET_LEVEL_AREA_INFORM, true, PLMT_NONE);
        packet_write(&p, &seq,                    sizeof(u16));
        packet_write(&p, &np->globalIndex,        sizeof(u8));
        packet_write(&p, &np->currCourseNum,      sizeof(s16));
        packet_write(&p, &np->currActNum,         sizeof(s16));
        packet_write(&p, &np->currLevelNum,       sizeof(s16));
        packet_write(&p, &np->currAreaIndex,      sizeof(s16));
        packet_write(&p, &np->currLevelSyncValid, sizeof(u8));
        packet_write(&p, &np->currAreaSyncValid,  sizeof(u8));
        network_send_to(np2->localIndex, &p);
    }

    LOG_INFO("tx level area inform for global %d", np->globalIndex);
}

void network_receive_level_area_inform(struct Packet* p) {

    SOFT_ASSERT(gNetworkType != NT_SERVER);

    u16 seq;
    u8 globalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    u8 levelSyncValid, areaSyncValid;
    packet_read(p, &seq,            sizeof(u16));
    packet_read(p, &globalIndex,    sizeof(u8));
    packet_read(p, &courseNum,      sizeof(s16));
    packet_read(p, &actNum,         sizeof(s16));
    packet_read(p, &levelNum,       sizeof(s16));
    packet_read(p, &areaIndex,      sizeof(s16));
    packet_read(p, &levelSyncValid, sizeof(u8));
    packet_read(p, &areaSyncValid,  sizeof(u8));

    LOG_INFO("rx level area inform for global %d", globalIndex);

    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving level area inform from inactive player!");
        return;
    }

    if (np == gNetworkPlayerLocal) { return; }
    if (sLevelAreaInformSeq[0][globalIndex] >= seq && abs(sLevelAreaInformSeq[0][globalIndex] - seq) < 256) {
        LOG_INFO("Received old level area inform seq: %d vs %d", sLevelAreaInformSeq[0][globalIndex], seq);
        return;
    }
    sLevelAreaInformSeq[0][globalIndex] = seq;

    np->currCourseNum      = courseNum;
    np->currActNum         = actNum;
    np->currLevelNum       = levelNum;
    np->currAreaIndex      = areaIndex;
    np->currLevelSyncValid = levelSyncValid;
    np->currAreaSyncValid  = areaSyncValid;
}
