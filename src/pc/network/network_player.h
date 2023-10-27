#ifndef NETWORK_PLAYER_H
#define NETWORK_PLAYER_H

#include <stdbool.h>
#include "network.h"
#include "pc/configfile.h"

#define UNKNOWN_LOCAL_INDEX ((u8)-1)
#define UNKNOWN_GLOBAL_INDEX ((u8)-1)
#define UNKNOWN_NETWORK_INDEX ((u64)-1)
#define NETWORK_PLAYER_TIMEOUT 15
#define NETWORK_PLAYER_PING_TIMEOUT 3
#define MAX_RX_SEQ_IDS 256
#define USE_REAL_PALETTE_VAR 0xFF

enum NetworkPlayerType {
    NPT_UNKNOWN,
    NPT_LOCAL,
    NPT_SERVER,
    NPT_CLIENT,
};

struct NetworkPlayer {
    bool connected;
    u8 type;
    u8 localIndex;
    u8 globalIndex;
    bool moderator;
    f32 lastReceived;
    f32 lastSent;
    f32 lastPingSent;
    u16 currLevelAreaSeqId;
    s16 currCourseNum;
    s16 currActNum;
    s16 currLevelNum;
    s16 currAreaIndex;
    bool currLevelSyncValid;
    bool currAreaSyncValid;
    bool currPositionValid;
    u8 fadeOpacity;
    u8 onRxSeqId;
    u8 modelIndex;
    u8 gag;
    u32 ping;
    struct PlayerPalette palette;
    char name[MAX_PLAYER_STRING+1];

    char description[MAX_DESCRIPTION_STRING+1];
    u8 descriptionR;
    u8 descriptionG;
    u8 descriptionB;
    u8 descriptionA;

    u8 overrideModelIndex;
    struct PlayerPalette overridePalette;

    u16 rxSeqIds[MAX_RX_SEQ_IDS];
    u32 rxPacketHash[MAX_RX_SEQ_IDS];

    // legacy fields to allow mods not to break
    u8 paletteIndex;
    u8 overridePaletteIndex;
    u8 overridePaletteIndexLp;
};

extern struct NetworkPlayer gNetworkPlayers[];
extern struct NetworkPlayer* gNetworkPlayerLocal;
extern struct NetworkPlayer* gNetworkPlayerServer;

void network_player_init(void);
void network_player_update_model(u8 localIndex);
bool network_player_any_connected(void);
u8 network_player_connected_count(void);
void network_player_set_description(struct NetworkPlayer* np, const char* description, u8 r, u8 g, u8 b, u8 a);

struct NetworkPlayer* network_player_from_global_index(u8 globalIndex);
struct NetworkPlayer* get_network_player_from_level(s16 courseNum, s16 actNum, s16 levelNum);
struct NetworkPlayer* get_network_player_from_area(s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);
struct NetworkPlayer* get_network_player_smallest_global(void);

void network_player_color_to_palette(struct NetworkPlayer *np, enum PlayerParts part, Color color);
void network_player_palette_to_color(struct NetworkPlayer *np, enum PlayerParts part, Color out);

void network_player_update(void);

u8 network_player_connected(enum NetworkPlayerType type, u8 globalIndex, u8 modelIndex, const struct PlayerPalette* playerPalette, const char* name);
u8 network_player_disconnected(u8 globalIndex);
void construct_player_popup(struct NetworkPlayer* np, char* msg, const char* level);

void network_player_update_course_level(struct NetworkPlayer* np, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);
void network_player_shutdown(bool popup);

#endif
