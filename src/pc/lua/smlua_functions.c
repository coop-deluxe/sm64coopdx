#include "smlua.h"
#include "smlua_cobject.h"

#include <PR/gbi.h>

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
#include "pc/utils/misc.h"
#include "include/level_misc_macros.h"
#include "include/macro_presets.h"
#include "utils/smlua_anim_utils.h"
#include "utils/smlua_collision_utils.h"
#include "game/hardcoded.h"
#include "gfx_symbols.h"
#include "include/macros.h"

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
        LOG_LUA_LINE("network_init_object() called with an invalid type for param 3: %s", luaL_typename(L, 3));
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
                LOG_LUA_LINE("Invalid type passed to network_init_object(): %s", luaL_typename(L, -1));
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

int smlua_func_set_exclamation_box_contents(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, 1) != LUA_TTABLE) {
        LOG_LUA_LINE("Invalid type passed to set_exclamation_box(): %s", luaL_typename(L, -1));
        return 0;
    }

    struct ExclamationBoxContent exclamationBoxNewContents[EXCLAMATION_BOX_MAX_SIZE];

    u8 exclamationBoxIndex = 0;
    lua_pushnil(L); // Initial pop
    while (lua_next(L, 1)) /* Main table index */ {
        if (lua_type(L, 3) != LUA_TTABLE) {
            LOG_LUA_LINE("set_exclamation_box: Subtable is not a table (Subtable %u)", exclamationBoxIndex);
            return 0;
        }

        lua_pushnil(L); // Subtable initial pop
        bool confirm[] = { false, false, false, false, false }; /* id, unused, firstByte, model, behavior */
        while (lua_next(L, 3)) /* Subtable index */ {
            // key is index -2, value is index -1
            const char* key = smlua_to_string(L, -2);
            if (!gSmLuaConvertSuccess) {
                LOG_LUA("set_exclamation_box: Failed to convert subtable key");
                return 0;
            }

            s32 value = smlua_to_integer(L, -1);
            if (!gSmLuaConvertSuccess) {
                LOG_LUA("set_exclamation_box: Failed to convert subtable value");
                return 0;
            }

            // Fill fields
            if (strcmp(key, "id") == 0) { exclamationBoxNewContents[exclamationBoxIndex].id = value; confirm[0] = true; }
            else if (strcmp(key, "unused") == 0) { exclamationBoxNewContents[exclamationBoxIndex].unused = value; confirm[1] = true; }
            else if (strcmp(key, "firstByte") == 0) { exclamationBoxNewContents[exclamationBoxIndex].firstByte = value; confirm[2] = true; }
            else if (strcmp(key, "model") == 0) { exclamationBoxNewContents[exclamationBoxIndex].model = value; confirm[3] = true; }
            else if (strcmp(key, "behavior") == 0) { exclamationBoxNewContents[exclamationBoxIndex].behavior = value; confirm[4] = true; }
            else {
                LOG_LUA_LINE_WARNING("set_exclamation_box: Invalid key passed (Subtable %d)", exclamationBoxIndex);
            }

            lua_pop(L, 1); // Pop value
        }
        // Check if the fields have been filled
        if (!(confirm[0]) || !(confirm[3]) || !(confirm[4])) {
            LOG_LUA("set_exclamation_box: A critical component of a content (id, model, or behavior) has not been set (Subtable %d)", exclamationBoxIndex);
            return 0;
        }
        if (!(confirm[1])) { exclamationBoxNewContents[exclamationBoxIndex].unused = 0; }
        if (!(confirm[2])) { exclamationBoxNewContents[exclamationBoxIndex].firstByte = 0; }

        if (++exclamationBoxIndex == EXCLAMATION_BOX_MAX_SIZE) { // There is an edge case where the 254th element will warn even though it works just fine
            // Immediately exit if at risk for out of bounds array access.
            lua_pop(L, 1);
            LOG_LUA_LINE_WARNING("set_exclamation_box: Too many items have been set for the exclamation box. Some content spawns may be lost.");
            break;
        }
        lua_pop(L, 1); // Pop subtable
    }

    memcpy(gExclamationBoxContents, exclamationBoxNewContents, sizeof(struct ExclamationBoxContent) * exclamationBoxIndex);
    gExclamationBoxSize = exclamationBoxIndex;

    return 1;
}

int smlua_func_get_exclamation_box_contents(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 0)) { return 0; }

    lua_newtable(L); // Index 1

    for (u8 i = 0; i < gExclamationBoxSize; i++) {
        lua_pushinteger(L, i); // Index 2
        lua_newtable(L); // Index 3

        lua_pushstring(L, "id");
        lua_pushinteger(L, gExclamationBoxContents[i].id);
        lua_settable(L, -3);

        lua_pushstring(L, "unused");
        lua_pushinteger(L, gExclamationBoxContents[i].unused);
        lua_settable(L, -3);

        lua_pushstring(L, "firstByte");
        lua_pushinteger(L, gExclamationBoxContents[i].firstByte);
        lua_settable(L, -3);

        lua_pushstring(L, "model");
        lua_pushinteger(L, gExclamationBoxContents[i].model);
        lua_settable(L, -3);

        lua_pushstring(L, "behavior");
        lua_pushinteger(L, gExclamationBoxContents[i].behavior);
        lua_settable(L, -3);

        lua_settable(L, 1); // Insert the subtable into the main table
    }

    return 1;
}

  //////////////
 // Textures //
//////////////

int smlua_func_get_texture_info(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, -1) != LUA_TSTRING) {
        LOG_LUA_LINE("Invalid type passed to get_texture_info(): %s", luaL_typename(L, -1));
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
    smlua_push_pointer(L, LVT_U8_P, texInfo.texture, NULL);
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
    if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 1"); return 0; }

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
    u32 areaIndex, bhvId, bhvArgs, bhvModelId;
    s16 bhvPosX, bhvPosY, bhvPosZ;
    s32 bhvPitch, bhvYaw, bhvRoll;
    bool area = false, bhv = false;
    MacroObject *macroData = NULL;

    // Gather arguments
    switch (type) {

        // AREA
        case 0x1F: {
            areaIndex = dynos_level_cmd_get(cmd, 2);
            area = true;
        } break;

        // OBJECT, OBJECT_WITH_ACTS
        case 0x24: {
            const BehaviorScript *bhvPtr = (const BehaviorScript *) dynos_level_cmd_get(cmd, 20);
            if (bhvPtr) {
                bhvId = get_id_from_behavior(bhvPtr);
                if (bhvId == id_bhv1Up) {
                    bhvId = get_id_from_vanilla_behavior(bhvPtr); // for behaviors with no id in the script (e.g. bhvInstantActiveWarp)
                }
                bhvArgs = dynos_level_cmd_get(cmd, 16);
                bhvModelId = dynos_level_cmd_get(cmd, 3);
                bhvPosX = dynos_level_cmd_get(cmd, 4);
                bhvPosY = dynos_level_cmd_get(cmd, 6);
                bhvPosZ = dynos_level_cmd_get(cmd, 8);
                bhvPitch = (dynos_level_cmd_get(cmd, 10) * 0x8000) / 180;
                bhvYaw   = (dynos_level_cmd_get(cmd, 12) * 0x8000) / 180;
                bhvRoll  = (dynos_level_cmd_get(cmd, 14) * 0x8000) / 180;
                bhv = true;
            }
        } break;

        // OBJECT_EXT, OBJECT_WITH_ACTS_EXT
        case 0x3F: {
            if (gLevelScriptModIndex != -1) {
                const char *bhvStr = dynos_level_get_token(dynos_level_cmd_get(cmd, 20));
                if (bhvStr) {
                    gSmLuaConvertSuccess = true;
                    bhvId = smlua_get_integer_mod_variable(gLevelScriptModIndex, bhvStr);
                    if (!gSmLuaConvertSuccess) {
                        gSmLuaConvertSuccess = true;
                        bhvId = smlua_get_any_integer_mod_variable(bhvStr);
                    }
                    if (gSmLuaConvertSuccess) {
                        bhvArgs = dynos_level_cmd_get(cmd, 16);
                        bhvModelId = dynos_level_cmd_get(cmd, 3);
                        bhvPosX = dynos_level_cmd_get(cmd, 4);
                        bhvPosY = dynos_level_cmd_get(cmd, 6);
                        bhvPosZ = dynos_level_cmd_get(cmd, 8);
                        bhvPitch = (dynos_level_cmd_get(cmd, 10) * 0x8000) / 180;
                        bhvYaw   = (dynos_level_cmd_get(cmd, 12) * 0x8000) / 180;
                        bhvRoll  = (dynos_level_cmd_get(cmd, 14) * 0x8000) / 180;
                        bhv = true;
                    }
                }
            }
        } break;

        // OBJECT_EXT2, OBJECT_WITH_ACTS_EXT2
        case 0x40: {
            if (gLevelScriptModIndex != -1) {
                const char *bhvStr = dynos_level_get_token(dynos_level_cmd_get(cmd, 24));
                if (bhvStr) {
                    gSmLuaConvertSuccess = true;
                    bhvId = smlua_get_integer_mod_variable(gLevelScriptModIndex, bhvStr);
                    if (!gSmLuaConvertSuccess) {
                        gSmLuaConvertSuccess = true;
                        bhvId = smlua_get_any_integer_mod_variable(bhvStr);
                    }
                    if (gSmLuaConvertSuccess) {
                        bhvArgs = dynos_level_cmd_get(cmd, 16);
                        bhvModelId = dynos_level_cmd_get(cmd, 3);
                        bhvPosX = dynos_level_cmd_get(cmd, 4);
                        bhvPosY = dynos_level_cmd_get(cmd, 6);
                        bhvPosZ = dynos_level_cmd_get(cmd, 8);
                        bhvPitch = (dynos_level_cmd_get(cmd, 10) * 0x8000) / 180;
                        bhvYaw   = (dynos_level_cmd_get(cmd, 12) * 0x8000) / 180;
                        bhvRoll  = (dynos_level_cmd_get(cmd, 14) * 0x8000) / 180;
                        bhv = true;
                    }
                }
            }
        } break;

        // MACRO_OBJECTS
        case 0x39: {
            macroData = (MacroObject *) dynos_level_cmd_get(cmd, 4);
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
    if (area) {
        lua_pushinteger(L, areaIndex);
    } else {
        lua_pushnil(L);
    }

    // Push 'bhvData'
    if (bhv) {
        lua_newtable(L);
        smlua_push_integer_field(-2, "behavior", bhvId);
        smlua_push_integer_field(-2, "behaviorArg", bhvArgs);
        smlua_push_integer_field(-2, "model", bhvModelId);
        smlua_push_integer_field(-2, "posX", bhvPosX);
        smlua_push_integer_field(-2, "posY", bhvPosY);
        smlua_push_integer_field(-2, "posZ", bhvPosZ);
        smlua_push_integer_field(-2, "pitch", bhvPitch);
        smlua_push_integer_field(-2, "yaw", bhvYaw);
        smlua_push_integer_field(-2, "roll", bhvRoll);
    } else {
        lua_pushnil(L);
    }

    // Push 'macroBhvIds' and 'macroBhvArgs' and 'macroBhvModels'
    if (macroData) {
        lua_newtable(L);
        s32 macroBhvIdsIdx = lua_gettop(L);
        lua_newtable(L);
        s32 macroBhvArgsIdx = lua_gettop(L);
        lua_newtable(L);
        s32 macroBhvModelsIdx = lua_gettop(L);
        for (s32 i = 0; *macroData != MACRO_OBJECT_END(); macroData += 5, i++) {
            s32 presetId = (s32) ((macroData[0] & 0x1FF) - 0x1F);
            s32 presetParams = MacroObjectPresets[presetId].param;
            s32 objParams = (macroData[4] & 0xFF00) | (presetParams & 0x00FF);
            s32 bhvParams = ((objParams & 0x00FF) << 16) | (objParams & 0xFF00);
            lua_pushinteger(L, i);
            lua_pushinteger(L, get_id_from_behavior(MacroObjectPresets[presetId].behavior));
            lua_settable(L, macroBhvIdsIdx);
            lua_pushinteger(L, i);
            lua_pushinteger(L, bhvParams);
            lua_settable(L, macroBhvArgsIdx);
            lua_pushinteger(L, i);
            lua_pushinteger(L, MacroObjectPresets[presetId].model);
            lua_settable(L, macroBhvModelsIdx);
        }
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
    }

    // call the callback
    if (0 != smlua_call_hook(L, 5, 0, 0, preprocess->mod)) {
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

    smlua_push_object(L, LOT_RAYINTERSECTIONINFO, collision_find_surface_on_ray(startX, startY, startZ, dirX, dirY, dirZ, precision), NULL);

    return 1;
}

  ////////////////
 // graph node //
////////////////

typedef struct { s16 type; u16 lot; } GraphNodeLot;
static GraphNodeLot graphNodeLots[23] = {
    { GRAPH_NODE_TYPE_ANIMATED_PART, LOT_GRAPHNODEANIMATEDPART },
    { GRAPH_NODE_TYPE_BACKGROUND, LOT_GRAPHNODEBACKGROUND },
    { GRAPH_NODE_TYPE_BILLBOARD, LOT_GRAPHNODEBILLBOARD },
    { GRAPH_NODE_TYPE_CAMERA, LOT_GRAPHNODECAMERA },
    { GRAPH_NODE_TYPE_CULLING_RADIUS, LOT_GRAPHNODECULLINGRADIUS },
    { GRAPH_NODE_TYPE_DISPLAY_LIST, LOT_GRAPHNODEDISPLAYLIST },
    { GRAPH_NODE_TYPE_FUNCTIONAL, LOT_FNGRAPHNODE },
    { GRAPH_NODE_TYPE_GENERATED_LIST, LOT_GRAPHNODEGENERATED },
    { GRAPH_NODE_TYPE_HELD_OBJ, LOT_GRAPHNODEHELDOBJECT },
    { GRAPH_NODE_TYPE_LEVEL_OF_DETAIL, LOT_GRAPHNODELEVELOFDETAIL },
    { GRAPH_NODE_TYPE_MASTER_LIST, LOT_GRAPHNODEMASTERLIST },
    { GRAPH_NODE_TYPE_OBJECT, LOT_GRAPHNODEOBJECT },
    { GRAPH_NODE_TYPE_OBJECT_PARENT, LOT_GRAPHNODEOBJECTPARENT },
    { GRAPH_NODE_TYPE_ORTHO_PROJECTION, LOT_GRAPHNODEORTHOPROJECTION },
    { GRAPH_NODE_TYPE_PERSPECTIVE, LOT_GRAPHNODEPERSPECTIVE },
    { GRAPH_NODE_TYPE_ROOT, LOT_GRAPHNODE },
    { GRAPH_NODE_TYPE_ROTATION, LOT_GRAPHNODEROTATION },
    { GRAPH_NODE_TYPE_SCALE, LOT_GRAPHNODESCALE },
    { GRAPH_NODE_TYPE_SHADOW, LOT_GRAPHNODESHADOW },
    { GRAPH_NODE_TYPE_START, LOT_GRAPHNODESTART },
    { GRAPH_NODE_TYPE_SWITCH_CASE, LOT_GRAPHNODESWITCHCASE },
    { GRAPH_NODE_TYPE_TRANSLATION, LOT_GRAPHNODETRANSLATION },
    { GRAPH_NODE_TYPE_TRANSLATION_ROTATION, LOT_GRAPHNODETRANSLATIONROTATION },
};

int smlua_func_cast_graph_node(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    struct GraphNode* graphNode;

    if (smlua_is_cobject(L, 1, LOT_GRAPHNODE)) {
        graphNode = (struct GraphNode*)smlua_to_cobject(L, 1, LOT_GRAPHNODE);
        if (!gSmLuaConvertSuccess) { LOG_LUA("cast_graph_node: Failed to convert parameter 1"); return 0; }
    } else if (smlua_is_cobject(L, 1, LOT_FNGRAPHNODE)) {
        graphNode = (struct GraphNode*)smlua_to_cobject(L, 1, LOT_FNGRAPHNODE);
        if (!gSmLuaConvertSuccess) { LOG_LUA("cast_graph_node: Failed to convert parameter 1"); return 0; }
    } else {
        LOG_LUA("cast_graph_node: Failed to convert parameter 1");
        return 0;
    }

    u16 lot = 0;
    for (u8 i = 0; i != 23; i++) {
        if (graphNode->type != graphNodeLots[i].type) continue;
        lot = graphNodeLots[i].lot;
        break;
    }
    if (lot == 0) {
        LOG_LUA("cast_graph_node: Invalid GraphNode type");
        return 0;
    }

    smlua_push_object(L, lot, graphNode, NULL);

    return 1;
}

  /////////////
 // strings //
/////////////

int smlua_func_get_uncolored_string(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    const char *str = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("get_uncolored_string: Failed to convert parameter 1"); return 0; }

    char *strNoColor = str_remove_color_codes(str);
    lua_pushstring(L, strNoColor);
    free(strNoColor);

    return 1;
}

  //////////////////
 // display list //
//////////////////

#define HANDLE_PARAM(paramNum)                                                                  \
s64 arg##paramNum = smlua_to_integer(L, 2 + paramNum);                                          \
if (!gSmLuaConvertSuccess) {                                                                    \
    LOG_LUA("gfx_set_command: '%s' failed to convert parameter " #paramNum ".", symbolName);    \
    return 0;                                                                                   \
}

#define GET_ARG(paramNum) arg##paramNum
#define CALL_SYMB(symb, ...) symb(__VA_ARGS__)

// Uses macro iterators to dynamically handle the correct number of parameters
#define define_gfx_symbol(symb, params, ...)                            \
if (strcmp(command, #symb) == 0) {                                      \
    if (paramCount != params) { LOG_LUA("gfx_set_command: '" #symb "' received incorrect number of parameters. Received %u, expected %u", paramCount, params); return 0; } \
    UNUSED const char symbolName[] = #symb;                             \
    REPEAT(HANDLE_PARAM, params);                                       \
    const Gfx _Gfx[] = { CALL_SYMB(symb, LIST_ARGS(GET_ARG, params)) }; \
    memcpy(gfx, _Gfx, sizeof(_Gfx));                                    \
    return 1;                                                           \
}

int smlua_func_gfx_set_command(lua_State* L) {
    int top = lua_gettop(L);
    if (top < 2) {
        LOG_LUA_LINE("Improper param count: Expected at least 2, Received %u", top);
        return 0;
    }

    Gfx* gfx = smlua_to_cobject(L, 1, LOT_GFX);
    if (!gSmLuaConvertSuccess) { LOG_LUA("Failed to convert parameter %u for function '%s'", 1, "gfx_set_command"); return 0; }

    const char *command = smlua_to_string(L, 2);
    if (!gSmLuaConvertSuccess) { LOG_LUA("Failed to convert parameter %u for function '%s'", 2, "gfx_set_command"); return 0; }

    u16 paramCount = top - 2;

    // Handle commands using the define_gfx_symbol macro
    GFX_SYMBOLS();
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
    smlua_bind_function(L, "set_exclamation_box_contents", smlua_func_set_exclamation_box_contents);
    smlua_bind_function(L, "get_exclamation_box_contents", smlua_func_get_exclamation_box_contents);
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
    smlua_bind_function(L, "cast_graph_node", smlua_func_cast_graph_node);
    smlua_bind_function(L, "get_uncolored_string", smlua_func_get_uncolored_string);
    smlua_bind_function(L, "gfx_set_command", smlua_func_gfx_set_command);
}
