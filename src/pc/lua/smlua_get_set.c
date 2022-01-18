#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

enum LuaValueType {
    LVT_U8,
    LVT_U16,
    LVT_U32,
    LVT_S8,
    LVT_S16,
    LVT_S32,
    LVT_F32,
    LVT_VEC3S,
    LVT_VEC3F,
};

struct LuaObjectField {
    const char* key;
    enum LuaValueType valueType;
    size_t valueOffset;
    bool immutable;
};

#define LUA_VEC3S_FIELD_COUNT 3
static struct LuaObjectField sVec3sFields[LUA_VEC3S_FIELD_COUNT] = {
    { "x", LVT_S16, sizeof(s16) * 0, false },
    { "y", LVT_S16, sizeof(s16) * 1, false },
    { "z", LVT_S16, sizeof(s16) * 2, false },
};

#define LUA_VEC3F_FIELD_COUNT 3
static struct LuaObjectField sVec3fFields[LUA_VEC3F_FIELD_COUNT] = {
    { "x", LVT_F32, sizeof(f32) * 0, false },
    { "y", LVT_F32, sizeof(f32) * 1, false },
    { "z", LVT_F32, sizeof(f32) * 2, false },
};

#define LUA_MARIO_STATE_FIELD_COUNT 55
static struct LuaObjectField sMarioStateFields[LUA_MARIO_STATE_FIELD_COUNT] = {
    { "playerIndex",              LVT_U16,   offsetof(struct MarioState, playerIndex)             , true  },
    { "input",                    LVT_U16,   offsetof(struct MarioState, input)                   , false },
    { "flags",                    LVT_U32,   offsetof(struct MarioState, flags)                   , false },
    { "particleFlags",            LVT_U32,   offsetof(struct MarioState, particleFlags)           , false },
    { "action",                   LVT_U32,   offsetof(struct MarioState, action)                  , false },
    { "prevAction",               LVT_U32,   offsetof(struct MarioState, prevAction)              , false },
    { "terrainSoundAddend",       LVT_U32,   offsetof(struct MarioState, terrainSoundAddend)      , false },
    { "actionState",              LVT_U16,   offsetof(struct MarioState, actionState)             , false },
    { "actionTimer",              LVT_U16,   offsetof(struct MarioState, actionTimer)             , false },
    { "actionArg",                LVT_U32,   offsetof(struct MarioState, actionArg)               , false },
    { "intendedMag",              LVT_F32,   offsetof(struct MarioState, intendedMag)             , false },
    { "intendedYaw",              LVT_S16,   offsetof(struct MarioState, intendedYaw)             , false },
    { "invincTimer",              LVT_S16,   offsetof(struct MarioState, invincTimer)             , false },
    { "framesSinceA",             LVT_U8,    offsetof(struct MarioState, framesSinceA)            , false },
    { "framesSinceB",             LVT_U8,    offsetof(struct MarioState, framesSinceB)            , false },
    { "wallKickTimer",            LVT_U8,    offsetof(struct MarioState, wallKickTimer)           , false },
    { "doubleJumpTimer",          LVT_U8,    offsetof(struct MarioState, doubleJumpTimer)         , false },
    { "faceAngle",                LVT_VEC3S, offsetof(struct MarioState, faceAngle)               , true  },
    { "angleVel",                 LVT_VEC3S, offsetof(struct MarioState, angleVel)                , true  },
    { "slideYaw",                 LVT_S16,   offsetof(struct MarioState, slideYaw)                , false },
    { "twirlYaw",                 LVT_S16,   offsetof(struct MarioState, twirlYaw)                , false },
    { "pos",                      LVT_VEC3F, offsetof(struct MarioState, pos)                     , true  },
    { "vel",                      LVT_VEC3F, offsetof(struct MarioState, vel)                     , true  },
    { "forwardVel",               LVT_F32,   offsetof(struct MarioState, forwardVel)              , false },
    { "slideVelX",                LVT_F32,   offsetof(struct MarioState, slideVelX)               , false },
    { "slideVelZ",                LVT_F32,   offsetof(struct MarioState, slideVelZ)               , false },
    { "ceilHeight",               LVT_F32,   offsetof(struct MarioState, ceilHeight)              , false },
    { "floorHeight",              LVT_F32,   offsetof(struct MarioState, floorHeight)             , false },
    { "floorAngle",               LVT_S16,   offsetof(struct MarioState, floorAngle)              , false },
    { "waterLevel",               LVT_S16,   offsetof(struct MarioState, waterLevel)              , false },
    { "collidedObjInteractTypes", LVT_U32,   offsetof(struct MarioState, collidedObjInteractTypes), false },
    { "numCoins",                 LVT_S16,   offsetof(struct MarioState, numCoins)                , false },
    { "numStars",                 LVT_S16,   offsetof(struct MarioState, numStars)                , false },
    { "mechani",                  LVT_S8,    offsetof(struct MarioState, numKeys)                 , false },
    { "numLives",                 LVT_S8,    offsetof(struct MarioState, numLives)                , false },
    { "health",                   LVT_S16,   offsetof(struct MarioState, health)                  , false },
    { "unkB0",                    LVT_S16,   offsetof(struct MarioState, unkB0)                   , false },
    { "hurtCounter",              LVT_U8,    offsetof(struct MarioState, hurtCounter)             , false },
    { "healCounter",              LVT_U8,    offsetof(struct MarioState, healCounter)             , false },
    { "squishTimer",              LVT_U8,    offsetof(struct MarioState, squishTimer)             , false },
    { "fadeWarpOpacity",          LVT_U8,    offsetof(struct MarioState, fadeWarpOpacity)         , false },
    { "capTimer",                 LVT_U16,   offsetof(struct MarioState, capTimer)                , false },
    { "prevNumStarsForDialog",    LVT_S16,   offsetof(struct MarioState, prevNumStarsForDialog)   , false },
    { "peakHeight",               LVT_F32,   offsetof(struct MarioState, peakHeight)              , false },
    { "quicksandDepth",           LVT_F32,   offsetof(struct MarioState, quicksandDepth)          , false },
    { "unkC4",                    LVT_F32,   offsetof(struct MarioState, unkC4)                   , false },
    { "currentRoom",              LVT_S16,   offsetof(struct MarioState, currentRoom)             , false },
    { "isSnoring",                LVT_U8,    offsetof(struct MarioState, isSnoring)               , false },
    { "freeze",                   LVT_U8,    offsetof(struct MarioState, freeze)                  , false },
    { "splineKeyframeFraction",   LVT_F32,   offsetof(struct MarioState, splineKeyframeFraction)  , false },
    { "splineState",              LVT_S32,   offsetof(struct MarioState, splineState)             , false },
    { "nonInstantWarpPos",        LVT_VEC3F, offsetof(struct MarioState, nonInstantWarpPos)       , true  },
    { "wasNetworkVisible",        LVT_U8,    offsetof(struct MarioState, wasNetworkVisible)       , false },
    { "minimumBoneY",             LVT_F32,   offsetof(struct MarioState, minimumBoneY)            , false },
    { "curAnimOffset",            LVT_F32,   offsetof(struct MarioState, curAnimOffset)           , false },
    /* TODO: implement
        struct Surface *wall;
        struct Surface *ceil;
        struct Surface *floor;
        struct Object *interactObj;
        struct Object *heldObj;
        struct Object *usedObj;
        struct Object *riddenObj;
        struct Object *marioObj;
        struct SpawnInfo *spawnInfo;
        struct Area *area;
        struct PlayerCameraState *statusForCamera;
        struct MarioBodyState *marioBodyState;
        struct Controller *controller;
        struct MarioAnimation *animation;
        struct Object* heldByObj;
        struct Object* bubbleObj;
        Vec4s* splineKeyframe;
        struct Character* character;
    */
};

enum LuaObjectType {
    LOT_VEC3S,
    LOT_VEC3F,
    LOT_MARIO_STATE,
    LOT_MAX,
};

struct LuaObjectTable {
    enum LuaObjectType objectType;
    struct LuaObjectField* fields;
    u16 fieldCount;
};

struct LuaObjectTable sLuaObjectTable[LOT_MAX] = {
    { LOT_VEC3S,       sVec3sFields,      LUA_VEC3S_FIELD_COUNT       },
    { LOT_VEC3F,       sVec3fFields,      LUA_VEC3F_FIELD_COUNT       },
    { LOT_MARIO_STATE, sMarioStateFields, LUA_MARIO_STATE_FIELD_COUNT },
};

static struct LuaObjectField* smlua_get_object_field(struct LuaObjectTable* ot, const char* key) {
    // TODO: change this to binary search or hash table or something
    for (int i = 0; i < ot->fieldCount; i++) {
        if (!strcmp(ot->fields[i].key, key)) {
            return &ot->fields[i];
        }
    }

    return NULL;
}

// iteration 3

static void smlua_push_object(lua_State* L, enum LuaObjectType lot, void* p) {
    lua_newtable(L);
    smlua_push_integer_field(lot, "_lot");
    smlua_push_integer_field((u64)p, "_pointer");
    lua_pushglobaltable(L);
    lua_getfield(gLuaState, -1, "_CObject");
    lua_setmetatable(L, -3);
    lua_pop(L, 1); // pop global table
}

static int smlua__get_field(lua_State* L) {
    enum LuaObjectType lot = lua_tointeger(L, -3);
    u64 pointer = lua_tointeger(L, -2);
    const char* key = lua_tostring(L, -1);

    if (pointer == 0) {
        LOG_LUA("_get_field on null pointer");
        return 0;
    }

    if (lot >= LOT_MAX) {
        LOG_LUA("_get_field on invalid LOT '%u'", lot);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[lot], key);
    if (data == NULL) {
        LOG_LUA("_get_field on invalid key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
        case LVT_U8:    lua_pushinteger(L, *(u8* )p);       break;
        case LVT_U16:   lua_pushinteger(L, *(u16*)p);       break;
        case LVT_U32:   lua_pushinteger(L, *(u32*)p);       break;
        case LVT_S8:    lua_pushinteger(L, *(s8* )p);       break;
        case LVT_S16:   lua_pushinteger(L, *(s16*)p);       break;
        case LVT_S32:   lua_pushinteger(L, *(s32*)p);       break;
        case LVT_F32:   lua_pushnumber( L, *(f32*)p);       break;
        case LVT_VEC3S: smlua_push_object(L, LOT_VEC3S, p); break;
        case LVT_VEC3F: smlua_push_object(L, LOT_VEC3F, p); break;
        default:
            LOG_LUA("_get_field on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
    }

    return 1;
}

static int smlua__set_field(lua_State* L) {
    enum LuaObjectType lot = lua_tointeger(L, -4);
    u64 pointer = lua_tointeger(L, -3);
    const char* key = lua_tostring(L, -2);

    if (pointer == 0) {
        LOG_LUA("_get_field on null pointer");
        return 0;
    }

    if (lot >= LOT_MAX) {
        LOG_LUA("_get_field on invalid LOT '%u'", lot);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[lot], key);
    if (data == NULL) {
        LOG_LUA("_get_field on invalid key '%s'", key);
        return 0;
    }

    if (data->immutable) {
        LOG_LUA("_get_field on immutable key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
    case LVT_U8:  *(u8*) p = lua_tointeger(L, -1); break;
    case LVT_U16: *(u16*)p = lua_tointeger(L, -1); break;
    case LVT_U32: *(u32*)p = lua_tointeger(L, -1); break;
    case LVT_S8:  *(s8*) p = lua_tointeger(L, -1); break;
    case LVT_S16: *(s16*)p = lua_tointeger(L, -1); break;
    case LVT_S32: *(s32*)p = lua_tointeger(L, -1); break;
    case LVT_F32: *(f32*)p = lua_tonumber(L, -1);  break;
    default:
        LOG_LUA("_get_field on unimplemented type '%d', key '%s'", data->valueType, key);
        return 0;
    }

    return 1;
}

// iteration 2

static int smlua_get_mario_state_field(lua_State* L) {
    u8 index = lua_tointeger(L, -2);
    const char* key = lua_tostring(L, -1);
    if (index >= MAX_PLAYERS) {
        LOG_LUA("get_mario_state_field() on invalid index '%d'", index);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[LOT_MARIO_STATE], key);
    if (data == NULL) {
        LOG_LUA("get_mario_state_field() on invalid key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)&gMarioStates[index]) + data->valueOffset;
    switch (data->valueType) {
        case LVT_U8:  lua_pushinteger(L, *(u8* )p); break;
        case LVT_U16: lua_pushinteger(L, *(u16*)p); break;
        case LVT_U32: lua_pushinteger(L, *(u32*)p); break;
        case LVT_S8:  lua_pushinteger(L, *(s8* )p); break;
        case LVT_S16: lua_pushinteger(L, *(s16*)p); break;
        case LVT_S32: lua_pushinteger(L, *(s32*)p); break;
        case LVT_F32: lua_pushnumber( L, *(f32*)p); break;
        case LVT_VEC3S:
            lua_newtable(L);
            smlua_push_integer_field((u64)p, "_pointer");
            lua_pushglobaltable(L);
            lua_getfield(gLuaState, -1, "_Vec3sMeta");
            lua_setmetatable(L, -3);
            lua_pop(L, 1); // pop global table
            break;
        case LVT_VEC3F:
            lua_newtable(L);
            smlua_push_integer_field((u64)p, "_pointer");
            lua_pushglobaltable(L);
            lua_getfield(gLuaState, -1, "_Vec3fMeta");
            lua_setmetatable(L, -3);
            lua_pop(L, 1); // pop global table
            break;
        default:
            LOG_LUA("get_mario_state_field() on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
    }

    return 1;
}

static int smlua_set_mario_state_field(lua_State* L) {
    u8 index = lua_tointeger(L, -3);
    const char* key = lua_tostring(L, -2);
    if (index >= MAX_PLAYERS) {
        LOG_LUA("set_mario_state_field() on invalid index '%d'", index);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[LOT_MARIO_STATE], key);
    if (data == NULL) {
        LOG_LUA("set_mario_state_field() on invalid key '%s'", key);
        return 0;
    }
    if (data->immutable) {
        LOG_LUA("set_mario_state_field() on immutable key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)&gMarioStates[index]) + data->valueOffset;
    switch (data->valueType) {
        case LVT_U8:  *(u8* )p = lua_tointeger(L, -1); break;
        case LVT_U16: *(u16*)p = lua_tointeger(L, -1); break;
        case LVT_U32: *(u32*)p = lua_tointeger(L, -1); break;
        case LVT_S8:  *(s8* )p = lua_tointeger(L, -1); break;
        case LVT_S16: *(s16*)p = lua_tointeger(L, -1); break;
        case LVT_S32: *(s32*)p = lua_tointeger(L, -1); break;
        case LVT_F32: *(f32*)p = lua_tonumber( L, -1); break;
        default:
            LOG_LUA("set_mario_state_field() on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
    }

    return 1;
}

static int smlua_get_vec3s_field(lua_State* L) {
    u64 pointer = lua_tointeger(L, -2);
    const char* key = lua_tostring(L, -1);

    if (pointer == 0) {
        LOG_LUA("get_vec3s_field() on null pointer");
        return 0;
    }

    if (!strcmp("x", key)) {
        lua_pushinteger(L, ((s16*)pointer)[0]);
    }
    else if (!strcmp("y", key)) {
        lua_pushinteger(L, ((s16*)pointer)[1]);
    }
    else if (!strcmp("z", key)) {
        lua_pushinteger(L, ((s16*)pointer)[2]);
    }
    else {
        LOG_LUA("get_vec3s_field() on invalid key '%s'", key);
        return 0;
    }

    return 1;
}

static int smlua_set_vec3s_field(lua_State* L) {
    u64 pointer = lua_tointeger(L, -3);
    const char* key = lua_tostring(L, -2);
    s16 value = lua_tointeger(L, -1);

    if (pointer == 0) {
        LOG_LUA("set_vec3s_field() on null pointer");
        return 0;
    }

    if (!strcmp("x", key)) {
        ((s16*)pointer)[0] = value;
    }
    else if (!strcmp("y", key)) {
        ((s16*)pointer)[1] = value;
    }
    else if (!strcmp("z", key)) {
        ((s16*)pointer)[2] = value;
    }
    else {
        LOG_LUA("set_vec3s_field() on invalid key '%s'", key);
        return 0;
    }

    return 1;
}

static int smlua_get_vec3f_field(lua_State* L) {
    u64 pointer = lua_tointeger(L, -2);
    const char* key = lua_tostring(L, -1);

    if (pointer == 0) {
        LOG_LUA("get_vec3f_field() on null pointer");
        return 0;
    }

    if (!strcmp("x", key)) {
        lua_pushnumber(L, ((f32*)pointer)[0]);
    } else if (!strcmp("y", key)) {
        lua_pushnumber(L, ((f32*)pointer)[1]);
    } else if (!strcmp("z", key)) {
        lua_pushnumber(L, ((f32*)pointer)[2]);
    } else {
        LOG_LUA("get_vec3f_field() on invalid key '%s'", key);
        return 0;
    }

    return 1;
}

static int smlua_set_vec3f_field(lua_State* L) {
    u64 pointer = lua_tointeger(L, -3);
    const char* key = lua_tostring(L, -2);
    f32 value = lua_tonumber(L, -1);

    if (pointer == 0) {
        LOG_LUA("set_vec3f_field() on null pointer");
        return 0;
    }

    if (!strcmp("x", key)) {
        ((f32*)pointer)[0] = value;
    } else if (!strcmp("y", key)) {
        ((f32*)pointer)[1] = value;
    } else if (!strcmp("z", key)) {
        ((f32*)pointer)[2] = value;
    } else {
        LOG_LUA("set_vec3f_field() on invalid key '%s'", key);
        return 0;
    }

    return 1;
}

// iteration 1

static int smlua_get_mario_state(lua_State* L) {
    int index = lua_tointeger(L, -1);
    lua_newtable(L);

    {
        struct MarioState* m = &gMarioStates[index];
        const int t = lua_gettop(L);

        smlua_push_integer_field(m->playerIndex, "playerIndex");
        smlua_push_integer_field(m->input, "input");
        smlua_push_integer_field(m->flags, "flags");
        smlua_push_integer_field(m->particleFlags, "particleFlags");
        smlua_push_integer_field(m->action, "action");
        smlua_push_integer_field(m->prevAction, "prevAction");
        smlua_push_integer_field(m->terrainSoundAddend, "terrainSoundAddend");
        smlua_push_integer_field(m->actionState, "actionState");
        smlua_push_integer_field(m->actionTimer, "actionTimer");
        smlua_push_integer_field(m->actionArg, "actionArg");
        smlua_push_number_field(m->intendedMag, "intendedMag");
        smlua_push_integer_field(m->intendedYaw, "intendedYaw");
        smlua_push_integer_field(m->invincTimer, "invincTimer");
        smlua_push_integer_field(m->framesSinceA, "framesSinceA");
        smlua_push_integer_field(m->framesSinceB, "framesSinceB");
        smlua_push_integer_field(m->wallKickTimer, "wallKickTimer");
        smlua_push_integer_field(m->doubleJumpTimer, "doubleJumpTimer");

        {
            lua_newtable(L);
            smlua_push_integer_field(m->faceAngle[0], "x");
            smlua_push_integer_field(m->faceAngle[1], "y");
            smlua_push_integer_field(m->faceAngle[2], "z");
            lua_setfield(L, t, "faceAngle");
        }

        {
            lua_newtable(L);
            smlua_push_integer_field(m->angleVel[0], "x");
            smlua_push_integer_field(m->angleVel[1], "y");
            smlua_push_integer_field(m->angleVel[2], "z");
            lua_setfield(L, t, "angleVel");
        }

        smlua_push_integer_field(m->slideYaw, "slideYaw");
        smlua_push_integer_field(m->twirlYaw, "twirlYaw");

        {
            lua_newtable(L);
            smlua_push_number_field(m->pos[0], "x");
            smlua_push_number_field(m->pos[1], "y");
            smlua_push_number_field(m->pos[2], "z");
            lua_setfield(L, t, "pos");
        }

        {
            lua_newtable(L);
            smlua_push_number_field(m->vel[0], "x");
            smlua_push_number_field(m->vel[1], "y");
            smlua_push_number_field(m->vel[2], "z");
            lua_setfield(L, t, "vel");
        }

        smlua_push_number_field(m->forwardVel, "forwardVel");
        smlua_push_number_field(m->slideVelX, "slideVelX");
        smlua_push_number_field(m->slideVelZ, "slideVelZ");

        //struct Surface* wall;
        //struct Surface* ceil;
        //struct Surface* floor;

        smlua_push_number_field(m->ceilHeight, "ceilHeight");
        smlua_push_number_field(m->floorHeight, "floorHeight");
        smlua_push_integer_field(m->floorAngle, "floorAngle");
        smlua_push_integer_field(m->waterLevel, "waterLevel");

        //struct Object* interactObj;
        //struct Object* heldObj;
        //struct Object* usedObj;
        //struct Object* riddenObj;
        //struct Object* marioObj;
        //struct SpawnInfo* spawnInfo;
        //struct Area* area;
        //struct PlayerCameraState* statusForCamera;
        //struct MarioBodyState* marioBodyState;

        {
            lua_newtable(L);
            smlua_push_integer_field(m->controller->buttonDown, "buttonDown");
            smlua_push_integer_field(m->controller->buttonPressed, "buttonPressed");
            smlua_push_integer_field(m->controller->extStickX, "extStickX");
            smlua_push_integer_field(m->controller->extStickY, "extStickY");
            smlua_push_integer_field(m->controller->port, "port");
            smlua_push_integer_field(m->controller->rawStickX, "rawStickX");
            smlua_push_integer_field(m->controller->rawStickY, "rawStickY");
            smlua_push_number_field(m->controller->stickMag, "stickMag");
            smlua_push_number_field(m->controller->stickX, "stickX");
            smlua_push_number_field(m->controller->stickY, "stickY");
            //m->controller->controllerData
            //m->controller->statusData
            lua_setfield(L, t, "controller");
        }

        //struct MarioAnimation* animation;

        smlua_push_integer_field(m->collidedObjInteractTypes, "collidedObjInteractTypes");
        smlua_push_integer_field(m->numCoins, "numCoins");
        smlua_push_integer_field(m->numStars, "numStars");
        smlua_push_integer_field(m->numKeys, "numKeys");
        smlua_push_integer_field(m->numLives, "numLives");
        smlua_push_integer_field(m->health, "health");
        smlua_push_integer_field(m->unkB0, "unkB0");
        smlua_push_integer_field(m->hurtCounter, "hurtCounter");
        smlua_push_integer_field(m->healCounter, "healCounter");
        smlua_push_integer_field(m->squishTimer, "squishTimer");
        smlua_push_integer_field(m->fadeWarpOpacity, "fadeWarpOpacity");
        smlua_push_integer_field(m->capTimer, "capTimer");
        smlua_push_integer_field(m->prevNumStarsForDialog, "prevNumStarsForDialog");
        smlua_push_number_field(m->peakHeight, "peakHeight");
        smlua_push_number_field(m->quicksandDepth, "quicksandDepth");
        smlua_push_number_field(m->unkC4, "unkC4");
        smlua_push_integer_field(m->currentRoom, "currentRoom");

        //struct Object* heldByObj;

        smlua_push_integer_field(m->isSnoring, "isSnoring");

        //struct Object* bubbleObj;

        smlua_push_integer_field(m->freeze, "freeze");

        {
            lua_newtable(L);
            smlua_push_number_field(m->nonInstantWarpPos[0], "x");
            smlua_push_number_field(m->nonInstantWarpPos[1], "y");
            smlua_push_number_field(m->nonInstantWarpPos[2], "z");
            lua_setfield(L, t, "nonInstantWarpPos");
        }

        u8 characterIndex = 0;
        for (int i = 0; i < CT_MAX; i++) {
            if (m->character == &gCharacters[i]) {
                characterIndex = i;
                break;
            }
        }
        smlua_push_integer_field(characterIndex, "character");

        smlua_push_integer_field(m->wasNetworkVisible, "wasNetworkVisible");
        smlua_push_number_field(m->minimumBoneY, "minimumBoneY");
        smlua_push_number_field(m->curAnimOffset, "curAnimOffset");
    }

    luaL_setmetatable(L, "mariostate");
    return 1;
}

static int smlua_set_mario_state(lua_State* L) {

    int index = lua_tointeger(L, -2);

    {
        struct MarioState* m = &gMarioStates[index];
        //smlua_get_u16_field(&m->playerIndex, "playerIndex");
        smlua_get_u16_field(&m->input, "input");
        smlua_get_u32_field(&m->flags, "flags");
        smlua_get_u32_field(&m->particleFlags, "particleFlags");
        smlua_get_u32_field(&m->action, "action");
        smlua_get_u32_field(&m->prevAction, "prevAction");
        smlua_get_u32_field(&m->terrainSoundAddend, "terrainSoundAddend");
        smlua_get_u16_field(&m->actionState, "actionState");
        smlua_get_u16_field(&m->actionTimer, "actionTimer");
        smlua_get_u32_field(&m->actionArg, "actionArg");
        smlua_get_number_field(&m->intendedMag, "intendedMag");
        smlua_get_s16_field(&m->intendedYaw, "intendedYaw");
        smlua_get_s16_field(&m->invincTimer, "invincTimer");
        smlua_get_u8_field(&m->framesSinceA, "framesSinceA");
        smlua_get_u8_field(&m->framesSinceB, "framesSinceB");
        smlua_get_u8_field(&m->wallKickTimer, "wallKickTimer");
        smlua_get_u8_field(&m->doubleJumpTimer, "doubleJumpTimer");

        {
            lua_getfield(L, -1, "faceAngle");
            smlua_get_s16_field(&m->faceAngle[0], "x");
            smlua_get_s16_field(&m->faceAngle[1], "y");
            smlua_get_s16_field(&m->faceAngle[2], "z");
            lua_pop(L, 1);
        }

        {
            lua_getfield(L, -1, "angleVel");
            smlua_get_s16_field(&m->angleVel[0], "x");
            smlua_get_s16_field(&m->angleVel[1], "y");
            smlua_get_s16_field(&m->angleVel[2], "z");
            lua_pop(L, 1);
        }

        smlua_get_s16_field(&m->slideYaw, "slideYaw");
        smlua_get_s16_field(&m->twirlYaw, "twirlYaw");

        {
            lua_getfield(L, -1, "pos");
            float oldX = m->pos[0];
            float oldY = m->pos[1];
            float oldZ = m->pos[2];
            smlua_get_number_field(&m->pos[0], "x");
            smlua_get_number_field(&m->pos[1], "y");
            smlua_get_number_field(&m->pos[2], "z");
            bool posChanged = (oldX != m->pos[0]) || (oldY != m->pos[1]) || (oldZ != m->pos[2]);
            if (m->marioObj != NULL && posChanged) {
                printf(" POS CHANGED \n");
                m->marioObj->oPosX = m->pos[0];
                m->marioObj->oPosY = m->pos[1];
                m->marioObj->oPosZ = m->pos[2];
                m->marioObj->header.gfx.pos[0] = m->pos[0];
                m->marioObj->header.gfx.pos[1] = m->pos[1];
                m->marioObj->header.gfx.pos[2] = m->pos[2];
            }
            lua_pop(L, 1);
        }

        {
            lua_getfield(L, -1, "vel");
            smlua_get_number_field(&m->vel[0], "x");
            smlua_get_number_field(&m->vel[1], "y");
            smlua_get_number_field(&m->vel[2], "z");
            lua_pop(L, 1);
        }

        smlua_get_number_field(&m->forwardVel, "forwardVel");
        smlua_get_number_field(&m->slideVelX, "slideVelX");
        smlua_get_number_field(&m->slideVelZ, "slideVelZ");

        //struct Surface* wall;
        //struct Surface* ceil;
        //struct Surface* floor;

        smlua_get_number_field(&m->ceilHeight, "ceilHeight");
        smlua_get_number_field(&m->floorHeight, "floorHeight");
        smlua_get_s16_field(&m->floorAngle, "floorAngle");
        smlua_get_s16_field(&m->waterLevel, "waterLevel");

        //struct Object* interactObj;
        //struct Object* heldObj;
        //struct Object* usedObj;
        //struct Object* riddenObj;
        //struct Object* marioObj;
        //struct SpawnInfo* spawnInfo;
        //struct Area* area;
        //struct PlayerCameraState* statusForCamera;
        //struct MarioBodyState* marioBodyState;

        {
            lua_getfield(L, -1, "controller");
            smlua_get_u16_field(&m->controller->buttonDown, "buttonDown");
            smlua_get_u16_field(&m->controller->buttonPressed, "buttonPressed");
            smlua_get_s16_field(&m->controller->extStickX, "extStickX");
            smlua_get_s16_field(&m->controller->extStickY, "extStickY");
            smlua_get_s32_field(&m->controller->port, "port");
            smlua_get_s16_field(&m->controller->rawStickX, "rawStickX");
            smlua_get_s16_field(&m->controller->rawStickY, "rawStickY");
            smlua_get_number_field(&m->controller->stickMag, "stickMag");
            smlua_get_number_field(&m->controller->stickX, "stickX");
            //m->controller->controllerData
            //m->controller->statusData
            lua_pop(L, 1);
        }

        //struct MarioAnimation* animation;

        smlua_get_u32_field(&m->collidedObjInteractTypes, "collidedObjInteractTypes");
        smlua_get_s16_field(&m->numCoins, "numCoins");
        smlua_get_s16_field(&m->numStars, "numStars");
        smlua_get_s8_field(&m->numKeys, "numKeys");
        smlua_get_s8_field(&m->numLives, "numLives");
        smlua_get_s16_field(&m->health, "health");
        smlua_get_s16_field(&m->unkB0, "unkB0");
        smlua_get_u8_field(&m->hurtCounter, "hurtCounter");
        smlua_get_u8_field(&m->healCounter, "healCounter");
        smlua_get_u8_field(&m->squishTimer, "squishTimer");
        smlua_get_u8_field(&m->fadeWarpOpacity, "fadeWarpOpacity");
        smlua_get_u16_field(&m->capTimer, "capTimer");
        smlua_get_s16_field(&m->prevNumStarsForDialog, "prevNumStarsForDialog");
        smlua_get_number_field(&m->peakHeight, "peakHeight");
        smlua_get_number_field(&m->quicksandDepth, "quicksandDepth");
        smlua_get_number_field(&m->unkC4, "unkC4");
        smlua_get_s16_field(&m->currentRoom, "currentRoom");

        //struct Object* heldByObj;

        smlua_get_u8_field(&m->isSnoring, "isSnoring");

        //struct Object* bubbleObj;

        smlua_get_u8_field(&m->freeze, "freeze");

        {
            lua_getfield(L, -1, "nonInstantWarpPos");
            smlua_get_number_field(&m->nonInstantWarpPos[0], "x");
            smlua_get_number_field(&m->nonInstantWarpPos[1], "y");
            smlua_get_number_field(&m->nonInstantWarpPos[2], "z");
            lua_pop(L, 1);
        }

        u8 characterIndex = 0;
        smlua_get_u8_field(&characterIndex, "character");
        if (characterIndex < CT_MAX) {
            m->character = &gCharacters[characterIndex];
            if (m->marioObj != NULL) {
                m->marioObj->header.gfx.sharedChild = gLoadedGraphNodes[m->character->modelId];
            }
        }

        smlua_get_u8_field(&m->wasNetworkVisible, "wasNetworkVisible");
        smlua_get_number_field(&m->minimumBoneY, "minimumBoneY");
        smlua_get_number_field(&m->curAnimOffset, "curAnimOffset");
    }

    return 1;
}

// END iteration 1

int smlua_set_mario_action(lua_State* L) {
    int index = lua_tointeger(L, -3);
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);
    lua_pushinteger(L, set_mario_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_set_jumping_action(lua_State* L) {
    int index = lua_tointeger(L, -3);
    u32 action = lua_tointeger(L, -2);
    u32 actionArg = lua_tointeger(L, -1);
    lua_pushinteger(L, set_jumping_action(&gMarioStates[index], action, actionArg));
    return 1;
}

int smlua_play_mario_sound(lua_State* L) {
    int index = lua_tointeger(L, -3);
    s32 actionSound = lua_tointeger(L, -2);
    s32 marioSound = lua_tointeger(L, -1);
    play_mario_sound(&gMarioStates[index], actionSound, marioSound);
    return 1;
}

int smlua_mario_set_forward_vel(lua_State* L) {
    int index = lua_tointeger(L, -2);
    f32 forwardVel = lua_tonumber(L, -1);
    mario_set_forward_vel(&gMarioStates[index], forwardVel);
    return 1;
}

int smlua_play_sound(lua_State* L) {
    s32 soundsBits = lua_tointeger(L, -4);
    f32 pos[3] = { lua_tonumber(L, -3), lua_tonumber(L, -2), lua_tonumber(L, -1) };
    extern void play_sound(s32 soundBits, f32 * pos);
    play_sound(soundsBits, pos);
    return 1;
}

int smlua_set_mario_animation(lua_State* L) {
    int index = lua_tointeger(L, -2);
    s32 targetAnimID = lua_tointeger(L, -1);
    lua_pushinteger(L, set_mario_animation(&gMarioStates[index], targetAnimID));
    return 1;
}

int smlua_update_sliding(lua_State* L) {
    int index = lua_tointeger(L, -2);
    f32 stopSpeed = lua_tonumber(L, -1);
    extern s32 update_sliding(struct MarioState* m, f32 stopSpeed);
    lua_pushinteger(L, update_sliding(&gMarioStates[index], stopSpeed));
    return 1;
}

int smlua_common_slide_action(lua_State* L) {
    int index = lua_tointeger(L, -4);
    u32 endAction = lua_tointeger(L, -3);
    u32 airAction = lua_tointeger(L, -2);
    u32 animation = lua_tointeger(L, -1);
    extern void common_slide_action(struct MarioState* m, u32 endAction, u32 airAction, s32 animation);
    common_slide_action(&gMarioStates[index], endAction, airAction, animation);
    return 1;
}

int smlua_set_anim_to_frame(lua_State* L) {
    int index = lua_tointeger(L, -2);
    s16 animFrame = lua_tonumber(L, -1);
    set_anim_to_frame(&gMarioStates[index], animFrame);
    return 1;
}

void smlua_bind_get_set(void) {
    lua_State* L = gLuaState;

    lua_pushcfunction(L, smlua_get_mario_state_field);
    lua_setglobal(L, "get_mario_state_field");

    lua_pushcfunction(L, smlua_set_mario_state_field);
    lua_setglobal(L, "set_mario_state_field");

    lua_pushcfunction(L, smlua_get_vec3s_field);
    lua_setglobal(L, "get_vec3s_field");

    lua_pushcfunction(L, smlua_set_vec3s_field);
    lua_setglobal(L, "set_vec3s_field");

    lua_pushcfunction(L, smlua_get_vec3f_field);
    lua_setglobal(L, "get_vec3f_field");

    lua_pushcfunction(L, smlua_set_vec3f_field);
    lua_setglobal(L, "set_vec3f_field");

    lua_pushcfunction(L, smlua_get_mario_state);
    lua_setglobal(L, "get_mario_state");

    lua_pushcfunction(L, smlua_set_mario_state);
    lua_setglobal(L, "set_mario_state");

    lua_pushcfunction(L, smlua_set_mario_action);
    lua_setglobal(L, "set_mario_action");

    lua_pushcfunction(L, smlua_set_jumping_action);
    lua_setglobal(L, "set_jumping_action");

    lua_pushcfunction(L, smlua_play_mario_sound);
    lua_setglobal(L, "play_mario_sound");

    lua_pushcfunction(L, smlua_mario_set_forward_vel);
    lua_setglobal(L, "mario_set_forward_vel");

    lua_pushcfunction(L, smlua_play_sound);
    lua_setglobal(L, "play_sound");

    lua_pushcfunction(L, smlua_set_mario_animation);
    lua_setglobal(L, "set_mario_animation");

    lua_pushcfunction(L, smlua_update_sliding);
    lua_setglobal(L, "update_sliding");

    lua_pushcfunction(L, smlua_common_slide_action);
    lua_setglobal(L, "common_slide_action");

    lua_pushcfunction(L, smlua_set_anim_to_frame);
    lua_setglobal(L, "set_anim_to_frame");

}