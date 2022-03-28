#include <stdio.h>
#include "../network.h"
#include "level_table.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

#include "pc/djui/djui.h"
#include "game/level_info.h"
#include "game/mario_misc.h"

void network_send_level_area_inform(void) {
    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np == NULL) { return; }
    np->currLevelAreaSeqId++;

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LEVEL_AREA_INFORM, true, PLMT_NONE);
    packet_write(&p, &np->currLevelAreaSeqId, sizeof(u16));
    packet_write(&p, &np->globalIndex,        sizeof(u8));
    packet_write(&p, &np->currCourseNum,      sizeof(s16));
    packet_write(&p, &np->currActNum,         sizeof(s16));
    packet_write(&p, &np->currLevelNum,       sizeof(s16));
    packet_write(&p, &np->currAreaIndex,      sizeof(s16));
    packet_write(&p, &np->currLevelSyncValid, sizeof(u8));
    packet_write(&p, &np->currAreaSyncValid,  sizeof(u8));
    network_send(&p);

    LOG_INFO("tx level area inform for global %d: (%d, %d, %d, %d)", np->globalIndex, np->currCourseNum, np->currActNum, np->currLevelNum, np->currAreaIndex);
}

void network_receive_level_area_inform(struct Packet* p) {
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

    LOG_INFO("rx level area inform for global %d: (%d, %d, %d, %d)", globalIndex, courseNum, actNum, levelNum, areaIndex);

    struct NetworkPlayer *np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving level area inform from inactive player!");
        return;
    }

    if (np == gNetworkPlayerLocal) { return; }

    if (np->currLevelAreaSeqId >= seq && abs(np->currLevelAreaSeqId - seq) < 256) {
        LOG_INFO("Received old level area inform seq: %d vs %d", np->currLevelAreaSeqId, seq);
        return;
    }

    np->currLevelAreaSeqId = seq;
    np->currLevelSyncValid = levelSyncValid;
    np->currAreaSyncValid  = areaSyncValid;
    network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);
}
