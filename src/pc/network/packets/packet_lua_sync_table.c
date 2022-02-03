#include <stdio.h>
#include "../network.h"
#include "pc/lua/smlua.h"
#include "pc/debuglog.h"

/////////////////////////////////////////////////////////////

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

/////////////////////////////////////////////////////////////

static bool packet_write_lnt(struct Packet* p, struct LSTNetworkType* lnt) {
    u8 lntType = lnt->type;
    packet_write(p, &lntType, sizeof(u8));

    switch (lnt->type) {
        case LST_NETWORK_TYPE_NUMBER: {
            f64 number = lnt->value.number;
            packet_write(p, &number, sizeof(f64));
            return true;
        }

        case LST_NETWORK_TYPE_INTEGER: {
            s64 integer = lnt->value.integer;
            packet_write(p, &integer, sizeof(s64));
            return true;
        }

        case LST_NETWORK_TYPE_BOOLEAN: {
            packet_write(p, &lnt->value.boolean, sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_STRING: {
            u16 valueLength = strlen(lnt->value.string);
            if (valueLength < 1 || valueLength > 256) {
                LOG_ERROR("attempted to send lua sync table with invalid string length: %u", valueLength);
                return false;
            }
            packet_write(p, &valueLength, sizeof(u16));
            packet_write(p, lnt->value.string, valueLength * sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_NIL: {
            // no-op
            return true;
        }

        default:
            break;
    }

    LOG_ERROR("attempted to send lua sync table with invalid lnt type: %d", lnt->type);
    return false;
}

static bool packet_read_lnt(struct Packet* p, struct LSTNetworkType* lnt) {
    packet_read(p, &lnt->type, sizeof(u8));

    switch (lnt->type) {
        case LST_NETWORK_TYPE_NUMBER:
            packet_read(p, &lnt->value.number, sizeof(f64));
            return true;

        case LST_NETWORK_TYPE_INTEGER:
            packet_read(p, &lnt->value.integer, sizeof(s64));
            return true;

        case LST_NETWORK_TYPE_BOOLEAN:
            packet_read(p, &lnt->value.boolean, sizeof(u8));
            return true;

        case LST_NETWORK_TYPE_STRING: {
            u16 valueLength = 0;
            packet_read(p, &valueLength, sizeof(u16));
            if (valueLength < 1 || valueLength > 256) {
                LOG_ERROR("received lua sync table with invalid value length: %d", valueLength);
                return false;
            }
            lnt->value.string = calloc(valueLength + 1, sizeof(u8));
            packet_read(p, lnt->value.string, valueLength * sizeof(u8));
            return true;
        }

        case LST_NETWORK_TYPE_NIL:
            // no-op
            return true;

        default:
            break;
    }

    LOG_ERROR("received lua sync table with invalid type: %d", lnt->type);
    return false;
}

/////////////////////////////////////////////////////////////

void network_send_lua_sync_table(u8 toLocalIndex, u64 seq, u16 modRemoteIndex, u16 lntKeyCount, struct LSTNetworkType* lntKeys, struct LSTNetworkType* lntValue) {
    if (gLuaState == NULL) { return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_SYNC_TABLE, true, PLMT_NONE);
    packet_write(&p, &seq, sizeof(u64));
    packet_write(&p, &modRemoteIndex, sizeof(u16));

    packet_write(&p, &lntKeyCount, sizeof(u16));
    for (int i = 0; i < lntKeyCount; i++) {
        if (!packet_write_lnt(&p, &lntKeys[i])) { return; }
    }

    if (!packet_write_lnt(&p, lntValue)) { return; }

    if (toLocalIndex == 0 || toLocalIndex >= MAX_PLAYERS) {
        network_send(&p);
    } else {
        network_send_to(toLocalIndex, &p);
    }
}

void network_receive_lua_sync_table(struct Packet* p) {
    if (gLuaState == NULL) { return; }

    u64 seq = 0;
    u16 modRemoteIndex = 0;
    u16 lntKeyCount = 0;
    struct LSTNetworkType lntKeys[MAX_UNWOUND_LNT] = { 0 };
    struct LSTNetworkType lntValue = { 0 };

    packet_read(p, &seq, sizeof(u64));
    packet_read(p, &modRemoteIndex, sizeof(u16));

    packet_read(p, &lntKeyCount, sizeof(u16));
    for (int i = 0; i < lntKeyCount; i++) {
        if (!packet_read_lnt(p, &lntKeys[i])) { goto cleanup; }
    }

    if (!packet_read_lnt(p, &lntValue)) { goto cleanup; }

    smlua_set_sync_table_field_from_network(seq, modRemoteIndex, lntKeyCount, lntKeys, &lntValue);

cleanup:
    for (int i = 0; i < lntKeyCount; i++) {
        if (lntKeys[i].type != LST_NETWORK_TYPE_STRING) { continue; }
        if (lntKeys[i].value.string == NULL) { continue; }
        free(lntKeys[i].value.string);
        lntKeys[i].value.string = NULL;
    }
    if (lntValue.type == LST_NETWORK_TYPE_STRING && lntValue.value.string != NULL) {
        free(lntValue.value.string);
        lntValue.value.string = NULL;
    }
}
