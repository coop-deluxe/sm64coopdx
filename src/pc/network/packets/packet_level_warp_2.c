#include "../network.h"
#include "game/level_update.h"
#include "game/object_list_processor.h"
//#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

#define SERVER_RETAIN_WARP_SECONDS 1

extern u8 gControlledWarpGlobalIndex;
extern float gPaintingMarioYEntry;

#pragma pack(1)
struct PacketLevelWarp2Data {
    s16 levelNum;
    s16 areaIndex;
    s16 actNum;

    u8 warpType;
    u8 warpLevelNum;
    u8 warpAreaIdx;
    u8 warpNodeId;
    u32 warpArg;

    s8 inWarpCheckpoint;
    s16 ttcSpeedSetting;
    s16 D_80339EE0;
    f32 paintingMarioYEntry;
    u8 controlledWarpGlobalIndex;
};

struct PacketLevelWarp2Data sSavedLevelWarp2Data = { 0 };
static clock_t sSavedClockTime = 0;

static void populate_packet_data(struct PacketLevelWarp2Data* data) {
    data->levelNum  = gCurrLevelNum;
    data->areaIndex = gCurrAreaIndex;
    data->actNum    = gCurrActNum;

    data->warpType     = sWarpDest.type;
    data->warpLevelNum = sWarpDest.levelNum;
    data->warpAreaIdx  = sWarpDest.areaIdx;
    data->warpNodeId   = sWarpDest.nodeId;
    data->warpArg      = sWarpDest.arg;

    data->inWarpCheckpoint          = gInWarpCheckpoint;
    data->ttcSpeedSetting           = gTTCSpeedSetting;
    data->D_80339EE0                = D_80339EE0;
    data->paintingMarioYEntry       = gPaintingMarioYEntry;
    data->controlledWarpGlobalIndex = gControlledWarpGlobalIndex;
}

void network_send_level_warp_2(u8 eventBegins, u8 controlledGlobalIndex) {
    struct PacketLevelWarp2Data data = { 0 };
    if (eventBegins) {
        gControlledWarpGlobalIndex = controlledGlobalIndex;
        populate_packet_data(&data);
        if (gNetworkType == NT_SERVER) {
            sSavedLevelWarp2Data = data;
            sSavedClockTime = clock();
        }
    } else {
        data = sSavedLevelWarp2Data;
    }

    struct Packet p;
    packet_init(&p, PACKET_LEVEL_WARP_2, true, false);
    packet_write(&p, &data, sizeof(struct PacketLevelWarp2Data));

    if (gNetworkType == NT_SERVER) {
        network_send(&p);
    } else {
        network_send_to(gNetworkPlayerServer->localIndex, &p);
    }

    LOG_INFO("send warp: %d, %d, %d", gCurrLevelNum, gCurrAreaIndex, gCurrActNum);
}

static void do_warp(struct PacketLevelWarp2Data* data) {
    if (gCurrLevelNum  != data->levelNum ) { gChangeLevel = data->levelNum; }

    sWarpDest.type     = data->warpType;
    sWarpDest.levelNum = data->warpLevelNum;
    sWarpDest.areaIdx  = data->warpAreaIdx;
    sWarpDest.nodeId   = data->warpNodeId;
    sWarpDest.arg      = data->warpArg;

    gInWarpCheckpoint          = data->inWarpCheckpoint;
    gTTCSpeedSetting           = data->ttcSpeedSetting;
    D_80339EE0                 = data->D_80339EE0;
    gPaintingMarioYEntry       = data->paintingMarioYEntry;
    gControlledWarpGlobalIndex = data->controlledWarpGlobalIndex;

    gCurrLevelNum = data->levelNum;
    gCurrAreaIndex = data->areaIndex;
    gCurrActNum = data->actNum;

    LOG_INFO("do warp: %d, %d, %d", gCurrLevelNum, gCurrAreaIndex, gCurrActNum);
}

void network_receive_level_warp_2(struct Packet* p) {
    struct PacketLevelWarp2Data remote = { 0 };
    packet_read(p, &remote, sizeof(struct PacketLevelWarp2Data));
    LOG_INFO("rx warp: %d, %d, %d", remote.levelNum, remote.areaIndex, remote.actNum);

    u8 levelOrAreaDifference = (gCurrLevelNum != remote.levelNum) || (gCurrAreaIndex != remote.areaIndex);

    if (gNetworkType == NT_SERVER) {
        f32 elapsed = (clock() - sSavedClockTime) / (f32)CLOCKS_PER_SEC;
        if (elapsed < SERVER_RETAIN_WARP_SECONDS || !levelOrAreaDifference) {
            network_send_level_warp_2(FALSE, gNetworkPlayerLocal->globalIndex);
            return;
        }
    }

    if (levelOrAreaDifference) {
        do_warp(&remote);
    }

    if (gNetworkType == NT_CLIENT) {
        sSavedLevelWarp2Data = remote;
        sSavedClockTime = clock();
    }

    if (gNetworkType == NT_SERVER) {
        network_send_level_warp_2(TRUE, remote.controlledWarpGlobalIndex);
    } else {
        sCurrPlayMode = PLAY_MODE_NORMAL;
        network_on_init_level();
    }
}

u8 network_is_warp_2_duplicate(void) {
    struct PacketLevelWarp2Data data = { 0 };
    populate_packet_data(&data);

    if (data.levelNum == 1 && data.areaIndex == 1) { return TRUE; }

    if (gNetworkType == NT_SERVER) {
        f32 elapsed = (clock() - sSavedClockTime) / (f32)CLOCKS_PER_SEC;
        if (elapsed >= SERVER_RETAIN_WARP_SECONDS) { return FALSE; }
    }
    return (memcmp(&sSavedLevelWarp2Data, &data, sizeof(struct PacketLevelWarp2Data)) == 0);
}