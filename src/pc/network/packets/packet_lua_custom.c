#include <stdio.h>
#include "../network.h"
#include "pc/mods/mod.h"
#include "pc/lua/smlua.h"
#include "pc/lua/smlua_utils.h"
#include "pc/debuglog.h"

void network_send_lua_custom(bool broadcast) {
    lua_State* L = gLuaState;
    s32 paramIndex = 1;

    if (!L) {
        LOG_ERROR("Sent lua custom packet when lua is dead");
        return;
    }

    // Figure out mod index
    if (gLuaActiveMod == NULL) {
        LOG_LUA_LINE("Could not figure out the current active mod!");
        return;
    }
    u16 modIndex = gLuaActiveMod->index;

    // Get local index
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

    // Get reliability
    bool reliability = smlua_to_boolean(L, paramIndex++);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Invalid 'reliable' type");
        return;
    }

    // Write packet header
    struct Packet p = { 0 };
    packet_init(&p, PACKET_LUA_CUSTOM, reliability, PLMT_NONE);
    datagram_add_uint16(&p.dg, modIndex);
    
    // Write our current key count.
    u32 cursorPosition = datagram_length(&p.dg);
    u8 keyCount = 0;
    datagram_add_uint8(&p.dg, keyCount);

    // Make sure value passed in is a table
    s32 tableIndex = paramIndex;
    if (lua_type(L, tableIndex) != LUA_TTABLE) {
        LOG_LUA_LINE("Tried to send a packet with a non-table");
        packet_clear(&p);
        return;
    }

    // Iterate table
    s32 iterateIndex = lua_gettop(L);
    lua_pushnil(L);  // first key
    while (lua_next(L, iterateIndex) != 0) {
        // Convert and write key
        struct LSTNetworkType lntKey = smlua_to_lnt(L, -2);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Failed to convert key to LNT (tx)");
            packet_clear(&p);
            return;
        }
        if (!packet_write_lnt(&p, &lntKey)) {
            packet_clear(&p);
            return;
        }

        // Convert and write value
        struct LSTNetworkType lntValue = smlua_to_lnt(L, -1);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Failed to convert value to LNT (tx)");
            packet_clear(&p);
            return;
        }
        if (!packet_write_lnt(&p, &lntValue)) {
            packet_clear(&p);
            return;
        }

        // Increment key count
        keyCount += 1;
        lua_pop(L, 1); // Pop value
    }
    lua_pop(L, 1); // Pop key
    
    // Update the current key count.
    u32 restoreCursorPosition = datagram_cursor_position(&p.dg);
    datagram_seek(&p.dg, cursorPosition);
    datagram_write_uint8(&p.dg, keyCount);
    datagram_seek(&p.dg, restoreCursorPosition);

    // Send packet
    if (broadcast) {
        network_send(&p);
    } else {
        network_send_to(toLocalIndex, &p);
    }
    packet_clear(&p);
}

void network_receive_lua_custom(struct Packet* p) {
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

    smlua_call_event_hooks(HOOK_ON_PACKET_RECEIVE, modIndex, tableIndex);
    lua_pop(L, 1); // pop table
}

  ////////////////
 // bytestring //
////////////////

#define MAX_BYTESTRING_LENGTH (PACKET_LENGTH - 15)

void network_send_lua_custom_bytestring(bool broadcast) {
    lua_State* L = gLuaState;
    s32 paramIndex = 1;

    if (!L) {
        LOG_ERROR("Sent lua custom bytestring packet when lua is dead");
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
            LOG_LUA_LINE("Tried to send bytestring packet to invalid local index: %d", toLocalIndex)
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
    packet_init(&p, PACKET_LUA_CUSTOM_BYTESTRING, reliability, PLMT_NONE);
    packet_write(&p, &modIndex, sizeof(u16));

    // make sure value passed in is a string
    s32 bytestringIndex = paramIndex;
    if (lua_type(L, bytestringIndex) != LUA_TSTRING) {
        LOG_LUA_LINE("Tried to send a bytestring packet with a non-string");
        return;
    }

    // get string information
    size_t totalLength = 0;
    const char* bytestring = lua_tolstring(L, bytestringIndex, &totalLength);

    // check length
    if (totalLength <= 0 || totalLength > MAX_BYTESTRING_LENGTH) {
        LOG_LUA_LINE("Tried to send a bytestring packet with an invalid length '%llu'. Must be above 0 and below '%u'", (u64)totalLength, MAX_BYTESTRING_LENGTH);
        return;
    }

    // write length
    u16 bytestringLength = totalLength;
    packet_write(&p, &bytestringLength, sizeof(u16));

    // write bytestring
    packet_write(&p, (char*)bytestring, totalLength);

    // send packet
    if (broadcast) {
        network_send(&p);
    } else {
        network_send_to(toLocalIndex, &p);
    }
}

void network_receive_lua_custom_bytestring(struct Packet* p) {
    lua_State* L = gLuaState;
    u16 modIndex = 0;
    u16 bytestringLength = 0;
    packet_read(p, &modIndex, sizeof(u16));
    packet_read(p, &bytestringLength, sizeof(u16));

    if (!L) {
        LOG_ERROR("Received lua custom bytestring packet when lua is dead");
        return;
    }

    if (bytestringLength == 0 || bytestringLength > MAX_BYTESTRING_LENGTH) {
        LOG_ERROR("Received lua custom bytestring packet with an invalid length");
        return;
    }

    // read byte string
    static char sBytestring[MAX_BYTESTRING_LENGTH + 1] = "";
    packet_read(p, &sBytestring, bytestringLength);

    if (datagram_has_error(&p->dg)) {
        LOG_ERROR("Received malformed lua custom bytestring packet");
        return;
    }

    // push bytestring
    lua_pushlstring(L, sBytestring, bytestringLength);
    s32 bytestringIndex = lua_gettop(L);

    // call hook
    smlua_call_event_hooks(HOOK_ON_PACKET_BYTESTRING_RECEIVE, modIndex, bytestringIndex);
    lua_pop(L, 1); // pop bytestring
}
