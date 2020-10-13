#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "behavior_data.h"
#include "src/game/behavior_actions.h"
#include "pc/debuglog.h"

extern struct Object* gCurrentObject;

void network_send_spawn_star(struct Object* o, u8 starType, f32 x, f32 y, f32 z, u32 behParams) {
    struct Packet p;
    packet_init(&p, PACKET_SPAWN_STAR, true, true);
    packet_write(&p, &starType, sizeof(u8));
    packet_write(&p, &x, sizeof(f32));
    packet_write(&p, &y, sizeof(f32));
    packet_write(&p, &z, sizeof(f32));
    packet_write(&p, &behParams, sizeof(u32));

    packet_write(&p, &o->oPosX, sizeof(u32) * 3);
    packet_write(&p, &o->oHomeX, sizeof(u32) * 3);

    network_send(&p);
}

void network_receive_spawn_star(struct Packet* p) {
    u8 starType;
    f32 x, y, z;
    u32 behParams;

    packet_read(p, &starType, sizeof(u8));
    packet_read(p, &x, sizeof(f32));
    packet_read(p, &y, sizeof(f32));
    packet_read(p, &z, sizeof(f32));
    packet_read(p, &behParams, sizeof(u32));

    u32 oldBehParams = gCurrentObject->oBehParams;
    gCurrentObject->oBehParams = behParams;
    struct Object* o = NULL;
    switch (starType) {
        case 0: o = spawn_default_star(x, y, z); break;
        case 1: o = spawn_red_coin_cutscene_star(x, y, z); break;
        case 2: o = spawn_no_exit_star(x, y, z); break;
        default: LOG_ERROR("UNKNOWN SPAWN STAR %d", starType);
    }
    gCurrentObject->oBehParams = oldBehParams;

    if (o != NULL) {
        packet_read(p, &o->oPosX, sizeof(u32) * 3);
        packet_read(p, &o->oHomeX, sizeof(u32) * 3);
    }
}

void network_send_spawn_star_nle(struct Object* o, u32 params) {
    u8 globalIndex = UNKNOWN_GLOBAL_INDEX;
    if (o->behavior == bhvMario) {
        u8 localIndex = o->oBehParams - 1;
        globalIndex = gNetworkPlayers[localIndex].globalIndex;
    }

    struct Packet p;
    packet_init(&p, PACKET_SPAWN_STAR_NLE, true, true);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &o->oSyncID, sizeof(u32));
    packet_write(&p, &params, sizeof(u32));

    network_send(&p);
}

void network_receive_spawn_star_nle(struct Packet* p) {
    u8 globalIndex = UNKNOWN_GLOBAL_INDEX;
    u32 syncId = 0;
    u32 params = 0;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &syncId, sizeof(u32));
    packet_read(p, &params, sizeof(u32));

    // grab network player first
    struct Object* object = NULL;
    if (globalIndex != UNKNOWN_GLOBAL_INDEX) {
        struct NetworkPlayer* np = network_player_from_global_index(globalIndex);
        if (np != NULL) {
            object = gMarioStates[np->localIndex].marioObj;
        }
    }

    // check for sync id
    if (object == NULL) {
        object = gSyncObjects[syncId].o;
    }

    // sanity check object
    if (object == NULL) {
        LOG_ERROR("Could not find object to attach to. %d %d", globalIndex, syncId);
        return;
    }

    // spawn
    bhv_spawn_star_no_level_exit(object, params, FALSE);
}
