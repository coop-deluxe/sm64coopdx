#include <stdio.h>
#include "../network.h"
#include "src/game/level_update.h"
#include "src/game/area.h"
#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

extern u8 gControlledWarp;

extern u8 sSelectableStarIndex;
extern u8 sSelectedActIndex;
extern s8 sLoadedActNum;

#pragma pack(1)
struct PacketInsidePaintingData {
    u8 seqId;
    u8 eventId;
    u8 starIndex;
    u8 actIndex;
    u8 loadedActNum;
};

static u8 eventId = 0;
static u8 remoteFinishedEventId = (u8)-1;

static u8 seqId = 0;
static u8 remoteLastSeqId = (u8)-1;

static void populate_packet_data(struct PacketInsidePaintingData* data) {
    data->seqId = seqId;
    data->eventId = eventId;
    data->starIndex = sSelectableStarIndex;
    data->actIndex = sSelectedActIndex;
    data->loadedActNum = sLoadedActNum;
}

void network_send_inside_painting(u8 startOfEvent, u8 endOfEvent) {
    if (startOfEvent) { eventId++; }
    struct PacketInsidePaintingData data = { 0 };
    populate_packet_data(&data);

    struct Packet p;
    packet_init(&p, PACKET_INSIDE_PAINTING, true);
    packet_write(&p, &data, sizeof(struct PacketInsidePaintingData));
    network_send(&p);
    seqId++;
}

void network_receive_inside_painting(struct Packet* p) {
    struct PacketInsidePaintingData local = { 0 };
    populate_packet_data(&local);

    struct PacketInsidePaintingData remote = { 0 };
    packet_read(p, &remote, sizeof(struct PacketInsidePaintingData));

    // de-dup
    if (remote.seqId == remoteLastSeqId) {
        LOG_INFO("we've seen this packet, escape!");
        return;
    }
    remoteLastSeqId = remote.seqId;
    if (remote.eventId == remoteFinishedEventId || (remote.eventId == remoteFinishedEventId - 1)) {
        LOG_INFO("we've finished this event, escape!");
        return;
    }

    // two-player hack: gControlledWarp is a bool instead of an index
    if (gControlledWarp) {
        LOG_INFO("this should never happen, received inside_painting when gControlledWarp");
        return;
    }

    LOG_INFO("received update");
    eventId = remote.eventId;
    sSelectableStarIndex = remote.starIndex;
    sSelectedActIndex = remote.actIndex;
    sLoadedActNum = remote.loadedActNum;

    if (sLoadedActNum != 0) {
        LOG_INFO("finished with painting");
        remoteFinishedEventId = remote.eventId;
    }
}

