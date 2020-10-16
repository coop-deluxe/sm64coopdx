#include <stdio.h>
#include "sm64.h"
#include "../network.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/ingame_menu.h"
#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

// two-player hack
// this entire system needs to be ripped out and replaced

static u8 eventId = 0;
static u8 remoteFinishedEventId[2] = { (u8)-1, (u8)-1 };

extern s16 gTTCSpeedSetting;
extern s16 D_80339EE0;
extern float gPaintingMarioYEntry;
extern u8 gControlledWarpGlobalIndex;

extern struct SavedWarpValues gReceiveWarp;
struct SavedWarpValues saved = { 0 };

static clock_t lastDoneEvent = 0;
static bool isInWarp = FALSE;

#pragma pack(1)
struct PacketLevelWarpData {
    u8 eventId;
    u8 done;
    u8 controlledWarp;
    struct WarpDest warpDest;
    s8 inWarpCheckpoint;
    s16 ttcSpeedSetting;
    s16 D_80339EE0;
    f32 paintingMarioYEntry;
};

static void populate_packet_data(struct PacketLevelWarpData* data, bool done, u8 packetEventId) {
    data->eventId = packetEventId;
    data->done = done;
    data->controlledWarp = gControlledWarpGlobalIndex;
    data->warpDest = saved.warpDest;
    data->inWarpCheckpoint = saved.inWarpCheckpoint;
    data->ttcSpeedSetting = saved.ttcSpeedSetting;
    data->D_80339EE0 = saved.D_80339EE0;
    data->paintingMarioYEntry = saved.paintingMarioYEntry;
}

void network_send_level_warp_begin(void) {
    isInWarp = TRUE;
    saved.warpDest = sWarpDest;
    saved.inWarpCheckpoint = gInWarpCheckpoint;
    saved.ttcSpeedSetting = gTTCSpeedSetting;
    saved.D_80339EE0 = D_80339EE0;
    saved.paintingMarioYEntry = gPaintingMarioYEntry;

    float elapsedSinceDone = (clock() - lastDoneEvent) / CLOCKS_PER_SEC;
    gControlledWarpGlobalIndex = (elapsedSinceDone < 1.0f)
                               ? 0
                               : gNetworkPlayerLocal->globalIndex;

    eventId++;
    if (eventId == (u8)-1) { eventId++; }
    LOG_INFO("new event [%d]!", eventId);

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, false, eventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, true, false);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);
}

void network_send_level_warp_repeat(void) {
    if (!isInWarp) {
        network_send_level_warp_begin();
        LOG_ERROR("sending repeat, but we're not warping!");
        return;
    }

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, false, eventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, false, false);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);
}

static void network_send_level_warp_done(u8 remoteEventId) {
    lastDoneEvent = clock();
    isInWarp = FALSE;

    struct PacketLevelWarpData data = { 0 };
    populate_packet_data(&data, true, remoteEventId);

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP, true, false);
    packet_write(&p, &data, sizeof(struct PacketLevelWarpData));
    network_send(&p);
}

static void do_warp(void) {
    // keep check_received_warp(void) in sync with this
    gReceiveWarp = saved;
    gReceiveWarp.received = TRUE;
    gInWarpCheckpoint = saved.inWarpCheckpoint;
    gTTCSpeedSetting = saved.ttcSpeedSetting;
    D_80339EE0 = saved.D_80339EE0;
    gPaintingMarioYEntry = saved.paintingMarioYEntry;
}

void network_receive_level_warp(struct Packet* p) {
    struct PacketLevelWarpData remote = { 0 };
    packet_read(p, &remote, sizeof(struct PacketLevelWarpData));

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
            gControlledWarpGlobalIndex = remote.controlledWarp;

            saved.warpDest = remote.warpDest;
            saved.inWarpCheckpoint = remote.inWarpCheckpoint;
            saved.ttcSpeedSetting = remote.ttcSpeedSetting;
            saved.D_80339EE0 = remote.D_80339EE0;
            saved.paintingMarioYEntry = remote.paintingMarioYEntry;

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
    gControlledWarpGlobalIndex = remote.controlledWarp;

    saved.warpDest = remote.warpDest;
    saved.inWarpCheckpoint = remote.inWarpCheckpoint;
    saved.ttcSpeedSetting = remote.ttcSpeedSetting;
    saved.D_80339EE0 = remote.D_80339EE0;
    saved.paintingMarioYEntry = remote.paintingMarioYEntry;

    LOG_INFO("finished event [%d]!", remote.eventId);
    do_warp();
    network_send_level_warp_done(remote.eventId);
}
