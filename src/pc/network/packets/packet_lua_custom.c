#include <stdio.h>
#include "../network.h"
#include "pc/mods/mod.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_utils.h"
#include "pc/debuglog.h"

void network_send_lua_custom(bool broadcast) {
    LOG_INFO("Sending lua custom packet");
    lua_State* L = gLuaState;
    u16 zero = 0;
    s32 paramIndex = 1;

    if (!L) {
        LOG_ERROR("Sent lua custom packet when lua is dead");
        return;
    }

    // figure out mod index
    if (gLuaActiveMod == NULL) {
        LOG_LUA_LINE("Could not figure out the current active mod!");
        return;
    }
    u16 modIndex = gLuaActiveMod->index;

    // get local index
    s32 toLocalIndex = 0;
    if (!broadcast) {
        toLocalIndex = smlua_to_integer(L, paramIndex++);
        if (toLocalIndex <= 0 || toLocalIndex >= MAX_PLAYERS) {
            LOG_LUA_LINE("Tried to send packet to invalid local index: %d", toLocalIndex)
            return;
        }
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("Invalid 'localIndex' type");
            return;
        }
    }

    // get reliability
    bool reliability = smlua_to_boolean(L, paramIndex++);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Invalid 'reliable' type");
        return;
    }

    // write packet header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_CUSTOM, reliability, PLMT_NONE);
    packet_write(&p, &modIndex, sizeof(u16));
    u8* keyCount = &p.buffer[p.cursor];
    packet_write(&p, &zero, sizeof(u8));

    // make sure value passed in is a table
    s32 tableIndex = paramIndex;
    if (lua_type(L, tableIndex) != LUA_TTABLE) {
        LOG_LUA_LINE("Tried to send a packet with a non-table");
        return;
    }

    // iterate table
    s32 iterateIndex = lua_gettop(L);
    lua_pushnil(L);  // first key
    while (lua_next(L, iterateIndex) != 0) {
        // convert and write key
        struct LSTNetworkType lntKey = smlua_to_lnt(L, -2);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Failed to convert key to LNT (tx)");
            return;
        }
        if (!packet_write_lnt(&p, &lntKey)) {
            return;
        }

        // convert and write value
        struct LSTNetworkType lntValue = smlua_to_lnt(L, -1);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Failed to convert value to LNT (tx)");
            return;
        }
        if (!packet_write_lnt(&p, &lntValue)) {
            return;
        }

        // increment key count
        *keyCount = *keyCount + 1;
        lua_pop(L, 1); // pop value
    }
    lua_pop(L, 1); // pop key

    // send packet
    if (broadcast) {
        network_send(&p);
    } else {
        network_send_to(toLocalIndex, &p);
    }
}

void network_receive_lua_custom(struct Packet* p) {
    LOG_INFO("Receiving lua custom packet");
    lua_State* L = gLuaState;
    u16 modIndex = 0;
    u8  keyCount = 0;
    packet_read(p, &modIndex, sizeof(u16));
    packet_read(p, &keyCount, sizeof(u8));

    if (!L) {
        LOG_ERROR("Received lua custom packet when lua is dead");
        return;
    }

    lua_newtable(L);
    s32 tableIndex = lua_gettop(L);
    for(u16 i = 0; i < keyCount; i++) {
        struct LSTNetworkType lntKey = { 0 };
        if (!packet_read_lnt(p, &lntKey)) {
            LOG_LUA_LINE("Failed to convert key to LNT (rx)");
            return;
        }
        smlua_push_lnt(&lntKey);

        struct LSTNetworkType lntValue = { 0 };
        if (!packet_read_lnt(p, &lntValue)) {
            LOG_LUA_LINE("Failed to convert value to LNT (rx)");
            return;
        }
        smlua_push_lnt(&lntValue);

        lua_settable(L, -3);
    }

    smlua_call_event_hooks_value_param(HOOK_ON_PACKET_RECEIVE, modIndex, tableIndex);
    lua_pop(L, 1); // pop table
}
