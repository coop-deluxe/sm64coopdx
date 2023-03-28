#include "../network.h"
#include "behavior_table.h"
#include "pc/debuglog.h"
#include "object_fields.h"

void print_sync_object_table(void) {
    LOG_INFO("Sync Object Table");
    for (u32 i = 0; i < SYNC_ID_BLOCK_SIZE * (MAX_PLAYERS + 1); i++) {
        struct SyncObject* so = sync_object_get(i);
        if (!so || !so->o) { continue; }
        u32 behaviorId = get_id_from_behavior(so->behavior);
        char* behaviorName = (char*)get_behavior_name_from_id(behaviorId);
        if (!behaviorName) { behaviorName = "UNKNOWN"; }
        LOG_INFO("%04d: %08X :: %s", so->id, behaviorId, behaviorName);
        if (so->o->oSyncID != so->id) {
            LOG_INFO("^^^^^^^^^^^^^^^^^^^^^ %u != %u", so->o->oSyncID, so->id);
        }
        behaviorId = behaviorId; // suppress warning
    }
    LOG_INFO(" ");
}

void network_send_debug_sync(void) {
    // check for lag
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        if (np->ping > 250) { return; }
    }

    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        if (!so || !so->o) { continue; }
        u32 behaviorId = get_id_from_behavior((so->behavior == NULL) ? so->behavior : so->o->behavior);
        struct Packet p = { 0 };
        packet_init(&p, PACKET_DEBUG_SYNC, false, PLMT_AREA);
        packet_write(&p, &so->id, sizeof(u32));
        packet_write(&p, &behaviorId, sizeof(u32));
        network_send(&p);
    }
}

void network_receive_debug_sync(struct Packet* p) {
    u32 id;
    u32 behaviorId;

    packet_read(p, &id, sizeof(u32));
    packet_read(p, &behaviorId, sizeof(u32));

    char* behaviorName = (char*)get_behavior_name_from_id(behaviorId);
    if (!behaviorName) { behaviorName = "UNKNOWN"; }

    struct SyncObject* so = sync_object_get(id);
    if (!so) {
        LOG_INFO("Sync Table Missing: %04d : %08X :: %s", id, behaviorId, behaviorName);
        return;
    }

    u32 localBehaviorId = get_id_from_behavior((so->behavior == NULL) ? so->behavior : so->o->behavior);
    char* localBehaviorName = (char*)get_behavior_name_from_id(localBehaviorId);
    if (!localBehaviorName) { localBehaviorName = "UNKNOWN"; }

    if (localBehaviorId != behaviorId) {
        LOG_INFO("Sync Table MisMatch: %04d : %08X != %08X :: (%s != %s)", id, localBehaviorId, behaviorId, localBehaviorName, behaviorName);
        return;
    }

}
