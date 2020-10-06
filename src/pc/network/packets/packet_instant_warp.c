#include <stdio.h>
#include "sm64.h"
#include "../network.h"
#include "engine/math_util.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/ingame_menu.h"
#include "game/mario.h"
#define DISABLE_MODULE_LOG
#include "pc/debuglog.h"

extern u8 gRejectInstantWarp;

static u8 seqId = 0;
static u8 remoteLastSeqId = (u8)-1;

#pragma pack(1)
struct PacketInstantWarpData {
    u8 seqId;
    Vec3f pos;
    s16 areaIndex;
    s16 yaw;
};

static void populate_packet_data(struct PacketInstantWarpData* data) {
    data->seqId = seqId;
    data->pos[0] = gMarioStates[0].pos[0];
    data->pos[1] = gMarioStates[0].pos[1];
    data->pos[2] = gMarioStates[0].pos[2];
    data->yaw = gMarioStates[0].faceAngle[1];
    data->areaIndex = gCurrAreaIndex;
}

void network_send_instant_warp(void) {

    struct PacketInstantWarpData data = { 0 };
    populate_packet_data(&data);

    struct Packet p;
    packet_init(&p, PACKET_INSTANT_WARP, true, false);
    packet_write(&p, &data, sizeof(struct PacketInstantWarpData));
    network_send(&p);
    LOG_INFO("tx %d", data.areaIndex);

    gRejectInstantWarp = 120;

    seqId++;
}

void network_receive_instant_warp(struct Packet* p) {
    struct PacketInstantWarpData remote = { 0 };
    packet_read(p, &remote, sizeof(struct PacketInstantWarpData));

    // de-dup
    if (remote.seqId == remoteLastSeqId) {
        LOG_INFO("we've seen this packet, escape!");
        return;
    }
    remoteLastSeqId = remote.seqId;

    LOG_INFO("rx instant warp");

    if (gCurrAreaIndex == remote.areaIndex) {
        if (sCurrPlayMode == PLAY_MODE_SYNC_LEVEL) { sCurrPlayMode = PLAY_MODE_NORMAL; }
        LOG_INFO("instant warp done %d", remote.areaIndex);
        return;
    }

    gMarioStates[0].pos[0] = remote.pos[0];
    gMarioStates[0].pos[1] = remote.pos[1];
    gMarioStates[0].pos[2] = remote.pos[2];
    vec3f_copy(gMarioStates[0].nonInstantWarpPos, gMarioStates[0].pos);

    gMarioStates[0].marioObj->oPosX = gMarioStates[0].pos[0];
    gMarioStates[0].marioObj->oPosY = gMarioStates[0].pos[1];
    gMarioStates[0].marioObj->oPosZ = gMarioStates[0].pos[2];

    /*gMarioStates[0].faceAngle[1] = remote.yaw;
    gMarioStates[0].intendedYaw = remote.yaw;
    gMarioStates[0].marioObj->oMoveAngleYaw = remote.yaw;
    gMarioStates[0].marioObj->oFaceAngleYaw = remote.yaw;*/

    for (int i = 0; i < MAX_PLAYERS; i++) {
        gMarioStates[i].marioObj->oIntangibleTimer = 30;
        force_idle_state(&gMarioStates[i]);
    }

    //s16 cameraAngle = gMarioStates[0].area->camera->yaw;
    change_area(remote.areaIndex);
    for (int i = 0; i < MAX_PLAYERS; i++) { gMarioStates[i].area = gCurrentArea; }

    //warp_camera(warp->displacement[0], warp->displacement[1], warp->displacement[2]);
    //gMarioStates[0].area->camera->yaw = cameraAngle;
    LOG_INFO("instant warp applied %d", remote.areaIndex);
    network_send_instant_warp();
}
