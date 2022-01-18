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
    LVT_CONTROLLER,
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

#define LUA_MARIO_STATE_FIELD_COUNT 56
static struct LuaObjectField sMarioStateFields[LUA_MARIO_STATE_FIELD_COUNT] = {
    { "playerIndex",              LVT_U16,        offsetof(struct MarioState, playerIndex)             , true  },
    { "input",                    LVT_U16,        offsetof(struct MarioState, input)                   , false },
    { "flags",                    LVT_U32,        offsetof(struct MarioState, flags)                   , false },
    { "particleFlags",            LVT_U32,        offsetof(struct MarioState, particleFlags)           , false },
    { "action",                   LVT_U32,        offsetof(struct MarioState, action)                  , false },
    { "prevAction",               LVT_U32,        offsetof(struct MarioState, prevAction)              , false },
    { "terrainSoundAddend",       LVT_U32,        offsetof(struct MarioState, terrainSoundAddend)      , false },
    { "actionState",              LVT_U16,        offsetof(struct MarioState, actionState)             , false },
    { "actionTimer",              LVT_U16,        offsetof(struct MarioState, actionTimer)             , false },
    { "actionArg",                LVT_U32,        offsetof(struct MarioState, actionArg)               , false },
    { "intendedMag",              LVT_F32,        offsetof(struct MarioState, intendedMag)             , false },
    { "intendedYaw",              LVT_S16,        offsetof(struct MarioState, intendedYaw)             , false },
    { "invincTimer",              LVT_S16,        offsetof(struct MarioState, invincTimer)             , false },
    { "framesSinceA",             LVT_U8,         offsetof(struct MarioState, framesSinceA)            , false },
    { "framesSinceB",             LVT_U8,         offsetof(struct MarioState, framesSinceB)            , false },
    { "wallKickTimer",            LVT_U8,         offsetof(struct MarioState, wallKickTimer)           , false },
    { "doubleJumpTimer",          LVT_U8,         offsetof(struct MarioState, doubleJumpTimer)         , false },
    { "faceAngle",                LVT_VEC3S,      offsetof(struct MarioState, faceAngle)               , true  },
    { "angleVel",                 LVT_VEC3S,      offsetof(struct MarioState, angleVel)                , true  },
    { "slideYaw",                 LVT_S16,        offsetof(struct MarioState, slideYaw)                , false },
    { "twirlYaw",                 LVT_S16,        offsetof(struct MarioState, twirlYaw)                , false },
    { "pos",                      LVT_VEC3F,      offsetof(struct MarioState, pos)                     , true  },
    { "vel",                      LVT_VEC3F,      offsetof(struct MarioState, vel)                     , true  },
    { "forwardVel",               LVT_F32,        offsetof(struct MarioState, forwardVel)              , false },
    { "slideVelX",                LVT_F32,        offsetof(struct MarioState, slideVelX)               , false },
    { "slideVelZ",                LVT_F32,        offsetof(struct MarioState, slideVelZ)               , false },
    { "ceilHeight",               LVT_F32,        offsetof(struct MarioState, ceilHeight)              , false },
    { "floorHeight",              LVT_F32,        offsetof(struct MarioState, floorHeight)             , false },
    { "floorAngle",               LVT_S16,        offsetof(struct MarioState, floorAngle)              , false },
    { "waterLevel",               LVT_S16,        offsetof(struct MarioState, waterLevel)              , false },
    { "controller",               LVT_CONTROLLER, offsetof(struct MarioState, controller)              , true  },
    { "collidedObjInteractTypes", LVT_U32,        offsetof(struct MarioState, collidedObjInteractTypes), false },
    { "numCoins",                 LVT_S16,        offsetof(struct MarioState, numCoins)                , false },
    { "numStars",                 LVT_S16,        offsetof(struct MarioState, numStars)                , false },
    { "mechani",                  LVT_S8,         offsetof(struct MarioState, numKeys)                 , false },
    { "numLives",                 LVT_S8,         offsetof(struct MarioState, numLives)                , false },
    { "health",                   LVT_S16,        offsetof(struct MarioState, health)                  , false },
    { "unkB0",                    LVT_S16,        offsetof(struct MarioState, unkB0)                   , false },
    { "hurtCounter",              LVT_U8,         offsetof(struct MarioState, hurtCounter)             , false },
    { "healCounter",              LVT_U8,         offsetof(struct MarioState, healCounter)             , false },
    { "squishTimer",              LVT_U8,         offsetof(struct MarioState, squishTimer)             , false },
    { "fadeWarpOpacity",          LVT_U8,         offsetof(struct MarioState, fadeWarpOpacity)         , false },
    { "capTimer",                 LVT_U16,        offsetof(struct MarioState, capTimer)                , false },
    { "prevNumStarsForDialog",    LVT_S16,        offsetof(struct MarioState, prevNumStarsForDialog)   , false },
    { "peakHeight",               LVT_F32,        offsetof(struct MarioState, peakHeight)              , false },
    { "quicksandDepth",           LVT_F32,        offsetof(struct MarioState, quicksandDepth)          , false },
    { "unkC4",                    LVT_F32,        offsetof(struct MarioState, unkC4)                   , false },
    { "currentRoom",              LVT_S16,        offsetof(struct MarioState, currentRoom)             , false },
    { "isSnoring",                LVT_U8,         offsetof(struct MarioState, isSnoring)               , false },
    { "freeze",                   LVT_U8,         offsetof(struct MarioState, freeze)                  , false },
    { "splineKeyframeFraction",   LVT_F32,        offsetof(struct MarioState, splineKeyframeFraction)  , false },
    { "splineState",              LVT_S32,        offsetof(struct MarioState, splineState)             , false },
    { "nonInstantWarpPos",        LVT_VEC3F,      offsetof(struct MarioState, nonInstantWarpPos)       , true  },
    { "wasNetworkVisible",        LVT_U8,         offsetof(struct MarioState, wasNetworkVisible)       , false },
    { "minimumBoneY",             LVT_F32,        offsetof(struct MarioState, minimumBoneY)            , false },
    { "curAnimOffset",            LVT_F32,        offsetof(struct MarioState, curAnimOffset)           , false },
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
        struct MarioAnimation *animation;
        struct Object* heldByObj;
        struct Object* bubbleObj;
        Vec4s* splineKeyframe;
        struct Character* character;
    */
};

#define LUA_CONTROLLER_FIELD_COUNT 10
static struct LuaObjectField sControllerFields[LUA_CONTROLLER_FIELD_COUNT] = {
    { "rawStickX",      LVT_S16,          offsetof(struct Controller, rawStickX),      false },
    { "rawStickY",      LVT_S16,          offsetof(struct Controller, rawStickY),      false },
    { "stickX",         LVT_F32,          offsetof(struct Controller, stickX),         false },
    { "stickY",         LVT_F32,          offsetof(struct Controller, stickY),         false },
    { "stickMag",       LVT_F32,          offsetof(struct Controller, stickMag),       false },
    { "buttonDown",     LVT_U16,          offsetof(struct Controller, buttonDown),     false },
    { "buttonPressed",  LVT_U16,          offsetof(struct Controller, buttonPressed),  false },
  //{ "statusData",     LVT_OSCONTSTATUS, offsetof(struct Controller, statusData),     false },
  //{ "controllerData", LVT_OSCONTPAD,    offsetof(struct Controller, controllerData), false },
    { "port",           LVT_S32,          offsetof(struct Controller, port),           false },
    { "extStickX",      LVT_S16,          offsetof(struct Controller, extStickX),      false },
    { "extStickY",      LVT_S16,          offsetof(struct Controller, extStickY),      false },
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
    { LOT_CONTROLLER,  sControllerFields, LUA_CONTROLLER_FIELD_COUNT  },
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
        case LVT_U8:         lua_pushinteger(L, *(u8* )p);       break;
        case LVT_U16:        lua_pushinteger(L, *(u16*)p);       break;
        case LVT_U32:        lua_pushinteger(L, *(u32*)p);       break;
        case LVT_S8:         lua_pushinteger(L, *(s8* )p);       break;
        case LVT_S16:        lua_pushinteger(L, *(s16*)p);       break;
        case LVT_S32:        lua_pushinteger(L, *(s32*)p);       break;
        case LVT_F32:        lua_pushnumber( L, *(f32*)p);       break;
        case LVT_VEC3S:      smlua_push_object(L, LOT_VEC3S, p); break;
        case LVT_VEC3F:      smlua_push_object(L, LOT_VEC3F, p); break;
        case LVT_CONTROLLER: smlua_push_object(L, LOT_CONTROLLER, *(struct Controller**)p); break;
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

void smlua_bind_cobject(void) {
    lua_State* L = gLuaState;

    lua_pushcfunction(L, smlua__get_field);
    lua_setglobal(L, "_get_field");

    lua_pushcfunction(L, smlua__set_field);
    lua_setglobal(L, "_set_field");

}