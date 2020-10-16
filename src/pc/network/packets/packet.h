#ifndef PACKET_H
#define PACKET_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include <stdbool.h>

#define PACKET_LENGTH 1024

enum PacketType {
    PACKET_ACK,
    PACKET_PLAYER,
    PACKET_OBJECT,
    PACKET_SPAWN_OBJECTS,
    PACKET_SPAWN_STAR,
    PACKET_SPAWN_STAR_NLE,
    PACKET_LEVEL_WARP,
    PACKET_INSIDE_PAINTING,
    PACKET_COLLECT_STAR,
    PACKET_COLLECT_COIN,
    PACKET_COLLECT_ITEM,
    PACKET_RESERVATION_REQUEST,
    PACKET_RESERVATION,
    PACKET_JOIN_REQUEST,
    PACKET_JOIN,
    PACKET_CHAT,
    PACKET_KICK,
    PACKET_KEEP_ALIVE,
    PACKET_LEAVING,
    PACKET_SAVE_FILE,
    PACKET_INSTANT_WARP,
    PACKET_NETWORK_PLAYERS,
    PACKET_DEATH,
    ///
    PACKET_CUSTOM = 255,
};

struct Packet {
    u8 localIndex;
    u16 dataLength;
    u16 cursor;
    bool error;
    bool reliable;
    bool levelAreaMustMatch;
    bool requestBroadcast;
    u16 seqId;
    bool sent;
    u8 buffer[PACKET_LENGTH];
};

enum KickReasonType {
    EKT_CLOSE_CONNECTION,
    EKT_FULL_PARTY,
};

// packet.c
void packet_receive(struct Packet* packet);

// packet_read_write.c
void packet_init(struct Packet* packet, enum PacketType packetType, bool reliable, bool levelAreaMustMatch);
void packet_set_flags(struct Packet* packet);
void packet_write(struct Packet* packet, void* data, u16 length);
u8 packet_initial_read(struct Packet* packet);
void packet_read(struct Packet* packet, void* data, u16 length);
u32 packet_hash(struct Packet* packet);
bool packet_check_hash(struct Packet* packet);

// packet_reliable.c
void network_forget_all_reliable(void);
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
void network_send_spawn_star_nle(struct Object* o, u32 params);
void network_receive_spawn_star_nle(struct Packet* p);

// packet_level_warp.c
void network_send_level_warp_begin(void);
void network_send_level_warp_repeat(void);
void network_receive_level_warp(struct Packet* p);

// packet_inside_painting.c
void network_send_inside_painting(void);
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
void network_receive_reservation_request(struct Packet* p);
void network_send_reservation(u8 toLocalIndex);
void network_receive_reservation(struct Packet* p);

// packet_join.c
void network_send_join_request(void);
void network_receive_join_request(struct Packet* p);
void network_send_join(struct Packet* joinRequestPacket);
void network_receive_join(struct Packet* p);

// packet_custom.c
u8 network_register_custom_packet(void (*send_callback)(struct Packet* p, void* params), void (*receive_callback)(struct Packet* p));
void network_send_custom(u8 customId, bool reliable, bool levelAreaMustMatch, void* params);
void network_receive_custom(struct Packet* p);

// packet_chat.c
void network_send_chat(char* message);
void network_receive_chat(struct Packet* p);

// packet_kick.c
void network_send_kick(enum KickReasonType kickReason);
void network_receive_kick(struct Packet* p);

// packet_keep_alive.c
void network_send_keep_alive(void);
void network_receive_keep_alive(struct Packet* p);

// packet_leaving.c
void network_send_leaving(u8 globalIndex);
void network_receive_leaving(struct Packet* p);

// packet_save_file.c
void network_send_save_file(s32 fileIndex);
void network_receive_save_file(struct Packet* p);

// packet_instant_warp.c
void network_send_instant_warp(void);
void network_receive_instant_warp(struct Packet* p);

// packet_network_players.c
void network_send_network_players(void);
void network_receive_network_players(struct Packet* p);

#endif
