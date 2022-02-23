#ifndef SMLUA_COBJECT_H
#define SMLUA_COBJECT_H

enum LuaValueType {
    LVT_BOOL,
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
    LVT_COBJECT,
    LVT_COBJECT_P,
    LVT_STRING,
    LVT_STRING_P,
    LVT_BEHAVIORSCRIPT,
    LVT_BEHAVIORSCRIPT_P,
    LVT_POINTER,
};

enum LuaObjectType {
    LOT_NONE = 0,
    LOT_VEC3S,
    LOT_VEC3F,
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

bool smlua_valid_lot(u16 lot);
void smlua_cobject_init_globals(void);
void smlua_bind_cobject(void);

#endif