#ifndef NETWORK_H
#define NETWORK_H

#include <PR/ultratypes.h>
#include <time.h>
#include "types.h"
#include <assert.h>
#include "network_player.h"
#include "network_utils.h"
#include "packets/packet.h"
#include "sync_object.h"
#include "pc/utils/string_linked_list.h"
#include "../cliopts.h"

#define SET_BIT(val, num) ((((u8)(val)) & 0x01) << (num));
#define GET_BIT(val, num) (((val) >> (num)) & 0x01)

// Mario 64 specific externs
extern struct MarioState gMarioStates[];

#define SYNC_DISTANCE_ONLY_DEATH -1.0f
#define SYNC_DISTANCE_ONLY_EVENTS -2.0f
#define SYNC_DISTANCE_INFINITE 0
#define PACKET_LENGTH 3000
#define NETWORKTYPESTR (gNetworkType == NT_CLIENT                            \
                        ? "Client"                                           \
                        : (gNetworkType == NT_SERVER ? "Server" : " None ")) \

#ifdef DEVELOPMENT
#define SOFT_ASSERT(_condition) { if (!(_condition)) { LOG_ERROR("failed assert at line %d", __LINE__); assert(_condition); } }
#define SOFT_ASSERT_RETURN(_condition, _retval) { if (!(_condition)) { LOG_ERROR("failed assert at line %d", __LINE__); assert(_condition); } }
#else
#define SOFT_ASSERT(_condition) { if (!(_condition)) { LOG_ERROR("failed soft assert at line %d", __LINE__); return; } }
#define SOFT_ASSERT_RETURN(_condition, _retval) { if (!(_condition)) { LOG_ERROR("failed soft assert at line %d", __LINE__); return _retval; } }
#endif

enum NetworkSystemType {
    NS_SOCKET,
    NS_COOPNET,
    NS_MAX,
};

struct NetworkSystem {
    bool (*initialize)(enum NetworkType, bool reconnecting);
    s64 (*get_id)(u8 localIndex);
    char* (*get_id_str)(u8 localIndex);
    void (*save_id)(u8 localIndex, s64 networkId);
    void (*clear_id)(u8 localIndex);
    void* (*dup_addr)(u8 localIndex);
    bool (*match_addr)(void* addr1, void* addr2);
    void (*update)(void);
    int  (*send)(u8 localIndex, void* addr, u8* data, u16 dataLength);
    void (*get_lobby_id)(char* destination, u32 destLength);
    void (*get_lobby_secret)(char* destination, u32 destLength);
    void (*shutdown)(bool reconnecting);
    bool requireServerBroadcast;
    char* name;
};

enum PlayerInteractions {
    PLAYER_INTERACTIONS_NONE,
    PLAYER_INTERACTIONS_SOLID,
    PLAYER_INTERACTIONS_PVP,
};

enum BouncyLevelBounds {
    BOUNCY_LEVEL_BOUNDS_OFF,
    BOUNCY_LEVEL_BOUNDS_ON,
    BOUNCY_LEVEL_BOUNDS_ON_CAP,
};

enum PvpType {
    PLAYER_PVP_CLASSIC,
    PLAYER_PVP_REVAMPED
};

struct ServerSettings {
    enum PlayerInteractions playerInteractions;
    enum BouncyLevelBounds bouncyLevelBounds;
    enum PvpType pvpType;
    u8 playerKnockbackStrength;
    u8 stayInLevelAfterStar;
    u8 skipIntro;
    u8 bubbleDeath;
    u8 enablePlayersInLevelDisplay;
    u8 enablePlayerList;
    u8 headlessServer;
    u8 nametags;
    u8 maxPlayers;
    u8 pauseAnywhere;
};

struct NametagsSettings {
    bool showHealth;
    bool showSelfTag;
};

// Networking-specific externs
extern struct NetworkSystem* gNetworkSystem;
extern enum NetworkType gNetworkType;
extern bool gNetworkAreaLoaded;
extern bool gNetworkAreaSyncing;
extern u32 gNetworkAreaTimer;
extern u32 gNetworkAreaTimerClock;
extern void* gNetworkServerAddr;
extern struct ServerSettings gServerSettings;
extern struct NametagsSettings gNametagsSettings;
extern bool gNetworkSentJoin;
extern u16 gNetworkRequestLocationTimer;
extern u8 gDebugPacketIdBuffer[];
extern u8 gDebugPacketSentBuffer[];
extern u8 gDebugPacketOnBuffer;
extern u32 gNetworkStartupTimer;

// network.c
void network_set_system(enum NetworkSystemType nsType);
bool network_init(enum NetworkType inNetworkType, bool reconnecting);
void network_on_init_area(void);
void network_on_loaded_area(void);
bool network_allow_unknown_local_index(enum PacketType packetType);
void network_send_to(u8 localIndex, struct Packet* p);
void network_send(struct Packet* p);
void network_receive(u8 localIndex, void* addr, u8* data, u16 dataLength);
void* network_duplicate_address(u8 localIndex);
void network_reset_reconnect_and_rehost(void);
void network_reconnect_begin(void);
bool network_is_reconnecting(void);
void network_rehost_begin(void);
void network_update(void);
void network_shutdown(bool sendLeaving, bool exiting, bool popup, bool reconnecting);

#endif
