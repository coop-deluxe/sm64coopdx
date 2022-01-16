#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "smlua.h"

#include "game\level_update.h"
#include "object_fields.h"

static lua_State* sLuaState = NULL;

static void smlua_dump_stack(lua_State* L) {
    int top = lua_gettop(L);
    for (int i = 1; i <= top; i++) {
        printf("%d\t%s\t", i, luaL_typename(L, i));
        switch (lua_type(L, i)) {
        case LUA_TNUMBER:
            printf("%g\n", lua_tonumber(L, i));
            break;
        case LUA_TSTRING:
            printf("%s\n", lua_tostring(L, i));
            break;
        case LUA_TBOOLEAN:
            printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
            break;
        case LUA_TNIL:
            printf("%s\n", "nil");
            break;
        default:
            printf("%p\n", lua_topointer(L, i));
            break;
        }
    }
}

static void smlua_push_integer_field(int val, char* name) {
    int t = lua_gettop(sLuaState);
    lua_pushinteger(sLuaState, val);
    lua_setfield(sLuaState, t, name);
}

static void smlua_push_number_field(float val, char* name) {
    int t = lua_gettop(sLuaState);
    lua_pushnumber(sLuaState, val);
    lua_setfield(sLuaState, t, name);
}

static void smlua_get_u8_field(u8* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_u16_field(u16* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_u32_field(u32* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_s8_field(s8* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_s16_field(s16* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_s32_field(s32* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tointeger(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

static void smlua_get_number_field(float* val, char* name) {
    lua_getfield(sLuaState, -1, name);
    *val = lua_tonumber(sLuaState, -1);
    lua_pop(sLuaState, 1);
}

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
        //struct Controller* controller;
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

        //struct Character* character;

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
        smlua_get_u16_field(&m->playerIndex, "playerIndex");
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
            smlua_get_number_field(&m->pos[0], "x");
            smlua_get_number_field(&m->pos[1], "y");
            smlua_get_number_field(&m->pos[2], "z");
            if (m->marioObj != NULL) {
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
        //struct Controller* controller;
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

        //struct Character* character;

        smlua_get_u8_field(&m->wasNetworkVisible, "wasNetworkVisible");
        smlua_get_number_field(&m->minimumBoneY, "minimumBoneY");
        smlua_get_number_field(&m->curAnimOffset, "curAnimOffset");
    }

    return 1;
}

void smlua_init(void) {
    sLuaState = luaL_newstate();
    lua_State* L = sLuaState;
    luaL_openlibs(L);

    lua_pushcfunction(L, smlua_get_mario_state);
    lua_setglobal(L, "get_mario_state");

    lua_pushcfunction(L, smlua_set_mario_state);
    lua_setglobal(L, "set_mario_state");
}

void smlua_run(void) {
    lua_State* L = sLuaState;
    // Our Lua code, it simply prints a Hello, World message
    char* code = "local m = get_mario_state(0)\nm.pos.y=600\nset_mario_state(0, m)";

    // Here we load the string and use lua_pcall for run the code
    if (luaL_loadstring(L, code) == LUA_OK) {
        if (lua_pcall(L, 0, 0, 0) == LUA_OK) {
            // If it was executed successfuly we 
            // remove the code from the stack
            lua_pop(L, lua_gettop(L));
        }
    }
}

void smlua_shutdown(void) {
    lua_State* L = sLuaState;
    lua_close(L);
}
