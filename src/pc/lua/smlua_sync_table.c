#include "smlua.h"
#include "pc/mod_list.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"

#define MAX_UNWOUND_SIZE 256
static struct LSTNetworkType sUnwoundLnts[MAX_UNWOUND_LNT] = { 0 };
u16 sUnwoundLntsCount = 0;

static void smlua_sync_table_create(u16 modRemoteIndex, enum LuaSyncTableType lst, int* parentIndex, int* keyIndex) {
    lua_State* L = gLuaState;
    lua_newtable(L);
    int t = lua_gettop(L);

    // push fields
    smlua_push_integer_field(t, "_remoteIndex", modRemoteIndex);
    smlua_push_integer_field(t, "_type", lst);
    smlua_push_table_field(t, "_seq");
    smlua_push_table_field(t, "_table");

    // set parent
    lua_pushstring(L, "_parent");
    if (parentIndex == NULL) { lua_pushnil(L); } else { lua_pushvalue(L, *parentIndex); }
    lua_settable(L, -3);

    // set key name
    lua_pushstring(L, "_name");
    if (keyIndex == NULL) { lua_pushnil(L); } else { lua_pushvalue(L, *keyIndex); }
    lua_settable(L, -3);

    // attach metatable
    lua_pushglobaltable(L);
    lua_getfield(L, -1, "_SyncTable");
    lua_setmetatable(L, -3);
    lua_pop(L, 1); // pop global table
}

static bool smlua_sync_table_unwind(int syncTableIndex, int keyIndex) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;
    sUnwoundLntsCount = 0;

    // get key
    sUnwoundLnts[sUnwoundLntsCount++] = smlua_to_lnt(L, keyIndex);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("attempted to unwind sync table with invalid key type");
        return false;
    }

    // duplicate sync table for iteration
    lua_pushvalue(L, syncTableIndex);
    syncTableIndex = lua_gettop(L);

    while (true) {
        // make sure we remain within limits
        if (sUnwoundLntsCount >= MAX_UNWOUND_LNT) {
            LOG_LUA("attempted to unwind sync table past its limit");
            return false;
        }

        // get name of table
        lua_pushstring(L, "_name");
        lua_gettable(L, syncTableIndex);
        sUnwoundLnts[sUnwoundLntsCount++] = smlua_to_lnt(L, -1);

        // translate player index
        lua_getfield(L, syncTableIndex, "_type");
        lua_Integer lst = lua_tointeger(L, -1);
        lua_pop(L, 1);
        if (lst == LST_PLAYER) {
            struct LSTNetworkType* n = &sUnwoundLnts[sUnwoundLntsCount - 1];
            assert(n->type == LST_NETWORK_TYPE_INTEGER);
            n->value.integer = network_player_global_index_from_local(n->value.integer);
        }

        lua_pop(L, 1); // pop _name value
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("attempted to unwind sync table with invalid parent");
            lua_pop(L, 1); // pop iterative _parent
            return false;
        }

        // get parent of table
        lua_pushstring(L, "_parent");
        lua_gettable(L, syncTableIndex);
        int parentType = lua_type(L, -1);
        lua_replace(L, syncTableIndex);

        // validate parent type
        if (parentType != LUA_TTABLE) {
            if (parentType != LUA_TNIL) {
                LOG_LUA("attempted to unwind sync table into an invalid parent");
                return false;
            }
            break;
        }
    }

    lua_pop(L, 1); // pop iterative _parent

    // check size
    size_t unwoundSize = 0;
    for (int i = 0; i < sUnwoundLntsCount; i++) {
        unwoundSize += sUnwoundLnts[i].size;
    }

    if (unwoundSize >= MAX_UNWOUND_SIZE) {
        LOG_LUA("attempted to unwind sync table with too long of a key/parent length");
        return false;
    }

    LUA_STACK_CHECK_END();
    return true;
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
        LOG_LUA("Error: tried to alter sync table with an invalid modRemoteIndex: %u", modRemoteIndex);
        return;
    }

    // get key
    struct LSTNetworkType lntKey = smlua_to_lnt(L, keyIndex);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Error: tried to alter sync table with an invalid key");
        return;
    }
    lntKey = lntKey;
    

      ////////////////
     // prev value //
    ////////////////

    lua_getfield(L, syncTableIndex, "_table");
    lua_pushvalue(L, keyIndex);
    lua_rawget(L, -2);
    int prevValueType = lua_type(L, -1);
    lua_pop(L, 1); // pop prev value
    lua_pop(L, 1); // pop _table

    if (prevValueType == LUA_TTABLE) {
        LOG_LUA("Error: tried to assign on top of sync table");
        return;
    }

      ///////////
     // value //
    ///////////

    // get value
    int valueType = lua_type(L, valueIndex);
    if (valueType == LUA_TTABLE) {
        if (prevValueType != LUA_TNIL) {
            LOG_LUA("Error: tried to set a sync table field to a different sync table");
            return;
        }

        if (!smlua_is_table_empty(valueIndex)) {
            LOG_LUA("Error: tried to generate a sync table with a non-empty table");
            return;
        }

        // create sync table
        int modRemoteIndex = smlua_get_integer_field(syncTableIndex, "_remoteIndex");

        // set table
        lua_getfield(L, syncTableIndex, "_table");
        lua_pushvalue(L, keyIndex);
        smlua_sync_table_create(modRemoteIndex, LST_NORMAL, &syncTableIndex, &keyIndex);
        lua_settable(L, -3);
        lua_pop(L, 1); // pop _table

        LUA_STACK_CHECK_END();
        return;
    }
    struct LSTNetworkType lntValue = smlua_to_lnt(L, valueIndex);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Error: tried to alter sync table with an invalid value");
        return;
    }

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


      /////////////
     // network //
    /////////////

    // unwind key + parent tables
    if (!smlua_sync_table_unwind(syncTableIndex, keyIndex)) {
        LOG_LUA("Error: failed to unwind sync table for sending over the network");
        return;
    }

    // send over the network
    if (!gLuaInitializingScript && seq > 0) {
        network_send_lua_sync_table(toLocalIndex, seq, modRemoteIndex, sUnwoundLntsCount, sUnwoundLnts, &lntValue);
    }

    LUA_STACK_CHECK_END();
}

static int smlua__set_sync_table_field(UNUSED lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    smlua_sync_table_send_field(0, 0, true);
    return 1;
}

void smlua_set_sync_table_field_from_network(u64 seq, u16 modRemoteIndex, u16 lntKeyCount, struct LSTNetworkType* lntKeys, struct LSTNetworkType* lntValue) {
    LUA_STACK_CHECK_BEGIN();
    lua_State* L = gLuaState;

    // figure out mod table
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

    // sanity check lntValue
    if (lntValue->type >= LST_NETWORK_TYPE_MAX) {
        LOG_ERROR("Received sync table field packet with an invalid lnt type: %u", lntValue->type);
        return;
    }

    lua_getglobal(L, "_G"); // get global table
    lua_getfield(L, LUA_REGISTRYINDEX, entry->path); // get the file's "global" table
    int fileGlobalIndex = lua_gettop(L);

    // push global sync table
    u16 syncTableSize = 1;
    smlua_push_lnt(&lntKeys[lntKeyCount - 1]);
    lua_gettable(L, fileGlobalIndex);
    int syncTableIndex = lua_gettop(L);
    if (lua_type(L, -1) != LUA_TTABLE) {
        LOG_ERROR("Received sync table field packet with an invalid table");
        return;
    }

    for (int i = lntKeyCount - 2; i >= 1; i--) {
        // get child sync table
        smlua_push_lnt(&lntKeys[i]);
        lua_gettable(L, -2);

        // create missing tables
        if (lua_type(L, -1) != LUA_TTABLE) {
            lua_pop(L, 1); // pop non-table

            // push internal table of parent
            lua_pushstring(L, "_table");
            lua_gettable(L, syncTableIndex);

            // set internal[key] = new sync table
            smlua_push_lnt(&lntKeys[i]);
            int keyIndex = lua_gettop(L);
            smlua_sync_table_create(modRemoteIndex, LST_NORMAL, &syncTableIndex, &keyIndex);
            lua_rawset(L, -3);

            // get new sync table
            smlua_push_lnt(&lntKeys[i]);
            lua_gettable(L, -2);

            lua_remove(L, -2); // remove paren'ts internal table
        } else {

            // translate player index
            if (smlua_get_integer_field(-1, "_type") == LST_PLAYER) {
                lua_pop(L, 1); // pop wrong table
                assert(lntKeys[i].type == LST_NETWORK_TYPE_INTEGER);
                lua_pushinteger(L, network_player_local_index_from_global(lntKeys[i].value.integer));
                lua_gettable(L, -2);
            }
        }

        lua_remove(L, -2); // remove parent table
    }

    // get seq table
    lua_getfield(L, -1, "_seq");

    // get seq number
    smlua_push_lnt(&lntKeys[0]);
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
    smlua_push_lnt(&lntKeys[0]);
    lua_pushinteger(L, seq);
    lua_settable(L, -3);
    lua_pop(L, 1); // pop seq table

    // get internal table
    lua_pushstring(L, "_table");
    lua_rawget(L, -2);
    int t = lua_gettop(L);

    // set key/value
    smlua_push_lnt(&lntKeys[0]);
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
    int fileGlobalIndex = lua_gettop(L);
    {
        // create and attach global sync table
        lua_pushstring(L, "gGlobalSyncTable");
        int keyIndex = lua_gettop(L);
        smlua_sync_table_create(modRemoteIndex, LST_NORMAL, NULL, &keyIndex);
        lua_settable(L, fileGlobalIndex);
    }
    {
        // create player sync table
        lua_pushstring(L, "gPlayerSyncTable");
        lua_newtable(L);
        int tableIndex = lua_gettop(L);
        smlua_push_string_field(tableIndex, "_name", "gPlayerSyncTable");

        // create internal table
        lua_pushstring(L, "_table");
        lua_newtable(L);
        int internalTableIndex = lua_gettop(L);

        // create player sync tables
        for (int i = 0; i < MAX_PLAYERS; i++) {
            lua_pushinteger(L, i);
            int keyIndex = lua_gettop(L);
            smlua_sync_table_create(modRemoteIndex, LST_PLAYER, &tableIndex, &keyIndex);
            lua_settable(L, internalTableIndex);
        }

        // attach internal table
        lua_settable(L, tableIndex);

        // attach metatable
        lua_pushglobaltable(L);
        lua_getfield(L, -1, "_ReadOnlyTable");
        lua_setmetatable(L, tableIndex);
        lua_pop(L, 1); // pop global table

        // attach player sync table
        lua_settable(L, fileGlobalIndex);
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
