#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/mario_step.h"
#include "game/mario_actions_stationary.h"
#include "audio/external.h"
#include "object_fields.h"
#include "engine/math_util.h"

  //////////
 // misc //
//////////

int smlua_func_sins(lua_State* L) {
    f32 x = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, sins(x));
    return 1;
}

int smlua_func_coss(lua_State* L) {
    f32 x = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushnumber(L, coss(x));
    return 1;
}

int smlua_func_atan2s(lua_State* L) {
    f32 y = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { return 0; }
    f32 x = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { return 0; }

    lua_pushinteger(L, atan2s(y, x));
    return 1;
}

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "sins", smlua_func_sins);
    smlua_bind_function(L, "coss", smlua_func_coss);
    smlua_bind_function(L, "atan2s", smlua_func_atan2s);
}