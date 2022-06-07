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

void network_send_reservation_release(u32 syncId) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);

    // make sure this is a reserved id
    if (syncId < RESERVED_IDS_SYNC_OBJECT_OFFSET) { return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_RESERVATION_RELEASE, true, PLMT_NONE);

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActStarNum, sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

    packet_write(&p, &syncId, sizeof(u32));

    network_send_to(gNetworkPlayerServer->localIndex, &p);
    LOG_INFO("tx reservation release");
}

void network_receive_reservation_release(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LOG_INFO("rx reservation release");

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    if (courseNum != np->currCourseNum || actNum != np->currActNum || levelNum != np->currLevelNum || areaIndex != np->currAreaIndex) {
        LOG_ERROR("received an improper location");
        return;
    }

    u32 syncId;
    packet_read(p, &syncId, sizeof(u32));

    reservation_area_release(np, syncId);
}
