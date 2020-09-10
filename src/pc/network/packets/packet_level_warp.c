#include <stdio.h>
#include "sm64.h"
#include "../network.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/ingame_menu.h"
#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

static u8 eventId = 0;
static u8 remoteFinishedEventId = (u8)-1;

static u8 seqId = 0;
static u8 remoteLastSeqId = (u8)-1;

extern u8 gControlledWarp; // two-player hack
extern u8 gReceiveWarp;
extern struct WarpDest gReceiveWarpDest;

struct WarpDest savedWarpNode = { 0 };

#pragma pack(1)
struct PacketLevelWarpData {
    u8 seqId;
    u8 eventId;
    u8 done;
    u8 controlledWarp;
    struct WarpDest warpDest;
};

static void populate_packet_data(struct PacketLevelWarpData* data, bool done) {
    data->seqId = seqId;
    data->eventId = eventId;
    data->done = done;
    data->controlledWarp = gControlledWarp;
    data->warpDest = savedWarpNode;
}

void network_send_level_warp(u8 done) {
    if (!done) {
        savedWarpNode = sWarpDest;
        gControlledWarp = true;
        eventId++;
        LOG_INFO("new event [%d]!", eventId);
    }

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, done);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, true);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);

    seqId++;
}

static void do_warp(void) {
    gReceiveWarpDest = savedWarpNode;
    gReceiveWarp = TRUE;
}

void network_receive_level_warp(struct Packet* p) {
    struct PacketLevelWarpData remote = { 0 };
    packet_read(p, &remote, sizeof(struct PacketLevelWarpData));

    // de-dup
    if (remote.seqId == remoteLastSeqId) {
        LOG_INFO("we've seen this packet, escape!");
        return;
    }
    remoteLastSeqId = remote.seqId;
    LOG_INFO("rx event [%d] last [%d]!", remote.eventId, remoteFinishedEventId);
    if (remote.eventId == remoteFinishedEventId || (remote.eventId == remoteFinishedEventId - 1)) {
        LOG_INFO("we've finished this event, escape!");
        return;
    }

    if (gNetworkType == NT_SERVER) {
        if (sCurrPlayMode != PLAY_MODE_SYNC_LEVEL) {
            // client initiated warp
            LOG_INFO("client initiated warp!");
            gControlledWarp = FALSE;
            savedWarpNode = remote.warpDest;
            eventId = remote.eventId;
            remoteFinishedEventId = remote.eventId;
            LOG_INFO("finished event [%d]!", remote.eventId);
            do_warp();
            network_send_level_warp(TRUE);
            return;
        } else if (remote.done) {
            // client done with warp
            LOG_INFO("client is done with warp, lets-a-go!");
            remoteFinishedEventId = remote.eventId;
            do_warp();
            return;
        } else {
            LOG_INFO("client initiated warp, but server is already warping!");
            return;
        }
    }

    assert(gNetworkType == NT_CLIENT);

    // server initiated warp
    LOG_INFO("server initiated warp!");
    gControlledWarp = !remote.controlledWarp; // two-player hack
    savedWarpNode = remote.warpDest;
    eventId = remote.eventId;
    remoteFinishedEventId = remote.eventId;
    LOG_INFO("finished event [%d]!", remote.eventId);
    do_warp();
    network_send_level_warp(TRUE);
}
