#include "smlua.h"
#include "src/game/object_list_processor.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/crash_handler.h"

#define MAX_HOOKED_REFERENCES 64
#define LUA_BEHAVIOR_FLAG (1 << 15)

static u64* sBehaviorOffset = &gPcDebug.bhvOffset;

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    int count;
    struct ModListEntry* entry;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

static int smlua_call_hook(lua_State* L, int nargs, int nresults, int errfunc, struct ModListEntry* activeEntry) {
    struct ModListEntry* prev = gLuaActiveEntry;
    gLuaActiveEntry = activeEntry;
    int rc = lua_pcall(L, nargs, nresults, errfunc);
    gLuaActiveEntry = prev;
    return rc;
}

int smlua_hook_event(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

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
    hook->entry = gLuaActiveEntry;

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
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->entry)) {
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
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->entry)) {
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
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->entry)) {
            LOG_LUA("Failed to call the callback: %u, %s", hookType, lua_tostring(L, -1));
            smlua_logline();
            continue;
        }
    }
}

void smlua_call_event_hooks_interact_params(enum LuaHookedEventType hookType, struct MarioState* m, struct Object* obj, u32 interactType, bool interactValue) {
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

        // push object
        smlua_push_object(L, LOT_OBJECT, obj);

        // push interact type
        lua_pushinteger(L, interactType);

        // push interact value
        lua_pushboolean(L, interactValue);

        // call the callback
        if (0 != smlua_call_hook(L, 4, 0, 0, hook->entry)) {
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
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->entry)) {
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
    u32 interactionType;
    int reference;
    struct ModListEntry* entry;
};

#define MAX_HOOKED_ACTIONS 128

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;

int smlua_hook_mario_action(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_range(L, 2, 3)) { return 0; }

    if (gLuaLoadingEntry == NULL) {
        LOG_LUA("hook_mario_action() can only be called on load.");
        return 0;
    }

    int paramCount = lua_gettop(L);

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

    lua_pushvalue(L, 2);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);

    if (ref == -1) {
        LOG_LUA("Hook Action: %lld tried to hook undefined function", action);
        smlua_logline();
        return 0;
    }

    lua_Integer interactionType = 0;
    if (paramCount >= 3) {
        interactionType = smlua_to_integer(L, 3);
        if (interactionType == 0 || !gSmLuaConvertSuccess) {
            LOG_LUA("Hook Action: tried to hook invalid interactionType: %lld, %u", interactionType, gSmLuaConvertSuccess);
            smlua_logline();
            return 0;
        }
    }

    struct LuaHookedMarioAction* hooked = &sHookedMarioActions[sHookedMarioActionsCount];
    hooked->action = action;
    hooked->interactionType = interactionType;
    hooked->reference = ref;
    hooked->entry = gLuaActiveEntry;
    if (!gSmLuaConvertSuccess) { return 0; }

    sHookedMarioActionsCount++;
    return 1;
}

bool smlua_call_action_hook(struct MarioState* m, s32* returnValue) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hook = &sHookedMarioActions[i];
        if (hook->action == m->action) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference);

            // push mario state
            lua_getglobal(L, "gMarioStates");
            lua_pushinteger(L, m->playerIndex);
            lua_gettable(L, -2);
            lua_remove(L, -2);

            // call the callback
            if (0 != smlua_call_hook(L, 1, 1, 0, hook->entry)) {
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

u32 smlua_get_action_interaction_type(struct MarioState* m) {
    u32 interactionType = 0;
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        if (sHookedMarioActions[i].action == m->action) {
            interactionType |= sHookedMarioActions[i].interactionType;
        }
    }
    return interactionType;
}

  //////////////////////
 // hooked behaviors //
//////////////////////

struct LuaHookedBehavior {
    u32 behaviorId;
    u32 overrideId;
    BehaviorScript behavior[2];
    const BehaviorScript* originalBehavior;
    int initReference;
    int loopReference;
    bool replace;
    struct ModListEntry* entry;
};

#define MAX_HOOKED_BEHAVIORS 256

static struct LuaHookedBehavior sHookedBehaviors[MAX_HOOKED_BEHAVIORS] = { 0 };
static int sHookedBehaviorsCount = 0;

const BehaviorScript* smlua_override_behavior(const BehaviorScript* behavior) {
    lua_State* L = gLuaState;
    if (L == NULL) { return behavior; }

    enum BehaviorId id = get_id_from_behavior(behavior);
    const BehaviorScript* luaBehavior = get_lua_behavior_from_id(id, false);
    if (luaBehavior != NULL) { return luaBehavior; }
    return behavior + *sBehaviorOffset;
}

const BehaviorScript* get_lua_behavior_from_id(enum BehaviorId id, bool returnOriginal) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];
        if (hooked->behaviorId != id && hooked->overrideId != id) { continue; }
        if (returnOriginal && !hooked->replace) { return hooked->originalBehavior; }
        return hooked->behavior;
    }
    return NULL;
}

int smlua_hook_behavior(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 5)) { return 0; }

    if (gLuaLoadingEntry == NULL) {
        LOG_LUA("hook_behavior() can only be called on load.");
        return 0;
    }

    if (sHookedBehaviorsCount >= MAX_HOOKED_BEHAVIORS) {
        LOG_LUA("Hooked behaviors exceeded maximum references!");
        smlua_logline();
        return 0;
    }

    bool noOverrideId = (lua_type(L, 1) == LUA_TNIL);
    gSmLuaConvertSuccess = true;
    lua_Integer overrideBehaviorId = noOverrideId ? 0xFFFFFF : smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Hook behavior: tried to override invalid behavior: %lld, %u", overrideBehaviorId, gSmLuaConvertSuccess);
        smlua_logline();
        return 0;
    }

    lua_Integer objectList = smlua_to_integer(L, 2);
    if (objectList <= 0 || objectList >= NUM_OBJ_LISTS || !gSmLuaConvertSuccess) {
        LOG_LUA("Hook behavior: tried use invalid object list: %lld, %u", objectList, gSmLuaConvertSuccess);
        smlua_logline();
        return 0;
    }

    bool replaceBehavior = smlua_to_boolean(L, 3);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Hook behavior: could not parse replaceBehavior");
        smlua_logline();
        return 0;
    }
    const BehaviorScript* originalBehavior = noOverrideId ? NULL : get_behavior_from_id(overrideBehaviorId);
    if (originalBehavior == NULL) {
        replaceBehavior = true;
    }

    int initReference = 0;
    int initReferenceType = lua_type(L, 4);
    if (initReferenceType == LUA_TNIL) {
        // nothing
    } else if (initReferenceType == LUA_TFUNCTION) {
        // get reference
        lua_pushvalue(L, 4);
        initReference = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        LOG_LUA("Hook behavior: tried to reference non-function for init");
        smlua_logline();
        return 0;
    }

    int loopReference = 0;
    int loopReferenceType = lua_type(L, 5);
    if (loopReferenceType == LUA_TNIL) {
        // nothing
    } else if (loopReferenceType == LUA_TFUNCTION) {
        // get reference
        lua_pushvalue(L, 5);
        loopReference = luaL_ref(L, LUA_REGISTRYINDEX);
    } else {
        LOG_LUA("Hook behavior: tried to reference non-function for loop");
        smlua_logline();
        return 0;
    }

    struct LuaHookedBehavior* hooked = &sHookedBehaviors[sHookedBehaviorsCount];
    u16 customBehaviorId = (sHookedBehaviorsCount & 0xFFFF) | LUA_BEHAVIOR_FLAG;
    hooked->behaviorId = customBehaviorId;
    hooked->overrideId = noOverrideId ? customBehaviorId : overrideBehaviorId;
    hooked->behavior[0] = (((unsigned int) (((unsigned int)(0x00) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(objectList) & ((0x01 << (8)) - 1)) << (16)))); // gross. this is BEGIN(objectList)
    hooked->behavior[1] = (((unsigned int) (((unsigned int)(0x39) & ((0x01 << (8)) - 1)) << (24))) | ((unsigned int) (((unsigned int)(customBehaviorId) & ((0x01 << (16)) - 1)) << (0)))); // gross. this is ID(customBehaviorId)
    hooked->originalBehavior = originalBehavior ? originalBehavior : hooked->behavior;
    hooked->initReference = initReference;
    hooked->loopReference = loopReference;
    hooked->replace = replaceBehavior;
    hooked->entry = gLuaActiveEntry;

    sHookedBehaviorsCount++;

    // return behavior ID
    lua_pushinteger(L, customBehaviorId);

    return 1;
}

bool smlua_call_behavior_hook(const BehaviorScript** behavior, struct Object* object, bool before) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }
    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];

        // find behavior
        if (object->behavior != hooked->behavior) {
            continue;
        }

        // figure out whether to run before or after
        if (before && !hooked->replace) {
            return false;
        }
        if (!before && hooked->replace) {
            return false;
        }

        // retrieve and remember first run
        bool firstRun = (object->curBhvCommand == hooked->originalBehavior) || (object->curBhvCommand == hooked->behavior);
        if (firstRun && hooked->replace) { *behavior = &hooked->behavior[1]; }

        // get function and null check it
        int reference = firstRun ? hooked->initReference : hooked->loopReference;
        if (reference == 0) {
            return true;
        }

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, reference);

        // push object
        smlua_push_object(L, LOT_OBJECT, object);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hooked->entry)) {
            LOG_LUA("Failed to call the behavior callback: %u, %s", hooked->behaviorId, lua_tostring(L, -1));
            smlua_logline();
            return true;
        }

        return hooked->replace;
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
    struct ModListEntry* entry;
};

#define MAX_HOOKED_CHAT_COMMANDS 64

static struct LuaHookedChatCommand sHookedChatCommands[MAX_HOOKED_CHAT_COMMANDS] = { 0 };
static int sHookedChatCommandsCount = 0;

int smlua_hook_chat_command(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    if (gLuaLoadingEntry == NULL) {
        LOG_LUA("hook_chat_command() can only be called on load.");
        return 0;
    }

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
    hooked->entry = gLuaActiveEntry;
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
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->entry)) {
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

    if (gLuaLoadingEntry == NULL) {
        LOG_LUA("hook_on_sync_table_change() can only be called on load.");
        return 0;
    }

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
        sHookedEvents[i].entry = NULL;
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        sHookedMarioActions[i].action = 0;
        sHookedMarioActions[i].reference = 0;
        sHookedMarioActions[i].entry = NULL;
    }
    sHookedMarioActionsCount = 0;

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        if (sHookedChatCommands[i].command != NULL) { free(sHookedChatCommands[i].command); }
        sHookedChatCommands[i].command = NULL;

        if (sHookedChatCommands[i].description != NULL) { free(sHookedChatCommands[i].description); }
        sHookedChatCommands[i].description = NULL;

        sHookedChatCommands[i].reference = 0;
        sHookedChatCommands[i].entry = NULL;
    }
    sHookedChatCommandsCount = 0;

    for (int i = 0; i < sHookedBehaviorsCount; i++) {
        struct LuaHookedBehavior* hooked = &sHookedBehaviors[i];
        hooked->behaviorId = 0;
        hooked->behavior[0] = 0;
        hooked->behavior[1] = 0;
        hooked->originalBehavior = NULL;
        hooked->initReference = 0;
        hooked->loopReference = 0;
        hooked->replace = false;
        hooked->entry = NULL;
    }
    sHookedBehaviorsCount = 0;
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);
    smlua_bind_function(L, "hook_chat_command", smlua_hook_chat_command);
    smlua_bind_function(L, "hook_on_sync_table_change", smlua_hook_on_sync_table_change);
    smlua_bind_function(L, "hook_behavior", smlua_hook_behavior);
}
