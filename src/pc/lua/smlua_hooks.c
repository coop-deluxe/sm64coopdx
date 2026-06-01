#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "smlua.h"
#include "sm64.h"
#include "behavior_commands.h"
#include "pc/mods/mod.h"
#include "game/object_list_processor.h"
#include "game/object_helpers.h"
#include "pc/djui/djui_chat_message.h"
#include "pc/crash_handler.h"
#include "game/hud.h"
#include "game/level_update.h"
#include "pc/debug_context.h"
#include "pc/network/network.h"
#include "pc/network/network_player.h"
#include "pc/network/socket/socket.h"
#include "pc/chat_commands.h"
#include "pc/pc_main.h"
#include "pc/djui/djui_lua_profiler.h"
#include "pc/djui/djui_panel.h"
#include "pc/configfile.h"
#include "pc/utils/misc.h"
#include "pc/lua/utils/smlua_model_utils.h"

#include "../mods/mods.h"
#include "game/print.h"
#include "gfx_dimensions.h"

extern void smlua_new_vec3f(Vec3f src);
extern void smlua_get_vec3f(Vec3f dest, int index);

#define MAX_HOOKED_REFERENCES 64

u64* gBehaviorOffset = &gPcDebug.bhvOffset;

struct LuaHookedEvent {
    int reference[MAX_HOOKED_REFERENCES];
    struct Mod* mod[MAX_HOOKED_REFERENCES];
    struct ModFile* modFile[MAX_HOOKED_REFERENCES];
    int count;
};

static struct LuaHookedEvent sHookedEvents[HOOK_MAX] = { 0 };

static const char* sLuaHookedEventTypeName[] = {
#define SMLUA_EVENT_HOOK(hookEventType, ...) [hookEventType] = #hookEventType,
#include "smlua_hook_events.inl"
#undef SMLUA_EVENT_HOOK
    [HOOK_MAX] = "HOOK_MAX"
};

int smlua_call_hook(lua_State* L, int nargs, int nresults, int errfunc, struct Mod* activeMod, struct ModFile* activeModFile) {
    if (!gGameInited) { return 0; } // Don't call hooks while the game is booting

    struct Mod* prevActiveMod = gLuaActiveMod;
    struct ModFile* prevActiveModFile = gLuaActiveModFile;

    gLuaActiveMod = activeMod;
    gLuaActiveModFile = activeModFile;
    gLuaLastHookMod = activeMod;
    gPcDebug.lastModRun = activeMod;

    lua_profiler_start_counter(activeMod);

    CTX_BEGIN(CTX_HOOK);
    int rc = smlua_pcall(L, nargs, nresults, errfunc);
    CTX_END(CTX_HOOK);

    lua_profiler_stop_counter(activeMod);

    gLuaActiveMod = prevActiveMod;
    gLuaActiveModFile = prevActiveModFile;
    return rc;
}

int smlua_hook_event(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    u16 hookType = smlua_to_integer(L, -2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Invalid hook type given to hook_event(): %d", hookType);
        return 0;
    }

    if (hookType >= HOOK_MAX) {
        LOG_LUA_LINE("Hook Type: %d exceeds max!", hookType);
        return 0;
    }

    struct LuaHookedEvent* hook = &sHookedEvents[hookType];
    if (hook->count >= MAX_HOOKED_REFERENCES) {
        LOG_LUA_LINE("Hook Type: %s exceeded maximum references!", sLuaHookedEventTypeName[hookType]);
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Tried to hook undefined function to '%s'", sLuaHookedEventTypeName[hookType]);
        return 0;
    }

    hook->reference[hook->count] = ref;
    hook->mod[hook->count] = gLuaActiveMod;
    hook->modFile[hook->count] = gLuaActiveModFile;
    hook->count++;

    return 1;
}

  ///////////////////
 // hooked events //
///////////////////

#include "smlua_hook_events_autogen.inl"

static bool smlua_call_event_hooks_on_hud_render(void (*resetFunc)(void), bool renderBehind) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    if (resetFunc) { resetFunc(); }

    const enum LuaHookedEventType renderHudHookTypes[] = {
        HOOK_ON_HUD_RENDER_BEHIND,
        HOOK_ON_HUD_RENDER,
    };
    for (s32 k = renderBehind ? 0 : 1; k != 2; ++k) {
        enum LuaHookedEventType hookType = renderHudHookTypes[k];
        struct LuaHookedEvent *hook = &sHookedEvents[hookType];
        for (int i = 0; i < hook->count; i++) {

            // support deprecated render behind hud
            if (hookType == HOOK_ON_HUD_RENDER && hook->mod[i]->renderBehindHud != renderBehind) {
                continue;
            }

            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

            // call the callback
            if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
                LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[hookType]);
            } else {
                hookResult = true;
            }

            if (resetFunc) { resetFunc(); }
        }
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_HUD_RENDER(void (*resetFunc)(void)) {
    return smlua_call_event_hooks_on_hud_render(resetFunc, false);
}

bool smlua_call_event_hooks_HOOK_ON_HUD_RENDER_BEHIND(void (*resetFunc)(void)) {
    return smlua_call_event_hooks_on_hud_render(resetFunc, true);
}

bool smlua_call_event_hooks_HOOK_ON_NAMETAGS_RENDER(s32 playerIndex, Vec3f pos, const char **playerNameOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_NAMETAGS_RENDER];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push playerIndex
        lua_pushinteger(L, playerIndex);

        // push pos
        smlua_new_vec3f(pos);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_NAMETAGS_RENDER]);
            continue;
        }

        // return playerNameOverride
        if (lua_type(L, -1) == LUA_TSTRING) {
            *playerNameOverride = smlua_to_string(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        // if it's a table, override name, pos or both
        if (lua_type(L, -1) == LUA_TTABLE) {
            bool override = false;

            // name
            lua_getfield(L, -1, "name");
            if (lua_type(L, -1) == LUA_TSTRING) {
                *playerNameOverride = smlua_to_string(L, -1);
                override = true;
            }
            lua_pop(L, 1);

            // pos
            lua_getfield(L, -1, "pos");
            if (lua_type(L, -1) == LUA_TTABLE) {
                smlua_get_vec3f(pos, -1);
                override = true;
            }
            lua_pop(L, 1);

            lua_settop(L, prevTop);
            if (override) {
                return true;
            }
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_WALL_COLLISION(f32 posX, f32 posY, f32 posZ, struct WallCollisionData *colData, s32 *numCollisions) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_WALL_COLLISION];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push posX, posY, posZ
        lua_pushnumber(L, posX);
        lua_pushnumber(L, posY);
        lua_pushnumber(L, posZ);

        // push colData
        smlua_push_object(L, LOT_WALLCOLLISIONDATA, colData, NULL);

        // call the callback (4 args, 1 result)
        if (0 != smlua_call_hook(L, 4, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_WALL_COLLISION]);
            lua_settop(L, prevTop);
            continue;
        }

        // return number overrides numCollisions
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *numCollisions = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            sInHook = false;
            return true;
        }

        lua_settop(L, prevTop);
    }
    sInHook = false;
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_CEIL(f32 posX, f32 posY, f32 posZ, struct Surface **pceil, f32 *height) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_CEIL];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push posX, posY, posZ
        lua_pushnumber(L, posX);
        lua_pushnumber(L, posY);
        lua_pushnumber(L, posZ);

        // push current ceil surface (or nil)
        if (pceil && *pceil) {
            smlua_push_object(L, LOT_SURFACE, *pceil, NULL);
        } else {
            lua_pushnil(L);
        }

        // push current height
        lua_pushnumber(L, *height);

        // call the callback (5 args, 2 results)
        if (0 != smlua_call_hook(L, 5, 2, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_CEIL]);
            lua_settop(L, prevTop);
            continue;
        }

        bool override = false;

        // first return value: height (number)
        if (lua_type(L, -2) == LUA_TNUMBER) {
            *height = smlua_to_number(L, -2);
            override = true;
        }

        // second return value: surface (userdata)
        if (lua_type(L, -1) == LUA_TUSERDATA) {
            struct Surface *surface = (struct Surface *)smlua_to_cobject(L, -1, LOT_SURFACE);
            if (surface && pceil) {
                *pceil = surface;
                override = true;
            }
        }

        lua_settop(L, prevTop);
        if (override) { sInHook = false; return true; }
    }
    sInHook = false;
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_FLOOR(f32 posX, f32 posY, f32 posZ, struct Surface **pfloor, f32 *height) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_FLOOR];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push posX, posY, posZ
        lua_pushnumber(L, posX);
        lua_pushnumber(L, posY);
        lua_pushnumber(L, posZ);

        // push current floor surface (or nil)
        if (pfloor && *pfloor) {
            smlua_push_object(L, LOT_SURFACE, *pfloor, NULL);
        } else {
            lua_pushnil(L);
        }

        // push current height
        lua_pushnumber(L, *height);

        // call the callback (5 args, 2 results)
        if (0 != smlua_call_hook(L, 5, 2, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_FLOOR]);
            lua_settop(L, prevTop);
            continue;
        }

        bool override = false;

        // first return value: height (number)
        if (lua_type(L, -2) == LUA_TNUMBER) {
            *height = smlua_to_number(L, -2);
            override = true;
        }

        // second return value: surface (userdata)
        if (lua_type(L, -1) == LUA_TUSERDATA) {
            struct Surface *surface = (struct Surface *)smlua_to_cobject(L, -1, LOT_SURFACE);
            if (surface && pfloor) {
                *pfloor = surface;
                override = true;
            }
        }

        lua_settop(L, prevTop);
        if (override) { sInHook = false; return true; }
    }
    sInHook = false;
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_SURFACE_ON_RAY(Vec3f orig, Vec3f dir, struct Surface **hit_surface, Vec3f hit_pos) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_SURFACE_ON_RAY];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push orig, dir
        smlua_new_vec3f(orig);
        smlua_new_vec3f(dir);

        // push hit_surface (or nil)
        if (hit_surface && *hit_surface) {
            smlua_push_object(L, LOT_SURFACE, *hit_surface, NULL);
        } else {
            lua_pushnil(L);
        }

        // push hit_pos
        smlua_new_vec3f(hit_pos);

        // call the callback (4 args, 2 results)
        if (0 != smlua_call_hook(L, 4, 2, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_SURFACE_ON_RAY]);
            lua_settop(L, prevTop);
            continue;
        }

        bool override = false;

        // first return value: surface (userdata)
        if (lua_type(L, -2) == LUA_TUSERDATA) {
            struct Surface *surface = (struct Surface *)smlua_to_cobject(L, -2, LOT_SURFACE);
            if (surface && hit_surface) {
                *hit_surface = surface;
                override = true;
            }
        }

        // second return value: hitPos (table {x, y, z})
        if (lua_type(L, -1) == LUA_TTABLE) {
            smlua_get_vec3f(hit_pos, -1);
            override = true;
        }

        lua_settop(L, prevTop);
        if (override) { sInHook = false; return true; }
    }
    sInHook = false;
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_WATER_LEVEL(f32 x, f32 z, f32 *waterLevel) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_WATER_LEVEL];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push x, z
        lua_pushnumber(L, x);
        lua_pushnumber(L, z);

        // push current water level
        lua_pushnumber(L, *waterLevel);

        // call the callback (3 args, 1 result)
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_WATER_LEVEL]);
            lua_settop(L, prevTop);
            continue;
        }

        // return number overrides waterLevel
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *waterLevel = smlua_to_number(L, -1);
            lua_settop(L, prevTop);
            sInHook = false;
            return true;
        }

        lua_settop(L, prevTop);
    }
    sInHook = false;
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_FIND_POISON_GAS_LEVEL(f32 x, f32 z, f32 *gasLevel) {
    static bool sInHook = false;
    lua_State *L = gLuaState;
    if (L == NULL || sInHook) { return false; }
    sInHook = true;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_FIND_POISON_GAS_LEVEL];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push x, z
        lua_pushnumber(L, x);
        lua_pushnumber(L, z);

        // push current gas level
        lua_pushnumber(L, *gasLevel);

        // call the callback (3 args, 1 result)
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_FIND_POISON_GAS_LEVEL]);
            lua_settop(L, prevTop);
            continue;
        }

        // return number overrides gasLevel
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *gasLevel = smlua_to_number(L, -1);
            lua_settop(L, prevTop);
            sInHook = false;
            return true;
        }

        lua_settop(L, prevTop);
    }
    sInHook = false;
    return false;
}

  ////////////////////
 // hooked actions //
////////////////////

struct LuaHookedMarioAction {
    u32 action;
    u32 interactionType;
    int actionHookRefs[ACTION_HOOK_MAX];
    struct Mod* mod;
    struct ModFile* modFile;
};

#define MAX_HOOKED_ACTIONS (ACT_NUM_GROUPS * ACT_NUM_ACTIONS_PER_GROUP)

static struct LuaHookedMarioAction sHookedMarioActions[MAX_HOOKED_ACTIONS] = { 0 };
static int sHookedMarioActionsCount = 0;
u32 gLuaMarioActionIndex[ACT_NUM_GROUPS] = { 0 };

int smlua_hook_mario_action(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_range(L, 2, 3)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_mario_action() can only be called on load.");
        return 0;
    }

    int paramCount = lua_gettop(L);

    if (sHookedMarioActionsCount >= MAX_HOOKED_ACTIONS) {
        LOG_LUA_LINE("Hooked mario actions exceeded maximum references!");
        return 0;
    }

    lua_Integer action = smlua_to_integer(L, 1);
    if (action == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook Action: tried to hook invalid action: %lld, %u", action, gSmLuaConvertSuccess);
        return 0;
    }

    int secondParamType = lua_type(L, 2);
    bool oldApi = secondParamType == LUA_TFUNCTION;

    if (!oldApi && secondParamType != LUA_TTABLE) {
        LOG_LUA_LINE("smlua_hook_mario_action received improper type '%s'", luaL_typename(L, 2));
        return 0;
    }

    lua_Integer interactionType = 0;
    if (paramCount >= 3) {
        interactionType = smlua_to_integer(L, 3);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Hook Action: tried to hook invalid interactionType: %lld, %u", interactionType, gSmLuaConvertSuccess);
            return 0;
        }
    }

    struct LuaHookedMarioAction* hooked = &sHookedMarioActions[sHookedMarioActionsCount];

    // Support calling the function with just one function corresponding to the "every frame" hook instead of a full
    // table with all hooks
    if (oldApi) {
        for (int i = 0; i < ACTION_HOOK_MAX; i++) {
            hooked->actionHookRefs[i] = LUA_NOREF;
        }

        lua_pushvalue(L, 2);
        int ref = luaL_ref(L, LUA_REGISTRYINDEX);

        if (ref == -1) {
            LOG_LUA_LINE("Hook Action: %lld tried to hook undefined function", action);
            return 0;
        }

        hooked->actionHookRefs[ACTION_HOOK_EVERY_FRAME] = ref;
    }
    else {
        for (int i = 0; i < ACTION_HOOK_MAX; i++) {
            lua_pushstring(L, LuaActionHookTypeArgName[i]);

            if (lua_gettable(L, 2) == LUA_TNIL) {
                hooked->actionHookRefs[i] = LUA_NOREF;
            } else {
                int ref = luaL_ref(L, LUA_REGISTRYINDEX);

                if (ref == -1) {
                    LOG_LUA_LINE("Hook Action: %lld tried to hook undefined function", action);
                    return 0;
                }

                hooked->actionHookRefs[i] = ref;
            }
        }
    }

    hooked->action = action;
    hooked->interactionType = interactionType;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    sHookedMarioActionsCount++;
    return 1;
}

bool smlua_call_action_hook(enum LuaActionHookType hookType, struct MarioState* m, s32* cancel) {
    lua_State* L = gLuaState;
    if (L == NULL) { return false; }

    //TODO GAG: Set up things such that O(n) check isn't performed on every action hook? Maybe in MarioState?
    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hook = &sHookedMarioActions[i];
        if (hook->action == m->action && hook->actionHookRefs[hookType] != LUA_NOREF) {
            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, hook->actionHookRefs[hookType]);

            // push mario state
            lua_getglobal(L, "gMarioStates");
            lua_pushinteger(L, m->playerIndex);
            lua_gettable(L, -2);
            lua_remove(L, -2);

            // call the callback
            if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod, hook->modFile)) {
                LOG_LUA("Failed to call the action callback: '%08X'", m->action);
                continue;
            }

            // output the return value
            // special return values:
            // - returning -1 allows to continue the execution, useful when overriding vanilla actions
            bool stopActionHook = true;
            *cancel = FALSE;

            switch (lua_type(L, -1)) {
                case LUA_TBOOLEAN: {
                    *cancel = smlua_to_boolean(L, -1) ? TRUE : FALSE;
                } break;

                case LUA_TNUMBER: {
                    s32 returnValue = (s32) smlua_to_integer(L, -1);
                    if (returnValue > 0) {
                        *cancel = TRUE;
                    } else if (returnValue == 0) {
                        *cancel = FALSE;
                    } else if (returnValue == ACTION_HOOK_CONTINUE_EXECUTION) {
                        stopActionHook = false;
                    } else {
                        LOG_LUA("Invalid return value when calling the action callback: '%08X' returned %d", m->action, returnValue);
                    }
                } break;
            }
            lua_pop(L, 1);

            if (stopActionHook) {
                return true;
            }
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

struct GrowingArray *gHookedBehaviors = NULL;

static struct LuaHookedBehavior *smlua_find_hooked_behavior(enum BehaviorId id) {
    growing_array_for_each_(gHookedBehaviors, struct LuaHookedBehavior, hooked) {
        if (hooked->behaviorId == id || hooked->customId == id) {
            return hooked;
        }
    }
    return NULL;
}

static struct LuaHookedBehavior *smlua_create_hooked_behavior() {
    struct LuaHookedBehavior *hooked = growing_array_alloc(gHookedBehaviors, sizeof(struct LuaHookedBehavior));
    hooked->bhvNames = growing_array_init(NULL, 4, malloc, free);
    hooked->initCallbacks = growing_array_init(NULL, 4, malloc, free);
    hooked->loopCallbacks = growing_array_init(NULL, 4, malloc, free);
    return hooked;
}

// Replace the original behavior with a custom behavior if it exists.
const BehaviorScript *smlua_override_behavior(const BehaviorScript *behavior) {
    enum BehaviorId id = get_id_from_behavior(behavior);
    struct LuaHookedBehavior *hooked = smlua_find_hooked_behavior(id);
    if (hooked) {
        return hooked->script;
    }
    return behavior + *gBehaviorOffset;
}

const BehaviorScript *smlua_get_original_behavior_from_id(enum BehaviorId id) {
    struct LuaHookedBehavior *hooked = smlua_find_hooked_behavior(id);
    if (hooked) {
        if (hooked->type == LUA_BEHAVIOR_TYPE_CALLBACKS) {
            const BehaviorScript *script = get_vanilla_behavior_from_id(id);
            if (script) {
                return script;
            }
        }
        return hooked->script;
    }
    return NULL;
}

// Return the first behavior command that will be executed by a freshly created object.
const BehaviorScript *smlua_get_behavior_command(const BehaviorScript *behavior) {
    enum BehaviorId id = get_id_from_behavior(behavior);
    struct LuaHookedBehavior *hooked = smlua_find_hooked_behavior(id);

    if (hooked) {

        // Lua and custom behaviors only
        if (hooked->type > LUA_BEHAVIOR_TYPE_CALLBACKS) {
            return hooked->script;
        }

        // Try to find the vanilla behavior script
        const BehaviorScript *vanillaScript = get_vanilla_behavior_from_id(hooked->behaviorId);
        if (vanillaScript) {
            return vanillaScript;
        }
    }
    return behavior;
}

const char* smlua_get_behavior_name_from_id(enum BehaviorId id) {
    struct LuaHookedBehavior *hooked = smlua_find_hooked_behavior(id);
    if (hooked) {
        return (const char *) hooked->bhvNames->buffer[hooked->bhvNames->count - 1]; // return the last name registered
    }
    return NULL;
}

int smlua_hook_custom_bhv(BehaviorScript *bhvScript, const char *bhvName) {
    enum BehaviorId id = get_id_from_behavior(bhvScript);

    // Can't hook Mario
    if (id == id_bhvMario) {
        LOG_LUA_LINE("Cannot hook Mario's behavior. Use HOOK_MARIO_UPDATE and HOOK_BEFORE_MARIO_UPDATE.");
        return 0;
    }

    // Do not allow custom behaviors to hook non-vanilla ids
    bool isVanillaId = id < id_bhv_max_count;
    struct LuaHookedBehavior *hooked = isVanillaId ? smlua_find_hooked_behavior(id) : NULL;

    // Create a new hooked behavior
    if (!hooked) {
        if (gHookedBehaviors->count >= MAX_HOOKED_BEHAVIORS) {
            LOG_ERROR("Hooked behaviors exceeded maximum references!");
            return 0;
        }

        enum BehaviorId customId = LUA_BEHAVIOR_START + gHookedBehaviors->count;

        hooked = smlua_create_hooked_behavior();
        hooked->behaviorId = isVanillaId ? id : customId;
        hooked->customId = customId;
        hooked->type = LUA_BEHAVIOR_TYPE_CUSTOM;
        hooked->script = bhvScript;
        hooked->script[1] = (BehaviorScript) ID(customId);

    } else {

        // Behavior script can be replaced as long as it's not a custom behavior
        if (hooked->type != LUA_BEHAVIOR_TYPE_CUSTOM) {
            free(hooked->script);
            hooked->type = LUA_BEHAVIOR_TYPE_CUSTOM;
            hooked->script = bhvScript;
            hooked->script[1] = (BehaviorScript) ID(hooked->customId);
        } else {
            LOG_LUA_WARNING("Hook behavior: the behavior script for the behavior %s is custom and cannot be changed", (const char *) hooked->bhvNames->buffer[hooked->bhvNames->count - 1]);
        }
    }

    // Add a name to that behavior
    char *name = growing_array_alloc(hooked->bhvNames, strlen(bhvName) + 1);
    strcpy(name, bhvName);

    // We want to push the behavior into the global LUA state. So mods can access it.
    // It's also used for some things that would normally access a LUA behavior instead.
    lua_State *L = gLuaState;
    if (L != NULL) {
        lua_pushinteger(L, hooked->customId);
        lua_setglobal(L, bhvName);
        LOG_INFO("Registered custom behavior for behavior id 0x%04hX (custom id: 0x%04hX, custom name: %s)", hooked->behaviorId, hooked->customId, bhvName);
    }

    return 1;
}

int smlua_hook_behavior(lua_State *L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_range(L, 5, 6)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_behavior() can only be called on load.");
        return 0;
    }

    int paramCount = lua_gettop(L);

    // Get behavior id
    enum BehaviorId id = LUA_BEHAVIOR_NEW_ID;
    if (lua_type(L, 1) != LUA_TNIL) {
        gSmLuaConvertSuccess = true;
        id = (enum BehaviorId) (u16) smlua_to_integer(L, 1);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Hook behavior: tried to override invalid behavior id");
            return 0;
        }
    }

    // Can't hook Mario
    if (id == id_bhvMario) {
        LOG_LUA_LINE("Hook behavior: cannot hook Mario's behavior. Use HOOK_MARIO_UPDATE and HOOK_BEFORE_MARIO_UPDATE.");
        return 0;
    }

    // Get object list
    enum ObjectList objectList = (enum ObjectList) (u8) smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess || objectList >= NUM_OBJ_LISTS) {
        LOG_LUA_LINE("Hook behavior: tried use invalid object list: %d, %u", objectList, gSmLuaConvertSuccess);
        return 0;
    }

    // Check replace if it's a vanilla behavior hook
    bool replaceBehavior = true;
    bool isVanillaId = id < id_bhv_max_count;
    if (isVanillaId) {
        replaceBehavior = smlua_to_boolean(L, 3);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("Hook behavior: could not convert replaceBehavior to boolean");
            return 0;
        }
    }

    // Get init function
    int initReference = 0;
    int initReferenceType = lua_type(L, 4);
    switch (initReferenceType) {
        case LUA_TNIL: break;

        case LUA_TFUNCTION: {
            lua_pushvalue(L, 4);
            initReference = luaL_ref(L, LUA_REGISTRYINDEX);
        } break;

        default: {
            LOG_LUA_LINE("Hook behavior: invalid type passed for argument initFunction: '%s', should be '%s'", lua_typename(L, initReferenceType), lua_typename(L, LUA_TFUNCTION));
        } return 0;
    }

    // Get loop function
    int loopReference = 0;
    int loopReferenceType = lua_type(L, 5);
    switch (loopReferenceType) {
        case LUA_TNIL: break;

        case LUA_TFUNCTION: {
            lua_pushvalue(L, 5);
            loopReference = luaL_ref(L, LUA_REGISTRYINDEX);
        } break;

        default: {
            LOG_LUA_LINE("Hook behavior: invalid type passed for argument loopFunction: '%s', should be '%s'", lua_typename(L, loopReferenceType), lua_typename(L, LUA_TFUNCTION));
        } return 0;
    }

    // Get name
    const char *bhvName = NULL;
    if (paramCount >= 6) {
        int bhvNameType = lua_type(L, 6);
        switch (bhvNameType) {
            case LUA_TNIL: break;

            case LUA_TSTRING: {
                bhvName = smlua_to_string(L, 6);
                if (!bhvName || !gSmLuaConvertSuccess) {
                    LOG_LUA_LINE("Hook behavior: could not parse bhvName");
                    return 0;
                }
            } break;

            default: {
                LOG_LUA_LINE("Hook behavior: invalid type passed for argument bhvName: '%s', should be '%s'", lua_typename(L, bhvNameType), lua_typename(L, LUA_TSTRING));
            } return 0;
        }
    }

    // Get an existing hooked behavior or create a new one
    // Do not allow arbitrary non-vanilla ids to be hooked
    struct LuaHookedBehavior *hooked = NULL;
    if (id != LUA_BEHAVIOR_NEW_ID) {
        hooked = smlua_find_hooked_behavior(id);
        if (!hooked && !isVanillaId) {
            LOG_LUA_LINE("Hook behavior: behavior id %u is not valid, cannot hook non-existing non-vanilla behaviors", id);
            return 0;
        }
    }
    if (!hooked) {
        if (gHookedBehaviors->count >= MAX_HOOKED_BEHAVIORS) {
            LOG_ERROR("Hooked behaviors exceeded maximum references!");
            return 0;
        }

        enum BehaviorId customId = LUA_BEHAVIOR_START + gHookedBehaviors->count;

        hooked = smlua_create_hooked_behavior();
        hooked->behaviorId = id != LUA_BEHAVIOR_NEW_ID ? id : customId;
        hooked->customId = customId;
        hooked->type = replaceBehavior ? LUA_BEHAVIOR_TYPE_LUA : LUA_BEHAVIOR_TYPE_CALLBACKS;
        hooked->script = calloc(4, sizeof(BehaviorScript));
        hooked->script[0] = (BehaviorScript) BEGIN(objectList);
        hooked->script[1] = (BehaviorScript) ID(customId);
        hooked->script[2] = (BehaviorScript) BREAK();
        hooked->script[3] = (BehaviorScript) BREAK();

    } else {

        // Behavior script can be replaced as long as it's not a custom behavior
        if (replaceBehavior) {
            switch (hooked->type) {
                case LUA_BEHAVIOR_TYPE_CALLBACKS: {
                    hooked->type = LUA_BEHAVIOR_TYPE_LUA;
                    hooked->script[0] = (BehaviorScript) BEGIN(objectList); // Override object list
                } break;

                case LUA_BEHAVIOR_TYPE_LUA: {
                    // nothing to change
                } break;

                case LUA_BEHAVIOR_TYPE_CUSTOM: {
                    LOG_LUA_WARNING("Hook behavior: the behavior script for the behavior %s is custom and cannot be changed", (const char *) hooked->bhvNames->buffer[hooked->bhvNames->count - 1]);
                } break;
            }
        }

        // Warn user if trying to change the object list
        enum ObjectList hookedObjectList = get_object_list_from_behavior(hooked->script);
        if (hookedObjectList != objectList) {
            LOG_LUA_WARNING("Hook behavior: trying to change the object list of the existing hooked behavior %s: %d (should be %d)", (const char *) hooked->bhvNames->buffer[hooked->bhvNames->count - 1], objectList, hookedObjectList);
        }
    }

    // If not provided and the hooked behavior has no name yet, generate generic behavior name: bhv<ModName>Custom<Index>
    // - <ModName> is the mod name in CamelCase format, alphanumeric chars only
    // - <Index> is in 3-digit numeric format (from 001 to 999, no longer applies for index greater than 1000)
    // For example, the 4th unnamed behavior of the mod "my-great_MOD" will be named "bhvMyGreatMODCustom004"
    if (!bhvName && hooked->bhvNames->count == 0) {
        static char sGenericBhvName[MOD_NAME_MAX_LENGTH + 16];
        s32 i = 3;
        snprintf(sGenericBhvName, 4, "bhv");
        for (char caps = TRUE, *c = gLuaLoadingMod->name; *c && i < MOD_NAME_MAX_LENGTH + 3; ++c) {
            if ('0' <= *c && *c <= '9') {
                sGenericBhvName[i++] = *c;
                caps = TRUE;
            } else if ('A' <= *c && *c <= 'Z') {
                sGenericBhvName[i++] = *c;
                caps = FALSE;
            } else if ('a' <= *c && *c <= 'z') {
                sGenericBhvName[i++] = *c + (caps ? 'A' - 'a' : 0);
                caps = FALSE;
            } else {
                caps = TRUE;
            }
        }
        snprintf(sGenericBhvName + i, 12, "Custom%03u", (u32) (gLuaLoadingMod->customBehaviorIndex++) + 1);
        bhvName = sGenericBhvName;
    }

    // Add name
    if (bhvName) {
        char *name = growing_array_alloc(hooked->bhvNames, strlen(bhvName) + 1);
        strcpy(name, bhvName);
    }

    // Add init function
    if (initReference) {
        struct LuaHookedBehaviorCallback *callback = growing_array_alloc(hooked->initCallbacks, sizeof(struct LuaHookedBehaviorCallback));
        callback->ref = initReference;
        callback->mod = gLuaActiveMod;
        callback->modFile = gLuaActiveModFile;
    }

    // Add loop function
    if (loopReference) {
        struct LuaHookedBehaviorCallback *callback = growing_array_alloc(hooked->loopCallbacks, sizeof(struct LuaHookedBehaviorCallback));
        callback->ref = loopReference;
        callback->mod = gLuaActiveMod;
        callback->modFile = gLuaActiveModFile;
    }

    // We want to push the behavior into the global LUA state. So mods can access it.
    // It's also used for some things that would normally access a LUA behavior instead.
    if (bhvName) {
        lua_pushinteger(L, hooked->customId);
        lua_setglobal(L, bhvName);
    } else {
        bhvName = hooked->bhvNames->buffer[hooked->bhvNames->count - 1]; // log with last registered name
    }
    LOG_INFO("Registered Lua behavior for behavior id 0x%04hX (custom id: 0x%04hX, custom name: %s)", hooked->behaviorId, hooked->customId, bhvName);

    // return behavior ID
    lua_pushinteger(L, hooked->customId);

    return 1;
}

void smlua_call_behavior_hook(struct Object* object) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }

    enum BehaviorId id = get_id_from_behavior(object->behavior);
    struct LuaHookedBehavior *hooked = smlua_find_hooked_behavior(id);
    if (hooked) {

        // This works for two reasons:
        // - A behavior first command is always BEGIN(objList), so, after the first update, curBhvCommand will no longer be initBhvCommand
        // - object->curBhvCommand is not updated until the end of this function
        bool init = object->curBhvCommand == object->initBhvCommand;

        // Run callbacks one after the other
        struct GrowingArray *callbacks = init ? hooked->initCallbacks : hooked->loopCallbacks;
        growing_array_for_each_(callbacks, struct LuaHookedBehaviorCallback, callback) {

            // push the callback onto the stack
            lua_rawgeti(L, LUA_REGISTRYINDEX, callback->ref);

            // push object
            smlua_push_object(L, LOT_OBJECT, object, NULL);

            // call the callback
            if (0 != smlua_call_hook(L, 1, 0, 0, callback->mod, callback->modFile)) {
                LOG_LUA("Failed to call behavior %s callback for behavior id: %hu",
                    (init ? "init" : "loop"), hooked->behaviorId
                );
                return;
            }
        }
    }
}


  /////////////////////////
 // hooked chat command //
/////////////////////////

struct LuaHookedChatCommand {
    char* command;
    char* description;
    int reference;
    struct Mod* mod;
    struct ModFile* modFile;
};

#define MAX_HOOKED_CHAT_COMMANDS 512

static struct LuaHookedChatCommand sHookedChatCommands[MAX_HOOKED_CHAT_COMMANDS] = { 0 };
static int sHookedChatCommandsCount = 0;

int smlua_hook_chat_command(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_chat_command() can only be called on load.");
        return 0;
    }

    if (sHookedChatCommandsCount >= MAX_HOOKED_CHAT_COMMANDS) {
        LOG_LUA_LINE("Hooked chat command exceeded maximum references!");
        return 0;
    }

    const char* command = smlua_to_string(L, 1);
    if (command == NULL || strlen(command) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook chat command: tried to hook invalid command");
        return 0;
    }

    const char* description = smlua_to_string(L, 2);
    if (description == NULL || strlen(description) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook chat command: tried to hook invalid description");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook chat command: tried to hook undefined function '%s'", command);
        return 0;
    }

    struct LuaHookedChatCommand* hooked = &sHookedChatCommands[sHookedChatCommandsCount];
    hooked->command = strdup(command);
    hooked->description = strdup(description);
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    sHookedChatCommandsCount++;
    return 1;
}

int smlua_update_chat_command_description(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    const char* command = smlua_to_string(L, 1);
    if (command == NULL || strlen(command) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update chat command: tried to update invalid command");
        return 0;
    }

    const char* description = smlua_to_string(L, 2);
    if (description == NULL || strlen(description) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update chat command: tried to update invalid description");
        return 0;
    }

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        if (!strcmp(hook->command, command)) {
            if (hook->description) {
                free(hook->description);
            }
            hook->description = strdup(description);
            return 1;
        }
    }

    LOG_LUA_LINE("Update chat command: could not find command to update");
    return 0;
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
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod, hook->modFile)) {
            LOG_LUA("Failed to call the chat command callback: %s", command);
            continue;
        }

        // output the return value
        bool returnValue = false;
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            returnValue = smlua_to_boolean(L, -1);
        }
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

bool is_valid_subcommand(const char* start, const char* end) {
    for (const char* ptr = start; ptr < end; ptr++) {
        if (isspace(*ptr) || *ptr == '\0') {
            return false;
        }
    }
    return true;
}

s32 sort_alphabetically(const void *a, const void *b) {
    const char* strA = *(const char**)a;
    const char* strB = *(const char**)b;

    s32 cmpResult = strcasecmp(strA, strB);

    if (cmpResult == 0) {
        return strcmp(strA, strB);
    }

    return cmpResult;
}

char** smlua_get_chat_player_list(void) {
    char* playerNames[MAX_PLAYERS] = { NULL };
    s32 playerCount = 0;

    for (s32 i = 0; i < MAX_PLAYERS; i++) {
        struct NetworkPlayer* np = &gNetworkPlayers[i];
        if (!np->connected) continue;

        bool isDuplicate = false;
        for (s32 j = 0; j < playerCount; j++) {
            if (strcmp(playerNames[j], np->name) == 0) {
                isDuplicate = true;
                break;
            }
        }

        if (!isDuplicate) {
            playerNames[playerCount++] = np->name;
        }
    }

    qsort(playerNames, playerCount, sizeof(char*), sort_alphabetically);

    char** sortedPlayers = (char**) malloc((playerCount + 1) * sizeof(char*));
    for (s32 i = 0; i < playerCount; i++) {
        sortedPlayers[i] = strdup(playerNames[i]);
    }
    sortedPlayers[playerCount] = NULL;
    return sortedPlayers;
}

char** smlua_get_chat_maincommands_list(void) {
#if defined(DEVELOPMENT)
    s32 defaultCmdsCount = 11;
    static char* defaultCmds[] = {"players", "kick", "ban", "permban", "moderator", "help", "?", "warp", "lua", "luaf", NULL};
#else
    s32 defaultCmdsCount = 8;
    static char* defaultCmds[] = {"players", "kick", "ban", "permban", "moderator", "help", "?", NULL};
#endif
    s32 defaultCmdsCountNew = 0;
    for (s32 i = 0; i < defaultCmdsCount; i++) {
        if (defaultCmds[i] != NULL) {
            defaultCmdsCountNew++;
        } else if (gServerSettings.nametags && defaultCmds[i] == NULL) {
            defaultCmds[i] = "nametags";
            defaultCmdsCountNew++;
            break;
        }
    }
    char** commands = (char**) malloc((sHookedChatCommandsCount + defaultCmdsCountNew + 1) * sizeof(char*));
    for (s32 i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        commands[i] = strdup(hook->command);
    }
    for (s32 i = 0; i < defaultCmdsCount; i++) {
        if (defaultCmds[i] != NULL) {
            commands[sHookedChatCommandsCount + i] = strdup(defaultCmds[i]);
        }
    }
    commands[sHookedChatCommandsCount + defaultCmdsCountNew] = NULL;
    qsort(commands, sHookedChatCommandsCount + defaultCmdsCountNew, sizeof(char*), sort_alphabetically);
    return commands;
}

char** smlua_get_chat_subcommands_list(const char* maincommand) {
    if (gServerSettings.nametags && strcmp(maincommand, "nametags") == 0) {
        s32 count = 2;
        char** subcommands = (char**) malloc((count + 1) * sizeof(char*));
        subcommands[0] = strdup("show-tag");
        subcommands[1] = strdup("show-health");
        subcommands[2] = NULL;
        return subcommands;
    }

    for (s32 i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hook = &sHookedChatCommands[i];
        if (strcmp(hook->command, maincommand) == 0) {
            char* noColorsDesc = djui_text_get_uncolored_string(NULL, strlen(hook->description) + 1, hook->description);
            char* startSubcommands = strstr(noColorsDesc, "[");
            char* endSubcommands = strstr(noColorsDesc, "]");

            if (startSubcommands && endSubcommands && is_valid_subcommand(startSubcommands + 1, endSubcommands)) {
                *endSubcommands = '\0';
                char* subcommandsStr = strdup(startSubcommands + 1);

                s32 count = 1;
                for (s32 j = 0; subcommandsStr[j]; j++) {
                    if (subcommandsStr[j] == '|') count++;
                }

                char** subcommands = (char**) malloc((count + 1) * sizeof(char*));
                char* token = strtok(subcommandsStr, "|");
                s32 index = 0;
                while (token) {
                    subcommands[index++] = strdup(token);
                    token = strtok(NULL, "|");
                }
                subcommands[index] = NULL;

                qsort(subcommands, count, sizeof(char*), sort_alphabetically);

                free(noColorsDesc);
                free(subcommandsStr);
                return subcommands;
            }
            free(noColorsDesc);
        }
    }
    return NULL;
}

bool smlua_maincommand_exists(const char* maincommand) {
    char** commands = smlua_get_chat_maincommands_list();
    bool result = false;

    s32 i = 0;
    while (commands[i] != NULL) {
        if (strcmp(commands[i], maincommand) == 0) {
            result = true;
            break;
        }
        i++;
    }

    for (s32 j = 0; commands[j] != NULL; j++) {
        free(commands[j]);
    }
    free(commands);

    return result;
}

bool smlua_subcommand_exists(const char* maincommand, const char* subcommand) {
    char** subcommands = smlua_get_chat_subcommands_list(maincommand);

    if (subcommands == NULL) {
        return false;
    }

    bool result = false;
    s32 i = 0;
    while (subcommands[i] != NULL) {
        if (strcmp(subcommands[i], subcommand) == 0) {
            result = true;
            break;
        }
        i++;
    }

    for (s32 j = 0; subcommands[j] != NULL; j++) {
        free(subcommands[j]);
    }
    free(subcommands);

    return result;
}

  //////////////////////////////
 // hooked sync table change //
//////////////////////////////

int smlua_hook_on_sync_table_change(lua_State* L) {
    LUA_STACK_CHECK_BEGIN(L);
    if (L == NULL) { return 0; }
    if(!smlua_functions_valid_param_count(L, 4)) { return 0; }

    int syncTableIndex = 1;
    int keyIndex = 2;
    int tagIndex = 3;
    int funcIndex = 4;

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("hook_on_sync_table_change() can only be called on load.");
        return 0;
    }

    if (lua_type(L, syncTableIndex) != LUA_TTABLE) {
        LOG_LUA_LINE("Tried to attach a non-table to hook_on_sync_table_change: %s", luaL_typename(L, syncTableIndex));
        return 0;
    }

    if (lua_type(L, funcIndex) != LUA_TFUNCTION) {
        LOG_LUA_LINE("Tried to attach a non-function to hook_on_sync_table_change: %s", luaL_typename(L, funcIndex));
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

    LUA_STACK_CHECK_END(L);
    return 1;
}


  ////////////////////////////
 // hooked mod menu button //
////////////////////////////

struct LuaHookedModMenuElement gHookedModMenuElements[MAX_HOOKED_MOD_MENU_ELEMENTS] = { 0 };
int gHookedModMenuElementsCount = 0;

int smlua_hook_mod_menu_text(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_TEXT;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = 0;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_button(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_BUTTON;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_checkbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    bool defaultValue = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_CHECKBOX;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = defaultValue;
    hooked->uintValue = 0;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_slider(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 5)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 defaultValue = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 sliderMin = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 sliderMax = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_SLIDER;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = defaultValue;
    hooked->stringValue[0] = '\0';
    hooked->length = 0;
    hooked->sliderMin = sliderMin;
    hooked->sliderMax = sliderMax;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_hook_mod_menu_inputbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 4)) { return 0; }

    if (gHookedModMenuElementsCount >= MAX_HOOKED_MOD_MENU_ELEMENTS) {
        LOG_LUA_LINE("Hooked mod menu element exceeded maximum references!");
        return 0;
    }

    const char* name = smlua_to_string(L, 1);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    const char* defaultValue = smlua_to_string(L, 2);
    if (defaultValue == NULL || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    u32 length = smlua_to_integer(L, 3);
    length = MIN(length, 256);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook invalid element");
        return 0;
    }

    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == -1) {
        LOG_LUA_LINE("Hook mod menu element: tried to hook undefined function '%s'", gLuaActiveMod->name);
        return 0;
    }

    struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[gHookedModMenuElementsCount];
    hooked->element = MOD_MENU_ELEMENT_INPUTBOX;
    snprintf(hooked->name, 64, "%s", name);
    hooked->boolValue = false;
    hooked->uintValue = 0;
    snprintf(hooked->stringValue, 256, "%s", defaultValue);
    hooked->length = length;
    hooked->sliderMin = 0;
    hooked->sliderMax = 0;
    hooked->reference = ref;
    hooked->mod = gLuaActiveMod;
    hooked->modFile = gLuaActiveModFile;

    lua_pushinteger(L, gHookedModMenuElementsCount);
    gHookedModMenuElementsCount++;
    return 1;
}

int smlua_update_mod_menu_element_name(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    const char* name = smlua_to_string(L, 2);
    if (name == NULL || strlen(name) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid name");
        return 0;
    }

    snprintf(gHookedModMenuElements[index].name, 64, "%s", name);
    return 1;
}

int smlua_update_mod_menu_element_checkbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_CHECKBOX) {
        LOG_LUA_LINE("Update mod menu element: element is not a checkbox.");
        return 0;
    }

    bool boolValue = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    gHookedModMenuElements[index].boolValue = boolValue;
    return 1;
}

int smlua_update_mod_menu_element_slider(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_SLIDER) {
        LOG_LUA_LINE("Update mod menu element: element is not a slider.");
        return 0;
    }

    u32 uintValue = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    gHookedModMenuElements[index].uintValue = uintValue;
    return 1;
}

int smlua_update_mod_menu_element_inputbox(lua_State* L) {
    if (L == NULL) { return 0; }
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    int index = smlua_to_integer(L, 1);
    if (index >= gHookedModMenuElementsCount || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element");
        return 0;
    }

    if (gHookedModMenuElements[index].element != MOD_MENU_ELEMENT_INPUTBOX) {
        LOG_LUA_LINE("Update mod menu element: element is not an inputbox.");
        return 0;
    }

    const char* stringValue = smlua_to_string(L, 2);
    if (stringValue == NULL || strlen(stringValue) == 0 || !gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Update mod menu element: tried to update invalid element string");
        return 0;
    }

    snprintf(gHookedModMenuElements[index].stringValue, gHookedModMenuElements[index].length, "%s", stringValue);
    return 1;
}

void smlua_call_mod_menu_element_hook(struct LuaHookedModMenuElement* hooked, int index) {
    lua_State* L = gLuaState;
    if (L == NULL) { return; }

    // push the callback onto the stack
    lua_rawgeti(L, LUA_REGISTRYINDEX, hooked->reference);

    // push parameter
    u8 params = 2;
    lua_pushinteger(L, index);
    switch (hooked->element) {
        case MOD_MENU_ELEMENT_TEXT:
            params = 1;
        case MOD_MENU_ELEMENT_BUTTON:
            params = 1;
            break;
        case MOD_MENU_ELEMENT_CHECKBOX:
            lua_pushboolean(L, hooked->boolValue);
            break;
        case MOD_MENU_ELEMENT_SLIDER:
            lua_pushinteger(L, hooked->uintValue);
            break;
        case MOD_MENU_ELEMENT_INPUTBOX:
            lua_pushstring(L, hooked->stringValue);
            break;
        case MOD_MENU_ELEMENT_MAX:
            break;
    }

    // call the callback
    if (0 != smlua_call_hook(L, params, 1, 0, hooked->mod, hooked->modFile)) {
        LOG_LUA("Failed to call the mod menu element callback: %s", hooked->name);
        return;
    }
}


  //////////
 // misc //
//////////

static void smlua_hook_replace_function_reference(lua_State* L, int* hookedReference, int oldReference, int newReference) {
    lua_rawgeti(L, LUA_REGISTRYINDEX, *hookedReference);   // stack: ..., hookedFunc
    int hookedIdx = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, oldReference);    // stack: ..., hookedFunc, oldFunc
    int oldIdx = lua_gettop(L);

    if (lua_rawequal(L, hookedIdx, oldIdx)) {
        luaL_unref(L, LUA_REGISTRYINDEX, *hookedReference);
        *hookedReference = newReference;
    }

    lua_pop(L, 2);
}

void smlua_hook_replace_function_references(lua_State* L, int oldReference, int newReference) {
    for (int i = 0; i < HOOK_MAX; i++) {
        struct LuaHookedEvent* hooked = &sHookedEvents[i];
        for (int j = 0; j < hooked->count; j++) {
            smlua_hook_replace_function_reference(L, &hooked->reference[j], oldReference, newReference);
        }
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hooked = &sHookedMarioActions[i];
        for (int j = 0; j < ACTION_HOOK_MAX; j++) {
            smlua_hook_replace_function_reference(L, &hooked->actionHookRefs[j], oldReference, newReference);
        }
    }

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hooked = &sHookedChatCommands[i];
        smlua_hook_replace_function_reference(L, &hooked->reference, oldReference, newReference);
    }

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        smlua_hook_replace_function_reference(L, &hooked->reference, oldReference, newReference);
    }

    growing_array_for_each_(gHookedBehaviors, struct LuaHookedBehavior, hooked) {
        growing_array_for_each_(hooked->initCallbacks, struct LuaHookedBehaviorCallback, callback) {
            smlua_hook_replace_function_reference(L, &callback->ref, oldReference, newReference);
        }
        growing_array_for_each_(hooked->loopCallbacks, struct LuaHookedBehaviorCallback, callback) {
            smlua_hook_replace_function_reference(L, &callback->ref, oldReference, newReference);
        }
    }
}

void smlua_clear_hooks(void) {
    for (int i = 0; i < HOOK_MAX; i++) {
        struct LuaHookedEvent* hooked = &sHookedEvents[i];
        for (int j = 0; j < hooked->count; j++) {
            hooked->reference[j] = 0;
            hooked->mod[j] = NULL;
        }
        hooked->count = 0;
    }

    for (int i = 0; i < sHookedMarioActionsCount; i++) {
        struct LuaHookedMarioAction* hooked = &sHookedMarioActions[i];
        hooked->action = 0;
        hooked->mod = NULL;
        hooked->modFile = NULL;
        memset(hooked->actionHookRefs, 0, sizeof(hooked->actionHookRefs));
    }
    sHookedMarioActionsCount = 0;
    memset(gLuaMarioActionIndex, 0, sizeof(gLuaMarioActionIndex));

    for (int i = 0; i < sHookedChatCommandsCount; i++) {
        struct LuaHookedChatCommand* hooked = &sHookedChatCommands[i];
        if (hooked->command != NULL) { free(hooked->command); }
        hooked->command = NULL;

        if (hooked->description != NULL) { free(sHookedChatCommands[i].description); }
        hooked->description = NULL;

        hooked->reference = 0;
        hooked->mod = NULL;
        hooked->modFile = NULL;
    }
    sHookedChatCommandsCount = 0;

    for (int i = 0; i < gHookedModMenuElementsCount; i++) {
        struct LuaHookedModMenuElement* hooked = &gHookedModMenuElements[i];
        hooked->element = MOD_MENU_ELEMENT_TEXT;
        hooked->name[0] = '\0';
        hooked->boolValue = false;
        hooked->uintValue = 0;
        hooked->stringValue[0] = '\0';
        hooked->length = 0;
        hooked->sliderMin = 0;
        hooked->sliderMax = 0;
        hooked->reference = 0;
        hooked->mod = NULL;
        hooked->modFile = NULL;
    }
    gHookedModMenuElementsCount = 0;

    growing_array_for_each_(gHookedBehaviors, struct LuaHookedBehavior, hooked) {

        // Free behavior script if Lua or change back id if it's custom
        if (hooked->type != LUA_BEHAVIOR_TYPE_CUSTOM) {
            free(hooked->script);
        } else {
            hooked->script[1] = (BehaviorScript) ID(hooked->behaviorId);
        }

        // Clear arrays.
        growing_array_free(&hooked->bhvNames);
        growing_array_free(&hooked->initCallbacks);
        growing_array_free(&hooked->loopCallbacks);
    }
    gHookedBehaviors = growing_array_init(gHookedBehaviors, 16, malloc, free);
}

void smlua_bind_hooks(void) {
    lua_State* L = gLuaState;
    smlua_clear_hooks();

    smlua_bind_function(L, "hook_event", smlua_hook_event);
    smlua_bind_function(L, "hook_mario_action", smlua_hook_mario_action);
    smlua_bind_function(L, "hook_chat_command", smlua_hook_chat_command);
    smlua_bind_function(L, "hook_on_sync_table_change", smlua_hook_on_sync_table_change);
    smlua_bind_function(L, "hook_behavior", smlua_hook_behavior);
    smlua_bind_function(L, "hook_mod_menu_text", smlua_hook_mod_menu_text);
    smlua_bind_function(L, "hook_mod_menu_button", smlua_hook_mod_menu_button);
    smlua_bind_function(L, "hook_mod_menu_checkbox", smlua_hook_mod_menu_checkbox);
    smlua_bind_function(L, "hook_mod_menu_slider", smlua_hook_mod_menu_slider);
    smlua_bind_function(L, "hook_mod_menu_inputbox", smlua_hook_mod_menu_inputbox);
    smlua_bind_function(L, "update_chat_command_description", smlua_update_chat_command_description);
    smlua_bind_function(L, "update_mod_menu_element_name", smlua_update_mod_menu_element_name);
    smlua_bind_function(L, "update_mod_menu_element_checkbox", smlua_update_mod_menu_element_checkbox);
    smlua_bind_function(L, "update_mod_menu_element_slider", smlua_update_mod_menu_element_slider);
    smlua_bind_function(L, "update_mod_menu_element_inputbox", smlua_update_mod_menu_element_inputbox);
}
