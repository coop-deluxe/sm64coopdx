#include <stdio.h>
#include "../network.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"

void network_send_lua_sync_table(u64 seq, u16 remoteIndex, u16 lst, u16 index, const char* key, enum LSTNetworkType lUnionType, union LSTNetworkUnion lUnion) {
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
                //LOG_INFO("sent lua_sync_table: %llu, %u, %u, %s, %u, %f", seq, remoteIndex, lst, key, lUnionType, number);
                break;
            }
        case LST_NETWORK_TYPE_INTEGER: {
                s64 integer = lUnion.integer;
                packet_write(&p, &integer, sizeof(s64));
                //LOG_INFO("sent lua_sync_table: %llu, %u, %u, %s, %u, %llu", seq, remoteIndex, lst, key, lUnionType, integer);
                break;
            }
        default:
            LOG_ERROR("attempted to send lua sync table with invalid type: %d", lUnionType);
            return;
    }

    network_send(&p);
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
        default:
            LOG_ERROR("received lua sync table with invalid type: %d", lUnionType);
            return;
    }

    smlua_set_sync_table_field_from_network(seq, remoteIndex, lst, index, key, lUnionType, lUnion);
}
