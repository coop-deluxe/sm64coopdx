#ifndef SMLUA_COBJECT_H
#define SMLUA_COBJECT_H

enum LuaValueType {
    LVT_BOOL,
    LVT_BOOL_P,
    LVT_U8,
    LVT_U8_P,
    LVT_U16,
    LVT_U16_P,
    LVT_U32,
    LVT_U32_P,
    LVT_S8,
    LVT_S8_P,
    LVT_S16,
    LVT_S16_P,
    LVT_S32,
    LVT_S32_P,
    LVT_F32,
    LVT_F32_P,
    LVT_U64,
    LVT_U64_P,
    LVT_COBJECT,
    LVT_COBJECT_P,
    LVT_STRING,
    LVT_STRING_P,
    LVT_BEHAVIORSCRIPT,
    LVT_BEHAVIORSCRIPT_P,
    LVT_OBJECTANIMPOINTER,
    LVT_OBJECTANIMPOINTER_P,
    LVT_COLLISION,
    LVT_COLLISION_P,
    LVT_LEVELSCRIPT,
    LVT_LEVELSCRIPT_P,
    LVT_TRAJECTORY,
    LVT_TRAJECTORY_P,
    LVT_LUAFUNCTION,
    LVT_POINTER,
    LVT_MAX,
};

enum LuaObjectType {
    LOT_NONE = 0,
    LOT_VEC3S,
    LOT_VEC3F,
    LOT_VEC4S,
    LOT_VEC4F,
    LOT_MAT4,
    LOT_COLOR,
    LOT_POINTER,
    LOT_MAX,
};

struct LuaObjectField {
    const char* key;
    enum LuaValueType valueType;
    size_t valueOffset;
    bool immutable;
    u16 lot;
};

struct LuaObjectTable {
    u16 lot;
    struct LuaObjectField* fields;
    u16 fieldCount;
};

typedef struct {
    void *pointer;
    u16 lot;
    bool freed;
} CObject;

typedef struct {
    void *pointer;
    u16 lvt;
    bool freed;
} CPointer;

bool smlua_valid_lot(u16 lot);
bool smlua_valid_lvt(u16 lvt);
struct LuaObjectField* smlua_get_object_field_from_ot(struct LuaObjectTable* ot, const char* key);
struct LuaObjectField* smlua_get_object_field(u16 lot, const char* key);
struct LuaObjectField* smlua_get_custom_field(lua_State* L, u32 lot, int keyIndex);
void smlua_cobject_init_globals(void);
void smlua_cobject_init_per_file_globals(const char* path);
void smlua_bind_cobject(void);

#endif