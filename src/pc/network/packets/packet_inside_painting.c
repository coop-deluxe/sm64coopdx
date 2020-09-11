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
extern s8 sReceivedLoadedActNum;

#pragma pack(1)
struct PacketInsidePaintingData {
    u8 seqId;
    u8 starIndex;
    u8 actIndex;
    u8 loadedActNum;
};

static u8 seqId = 0;
static u8 remoteLastSeqId = (u8)-1;

static void populate_packet_data(struct PacketInsidePaintingData* data) {
    data->seqId = seqId;
    data->starIndex = sSelectableStarIndex;
    data->actIndex = sSelectedActIndex;
    data->loadedActNum = sLoadedActNum;
}

void network_send_inside_painting(void) {
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

    // two-player hack: gControlledWarp is a bool instead of an index
    if (gControlledWarp) {
        LOG_INFO("this should never happen, received inside_painting when gControlledWarp");
        return;
    }

    LOG_INFO("received update");
    
    sSelectableStarIndex = remote.starIndex;
    sSelectedActIndex = remote.actIndex;
    if (sReceivedLoadedActNum == 0) {
        sReceivedLoadedActNum = remote.loadedActNum;
    }

    if (sReceivedLoadedActNum != 0) {
        LOG_INFO("finished with painting");
    }
}

