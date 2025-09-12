/* THIS FILE IS AUTO-GENERATED */
/*   DO NOT EDIT IT MANUALLY   */


bool smlua_call_event_hooks_HOOK_UPDATE() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_UPDATE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_UPDATE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_MARIO_UPDATE(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_MARIO_UPDATE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_MARIO_UPDATE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_BEFORE_MARIO_UPDATE(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_BEFORE_MARIO_UPDATE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_BEFORE_MARIO_UPDATE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_SET_MARIO_ACTION(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SET_MARIO_ACTION];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SET_MARIO_ACTION]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_BEFORE_PHYS_STEP(struct MarioState *m, s32 stepType, u32 stepArg, s32 *stepResultOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_BEFORE_PHYS_STEP];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push stepType
        lua_pushinteger(L, stepType);

        // push stepArg
        lua_pushinteger(L, stepArg);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_BEFORE_PHYS_STEP]);
            continue;
        }

        // return stepResultOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *stepResultOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ALLOW_PVP_ATTACK(struct MarioState *attacker, struct MarioState *victim, u32 interaction, bool *allowAttack) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ALLOW_PVP_ATTACK];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push attacker
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, attacker->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push victim
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, victim->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push interaction
        lua_pushinteger(L, interaction);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ALLOW_PVP_ATTACK]);
            continue;
        }
        hookResult = true;

        // return allowAttack
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowAttack = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PVP_ATTACK(struct MarioState *attacker, struct MarioState *victim, u32 interaction) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PVP_ATTACK];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push attacker
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, attacker->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push victim
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, victim->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push interaction
        lua_pushinteger(L, interaction);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PVP_ATTACK]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PLAYER_CONNECTED(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PLAYER_CONNECTED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PLAYER_CONNECTED]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PLAYER_DISCONNECTED(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PLAYER_DISCONNECTED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PLAYER_DISCONNECTED]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ALLOW_INTERACT(struct MarioState *m, struct Object *obj, u32 interactType, bool *allowInteract) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ALLOW_INTERACT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interactType
        lua_pushinteger(L, interactType);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ALLOW_INTERACT]);
            continue;
        }
        hookResult = true;

        // return allowInteract
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowInteract = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_INTERACT(struct MarioState *m, struct Object *obj, u32 interactType, bool interactValue) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_INTERACT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interactType
        lua_pushinteger(L, interactType);

        // push interactValue
        lua_pushboolean(L, interactValue);

        // call the callback
        if (0 != smlua_call_hook(L, 4, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_INTERACT]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_LEVEL_INIT(u8 warpType, s16 levelNum, u8 areaIdx, u8 nodeId, u32 warpArg) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_LEVEL_INIT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push warpType
        lua_pushinteger(L, warpType);

        // push levelNum
        lua_pushinteger(L, levelNum);

        // push areaIdx
        lua_pushinteger(L, areaIdx);

        // push nodeId
        lua_pushinteger(L, nodeId);

        // push warpArg
        lua_pushinteger(L, warpArg);

        // call the callback
        if (0 != smlua_call_hook(L, 5, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_LEVEL_INIT]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_WARP(u8 warpType, s16 levelNum, u8 areaIdx, u8 nodeId, u32 warpArg) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_WARP];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push warpType
        lua_pushinteger(L, warpType);

        // push levelNum
        lua_pushinteger(L, levelNum);

        // push areaIdx
        lua_pushinteger(L, areaIdx);

        // push nodeId
        lua_pushinteger(L, nodeId);

        // push warpArg
        lua_pushinteger(L, warpArg);

        // call the callback
        if (0 != smlua_call_hook(L, 5, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_WARP]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_SYNC_VALID() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SYNC_VALID];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SYNC_VALID]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_OBJECT_UNLOAD(struct Object *obj) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_OBJECT_UNLOAD];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_OBJECT_UNLOAD]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_SYNC_OBJECT_UNLOAD(struct Object *obj) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SYNC_OBJECT_UNLOAD];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SYNC_OBJECT_UNLOAD]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PAUSE_EXIT(bool usedExitToCastle, bool *allowExit) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PAUSE_EXIT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push usedExitToCastle
        lua_pushboolean(L, usedExitToCastle);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PAUSE_EXIT]);
            continue;
        }
        hookResult = true;

        // return allowExit
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowExit = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_GET_STAR_COLLECTION_DIALOG(s32 *dialogID) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_GET_STAR_COLLECTION_DIALOG];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_GET_STAR_COLLECTION_DIALOG]);
            continue;
        }

        // return dialogID
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *dialogID = smlua_to_integer(L, -1);
        }

        lua_settop(L, prevTop);
        return true;
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_SET_CAMERA_MODE(struct Camera *c, s16 mode, s16 frames, bool *allowSetCameraMode) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SET_CAMERA_MODE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push c
        smlua_push_object(L, LOT_CAMERA, c, NULL);

        // push mode
        lua_pushinteger(L, mode);

        // push frames
        lua_pushinteger(L, frames);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SET_CAMERA_MODE]);
            continue;
        }
        hookResult = true;

        // return allowSetCameraMode
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowSetCameraMode = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_OBJECT_RENDER(struct Object *obj) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_OBJECT_RENDER];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_OBJECT_RENDER]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_DEATH(struct MarioState *m, bool *allowDeath) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_DEATH];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_DEATH]);
            continue;
        }
        hookResult = true;

        // return allowDeath
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowDeath = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PACKET_RECEIVE(s32 modIndex, s32 valueIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PACKET_RECEIVE];
    for (int i = 0; i < hook->count; i++) {
        if (hook->mod[i]->index != modIndex) { continue; }
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push valueIndex
        lua_pushvalue(L, valueIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PACKET_RECEIVE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_USE_ACT_SELECT(s32 levelNum, bool *useActSelect) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_USE_ACT_SELECT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push levelNum
        lua_pushinteger(L, levelNum);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_USE_ACT_SELECT]);
            continue;
        }

        // return useActSelect
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *useActSelect = smlua_to_boolean(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_CHANGE_CAMERA_ANGLE(s32 camAngleType, bool *allowSetCamAngle) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_CHANGE_CAMERA_ANGLE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push camAngleType
        lua_pushinteger(L, camAngleType);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_CHANGE_CAMERA_ANGLE]);
            continue;
        }
        hookResult = true;

        // return allowSetCamAngle
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowSetCamAngle = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_SCREEN_TRANSITION(s32 transitionType, bool *allowPlayTransition) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SCREEN_TRANSITION];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push transitionType
        lua_pushinteger(L, transitionType);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SCREEN_TRANSITION]);
            continue;
        }
        hookResult = true;

        // return allowPlayTransition
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowPlayTransition = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ALLOW_HAZARD_SURFACE(struct MarioState *m, s32 hazardType, bool *allowHazard) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ALLOW_HAZARD_SURFACE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push hazardType
        lua_pushinteger(L, hazardType);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ALLOW_HAZARD_SURFACE]);
            continue;
        }
        hookResult = true;

        // return allowHazard
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowHazard = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_CHAT_MESSAGE(struct MarioState *m, const char *message, bool *allowMessage) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_CHAT_MESSAGE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push message
        lua_pushstring(L, message);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_CHAT_MESSAGE]);
            continue;
        }
        hookResult = true;

        // return allowMessage
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowMessage = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_OBJECT_SET_MODEL(struct Object *obj, s32 modelID, enum ModelExtendedId modelExtendedId) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_OBJECT_SET_MODEL];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push modelID
        lua_pushinteger(L, modelID);

        // push modelExtendedId
        lua_pushinteger(L, modelExtendedId);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_OBJECT_SET_MODEL]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_CHARACTER_SOUND(struct MarioState *m, enum CharacterSound characterSound, s32 *soundOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_CHARACTER_SOUND];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push characterSound
        lua_pushinteger(L, characterSound);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_CHARACTER_SOUND]);
            continue;
        }

        // return soundOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *soundOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_BEFORE_SET_MARIO_ACTION(struct MarioState *m, u32 action, u32 actionArg, u32 *actionOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_BEFORE_SET_MARIO_ACTION];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push action
        lua_pushinteger(L, action);

        // push actionArg
        lua_pushinteger(L, actionArg);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_BEFORE_SET_MARIO_ACTION]);
            continue;
        }
        hookResult = true;

        // return actionOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *actionOverride = smlua_to_integer(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_JOINED_GAME() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_JOINED_GAME];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_JOINED_GAME]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_OBJECT_ANIM_UPDATE(struct Object *obj) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_OBJECT_ANIM_UPDATE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_OBJECT_ANIM_UPDATE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_DIALOG(s32 dialogID, bool *openDialogBox, const char **dialogTextOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_DIALOG];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push dialogID
        lua_pushinteger(L, dialogID);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 2, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_DIALOG]);
            continue;
        }
        hookResult = true;

        // return openDialogBox
        if (lua_type(L, -2) == LUA_TBOOLEAN) {
            *openDialogBox = smlua_to_boolean(L, -2);
        }

        // return dialogTextOverride
        if (lua_type(L, -1) == LUA_TSTRING) {
            *dialogTextOverride = smlua_to_string(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_EXIT() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_EXIT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_EXIT]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_DIALOG_SOUND(s32 speaker, s32 *speakerOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_DIALOG_SOUND];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push speaker
        lua_pushinteger(L, speaker);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_DIALOG_SOUND]);
            continue;
        }

        // return speakerOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *speakerOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_COLLIDE_LEVEL_BOUNDS(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_COLLIDE_LEVEL_BOUNDS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_COLLIDE_LEVEL_BOUNDS]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_MIRROR_MARIO_RENDER(struct GraphNodeObject *mirrorMario, s32 playerIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_MIRROR_MARIO_RENDER];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push mirrorMario
        smlua_push_object(L, LOT_GRAPHNODEOBJECT, mirrorMario, NULL);

        // push playerIndex
        lua_pushinteger(L, playerIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_MIRROR_MARIO_RENDER]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED(struct MarioState *m, f32 *floorNormalY) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_MARIO_OVERRIDE_PHYS_STEP_DEFACTO_SPEED]);
            continue;
        }

        // return floorNormalY
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *floorNormalY = smlua_to_number(L, -1);
        }

        lua_settop(L, prevTop);
        return true;
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_OBJECT_LOAD(struct Object *obj) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_OBJECT_LOAD];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_OBJECT_LOAD]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PLAY_SOUND(s32 soundBits, Vec3f pos, s32 *soundBitsOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PLAY_SOUND];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push soundBits
        lua_pushinteger(L, soundBits);

        // push pos
        extern void smlua_new_vec3f(Vec3f src);
        smlua_new_vec3f(pos);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PLAY_SOUND]);
            continue;
        }

        // return soundBitsOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *soundBitsOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_SEQ_LOAD(u32 seqPlayer, u32 seqId, s32 loadAsync, u32 *seqIdOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_SEQ_LOAD];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push seqPlayer
        lua_pushinteger(L, seqPlayer);

        // push seqId
        lua_pushinteger(L, seqId);

        // push loadAsync
        lua_pushinteger(L, loadAsync);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_SEQ_LOAD]);
            continue;
        }

        // return seqIdOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *seqIdOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_ATTACK_OBJECT(struct MarioState *m, struct Object *obj, s32 interaction) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_ATTACK_OBJECT];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push obj
        smlua_push_object(L, LOT_OBJECT, obj, NULL);

        // push interaction
        lua_pushinteger(L, interaction);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_ATTACK_OBJECT]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_LANGUAGE_CHANGED(const char *langName) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_LANGUAGE_CHANGED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push langName
        lua_pushstring(L, langName);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_LANGUAGE_CHANGED]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_MODS_LOADED() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_MODS_LOADED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_MODS_LOADED]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_DJUI_THEME_CHANGED() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_DJUI_THEME_CHANGED];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_DJUI_THEME_CHANGED]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_GEO_PROCESS(struct GraphNode *node, s32 matStackIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_GEO_PROCESS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push node
        smlua_push_object(L, LOT_GRAPHNODE, node, NULL);

        // push matStackIndex
        lua_pushinteger(L, matStackIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_GEO_PROCESS]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_BEFORE_GEO_PROCESS(struct GraphNode *node, s32 matStackIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_BEFORE_GEO_PROCESS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push node
        smlua_push_object(L, LOT_GRAPHNODE, node, NULL);

        // push matStackIndex
        lua_pushinteger(L, matStackIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_BEFORE_GEO_PROCESS]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_GEO_PROCESS_CHILDREN(struct GraphNode *parent, s32 matStackIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_GEO_PROCESS_CHILDREN];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push parent
        smlua_push_object(L, LOT_GRAPHNODE, parent, NULL);

        // push matStackIndex
        lua_pushinteger(L, matStackIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_GEO_PROCESS_CHILDREN]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_MARIO_OVERRIDE_GEOMETRY_INPUTS(struct MarioState *m, bool *allowUpdateGeometryInputs) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_MARIO_OVERRIDE_GEOMETRY_INPUTS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_MARIO_OVERRIDE_GEOMETRY_INPUTS]);
            continue;
        }
        hookResult = true;

        // return allowUpdateGeometryInputs
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowUpdateGeometryInputs = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_INTERACTIONS(struct MarioState *m) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_INTERACTIONS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_INTERACTIONS]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ALLOW_FORCE_WATER_ACTION(struct MarioState *m, bool isInWaterAction, bool *allowForceAction) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ALLOW_FORCE_WATER_ACTION];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push isInWaterAction
        lua_pushboolean(L, isInWaterAction);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ALLOW_FORCE_WATER_ACTION]);
            continue;
        }
        hookResult = true;

        // return allowForceAction
        if (lua_type(L, -1) == LUA_TBOOLEAN) {
            *allowForceAction = smlua_to_boolean(L, -1);
        }

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_BEFORE_WARP(s16 destLevel, s16 destArea, s16 destWarpNode, s32 arg, struct WarpDest *warpDestOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_BEFORE_WARP];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push destLevel
        lua_pushinteger(L, destLevel);

        // push destArea
        lua_pushinteger(L, destArea);

        // push destWarpNode
        lua_pushinteger(L, destWarpNode);

        // push arg
        lua_pushinteger(L, arg);

        // call the callback
        if (0 != smlua_call_hook(L, 4, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_BEFORE_WARP]);
            continue;
        }

        // if the hook returns a table, use it to override the warp parameters
        if (lua_istable(L, -1)) {

            lua_getfield(L, -1, "destLevel");
            if (lua_isnumber(L, -1)) {
                warpDestOverride->levelNum = smlua_to_integer(L, -1);
            }
            lua_pop(L, 1);

            lua_getfield(L, -1, "destArea");
            if (lua_isnumber(L, -1)) {
                warpDestOverride->areaIdx = smlua_to_integer(L, -1);
            }
            lua_pop(L, 1);

            lua_getfield(L, -1, "destWarpNode");
            if (lua_isnumber(L, -1)) {
                warpDestOverride->nodeId = smlua_to_integer(L, -1);
            }
            lua_pop(L, 1);

            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_INSTANT_WARP(u8 areaIdx, u8 nodeId, Vec3s displacement) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_INSTANT_WARP];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push areaIdx
        lua_pushinteger(L, areaIdx);

        // push nodeId
        lua_pushinteger(L, nodeId);

        // push displacement
        extern void smlua_new_vec3s(Vec3s src);
        smlua_new_vec3s(displacement);

        // call the callback
        if (0 != smlua_call_hook(L, 3, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_INSTANT_WARP]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_MARIO_OVERRIDE_FLOOR_CLASS(struct MarioState *m, s32 floorClass, s32 *floorClassOverride) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_MARIO_OVERRIDE_FLOOR_CLASS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push m
        lua_getglobal(L, "gMarioStates");
        lua_pushinteger(L, m->playerIndex);
        lua_gettable(L, -2);
        lua_remove(L, -2);

        // push floorClass
        lua_pushinteger(L, floorClass);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 1, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_MARIO_OVERRIDE_FLOOR_CLASS]);
            continue;
        }

        // return floorClassOverride
        if (lua_type(L, -1) == LUA_TNUMBER) {
            *floorClassOverride = smlua_to_integer(L, -1);
            lua_settop(L, prevTop);
            return true;
        }

        lua_settop(L, prevTop);
    }
    return false;
}

bool smlua_call_event_hooks_HOOK_ON_ADD_SURFACE(struct Surface *surface, bool dynamic) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_ADD_SURFACE];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push surface
        smlua_push_object(L, LOT_SURFACE, surface, NULL);

        // push dynamic
        lua_pushboolean(L, dynamic);

        // call the callback
        if (0 != smlua_call_hook(L, 2, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_ADD_SURFACE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_CLEAR_AREAS() {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_CLEAR_AREAS];
    for (int i = 0; i < hook->count; i++) {
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // call the callback
        if (0 != smlua_call_hook(L, 0, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_CLEAR_AREAS]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}

bool smlua_call_event_hooks_HOOK_ON_PACKET_BYTESTRING_RECEIVE(s32 modIndex, s32 valueIndex) {
    lua_State *L = gLuaState;
    if (L == NULL) { return false; }
    bool hookResult = false;

    struct LuaHookedEvent *hook = &sHookedEvents[HOOK_ON_PACKET_BYTESTRING_RECEIVE];
    for (int i = 0; i < hook->count; i++) {
        if (hook->mod[i]->index != modIndex) { continue; }
        s32 prevTop = lua_gettop(L);

        // push the callback onto the stack
        lua_rawgeti(L, LUA_REGISTRYINDEX, hook->reference[i]);

        // push valueIndex
        lua_pushvalue(L, valueIndex);

        // call the callback
        if (0 != smlua_call_hook(L, 1, 0, 0, hook->mod[i], hook->modFile[i])) {
            LOG_LUA("Failed to call the callback for hook %s", sLuaHookedEventTypeName[HOOK_ON_PACKET_BYTESTRING_RECEIVE]);
            continue;
        }
        hookResult = true;

        lua_settop(L, prevTop);
    }
    return hookResult;
}
