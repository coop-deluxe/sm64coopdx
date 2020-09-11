#include <stdio.h>
#include "sm64.h"
#include "../network.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/ingame_menu.h"
#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

static u8 eventId = 0;
static u8 remoteFinishedEventId[2] = { (u8)-1, (u8)-1 };

static u8 seqId = 0;
static u8 remoteLastSeqId = (u8)-1;

extern s16 D_80339EE0;
extern u8 gControlledWarp; // two-player hack
extern u8 gReceiveWarp;
extern struct WarpDest gReceiveWarpDest;

s16 saved_D_80339EE0 = 0;
struct WarpDest savedWarpNode = { 0 };

static clock_t lastDoneEvent = 0;
static bool isInWarp = FALSE;

#pragma pack(1)
struct PacketLevelWarpData {
    u8 seqId;
    u8 eventId;
    u8 done;
    u8 controlledWarp;
    struct WarpDest warpDest;
    s16 D_80339EE0;
};

static void populate_packet_data(struct PacketLevelWarpData* data, bool done, u8 packetEventId) {
    data->seqId = seqId;
    data->eventId = packetEventId;
    data->done = done;
    data->controlledWarp = gControlledWarp;
    data->warpDest = savedWarpNode;
    data->D_80339EE0 = saved_D_80339EE0;
}

void network_send_level_warp_begin(void) {
    assert(!isInWarp);
    isInWarp = TRUE;
    savedWarpNode = sWarpDest;
    saved_D_80339EE0 = D_80339EE0;

    float elapsedSinceDone = (clock() - lastDoneEvent) / CLOCKS_PER_SEC;
    gControlledWarp = (elapsedSinceDone < 1.0f)
                      ? (gNetworkType == NT_SERVER) // two-player hack
                      : true;

    eventId++;
    if (eventId == (u8)-1) { eventId++; }
    LOG_INFO("new event [%d]!", eventId);

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, false, eventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, true);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);

    seqId++;
}

static void network_send_level_warp_repeat(void) {
    assert(isInWarp);

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, false, eventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, false);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);

    seqId++;
}

static void network_send_level_warp_done(u8 remoteEventId) {
    lastDoneEvent = clock();
    isInWarp = FALSE;

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, true, remoteEventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, true);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);

    seqId++;
}

static void do_warp(void) {
    gReceiveWarpDest = savedWarpNode;
    D_80339EE0 = saved_D_80339EE0;
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

    LOG_INFO("rx event [%d] last [%d, %d]", remote.eventId, remoteFinishedEventId[0], remoteFinishedEventId[1]);

    if (remote.done && remote.eventId != eventId) {
        LOG_INFO("remote has finished the wrong id!");
        return;
    }

    if (!remote.done) {
        if (remote.eventId == remoteFinishedEventId[0] || remote.eventId == remoteFinishedEventId[1]) {
            LOG_INFO("we've finished this event, escape!");
            return;
        }
        remoteFinishedEventId[1] = remoteFinishedEventId[0];
        remoteFinishedEventId[0] = remote.eventId;
    }

    if (gNetworkType == NT_SERVER) {
        if (!isInWarp && remote.done) {
            LOG_INFO("client is done with warp, but so are we!");
            return;
        } else if (!isInWarp) {
            // client initiated warp
            LOG_INFO("client initiated warp!");
            gControlledWarp = !remote.controlledWarp; // two-player hack
            savedWarpNode = remote.warpDest;
            saved_D_80339EE0 = remote.D_80339EE0;
            do_warp();
            network_send_level_warp_done(remote.eventId);
            return;
        } else if (remote.done && remote.eventId == eventId) {
            // client done with warp
            LOG_INFO("client is done with warp, lets-a-go!");
            do_warp();
            isInWarp = FALSE;
            return;
        } else {
            LOG_INFO("client initiated warp, but server is already warping!");
            LOG_INFO("remote.done: %d, remote.eventId: %d!", remote.done, remote.eventId);
            network_send_level_warp_repeat();
            return;
        }
    }

    assert(gNetworkType == NT_CLIENT);

    // server initiated warp
    LOG_INFO("server initiated warp!");
    gControlledWarp = !remote.controlledWarp; // two-player hack
    savedWarpNode = remote.warpDest;
    saved_D_80339EE0 = remote.D_80339EE0;
    LOG_INFO("finished event [%d]!", remote.eventId);
    do_warp();
    network_send_level_warp_done(remote.eventId);
}
