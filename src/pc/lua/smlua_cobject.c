#include "smlua.h"

#include "data/dynos_cmap.cpp.h"
#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "game/first_person_cam.h"
#include "game/hardcoded.h"
#include "game/scroll_targets.h"
#include "game/rendering_graph_node.h"
#include "audio/external.h"
#include "object_fields.h"
#include "pc/djui/djui_hud_utils.h"
#include "pc/lua/smlua.h"
#include "pc/lua/utils/smlua_anim_utils.h"
#include "pc/lua/utils/smlua_collision_utils.h"
#include "pc/lua/utils/smlua_obj_utils.h"
#include "pc/mods/mods.h"

extern struct LuaObjectTable sLuaObjectTable[LOT_MAX];

int gSmLuaCObjects = 0;
int gSmLuaCPointers = 0;
int gSmLuaCObjectMetatable = 0;
int gSmLuaCPointerMetatable = 0;

struct LuaObjectField* smlua_get_object_field_from_ot(struct LuaObjectTable* ot, const char* key) {
    // binary search
    s32 min = 0;
    s32 max = ot->fieldCount - 1;
    s32 i = (min + max) / 2;
    while (min <= max) {
        if (!ot->fields[i].key) { return NULL; }
        s32 rc = strcmp(key, ot->fields[i].key);
        if (rc == 0) {
            return &ot->fields[i];
        } else if (rc < 0) {
            max = i - 1;
            i = (min + max) / 2;
        } else if (rc > 0) {
            min = i + 1;
            i = (min + max) / 2;
        }
    }

    return NULL;
}

bool smlua_valid_lot(u16 lot) {
    if (lot > LOT_NONE && lot < LOT_MAX) { return true; }
    if (lot > LOT_AUTOGEN_MIN && lot < LOT_AUTOGEN_MAX) { return true; }
    return false;
}

struct LuaObjectField *smlua_get_object_field(u16 lot, const char* key) {
    if (!smlua_valid_lot(lot)) { return NULL; }
    if (lot > LOT_AUTOGEN_MIN) {
        return smlua_get_object_field_autogen(lot, key);
    }

    struct LuaObjectTable* ot = &sLuaObjectTable[lot];
    return smlua_get_object_field_from_ot(ot, key);
}

bool smlua_valid_lvt(u16 lvt) {
    return (lvt < LVT_MAX);
}

static const char *sLuaLvtNames[] = {
    [LVT_BOOL] = "bool",
    [LVT_BOOL_P] = "bool pointer",
    [LVT_U8] = "u8",
    [LVT_U8_P] = "u8 pointer",
    [LVT_U16] = "u16",
    [LVT_U16_P] = "u16 pointer",
    [LVT_U32] = "u32",
    [LVT_U32_P] = "u32 pointer",
    [LVT_S8] = "s8",
    [LVT_S8_P] = "s8 pointer",
    [LVT_S16] = "s16",
    [LVT_S16_P] = "s16 pointer",
    [LVT_S32] = "s32",
    [LVT_S32_P] = "s32 pointer",
    [LVT_F32] = "f32",
    [LVT_F32_P] = "f32 pointer",
    [LVT_U64] = "u64",
    [LVT_U64_P] = "u64 pointer",
    [LVT_COBJECT] = "CObject",
    [LVT_COBJECT_P] = "CObject pointer",
    [LVT_STRING] = "string",
    [LVT_STRING_P] = "string pointer",
    [LVT_BEHAVIORSCRIPT_P] = "BehaviorScript pointer",
    [LVT_OBJECTANIMPOINTER_P] = "ObjectAnimPointer pointer",
    [LVT_COLLISION_P] = "Collision pointer",
    [LVT_LEVELSCRIPT_P] = "LevelScript pointer",
    [LVT_TRAJECTORY_P] = "Trajectory pointer",
    [LVT_TEXTURE_P] = "Texture pointer",
    [LVT_LUAFUNCTION] = "LuaFunction",
    [LVT_LUATABLE] = "LuaTable",
    [LVT_POINTER] = "pointer",
    [LVT_FUNCTION] = "function",
    [LVT_PROPERTY] = "property",
    [LVT_MAX] = "unknown",
};

const char *smlua_get_lvt_name(u16 lvt) {
    assert(smlua_valid_lvt(lvt)); // if this is false, it means there's an invalid lvt somewhere
    return sLuaLvtNames[lvt];
}

  //////////////////////////
 // custom object fields //
//////////////////////////

static const struct { enum LuaValueType lvt; const char *name; } sCustomFieldValidTypes[] = {
    { LVT_U32, "u32" },
    { LVT_S32, "s32" },
    { LVT_F32, "f32" },
};

static enum LuaValueType smlua_get_custom_field_type(const char *name) {
    for (s32 i = 0; i != ARRAY_COUNT(sCustomFieldValidTypes); ++i) {
        if (strcmp(name, sCustomFieldValidTypes[i].name) == 0) {
            return sCustomFieldValidTypes[i].lvt;
        }
    }
    return LVT_MAX;
}

static const char *smlua_get_custom_field_type_name(enum LuaValueType lvt) {
    for (s32 i = 0; i != ARRAY_COUNT(sCustomFieldValidTypes); ++i) {
        if (lvt == sCustomFieldValidTypes[i].lvt) {
            return sCustomFieldValidTypes[i].name;
        }
    }
    return NULL;
}

// ---

struct CustomObjectField {
    const char *name;
    enum LuaValueType lvt;
    struct Mod *mod;
    s32 index;
};

void smlua_free_custom_field(void *p) {
    struct CustomObjectField *cof = (struct CustomObjectField *) p;
    if (cof) {
        free((void *) cof->name);
        free(cof);
    }
}

static int smlua_cmp_custom_fields(const void *l, const void *r) {
    const struct CustomObjectField *lcof = *((const struct CustomObjectField **) l);
    const struct CustomObjectField *rcof = *((const struct CustomObjectField **) r);
    return strcmp(lcof->name, rcof->name);
}

static struct CustomObjectField *smlua_create_custom_field(struct GrowingArray *customObjectFields, const char *key, enum LuaValueType lvt, struct Mod *mod) {
    const char *name = strdup(key);
    if (!name) {
        return NULL;
    }

    struct CustomObjectField *cof = growing_array_alloc(customObjectFields, sizeof(struct CustomObjectField));
    if (!cof) {
        free((void *) name);
        return NULL;
    }

    cof->name = name;
    cof->lvt = lvt;
    cof->mod = mod;
    growing_array_sort(customObjectFields, smlua_cmp_custom_fields);
    return cof;
}

static struct GrowingArray *sGlobalCustomObjectFields = NULL;
s32 gNumCustomObjectFields = 0;

// ---

#define OBJECT_CUSTOM_FIELD_SIZE sizeof(u32)

// Map object pointers to custom object field values
void *sObjectCustomFields = NULL;

// ---

void smlua_init_custom_fields() {
    sGlobalCustomObjectFields = growing_array_init(NULL, 4, malloc, smlua_free_custom_field);
    sObjectCustomFields = hmap_create(false);
}

// Give a field index to all defined custom object fields.
// This must be done at the end of the init phase, to make sure all fields are sorted.
void smlua_index_custom_fields() {
    gNumCustomObjectFields = 0;

    // Index local fields first
    for (u16 i = 0; i < gActiveMods.entryCount; i++) {
        struct Mod *mod = gActiveMods.entries[i];
        growing_array_for_each_(mod->customObjectFields, struct CustomObjectField, cof) {
            cof->index = gNumCustomObjectFields++;
        }
    }

    // Index global fields last
    growing_array_for_each_(sGlobalCustomObjectFields, struct CustomObjectField, cof) {
        cof->index = gNumCustomObjectFields++;
    }
}

void smlua_clear_custom_fields() {
    growing_array_free(&sGlobalCustomObjectFields);
    for (void *objCustomFields = hmap_begin(sObjectCustomFields); objCustomFields != NULL; objCustomFields = hmap_next(sObjectCustomFields)) {
        free(objCustomFields);
    }
    hmap_destroy(sObjectCustomFields);
    sObjectCustomFields = NULL;
    gNumCustomObjectFields = 0;
}

static int smlua_func_define_custom_obj_fields(lua_State* L) {
    LUA_STACK_CHECK_BEGIN(L);
    if (!smlua_functions_valid_param_count(L, 1)) { return 0; }

    if (lua_type(L, 1) != LUA_TTABLE) {
        LOG_LUA_LINE("Invalid parameter passed to define_custom_obj_fields(), it must be a table");
        return 0;
    }

    if (gLuaLoadingMod == NULL) {
        LOG_LUA_LINE("define_custom_obj_fields() can only be called on load.");
        return 0;
    }

    // table is in the stack at index 't'
    lua_pushnil(L);  // first key
    s32 iterationTop = lua_gettop(L);
    while (lua_next(L, 1) != 0) {
        int keyIndex = lua_gettop(L) - 1;
        int valueIndex = lua_gettop(L) - 0;
        // uses 'key' (at index -2) and 'value' (at index -1)
        if (lua_type(L, keyIndex) != LUA_TSTRING) {
            LOG_LUA_LINE("define_custom_obj_fields: Invalid key type: '%s', should be '%s'", luaL_typename(L, keyIndex), lua_typename(L, LUA_TSTRING));
            lua_settop(L, iterationTop);
            continue;
        }

        int valueType = lua_type(L, valueIndex);
        if (valueType != LUA_TSTRING && valueType != LUA_TTABLE) {
            LOG_LUA_LINE("define_custom_obj_fields: Invalid value type: '%s', should be '%s' or '%s'", lua_typename(L, valueType), lua_typename(L, LUA_TSTRING), lua_typename(L, LUA_TTABLE));
            lua_settop(L, iterationTop);
            continue;
        }

        const char* key = smlua_to_string(L, keyIndex);
        if (key[0] != 'o') {
            LOG_LUA_LINE("define_custom_obj_fields: Invalid key name: %s", key);
            lua_settop(L, iterationTop);
            continue;
        }

        // check if key is a regular object field
        if (smlua_get_object_field(LOT_OBJECT, key)) {
            LOG_LUA_LINE("define_custom_obj_fields: Key name cannot be a regular object field: %s", key);
            lua_settop(L, iterationTop);
            continue;
        }

        bool global = false;
        const char *value = NULL;
        if (valueType == LUA_TTABLE) {
            lua_pushvalue(L, valueIndex);

            // get type
            lua_pushstring(L, "type");
            lua_rawget(L, -2);
            if (lua_type(L, -1) != LUA_TSTRING) {
                LOG_LUA_LINE("define_custom_obj_fields: Invalid type for 'type' of key %s: '%s', should be '%s'", key, luaL_typename(L, -1), lua_typename(L, LUA_TSTRING));
                lua_settop(L, iterationTop);
                continue;
            }
            value = smlua_to_string(L, -1);
            if (!gSmLuaConvertSuccess || !value) {
                LOG_LUA_LINE("define_custom_obj_fields: Could not convert to string 'type' of key %s", key);
                lua_settop(L, iterationTop);
                continue;
            }
            lua_pop(L, 1);

            // get global
            lua_pushstring(L, "global");
            lua_rawget(L, -2);
            if (lua_type(L, -1) != LUA_TNIL) {
                if (lua_type(L, -1) != LUA_TBOOLEAN) {
                    LOG_LUA_LINE("define_custom_obj_fields: Invalid type for 'global' of key %s: '%s', should be '%s'", key, luaL_typename(L, -1), lua_typename(L, LUA_TBOOLEAN));
                    lua_settop(L, iterationTop);
                    continue;
                }
                global = smlua_to_boolean(L, -1);
                if (!gSmLuaConvertSuccess) {
                    LOG_LUA_LINE("define_custom_obj_fields: Could not convert to boolean 'global' of key %s", key);
                    lua_settop(L, iterationTop);
                    continue;
                }
            }
            lua_pop(L, 1);

            lua_pop(L, 1); // pop table
        } else {
            value = smlua_to_string(L, valueIndex);
        }
        enum LuaValueType lvt = smlua_get_custom_field_type(value);
        if (lvt == LVT_MAX) {
            LOG_LUA_LINE("define_custom_obj_fields: Invalid type name for key %s: '%s'", key, value);
            lua_settop(L, iterationTop);
            continue;
        }

        // Get existing or create new custom field
        struct GrowingArray *customObjectFields = global ? sGlobalCustomObjectFields : gLuaLoadingMod->customObjectFields;
        struct CustomObjectField newCof = { key };
        struct CustomObjectField *cof = growing_array_bsearch(customObjectFields, &newCof, smlua_cmp_custom_fields);
        if (!cof) {

            // Check if it's already defined as not global/local
            cof = growing_array_bsearch(global ? gLuaLoadingMod->customObjectFields : sGlobalCustomObjectFields, &newCof, smlua_cmp_custom_fields);
            if (cof) {

                // Global but already defined as local
                if (global) {
                    LOG_LUA_LINE("define_custom_obj_fields: Custom object field is already defined as local for key: %s", key);
                    lua_settop(L, iterationTop);
                    continue;
                }

                // Local but already defined as global in the same mod
                if (cof->mod == gLuaLoadingMod) {
                    LOG_LUA_LINE("define_custom_obj_fields: Custom object field is already defined as global in this mod for key: %s", key);
                    lua_settop(L, iterationTop);
                    continue;
                }
            }

            cof = smlua_create_custom_field(customObjectFields, key, lvt, gLuaLoadingMod);
            if (!cof) {
                LOG_LUA_LINE("define_custom_obj_fields: Could not create custom object field for key: %s", key);
                lua_settop(L, iterationTop);
                continue;
            }

            LOG_INFO(
                "define_custom_obj_fields: Registered custom object field as type '%s': %s%s",
                smlua_get_custom_field_type_name(lvt),
                key,
                (global ? " (GLOBAL)" : "")
            );

        } else {

            // Raise error if LVTs don't match
            if (cof->lvt != lvt) {
                LOG_LUA_LINE("define_custom_obj_fields: Key %s already exists with type '%s'", key, smlua_get_custom_field_type_name(cof->lvt));
                lua_settop(L, iterationTop);
                continue;
            }
        }

        lua_settop(L, iterationTop);
    }

    lua_settop(L, iterationTop);

    lua_pop(L, 1); // pop key

    LUA_STACK_CHECK_END(L);
    return 1;
}

static void *smlua_get_object_custom_fields(struct Object *o) {
    if (!sObjectCustomFields || gNumCustomObjectFields == 0) {
        return NULL;
    }

    // Find in cache
    void *objCustomFields = hmap_get(sObjectCustomFields, (int64_t) o);
    if (objCustomFields) {
        return objCustomFields;
    }

    // Allocate new fields
    objCustomFields = calloc(gNumCustomObjectFields, OBJECT_CUSTOM_FIELD_SIZE);
    if (!objCustomFields) {
        LOG_ERROR("Could not create custom fields for object %p", o);
        return NULL;
    }

    hmap_put(sObjectCustomFields, (int64_t) o, objCustomFields);
    return objCustomFields;
}

void smlua_init_object_custom_fields(struct Object *o) {
    if (!o) {
        return;
    }

    void *objCustomFields = smlua_get_object_custom_fields(o);
    if (!objCustomFields) {
        return;
    }

    // Clear and set
    memset(objCustomFields, 0, OBJECT_CUSTOM_FIELD_SIZE * gNumCustomObjectFields);
    o->customFields = objCustomFields;
}

struct LuaObjectField *smlua_get_custom_field(struct Object *o, const char *key, struct Mod *mod) {
    if (!key) {
        return NULL;
    }

    // Retrieve object custom fields
    void *objCustomFields = NULL;
    if (o && sObjectCustomFields) {
        objCustomFields = o->customFields;
        if (!objCustomFields) {
            objCustomFields = o->customFields = smlua_get_object_custom_fields(o);
            if (!objCustomFields) {
                return NULL;
            }
        }
    }

    struct CustomObjectField cofToFind = { key };
    struct CustomObjectField *cof = NULL;

    // Check mod's custom fields
    if (mod) {
        cof = growing_array_bsearch(mod->customObjectFields, &cofToFind, smlua_cmp_custom_fields);
    }

    // Check global custom fields
    if (!cof) {
        cof = growing_array_bsearch(sGlobalCustomObjectFields, &cofToFind, smlua_cmp_custom_fields);
    }

    // Not found...
    if (!cof) {
        return NULL;
    }

    // Turn it into a LuaObjectField
    // o + valueOffset = objCustomFields + cof->index * OBJECT_CUSTOM_FIELD_SIZE
    static struct LuaObjectField lof;
    lof.key = cof->name;
    lof.valueType = cof->lvt;
    lof.valueOffset = ((uintptr_t) objCustomFields) + cof->index * OBJECT_CUSTOM_FIELD_SIZE - ((uintptr_t) o);
    lof.immutable = false;
    lof.lot = LOT_NONE;
    lof.count = 1;
    lof.size = OBJECT_CUSTOM_FIELD_SIZE;
    return &lof;
}

  /////////////////////
 // CObject get/set //
/////////////////////

static bool smlua_push_field(lua_State* L, u8* p, struct LuaObjectField *data) {
    switch (data->valueType) {
        case LVT_BOOL:      lua_pushboolean(L, *(u8* )p);                    break;
        case LVT_U8:        lua_pushinteger(L, *(u8* )p);                    break;
        case LVT_U16:       lua_pushinteger(L, *(u16*)p);                    break;
        case LVT_U32:       lua_pushinteger(L, *(u32*)p);                    break;
        case LVT_S8:        lua_pushinteger(L, *(s8* )p);                    break;
        case LVT_S16:       lua_pushinteger(L, *(s16*)p);                    break;
        case LVT_S32:       lua_pushinteger(L, *(s32*)p);                    break;
        case LVT_F32:       lua_pushnumber( L, *(f32*)p);                    break;
        case LVT_U64:       lua_pushinteger(L, *(u64*)p);                    break;
        case LVT_COBJECT:   smlua_push_object(L, data->lot, p, NULL);        break;
        case LVT_COBJECT_P: smlua_push_object(L, data->lot, *(u8**)p, NULL); break;
        case LVT_STRING:    lua_pushstring(L, (char*)p);                     break;
        case LVT_STRING_P:  lua_pushstring(L, *(char**)p);                   break;

        // pointers
        case LVT_BOOL_P:
        case LVT_U8_P:
        case LVT_U16_P:
        case LVT_U32_P:
        case LVT_S8_P:
        case LVT_S16_P:
        case LVT_S32_P:
        case LVT_F32_P:
        case LVT_U64_P:
        case LVT_BEHAVIORSCRIPT_P:
        case LVT_OBJECTANIMPOINTER_P:
        case LVT_COLLISION_P:
        case LVT_LEVELSCRIPT_P:
        case LVT_TRAJECTORY_P:
        case LVT_TEXTURE_P:
            smlua_push_pointer(L, data->valueType, *(u8**)p, NULL);
            break;

        default:
            return true;
    }
    return false;
}

static bool smlua_set_field(lua_State* L, u8* p, struct LuaObjectField *data) {
    void* valuePointer = NULL;
    switch (data->valueType) {
        case LVT_BOOL:*(u8*) p = smlua_to_boolean(L, 3); break;
        case LVT_U8:  *(u8*) p = smlua_to_integer(L, 3); break;
        case LVT_U16: *(u16*)p = smlua_to_integer(L, 3); break;
        case LVT_U32: *(u32*)p = smlua_to_integer(L, 3); break;
        case LVT_S8:  *(s8*) p = smlua_to_integer(L, 3); break;
        case LVT_S16: *(s16*)p = smlua_to_integer(L, 3); break;
        case LVT_S32: *(s32*)p = smlua_to_integer(L, 3); break;
        case LVT_F32: *(f32*)p = smlua_to_number(L, 3);  break;
        case LVT_U64: *(s64*)p = smlua_to_integer(L, 3); break;

        case LVT_COBJECT_P:
            if (lua_isnil(L, 3)) {
                *(u8**)p = NULL;
                break;
            }
            valuePointer = smlua_to_cobject(L, 3, data->lot);
            if (gSmLuaConvertSuccess) {
                *(u8**)p = valuePointer;
            }
            break;

        // pointers
        case LVT_BOOL_P:
        case LVT_U8_P:
        case LVT_U16_P:
        case LVT_U32_P:
        case LVT_S8_P:
        case LVT_S16_P:
        case LVT_S32_P:
        case LVT_F32_P:
        case LVT_U64_P:
        case LVT_BEHAVIORSCRIPT_P:
        case LVT_OBJECTANIMPOINTER_P:
        case LVT_COLLISION_P:
        case LVT_LEVELSCRIPT_P:
        case LVT_TRAJECTORY_P:
        case LVT_TEXTURE_P:
            if (lua_isnil(L, 3)) {
                *(u8**)p = NULL;
                break;
            }
            valuePointer = smlua_to_cpointer(L, 3, data->valueType);
            if (gSmLuaConvertSuccess) {
                *(u8**)p = valuePointer;
            }
            break;

        default:
            return true;
    }
    return false;
}

static int smlua__get_field(lua_State* L) {
    LUA_STACK_CHECK_BEGIN_NUM(L, 1);

    const CObject *cobj = lua_touserdata(L, 1);
    enum LuaObjectType lot = cobj->lot;
    u64 pointer = (u64)(intptr_t) cobj->pointer;

    if (cobj->freed) {
        LOG_LUA_LINE("_get_field on freed object");
        return 0;
    }

    if (lot == LOT_ARRAY) {
        struct LuaObjectField* data = cobj->info;
        if (!data) {
            LOG_LUA_LINE("Tried to get invalid cobject array");
            return 0;
        }

        int isNum;
        lua_Integer index = lua_tointegerx(L, 2, &isNum);
        if (!isNum) {
            const char *key = lua_tostring(L, 2);
            if (key && key[0] == '_') {
                if (strcmp(key, "_lot") == 0) {
                    lua_pushinteger(L, data->lot);
                    return 1;
                }
                if (strcmp(key, "_pointer") == 0) {
                    lua_pushinteger(L, pointer);
                    return 1;
                }
            }
            LOG_LUA_LINE("Tried to get a non-integer field of cobject array");
            return 0;
        }

        lua_Integer indexStart = data->cArray ? 0 : 1;
        lua_Integer indexEnd = indexStart + (lua_Integer) data->count;
        if (index < indexStart || index >= indexEnd) {
            LOG_LUA_LINE("Index out of bounds: "LUA_INTEGER_FMT" (should be between "LUA_INTEGER_FMT" and "LUA_INTEGER_FMT")", index, indexStart, indexEnd - 1);
            return 0;
        }

        index -= indexStart;
        u8* p = ((u8*)(intptr_t)pointer) + (index * data->size);
        if (smlua_push_field(L, p, data)) {
            LOG_LUA_LINE("_get_field on unimplemented type '%d', index "LUA_INTEGER_FMT, data->valueType, index);
            return 0;
        }

        LUA_STACK_CHECK_END(L);
        return 1;
    }

    const char *key = lua_tostring(L, 2);
    if (!key) {
        LOG_LUA_LINE("Tried to get a non-string field of cobject");
        return 0;
    }

    // Legacy support
    if (key[0] == '_') {
        if (strcmp(key, "_lot") == 0) {
            lua_pushinteger(L, lot);
            return 1;
        }
        if (strcmp(key, "_pointer") == 0) {
            lua_pushinteger(L, pointer);
            return 1;
        }
    }

    struct LuaObjectField* data = smlua_get_object_field(lot, key);
    if (data == NULL && (u16) lot == LOT_OBJECT) {
        data = smlua_get_custom_field(cobj->pointer, key, gLuaActiveMod);
    }
    if (data == NULL) {
        LOG_LUA_LINE("_get_field on invalid key '%s', lot '%s'", key, smlua_get_lot_name(lot));
        return 0;
    }

    // CObject function members
    if (data->valueType == LVT_FUNCTION) {
        lua_getglobal(L, data->function);
        LUA_STACK_CHECK_END(L);
        return 1;
    }

    // CObject property
    if (data->valueType == LVT_PROPERTY) {
        lua_getglobal(L, data->get);
        lua_pushvalue(L, 1);
        smlua_pcall(L, 1, 1, 0);
        LUA_STACK_CHECK_END(L);
        return 1;
    }

    u8* p = ((u8*)(intptr_t)pointer) + data->valueOffset;
    if (data->count > 1) {
        smlua_push_object(L, LOT_ARRAY, p, data);
        if (!gSmLuaConvertSuccess) {
            LOG_LUA_LINE("_get_field failed to retrieve value type '%d', key '%s'", data->valueType, key);
            return 0;
        }
    } else {
        if (smlua_push_field(L, p, data)) {
            LOG_LUA_LINE("_get_field on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
        }
    }

    LUA_STACK_CHECK_END(L);
    return 1;
}

static int smlua__set_field(lua_State* L) {
    LUA_STACK_CHECK_BEGIN(L);

    const CObject *cobj = lua_touserdata(L, 1);
    enum LuaObjectType lot = cobj->lot;
    u64 pointer = (u64)(intptr_t) cobj->pointer;

    if (cobj->freed) {
        LOG_LUA_LINE("_set_field on freed object");
        return 0;
    }

    if (lot == LOT_ARRAY) {
        struct LuaObjectField* data = cobj->info;
        if (!data) {
            LOG_LUA_LINE("Tried to set invalid cobject array");
            return 0;
        }

        int isNum;
        lua_Integer index = lua_tointegerx(L, 2, &isNum);
        if (!isNum) {
            LOG_LUA_LINE("Tried to set a non-integer field of cobject array");
            return 0;
        }

        lua_Integer indexStart = data->cArray ? 0 : 1;
        lua_Integer indexEnd = indexStart + (lua_Integer) data->count;
        if (index < indexStart || index >= indexEnd) {
            LOG_LUA_LINE("Index out of bounds: "LUA_INTEGER_FMT" (should be between "LUA_INTEGER_FMT" and "LUA_INTEGER_FMT")", index, indexStart, indexEnd - 1);
            return 0;
        }

        index -= indexStart;
        u8* p = ((u8*)(intptr_t)pointer) + (index * data->size);
        if (smlua_set_field(L, p, data)) {
            LOG_LUA_LINE("_set_field on unimplemented type '%d', index "LUA_INTEGER_FMT"", data->valueType, index);
            return 0;
        }

        LUA_STACK_CHECK_END(L);
        return 1;
    }

    const char *key = lua_tostring(L, 2);
    if (!key) {
        LOG_LUA_LINE("Tried to set a non-string field of cobject");
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(lot, key);
    if (data == NULL && (u16) lot == LOT_OBJECT) {
        data = smlua_get_custom_field(cobj->pointer, key, gLuaActiveMod);
    }

    if (data == NULL) {
        LOG_LUA_LINE("_set_field on invalid key '%s'", key);
        return 0;
    }

    // CObject property
    if (data->valueType == LVT_PROPERTY) {
        if (data->set) {
            lua_getglobal(L, data->set);
            lua_pushvalue(L, 1);
            lua_pushvalue(L, 3);
            smlua_pcall(L, 2, 1, 0);
            LUA_STACK_CHECK_END(L);
            return 1;
        } else {
            LOG_LUA_LINE("_set_field on immutable key '%s'", key);
            return 0;
        }
    }

    if (data->immutable || data->valueType == LVT_FUNCTION) {
        LOG_LUA_LINE("_set_field on immutable key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)(intptr_t)pointer) + data->valueOffset;
    if (smlua_set_field(L, p, data)) {
        LOG_LUA_LINE("_set_field on unimplemented type '%d', key '%s'", data->valueType, key);
        return 0;
    }
    if (!gSmLuaConvertSuccess) {
        LOG_LUA_LINE("_set_field failed to retrieve value type '%d', key '%s'", data->valueType, key);
        return 0;
    }

    LUA_STACK_CHECK_END(L);
    return 1;
}

int smlua__iter(lua_State *L) {
    lua_rawgeti(L, 1, 1);
    int i = lua_tointeger(L, -1);
    lua_pop(L, 1);

    lua_rawgeti(L, 1, 2);
    const CObject *cobj = lua_touserdata(L, -1);
    lua_pop(L, 1);

    // Only support autogen objects
    if (cobj->lot <= LOT_AUTOGEN_MIN || cobj->lot >= LOT_AUTOGEN_MAX) {
        return 0;
    }

    struct LuaObjectField *data = NULL;

    // Regular fields
    extern struct LuaObjectTable sLuaObjectAutogenTable[];
    struct LuaObjectTable* ot = &sLuaObjectAutogenTable[cobj->lot - LOT_AUTOGEN_MIN - 1];
    if (i < ot->fieldCount) {
        data = &ot->fields[i];
    }

    // Custom object fields
    if (data == NULL && cobj->lot == LOT_OBJECT && cobj->pointer != NULL && sObjectCustomFields != NULL) {
        int j = i - ot->fieldCount;
        struct Object *obj = cobj->pointer;
        void *objCustomFields = obj->customFields;
        if (objCustomFields == NULL) {
            return 0;
        }

        // Mod's custom fields
        if (gLuaActiveMod) {
            growing_array_for_each_(gLuaActiveMod->customObjectFields, struct CustomObjectField, cof) {
                data = smlua_get_custom_field(obj, cof->name, gLuaActiveMod);
                if (data != NULL && j-- == 0) {
                    break;
                }
            }
        }

        // Global custom fields
        if (j >= 0) {
            growing_array_for_each_(sGlobalCustomObjectFields, struct CustomObjectField, cof) {
                data = smlua_get_custom_field(obj, cof->name, NULL);
                if (data != NULL && j-- == 0) {
                    break;
                }
            }
        }

        // No more custom fields
        if (j >= 0) {
            return 0;
        }
    }

    if (data == NULL) {
        return 0;
    }

    u8* pointer = ((u8*)(intptr_t)cobj->pointer) + data->valueOffset;
    lua_pushstring(L, data->key);
    smlua_push_field(L, pointer, data);

    lua_pushinteger(L, ++i);
    lua_rawseti(L, 1, 1);

    return 2;
}

int smlua__pairs(lua_State *L) {
    lua_pushcfunction(L, smlua__iter);

    lua_newtable(L);
    lua_pushinteger(L, 0); lua_rawseti(L, -2, 1);
    lua_pushvalue  (L, 1); lua_rawseti(L, -2, 2);

    lua_pushnil(L);
    return 3;
}

int smlua__eq(lua_State *L) {
    const CObject *a = lua_touserdata(L, 1);
    const CObject *b = lua_touserdata(L, 2);
    lua_pushboolean(L, a && b && a->lot == b->lot && a->pointer == b->pointer);
    return 1;
}

int smlua__bnot(lua_State *L) {
    const CObject *a = lua_touserdata(L, 1);
    lua_pushboolean(L, !a || a->freed);
    return 1;
}

static int smlua_cpointer_get(lua_State* L) {
    const CPointer *cptr = lua_touserdata(L, 1);
    const char *key = lua_tostring(L, 2);
    if (key == NULL) { return 0; }

    // Legacy support
    if (key[0] == '_') {
        if (strcmp(key, "_pointer") == 0) {
            lua_pushinteger(L, (u64)(intptr_t) cptr->pointer);
            return 1;
        }
        if (strcmp(key, "_lvt") == 0) {
            lua_pushinteger(L, cptr->lvt);
            return 1;
        }
    }

    return 0;
}
static int smlua_cpointer_set(UNUSED lua_State* L) { return 0; }

  //////////
 // bind //
//////////

void smlua_cobject_init_globals(void) {
    lua_State* L = gLuaState;

    // Create object pools
    lua_newtable(L);
    gSmLuaCObjects = luaL_ref(L, LUA_REGISTRYINDEX);
    lua_newtable(L);
    gSmLuaCPointers = luaL_ref(L, LUA_REGISTRYINDEX);

    // Create metatables
    luaL_newmetatable(L, "CObject");
    luaL_Reg cObjectMethods[] = {
        { "__index",    smlua__get_field },
        { "__newindex", smlua__set_field },
        { "__pairs",    smlua__pairs },
        { "__eq",       smlua__eq },
        { "__bnot",     smlua__bnot },
        { "__metatable", NULL },
        { NULL, NULL }
    };
    luaL_setfuncs(L, cObjectMethods, 0);
    gSmLuaCObjectMetatable = luaL_ref(L, LUA_REGISTRYINDEX);
    luaL_newmetatable(L, "CPointer");
    luaL_Reg cPointerMethods[] = {
        { "__index",    smlua_cpointer_get },
        { "__newindex", smlua_cpointer_set },
        { "__eq",       smlua__eq },
        { "__bnot",     smlua__bnot },
        { "__metatable", NULL },
        { NULL, NULL }
    };
    luaL_setfuncs(L, cPointerMethods, 0);
    gSmLuaCPointerMetatable = luaL_ref(L, LUA_REGISTRYINDEX);

#define EXPOSE_GLOBAL_ARRAY(lot, ptr, iterator) \
    { \
        lua_newtable(L); \
        int t = lua_gettop(gLuaState); \
        for (s32 i = 0; i < iterator; i++) { \
            lua_pushinteger(L, i); \
            smlua_push_object(L, lot, &ptr[i], NULL); \
            lua_settable(L, t); \
        } \
        lua_setglobal(L, #ptr); \
    } \

#define EXPOSE_GLOBAL(lot, ptr) smlua_push_object(L, lot, &ptr, NULL); lua_setglobal(L, #ptr);
#define EXPOSE_GLOBAL_PTR(lot, ptr) smlua_push_object(L, lot, ptr, NULL); lua_setglobal(L, #ptr);
#define EXPOSE_GLOBAL_WITH_NAME(lot, ptr, name) smlua_push_object(L, lot, ptr, NULL); lua_setglobal(L, name);

    // Array structs

    EXPOSE_GLOBAL_ARRAY(LOT_MARIOSTATE, gMarioStates, MAX_PLAYERS);

    EXPOSE_GLOBAL_ARRAY(LOT_NETWORKPLAYER, gNetworkPlayers, MAX_PLAYERS);

    {
        lua_newtable(L);
        int t = lua_gettop(gLuaState);
        for (s32 i = 0; i < gActiveMods.entryCount; i++) {
            lua_pushinteger(L, i);
            smlua_push_object(L, LOT_MOD, gActiveMods.entries[i], NULL);
            lua_settable(L, t);
        }
        lua_setglobal(L, "gActiveMods");
    }

    EXPOSE_GLOBAL_ARRAY(LOT_CHARACTER, gCharacters, CT_MAX);

    EXPOSE_GLOBAL_ARRAY(LOT_CONTROLLER, gControllers, MAX_PLAYERS);

    EXPOSE_GLOBAL_ARRAY(LOT_MAT4, gMatStack, MATRIX_STACK_SIZE);

    EXPOSE_GLOBAL_ARRAY(LOT_MAT4, gMatStackPrev, MATRIX_STACK_SIZE);

    // Structs

    EXPOSE_GLOBAL_WITH_NAME(LOT_GLOBALTEXTURES, &gGlobalTextures, "gTextures");

    EXPOSE_GLOBAL_WITH_NAME(LOT_GLOBALOBJECTANIMATIONS, &gGlobalObjectAnimations, "gObjectAnimations");

    EXPOSE_GLOBAL(LOT_PAINTINGVALUES, gPaintingValues);

    EXPOSE_GLOBAL(LOT_GLOBALOBJECTCOLLISIONDATA, gGlobalObjectCollisionData);

    EXPOSE_GLOBAL(LOT_LEVELVALUES, gLevelValues);

    EXPOSE_GLOBAL(LOT_BEHAVIORVALUES, gBehaviorValues);

    EXPOSE_GLOBAL(LOT_FIRSTPERSONCAMERA, gFirstPersonCamera);

    EXPOSE_GLOBAL(LOT_LAKITUSTATE, gLakituState);

    EXPOSE_GLOBAL(LOT_SERVERSETTINGS, gServerSettings);

    EXPOSE_GLOBAL(LOT_NAMETAGSSETTINGS, gNametagsSettings);

    EXPOSE_GLOBAL(LOT_HUDDISPLAY, gHudDisplay);
}

void smlua_cobject_init_per_file_globals(const char* path) {
    lua_State* L = gLuaState;

    lua_getfield(L, LUA_REGISTRYINDEX, path); // push per-file globals

    lua_pop(L, 1); // pop per-file globals
}

void smlua_bind_cobject(void) {
    lua_State* L = gLuaState;

    smlua_bind_function(L, "define_custom_obj_fields", smlua_func_define_custom_obj_fields);
}
