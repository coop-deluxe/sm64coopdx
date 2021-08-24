#include <stdio.h>
#include "../network.h"
#include "../reservation_area.h"
#include "object_fields.h"
#include "object_constants.h"
#include "behavior_table.h"
#include "course_table.h"
#include "src/game/interaction.h"
#include "src/engine/math_util.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

void network_send_reservation_use(u8 syncId) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // make sure this is a reserved id
    if (syncId < RESERVED_IDS_SYNC_OBJECT_OFFSET) { return; }

    struct Packet p;
    packet_init(&p, PACKET_RESERVATION_USE, true, PLMT_NONE);

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    packet_write(&p, &gCurrCourseNum,  sizeof(u8));
    packet_write(&p, &gCurrActStarNum, sizeof(u8));
    packet_write(&p, &gCurrLevelNum,   sizeof(u8));
    packet_write(&p, &gCurrAreaIndex,  sizeof(u8));

    packet_write(&p, &syncId, sizeof(u8));

    network_send_to(gNetworkPlayerServer->localIndex, &p);
    LOG_INFO("tx reservation use");
}

void network_receive_reservation_use(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("rx reservation use");

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving from inactive player!");
        return;
    }

    u8 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(u8));
    packet_read(p, &actNum,    sizeof(u8));
    packet_read(p, &levelNum,  sizeof(u8));
    packet_read(p, &areaIndex, sizeof(u8));

    if (courseNum != np->currCourseNum || actNum != np->currActNum|| levelNum != np->currLevelNum || areaIndex != np->currAreaIndex) {
        LOG_ERROR("received an improper location");
        return;
    }

    u8 syncId;
    packet_read(p, &syncId, sizeof(u8));

    reservation_area_use(np, syncId);
}
