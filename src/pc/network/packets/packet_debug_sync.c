#include "../network.h"
#include "behavior_table.h"
#include "pc/debuglog.h"

static void print_sync_object_table(void) {
    LOG_INFO("Sync Object Table");
    for (s32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        u32 behaviorId = get_id_from_behavior(gSyncObjects[i].behavior);
        LOG_INFO("%03d: %08X", i, behaviorId);
        behaviorId = behaviorId; // suppress warning
    }
    LOG_INFO(" ");
}

void network_send_debug_sync(void) {
    u8 objectCount = 0;
    for (s32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        objectCount++;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DEBUG_SYNC, true, PLMT_AREA);
    packet_write(&p, &objectCount, sizeof(u8));
    for (s32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        u32 behaviorId = get_id_from_behavior((gSyncObjects[i].behavior == NULL) ? gSyncObjects[i].behavior : gSyncObjects[i].o->behavior);
        packet_write(&p, &i, sizeof(u8));
        packet_write(&p, &behaviorId, sizeof(u32));
    }
    network_send(&p);
}

void network_receive_debug_sync(struct Packet* p) {
    u8 objectCount = 0;
    u32 remoteBehaviorIds[MAX_SYNC_OBJECTS] = { 0 };

    packet_read(p, &objectCount, sizeof(u8));
    for (s32 i = 0; i < objectCount; i++) {
        u8 j;
        u32 behaviorId;
        packet_read(p, &j, sizeof(u8));
        packet_read(p, &behaviorId, sizeof(u32));
        remoteBehaviorIds[j] = behaviorId;
    }

    bool hasMismatch = false;
    for (s32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        u32 localBehaviorId = (gSyncObjects[i].o == NULL) ? 0 : get_id_from_behavior(gSyncObjects[i].behavior);
        u32 remoteBehaviorId = remoteBehaviorIds[i];
        if (localBehaviorId != remoteBehaviorId) {
            hasMismatch = true;
            break;
        }
    }
    if (!hasMismatch) { return; }

    LOG_INFO(" ");
    LOG_INFO("Sync Object Table Mismatch");
    for (s32 i = 0; i < MAX_SYNC_OBJECTS; i++) {
        u32 localBehaviorId = (gSyncObjects[i].o == NULL) ? 0 : get_id_from_behavior(gSyncObjects[i].behavior);
        u32 remoteBehaviorId = remoteBehaviorIds[i];
        if (localBehaviorId == 0 && remoteBehaviorId == 0) { continue; }
        LOG_INFO("%03d:  %04X  %04X  %s", i, localBehaviorId, remoteBehaviorId, (localBehaviorId == remoteBehaviorId) ? "   " : "<<<");
    }
}
