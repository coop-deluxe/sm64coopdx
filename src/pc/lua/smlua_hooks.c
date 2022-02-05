#include "smlua.h"
#include "pc/djui/djui_chat_message.h"

#define MAX_HOOKED_REFERENCES 64

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

int smlua_hook_event(lua_State* L) {
    if (L == NULL) { return 0; }
    u16 hookType = smlua_to_integer(L, -2);
    if (!gSmLuaConvertSuccess) { return 0; }

    if (hookType >= HOOK_MAX) {
        LOG_LUA("Hook Type: %d exceeds max!", hookType);
        smlua_logline();
        return 0;
    }

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    if (hook->count >= MAX_HOOKED_REFERENCES) {
        LOG_LUA("Hook Type: %s exceeded maximum references!", LuaHookedEventTypeName[hookType]);
        smlua_logline();
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA("tried to hook undefined function to '%s'", LuaHookedEventTypeName[hookType]);
        smlua_logline();
        return 0;
    }

    hook->reference[hook->count] = ref;
    hook->count++;

    return 1;
}

void smlua_call_event_hooks(enum LuaHookedEventType hookType) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != lua_pcall(L, 0, 0, 0)) {
            LOG_LUA("Failed to call the event_hook callback: %u, %s", hookType, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }
    }
}

void smlua_call_event_hooks_mario_param(enum LuaHookedEventType hookType, struct MarioState* m) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != lua_pcall(L, 1, 0, 0)) {
            LOG_LUA("Failed to call the callback: %u, %s", hookType, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }
    }
}

void smlua_call_event_hooks_mario_params(enum LuaHookedEventType hookType, struct MarioState* m1, struct MarioState* m2) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m1->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push mario state
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m2->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != lua_pcall(L, 2, 0, 0)) {
            LOG_LUA("Failed to call the callback: %u, %s", hookType, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }
    }
}

void smlua_call_event_hooks_network_player_param(enum LuaHookedEventType hookType, struct NetworkPlayer* np) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }
    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    for (int i = 0; i < hook->count; i++) {
        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mario state
        lua_getglobal(L, "gNetworkPlayers");
        lua_pushinteger(L, np->localIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != lua_pcall(L, 1, 0, 0)) {
            LOG_LUA("Failed to call the callback: %u, %s", hookType, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }
    }
}

  ////////////////////
 // hooked actions //
////////////////////

struct LuaHookedMarioAction {
    u32 action;
    int reference;
};

#define MAX_HOOKED_ACTIONS 64

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;

int smlua_hook_mario_action(lua_State* L) {
    if (L == NULL) { return 0; }
    if (sHookedMarioActionsCount >= MAX_HOOKED_ACTIONS) {
        LOG_LUA("Hooked mario actions exceeded maximum references!");
        smlua_logline();
        return 0;
    }

    lua_Integer action = smlua_to_integer(L, 1);
    if (action == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA("Hook Action: tried to hook invalid action: %lld, %u", action, gSmLuaConvertSuccess);
        smlua_logline();
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);

    if (ref == -1) {
        LOG_LUA("Hook Action: %lld tried to hook undefined function", action);
        smlua_logline();
        return 0;
    }

    struct LuaHookedMarioAction* hooked = &sHookedMarioActions[sHookedMarioActionsCount];
    hooked->action = action;
    hooked->reference = ref;
    if (!gSmLuaConvertSuccess) { return 0; }

    sHookedMarioActionsCount++;
    return 1;
}

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        if (sHookedMarioActions[i].action == m->action) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, sHookedMarioActions[i].reference);

            // push mario state
            lua_getglobal(L, "gMarioStates");
            lua_pushinteger(L, m->playerIndex);
            lua_gettable(L, -2);
            lua_remove(L, -2);

            // call the callback
            if (0 != lua_pcall(L, 1, 1, 0)) {
                LOG_LUA("Failed to call the action callback: %u, %s", m->action, lua_tostring(L, -1));
                smlua_logline();
                continue;
            }

            // output the return value
            *returnValue = smlua_to_integer(L, -1);
            lua_pop(L, 1);

            if (!gSmLuaConvertSuccess) { return false; }

            return true;
        }
    }

    return false;
}

  /////////////////////////
 // hooked chat command //
/////////////////////////

struct LuaHookedChatCommand {
    char* command;
    char* description;
    int reference;
};

#define MAX_HOOKED_CHAT_COMMANDS 64

static struct LuaHookedChatCommand sHookedChatCommands[MAX_HOOKED_CHAT_COMMANDS] = { 0 };
static int sHookedChatCommandsCount = 0;

int smlua_hook_chat_command(lua_State* L) {
    if (L == NULL) { return 0; }
    if (sHookedChatCommandsCount >= MAX_HOOKED_CHAT_COMMANDS) {
        LOG_LUA("Hooked chat command exceeded maximum references!");
        smlua_logline();
        return 0;
    }

    const char* command = smlua_to_string(L, 1);
    if (command == NULL || strlen(command) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA("Hook chat command: tried to hook invalid command");
        smlua_logline();
        return 0;
    }

    const char* description = smlua_to_string(L, 2);
    if (description == NULL || strlen(description) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA("Hook chat command: tried to hook invalid description");
        smlua_logline();
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA("Hook chat command: tried to hook undefined function '%s'", command);
        smlua_logline();
        return 0;
    }

    struct LuaHookedChatCommand* hooked = &sHookedChatCommands[sHookedChatCommandsCount];
    hooked->command = strdup(command);
    hooked->description = strdup(description);
    hooked->reference = ref;
    if (!gSmLuaConvertSuccess) { return 0; }

    sHookedChatCommandsCount++;
    return 1;
}

bool smlua_call_chat_command_hook(char* command) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        size_t commandLength = strlen(hook->command);
        for (size_t j = 0; j < commandLength; j++) {
            if (hook->command[j] != command[j + 1]) {
                goto NEXT_HOOK;
            }
        }

        char* params = &command[commandLength + 1];
        if (*params != '\0' && *params != ' ') {
            goto NEXT_HOOK;
        }
        if (*params == ' ') {
            params++;
        }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference);

        // push parameter
        lua_pushstring(L, params);

        // call the callback
        if (0 != lua_pcall(L, 1, 1, 0)) {
            LOG_LUA("Failed to call the chat command callback: %s, %s", command, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }

        // output the return value
        bool returnValue = smlua_to_boolean(L, -1);
        lua_pop(L, 1);

        if (!gSmLuaConvertSuccess) { return false; }

        return returnValue;

NEXT_HOOK:;
    }

    return false;
}

void smlua_display_chat_commands(void) {
    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        char msg[256] = { 0 };
        snprintf(msg, 256, "/%s %s", hook->command, hook->description);
        djui_chat_message_create(msg);
    }
}

  //////////////////////////////
 // hooked sync table change //
//////////////////////////////


int smlua_hook_on_sync_table_change(lua_State* L) {
    LUA_STACK_CHECK_BEGIN();
    if (L == NULL) { return 0; }
    if(!smlua_functions_valid_param_count(L, 4)) { return 0; }

    int syncTableIndex = 1;
    int keyIndex = 2;
    int tagIndex = 3;
    int funcIndex = 4;

    if (lua_type(L, syncTableIndex) != LUA_TTABLE) {
        LOG_LUA("Tried to attach a non-table to hook_on_sync_table_change: %d", lua_type(L, syncTableIndex));
        smlua_logline();
        return 0;
    }

    if (lua_type(L, funcIndex) != LUA_TFUNCTION) {
        LOG_LUA("Tried to attach a non-function to hook_on_sync_table_change: %d", lua_type(L, funcIndex));
        smlua_logline();
        return 0;
    }

    // set hook's table
    lua_newtable(L);
    int valTableIndex = lua_gettop(L);

    lua_pushstring(L, "_func");
    lua_pushvalue(L, funcIndex);
    lua_settable(L, valTableIndex);

    lua_pushstring(L, "_tag");
    lua_pushvalue(L, tagIndex);
    lua_settable(L, valTableIndex);

    // get _hook_on_changed
    lua_pushstring(L, "_hook_on_changed");
    lua_rawget(L, syncTableIndex);
    int hookOnChangedIndex = lua_gettop(L);

    // attach
    lua_pushvalue(L, keyIndex);
    lua_pushvalue(L, valTableIndex);
    lua_settable(L, hookOnChangedIndex);

    // clean up
    lua_remove(L, hookOnChangedIndex);
    lua_remove(L, valTableIndex);

    LUA_STACK_CHECK_END();
    return 1;
}


  //////////
 // misc //
//////////

static void smlua_clear_hooks(void) {
    for (int i = 0; i < HOOK_MAX; i++) {
        for (int j = 0; j < sHookedEvents[i].count; j++) {
            sHookedEvents[i].reference[j] = 0;
        }
        sHookedEvents[i].count = 0;
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        sHookedMarioActions[i].action = 0;
        sHookedMarioActions[i].reference = 0;
    }
    sHookedMarioActionsCount = 0;

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        if (sHookedChatCommands[i].command != NULL) { free(sHookedChatCommands[i].command); }
        sHookedChatCommands[i].command = NULL;

        if (sHookedChatCommands[i].description != NULL) { free(sHookedChatCommands[i].description); }
        sHookedChatCommands[i].description = NULL;

        sHookedChatCommands[i].reference = 0;
    }
    sHookedChatCommandsCount = 0;
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);
    smlua_bind_function(L, "hook_chat_command", smlua_hook_chat_command);
    smlua_bind_function(L, "hook_on_sync_table_change", smlua_hook_on_sync_table_change);
}
