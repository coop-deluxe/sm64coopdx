#ifndef SMLUA_COBJECT_H
#define SMLUA_COBJECT_H

enum LuaValueType {
    LVT_BOOL,
    LVT_U8,
    LVT_U16,
    LVT_U32,
    LVT_S8,
    LVT_S16,
    LVT_S32,
    LVT_F32,
    LVT_COBJECT,
    LVT_COBJECT_P,
    LVT_STRING,
    LVT_STRING_P,
};

enum LuaObjectType {
    LOT_NONE = 0,
    LOT_VEC3S,
    LOT_VEC3F,
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

bool smlua_valid_lot(u16 lot);
void smlua_cobject_init_globals(void);
void smlua_bind_cobject(void);

#endif