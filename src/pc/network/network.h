#ifndef NETWORK_H
#define NETWORK_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include "network_player.h"
#include "network_utils.h"
#include "packets/packet.h"
#include "pc/utils/string_linked_list.h"
#include "../cliopts.h"

#define SET_BIT(val, num) ((((u8)(val)) & 0x01) << (num));
#define GET_BIT(val, num) (((val) >> (num)) & 0x01)

// Mario 64 specific externs
extern struct MarioState gMarioStates[];

#define SYNC_DISTANCE_ONLY_DEATH -1.0f
#define SYNC_DISTANCE_ONLY_EVENTS -2.0f
#define SYNC_DISTANCE_INFINITE 0
#define MAX_SYNC_OBJECTS 256 // note: increasing this requires code to be rewritten
#define MAX_SYNC_OBJECT_FIELDS 64
#define PACKET_LENGTH 1024
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
    NS_DISCORD,
};

struct NetworkSystem {
    bool (*initialize)(enum NetworkType);
    s64 (*get_id)(u8 localIndex);
    void (*save_id)(u8 localIndex, s64 networkId);
    void (*clear_id)(u8 localIndex);
    void* (*dup_addr)(u8 localIndex);
    bool (*match_addr)(void* addr1, void* addr2);
    void (*update)(void);
    int  (*send)(u8 localIndex, void* addr, u8* data, u16 dataLength);
    void (*shutdown)(void);
    bool requireServerBroadcast;
};

struct SyncObject {
    struct Object* o;
    float maxSyncDistance;
    bool owned;
    f32 clockSinceUpdate;
    void* behavior;
    u16 txEventId;
    u16 rxEventId[MAX_PLAYERS];
    u16 randomSeed;
    u8 extraFieldCount;
    bool fullObjectSync;
    bool syncDeathEvent;
    bool hasStandardFields;
    float minUpdateRate;
    float maxUpdateRate;
    u8 (*ignore_if_true)(void);
    void (*on_received_pre)(u8 fromLocalIndex);
    void (*on_received_post)(u8 fromLocalIndex);
    void (*on_sent_pre)(void);
    void (*on_sent_post)(void);
    void (*override_ownership)(u8* shouldOverride, u8* shouldOwn);
    void (*on_forget)(void);
    void* extraFields[MAX_SYNC_OBJECT_FIELDS];
    bool rememberLastReliablePacket;
    bool lastReliablePacketIsStale;
};

enum PlayerInteractions {
    PLAYER_INTERACTIONS_NONE,
    PLAYER_INTERACTIONS_SOLID,
    PLAYER_INTERACTIONS_PVP,
};

struct ServerSettings {
    enum PlayerInteractions playerInteractions;
    u8 playerKnockbackStrength;
    u8 stayInLevelAfterStar;
    u8 skipIntro;
    u8 shareLives;
    u8 enableCheats;
    u8 bubbleDeath;
    u8 headlessServer;
};

// Networking-specific externs
extern struct NetworkSystem* gNetworkSystem;
extern enum NetworkType gNetworkType;
extern bool gNetworkAreaLoaded;
extern bool gNetworkAreaSyncing;
extern u32 gNetworkAreaTimer;
extern u32 gNetworkAreaTimerClock;
extern void* gNetworkServerAddr;
extern struct SyncObject gSyncObjects[];
extern struct ServerSettings gServerSettings;
extern struct StringLinkedList gRegisteredMods;
extern bool gNetworkSentJoin;

// network.c
void network_set_system(enum NetworkSystemType nsType);
bool network_init(enum NetworkType inNetworkType);
void network_on_init_area(void);
void network_on_loaded_area(void);
bool network_allow_unknown_local_index(enum PacketType packetType);
void network_send_to(u8 localIndex, struct Packet* p);
void network_send(struct Packet* p);
void network_receive(u8 localIndex, void* addr, u8* data, u16 dataLength);
void* network_duplicate_address(u8 localIndex);
void network_update(void);
void network_register_mod(char* modName);
void network_shutdown(bool sendLeaving);

#endif
