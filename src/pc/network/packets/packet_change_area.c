#include <stdio.h>
#include "../network.h"
#include "level_table.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

static void player_changed_area(struct NetworkPlayer *np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    // set NetworkPlayer variables
    np->currAreaSyncValid  = false;
    network_player_update_course_level(np, courseNum, actNum, levelNum, areaIndex);

    // find a NetworkPlayer at that area
    struct NetworkPlayer *npLevelAreaMatch = get_network_player_from_area(courseNum, actNum, levelNum, areaIndex);

    bool inCredits = (np->currActNum == 99);
    if (npLevelAreaMatch == NULL || inCredits) {
        // no NetworkPlayer in the level
        network_send_sync_valid(np, courseNum, actNum, levelNum, areaIndex);
        return;
    }

    // matching NetworkPlayer is client
    network_send_area_request(np, npLevelAreaMatch);
}

void network_send_change_area(void) {
    extern s16 gCurrCourseNum, gCurrActNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;

    // override castle act to 0 to prevent instancing of the hub
    if (gCurrCourseNum == 0 && (gCurrLevelNum == LEVEL_CASTLE || gCurrLevelNum == LEVEL_CASTLE_GROUNDS || gCurrLevelNum == LEVEL_CASTLE_COURTYARD)) {
        if (gCurrActStarNum != 99) {
            gCurrActStarNum = 0;
            gCurrActNum = 0;
        }
    }

    if (gNetworkType == NT_SERVER) {
        player_changed_area(gNetworkPlayerLocal, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
        return;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHANGE_AREA, true, PLMT_NONE);
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActStarNum, sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));
    network_send_to(gNetworkPlayerServer->localIndex, &p);

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    np->currAreaSyncValid  = false;
    network_player_update_course_level(np, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);

    LOG_INFO("tx change area");
}

void network_receive_change_area(struct Packet *p) {
    LOG_INFO("rx change area");

    SOFT_ASSERT(gNetworkType == NT_SERVER);
    struct NetworkPlayer *np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving change area from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    player_changed_area(np, courseNum, actNum, levelNum, areaIndex);
}
