#ifndef NETWORK_PLAYER_H
#define NETWORK_PLAYER_H

#include <stdbool.h>
#include "network.h"

#define UNKNOWN_LOCAL_INDEX ((u8)-1)
#define UNKNOWN_GLOBAL_INDEX ((u8)-1)
#define UNKNOWN_NETWORK_INDEX ((u64)-1)
#define NETWORK_PLAYER_TIMEOUT 10
#define MAX_RX_SEQ_IDS 16

enum NetworkPlayerType {
    NPT_UNKNOWN,
    NPT_LOCAL,
    NPT_SERVER,
    NPT_CLIENT,
};

struct NetworkPlayer {
    bool connected;
    enum NetworkPlayerType type;
    u8 localIndex;
    u8 globalIndex;
    clock_t lastReceived;
    clock_t lastSent;
    u16 currLevelAreaSeqId;
    s16 currCourseNum;
    s16 currActNum;
    s16 currLevelNum;
    s16 currAreaIndex;
    bool currLevelSyncValid;
    bool currAreaSyncValid;
    u8 fadeOpacity;
    u16 rxSeqIds[MAX_RX_SEQ_IDS];
    u8 onRxSeqId;
};

extern struct NetworkPlayer gNetworkPlayers[];
extern struct NetworkPlayer* gNetworkPlayerLocal;
extern struct NetworkPlayer* gNetworkPlayerServer;

bool network_player_any_connected(void);
u8 network_player_connected_count(void);
struct NetworkPlayer* network_player_from_global_index(u8 globalIndex);
struct NetworkPlayer* get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum);
struct NetworkPlayer* get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);
struct NetworkPlayer* get_network_player_smallest_global(void);
void network_player_update(void);
u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex);
u8 network_player_disconnected(u8 globalIndex);
void network_player_shutdown(void);

#endif
