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
    packet_write_uint8(&p, starType);
    packet_write_uint8(&p, networkPlayerIndex);
    packet_write_float32(&p, x);
    packet_write_float32(&p, y);
    packet_write_float32(&p, z);
    packet_write_uint32(&p, behParams);
    packet_write_float32(&p, o->oPosX);
    packet_write_float32(&p, o->oPosY);
    packet_write_float32(&p, o->oPosZ);
    packet_write_float32(&p, o->oHomeX);
    packet_write_float32(&p, o->oHomeY);
    packet_write_float32(&p, o->oHomeZ);

    network_send(&p);
    packet_clear(&p);
}

void network_receive_spawn_star(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= (sizeof(u8) * 2) + (sizeof(f32) * 9) + sizeof(u32));
    
    u8 starType = packet_read_uint8(p);
    u8 networkPlayerIndex = packet_read_uint8(p);
    f32 x = packet_read_float32(p);
    f32 y = packet_read_float32(p);
    f32 z = packet_read_float32(p);
    u32 behParams = packet_read_uint32(p);

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
        o->oPosX = packet_read_float32(p);
        o->oPosY = packet_read_float32(p);
        o->oPosZ = packet_read_float32(p);
        o->oHomeX = packet_read_float32(p);
        o->oHomeY = packet_read_float32(p);
        o->oHomeZ = packet_read_float32(p);

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
    if (o->behavior == bhvMario) {
        u8 localIndex = o->oBehParams - 1;
        if (localIndex < MAX_PLAYERS) { globalIndex = gNetworkPlayers[localIndex].globalIndex; }
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_SPAWN_STAR_NLE, true, PLMT_AREA);
    packet_write_uint8(&p, globalIndex);
    packet_write_uint32(&p, o->oSyncID);
    packet_write_uint32(&p, params);

    network_send(&p);
    packet_clear(&p);
}

void network_receive_spawn_star_nle(struct Packet* p) {
    if (p == NULL) { return; }
    
    // Sanity check for data contents. Read will throw an error anyways,
    // But it's better to catch malformed or maliciously formed packets here.
    SOFT_ASSERT(packet_get_remaining_size(p) >= sizeof(u8) + (sizeof(u32) * 2));
  
    u8 globalIndex = packet_read_uint8(p);
    u32 syncId = packet_read_uint32(p);
    u32 params = packet_read_uint32(p);

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
