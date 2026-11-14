#ifndef PACKET_DEFINITIONS_H
#define PACKET_DEFINITIONS_H

#include "types.h"

#include <PR/ultratypes.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>

#include "pc/network/packets/datagram.h"

#define PACKET_LENGTH 3000
#define PACKET_DESTINATION_BROADCAST ((u8)-1)
#define PACKET_DESTINATION_SERVER ((u8)-2)

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
    PACKET_LUA_CUSTOM_BYTESTRING,

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
    struct Datagram dg;
    void* addr;
    enum PacketType packetType;
    bool sent;
    bool reliable;
    bool levelAreaMustMatch;
    bool levelMustMatch;
    bool requestBroadcast;
    bool keepSendingAfterDisconnect;
    u8 localIndex;
    u8 destGlobalId;
    u16 seqId;
    u16 orderedGroupId;
    u16 orderedSeqId;
    u8 orderedFromGlobalId;
    u8 courseNum;
    u8 actNum;
    u8 areaIndex;
    s16 levelNum;
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

#endif // PACKET_DEFINITIONS_H