#include <stdio.h>
#include "../network.h"
#include "../reservation_area.h"
#include "pc/djui/djui.h"
#include "pc/debuglog.h"

#ifdef DEVELOPMENT
#include "behavior_table.h"

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

static void print_network_player_table(void) {
    LOG_INFO("Network Player Table");
    LOG_INFO("%5s %5s %8s %8s %8s %8s %8s", "gID", "lID", "course", "act", "level", "area", "valid");
    for (int i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) { continue; }
        LOG_INFO("%5d %5d %8d %8d %8d %8d %8d", np->globalIndex, np->localIndex, np->currCourseNum, np->currActNum, np->currLevelNum, np->currAreaIndex, np->currAreaSyncValid);
    }
    LOG_INFO(" ");
}
#endif

void network_send_chat(char* message, u8 globalIndex) {
    u16 messageLength = strlen(message);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_CHAT, true, PLMT_NONE);
    packet_write(&p, &globalIndex, sizeof(u8));
    packet_write(&p, &messageLength, sizeof(u16));
    packet_write(&p, message, messageLength * sizeof(u8));
    network_send(&p);

#ifdef DEVELOPMENT
    print_network_player_table();
    //reservation_area_debug();
    //print_sync_object_table();
#endif
}

void network_receive_chat(struct Packet* p) {
    u16 remoteMessageLength = 0;
    char remoteMessage[256] = { 0 };
    u8 globalIndex;

    packet_read(p, &globalIndex, sizeof(u8));
    packet_read(p, &remoteMessageLength, sizeof(u16));
    if (remoteMessageLength > 256) { remoteMessageLength = 255; }
    packet_read(p, &remoteMessage, remoteMessageLength * sizeof(u8));

    // add the message
    djui_chat_message_create_from(globalIndex, remoteMessage);
    LOG_INFO("rx chat: %s", remoteMessage);
    /*
#ifdef DEVELOPMENT
    print_network_player_table();
#endif
    */
}
