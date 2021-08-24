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

void network_send_reservation_list(struct NetworkPlayer* np, u8 syncIds[]) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);

    struct Packet p;
    packet_init(&p, PACKET_RESERVATION_LIST, true, PLMT_NONE);

    packet_write(&p, &np->currCourseNum, sizeof(u8));
    packet_write(&p, &np->currActNum,    sizeof(u8));
    packet_write(&p, &np->currLevelNum,  sizeof(u8));
    packet_write(&p, &np->currAreaIndex, sizeof(u8));

    for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
        packet_write(&p, &syncIds[i], sizeof(u8));
    }

    network_send_to(np->localIndex, &p);
    LOG_INFO("tx reservation list");
}

void network_receive_reservation_list(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    LOG_INFO("rx reservation list");

    u8 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(u8));
    packet_read(p, &actNum,    sizeof(u8));
    packet_read(p, &levelNum,  sizeof(u8));
    packet_read(p, &areaIndex, sizeof(u8));

    extern s16 gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;
    if (courseNum != gCurrCourseNum || actNum != gCurrActStarNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("received an improper location");
        return;
    }

    u8 syncIds[RESERVED_IDS_PER_PLAYER_COUNT];
    for (int i = 0; i < RESERVED_IDS_PER_PLAYER_COUNT; i++) {
        packet_read(p, &syncIds[i], sizeof(u8));
    }

    reservation_area_local_update(courseNum, actNum, levelNum, areaIndex, syncIds);
}
