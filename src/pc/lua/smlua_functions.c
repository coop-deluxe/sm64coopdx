#include "smlua.h"
#include "smlua_cobject.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/mario_step.h"
#include "game/mario_actions_stationary.h"
#include "audio/external.h"
#include "object_fields.h"
#include "engine/math_util.h"
#include "engine/level_script.h"
#include "pc/djui/djui_hud_utils.h"
#include "include/level_misc_macros.h"
#include "include/macro_presets.h"
#include "utils/smlua_anim_utils.h"
#include "utils/smlua_collision_utils.h"

bool smlua_functions_valid_param_count(lua_State* L, int expected) {
    int top = lua_gettop(L);
    if (top != expected) {
        LOG_LUA_LINE("Improper param count: Expected %u, Received %u", expected, top);
        return false;
    }
    return true;
}

bool smlua_functions_valid_param_range(lua_State* L, int min, int max) {
    int top = lua_gettop(L);
    if (top < min || top > max) {
        LOG_LUA_LINE("Improper param count: Expected (%u - %u), Received %u", min, max, top);
        return false;
    }
    return true;
}

  //////////
 // misc //
//////////

int smlua_func_init_mario_after_warp(lua_State* L) {
    if (network_player_connected_count() >= 2) {
        LOG_LUA_LINE("init_mario_after_warp() can only be used in singleplayer");
        return 0;
    }

    if(!smlua_functions_valid_param_count(L, 0)) { return 0; }

    extern void init_mario_after_warp(void);
    init_mario_after_warp();

    return 1;
}

int smlua_func_initiate_warp(lua_State* L) {
    if(!smlua_functions_valid_param_count(L, 4)) { return 0; }

    s16 destLevel = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("initiate_warp: Failed to convert parameter 1"); return 0; }
    s16 destArea = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("initiate_warp: Failed to convert parameter 2"); return 0; }
    s16 destWarpNode = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("initiate_warp: Failed to convert parameter 3"); return 0; }
    s32 arg3 = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("initiate_warp: Failed to convert parameter 4"); return 0; }

    extern void initiate_warp(s16 destLevel, s16 destArea, s16 destWarpNode, s32 arg3);
    initiate_warp(destLevel, destArea, destWarpNode, arg3);

    return 1;
}

int smlua_func_reset_level(lua_State* L) {
    if (network_player_connected_count() >= 2) {
        LOG_LUA_LINE("reset_level() can only be used in singleplayer");
        return 0;
    }

    if(!smlua_functions_valid_param_count(L, 0)) { return 0; }

    gChangeLevel = gCurrLevelNum;

    return 1;
}

int smlua_func_network_init_object(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }

    struct Object* obj = smlua_to_cobject(L, 1, LOT_OBJECT);
    if (!gSmLuaConvertSuccess || obj == NULL) { LOG_LUA("network_init_object: Failed to convert parameter 1"); return 0; }

    bool standardSync = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("network_init_object: Failed to convert parameter 2"); return 0; }

    if (lua_type(L, 3) != LUA_TNIL && lua_type(L, 3) != LUA_TTABLE) {
        LOG_LUA_LINE("network_init_object() called with an invalid type for param 3: %u", lua_type(L, 3));
        return 0;
    }

    struct SyncObject* so = sync_object_init(obj, standardSync ? 4000.0f : SYNC_DISTANCE_ONLY_EVENTS);
    if (so == NULL) {
        LOG_LUA_LINE("network_init_object: Failed to allocate sync object.");
        return 0;
    }

    if (lua_type(L, 3) == LUA_TTABLE) {
        lua_pushnil(L);  // first key

        while (lua_next(L, 3) != 0) {
            // uses 'key' (at index -2) and 'value' (at index -1)
            if (lua_type(L, -1) != LUA_TSTRING) {
                LOG_LUA_LINE("Invalid type passed to network_init_object(): %u", lua_type(L, -1));
                lua_pop(L, 1); // pop value
                continue;
            }
            const char* fieldIdentifier = smlua_to_string(L, -1);
            if (!gSmLuaConvertSuccess) {
                LOG_LUA_LINE("Invalid field passed to network_init_object()");
                lua_pop(L, 1); // pop value
                continue;
            }

            struct LuaObjectField* data = smlua_get_object_field(LOT_OBJECT, fieldIdentifier);
            if (data == NULL) {
                data = smlua_get_custom_field(L, LOT_OBJECT, lua_gettop(L));
            }

            u8 lvtSize = 0;
            if ((data->valueType == LVT_U32) || (data->valueType == LVT_S32) || (data->valueType == LVT_F32)) { lvtSize = 32; }
            if ((data->valueType == LVT_U16) || (data->valueType == LVT_S16)) { lvtSize = 16; }
            if ((data->valueType == LVT_U8) || (data->valueType == LVT_S8)) { lvtSize = 8; }

            if (data == NULL || lvtSize == 0) {
                LOG_LUA_LINE("Invalid field passed to network_init_object(): %s", fieldIdentifier);
                lua_pop(L, 1); // pop value
                continue;
            }

            u8* field = ((u8*)(intptr_t)obj) + data->valueOffset;
            sync_object_init_field_with_size(obj, field, lvtSize);

            lua_pop(L, 1); // pop value
        }
        lua_pop(L, 1); // pop key
    }

    return 1;
}

int smlua_func_network_send_object(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    struct Object* obj = smlua_to_cobject(L, 1, LOT_OBJECT);
    if (!gSmLuaConvertSuccess || obj == NULL) { LOG_LUA("network_send_object: Failed to convert parameter 1"); return 0; }

    bool reliable = smlua_to_boolean(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("network_send_object: Failed to convert parameter 2"); return 0; }

    struct SyncObject* so = sync_object_get(obj->oSyncID);
    if (!so || so->o != obj) {
        LOG_LUA_LINE("network_send_object: Failed to retrieve sync object.");
        return 0;
    }

    network_send_object_reliability(obj, reliable);

    return 1;
}

int smlua_func_network_send(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }
    network_send_lua_custom(true);
    return 1;
}

int smlua_func_network_send_to(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    network_send_lua_custom(false);
    return 1;
}

  //////////////
 // Textures //
//////////////

int smlua_func_get_texture_info(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, -1) != LUA_TSTRING) {
        LOG_LUA_LINE("Invalid type passed to get_texture_info(): %u", lua_type(L, -1));
        lua_pop(L, 1); // pop value
        return 0;
    }

    struct TextureInfo texInfo = { 0 };
    const char* textureName = smlua_to_string(L, -1);
    if (!dynos_texture_get(textureName, &texInfo)) {
        LOG_LUA_LINE("Could not find texture info for '%s'", textureName);
        return 0;
    }

    lua_newtable(L);

    lua_pushstring(L, "texture");
    smlua_push_pointer(L, LVT_U8_P, texInfo.texture);
    lua_settable(L, -3);

    lua_pushstring(L, "bitSize");
    lua_pushinteger(L, texInfo.bitSize);
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushinteger(L, texInfo.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushinteger(L, texInfo.height);
    lua_settable(L, -3);

    lua_pushstring(L, "name");
    lua_pushstring(L, texInfo.name);
    lua_settable(L, -3);

    return 1;
}

int smlua_func_djui_hud_render_texture(lua_State* L) {
    if(!smlua_functions_valid_param_count(L, 5)) { return 0; }

    struct TextureInfo tmpTexInfo = { 0 };
    struct TextureInfo* texInfo = &tmpTexInfo;

    if (smlua_is_cobject(L, 1, LOT_TEXTUREINFO)) {
        texInfo = (struct TextureInfo*)smlua_to_cobject(L, 1, LOT_TEXTUREINFO);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1"); return 0; }
    } else {
        int top = lua_gettop(L);
        lua_pushvalue(L, 1);

        lua_pushstring(L, "texture");
        lua_gettable(L, top+1);
        tmpTexInfo.texture = smlua_to_cpointer(L, lua_gettop(L), LVT_U8_P);
        lua_pop(L, 1);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1's 'texture' field"); return 0; }

        tmpTexInfo.bitSize = smlua_get_integer_field(top+1, "bitSize");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1's 'bitSize' field"); return 0; }

        tmpTexInfo.width   = smlua_get_integer_field(top+1, "width");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1's 'width' field"); return 0; }

        tmpTexInfo.height  = smlua_get_integer_field(top+1, "height");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1's 'height' field"); return 0; }

        tmpTexInfo.name    = smlua_get_string_field(top+1, "name");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 1's 'name' field"); return 0; }

        lua_settop(L, top);
    }

    f32 x = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 2"); return 0; }
    f32 y = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 3"); return 0; }
    f32 scaleW = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 4"); return 0; }
    f32 scaleH = smlua_to_number(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture: Failed to convert parameter 5"); return 0; }

    djui_hud_render_texture_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, x, y, scaleW, scaleH);

    return 1;
}

int smlua_func_djui_hud_render_texture_tile(lua_State* L) {
    if(!smlua_functions_valid_param_count(L, 9)) { return 0; }

    struct TextureInfo tmpTexInfo = { 0 };
    struct TextureInfo* texInfo = &tmpTexInfo;

    if (smlua_is_cobject(L, 1, LOT_TEXTUREINFO)) {
        texInfo = (struct TextureInfo*)smlua_to_cobject(L, 1, LOT_TEXTUREINFO);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1"); return 0; }
    } else {
        int top = lua_gettop(L);
        lua_pushvalue(L, 1);

        lua_pushstring(L, "texture");
        lua_gettable(L, top+1);
        tmpTexInfo.texture = smlua_to_cpointer(L, lua_gettop(L), LVT_U8_P);
        lua_pop(L, 1);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1's 'texture' field"); return 0; }

        tmpTexInfo.bitSize = smlua_get_integer_field(top+1, "bitSize");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1's 'bitSize' field"); return 0; }

        tmpTexInfo.width   = smlua_get_integer_field(top+1, "width");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1's 'width' field"); return 0; }

        tmpTexInfo.height  = smlua_get_integer_field(top+1, "height");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1's 'height' field"); return 0; }

        tmpTexInfo.name    = smlua_get_string_field(top+1, "name");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 1's 'name' field"); return 0; }

        lua_settop(L, top);
    }

    f32 x = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 2"); return 0; }
    f32 y = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 3"); return 0; }
    f32 scaleW = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 4"); return 0; }
    f32 scaleH = smlua_to_number(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 5"); return 0; }
    f32 tileX = smlua_to_number(L, 6);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 6"); return 0; }
    f32 tileY = smlua_to_number(L, 7);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 7"); return 0; }
    f32 tileW = smlua_to_number(L, 8);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 8"); return 0; }
    f32 tileH = smlua_to_number(L, 9);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile: Failed to convert parameter 9"); return 0; }

    djui_hud_render_texture_tile_raw(texInfo->texture, texInfo->bitSize, texInfo->width, texInfo->height, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH);

    return 1;
}

int smlua_func_djui_hud_render_texture_interpolated(lua_State* L) {
    if(!smlua_functions_valid_param_count(L, 9)) { return 0; }

    struct TextureInfo tmpTexInfo = { 0 };
    struct TextureInfo* texInfo = &tmpTexInfo;

    if (smlua_is_cobject(L, 1, LOT_TEXTUREINFO)) {
        texInfo = (struct TextureInfo*)smlua_to_cobject(L, 1, LOT_TEXTUREINFO);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1"); return 0; }
    } else {
        int top = lua_gettop(L);
        lua_pushvalue(L, 1);

        lua_pushstring(L, "texture");
        lua_gettable(L, top+1);
        tmpTexInfo.texture = smlua_to_cpointer(L, lua_gettop(L), LVT_U8_P);
        lua_pop(L, 1);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1's 'texture' field"); return 0; }

        tmpTexInfo.bitSize = smlua_get_integer_field(top+1, "bitSize");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1's 'bitSize' field"); return 0; }

        tmpTexInfo.width   = smlua_get_integer_field(top+1, "width");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1's 'width' field"); return 0; }

        tmpTexInfo.height  = smlua_get_integer_field(top+1, "height");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1's 'height' field"); return 0; }

        tmpTexInfo.name    = smlua_get_string_field(top+1, "name");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 1's 'name' field"); return 0; }

        lua_settop(L, top);
    }

    f32 prevX = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 2"); return 0; }
    f32 prevY = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 3"); return 0; }
    f32 prevScaleW = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 4"); return 0; }
    f32 prevScaleH = smlua_to_number(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 5"); return 0; }
    f32 x = smlua_to_number(L, 6);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 6"); return 0; }
    f32 y = smlua_to_number(L, 7);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 7"); return 0; }
    f32 scaleW = smlua_to_number(L, 8);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 8"); return 0; }
    f32 scaleH = smlua_to_number(L, 9);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_interpolated: Failed to convert parameter 9"); return 0; }

    djui_hud_render_texture_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH);

    return 1;
}

int smlua_func_djui_hud_render_texture_tile_interpolated(lua_State* L) {
    if(!smlua_functions_valid_param_count(L, 13)) { return 0; }

    struct TextureInfo tmpTexInfo = { 0 };
    struct TextureInfo* texInfo = &tmpTexInfo;

    if (smlua_is_cobject(L, 1, LOT_TEXTUREINFO)) {
        texInfo = (struct TextureInfo*)smlua_to_cobject(L, 1, LOT_TEXTUREINFO);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1"); return 0; }
    } else {
        int top = lua_gettop(L);
        lua_pushvalue(L, 1);

        lua_pushstring(L, "texture");
        lua_gettable(L, top+1);
        tmpTexInfo.texture = smlua_to_cpointer(L, lua_gettop(L), LVT_U8_P);
        lua_pop(L, 1);
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1's 'texture' field"); return 0; }

        tmpTexInfo.bitSize = smlua_get_integer_field(top+1, "bitSize");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1's 'bitSize' field"); return 0; }

        tmpTexInfo.width   = smlua_get_integer_field(top+1, "width");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1's 'width' field"); return 0; }

        tmpTexInfo.height  = smlua_get_integer_field(top+1, "height");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1's 'height' field"); return 0; }

        tmpTexInfo.name    = smlua_get_string_field(top+1, "name");
        if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 1's 'name' field"); return 0; }

        lua_settop(L, top);
    }

    f32 prevX = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 2"); return 0; }
    f32 prevY = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 3"); return 0; }
    f32 prevScaleW = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 4"); return 0; }
    f32 prevScaleH = smlua_to_number(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 5"); return 0; }
    f32 x = smlua_to_number(L, 6);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 6"); return 0; }
    f32 y = smlua_to_number(L, 7);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 7"); return 0; }
    f32 scaleW = smlua_to_number(L, 8);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 8"); return 0; }
    f32 scaleH = smlua_to_number(L, 9);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 9"); return 0; }
    f32 tileX = smlua_to_number(L, 10);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 10"); return 0; }
    f32 tileY = smlua_to_number(L, 11);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 11"); return 0; }
    f32 tileW = smlua_to_number(L, 12);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 12"); return 0; }
    f32 tileH = smlua_to_number(L, 13);
    if (!gSmLuaConvertSuccess) { LOG_LUA("djui_hud_render_texture_tile_interpolated: Failed to convert parameter 13"); return 0; }

    djui_hud_render_texture_tile_interpolated(texInfo, prevX, prevY, prevScaleW, prevScaleH, x, y, scaleW, scaleH, tileX, tileY, tileW, tileH);

    return 1;
}

int smlua_func_texture_override_set(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    const char* textureName = smlua_to_string(L, 1);

    struct TextureInfo tmpOverrideTexInfo = { 0 };
    struct TextureInfo* overrideTexInfo = &tmpOverrideTexInfo;

    if (smlua_is_cobject(L, 2, LOT_TEXTUREINFO)) {
        overrideTexInfo = (struct TextureInfo*)smlua_to_cobject(L, 2, LOT_TEXTUREINFO);
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2"); return 0; }
    } else {
        int top = lua_gettop(L);
        lua_pushvalue(L, 2);

        lua_pushstring(L, "texture");
        lua_gettable(L, top+1);
        tmpOverrideTexInfo.texture = smlua_to_cpointer(L, lua_gettop(L), LVT_U8_P);
        lua_pop(L, 1);
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2's 'texture' field"); return 0; }

        tmpOverrideTexInfo.bitSize = smlua_get_integer_field(top+1, "bitSize");
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2's 'bitSize' field"); return 0; }

        tmpOverrideTexInfo.width   = smlua_get_integer_field(top+1, "width");
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2's 'width' field"); return 0; }

        tmpOverrideTexInfo.height  = smlua_get_integer_field(top+1, "height");
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2's 'height' field"); return 0; }

        tmpOverrideTexInfo.name  = smlua_get_string_field(top+1, "name");
        if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2's 'name' field"); return 0; }

        lua_settop(L, top);
    }

    dynos_texture_override_set(textureName, overrideTexInfo);

    return 1;
}

int smlua_func_texture_override_reset(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    const char* textureName = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_reset: Failed to convert parameter 1"); return 0; }

    dynos_texture_override_reset(textureName);

    return 1;
}

  ////////////////////////////////
 // level script preprocessing //
////////////////////////////////

struct LuaLevelScriptParse {
    int reference;
    struct Mod* mod;
};

struct LuaLevelScriptParse sLevelScriptParse = { 0 };

s32 smlua_func_level_script_parse_callback(u8 type, void *cmd) {
    u32 areaIndex, bhvId, bhvArgs;
    u32 *pAreaIndex = NULL, *pBhvId = NULL, *pBhvArgs = NULL;
    MacroObject *pMacroData = NULL;

    // Gather arguments
    switch (type) {

        // AREA
        case 0x1F: {
            areaIndex = (u8) dynos_level_cmd_get(cmd, 2);
            pAreaIndex = &areaIndex;
        } break;

        // OBJECT_WITH_ACTS
        case 0x24: {
            const BehaviorScript *bhv = (const BehaviorScript *) dynos_level_cmd_get(cmd, 20);
            if (bhv) {
                bhvId = (u32) get_id_from_behavior(bhv);
                bhvArgs = (u32) dynos_level_cmd_get(cmd, 16);
                pBhvId = &bhvId;
                pBhvArgs = &bhvArgs;
            }
        } break;

        // OBJECT_WITH_ACTS_EXT
        case 0x3F: {
            if (gLevelScriptModIndex != -1) {
                const char *bhvStr = dynos_level_get_token(dynos_level_cmd_get(cmd, 20));
                if (bhvStr) {
                    gSmLuaConvertSuccess = true;
                    bhvId = (u32) smlua_get_integer_mod_variable(gLevelScriptModIndex, bhvStr);
                    if (!gSmLuaConvertSuccess) {
                        gSmLuaConvertSuccess = true;
                        bhvId = (u32) smlua_get_any_integer_mod_variable(bhvStr);
                    }
                    if (gSmLuaConvertSuccess) {
                        bhvArgs = (u32) dynos_level_cmd_get(cmd, 16);
                        pBhvId = &bhvId;
                        pBhvArgs = &bhvArgs;
                    }
                }
            }
        } break;

        // OBJECT_WITH_ACTS_EXT2
        case 0x40: {
            if (gLevelScriptModIndex != -1) {
                const char *bhvStr = dynos_level_get_token(dynos_level_cmd_get(cmd, 24));
                if (bhvStr) {
                    gSmLuaConvertSuccess = true;
                    bhvId = (u32) smlua_get_integer_mod_variable(gLevelScriptModIndex, bhvStr);
                    if (!gSmLuaConvertSuccess) {
                        gSmLuaConvertSuccess = true;
                        bhvId = (u32) smlua_get_any_integer_mod_variable(bhvStr);
                    }
                    if (gSmLuaConvertSuccess) {
                        bhvArgs = (u32) dynos_level_cmd_get(cmd, 16);
                        pBhvId = &bhvId;
                        pBhvArgs = &bhvArgs;
                    }
                }
            }
        } break;

        // MACRO_OBJECTS
        case 0x39: {
            pMacroData = (MacroObject *) dynos_level_cmd_get(cmd, 4);
        } break;

        // None of the above
        default: return 0;
    }

    // Retrieve Lua state
    lua_State* L = gLuaState;
    if (L == NULL) { return 0; }
    struct LuaLevelScriptParse* preprocess = &sLevelScriptParse;
    lua_rawgeti(L, LUA_REGISTRYINDEX, preprocess->reference);

    // Push 'areaIndex'
    if (pAreaIndex) {
        lua_pushinteger(L, *pAreaIndex);
    } else {
        lua_pushnil(L);
    }

    // Push 'bhvData'
    if (pBhvId && pBhvArgs) {
        lua_newtable(L);
        lua_pushstring(L, "behavior");
        lua_pushinteger(L, *pBhvId);
        lua_settable(L, -3);
        lua_pushstring(L, "behaviorArg");
        lua_pushinteger(L, *pBhvArgs);
        lua_settable(L, -3);
    } else {
        lua_pushnil(L);
    }

    // Push 'macroBhvIds' and 'macroBhvArgs'
    if (pMacroData) {
        lua_newtable(L);
        s32 macroBhvIdsIdx = lua_gettop(gLuaState);
        lua_newtable(L);
        s32 macroBhvArgsIdx = lua_gettop(gLuaState);
        for (s32 i = 0; *pMacroData != MACRO_OBJECT_END(); pMacroData += 5, i++) {
            s32 presetId = (s32) ((pMacroData[0] & 0x1FF) - 0x1F);
            s32 presetParams = MacroObjectPresets[presetId].param;
            s32 objParams = (pMacroData[4] & 0xFF00) | (presetParams & 0x00FF);
            s32 bhvParams = ((objParams & 0x00FF) << 16) | (objParams & 0xFF00);
            lua_pushinteger(L, i);
            lua_pushinteger(L, get_id_from_behavior(MacroObjectPresets[presetId].behavior));
            lua_settable(L, macroBhvIdsIdx);
            lua_pushinteger(L, i);
            lua_pushinteger(L, bhvParams);
            lua_settable(L, macroBhvArgsIdx);
        }
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
    }

    // call the callback
    if (0 != smlua_call_hook(L, 4, 0, 0, preprocess->mod)) {
        LOG_LUA("Failed to call the callback behaviors: %u", type);
        return 0;
    }
    return 0;
}

void smlua_func_level_script_parse(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return; }

    lua_Integer levelNum = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("Invalid level script name");
        return;
    }

    struct LuaLevelScriptParse* preprocess = &sLevelScriptParse;
    preprocess->reference = LUA_NOREF;

    lua_pushvalue(L, 2);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);

    if (ref == -1) {
        LOG_LUA_LINE("Level Script Parse: %lld tried to parse using undefined function", levelNum);
        return;
    }

    preprocess->reference = ref;
    preprocess->mod = gLuaActiveMod;

    void *script = dynos_level_get_script(levelNum);
    if (script == NULL) {
        LOG_LUA("Failed to find script: %lld", levelNum);
        return;
    }
    s32 modIndex = dynos_level_get_mod_index(levelNum);

    // Back up current values
    LevelScript *currLevelScript = gLevelScriptActive;
    s32 currModIndex = gLevelScriptModIndex;

    // Parse script
    gLevelScriptActive = (LevelScript *) script;
    gLevelScriptModIndex = modIndex;
    dynos_level_parse_script(script, smlua_func_level_script_parse_callback);

    // Restore current values
    gLevelScriptActive = currLevelScript;
    gLevelScriptModIndex = currModIndex;
}

  ///////////////////////
 // custom animations //
///////////////////////

static u16 *smlua_to_u16_list(lua_State* L, int index, u32* length) {

    // Get number of values
    *length = lua_rawlen(L, index);
    if (!*length) { LOG_LUA("smlua_to_u16_list: Table must not be empty"); return NULL; }
    u16 *values = calloc(*length, sizeof(u16));

    // Retrieve values
    lua_pushnil(L);
    s32 top = lua_gettop(L);
    while (lua_next(L, index) != 0) {
        int indexKey = lua_gettop(L) - 1;
        int indexValue = lua_gettop(L) - 0;

        s32 key = smlua_to_integer(L, indexKey);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("smlua_to_u16_list: Failed to convert table key");
            free(values);
            return 0;
        }

        u16 value = smlua_to_integer(L, indexValue);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("smlua_to_u16_list: Failed to convert table value");
            free(values);
            return 0;
        }

        values[key - 1] = value;
        lua_settop(L, top);
    }
    lua_settop(L, top);
    return values;
}

int smlua_func_smlua_anim_util_register_animation(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 8)) { return 0; }

    const char *name = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'name'"); return 0; }

    s16 flags = smlua_to_integer(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'flags'"); return 0; }

    s16 animYTransDivisor = smlua_to_integer(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'animYTransDivisor'"); return 0; }

    s16 startFrame = smlua_to_integer(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'startFrame'"); return 0; }

    s16 loopStart = smlua_to_integer(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'loopStart'"); return 0; }

    s16 loopEnd = smlua_to_integer(L, 6);
    if (!gSmLuaConvertSuccess) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'loopEnd'"); return 0; }

    u32 valuesLength = 0;
    u16 *values = (u16 *) smlua_to_u16_list(L, 7, &valuesLength);
    if (!values) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'values'"); return 0; }

    u32 indexLength = 0;
    u16 *index = (u16 *) smlua_to_u16_list(L, 8, &indexLength);
    if (!index) { LOG_LUA("smlua_anim_util_register_animation: Failed to convert parameter 'index'"); free(values); return 0; }

    smlua_anim_util_register_animation(name, flags, animYTransDivisor, startFrame, loopStart, loopEnd, values, valuesLength, index, indexLength);

    return 1;
}

  /////////////
 // console //
/////////////

int smlua_func_log_to_console(lua_State* L) {
    if (!smlua_functions_valid_param_range(L, 1, 2)) { return 0; }

    int paramCount = lua_gettop(L);

    const char* message = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("log_to_console: Failed to convert parameter 1 for function"); return 0; }

    enum ConsoleMessageLevel level = CONSOLE_MESSAGE_INFO;
    if (paramCount >= 2) {
        level = smlua_to_integer(L, 2);
        if (!gSmLuaConvertSuccess) { LOG_LUA("log_to_console: Failed to convert parameter 2 for function"); return 0; }
    }

    djui_console_message_create(message, level);

    return 1;
}

  ////////////////////
 // scroll targets //
////////////////////

int smlua_func_add_scroll_target(lua_State* L) {
    // add_scroll_target used to require offset and size of the vertex buffer to be used
    if (!smlua_functions_valid_param_range(L, 2, 4)) { return 0; }
    int paramCount = lua_gettop(L);

    u32 index = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("add_scroll_target: Failed to convert parameter 1 for function"); return 0; }
    const char* name = smlua_to_string(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("add_scroll_target: Failed to convert parameter 2 for function"); return 0; }

    // If the offset and size parameters are provided, use them, although they aren't required.
    u32 offset = 0;
    u32 size = 0;
    switch (paramCount) {
        case 4:
            size = smlua_to_integer(L, 4);
        case 3:
            offset = smlua_to_integer(L, 3);
            break;
    }

    dynos_add_scroll_target(index, name, offset, size);

    return 1;
}

  /////////////
 // raycast //
/////////////

int smlua_func_collision_find_surface_on_ray(lua_State* L) {
    if (!smlua_functions_valid_param_range(L, 6, 7)) { return 0; }
    int paramCount = lua_gettop(L);

    f32 startX = smlua_to_number(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 1"); return 0; }
    f32 startY = smlua_to_number(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 2"); return 0; }
    f32 startZ = smlua_to_number(L, 3);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 3"); return 0; }
    f32 dirX = smlua_to_number(L, 4);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 4"); return 0; }
    f32 dirY = smlua_to_number(L, 5);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 5"); return 0; }
    f32 dirZ = smlua_to_number(L, 6);
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 6"); return 0; }
    f32 precision = paramCount == 7 ? smlua_to_number(L, 7) : 3.0f;
    if (!gSmLuaConvertSuccess) { LOG_LUA("collision_find_surface_on_ray: Failed to convert parameter 7"); return 0; }

    smlua_push_object(L, LOT_RAYINTERSECTIONINFO, collision_find_surface_on_ray(startX, startY, startZ, dirX, dirY, dirZ, precision));

    return 1;
}

  //////////
 // bind //
//////////

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "init_mario_after_warp", smlua_func_init_mario_after_warp);
    smlua_bind_function(L, "initiate_warp", smlua_func_initiate_warp);
    smlua_bind_function(L, "network_init_object", smlua_func_network_init_object);
    smlua_bind_function(L, "network_send_object", smlua_func_network_send_object);
    smlua_bind_function(L, "reset_level", smlua_func_reset_level);
    smlua_bind_function(L, "network_send", smlua_func_network_send);
    smlua_bind_function(L, "network_send_to", smlua_func_network_send_to);
    smlua_bind_function(L, "get_texture_info", smlua_func_get_texture_info);
    smlua_bind_function(L, "djui_hud_render_texture", smlua_func_djui_hud_render_texture);
    smlua_bind_function(L, "djui_hud_render_texture_tile", smlua_func_djui_hud_render_texture_tile);
    smlua_bind_function(L, "djui_hud_render_texture_interpolated", smlua_func_djui_hud_render_texture_interpolated);
    smlua_bind_function(L, "djui_hud_render_texture_tile_interpolated", smlua_func_djui_hud_render_texture_tile_interpolated);
    smlua_bind_function(L, "texture_override_set", smlua_func_texture_override_set);
    smlua_bind_function(L, "texture_override_reset", smlua_func_texture_override_reset);
    smlua_bind_function(L, "level_script_parse", smlua_func_level_script_parse);
    smlua_bind_function(L, "smlua_anim_util_register_animation", smlua_func_smlua_anim_util_register_animation);
    smlua_bind_function(L, "log_to_console", smlua_func_log_to_console);
    smlua_bind_function(L, "add_scroll_target", smlua_func_add_scroll_target);
    smlua_bind_function(L, "collision_find_surface_on_ray", smlua_func_collision_find_surface_on_ray);
}
