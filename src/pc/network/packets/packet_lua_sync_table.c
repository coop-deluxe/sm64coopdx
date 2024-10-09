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

void network_send_lua_sync_table(u8 toLocalIndex, u64 seq, u16 modRemoteIndex, u16 lntKeyCount, struct LSTNetworkType* lntKeys, struct LSTNetworkType* lntValue) {
    if (gLuaState == NULL) { return; }
    if (lntKeyCount >= MAX_UNWOUND_LNT) { LOG_ERROR("Tried to send too many lnt keys"); return; }

    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_SYNC_TABLE, true, PLMT_NONE);
    packet_write(&p, &seq, sizeof(u64));
    packet_write(&p, &modRemoteIndex, sizeof(u16));
    packet_write(&p, &lntKeyCount, sizeof(u16));

    //LOG_INFO("TX SYNC (%llu):", seq);
    for (s32 i = 0; i < lntKeyCount; i++) {
        if (!packet_write_lnt(&p, &lntKeys[i])) { return; }
        //LOG_INFO("  %s", smlua_lnt_to_str(&lntKeys[i]));
    }
    //LOG_INFO("    -> %s", smlua_lnt_to_str(lntValue));
    //LOG_INFO("  count %u", lntKeyCount);

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
    if (lntKeyCount >= MAX_UNWOUND_LNT) { LOG_ERROR("Tried to receive too many lnt keys"); return; }

    //LOG_INFO("RX SYNC (%llu):", seq);
    for (s32 i = 0; i < lntKeyCount; i++) {
        if (!packet_read_lnt(p, &lntKeys[i])) { goto cleanup; }
        //LOG_INFO("  %s", smlua_lnt_to_str(&lntKeys[i]));
    }
    //LOG_INFO("    -> %s", smlua_lnt_to_str(&lntValue));
    //LOG_INFO("  count %u", lntKeyCount);

    if (!packet_read_lnt(p, &lntValue)) { goto cleanup; }

    if (p->error) { LOG_ERROR("Packet read error"); return; }
    smlua_set_sync_table_field_from_network(seq, modRemoteIndex, lntKeyCount, lntKeys, &lntValue);

cleanup:
    for (s32 i = 0; i < lntKeyCount; i++) {
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
