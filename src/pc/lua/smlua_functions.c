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
#include "level_commands.h"
#include "engine/math_util.h"
#include "engine/level_script.h"
#include "engine/surface_load.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/utils/misc.h"
#include "include/level_misc_macros.h"
#include "include/macro_presets.h"
#include "utils/smlua_anim_utils.h"
#include "utils/smlua_collision_utils.h"
#include "game/hardcoded.h"
#include "game/macro_special_objects.h"
#include "include/macros.h"
#include "include/surface_terrains.h"
#include "include/special_presets.h"

extern void smlua_new_vec3s(Vec3s);

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

  ///////////
 // print //
///////////

int smlua_func_print(lua_State *L) {
    int top = lua_gettop(L);

    char* completeString = calloc(1, 1);
    if (!completeString) {
        return 0;
    }

    size_t pos = 0;
    for (int i = 1; i <= top; i++) {
        size_t len;
        const char* str = luaL_tolstring(L, i, &len);

        size_t needExtra = len + 1 + (i > 1);
        char* grownString = realloc(completeString, pos + needExtra);
        if (!grownString) {
            free(completeString);
            return 0;
        }
        completeString = grownString;

        if (i > 1) {
            completeString[pos] = '\t';
            pos += 1;
        }

        memcpy(completeString + pos, str, len);
        pos += len;
        lua_pop(L, 1);
    }

    completeString[pos] = '\0';

    // print to terminal and console
    log_to_terminal("%s\n", completeString);
    djui_console_message_create(completeString, CONSOLE_MESSAGE_INFO);

    free(completeString);
    return 0;
}

  ///////////
 // table //
///////////

int smlua_func_table_copy(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(L, 1);

    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, 1) != LUA_TTABLE) {
        LOG_LUA_LINE("table_copy() called with an invalid type for param 1: %s", luaL_typename(L, 1));
        return 0;
    }

    // Create a new table that will be the copy
    lua_newtable(L);

    // Iterate through original table
    lua_pushnil(L); // first key
    while (lua_next(L, 1) != 0) {

        // Stack at the start of iteration is orig_table, new_table, key, value
        // At the end of iteration, we need the key on top of the stack
        // But settable also needs the key, so we manipulate the stack to become:
        // orig_table, new_table, key, key, value   (before settable)
        // orig_table, new_table, key               (after settable)
        lua_pushvalue(L, -2);
        lua_insert(L, -2);
        lua_settable(L, 2);
    }

    LUA_STACK_CHECK_END(L);
    return 1;
}

static void table_deepcopy_table(lua_State *L, int idxTable, int idxCache);

static void table_deepcopy_value(lua_State *L, int idx, int idxCache) {
    idx = lua_absindex(L, idx);
    if (lua_type(L, idx) == LUA_TTABLE) {
        table_deepcopy_table(L, idx, idxCache);
    } else {
        lua_pushvalue(L, idx);
    }
}

static void table_deepcopy_table(lua_State *L, int idxTable, int idxCache) {
    idxTable = lua_absindex(L, idxTable);
    idxCache = lua_absindex(L, idxCache);

    // Check the cache to see if the table has already been copied
    lua_pushvalue(L, idxTable);
    lua_rawget(L, idxCache);
    if (!lua_isnil(L, -1)) {
        return;
    }
    lua_pop(L, 1);

    // Create a new table that will be the copy and add it to the cache
    lua_newtable(L);
    int idxNewTable = lua_gettop(L);
    lua_pushvalue(L, idxTable);
    lua_pushvalue(L, idxNewTable);
    lua_rawset(L, idxCache);

    // Iterate through original table
    lua_pushnil(L); // first key
    while (lua_next(L, idxTable) != 0) {
        int idxKey = lua_absindex(L, -2);
        int idxValue = lua_absindex(L, -1);

        // Copy key and value to new table
        table_deepcopy_value(L, idxKey, idxCache);
        table_deepcopy_value(L, idxValue, idxCache);
        lua_settable(L, idxNewTable);

        // Pop value to set key on top of the stack
        lua_pop(L, 1);
    }

    // Copy metatable
    if (lua_getmetatable(L, idxTable)) {
        table_deepcopy_value(L, -1, idxCache);
        lua_setmetatable(L, idxNewTable);
        lua_pop(L, 1);
    }
}

int smlua_func_table_deepcopy(lua_State *L) {
    LUA_STACK_CHECK_BEGIN_NUM(L, 1);

    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, 1) != LUA_TTABLE) {
        LOG_LUA_LINE("table_deepcopy() called with an invalid type for param 1: %s", luaL_typename(L, 1));
        return 0;
    }

    // Cache to prevent copying the same table twice
    lua_newtable(L);
    int idxCache = lua_gettop(L);

    table_deepcopy_table(L, 1, idxCache);

    lua_remove(L, idxCache);

    LUA_STACK_CHECK_END(L);
    return 1;
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
                data = smlua_get_custom_field(obj, fieldIdentifier, gLuaActiveMod);
                if (data == NULL) {
                    LOG_LUA_LINE("Unknown field passed to network_init_object(): %s", fieldIdentifier);
                    lua_pop(L, 1); // pop value
                    continue;
                }
            }

            // These types are the only ones allowed for `network_init_object`
            u8 lvtSizeBytes = 0;
            switch (data->valueType) {
                case LVT_U8: lvtSizeBytes = sizeof(u8); break;
                case LVT_U16: lvtSizeBytes = sizeof(u16); break;
                case LVT_U32: lvtSizeBytes = sizeof(u32); break;
                case LVT_S8: lvtSizeBytes = sizeof(s8); break;
                case LVT_S16: lvtSizeBytes = sizeof(s16); break;
                case LVT_S32: lvtSizeBytes = sizeof(s32); break;
                case LVT_F32: lvtSizeBytes = sizeof(f32); break;
                default: {
                    LOG_LUA_LINE("Invalid field passed to network_init_object(): %s", fieldIdentifier);
                    lua_pop(L, 1); // pop value
                    continue;
                }
            }

            u8* field = ((u8*)(intptr_t)obj) + data->valueOffset;
            sync_object_init_field_with_size(obj, field, lvtSizeBytes);

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

int smlua_func_network_send_bytestring(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }
    network_send_lua_custom_bytestring(true);
    return 1;
}

int smlua_func_network_send_bytestring_to(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 3)) { return 0; }
    network_send_lua_custom_bytestring(false);
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
                LOG_LUA_WARNING_ONCE("set_exclamation_box: Invalid key passed (Subtable %d)", exclamationBoxIndex);
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
            LOG_LUA_WARNING_ONCE("set_exclamation_box: Too many items have been set for the exclamation box. Some content spawns may be lost.");
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
    smlua_push_pointer(L, LVT_TEXTURE_P, (void *) texInfo.texture, NULL);
    lua_settable(L, -3);

    lua_pushstring(L, "width");
    lua_pushinteger(L, texInfo.width);
    lua_settable(L, -3);

    lua_pushstring(L, "height");
    lua_pushinteger(L, texInfo.height);
    lua_settable(L, -3);

    lua_pushstring(L, "format");
    lua_pushinteger(L, texInfo.format);
    lua_settable(L, -3);

    lua_pushstring(L, "size");
    lua_pushinteger(L, texInfo.size);
    lua_settable(L, -3);

    lua_pushstring(L, "name");
    lua_pushstring(L, texInfo.name);
    lua_settable(L, -3);

    return 1;
}

int smlua_func_texture_override_set(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    const char* textureName = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 1"); return 0; }

    struct TextureInfo *overrideTexInfo = smlua_to_texture_info(L, 2);
    if (!overrideTexInfo || !gSmLuaConvertSuccess) { LOG_LUA("texture_override_set: Failed to convert parameter 2"); return 0; }

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

static struct LuaLevelParseScript {
    int callback;
    struct Mod *mod;
    struct ModFile *modFile;
    bool isLegacyFunc;
    bool isParsing;
} sLuaLevelParseScript = { 0 };

//
// Legacy level_script_parse compatibility
//

static bool level_script_parse_get_value(lua_State *L, int index, const char *key, int type) {
    index = lua_absindex(L, index);
    lua_pushstring(L, key);
    if (type == lua_gettable(L, index)) {
        return true;
    }
    lua_pop(L, 1);
    return false;
}

static bool level_script_parse_push_field(lua_State *L, int srcIndex, const char *srcKey, int dstIndex, const char *dstKey, int type) {
    srcIndex = lua_absindex(L, srcIndex);
    dstIndex = lua_absindex(L, dstIndex);
    if (level_script_parse_get_value(L, srcIndex, srcKey, type)) {
        lua_setfield(L, dstIndex, dstKey);
        return true;
    }
    return false;
}

static int level_script_parse_push_params(lua_State *L, int index, int count) {
    for (int i = 0; i != count; ++i) {
        lua_insert(L, index);
    }
    index += count;
    lua_settop(L, index);
    return index;
}

static void level_script_parse_convert_parameters(lua_State *L) {
    int tableIndex = lua_gettop(L);

    // Push 'areaIndex'
    if (!level_script_parse_get_value(L, tableIndex, "area", LUA_TTABLE) ||
        !level_script_parse_get_value(L, -1, "index", LUA_TNUMBER)) {
        lua_pushnil(L);
    }
    tableIndex = level_script_parse_push_params(L, tableIndex, 1);

    // Push 'bhvData'
    if (level_script_parse_get_value(L, tableIndex, "object", LUA_TTABLE)) {
        lua_newtable(L);
        level_script_parse_push_field(L, -2, "behaviorId", -1, "behavior", LUA_TNUMBER);
        level_script_parse_push_field(L, -2, "behParams", -1, "behaviorArg", LUA_TNUMBER);
        level_script_parse_push_field(L, -2, "vanillaModelId", -1, "model", LUA_TNUMBER);
        if (level_script_parse_get_value(L, -2, "pos", LUA_TTABLE)) {
            level_script_parse_push_field(L, -1, "x", -2, "posX", LUA_TNUMBER);
            level_script_parse_push_field(L, -1, "y", -2, "posY", LUA_TNUMBER);
            level_script_parse_push_field(L, -1, "z", -2, "posZ", LUA_TNUMBER);
            lua_pop(L, 1);
        }
        if (level_script_parse_get_value(L, -2, "angle", LUA_TTABLE)) {
            level_script_parse_push_field(L, -1, "x", -2, "pitch", LUA_TNUMBER);
            level_script_parse_push_field(L, -1, "y", -2, "yaw", LUA_TNUMBER);
            level_script_parse_push_field(L, -1, "z", -2, "roll", LUA_TNUMBER);
            lua_pop(L, 1);
        }
    } else {
        lua_pushnil(L);
    }
    tableIndex = level_script_parse_push_params(L, tableIndex, 1);

    // Push 'macroBhvIds', 'macroBhvArgs' and 'macroBhvModels'
    if (level_script_parse_get_value(L, tableIndex, "macroObjects", LUA_TTABLE)) {
        lua_newtable(L); int macroBhvIdsIndex = lua_gettop(L);
        lua_newtable(L); int macroBhvArgsIndex = lua_gettop(L);
        lua_newtable(L); int macroBhvModelsIndex = lua_gettop(L);
        for (int i = 1; lua_rawgeti(L, -4, i) != LUA_TNIL; ++i) {
            if (!level_script_parse_get_value(L, -1, "behaviorId", LUA_TNUMBER)) {
                lua_pushinteger(L, id_bhv_max_count);
            }
            lua_rawseti(L, macroBhvIdsIndex, i);
            if (!level_script_parse_get_value(L, -1, "behParams", LUA_TNUMBER)) {
                lua_pushinteger(L, 0);
            }
            lua_rawseti(L, macroBhvArgsIndex, i);
            if (!level_script_parse_get_value(L, -1, "vanillaModelId", LUA_TNUMBER)) {
                lua_pushinteger(L, E_MODEL_NONE);
            }
            lua_rawseti(L, macroBhvModelsIndex, i);
            lua_pop(L, 1);
        }
        lua_pop(L, 1); // Pop the nil from the last lua_rawgeti
    } else {
        lua_pushnil(L);
        lua_pushnil(L);
        lua_pushnil(L);
    }
    tableIndex = level_script_parse_push_params(L, tableIndex, 3);

    // Pop table
    lua_settop(L, tableIndex - 1);
}

//
// level_parse_script
//

#define dynos_level_cmd_get_lua_param(paramName, paramType, luaParamFlag) \
    smlua_get_lua_param(paramName, paramType, dynos_level_cmd_get(cmd, luaParamFlag##_OFFSET(type)), luaParams, luaParamFlag, { \
        break; \
    })

static void smlua_func_level_parse_collision(lua_State *L, Collision *data, u32 size) {

    // Collision data
    lua_newtable(L);
    smlua_push_pointer(L, LVT_COLLISION_P, data, NULL); lua_setfield(L, -2, "data");
    smlua_push_integer_field(-2, "size", size); // size in bytes

    lua_setfield(L, -2, "collision");

    // Special objects and water boxes
    lua_newtable(L); int specialObjectsTable = lua_gettop(L); s32 specialObjectsTableIndex = 1;
    lua_newtable(L); int waterBoxesTable = lua_gettop(L); s32 waterBoxesTableIndex = 1;

    Collision *end = data + (size / sizeof(Collision));
    while (data < end) {
        s16 terrainLoadType = *data++;
        switch (terrainLoadType) {
            case TERRAIN_LOAD_VERTICES: {
                s16 numVertices = *data++;
                data += 3 * numVertices;
            } break;

            case TERRAIN_LOAD_OBJECTS: {
                s16 numSpecialObjects = *data++;

                for (s16 i = 0; i < numSpecialObjects; ++i) {
                    u8 presetID = (u8) *data++;
                    Vec3s pos;
                    pos[0] = *data++;
                    pos[1] = *data++;
                    pos[2] = *data++;

                    s32 index = get_special_object_preset_index(presetID);
                    if (index == -1) {
                        // If the preset cannot be identified, the rest of the collision data
                        // can no longer be parsed properly; abort and return
                        lua_pop(L, 2);
                        return;
                    }

                    const struct SpecialPreset *preset = &SpecialObjectPresets[index];
                    u8 vanillaModelId = preset->model;
                    enum BehaviorId behaviorId = get_id_from_behavior(preset->behavior);
                    u8 defParam = preset->defParam;

                    if (behaviorId != id_bhv_max_count) {
                        lua_newtable(L);
                        smlua_new_vec3s(pos); lua_setfield(L, -2, "pos");
                        smlua_new_vec3s(gVec3sZero); lua_setfield(L, -2, "angle");
                        smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
                        smlua_push_integer_field(-2, "behaviorId", behaviorId);
                        smlua_push_integer_field(-2, "behParams", 0);
                    }

                    switch (preset->type) {
                        case SPTYPE_NO_YROT_OR_PARAMS: {
                            // Nothing to add
                        } break;

                        case SPTYPE_YROT_NO_PARAMS: {
                            Vec3s angle = { 0, *data++, 0 };
                            if (behaviorId != id_bhv_max_count) {
                                smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
                            }
                        } break;

                        case SPTYPE_PARAMS_AND_YROT: {
                            Vec3s angle = { 0, *data++, 0 };
                            u32 behParams = ((u32) (*data++)) << 16;
                            if (behaviorId != id_bhv_max_count) {
                                smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
                                smlua_push_integer_field(-2, "behParams", behParams);
                            }
                        } break;

                        case SPTYPE_UNKNOWN: { // Unused and unknown data
                            f32 macroUnk108 = (f32) *data++;
                            f32 macroUnk10C = (f32) *data++;
                            f32 macroUnk110 = (f32) *data++;
                            if (behaviorId != id_bhv_max_count) {
                                smlua_push_number_field(-2, "oMacroUnk108", macroUnk108);
                                smlua_push_number_field(-2, "oMacroUnk10C", macroUnk10C);
                                smlua_push_number_field(-2, "oMacroUnk110", macroUnk110);
                            }
                        } break;

                        case SPTYPE_DEF_PARAM_AND_YROT: {
                            Vec3s angle = { 0, *data++, 0 };
                            u32 behParams = ((u32) defParam) << 16;
                            if (behaviorId != id_bhv_max_count) {
                                smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
                                smlua_push_integer_field(-2, "behParams", behParams);
                            }
                        } break;

                        default: { // Undefined
                            // Cannot tell how many extra bytes to read
                            // The game assumes it's 0, but better abort here
                            if (behaviorId != id_bhv_max_count) {
                                lua_pop(L, 3);
                            } else {
                                lua_pop(L, 2);
                            }
                        } return;
                    }

                    if (behaviorId != id_bhv_max_count) {
                        lua_rawseti(L, specialObjectsTable, specialObjectsTableIndex++);
                    }
                }
            } break;

            case TERRAIN_LOAD_ENVIRONMENT: {
                s16 numRegions = *data++;

                for (s16 i = 0; i < numRegions; ++i) {
                    // WaterRegion
                    s16 id = *data++;
                    s16 xmin = *data++;
                    s16 xmax = *data++;
                    s16 zmin = *data++;
                    s16 zmax = *data++;
                    s16 height = *data++;

                    lua_newtable(L);
                    smlua_push_integer_field(-2, "id", id);
                    smlua_push_integer_field(-2, "xmin", xmin);
                    smlua_push_integer_field(-2, "xmax", xmax);
                    smlua_push_integer_field(-2, "zmin", zmin);
                    smlua_push_integer_field(-2, "zmax", zmax);
                    smlua_push_integer_field(-2, "height", height);

                    lua_rawseti(L, waterBoxesTable, waterBoxesTableIndex++);
                }
            } break;

            case TERRAIN_LOAD_CONTINUE: {
            } continue;

            case TERRAIN_LOAD_END: {
                data = end;
            } break;

            default: {
                s16 numSurfaces = *data++;
                data += (3 + surface_has_force(terrainLoadType)) * numSurfaces;
            } break;
        }
    }

    lua_setfield(L, -3, "waterBoxes");
    lua_setfield(L, -2, "specialObjects");
}

static void smlua_func_level_parse_macro_objects(lua_State *L, MacroObject *macroData) {
    for (s32 i = 1; *macroData != MACRO_OBJECT_END(); macroData += 5) {
        s16 presetId = (s16) ((macroData[0] & 0x1FF) - 0x1F);
        if (presetId < 0 || presetId >= MACRO_OBJECT_PRESET_COUNT) {
            continue;
        }

        struct MacroPreset *preset = &MacroObjectPresets[presetId];
        Vec3s pos = { macroData[1], macroData[2], macroData[3] };
        Vec3s angle = { 0, convert_rotation(((macroData[0] >> 9) & 0x7F) << 1), 0 };
        u16 objParams = macroData[4];
        u16 presetParams = preset->param;
        if (presetParams != 0) {
            objParams = (objParams & 0xFF00) + (presetParams & 0x00FF);
        }

        u8 vanillaModelId = (u8) preset->model;
        enum BehaviorId behaviorId = get_id_from_behavior(preset->behavior);
        u32 behParams = ((objParams & 0x00FF) << 16) | (objParams & 0xFF00);

        lua_newtable(L);
        smlua_new_vec3s(pos); lua_setfield(L, -2, "pos");
        smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
        smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
        smlua_push_integer_field(-2, "behaviorId", behaviorId);
        smlua_push_integer_field(-2, "behParams", behParams);

        lua_rawseti(L, -2, i++);
    }
}

static s32 smlua_func_level_parse_script_callback(u8 type, void *cmd) {
    lua_State *L = gLuaState;
    if (L == NULL) { return DYNOS_LEVEL_PARSE_STOP; }
    int top = lua_gettop(L);

    lua_rawgeti(L, LUA_REGISTRYINDEX, sLuaLevelParseScript.callback);
    int callbackIndex = lua_gettop(L);

    lua_newtable(L);

    // Gather arguments
    switch (type) {

        // AREA
        case 0x1F: {
            u8 index = (u8) dynos_level_cmd_get(cmd, 2);
            const GeoLayout *geoLayout = (const GeoLayout *) dynos_level_cmd_get(cmd, 4);
            const char *modelName = dynos_geolayout_get_name(geoLayout);

            lua_newtable(L);
            smlua_push_integer_field(-2, "index", index);
            if (modelName) {
                enum ModelExtendedId modelId = smlua_model_util_get_id(modelName);
                smlua_push_integer_field(-2, "modelId", modelId);
                smlua_push_string_field(-2, "modelName", modelName);
            }

            lua_setfield(L, -2, "area");
        } break;

        // LOAD_MODEL_FROM_DL
        case 0x21: {
            u8 vanillaModelId = (u8) dynos_level_cmd_get(cmd, 2);
            u8 layer = (u8) (dynos_level_cmd_get(cmd, 2) >> 12);
            const Gfx *displayList = (const Gfx *) dynos_level_cmd_get(cmd, 4);

            lua_newtable(L);
            smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
            if (displayList) {
                Gfx *wDisplayList = dynos_gfx_get_writable_display_list((Gfx *) displayList);
                if (wDisplayList) {
                    smlua_push_object(L, LOT_GFX, wDisplayList, NULL); lua_setfield(L, -2, "displayList");
                }
            }
            smlua_push_integer_field(-2, "layer", layer);

            lua_setfield(L, -2, "model");
        } break;

        // LOAD_MODEL_FROM_GEO
        case 0x22: {
            u8 vanillaModelId = (u8) dynos_level_cmd_get(cmd, 2);
            const GeoLayout *geoLayout = (const GeoLayout *) dynos_level_cmd_get(cmd, 4);
            const char *modelName = dynos_geolayout_get_name(geoLayout);

            lua_newtable(L);
            smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
            if (modelName) {
                enum ModelExtendedId modelId = smlua_model_util_get_id(modelName);
                smlua_push_integer_field(-2, "modelId", modelId);
                smlua_push_string_field(-2, "modelName", modelName);
            }

            lua_setfield(L, -2, "model");
        } break;

        // LOAD_MODEL_FROM_GEO_EXT
        case 0x41: {
            u8 vanillaModelId = (u8) dynos_level_cmd_get(cmd, 2);
            const char *modelName = dynos_level_get_token((u32) dynos_level_cmd_get(cmd, 4));

            lua_newtable(L);
            smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
            if (modelName) {
                enum ModelExtendedId modelId = smlua_model_util_get_id(modelName);
                smlua_push_integer_field(-2, "modelId", modelId);
                smlua_push_string_field(-2, "modelName", modelName);
            }

            lua_setfield(L, -2, "model");
        } break;

        // OBJECT, OBJECT_WITH_ACTS
        case 0x24: {
            u8 acts = (u8) dynos_level_cmd_get(cmd, 2);
            Vec3s pos = {
                (s16) ((u16) dynos_level_cmd_get(cmd, 4)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 6)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 8))
            };
            Vec3s angle = {
                (s16) ((((u16) dynos_level_cmd_get(cmd, 10)) * 0x8000) / 180),
                (s16) ((((u16) dynos_level_cmd_get(cmd, 12)) * 0x8000) / 180),
                (s16) ((((u16) dynos_level_cmd_get(cmd, 14)) * 0x8000) / 180)
            };
            u8 vanillaModelId = (u8) dynos_level_cmd_get(cmd, 3);
            enum BehaviorId behaviorId = get_id_from_behavior((const BehaviorScript *) dynos_level_cmd_get(cmd, 20));
            u32 behParams = (u32) dynos_level_cmd_get(cmd, 16);

            lua_newtable(L);
            smlua_push_integer_field(-2, "acts", acts);
            smlua_new_vec3s(pos); lua_setfield(L, -2, "pos");
            smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
            smlua_push_integer_field(-2, "vanillaModelId", vanillaModelId);
            smlua_push_integer_field(-2, "behaviorId", behaviorId);
            smlua_push_integer_field(-2, "behParams", behParams);

            lua_setfield(L, -2, "object");
        } break;

        // OBJECT_EXT, OBJECT_WITH_ACTS_EXT
        // OBJECT_EXT2, OBJECT_WITH_ACTS_EXT2
        // OBJECT_EXT_LUA_PARAMS
        case 0x3F:
        case 0x40:
        case 0x43: {
            if (gLevelScriptModIndex != -1) {
                u16 luaParams = (
                    type == 0x3F ? OBJECT_EXT_LUA_BEHAVIOR : (
                    type == 0x40 ? OBJECT_EXT_LUA_BEHAVIOR | OBJECT_EXT_LUA_MODEL : (
                    (u16) dynos_level_cmd_get(cmd, 2)
                )));

                dynos_level_cmd_get_lua_param(modelId, u32, OBJECT_EXT_LUA_MODEL);
                dynos_level_cmd_get_lua_param(posX, s16, OBJECT_EXT_LUA_POS_X);
                dynos_level_cmd_get_lua_param(posY, s16, OBJECT_EXT_LUA_POS_Y);
                dynos_level_cmd_get_lua_param(posZ, s16, OBJECT_EXT_LUA_POS_Z);
                dynos_level_cmd_get_lua_param(anglePitch, s16, OBJECT_EXT_LUA_ANGLE_X);
                dynos_level_cmd_get_lua_param(angleYaw, s16, OBJECT_EXT_LUA_ANGLE_Y);
                dynos_level_cmd_get_lua_param(angleRoll, s16, OBJECT_EXT_LUA_ANGLE_Z);
                dynos_level_cmd_get_lua_param(behParams, u32, OBJECT_EXT_LUA_BEH_PARAMS);
                dynos_level_cmd_get_lua_param(behavior, uintptr_t, OBJECT_EXT_LUA_BEHAVIOR);
                dynos_level_cmd_get_lua_param(acts, u8, OBJECT_EXT_LUA_ACTS);
                enum BehaviorId behaviorId = (luaParams & OBJECT_EXT_LUA_BEHAVIOR) ? behavior : get_id_from_behavior((const BehaviorScript *) behavior);
                Vec3s pos = { posX, posY, posZ };
                Vec3s angle = { anglePitch, angleYaw, angleRoll };

                lua_newtable(L);
                smlua_push_integer_field(-2, "acts", acts);
                smlua_new_vec3s(pos); lua_setfield(L, -2, "pos");
                smlua_new_vec3s(angle); lua_setfield(L, -2, "angle");
                if (luaParams & OBJECT_EXT_LUA_MODEL) {
                    smlua_push_integer_field(-2, "vanillaModelId", smlua_model_util_load((enum ModelExtendedId) modelId));
                    smlua_push_integer_field(-2, "modelId", modelId);
                } else {
                    smlua_push_integer_field(-2, "vanillaModelId", modelId);
                }
                smlua_push_integer_field(-2, "behaviorId", behaviorId);
                smlua_push_integer_field(-2, "behParams", behParams);

                lua_setfield(L, -2, "object");
            }
        } break;

        // WARP_NODE
        // PAINTING_WARP_NODE
        case 0x26:
        case 0x27: {
            u8 id = (u8) dynos_level_cmd_get(cmd, 2);
            u8 destLevel = (u8) dynos_level_cmd_get(cmd, 3);
            u8 destArea = (u8) dynos_level_cmd_get(cmd, 4);
            u8 destNode = (u8) dynos_level_cmd_get(cmd, 5);
            u8 flags = (u8) dynos_level_cmd_get(cmd, 6);

            lua_newtable(L);
            smlua_push_integer_field(-2, "id", id);
            smlua_push_integer_field(-2, "destLevel", destLevel);
            smlua_push_integer_field(-2, "destArea", destArea);
            smlua_push_integer_field(-2, "destNode", destNode);
            smlua_push_integer_field(-2, "flags", flags);
            smlua_push_boolean_field(-2, "painting", type == 0x27);

            lua_setfield(L, -2, "warpNode");
        } break;

        // INSTANT_WARP
        case 0x28: {
            u8 index = (u8) dynos_level_cmd_get(cmd, 2);
            u8 destArea = (u8) dynos_level_cmd_get(cmd, 3);
            Vec3s displacement = {
                (s16) ((u16) dynos_level_cmd_get(cmd, 4)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 6)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 8))
            };

            lua_newtable(L);
            smlua_push_integer_field(-2, "index", index);
            smlua_push_integer_field(-2, "destArea", destArea);
            smlua_new_vec3s(displacement); lua_setfield(L, -2, "displacement");

            lua_setfield(L, -2, "instantWarp");
        } break;

        // TERRAIN
        case 0x2E: {
            Collision *data = (Collision *) dynos_level_cmd_get(cmd, 4);
            u32 size = get_area_terrain_size(data) * sizeof(Collision);

            smlua_func_level_parse_collision(L, data, size);
        } break;

        // SHOW_DIALOG
        case 0x30: {
            u8 index = (u8) dynos_level_cmd_get(cmd, 2);
            enum DialogId dialogId = (u8) dynos_level_cmd_get(cmd, 3);

            lua_newtable(L);
            smlua_push_integer_field(-2, "index", index);
            smlua_push_integer_field(-2, "dialogId", dialogId);

            lua_setfield(L, -2, "dialog");
        } break;

        // SHOW_DIALOG_EXT
        case 0x44: {
            u8 luaParams = (u8) dynos_level_cmd_get(cmd, 2);

            dynos_level_cmd_get_lua_param(index, u8, SHOW_DIALOG_EXT_LUA_INDEX);
            dynos_level_cmd_get_lua_param(dialogId, s32, SHOW_DIALOG_EXT_LUA_DIALOG);

            lua_newtable(L);
            smlua_push_integer_field(-2, "index", index);
            smlua_push_integer_field(-2, "dialogId", dialogId);

            lua_setfield(L, -2, "dialog");
        } break;

        // TERRAIN_TYPE
        case 0x31: {
            u16 terrainType = (u16) dynos_level_cmd_get(cmd, 2);

            lua_newtable(L);
            smlua_push_integer_field(-2, "type", terrainType);

            lua_setfield(L, -2, "terrain");
        } break;

        // SET_BACKGROUND_MUSIC
        case 0x36: {
            u16 settings = (u16) dynos_level_cmd_get(cmd, 2);
            u16 seqId = (u16) dynos_level_cmd_get(cmd, 4);

            lua_newtable(L);
            smlua_push_integer_field(-2, "settings", settings);
            smlua_push_integer_field(-2, "seqId", seqId);

            lua_setfield(L, -2, "music");
        } break;

        // WHIRLPOOL
        case 0x3B: {
            u8 index = (u8) dynos_level_cmd_get(cmd, 2);
            u8 condition = (u8) dynos_level_cmd_get(cmd, 3);
            Vec3s pos = {
                (s16) ((u16) dynos_level_cmd_get(cmd, 4)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 6)),
                (s16) ((u16) dynos_level_cmd_get(cmd, 8))
            };
            s16 strength = (s16) ((u16) dynos_level_cmd_get(cmd, 10));

            lua_newtable(L);
            smlua_push_integer_field(-2, "index", index);
            smlua_push_integer_field(-2, "condition", condition);
            smlua_new_vec3s(pos); lua_setfield(L, -2, "pos");
            smlua_push_integer_field(-2, "strength", strength);

            lua_setfield(L, -2, "whirlpool");
        } break;

        // MACRO_OBJECTS
        case 0x39: {
            MacroObject *macroData = (MacroObject *) dynos_level_cmd_get(cmd, 4);

            lua_newtable(L);
            smlua_func_level_parse_macro_objects(L, macroData);

            lua_setfield(L, -2, "macroObjects");
        } break;

        // None of the above
        default: {
            lua_settop(L, top);
            return DYNOS_LEVEL_PARSE_CONTINUE;
        }
    }

    // Legacy 'level_script_parse'
    if (sLuaLevelParseScript.isLegacyFunc) {
        level_script_parse_convert_parameters(L);
    }

    // Call the callback
    if (0 != smlua_call_hook(L, lua_gettop(L) - callbackIndex, 0, 0, sLuaLevelParseScript.mod, sLuaLevelParseScript.modFile)) {
        LOG_LUA("level_parse_script: Failed to call the callback: %u", type);
    }

    lua_settop(L, top);
    return DYNOS_LEVEL_PARSE_CONTINUE;
}

int smlua_func_level_parse_script(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 2)) { return 0; }

    if (sLuaLevelParseScript.isParsing) {
        LOG_LUA("Cannot call 'level_parse_script' inside itself");
        return 0;
    }

    enum LevelNum levelNum = smlua_to_integer(L, 1);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("Failed to convert parameter 1 for function 'level_parse_script'");
        return 0;
    }

    void *levelScript = dynos_level_get_script(levelNum);
    if (levelScript == NULL) {
        LOG_LUA_LINE("Could not find script for level num: %d", levelNum);
        return 0;
    }

    lua_pushvalue(L, 2);
    int ref = luaL_ref(L, LUA_REGISTRYINDEX);
    if (ref == LUA_REFNIL) {
        LOG_LUA_LINE("Failed to convert parameter 2 for function 'level_parse_script': undefined function");
        return 0;
    }

    // Setup Lua callback
    sLuaLevelParseScript.callback = ref;
    sLuaLevelParseScript.mod = gLuaActiveMod;
    sLuaLevelParseScript.modFile = gLuaActiveModFile;
    sLuaLevelParseScript.isParsing = true;

    // Back up current values
    LevelScript *currLevelScript = gLevelScriptActive;
    s32 currModIndex = gLevelScriptModIndex;

    // Parse script
    gLevelScriptActive = (LevelScript *) levelScript;
    gLevelScriptModIndex = dynos_level_get_mod_index(levelNum);
    dynos_level_parse_script(levelScript, smlua_func_level_parse_script_callback);

    // Restore current values
    gLevelScriptActive = currLevelScript;
    gLevelScriptModIndex = currModIndex;

    // Cleanup Lua callback
    luaL_unref(L, LUA_REGISTRYINDEX, ref);
    sLuaLevelParseScript.isParsing = false;

    return 1;
}

int smlua_func_level_script_parse(lua_State* L) {
    sLuaLevelParseScript.isLegacyFunc = true;
    int res = smlua_func_level_parse_script(L);
    sLuaLevelParseScript.isLegacyFunc = false;
    return res;
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

        lua_Integer key = smlua_to_integer(L, indexKey);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA("smlua_to_u16_list: Failed to convert table key");
            free(values);
            return 0;
        }

        if (key < 1 || key > *length) {
            LOG_LUA("smlua_to_u16_list: Table key out of bounds: " LUA_INTEGER_FMT, key);
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
    char* colorCode;
    switch (level) {
        case CONSOLE_MESSAGE_WARNING: colorCode = "\x1b[33m"; break;
        case CONSOLE_MESSAGE_ERROR:   colorCode = "\x1b[31m"; break;
        default:                      colorCode = "\x1b[0m"; break;
    }
    log_to_terminal("%s%s\x1b[0m\n", colorCode, message);

    return 1;
}

  ////////////////////
 // scroll targets //
////////////////////

int smlua_func_add_scroll_target(lua_State* L) {

    // add_scroll_target used to require offset and size of the vertex buffer to be used
    int paramCount = lua_gettop(L);
    if (paramCount < 2 || paramCount > 4) {
        LOG_LUA_LINE("Improper param count: Expected (2 - 4), Received %u", paramCount);
        return 0;
    }

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
static GraphNodeLot graphNodeLots[] = {
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
    { GRAPH_NODE_TYPE_SCALE_XYZ, LOT_GRAPHNODESCALEXYZ },
    { GRAPH_NODE_TYPE_SHADOW, LOT_GRAPHNODESHADOW },
    { GRAPH_NODE_TYPE_START, LOT_GRAPHNODESTART },
    { GRAPH_NODE_TYPE_SWITCH_CASE, LOT_GRAPHNODESWITCHCASE },
    { GRAPH_NODE_TYPE_TRANSLATION, LOT_GRAPHNODETRANSLATION },
    { GRAPH_NODE_TYPE_TRANSLATION_ROTATION, LOT_GRAPHNODETRANSLATIONROTATION },
    { GRAPH_NODE_TYPE_BONE, LOT_GRAPHNODEBONE },
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
    for (u8 i = 0; i < ARRAY_COUNT(graphNodeLots); i++) {
        if (graphNode->type != graphNodeLots[i].type) continue;
        lot = graphNodeLots[i].lot;
        break;
    }
    if (lot == 0) {
        LOG_LUA("cast_graph_node: Invalid GraphNode type");
        return 0;
    }

    smlua_push_object(L, lot, graphNode, NULL);

    // Register this graph node as modified so it can be reset later
    dynos_actor_register_modified_graph_node(graphNode);

    return 1;
}

  /////////////
 // strings //
/////////////

int smlua_func_get_uncolored_string(lua_State* L) {
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    const char *str = smlua_to_string(L, 1);
    if (!gSmLuaConvertSuccess) { LOG_LUA("get_uncolored_string: Failed to convert parameter 1"); return 0; }

    char *strNoColor = djui_text_get_uncolored_string(NULL, strlen(str) + 1, str);
    lua_pushstring(L, strNoColor);
    free(strNoColor);

    return 1;
}

  //////////////////
 // display list //
//////////////////

static int get_gfx_command_specifiers_count(const char *command) {
    int count = 0;
    for (; *command; count += (*command == '%'), command++);
    return count;
}

int smlua_func_gfx_set_command(lua_State* L) {
    int top = lua_gettop(L);
    if (top < 2) {
        LOG_LUA_LINE("gfx_set_command: Improper param count: Expected at least 2, Received %u", top);
        return 0;
    }

    Gfx* gfx = smlua_to_cobject(L, 1, LOT_GFX);
    if (!gSmLuaConvertSuccess || !gfx) {
        LOG_LUA_LINE("gfx_set_command: Failed to convert parameter %u", 1);
        return 0;
    }

    const char *command = smlua_to_string(L, 2);
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("gfx_set_command: Failed to convert parameter %u", 2);
        return 0;
    }

    // Compare the number of provided parameters to the number of specifiers in the command
    int paramCount = top - 2;
    int specifiersCount = get_gfx_command_specifiers_count(command);
    if (specifiersCount != paramCount) {
        LOG_LUA_LINE("gfx_set_command: Command \"%s\": Invalid number of command parameters: Expected %u, provided %u", command, specifiersCount, paramCount);
        return 0;
    }

    // Parse the command
    u32 errorSize = 0x400;
    char errorMsg[errorSize];
    if (!dynos_smlua_parse_gfx_command(L, gfx, command, specifiersCount != 0, errorMsg, errorSize)) {
        LOG_LUA_LINE("gfx_set_command: Command \"%s\": %s", command, errorMsg);
        return 0;
    }

    return 1;
}

  //////////
 // bind //
//////////

void smlua_bind_functions(void) {
    lua_State* L = gLuaState;

    // misc
    smlua_bind_function(L, "print", smlua_func_print);
    smlua_bind_function(L, "table_copy", smlua_func_table_copy);
    smlua_bind_function(L, "table_deepcopy", smlua_func_table_deepcopy);
    smlua_bind_function(L, "init_mario_after_warp", smlua_func_init_mario_after_warp);
    smlua_bind_function(L, "network_init_object", smlua_func_network_init_object);
    smlua_bind_function(L, "network_send_object", smlua_func_network_send_object);
    smlua_bind_function(L, "reset_level", smlua_func_reset_level);
    smlua_bind_function(L, "network_send", smlua_func_network_send);
    smlua_bind_function(L, "network_send_to", smlua_func_network_send_to);
    smlua_bind_function(L, "network_send_bytestring", smlua_func_network_send_bytestring);
    smlua_bind_function(L, "network_send_bytestring_to", smlua_func_network_send_bytestring_to);
    smlua_bind_function(L, "set_exclamation_box_contents", smlua_func_set_exclamation_box_contents);
    smlua_bind_function(L, "get_exclamation_box_contents", smlua_func_get_exclamation_box_contents);
    smlua_bind_function(L, "get_texture_info", smlua_func_get_texture_info);
    smlua_bind_function(L, "texture_override_set", smlua_func_texture_override_set);
    smlua_bind_function(L, "texture_override_reset", smlua_func_texture_override_reset);
    smlua_bind_function(L, "level_script_parse", smlua_func_level_script_parse); // deprecated
    smlua_bind_function(L, "level_parse_script", smlua_func_level_parse_script);
    smlua_bind_function(L, "smlua_anim_util_register_animation", smlua_func_smlua_anim_util_register_animation);
    smlua_bind_function(L, "log_to_console", smlua_func_log_to_console);
    smlua_bind_function(L, "add_scroll_target", smlua_func_add_scroll_target);
    smlua_bind_function(L, "collision_find_surface_on_ray", smlua_func_collision_find_surface_on_ray);
    smlua_bind_function(L, "cast_graph_node", smlua_func_cast_graph_node);
    smlua_bind_function(L, "get_uncolored_string", smlua_func_get_uncolored_string);
    smlua_bind_function(L, "gfx_set_command", smlua_func_gfx_set_command);
}
