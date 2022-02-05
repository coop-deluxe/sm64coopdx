#include "../network.h"
#include "behavior_table.h"
#include "pc/debuglog.h"

static void print_sync_object_table(void) {
    LOG_INFO("Sync Object Table");
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        u16 behaviorId = get_id_from_behavior(gSyncObjects[i].behavior);
        LOG_INFO("%03d: %04X", i, behaviorId);
        behaviorId = behaviorId; // suppress warning
    }
    LOG_INFO(" ");
}

void network_send_debug_sync(void) {
    u8 objectCount = 0;
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        objectCount++;
    }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_DEBUG_SYNC, true, PLMT_AREA);
    packet_write(&p, &objectCount, sizeof(u8));
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        if (gSyncObjects[i].o == NULL) { continue; }
        u16 behaviorId = get_id_from_behavior((gSyncObjects[i].behavior == NULL) ? gSyncObjects[i].behavior : gSyncObjects[i].o->behavior);
        packet_write(&p, &i, sizeof(u8));
        packet_write(&p, &behaviorId, sizeof(u16));
    }
    network_send(&p);
}

void network_receive_debug_sync(struct Packet* p) {
    u8 objectCount = 0;
    u16 remoteBehaviorIds[MAX_SYNC_OBJECTS] = { 0 };

    packet_read(p, &objectCount, sizeof(u8));
    for (int i = 0; i < objectCount; i++) {
        u8 j;
        u16 behaviorId;
        packet_read(p, &j, sizeof(u8));
        packet_read(p, &behaviorId, sizeof(u16));
        remoteBehaviorIds[j] = behaviorId;
    }

    bool hasMismatch = false;
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        u16 localBehaviorId = (gSyncObjects[i].o == NULL) ? 0 : get_id_from_behavior(gSyncObjects[i].behavior);
        u16 remoteBehaviorId = remoteBehaviorIds[i];
        if (localBehaviorId != remoteBehaviorId) {
            hasMismatch = true;
            break;
        }
    }
    if (!hasMismatch) { return; }

    extern s16 gCurrCourseNum;
    if (gCurrCourseNum == 0) { return; }

    LOG_INFO(" ");
    LOG_INFO("Sync Object Table Mismatch");
    for (int i = 0; i < MAX_SYNC_OBJECTS; i++) {
        u16 localBehaviorId = (gSyncObjects[i].o == NULL) ? 0 : get_id_from_behavior(gSyncObjects[i].behavior);
        u16 remoteBehaviorId = remoteBehaviorIds[i];
        if (localBehaviorId == 0 && remoteBehaviorId == 0) { continue; }
        LOG_INFO("%03d:  %04X  %04X  %s", i, localBehaviorId, remoteBehaviorId, (localBehaviorId == remoteBehaviorId) ? "   " : "<<<");
    }
}
