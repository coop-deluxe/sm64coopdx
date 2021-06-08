#include <stdio.h>
#include "../network.h"
#include "menu/custom_menu_system.h"
//#define DISABLE_MODULE_LOG 1
#include "pc/debuglog.h"

extern s16 gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex;

#define MAX_STATIC_SPAWN_REMOVAL 256
u8 sStaticSpawnRemoval[MAX_STATIC_SPAWN_REMOVAL] = { 0 };
u8 sStaticSpawnRemovalIndex = 0;

void static_spawn_removal_remember(u8 syncId) {
    sStaticSpawnRemoval[sStaticSpawnRemovalIndex++] = syncId;
    if (sStaticSpawnRemovalIndex == 0) { sStaticSpawnRemovalIndex = MAX_STATIC_SPAWN_REMOVAL - 1; }
}

void static_spawn_removal_clear(void) {
    sStaticSpawnRemovalIndex = 0;
}

struct NetworkPlayer* get_network_player_from_valid_location(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex) {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected)                 { continue; }
        if (!np->currAreaSyncValid)         { continue; }
        if (np->currCourseNum != courseNum) { continue; }
        if (np->currActNum    != actNum)    { continue; }
        if (np->currLevelNum  != levelNum)  { continue; }
        if (np->currAreaIndex != areaIndex) { continue; }
        return np;
    }
    return NULL;
}

///////////////////////////////////////////////////////////////////////////////

void network_send_location_request(void) {
    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* np = get_network_player_from_valid_location(gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex);
        if (np == NULL) {
            gNetworkPlayerLocal->currAreaSyncValid = true;
            LOG_INFO("set currAreaSyncValid to true (1)");
            return;
        }
        //LOG_INFO("network_send_location_request()");
        network_send_client_location_request(gNetworkPlayerLocal->globalIndex, np->globalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_REQUEST, true, false);
    packet_write(&p, &gCurrCourseNum,     sizeof(s16));
    packet_write(&p, &gCurrActNum,        sizeof(s16));
    packet_write(&p, &gCurrLevelNum,      sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,     sizeof(s16));
    network_send_to(0, &p);
    //LOG_INFO("network_send_location_request() { %d, %d, %d, %d }", gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex);
}

void network_receive_location_request(struct Packet* p) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("non-server is receiving a location request!");
        return;
    }

    struct NetworkPlayer* np = &gNetworkPlayers[p->localIndex];
    if (np == NULL || np->localIndex == UNKNOWN_LOCAL_INDEX || !np->connected) {
        LOG_ERROR("Receiving location request from inactive player!");
        return;
    }

    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &courseNum, sizeof(s16));
    packet_read(p, &actNum,    sizeof(s16));
    packet_read(p, &levelNum,  sizeof(s16));
    packet_read(p, &areaIndex, sizeof(s16));

    np->currCourseNum     = courseNum;
    np->currActNum        = actNum;
    np->currLevelNum      = levelNum;
    np->currAreaIndex     = areaIndex;
    np->currAreaSyncValid = false;
    LOG_INFO("set global %d's currAreaSyncValid to false", np->globalIndex);

    //LOG_INFO("network_receive_location_request() { %d, %d, %d, %d }", courseNum, actNum, levelNum, areaIndex);

    struct NetworkPlayer* np2 = get_network_player_from_valid_location(courseNum, actNum, levelNum, areaIndex);
    if (np2 == NULL) {
        network_send_level_area_valid(np->globalIndex);
    } else if (np2 == gNetworkPlayerLocal) {
        network_send_location_response(np->globalIndex);
    } else {
        network_send_client_location_request(np->globalIndex, np2->globalIndex);
    }
}

///////////////////////////////////////////////////////////////////////////////

void network_send_client_location_request(u8 destGlobalIndex, u8 srcGlobalIndex) {
    if (gNetworkType != NT_SERVER) {
        LOG_ERROR("client can't send a 'client location request'");
        return;
    }
    
    struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_client_location_request: dest np is invalid (global %d)", destGlobalIndex);
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_CLIENT_LOCATION_REQUEST, true, false);
    packet_write(&p, &destGlobalIndex,       sizeof(u8));
    packet_write(&p, &destNp->currCourseNum, sizeof(s16));
    packet_write(&p, &destNp->currActNum,    sizeof(s16));
    packet_write(&p, &destNp->currLevelNum,  sizeof(s16));
    packet_write(&p, &destNp->currAreaIndex, sizeof(s16));

    //LOG_INFO("network_send_client_location_request() { %d, %d, %d, %d, %d }", destGlobalIndex, destNp->currCourseNum, destNp->currActNum, destNp->currLevelNum, destNp->currAreaIndex);

    struct NetworkPlayer* srcNp = network_player_from_global_index(srcGlobalIndex);
    if (srcNp == NULL || !srcNp->connected || !srcNp->currAreaSyncValid) {
        LOG_ERROR("network_send_client_location_request: source np is invalid (global %d)", srcGlobalIndex);
        return;
    }

    network_send_to(srcNp->localIndex, &p);
}

void network_receive_client_location_request(struct Packet* p) {
    if (gNetworkType == NT_SERVER) {
        LOG_ERROR("server is receiving a 'client location request'!");
        return;
    }

    u8 destGlobalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &destGlobalIndex, sizeof(u8));
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    //LOG_INFO("network_receive_client_location_request() { %d, %d, %d, %d, %d }", destGlobalIndex, courseNum, actNum, levelNum, areaIndex);

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("Receiving 'client location request' with the wrong location!");
        return;
    }

    network_send_location_response(destGlobalIndex);
}

///////////////////////////////////////////////////////////////////////////////

void network_send_location_response(u8 destGlobalIndex) {
    if (!gNetworkPlayerLocal->currAreaSyncValid) {
        LOG_ERROR("my area is invalid");
        return;
    }

    struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
    if (destNp == NULL || !destNp->connected) {
        LOG_ERROR("network_send_location_response: dest np is invalid");
        return;
    }

    struct Packet p;
    packet_init(&p, PACKET_LOCATION_RESPONSE, true, false);
    packet_write(&p, &destGlobalIndex, sizeof(u8));
    packet_write(&p, &gCurrCourseNum,  sizeof(s16));
    packet_write(&p, &gCurrActNum,     sizeof(s16));
    packet_write(&p, &gCurrLevelNum,   sizeof(s16));
    packet_write(&p, &gCurrAreaIndex,  sizeof(s16));

    packet_write(&p, &gMarioStates[0].numCoins, sizeof(s16));

    packet_write(&p, &sStaticSpawnRemovalIndex, sizeof(u8));
    for (int i = 0; i < sStaticSpawnRemovalIndex; i++) {
        packet_write(&p, &sStaticSpawnRemoval[i], sizeof(u8));
    }

    //LOG_INFO("network_send_location_response() { %d, %d, %d, %d, %d } to: %d", destGlobalIndex, gCurrCourseNum, gCurrActNum, gCurrLevelNum, gCurrAreaIndex, (gNetworkType == NT_SERVER) ? destNp->localIndex : 0);

    network_send_to((gNetworkType == NT_SERVER) ? destNp->localIndex : 0, &p);

    if (gNetworkType == NT_SERVER) {
        LOG_INFO("sending response from global %d to global %d", gNetworkPlayerLocal->globalIndex, destNp->globalIndex);
    }

}

void network_receive_location_response(struct Packet* p) {
    u8 destGlobalIndex;
    s16 courseNum, actNum, levelNum, areaIndex;
    packet_read(p, &destGlobalIndex, sizeof(u8));
    packet_read(p, &courseNum,       sizeof(s16));
    packet_read(p, &actNum,          sizeof(s16));
    packet_read(p, &levelNum,        sizeof(s16));
    packet_read(p, &areaIndex,       sizeof(s16));

    // TODO: read entities here!

    //LOG_INFO("network_receive_location_response() { %d, %d, %d, %d, %d }", destGlobalIndex, courseNum, actNum, levelNum, areaIndex);

    if (gNetworkType == NT_SERVER && gNetworkPlayerLocal->globalIndex != destGlobalIndex) {
        // recreate packet and send to destination
        struct Packet p2;
        packet_duplicate(p, &p2);

        struct NetworkPlayer* destNp = network_player_from_global_index(destGlobalIndex);
        if (destNp == NULL || !destNp->connected) {
            LOG_ERROR("network_receive_location_response: dest np is invalid");
            return;
        }
        struct NetworkPlayer* srcNp = &gNetworkPlayers[p->localIndex];
        LOG_INFO("sending location response from global %d to global %d", srcNp->globalIndex, destNp->globalIndex);
        network_send_to(destNp->localIndex, &p2);
        return;
    } else if (gNetworkPlayerLocal->globalIndex != destGlobalIndex) {
        LOG_ERROR("Receiving 'location response' meant for someone else!");
        return;
    }

    if (courseNum != gCurrCourseNum || actNum != gCurrActNum || levelNum != gCurrLevelNum || areaIndex != gCurrAreaIndex) {
        LOG_ERROR("Receiving 'location response' with the wrong location!");
        return;
    }
    // TODO: apply entities!

    if (gNetworkType == NT_SERVER) {
        struct NetworkPlayer* srcNp = &gNetworkPlayers[p->localIndex];
        LOG_INFO("sending location response from global %d to global %d", srcNp->globalIndex, gNetworkPlayerLocal->globalIndex);
    }

    if (gNetworkPlayerLocal->currAreaSyncValid) {
        LOG_ERROR("Receiving 'location response' when our location is already valid!");
        return;
    }

    s16 numCoins;
    packet_read(p, &numCoins, sizeof(s16));

    u8 staticSpawnRemovals;
    static_spawn_removal_clear();

    packet_read(p, &staticSpawnRemovals, sizeof(u8));
    for (int i = 0; i < staticSpawnRemovals; i++) {
        u8 syncId;
        packet_read(p, &syncId, sizeof(u8));
        struct SyncObject* so = &gSyncObjects[syncId];
        if (so != NULL) {
            if (so->o != NULL) {
                obj_mark_for_deletion(so->o);
                LOG_INFO("marking for deletion: %d", syncId);
            }
            network_forget_sync_object(so);
        }
    }

    gMarioStates[0].numCoins = numCoins;
    gNetworkPlayerLocal->currAreaSyncValid = true;
    LOG_INFO("set currAreaSyncValid to true (2)");
    if (gNetworkType != NT_SERVER) {
        network_send_level_area_valid(0);
    }
    //LOG_INFO("network_receive_location_response() ==> valid");
}