#include <stdio.h>
#include "level_table.h"
#include "../network.h"
#include "menu/custom_menu_system.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;
static u16 currLevelAreaSeqId = 0;

void network_send_level_area(void) {
    // override castle act to 0 to prevent instancing of the hub
    if (gCurrCourseNum == 0 && (gCurrLevelNum == LEVEL_CASTLE || gCurrLevelNum == LEVEL_CASTLE_GROUNDS || gCurrLevelNum == LEVEL_CASTLE_COURTYARD)) {
        gCurrActNum = 0;
    }

    struct Packet p;
    currLevelAreaSeqId++;
    packet_init(&p, PACKET_LEVEL_AREA, true, false);
    packet_write(&p, &gNetworkPlayerLocal->globalIndex, sizeof(u8));
    packet_write(&p, &currLevelAreaSeqId, sizeof(u16));
    packet_write(&p, &gCurrCourseNum,     sizeof(s16));
    packet_write(&p, &gCurrActNum,        sizeof(s16));
    packet_write(&p, &gCurrLevelNum,      sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,     sizeof(s16));
    network_send(&p);

    struct NetworkPlayer* np = gNetworkPlayerLocal;
    if (np != NULL) {
        np->currLevelAreaSeqId = currLevelAreaSeqId;
        np->currCourseNum      = gCurrCourseNum;
        np->currActNum         = gCurrActNum;
        np->currLevelNum       = gCurrLevelNum;
        np->currAreaIndex      = gCurrAreaIndex;
        np->currAreaSyncValid  = false;

        //LOG_INFO("set currAreaSyncValid to false");
    }

    //LOG_INFO("tx location: [%d, %d, %d, %d]", gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex);
}

void network_receive_level_area(struct Packet* p) {
    u8 globalIndex;
    u16 levelAreaSeqId;
    s16 courseNum, actNum, levelNum, areaIndex;

    packet_read(p, &globalIndex,    sizeof(u8));
    packet_read(p, &levelAreaSeqId, sizeof(u16));
    packet_read(p, &courseNum,      sizeof(s16));
    packet_read(p, &actNum,         sizeof(s16));
    packet_read(p, &levelNum,       sizeof(s16));
    packet_read(p, &areaIndex,      sizeof(s16));

    struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
    if (np == gNetworkPlayerLocal) {
        LOG_ERROR("Receiving level area from myself!");
        return;
    }

    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving level area from inactive player global %d!", np->globalIndex);
        return;
    }

    if (levelAreaSeqId <= np->currLevelAreaSeqId) {
        LOG_ERROR("Receiving old level area (%d <= %d) from local %d, global %d!", levelAreaSeqId, np->currLevelAreaSeqId, p->localIndex, np->globalIndex);
        return;
    }

    np->currLevelAreaSeqId = levelAreaSeqId;
    np->currCourseNum      = courseNum;
    np->currActNum         = actNum;
    np->currLevelNum       = levelNum;
    np->currAreaIndex      = areaIndex;

    //LOG_INFO("rx location: [%d, %d, %d, %d] from local %d, global %d", courseNum, actNum, levelNum, areaIndex, p->localIndex, np->globalIndex);
}

///////////////////////////////////////////////////////////////////////////////

static void network_send_level_area_valid_server(u8 toGlobalIndex) {
    struct NetworkPlayer* np = network_player_from_global_index(toGlobalIndex);
    if (np == NULL || !np->connected) {
        LOG_ERROR("tried to send level area valid to invalid player");
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_AREA_VALID, true, false);
    packet_write(&p, &np->currCourseNum, sizeof(s16));
    packet_write(&p, &np->currActNum,    sizeof(s16));
    packet_write(&p, &np->currLevelNum,  sizeof(s16));
    packet_write(&p, &np->currAreaIndex, sizeof(s16));
    network_send_to(np->localIndex, &p);
}

static void network_send_level_area_valid_client() {
    struct Packet p;
    packet_init(&p, PACKET_LEVEL_AREA_VALID, true, false);
    network_send_to(gNetworkPlayerServer->localIndex, &p);
}

void network_send_level_area_valid(u8 toGlobalIndex) {
    if (gNetworkType == NT_SERVER) {
        network_send_level_area_valid_server(toGlobalIndex);
    } else if (toGlobalIndex != 0) {
        LOG_ERROR("client tried to send 'level area valid' to non-server");
    } else {
        network_send_level_area_valid_client();
    }
}

static void network_receive_level_area_valid_server(struct Packet* p) {
    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || !np->connected) {
        LOG_ERROR("network_receive_level_area_valid_server(): invalid network player");
        return;
    }
    np->currAreaSyncValid = true;
    //LOG_INFO("set global %d's currAreaSyncValid to true", np->globalIndex);
}

static void network_receive_level_area_valid_client(struct Packet* p) {
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("tried to validate a level area that isn't current");
        return;
    }

    gNetworkPlayerLocal->currAreaSyncValid = true;
    network_send_level_area_valid_client();
    //LOG_INFO("set currAreaSyncValid to true (3)");
}

void network_receive_level_area_valid(struct Packet* p) {
    if (gNetworkType == NT_SERVER) {
        network_receive_level_area_valid_server(p);
    } else {
        network_receive_level_area_valid_client(p);
    }
}
