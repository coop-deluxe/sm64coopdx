#ifndef SMLUA_COBJECT_H
#define SMLUA_COBJECT_H

enum LuaObjectType {
    LOT_NONE,
    LOT_VEC3S,
    LOT_VEC3F,
    LOT_MARIO_STATE,
    LOT_CONTROLLER,
    LOT_BODY_STATE,
    LOT_OBJECT,
    LOT_OBJECTNODE,
    LOT_GRAPHNODEOBJECT,
    LOT_MAX,
};

void smlua_bind_cobject(void);

#endif