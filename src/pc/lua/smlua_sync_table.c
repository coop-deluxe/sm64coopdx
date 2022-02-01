#include "smlua.h"
#include "pc/mod_list.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"

static bool smlua_value_to_lnt(int index, struct LSTNetworkType* lnt) {
    lua_State* L = gLuaState;
    int valueType = lua_type(L, index);

    if (valueType == LUA_TNUMBER) {
        lnt->type = LST_NETWORK_TYPE_INTEGER;
        lnt->value.integer = lua_tointeger(L, index);

        if (lnt->value.integer == 0) {
            lnt->type = LST_NETWORK_TYPE_NUMBER;
            lnt->value.number = lua_tonumber(L, index);
        }
        return true;
    }

    if (valueType == LUA_TBOOLEAN) {
        lnt->type = LST_NETWORK_TYPE_BOOLEAN;
        lnt->value.boolean = lua_toboolean(L, index);
        return true;
    }

    if (valueType == LUA_TSTRING) {
        lnt->type = LST_NETWORK_TYPE_STRING;
        lnt->value.string = lua_tostring(L, index);
        if (lnt->value.string == NULL || strlen(lnt->value.string) > 256) {
            LOG_LUA("smlua_value_to_lnt on invalid string value: '%s'", (lnt->value.string == NULL) ? "<null>" : lnt->value.string);
            return false;
        }
        return true;
    }

    if (valueType == LUA_TNIL) {
        lnt->type = LST_NETWORK_TYPE_NIL;
        return true;
    }

    return false;
}

static void smlua_push_lnt(struct LSTNetworkType* lnt) {
    lua_State* L = gLuaState;
    switch (lnt->type) {
        case LST_NETWORK_TYPE_INTEGER:
            lua_pushinteger(L, lnt->value.integer);
            break;
        case LST_NETWORK_TYPE_NUMBER:
            lua_pushnumber(L, lnt->value.number);
            break;
        case LST_NETWORK_TYPE_BOOLEAN:
            lua_pushboolean(L, lnt->value.boolean);
            break;
        case LST_NETWORK_TYPE_STRING:
            lua_pushstring(L, lnt->value.string);
            break;
        case LST_NETWORK_TYPE_NIL:
            lua_pushnil(L);
            break;
        default: SOFT_ASSERT(false);
    }
}

static void smlua_sync_table_send_field(u8 toLocalIndex, int stackIndex, bool alterSeq) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    int syncTableIndex = stackIndex + 1;
    int keyIndex       = stackIndex + 2;
    int valueIndex     = stackIndex + 3;

    // get modRemoteIndex
    u16 modRemoteIndex = smlua_get_integer_field(syncTableIndex, "_remoteIndex");
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("smlua_sync_table_send_field on invalid modRemoteIndex: %u", modRemoteIndex);
        return;
    }

    // get lst
    enum LuaSyncTableType lst = smlua_get_integer_field(syncTableIndex, "_type");
    if (!gSmLuaConvertSuccess || lst >= LST_MAX) {
        LOG_LUA("smlua_sync_table_send_field on invalid LST: %u", lst);
        return;
    }

    // get key
    struct LSTNetworkType lntKey = { 0 };
    if (!smlua_value_to_lnt(keyIndex, &lntKey)) { return; }


      ///////////
     // value //
    ///////////

    // get value
    struct LSTNetworkType lntValue = { 0 };
    if (!smlua_value_to_lnt(valueIndex, &lntValue)) { return; }

    // set value
    lua_getfield(L, syncTableIndex, "_table");
    lua_pushvalue(L, -3);
    lua_pushvalue(L, -3);
    lua_settable(L, -3);
    lua_pop(L, 1); // pop _table


      /////////
     // seq //
    /////////

    // get seq table
    lua_getfield(L, syncTableIndex, "_seq");
    lua_pushvalue(L, keyIndex);
    lua_gettable(L, -2);
    u64 seq = lua_tointeger(L, -1);
    lua_pop(L, 1); // pop seq value

    // set seq number
    if (!gLuaInitializingScript && alterSeq) {
        seq += MAX_PLAYERS + (MAX_PLAYERS - gNetworkPlayers[0].globalIndex);
        lua_pushvalue(L, keyIndex);
        lua_pushinteger(L, seq);
        lua_settable(L, -3);
    }
    lua_pop(L, 1); // pop seq table


      ///////////
     // index //
    ///////////

    // get index
    u16 index = smlua_get_integer_field(syncTableIndex, "_index");
    index = network_player_global_index_from_local(index);


      /////////////
     // network //
    /////////////

    // send over the network
    if (!gLuaInitializingScript && seq > 0) {
        network_send_lua_sync_table(toLocalIndex, seq, modRemoteIndex, lst, index, &lntKey, &lntValue);
    }

    LUA_STACK_CHECK_END();
}

static int smlua__set_sync_table_field(UNUSED lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    smlua_sync_table_send_field(0, 0, true);
    return 1;
}

void smlua_set_sync_table_field_from_network(u64 seq, u16 modRemoteIndex, u16 lst, u16 index, struct LSTNetworkType* lntKey, struct LSTNetworkType* lntValue) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    // figure out table
    struct ModTable* table = NULL;
    if (gNetworkType == NT_SERVER) {
        table = &gModTableLocal;
    } else if (gNetworkType == NT_CLIENT) {
        table = &gModTableRemote;
    } else {
        LOG_ERROR("Received sync table field packet with an unknown network type: %d", gNetworkType);
        return;
    }

    // figure out entry
    struct ModListEntry* entry = NULL;
    for (int i = 0; i < table->entryCount; i++) {
        if (table->entries[i].remoteIndex == modRemoteIndex) {
            entry = &table->entries[i];
            break;
        }
    }
    if (entry == NULL) {
        LOG_ERROR("Could not find mod list entry for modRemoteIndex: %u", modRemoteIndex);
        return;
    }

    // sanity check lst
    if (lst >= LST_MAX) {
        LOG_ERROR("Received sync table field packet with an invalid LST: %u", lst);
        return;
    }

    // sanity check lntValue
    if (lntValue->type >= LST_NETWORK_TYPE_MAX) {
        LOG_ERROR("Received sync table field packet with an invalid lnt type: %u", lntValue->type);
        return;
    }

    lua_getglobal(L, "_G"); // get global table
    lua_getfield(L, LUA_REGISTRYINDEX, entry->path); // get the file's "global" table

    // get sync table
    u16 syncTableSize = 0;
    switch (lst) {
        case LST_GLOBAL:
            syncTableSize = 1;
            lua_getfield(L, -1, "gGlobalSyncTable");
            break;
        case LST_PLAYER:
            syncTableSize = 2;
            lua_getfield(L, -1, "gPlayerSyncTable");
            lua_pushinteger(L, network_player_local_index_from_global(index));
            lua_gettable(L, -2);
            break;
        default: assert(false);
    }

    // get seq table
    lua_getfield(L, -1, "_seq");

    // get seq number
    smlua_push_lnt(lntKey);
    lua_gettable(L, -2);
    u64 readSeq = lua_tointeger(L, -1);
    lua_pop(L, 1); // pop seq value

    // validate seq
    if (seq <= readSeq) {
        LOG_INFO("Received outdated sync table field packet: %llu <= %llu", seq, readSeq);
        lua_pop(L, 1); // pop seq table
        lua_pop(L, syncTableSize); // pop sync table
        lua_pop(L, 1); // pop file's "global" table
        lua_pop(L, 1); // pop global table
        return;
    }

    // set seq number
    smlua_push_lnt(lntKey);
    lua_pushinteger(L, seq);
    lua_settable(L, -3);
    lua_pop(L, 1); // pop seq table

    // get internal table
    lua_pushstring(L, "_table");
    lua_rawget(L, -2);
    int t = lua_gettop(L);

    // set key/value
    smlua_push_lnt(lntKey);
    smlua_push_lnt(lntValue);
    lua_rawset(L, t);

    lua_pop(L, 1); // pop internal table
    lua_pop(L, syncTableSize); // pop sync table
    lua_pop(L, 1); // pop file's "global" table
    lua_pop(L, 1); // pop global table
    LUA_STACK_CHECK_END();
}

static void smlua_exec_str(char* str) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;
    if (luaL_dostring(L, str) != LUA_OK) {
        LOG_LUA("Failed to load lua string.");
        puts(smlua_to_string(L, lua_gettop(L)));
    }
    LUA_STACK_CHECK_END();
}

void smlua_sync_table_init_globals(char* path, u16 modRemoteIndex) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    lua_getfield(L, LUA_REGISTRYINDEX, path);
    int base = lua_gettop(L);
    {
        lua_newtable(L);
        int t = lua_gettop(L);

        // push fields
        smlua_push_integer_field(t, "_remoteIndex", modRemoteIndex);
        smlua_push_integer_field(t, "_type", LST_GLOBAL);
        smlua_push_integer_field(t, "_index", 0);
        smlua_push_table_field(t, "_seq");
        smlua_push_table_field(t, "_table");
        smlua_push_string_field(t, "_name", "gGlobalSyncTable");
        smlua_push_nil_field(t, "_parent");

        // attach metatable
        lua_pushglobaltable(L);
        lua_getfield(L, -1, "_SyncTable");
        lua_setmetatable(L, -3);
        lua_pop(L, 1); // pop global table

        // attach sync table to file's "globals"
        lua_setfield(L, base, "gGlobalSyncTable");
    }
    {
        lua_newtable(L);
        int playerTop = lua_gettop(L);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            lua_pushinteger(L, i);

            lua_newtable(L);
            int t = lua_gettop(L);

            smlua_push_integer_field(t, "_remoteIndex", modRemoteIndex);
            smlua_push_integer_field(t, "_type", LST_PLAYER);
            smlua_push_integer_field(t, "_index", i);
            smlua_push_table_field(t, "_seq");
            smlua_push_table_field(t, "_table");
            smlua_push_string_field(t, "_name", "gPlayerSyncTable"); // <--- incorrect
            smlua_push_nil_field(t, "_parent"); // <--- incorrect

            // attach metatable
            lua_pushglobaltable(L);
            lua_getfield(L, -1, "_SyncTable");
            lua_setmetatable(L, -3);
            lua_pop(L, 1); // pop global table

            // attach table to gPlayerSyncTable
            lua_settable(L, playerTop);
        }
        lua_setfield(L, base, "gPlayerSyncTable");
    }
    lua_pop(L, 1); // pop file's "global" table

    LUA_STACK_CHECK_END();
}

void smlua_bind_sync_table(void) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;
    smlua_bind_function(L, "_set_sync_table_field", smlua__set_sync_table_field);
    LUA_STACK_CHECK_END();
}

////////////////////////////////////////////////


static void smlua_sync_table_send_table(u8 toLocalIndex) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;
    int tableIndex = lua_gettop(L);

    lua_getfield(L, -1, "_table");
    int internalIndex = lua_gettop(L);

    lua_pushnil(L); // first key
    while (lua_next(L, internalIndex) != 0) {
        // uses 'key' (at index -2) and 'value' (at index -1)
        //LOG_INFO("    sending sync table field: %s", lua_tostring(L, -2));

        lua_pushvalue(L, tableIndex); // insert sync table
        lua_insert(L, -3); // re-order sync table

        smlua_sync_table_send_field(toLocalIndex, internalIndex, false);

        lua_remove(L, -3); // remove sync table

        lua_pop(L, 1); // removed value ; keeps 'key' for next iteration
    }

    lua_pop(L, 1); // remove internal table

    LUA_STACK_CHECK_END();
}

static void smlua_sync_table_send_all_file(u8 toLocalIndex, const char* path) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    LOG_INFO("sending sync table for file %s to %u", path, toLocalIndex);

    lua_getfield(L, LUA_REGISTRYINDEX, path); // get the file's "global" table

    {
        lua_getfield(L, -1, "gGlobalSyncTable");
        smlua_sync_table_send_table(toLocalIndex);
        lua_pop(L, 1); // pop gGlobalSyncTable
    }

    {
        lua_getfield(L, -1, "gPlayerSyncTable");
        for (int i = 0; i < MAX_PLAYERS; i++) {
            // get gPlayerSyncTable[i]
            lua_pushinteger(L, i);
            lua_gettable(L, -2);

            smlua_sync_table_send_table(toLocalIndex);

            lua_pop(L, 1); // pop gPlayerSyncTable[i]
        }
        lua_pop(L, 1); // pop gPlayerSyncTable
    }

    lua_pop(L, 1); // pop file's "global" table

    LUA_STACK_CHECK_END();
}

void smlua_sync_table_send_all(u8 toLocalIndex) {
    SOFT_ASSERT(gNetworkType == NT_SERVER);
    LUA_STACK_CHECK_BEGIN();
    for (int i = 0; i < gModTableLocal.entryCount; i++) {
        struct ModListEntry* entry = &gModTableLocal.entries[i];
        if (!entry->enabled) { continue; }
        smlua_sync_table_send_all_file(toLocalIndex, entry->path);
    }
    LUA_STACK_CHECK_END();
}
