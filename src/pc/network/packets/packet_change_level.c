#include <stdio.h>
#include "../network.h"
#include "../reservation_area.h"
#include "level_table.h"
#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

static void player_changed_level(struct NetworkPlayer* np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    // set NetworkPlayer variables
    np->currCourseNum      = courseNum;
    np->currActNum         = actNum;
    np->currLevelNum       = levelNum;
    np->currAreaIndex      = areaIndex;
    np->currLevelSyncValid = false;
    np->currAreaSyncValid  = false;
    reservation_area_change(np);

    // find a NetworkPlayer around that location
    struct NetworkPlayer* npLevelAreaMatch = get_network_player_from_area(courseNum, actNum, levelNum, areaIndex);
    struct NetworkPlayer* npLevelMatch     = get_network_player_from_level(courseNum, actNum, levelNum);
    struct NetworkPlayer* npAny = (npLevelAreaMatch == NULL) ? npLevelMatch : npLevelAreaMatch;

    if (npAny == NULL) {
        // no NetworkPlayer in the level
        network_send_sync_valid(np);
        network_send_level_area_inform(np);
        return;
    }

    // matching NetworkPlayer is client
    if (npAny == npLevelAreaMatch) {
        network_send_level_area_request(np, npAny);
    } else {
        network_send_level_request(np, npAny);
    }
    network_send_level_area_inform(np);
}

void network_send_change_level(void) {
    extern s16 gCurrCourseNum, gCurrActNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex;

    // override castle act to 0 to prevent instancing of the hub
    if (gCurrCourseNum == 0 && (gCurrLevelNum == LEVEL_CASTLE || gCurrLevelNum == LEVEL_CASTLE_GROUNDS || gCurrLevelNum == LEVEL_CASTLE_COURTYARD)) {
        gCurrActStarNum = 0;
        gCurrActNum = 0;
    }

    if (gNetworkType == NT_SERVER) {
        player_changed_level(gNetworkPlayerLocal, gCurrCourseNum, gCurrActStarNum, gCurrLevelNum, gCurrAreaIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_CHANGE_LEVEL, true, false);
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActStarNum, sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));
    network_send_to(gNetworkPlayerServer->localIndex, &p);

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    np->currCourseNum = gCurrCourseNum;
    np->currActNum    = gCurrActStarNum;
    np->currLevelNum  = gCurrLevelNum;
    np->currAreaIndex = gCurrAreaIndex;
    np->currAreaSyncValid  = false;
    np->currLevelSyncValid = false;

    LOG_INFO("tx change level");
}

void network_receive_change_level(struct Packet* p) {
    LOG_INFO("rx change level");

    assert(gNetworkType == NT_SERVER);
    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving change level from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    player_changed_level(np, courseNum, actNum, levelNum, areaIndex);
}
