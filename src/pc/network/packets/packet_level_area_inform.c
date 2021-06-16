#include <stdio.h>
#include "../network.h"
#include "level_table.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_level_area_inform(struct NetworkPlayer* np) {
    assert(gNetworkType == NT_SERVER);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_AREA_INFORM, true, false);
    packet_write(&p, &np->globalIndex,        sizeof(u8));
    packet_write(&p, &np->currCourseNum,      sizeof(s16));
    packet_write(&p, &np->currActNum,         sizeof(s16));
    packet_write(&p, &np->currLevelNum,       sizeof(s16));
    packet_write(&p, &np->currAreaIndex,      sizeof(s16));
    packet_write(&p, &np->currLevelSyncValid, sizeof(u8));
    packet_write(&p, &np->currAreaSyncValid,  sizeof(u8));
    network_send(&p);

    LOG_INFO("tx level area inform");
}

void network_receive_level_area_inform(struct Packet* p) {
    LOG_INFO("rx level area inform");

    assert(gNetworkType != NT_SERVER);

    u8 globalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    u8 levelSyncValid, areaSyncValid;
    packet_read(p, &globalIndex,    sizeof(u8));
    packet_read(p, &courseNum,      sizeof(s16));
    packet_read(p, &actNum,         sizeof(s16));
    packet_read(p, &levelNum,       sizeof(s16));
    packet_read(p, &areaIndex,      sizeof(s16));
    packet_read(p, &levelSyncValid, sizeof(u8));
    packet_read(p, &areaSyncValid,  sizeof(u8));

    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving level area inform from inactive player!");
        return;
    }

    if (np == gNetworkPlayerLocal) { return; }

    np->currCourseNum      = courseNum;
    np->currActNum         = actNum;
    np->currLevelNum       = levelNum;
    np->currAreaIndex      = areaIndex;
    np->currLevelSyncValid = levelSyncValid;
    np->currAreaSyncValid  = areaSyncValid;
}
