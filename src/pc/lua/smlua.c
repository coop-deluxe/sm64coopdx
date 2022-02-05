#include "smlua.h"
#include "pc/mod_list.h"

lua_State* gLuaState = NULL;
u8 gLuaInitializingScript = 0;

static void smlua_exec_file(char* path) {
    lua_State* L = gLuaState;
    if (luaL_dofile(L, path) != LUA_OK) {
        LOG_LUA("Failed to load lua file '%s'.", path);
        puts(smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

static void smlua_exec_str(char* str) {
    lua_State* L = gLuaState;
    if (luaL_dostring(L, str) != LUA_OK) {
        LOG_LUA("Failed to load lua string.");
        puts(smlua_to_string(L, lua_gettop(L)));
    }
    lua_pop(L, lua_gettop(L));
}

static void smlua_load_script(char* path, u16 remoteIndex) {
    lua_State* L = gLuaState;
    gLuaInitializingScript = 1;
    if (luaL_loadfile(L, path) != LUA_OK) {
        LOG_LUA("Failed to load lua script '%s'.", path);
        puts(smlua_to_string(L, lua_gettop(L)));
        return;
    }

    lua_newtable(L); // create _ENV tables
    lua_newtable(L); // create metatable
    lua_getglobal(L, "_G"); // get global table

    // set global as the metatable
    lua_setfield(L, -2, "__index");
    lua_setmetatable(L, -2);

    // push to registry with path as name (must be unique)
    lua_setfield(L, LUA_REGISTRYINDEX, path);
    lua_getfield(L, LUA_REGISTRYINDEX, path);
    lua_setupvalue(L, 1, 1); // set upvalue (_ENV)

    // load per-file globals
    smlua_sync_table_init_globals(path, remoteIndex);

    // run chunks
    if (lua_pcall(L, 0, LUA_MULTRET, 0) != LUA_OK) {
        LOG_LUA("Failed to execute lua script '%s'.", path);
        puts(smlua_to_string(L, lua_gettop(L)));
        smlua_dump_stack();
        gLuaInitializingScript = 0;
        return;
    }
    gLuaInitializingScript = 0;
}

void smlua_init(void) {
    smlua_shutdown();
    smlua_cobject_allowlist_init();

    gLuaState = luaL_newstate();
    lua_State* L = gLuaState;

    // load libraries
    luaopen_base(L);
    //luaopen_coroutine(L);
    //luaopen_debug(L);
    //luaopen_io(L);
    luaL_requiref(L, "math", luaopen_math, 1);
    //luaopen_os(L);
    //luaopen_package(L);
    luaL_requiref(L, "string", luaopen_string, 1);
    luaL_requiref(L, "table", luaopen_table, 1);
    //luaopen_utf8(L);

    smlua_bind_hooks();
    smlua_bind_cobject();
    smlua_bind_functions();
    smlua_bind_functions_autogen();
    smlua_bind_sync_table();

    extern char gSmluaConstants[];
    smlua_exec_str(gSmluaConstants);

    smlua_cobject_init_globals();

    // load scripts
    LOG_INFO("Loading scripts:");
    struct ModTable* table = gModTableCurrent;
    for (int i = 0; i < table->entryCount; i++) {
        struct ModListEntry* entry = &table->entries[i];
        if (!entry->enabled) { continue; }
        LOG_INFO("    %s", entry->path);
        smlua_load_script(entry->path, entry->remoteIndex);
    }
}

void smlua_update(void) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    smlua_call_event_hooks(HOOK_UPDATE);
}

void smlua_shutdown(void) {
    smlua_cobject_allowlist_shutdown();
    lua_State* L = gLuaState;
    if (L != NULL) {
        lua_close(L);
        gLuaState = NULL;
    }
}
