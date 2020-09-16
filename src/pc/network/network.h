#ifndef NETWORK_H
#define NETWORK_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include "packets/packet.h"
#include "../cliopts.h"

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

enum NetworkSystemType {
    NS_SOCKET,
    NS_DISCORD,
};

struct NetworkSystem {
    bool (*initialize)(enum NetworkType);
    void (*update)(void);
    int  (*send)(u8* data, u16 dataLength);
    void (*shutdown)(void);
};

struct SyncObject {
    struct Object* o;
    u16 reserved;
    float maxSyncDistance;
    bool owned;
    clock_t clockSinceUpdate;
    void* behavior;
    u16 txEventId;
    u16 rxEventId;
    u8 extraFieldCount;
    bool fullObjectSync;
    bool keepRandomSeed;
    bool syncDeathEvent;
    bool hasStandardFields;
    float maxUpdateRate;
    u8 (*ignore_if_true)(void);
    void (*on_received)(void);
    void* extraFields[MAX_SYNC_OBJECT_FIELDS];
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
};

// Networking-specific externs
extern bool gNetworkLevelLoaded;
extern enum NetworkType gNetworkType;
extern struct SyncObject gSyncObjects[];
extern struct ServerSettings gServerSettings;

// network.c
void network_set_system(enum NetworkSystemType nsType);
bool network_init(enum NetworkType inNetworkType);
void network_on_init_level(void);
void network_on_loaded_level(void);
void network_send(struct Packet* p);
void network_receive(u8* data, u16 dataLength);
void network_update(void);
void network_shutdown(void);

#endif
