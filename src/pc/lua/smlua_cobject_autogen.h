/* THIS FILE IS AUTOGENERATED */
/* SHOULD NOT BE MANUALLY CHANGED */
#ifndef SMLUA_COBJECT_AUTOGEN_H
#define SMLUA_COBJECT_AUTOGEN_H

enum LuaObjectAutogenType {
    LOT_AUTOGEN_MIN = 1000,
    LOT_CONTROLLER,
    LOT_ANIMATION,
    LOT_GRAPHNODE,
    LOT_GRAPHNODEOBJECT_SUB,
    LOT_GRAPHNODEOBJECT,
    LOT_OBJECTNODE,
    LOT_OBJECT,
    LOT_OBJECTHITBOX,
    LOT_WAYPOINT,
    LOT_SURFACE,
    LOT_MARIOBODYSTATE,
    LOT_OFFSETSIZEPAIR,
    LOT_MARIOANIMATION,
    LOT_MARIOSTATE,
    LOT_WARPNODE,
    LOT_OBJECTWARPNODE,
    LOT_INSTANTWARP,
    LOT_SPAWNINFO,
    LOT_WHIRLPOOL,
    LOT_AREA,
    LOT_WARPTRANSITIONDATA,
    LOT_WARPTRANSITION,
    LOT_PLAYERCAMERASTATE,
    LOT_TRANSITIONINFO,
    LOT_HANDHELDSHAKEPOINT,
    LOT_CAMERATRIGGER,
    LOT_CUTSCENE,
    LOT_CAMERAFOVSTATUS,
    LOT_CUTSCENESPLINEPOINT,
    LOT_PLAYERGEOMETRY,
    LOT_LINEARTRANSITIONPOINT,
    LOT_MODETRANSITIONINFO,
    LOT_PARALLELTRACKINGPOINT,
    LOT_CAMERASTOREDINFO,
    LOT_CUTSCENEVARIABLE,
    LOT_CAMERA,
    LOT_LAKITUSTATE,
    LOT_CHARACTER,
    LOT_WALLCOLLISIONDATA,
    LOT_FLOORGEOMETRY,
    LOT_AUTOGEN_MAX,
};

struct LuaObjectField* smlua_get_object_field_autogen(u16 lot, const char* key);

#endif
