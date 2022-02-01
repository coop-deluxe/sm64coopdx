#include <stdio.h>
#include "../network.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"

static char sLuaStrValue[257] = { 0 };

void network_send_lua_sync_table_request(void) {
    SOFT_ASSERT(gNetworkType == NT_CLIENT);
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_SYNC_TABLE_REQUEST, true, PLMT_NONE);
    network_send_to((gNetworkPlayerServer != NULL) ? gNetworkPlayerServer->localIndex : 0, &p);
    LOG_INFO("sending lua sync table request");
}

void network_receive_lua_sync_table_request(struct Packet* p) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    SOFT_ASSERT(p->localIndex < MAX_PLAYERS);
    smlua_sync_table_send_all(p->localIndex);
    LOG_INFO("received lua sync table request");
}

void network_send_lua_sync_table(u8 toLocalIndex, u64 seq, u16 remoteIndex, u16 lst, u16 index, const char* key, enum LSTNetworkType lUnionType, union LSTNetworkUnion lUnion) {
    u16 keyLength = strlen(key);

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_SYNC_TABLE, true, PLMT_NONE);
    packet_write(&p, &seq, sizeof(u64));
    packet_write(&p, &remoteIndex, sizeof(u16));
    packet_write(&p, &lst, sizeof(u16));
    packet_write(&p, &index, sizeof(u16));

    packet_write(&p, &keyLength, sizeof(u16));
    packet_write(&p, (char*)key, keyLength * sizeof(u8));

    packet_write(&p, &lUnionType, sizeof(u16));
    switch (lUnionType) {
        case LST_NETWORK_TYPE_NUMBER: {
                f64 number = lUnion.number;
                packet_write(&p, &number, sizeof(f64));
                //LOG_INFO("tx lua_sync_table: %llu, %u, %u, %s, %u, %f", seq, remoteIndex, lst, key, lUnionType, number);
                break;
            }
        case LST_NETWORK_TYPE_INTEGER: {
                s64 integer = lUnion.integer;
                packet_write(&p, &integer, sizeof(s64));
                //LOG_INFO("tx lua_sync_table: %llu, %u, %u, %s, %u, %llu", seq, remoteIndex, lst, key, lUnionType, integer);
                break;
            }
        case LST_NETWORK_TYPE_BOOLEAN: {
                packet_write(&p, &lUnion.boolean, sizeof(u8));
                //LOG_INFO("tx lua_sync_table: %llu, %u, %u, %s, %u, %u", seq, remoteIndex, lst, key, lUnionType, lUnion.boolean);
                break;
            }
        case LST_NETWORK_TYPE_STRING: {
                snprintf(sLuaStrValue, 256, "%s", lUnion.string);
                u16 valueLength = strlen(sLuaStrValue);
                packet_write(&p, &valueLength, sizeof(u16));
                packet_write(&p, &sLuaStrValue, valueLength * sizeof(u8));
                //LOG_INFO("tx lua_sync_table: %llu, %u, %u, %s, %u, %s", seq, remoteIndex, lst, key, lUnionType, sLuaStrValue);
                break;
            }
        case LST_NETWORK_TYPE_NIL: {
                // no-op
                //LOG_INFO("tx lua_sync_table: %llu, %u, %u, %s, %u, <NIL>", seq, remoteIndex, lst, key, lUnionType);
                break;
            }
        default:
            LOG_ERROR("attempted to send lua sync table with invalid type: %d", lUnionType);
            return;
    }

    if (toLocalIndex == 0 || toLocalIndex >= MAX_PLAYERS) {
        network_send(&p);
    } else {
        network_send_to(toLocalIndex, &p);
    }
}

void network_receive_lua_sync_table(struct Packet* p) {
    u64 seq = 0;
    u16 remoteIndex = 0;
    u16 lst = 0;
    u16 index = 0;
    u16 keyLength = 0;
    char key[65] = { 0 };
    u16 lUnionType = 0;
    union LSTNetworkUnion lUnion;

    packet_read(p, &seq, sizeof(u64));
    packet_read(p, &remoteIndex, sizeof(u16));
    packet_read(p, &lst, sizeof(u16));
    packet_read(p, &index, sizeof(u16));

    packet_read(p, &keyLength, sizeof(u16));
    if (keyLength > 64) {
        LOG_ERROR("received lua sync table with invalid key length: %d", keyLength);
        return;
    }
    packet_read(p, &key, keyLength * sizeof(u8));

    packet_read(p, &lUnionType, sizeof(u16));
    switch (lUnionType) {
        case LST_NETWORK_TYPE_NUMBER:
            packet_read(p, &lUnion.number, sizeof(f64));
            //LOG_INFO("rx lua_sync_table: %llu, %u, %u, %s, %u, %f", seq, remoteIndex, lst, key, lUnionType, lUnion.number);
            break;
        case LST_NETWORK_TYPE_INTEGER:
            packet_read(p, &lUnion.integer, sizeof(s64));
            //LOG_INFO("rx lua_sync_table: %llu, %u, %u, %s, %u, %llu", seq, remoteIndex, lst, key, lUnionType, lUnion.integer);
            break;
        case LST_NETWORK_TYPE_BOOLEAN:
            packet_read(p, &lUnion.boolean, sizeof(u8));
            //LOG_INFO("rx lua_sync_table: %llu, %u, %u, %s, %u, %u", seq, remoteIndex, lst, key, lUnionType, lUnion.boolean);
            break;
        case LST_NETWORK_TYPE_STRING: {
                u16 valueLength = 0;
                packet_read(p, &valueLength, sizeof(u16));
                if (keyLength > 256) {
                    LOG_ERROR("received lua sync table with invalid value length: %d", keyLength);
                    return;
                }

                packet_read(p, &sLuaStrValue, valueLength * sizeof(u8));
                sLuaStrValue[valueLength] = 0;
                lUnion.string = sLuaStrValue;
                //LOG_INFO("rx lua_sync_table: %llu, %u, %u, %s, %u, %s", seq, remoteIndex, lst, key, lUnionType, lUnion.string);
                break;
            }
        case LST_NETWORK_TYPE_NIL:
            // no-op
            //LOG_INFO("rx lua_sync_table: %llu, %u, %u, %s, %u, <NIL>", seq, remoteIndex, lst, key, lUnionType);
            break;
        default:
            LOG_ERROR("received lua sync table with invalid type: %d", lUnionType);
            return;
    }

    smlua_set_sync_table_field_from_network(seq, remoteIndex, lst, index, key, lUnionType, lUnion);
}
