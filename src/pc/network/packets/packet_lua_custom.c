#include <stdio.h>
#include "../network.h"
#include "pc/mods/mod.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_utils.h"
#include "pc/log.h"

void network_send_lua_custom(bool broadcast) {
    log_context_begin(LOG_CTX_NETWORK);
    LOG_DEBUG_VERBOSE("Sending lua custom packet");
    lua_State* L = gLuaState;
    u16 zero = 0;
    s32 paramIndex = 1;

    if (!L) {
        LOG_ERROR_VERBOSE("Sent lua custom packet when lua is dead");
        log_context_end(LOG_CTX_NETWORK);
        return;
    }

    // figure out mod index
    if (gLuaActiveMod == NULL) {
        LOG_LUA_LINE("Could not figure out the current active mod!");
        log_context_end(LOG_CTX_NETWORK);
        return;
    }
    u16 modIndex = gLuaActiveMod->index;

    // get local index
    s32 toLocalIndex = 0;
    if (!broadcast) {
        toLocalIndex = smlua_to_integer(L, paramIndex++);
        if (toLocalIndex <= 0 || toLocalIndex >= MAX_PLAYERS) {
            LOG_LUA_LINE("Tried to send packet to invalid local index: %d", toLocalIndex)
            log_context_end(LOG_CTX_NETWORK);
            return;
        }
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("Invalid 'localIndex' type");
            log_context_end(LOG_CTX_NETWORK);
            return;
        }
    }

    // get reliability
    bool reliability = smlua_to_boolean(L, paramIndex++);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Invalid 'reliable' type");
        log_context_end(LOG_CTX_NETWORK);
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
        log_context_end(LOG_CTX_NETWORK);
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
            log_context_end(LOG_CTX_NETWORK);
            return;
        }
        if (!packet_write_lnt(&p, &lntKey)) {
            return;
            log_context_end(LOG_CTX_NETWORK);
        }

        // convert and write value
        struct LSTNetworkType lntValue = smlua_to_lnt(L, -1);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Failed to convert value to LNT (tx)");
            log_context_end(LOG_CTX_NETWORK);
            return;
        }
        if (!packet_write_lnt(&p, &lntValue)) {
            log_context_end(LOG_CTX_NETWORK);
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
    log_context_end(LOG_CTX_NETWORK);
}

void network_receive_lua_custom(struct Packet* p) {
    LOG_DEBUG_VERBOSE("Receiving lua custom packet");
    lua_State* L = gLuaState;
    u16 modIndex = 0;
    u8  keyCount = 0;
    packet_read(p, &modIndex, sizeof(u16));
    packet_read(p, &keyCount, sizeof(u8));

    if (!L) {
        LOG_ERROR_VERBOSE("Received lua custom packet when lua is dead");
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
