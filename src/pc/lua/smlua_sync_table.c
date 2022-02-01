#include "smlua.h"
#include "pc/mod_list.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"

static u8 smlua_sync_table_send_field(u8 toLocalIndex, int stackIndex, bool alterSeq, bool push) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    // get remoteIndex
    u16 remoteIndex = smlua_get_integer_field(stackIndex + 1, "_remoteIndex");
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("smlua_sync_table_send_field on invalid remoteIndex: %u", remoteIndex);
        if (push) { lua_pushinteger(L, 0); }
        return 0;
    }

    // get lst
    enum LuaSyncTableType lst = smlua_get_integer_field(stackIndex + 1, "_type");
    if (!gSmLuaConvertSuccess) { return 0; }
    if (lst >= LST_MAX) {
        LOG_LUA("smlua_sync_table_send_field on invalid LST: %u", lst);
        if (push) { lua_pushinteger(L, 0); }
        return 0;
    }

    // get key
    const char* key = smlua_to_string(L, stackIndex + 2);
    if (!gSmLuaConvertSuccess) { return 0; }
    if (key == NULL || strlen(key) == 0 || strlen(key) > 64) {
        LOG_LUA("smlua_sync_table_send_field on invalid key: '%s'", (key == NULL) ? "<null>" : key);
        if (push) { lua_pushinteger(L, 0); }
        return 0;
    }

    // get value
    union LSTNetworkUnion lUnion = { 0 };
    enum LSTNetworkType lUnionType = LST_NETWORK_TYPE_MAX;
    int valueType = lua_type(L, stackIndex + 3);
    if (valueType == LUA_TNUMBER) {
        lUnion.integer = lua_tointeger(L, stackIndex + 3);
        lUnionType = LST_NETWORK_TYPE_INTEGER;

        if (lUnion.integer == 0) {
            lUnion.number = lua_tonumber(L, stackIndex + 3);
            lUnionType = LST_NETWORK_TYPE_NUMBER;
        }

    } else if (valueType == LUA_TBOOLEAN) {
        lUnion.boolean = lua_toboolean(L, stackIndex + 3);
        lUnionType = LST_NETWORK_TYPE_BOOLEAN;
    } else if (valueType == LUA_TSTRING) {
        lUnion.string = lua_tostring(L, stackIndex + 3);
        lUnionType = LST_NETWORK_TYPE_STRING;
        if (lUnion.string == NULL || strlen(lUnion.string) > 256) {
            LOG_LUA("smlua_sync_table_send_field on invalid string value: '%s'", (lUnion.string == NULL) ? "<null>" : lUnion.string);
            if (push) { lua_pushinteger(L, 0); }
            return 0;
        }
    } else if (valueType == LUA_TNIL) {
        lUnionType = LST_NETWORK_TYPE_NIL;
    } else {
        LOG_LUA("smlua_sync_table_send_field on invalid type: '%d'", valueType);
        if (push) { lua_pushinteger(L, 0); }
        return 0;
    }

    // get seq table
    lua_getfield(L, stackIndex + 1, "_seq");
    int seqT = lua_gettop(L);

    // get seq number
    lua_getfield(L, -1, key);
    u64 seq = lua_tointeger(L, -1);
    lua_pop(L, 1);

    // set seq number
    if (!gLuaInitializingScript && alterSeq) {
        seq += MAX_PLAYERS + (MAX_PLAYERS - gNetworkPlayers[0].globalIndex);
        smlua_push_number_field(seqT, (char*)key, seq);
    }
    lua_pop(L, 1);

    // get index
    u16 index = smlua_get_integer_field(stackIndex + 1, "_index");
    index = network_player_global_index_from_local(index);

    if (!gLuaInitializingScript && seq > 0) {
        network_send_lua_sync_table(toLocalIndex, seq, remoteIndex, lst, index, key, lUnionType, lUnion);
    }

    LUA_STACK_CHECK_END();
    if (push) { lua_pushinteger(L, 1); }
    return 1;
}

static int smlua__set_sync_table_field(UNUSED lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    return smlua_sync_table_send_field(0, 0, true, true);
}

void smlua_set_sync_table_field_from_network(u64 seq, u16 remoteIndex, u16 lst, u16 index, const char* key, u16 lUnionType, union LSTNetworkUnion lUnion) {
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
        if (table->entries[i].remoteIndex == remoteIndex) {
            entry = &table->entries[i];
            break;
        }
    }
    if (entry == NULL) {
        LOG_ERROR("Could not find mod list entry for remoteIndex: %u", remoteIndex);
        return;
    }

    // sanity check lst
    if (lst >= LST_MAX) {
        LOG_ERROR("Received sync table field packet with an invalid LST: %u", lst);
        return;
    }

    // sanity check lUnionType
    if (lUnionType >= LST_NETWORK_TYPE_MAX) {
        LOG_ERROR("Received sync table field packet with an invalid lUnionType: %u", lUnionType);
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
    int seqT = lua_gettop(L);

    // get seq number
    lua_getfield(L, -1, key);
    u64 readSeq = lua_tointeger(L, -1);
    lua_pop(L, 1);

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
    smlua_push_number_field(seqT, (char*)key, seq);
    lua_pop(L, 1); // pop seq table

    // get internal table
    lua_pushstring(L, "_table");
    lua_rawget(L, -2);
    int t = lua_gettop(L);

    // set key/value
    switch (lUnionType) {
        case LST_NETWORK_TYPE_INTEGER:
            lua_pushstring(L, key);
            lua_pushinteger(L, lUnion.integer);
            lua_rawset(L, t);
            break;
        case LST_NETWORK_TYPE_NUMBER:
            lua_pushstring(L, key);
            lua_pushnumber(L, lUnion.number);
            lua_rawset(L, t);
            break;
        case LST_NETWORK_TYPE_BOOLEAN:
            lua_pushstring(L, key);
            lua_pushboolean(L, lUnion.boolean);
            lua_rawset(L, t);
            break;
        case LST_NETWORK_TYPE_STRING:
            lua_pushstring(L, key);
            lua_pushstring(L, lUnion.string);
            lua_rawset(L, t);
            break;
        case LST_NETWORK_TYPE_NIL:
            lua_pushstring(L, key);
            lua_pushnil(L);
            lua_rawset(L, t);
            break;
        default: SOFT_ASSERT(false);
    }

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

void smlua_sync_table_init_globals(char* path, u16 remoteIndex) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    lua_getfield(L, LUA_REGISTRYINDEX, path);
    int base = lua_gettop(L);
    {
        lua_newtable(L);
        int t = lua_gettop(L);

        smlua_push_integer_field(t, "_remoteIndex", remoteIndex);
        smlua_push_integer_field(t, "_type", LST_GLOBAL);
        smlua_push_integer_field(t, "_index", 0);

        lua_newtable(L);
        lua_setfield(L, t, "_seq");

        lua_newtable(L);
        lua_setfield(L, t, "_table");

        lua_pushglobaltable(L);
        lua_getfield(L, -1, "_SyncTable");
        lua_setmetatable(L, -3);
        lua_pop(L, 1); // pop global table
        lua_setfield(L, base, "gGlobalSyncTable");
    }
    {
        lua_newtable(L);
        int playerTop = lua_gettop(L);
        for (int i = 0; i < MAX_PLAYERS; i++) {
            lua_pushinteger(L, i);

            lua_newtable(L);
            int t = lua_gettop(L);

            smlua_push_integer_field(t, "_remoteIndex", remoteIndex);
            smlua_push_integer_field(t, "_type", LST_PLAYER);
            smlua_push_integer_field(t, "_index", i);

            lua_newtable(L);
            lua_setfield(L, t, "_seq");

            lua_newtable(L);
            lua_setfield(L, t, "_table");

            lua_pushglobaltable(L);
            lua_getfield(L, -1, "_SyncTable");
            lua_setmetatable(L, -3);
            lua_pop(L, 1); // pop global table

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

        smlua_sync_table_send_field(toLocalIndex, internalIndex, false, false);

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
