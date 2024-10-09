#ifndef PACKET_H
#define PACKET_H

#include <PR/ultratypes.h>
#include <time.h>
#include "types.h"
#include <assert.h>
#include <stdbool.h>

#define PACKET_LENGTH 3000
#define PACKET_DESTINATION_BROADCAST ((u8)-1)
#define PACKET_DESTINATION_SERVER ((u8)-2)

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
    PACKET_GLOBAL_POPUP,
    PACKET_DEBUG_SYNC,
    PACKET_JOIN_REQUEST,
    PACKET_JOIN,
    PACKET_CHAT,
    PACKET_KICK,
    PACKET_KEEP_ALIVE,
    PACKET_LEAVING,
    PACKET_SAVE_FILE,
    PACKET_SAVE_SET_FLAG,
    PACKET_SAVE_REMOVE_FLAG,
    PACKET_NETWORK_PLAYERS,
    PACKET_DEATH,

    PACKET_PING,
    PACKET_PONG,
    PACKET_UNUSED_23,

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
    PACKET_CHANGE_WATER_LEVEL,

    PACKET_PLAYER_SETTINGS,

    PACKET_MOD_LIST_REQUEST,
    PACKET_MOD_LIST,
    PACKET_DOWNLOAD_REQUEST,
    PACKET_DOWNLOAD,
    PACKET_MOD_LIST_ENTRY,
    PACKET_MOD_LIST_FILE,
    PACKET_MOD_LIST_DONE,

    PACKET_LUA_SYNC_TABLE_REQUEST,
    PACKET_LUA_SYNC_TABLE,

    PACKET_NETWORK_PLAYERS_REQUEST,

    PACKET_REQUEST_FAILED,

    PACKET_LUA_CUSTOM,
    
    PACKET_COMMAND,
    PACKET_MODERATOR,

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
    bool keepSendingAfterDisconnect;
    u8 destGlobalId;
    u16 seqId;
    bool sent;
    u8 orderedFromGlobalId;
    u16 orderedGroupId;
    u16 orderedSeqId;
    u8 courseNum;
    u8 actNum;
    s16 levelNum;
    u8 areaIndex;
    u8 buffer[PACKET_LENGTH];
};

enum KickReasonType {
    EKT_CLOSE_CONNECTION,
    EKT_FULL_PARTY,
    EKT_KICKED,
    EKT_BANNED,
    EKT_REJOIN,
};

enum ChatConfirmCommand {
    CCC_NONE,
    CCC_KICK,
    CCC_BAN,
    CCC_PERMBAN,
    CCC_MODERATOR,
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

extern u8 gAllowOrderedPacketClear;

// packet.c
void packet_compress(struct Packet* p, u8** compBuffer, u32* compSize);
bool packet_decompress(struct Packet* p, u8* compBuffer, u32 compSize);
void packet_process(struct Packet* p);
void packet_receive(struct Packet* packet);
bool packet_spoofed(struct Packet* p, u8 globalIndex);

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
void packet_ordered_clear_all(void);
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
void packet_ordered_clear_table(u8 globalIndex, u16 groupdId);
void packet_ordered_clear(u8 globalIndex);
void packet_ordered_update(void);

// packet_player.c
void network_update_player(void);
void network_receive_player(struct Packet* p);

// packet_object.c
void network_send_object(struct Object* o);
void network_send_object_reliability(struct Object* o, bool reliable);
void network_receive_object(struct Packet* p);
void network_update_objects(void);

// packet_spawn_object.c
void network_send_spawn_objects(struct Object* objects[], u32 models[], u8 objectCount);
void network_send_spawn_objects_to(u8 sendToLocalIndex, struct Object* objects[], u32 models[], u8 objectCount);
void network_receive_spawn_objects(struct Packet* p);

// packet_spawn_star.c
void network_send_spawn_star(struct Object* o, u8 starType, f32 x, f32 y, f32 z, u32 behParams, u8 networkPlayerIndex);
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
void network_send_kick(u8 localIndex, enum KickReasonType kickReason);
void network_receive_kick(struct Packet* p);

// packet_command_mod.c
void network_send_chat_command(u8 localIndex, enum ChatConfirmCommand CCC);
void network_receive_chat_command(struct Packet* p);

// packet_moderator.c
void network_send_moderator(u8 localIndex);
void network_receive_moderator(struct Packet* p);

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

// packet_save_remove_flag.c
void network_send_save_remove_flag(s32 fileIndex, s32 courseIndex, u8 courseStarsToRemove, u32 flagsToRemove);
void network_receive_save_remove_flag(struct Packet* p);

// packet_network_players.c
void network_send_network_players_request(void);
void network_receive_network_players_request(struct Packet* p);
void network_send_network_players(u8 exceptLocalIndex);
void network_receive_network_players(struct Packet* p);

// packet_death.c
void network_send_death(void);
void network_receive_death(struct Packet* p);

// packet_ping.c
void network_send_ping(struct NetworkPlayer* toNp);
void network_receive_ping(struct Packet* p);
void network_receive_pong(struct Packet* p);

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

void area_remove_sync_ids_add(u32 syncId);
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
void network_send_level_area_inform(void);
void network_receive_level_area_inform(struct Packet* p);

// packet_level_respawn_info.c
void network_send_level_respawn_info(struct Object* o, u8 respawnInfoBits);
void network_receive_level_respawn_info(struct Packet* p);

// packet_change_water_level.c
void network_send_change_water_level(u8 index, s16 height);
void network_receive_change_water_level(struct Packet* p);

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
void network_receive_mod_list_entry(struct Packet* p);
void network_receive_mod_list_file(struct Packet* p);
void network_receive_mod_list_done(struct Packet* p);

// packet_download.c
void network_start_download_requests(void);
void network_send_next_download_request(void);
void network_send_download_request(u64 offset);
void network_receive_download_request(struct Packet* p);
void network_send_download(u64 offset);
void network_receive_download(struct Packet* p);

// packet_global_popup.c
void network_send_global_popup(const char* message, int lines);
void network_receive_global_popup(struct Packet* p);

// packet_lua_sync_table.c
void network_send_lua_sync_table_request(void);
void network_receive_lua_sync_table_request(struct Packet* p);

void network_send_lua_sync_table(u8 toLocalIndex, u64 seq, u16 remoteIndex, u16 lntKeyCount, struct LSTNetworkType* lntKey, struct LSTNetworkType* lntValue);
void network_receive_lua_sync_table(struct Packet* p);

// packet_request_failed.c
void network_send_request_failed(struct NetworkPlayer* toNp, u8 requestType);
void network_receive_request_failed(struct Packet* p);

// packet_lua_custom.c
void network_send_lua_custom(bool broadcast);
void network_receive_lua_custom(struct Packet* p);

#endif
