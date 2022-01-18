#ifndef SMLUA_COBJECT_H
#define SMLUA_COBJECT_H

enum LuaObjectType {
    LOT_VEC3S,
    LOT_VEC3F,
    LOT_MARIO_STATE,
    LOT_CONTROLLER,
    LOT_MAX,
};

void smlua_bind_cobject(void);

#endif