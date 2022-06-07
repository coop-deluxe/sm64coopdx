#include "../network.h"
#include "behavior_table.h"
#include "pc/debuglog.h"

static void print_sync_object_table(void) {
    LOG_INFO("Sync Object Table");
    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        if (!so || !so->o) { continue; }
        u32 behaviorId = get_id_from_behavior(so->behavior);
        LOG_INFO("%03d: %08X", so->id, behaviorId);
        behaviorId = behaviorId; // suppress warning
    }
    LOG_INFO(" ");
}

void network_send_debug_sync(void) {
    u16 objectCount = 0;
    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        if (!so || !so->o) { continue; }
        objectCount++;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DEBUG_SYNC, true, PLMT_AREA);
    packet_write(&p, &objectCount, sizeof(u16));
    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        if (!so || !so->o) { continue; }
        u32 behaviorId = get_id_from_behavior((so->behavior == NULL) ? so->behavior : so->o->behavior);
        packet_write(&p, &so->id, sizeof(u32));
        packet_write(&p, &behaviorId, sizeof(u32));
    }
    network_send(&p);
}

void network_receive_debug_sync(struct Packet* p) {
    u16 objectCount = 0;
    u32 remoteBehaviorIds[1024] = { 0 };

    packet_read(p, &objectCount, sizeof(u16));
    for (s32 i = 0; i < objectCount; i++) {
        u32 j;
        u32 behaviorId;
        packet_read(p, &j, sizeof(u32));
        packet_read(p, &behaviorId, sizeof(u32));
        remoteBehaviorIds[j] = behaviorId;
    }

    bool hasMismatch = false;
    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        u32 localBehaviorId = (so && so->o) ? get_id_from_behavior(so->behavior) : 0;
        u32 remoteBehaviorId = remoteBehaviorIds[so->id];
        if (localBehaviorId != remoteBehaviorId) {
            hasMismatch = true;
            break;
        }
    }
    if (!hasMismatch) { return; }

    LOG_INFO(" ");
    LOG_INFO("Sync Object Table Mismatch");
    for (struct SyncObject* so = sync_object_get_first(); so != NULL; so = sync_object_get_next()) {
        u32 localBehaviorId = (so && so->o) ? get_id_from_behavior(so->behavior) : 0;
        u32 remoteBehaviorId = remoteBehaviorIds[so->id];
        if (localBehaviorId == 0 && remoteBehaviorId == 0) { continue; }
        LOG_INFO("%03d:  %04X  %04X  %s", so->id, localBehaviorId, remoteBehaviorId, (localBehaviorId == remoteBehaviorId) ? "   " : "<<<");
    }
}
