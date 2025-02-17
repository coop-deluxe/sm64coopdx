#include <stdio.h>
#include "../network.h"
#include "object_fields.h"
#include "behavior_data.h"
#include "game/behavior_actions.h"
#include "pc/lua/smlua_hooks.h"
#include "pc/debuglog.h"

extern struct Object* gCurrentObject;

void network_send_spawn_star(struct Object* o, u8 starType, f32 x, f32 y, f32 z, u32 behParams, u8 networkPlayerIndex) {
    struct Packet p = { 0 };
    packet_init(&p, PACKET_SPAWN_STAR, true, PLMT_AREA);
    packet_write(&p, &starType, sizeof(u8));
    packet_write(&p, &x, sizeof(f32));
    packet_write(&p, &y, sizeof(f32));
    packet_write(&p, &z, sizeof(f32));
    packet_write(&p, &behParams, sizeof(u32));
    packet_write(&p, &networkPlayerIndex, sizeof(u8));

    packet_write(&p, &o->oPosX, sizeof(u32) * 3);
    packet_write(&p, &o->oHomeX, sizeof(u32) * 3);

    network_send(&p);
}

void network_receive_spawn_star(struct Packet* p) {
    u8 starType;
    f32 x, y, z;
    u32 behParams;
    u8 networkPlayerIndex = UNKNOWN_GLOBAL_INDEX;

    packet_read(p, &starType, sizeof(u8));
    packet_read(p, &x, sizeof(f32));
    packet_read(p, &y, sizeof(f32));
    packet_read(p, &z, sizeof(f32));
    packet_read(p, &behParams, sizeof(u32));
    packet_read(p, &networkPlayerIndex, sizeof(u8));

    struct Object* oldObject = gCurrentObject;
    struct Object* o = NULL;
    gCurrentObject = gMarioStates[0].marioObj;
    if (gCurrentObject) {
        u32 oldBehParams = gCurrentObject->oBehParams;
        gCurrentObject->oBehParams = behParams;
        switch (starType) {
            case 0: o = spawn_default_star(x, y, z); break;
            case 1: o = spawn_red_coin_cutscene_star(x, y, z); break;
            case 2: o = spawn_no_exit_star(x, y, z); break;
            default: LOG_ERROR("UNKNOWN SPAWN STAR %d", starType);
        }
        gCurrentObject->oBehParams = oldBehParams;
    }
    gCurrentObject = oldObject;

    if (o != NULL) {
        packet_read(p, &o->oPosX, sizeof(u32) * 3);
        packet_read(p, &o->oHomeX, sizeof(u32) * 3);

        // Here we check if we're supposed to play the cutscene or not depending on if
        // the global player index sent matches us.
        // If the network player index is -1, Then the cutscene will always be skipped.
        // This check is vital for objects which are network owned specfically.
        // Leaving this the only way to properly set the cutscene flags
        // for those who don't own the object.
        //printf("network_receive_spawn_star: Network Player Index is %i, Our Global Index is %i.\n", networkPlayerIndex, gNetworkPlayers[0].globalIndex);
        if (networkPlayerIndex == gNetworkPlayers[0].globalIndex) {
            o->oStarSpawnExtCutsceneFlags = 1;
        } else {
            o->oStarSpawnExtCutsceneFlags = 0;
        }
    }
}

void network_send_spawn_star_nle(struct Object* o, u32 params) {
    if (!o) { return; }
    u8 globalIndex = UNKNOWN_GLOBAL_INDEX;
    if (o->behavior == smlua_override_behavior(bhvMario)) {
        u8 localIndex = o->oBehParams - 1;
        if (localIndex < MAX_PLAYERS) { globalIndex = gNetworkPlayers[localIndex].globalIndex; }
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_SPAWN_STAR_NLE, true, PLMT_AREA);
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
    struct SyncObject* so = sync_object_get(syncId);
    if (object == NULL && so) {
        object = so->o;
    }

    // sanity check object
    if (object == NULL) {
        LOG_ERROR("Could not find object to attach to. %d %d", globalIndex, syncId);
        return;
    }

    // spawn
    bhv_spawn_star_no_level_exit(object, params, FALSE);
}
