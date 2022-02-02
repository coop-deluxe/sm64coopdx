#ifndef PACKET_H
#define PACKET_H

#include "PR/ultratypes.h"
#include <time.h>
#include <types.h>
#include <assert.h>
#include <stdbool.h>

#define PACKET_LENGTH 1024
#define PACKET_DESTINATION_BROADCAST ((u8)-1)

struct NetworkPlayer;

enum PacketType {
    PACKET_ACK,
    PACKET_PLAYER,
    PACKET_OBJECT,
    PACKET_SPAWN_OBJECTS,
    PACKET_SPAWN_STAR,
    PACKET_SPAWN_STAR_NLE,
    PACKET_COLLECT_STAR,
    PACKET_COLLECT_COIN,
    PACKET_COLLECT_ITEM,
    PACKET_UNUSED1,
    PACKET_DEBUG_SYNC,
    PACKET_JOIN_REQUEST,
    PACKET_JOIN,
    PACKET_CHAT,
    PACKET_KICK,
    PACKET_KEEP_ALIVE,
    PACKET_LEAVING,
    PACKET_SAVE_FILE,
    PACKET_SAVE_SET_FLAG,
    PACKET_NETWORK_PLAYERS,
    PACKET_DEATH,

    PACKET_RESERVATION_LIST,
    PACKET_RESERVATION_USE,
    PACKET_RESERVATION_RELEASE,

    PACKET_CHANGE_LEVEL,
    PACKET_CHANGE_AREA,
    PACKET_LEVEL_AREA_REQUEST,
    PACKET_LEVEL_REQUEST,
    PACKET_LEVEL,
    PACKET_AREA_REQUEST,
    PACKET_AREA,
    PACKET_SYNC_VALID,
    PACKET_LEVEL_SPAWN_INFO,
    PACKET_LEVEL_MACRO,
    PACKET_LEVEL_AREA_INFORM,
    PACKET_LEVEL_RESPAWN_INFO,

    PACKET_PLAYER_SETTINGS,

    PACKET_MOD_LIST_REQUEST,
    PACKET_MOD_LIST,
    PACKET_DOWNLOAD_REQUEST,
    PACKET_DOWNLOAD,

    PACKET_LUA_SYNC_TABLE_REQUEST,
    PACKET_LUA_SYNC_TABLE,

    PACKET_NETWORK_PLAYERS_REQUEST,

    ///
    PACKET_CUSTOM = 255,
};

enum PacketLevelMatchType {
    PLMT_NONE,
    PLMT_AREA,
    PLMT_LEVEL
};

struct Packet {
    enum PacketType packetType;
    u8 localIndex;
    u16 dataLength;
    u16 cursor;
    void* addr;
    bool error;
    bool writeError;
    bool reliable;
    bool levelAreaMustMatch;
    bool levelMustMatch;
    bool requestBroadcast;
    u8 destGlobalId;
    u16 seqId;
    bool sent;
    u8 orderedFromGlobalId;
    u8 orderedGroupId;
    u8 orderedSeqId;
    u8 courseNum;
    u8 actNum;
    u8 levelNum;
    u8 areaIndex;
    u8 buffer[PACKET_LENGTH];
};

enum KickReasonType {
    EKT_CLOSE_CONNECTION,
    EKT_FULL_PARTY,
};

struct LSTNetworkType {
    enum {
        LST_NETWORK_TYPE_INTEGER,
        LST_NETWORK_TYPE_NUMBER,
        LST_NETWORK_TYPE_BOOLEAN,
        LST_NETWORK_TYPE_STRING,
        LST_NETWORK_TYPE_NIL,
        LST_NETWORK_TYPE_MAX
    } type;

    union {
        long long integer;
        double number;
        u8 boolean;
        char* string;
    } value;

    size_t size;
};

// packet.c
void packet_process(struct Packet* p);
void packet_receive(struct Packet* packet);

// packet_read_write.c
void packet_init(struct Packet* packet, enum PacketType packetType, bool reliable, enum PacketLevelMatchType levelAreaMustMatch);
void packet_duplicate(struct Packet* srcPacket, struct Packet* dstPacket);
void packet_set_flags(struct Packet* packet);
void packet_set_destination(struct Packet* packet, u8 destGlobalId);
void packet_write(struct Packet* packet, void* data, u16 length);
u8 packet_initial_read(struct Packet* packet);
void packet_read(struct Packet* packet, void* data, u16 length);
u32 packet_hash(struct Packet* packet);
bool packet_check_hash(struct Packet* packet);
void packet_ordered_begin(void);
void packet_ordered_end(void);
void packet_set_ordered_data(struct Packet* packet);

// packet_reliable.c
void network_forget_all_reliable(void);
void network_forget_all_reliable_from(u8 localIndex);
void network_send_ack(struct Packet* p);
void network_receive_ack(struct Packet* p);
void network_remember_reliable(struct Packet* p);
void network_update_reliable(void);

// packet_ordered.c
void packet_ordered_add(struct Packet* p);
void packet_ordered_clear_table(u8 globalIndex, u8 groupdId);
void packet_ordered_clear(u8 globalIndex);
void packet_ordered_update(void);

// packet_player.c
void network_update_player(void);
void network_receive_player(struct Packet* p);

// packet_object.c
struct Packet* get_last_sync_ent_reliable_packet(u8 syncId);
void forget_ent_reliable_packet(struct Object* o);
void network_override_object(u8 syncId, struct Object* o);
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
void network_send_spawn_objects_to(u8 sendToLocalIndex, struct Object* objects[], u32 models[], u8 objectCount);
void network_receive_spawn_objects(struct Packet* p);

// packet_spawn_star.c
void network_send_spawn_star(struct Object* o, u8 starType, f32 x, f32 y, f32 z, u32 behParams);
void network_receive_spawn_star(struct Packet* p);
void network_send_spawn_star_nle(struct Object* o, u32 params);
void network_receive_spawn_star_nle(struct Packet* p);

// packet_collect_star.c
void network_send_collect_star(struct Object* o, s16 coinScore, s16 starIndex);
void network_receive_collect_star(struct Packet* p);

// packet_collect_coin.c
void network_send_collect_coin(struct Object* o);
void network_receive_collect_coin(struct Packet* p);

// packet_collect_item.c
void network_send_collect_item(struct Object* o);
void network_receive_collect_item(struct Packet* p);

// packet_join.c
void network_send_join_request(void);
void network_receive_join_request(struct Packet* p);
void network_send_join(struct Packet* joinRequestPacket);
void network_receive_join(struct Packet* p);

// packet_custom.c
u8 network_register_custom_packet(void (*send_callback)(struct Packet* p, void* params), void (*receive_callback)(struct Packet* p));
void network_send_custom(u8 customId, bool reliable, enum PacketLevelMatchType levelAreaMustMatch, void* params);
void network_receive_custom(struct Packet* p);

// packet_chat.c
void network_send_chat(char* message, u8 globalIndex);
void network_receive_chat(struct Packet* p);

// packet_kick.c
void network_send_kick(enum KickReasonType kickReason);
void network_receive_kick(struct Packet* p);

// packet_keep_alive.c
void network_send_keep_alive(u8 localIndex);
void network_receive_keep_alive(struct Packet* p);

// packet_leaving.c
void network_send_leaving(u8 globalIndex);
void network_receive_leaving(struct Packet* p);

// packet_save_file.c
void network_send_save_file(s32 fileIndex);
void network_receive_save_file(struct Packet* p);

// packet_save_set_flag.c
void network_send_save_set_flag(s32 fileIndex, s32 courseIndex, u8 courseStars, u32 flags);
void network_receive_save_set_flag(struct Packet* p);

// packet_network_players.c
void network_send_network_players_request(void);
void network_receive_network_players_request(struct Packet* p);
void network_send_network_players(u8 exceptLocalIndex);
void network_receive_network_players(struct Packet* p);

// packet_death.c
void network_send_death(void);
void network_receive_death(struct Packet* p);

// packet_change_level.c
void network_send_change_level(void);
void network_receive_change_level(struct Packet* p);

// packet_change_area.c
void network_send_change_area(void);
void network_receive_change_area(struct Packet* p);

// packet_level_area_request.c
void network_send_level_area_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp);
void network_receive_level_area_request(struct Packet* p);

// packet_level_request.c
void network_send_level_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp);
void network_receive_level_request(struct Packet* p);

// packet_level.c
void network_send_level(struct NetworkPlayer* toNp, bool sendArea);
void network_receive_level(struct Packet* p);

// packet_area_request.c
void network_send_area_request(struct NetworkPlayer* fromNp, struct NetworkPlayer* toNp);
void network_receive_area_request(struct Packet* p);

// packet_area.c

void area_remove_sync_ids_add(u8 syncId);
void area_remove_sync_ids_clear(void);
void network_send_area(struct NetworkPlayer* toNp);
void network_receive_area(struct Packet* p);

// packet_sync_valid.c
void network_send_sync_valid(struct NetworkPlayer* toNp, s16 courseNum, s16 actNum, s16 levelNum, s16 areaIndex);
void network_receive_sync_valid(struct Packet* p);

// packet_level_spawn_info.c
void network_send_level_spawn_info(struct NetworkPlayer* destNp);
void network_receive_level_spawn_info(struct Packet* p);

// packet_level_macro.c
void network_send_level_macro(struct NetworkPlayer* destNp);
void network_receive_level_macro(struct Packet* p);

// packet_level_area_inform.c
void network_send_level_area_inform(struct NetworkPlayer* np);
void network_receive_level_area_inform(struct Packet* p);

// packet_level_respawn_info.c
void network_send_level_respawn_info(struct Object* o, u8 respawnInfoBits);
void network_receive_level_respawn_info(struct Packet* p);

// packet_reservation_list.c
void network_send_reservation_list(struct NetworkPlayer* np, u8 syncIds[]);
void network_receive_reservation_list(struct Packet* p);

// packet_reservation_use.c
void network_send_reservation_use(u8 syncId);
void network_receive_reservation_use(struct Packet* p);

// packet_reservation_release.c
void network_send_reservation_release(u8 syncId);
void network_receive_reservation_release(struct Packet* p);

// packet_debug_sync.c
void network_send_debug_sync(void);
void network_receive_debug_sync(struct Packet* p);

// packet_player_settings.c
void network_send_player_settings(void);
void network_receive_player_settings(struct Packet* p);

// packet_mod_list.c
void network_send_mod_list_request(void);
void network_receive_mod_list_request(UNUSED struct Packet* p);
void network_send_mod_list(void);
void network_receive_mod_list(struct Packet* p);

// packet_download.c
void network_send_next_download_request(void);
void network_send_download_request(u16 clientIndex, u16 serverIndex, u64 offset);
void network_receive_download_request(struct Packet* p);
void network_send_download(u16 clientIndex, u16 serverIndex, u64 offset);
void network_receive_download(struct Packet* p);

// packet_lua_sync_table.c
void network_send_lua_sync_table_request(void);
void network_receive_lua_sync_table_request(struct Packet* p);

void network_send_lua_sync_table(u8 toLocalIndex, u64 seq, u16 remoteIndex, u16 lntKeyCount, struct LSTNetworkType* lntKey, struct LSTNetworkType* lntValue);
void network_receive_lua_sync_table(struct Packet* p);

#endif
