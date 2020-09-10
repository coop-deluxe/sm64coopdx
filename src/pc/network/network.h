#ifndef NETWORK_H
#define NETWORK_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include "../cliopts.h"

// Mario 64 specific externs
extern struct MarioState gMarioStates[];

#define SYNC_DISTANCE_ONLY_DEATH -1.0f
#define SYNC_DISTANCE_ONLY_EVENTS -2.0f
#define SYNC_DISTANCE_INFINITE 0
#define MAX_SYNC_OBJECTS 256 // note: increasing this requires code to be rewritten
#define MAX_SYNC_OBJECT_FIELDS 64
#define PACKET_LENGTH 1024
#define NETWORKTYPESTR (gNetworkType == NT_CLIENT ? "Client" : "Server")

enum PacketType {
    PACKET_ACK,
    PACKET_PLAYER,
    PACKET_OBJECT,
    PACKET_SPAWN_OBJECTS,
    PACKET_SPAWN_STAR,
    PACKET_LEVEL_WARP,
    PACKET_INSIDE_PAINTING,
    PACKET_COLLECT_STAR,
    PACKET_COLLECT_COIN,
    PACKET_COLLECT_ITEM,
    PACKET_RESERVATION_REQUEST,
    PACKET_RESERVATION,
    PACKET_SAVE_FILE_REQUEST,
    PACKET_SAVE_FILE,
    PACKET_CUSTOM = 255,
};

struct Packet {
    u16 dataLength;
    u16 cursor;
    bool error;
    bool reliable;
    u16 seqId;
    bool sent;
    u8 buffer[PACKET_LENGTH];
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
    u8 (*ignore_if_true)(struct Object*);
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
void network_init(enum NetworkType inNetworkType, char* ip, unsigned int port);
void network_on_init_level(void);
void network_on_loaded_level(void);
void network_send(struct Packet* p);
void network_update(void);
void network_shutdown(void);

// packet_read_write.c
void packet_init(struct Packet* packet, enum PacketType packetType, bool reliable);
void packet_write(struct Packet* packet, void* data, u16 length);
void packet_read(struct Packet* packet, void* data, u16 length);
u32 packet_hash(struct Packet* packet);
bool packet_check_hash(struct Packet* packet);

// packet_reliable.c
void network_send_ack(struct Packet* p);
void network_receive_ack(struct Packet* p);
void network_remember_reliable(struct Packet* p);
void network_update_reliable(void);

// packet_player.c
void network_update_player(void);
void network_receive_player(struct Packet* p);

// packet_object.c
struct SyncObject* network_init_object(struct Object* object, float maxSyncDistance);
void network_init_object_field(struct Object* o, void* field);
bool network_owns_object(struct Object* o);
bool network_sync_object_initialized(struct Object* o);
void network_clear_sync_objects(void);
void network_set_sync_id(struct Object* o);
void network_send_object(struct Object* o);
void network_send_object_reliability(struct Object* o, bool reliable);
void network_receive_object(struct Packet* p);
void network_forget_sync_object(struct SyncObject* so);
void network_update_objects(void);

// packet_spawn_object.c
void network_send_spawn_objects(struct Object* objects[], u32 models[], u8 objectCount);
void network_receive_spawn_objects(struct Packet* p);

// packet_spawn_star.c
void network_send_spawn_star(struct Object* o, u8 starType, f32 x, f32 y, f32 z, u32 behParams);
void network_receive_spawn_star(struct Packet* p);

// packet_level_warp.c
void network_send_level_warp(u8 done);
void network_receive_level_warp(struct Packet* p);

// packet_inside_painting.c
void network_send_inside_painting(u8 startOfEvent, u8 endOfEvent);
void network_receive_inside_painting(struct Packet* p);

// packet_collect_star.c
void network_send_collect_star(struct Object* o, s16 coinScore, s16 starIndex);
void network_receive_collect_star(struct Packet* p);

// packet_collect_coin.c
void network_send_collect_coin(struct Object* o);
void network_receive_collect_coin(struct Packet* p);

// packet_collect_item.c
void network_send_collect_item(struct Object* o);
void network_receive_collect_item(struct Packet* p);

// packet_reservation.c
void network_send_reservation_request(void);
void network_receive_reservation_request(UNUSED struct Packet* p);
void network_send_reservation(void);
void network_receive_reservation(struct Packet* p);

// packet_save_file.c
void network_send_save_file_request(void);
void network_receive_save_file_request(UNUSED struct Packet* p);
void network_send_save_file(void);
void network_receive_save_file(struct Packet* p);

// packet_custom.c
u8 network_register_custom_packet(void (*send_callback)(struct Packet* p, void* params), void (*receive_callback)(struct Packet* p));
void network_send_custom(u8 customId, bool reliable, void* params);
void network_receive_custom(struct Packet* p);

#endif
