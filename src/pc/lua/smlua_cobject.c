#include "smlua.h"

#include "game/level_update.h"
#include "game/area.h"
#include "game/mario.h"
#include "audio/external.h"
#include "object_fields.h"

enum LuaValueType {
    LVT_U8,
    LVT_U16,
    LVT_U32,
    LVT_S8,
    LVT_S16,
    LVT_S32,
    LVT_F32,
    LVT_COBJECT,
    LVT_COBJECT_P,
};

struct LuaObjectField {
    const char* key;
    enum LuaValueType valueType;
    size_t valueOffset;
    bool immutable;
    enum LuaObjectType lot;
};

#define LUA_VEC3S_FIELD_COUNT 3
static struct LuaObjectField sVec3sFields[LUA_VEC3S_FIELD_COUNT] = {
    { "x", LVT_S16, sizeof(s16) * 0, false, LOT_NONE },
    { "y", LVT_S16, sizeof(s16) * 1, false, LOT_NONE },
    { "z", LVT_S16, sizeof(s16) * 2, false, LOT_NONE },
};

#define LUA_VEC3F_FIELD_COUNT 3
static struct LuaObjectField sVec3fFields[LUA_VEC3F_FIELD_COUNT] = {
    { "x", LVT_F32, sizeof(f32) * 0, false, LOT_NONE },
    { "y", LVT_F32, sizeof(f32) * 1, false, LOT_NONE },
    { "z", LVT_F32, sizeof(f32) * 2, false, LOT_NONE },
};

#define LUA_MARIO_STATE_FIELD_COUNT 65
static struct LuaObjectField sMarioStateFields[LUA_MARIO_STATE_FIELD_COUNT] = {
    { "playerIndex",              LVT_U16,          offsetof(struct MarioState, playerIndex),              true,  LOT_NONE       },
    { "input",                    LVT_U16,          offsetof(struct MarioState, input),                    false, LOT_NONE       },
    { "flags",                    LVT_U32,          offsetof(struct MarioState, flags),                    false, LOT_NONE       },
    { "particleFlags",            LVT_U32,          offsetof(struct MarioState, particleFlags),            false, LOT_NONE       },
    { "action",                   LVT_U32,          offsetof(struct MarioState, action),                   false, LOT_NONE       },
    { "prevAction",               LVT_U32,          offsetof(struct MarioState, prevAction),               false, LOT_NONE       },
    { "terrainSoundAddend",       LVT_U32,          offsetof(struct MarioState, terrainSoundAddend),       false, LOT_NONE       },
    { "actionState",              LVT_U16,          offsetof(struct MarioState, actionState),              false, LOT_NONE       },
    { "actionTimer",              LVT_U16,          offsetof(struct MarioState, actionTimer),              false, LOT_NONE       },
    { "actionArg",                LVT_U32,          offsetof(struct MarioState, actionArg),                false, LOT_NONE       },
    { "intendedMag",              LVT_F32,          offsetof(struct MarioState, intendedMag),              false, LOT_NONE       },
    { "intendedYaw",              LVT_S16,          offsetof(struct MarioState, intendedYaw),              false, LOT_NONE       },
    { "invincTimer",              LVT_S16,          offsetof(struct MarioState, invincTimer),              false, LOT_NONE       },
    { "framesSinceA",             LVT_U8,           offsetof(struct MarioState, framesSinceA),             false, LOT_NONE       },
    { "framesSinceB",             LVT_U8,           offsetof(struct MarioState, framesSinceB),             false, LOT_NONE       },
    { "wallKickTimer",            LVT_U8,           offsetof(struct MarioState, wallKickTimer),            false, LOT_NONE       },
    { "doubleJumpTimer",          LVT_U8,           offsetof(struct MarioState, doubleJumpTimer),          false, LOT_NONE       },
    { "faceAngle",                LVT_COBJECT,      offsetof(struct MarioState, faceAngle),                true,  LOT_VEC3S      },
    { "angleVel",                 LVT_COBJECT,      offsetof(struct MarioState, angleVel),                 true,  LOT_VEC3S      },
    { "slideYaw",                 LVT_S16,          offsetof(struct MarioState, slideYaw),                 false, LOT_NONE       },
    { "twirlYaw",                 LVT_S16,          offsetof(struct MarioState, twirlYaw),                 false, LOT_NONE       },
    { "pos",                      LVT_COBJECT,      offsetof(struct MarioState, pos),                      true,  LOT_VEC3F      },
    { "vel",                      LVT_COBJECT,      offsetof(struct MarioState, vel),                      true,  LOT_VEC3F      },
    { "forwardVel",               LVT_F32,          offsetof(struct MarioState, forwardVel),               false, LOT_NONE       },
    { "slideVelX",                LVT_F32,          offsetof(struct MarioState, slideVelX),                false, LOT_NONE       },
    { "slideVelZ",                LVT_F32,          offsetof(struct MarioState, slideVelZ),                false, LOT_NONE       },
    { "wall",                     LVT_COBJECT_P,    offsetof(struct MarioState, wall),                     true,  LOT_SURFACE    },
    { "ceil",                     LVT_COBJECT_P,    offsetof(struct MarioState, ceil),                     true,  LOT_SURFACE    },
    { "floor",                    LVT_COBJECT_P,    offsetof(struct MarioState, floor),                    true,  LOT_SURFACE    },
    { "ceilHeight",               LVT_F32,          offsetof(struct MarioState, ceilHeight),               false, LOT_NONE       },
    { "floorHeight",              LVT_F32,          offsetof(struct MarioState, floorHeight),              false, LOT_NONE       },
    { "floorAngle",               LVT_S16,          offsetof(struct MarioState, floorAngle),               false, LOT_NONE       },
    { "waterLevel",               LVT_S16,          offsetof(struct MarioState, waterLevel),               false, LOT_NONE       },
    { "interactObj",              LVT_COBJECT_P,    offsetof(struct MarioState, interactObj),              false, LOT_OBJECT     },
    { "heldObj",                  LVT_COBJECT_P,    offsetof(struct MarioState, heldObj),                  false, LOT_OBJECT     },
    { "usedObj",                  LVT_COBJECT_P,    offsetof(struct MarioState, usedObj),                  false, LOT_OBJECT     },
    { "interactObj",              LVT_COBJECT_P,    offsetof(struct MarioState, interactObj),              false, LOT_OBJECT     },
    { "marioObj",                 LVT_COBJECT_P,    offsetof(struct MarioState, marioObj),                 true,  LOT_OBJECT     },
    { "marioBodyState",           LVT_COBJECT_P,    offsetof(struct MarioState, marioBodyState),           true,  LOT_BODY_STATE },
    { "controller",               LVT_COBJECT_P,    offsetof(struct MarioState, controller),               true,  LOT_CONTROLLER },
    { "collidedObjInteractTypes", LVT_U32,          offsetof(struct MarioState, collidedObjInteractTypes), false, LOT_NONE       },
    { "numCoins",                 LVT_S16,          offsetof(struct MarioState, numCoins),                 false, LOT_NONE       },
    { "numStars",                 LVT_S16,          offsetof(struct MarioState, numStars),                 false, LOT_NONE       },
    { "mechani",                  LVT_S8,           offsetof(struct MarioState, numKeys),                  false, LOT_NONE       },
    { "numLives",                 LVT_S8,           offsetof(struct MarioState, numLives),                 false, LOT_NONE       },
    { "health",                   LVT_S16,          offsetof(struct MarioState, health),                   false, LOT_NONE       },
    { "unkB0",                    LVT_S16,          offsetof(struct MarioState, unkB0),                    false, LOT_NONE       },
    { "hurtCounter",              LVT_U8,           offsetof(struct MarioState, hurtCounter),              false, LOT_NONE       },
    { "healCounter",              LVT_U8,           offsetof(struct MarioState, healCounter),              false, LOT_NONE       },
    { "squishTimer",              LVT_U8,           offsetof(struct MarioState, squishTimer),              false, LOT_NONE       },
    { "fadeWarpOpacity",          LVT_U8,           offsetof(struct MarioState, fadeWarpOpacity),          false, LOT_NONE       },
    { "capTimer",                 LVT_U16,          offsetof(struct MarioState, capTimer),                 false, LOT_NONE       },
    { "prevNumStarsForDialog",    LVT_S16,          offsetof(struct MarioState, prevNumStarsForDialog),    false, LOT_NONE       },
    { "peakHeight",               LVT_F32,          offsetof(struct MarioState, peakHeight),               false, LOT_NONE       },
    { "quicksandDepth",           LVT_F32,          offsetof(struct MarioState, quicksandDepth),           false, LOT_NONE       },
    { "unkC4",                    LVT_F32,          offsetof(struct MarioState, unkC4),                    false, LOT_NONE       },
    { "currentRoom",              LVT_S16,          offsetof(struct MarioState, currentRoom),              false, LOT_NONE       },
    { "isSnoring",                LVT_U8,           offsetof(struct MarioState, isSnoring),                false, LOT_NONE       },
    { "freeze",                   LVT_U8,           offsetof(struct MarioState, freeze),                   false, LOT_NONE       },
    { "splineKeyframeFraction",   LVT_F32,          offsetof(struct MarioState, splineKeyframeFraction),   false, LOT_NONE       },
    { "splineState",              LVT_S32,          offsetof(struct MarioState, splineState),              false, LOT_NONE       },
    { "nonInstantWarpPos",        LVT_COBJECT,      offsetof(struct MarioState, nonInstantWarpPos),        true,  LOT_VEC3F      },
    { "wasNetworkVisible",        LVT_U8,           offsetof(struct MarioState, wasNetworkVisible),        false, LOT_NONE       },
    { "minimumBoneY",             LVT_F32,          offsetof(struct MarioState, minimumBoneY),             false, LOT_NONE       },
    { "curAnimOffset",            LVT_F32,          offsetof(struct MarioState, curAnimOffset),            false, LOT_NONE       },
    /* TODO: implement
        struct SpawnInfo *spawnInfo;
        struct Area *area;
        struct PlayerCameraState *statusForCamera;
        struct MarioAnimation *animation;
        struct Object* heldByObj;
        struct Object* bubbleObj;
        Vec4s* splineKeyframe;
        struct Character* character;
    */
};

#define LUA_CONTROLLER_FIELD_COUNT 10
static struct LuaObjectField sControllerFields[LUA_CONTROLLER_FIELD_COUNT] = {
    { "rawStickX",      LVT_S16,          offsetof(struct Controller, rawStickX),      false, LOT_NONE },
    { "rawStickY",      LVT_S16,          offsetof(struct Controller, rawStickY),      false, LOT_NONE },
    { "stickX",         LVT_F32,          offsetof(struct Controller, stickX),         false, LOT_NONE },
    { "stickY",         LVT_F32,          offsetof(struct Controller, stickY),         false, LOT_NONE },
    { "stickMag",       LVT_F32,          offsetof(struct Controller, stickMag),       false, LOT_NONE },
    { "buttonDown",     LVT_U16,          offsetof(struct Controller, buttonDown),     false, LOT_NONE },
    { "buttonPressed",  LVT_U16,          offsetof(struct Controller, buttonPressed),  false, LOT_NONE },
  //{ "statusData",     LVT_OSCONTSTATUS, offsetof(struct Controller, statusData),     false, LOT_NONE },
  //{ "controllerData", LVT_OSCONTPAD,    offsetof(struct Controller, controllerData), false, LOT_NONE },
    { "port",           LVT_S32,          offsetof(struct Controller, port),           false, LOT_NONE },
    { "extStickX",      LVT_S16,          offsetof(struct Controller, extStickX),      false, LOT_NONE },
    { "extStickY",      LVT_S16,          offsetof(struct Controller, extStickY),      false, LOT_NONE },
};

#define LUA_BODY_STATE_FIELD_COUNT 11
static struct LuaObjectField sMarioBodyStateFields[LUA_BODY_STATE_FIELD_COUNT] = {
    { "action",              LVT_U32,     offsetof(struct MarioBodyState, action),              false, LOT_NONE  },
    { "capState",            LVT_S8,      offsetof(struct MarioBodyState, capState),            false, LOT_NONE  },
    { "eyeState",            LVT_S8,      offsetof(struct MarioBodyState, eyeState),            false, LOT_NONE  },
    { "handState",           LVT_S8,      offsetof(struct MarioBodyState, handState),           false, LOT_NONE  },
    { "wingFlutter",         LVT_S8,      offsetof(struct MarioBodyState, wingFlutter),         false, LOT_NONE  },
    { "modelState",          LVT_S16,     offsetof(struct MarioBodyState, modelState),          false, LOT_NONE  },
    { "grabPos",             LVT_S8,      offsetof(struct MarioBodyState, grabPos),             false, LOT_NONE  },
    { "punchState",          LVT_U8,      offsetof(struct MarioBodyState, punchState),          false, LOT_NONE  },
    { "torsoAngle",          LVT_COBJECT, offsetof(struct MarioBodyState, torsoAngle),          true,  LOT_VEC3S },
    { "headAngle",           LVT_COBJECT, offsetof(struct MarioBodyState, headAngle),           true,  LOT_VEC3S },
    { "heldObjLastPosition", LVT_COBJECT, offsetof(struct MarioBodyState, heldObjLastPosition), true,  LOT_VEC3S },
};

#define LUA_OBJECT_FIELD_COUNT 16
static struct LuaObjectField sObjectFields[LUA_OBJECT_FIELD_COUNT] = {
    { "header",                   LVT_COBJECT,   offsetof(struct Object, header),                   true,  LOT_OBJECTNODE },
    { "parentObj",                LVT_COBJECT_P, offsetof(struct Object, parentObj),                false, LOT_OBJECT     },
    { "prevObj",                  LVT_COBJECT_P, offsetof(struct Object, prevObj),                  false, LOT_OBJECT     },
    { "collidedObjInteractTypes", LVT_U32,       offsetof(struct Object, collidedObjInteractTypes), false, LOT_NONE       },
    { "activeFlags",              LVT_S16,       offsetof(struct Object, activeFlags),              false, LOT_NONE       },
    { "numCollidedObjs",          LVT_S16,       offsetof(struct Object, numCollidedObjs),          false, LOT_NONE       },
    { "bhvStackIndex",            LVT_U32,       offsetof(struct Object, bhvStackIndex),            false, LOT_NONE       },
    { "bhvDelayTimer",            LVT_S16,       offsetof(struct Object, bhvDelayTimer),            false, LOT_NONE       },
    { "respawnInfoType",          LVT_S16,       offsetof(struct Object, respawnInfoType),          false, LOT_NONE       },
    { "hitboxRadius",             LVT_F32,       offsetof(struct Object, hitboxRadius),             false, LOT_NONE       },
    { "hitboxHeight",             LVT_F32,       offsetof(struct Object, hitboxHeight),             false, LOT_NONE       },
    { "hurtboxRadius",            LVT_F32,       offsetof(struct Object, hurtboxRadius),            false, LOT_NONE       },
    { "hurtboxHeight",            LVT_F32,       offsetof(struct Object, hurtboxHeight),            false, LOT_NONE       },
    { "hitboxDownOffset",         LVT_F32,       offsetof(struct Object, hitboxDownOffset),         false, LOT_NONE       },
    { "heldByPlayerIndex",        LVT_U32,       offsetof(struct Object, heldByPlayerIndex),        false, LOT_NONE       },
    { "platform",                 LVT_COBJECT_P, offsetof(struct Object, platform),                 false, LOT_OBJECT     },
    /* TODO: implement
        struct Object *collidedObjs[4]
        union rawData
        const BehaviorScript *curBhvCommand
        uintptr_t bhvStack[8]
        const BehaviorScript *behavior
        void *collisionData
        Mat4 transform
        void *respawnInfo
    */
};

#define LUA_OBJECTNODE_FIELD_COUNT 3
static struct LuaObjectField sObjectNodeFields[LUA_OBJECTNODE_FIELD_COUNT] = {
    { "gfx",  LVT_COBJECT,   offsetof(struct ObjectNode, gfx),  true, LOT_GRAPHNODEOBJECT },
    { "next", LVT_COBJECT_P, offsetof(struct ObjectNode, next), true, LOT_OBJECTNODE },
    { "prev", LVT_COBJECT_P, offsetof(struct ObjectNode, prev), true, LOT_OBJECTNODE },
};

#define LUA_GRAPHNODEOBJECT_FIELD_COUNT 14
static struct LuaObjectField sGraphNodeObjectFields[LUA_GRAPHNODEOBJECT_FIELD_COUNT] = {
    { "areaIndex",              LVT_S8,        offsetof(struct GraphNodeObject, unk18),                  false, LOT_NONE                },
    { "activeAreaIndex",        LVT_S8,        offsetof(struct GraphNodeObject, unk19),                  false, LOT_NONE                },
    { "angle",                  LVT_COBJECT,   offsetof(struct GraphNodeObject, angle),                  false, LOT_VEC3S               },
    { "pos",                    LVT_COBJECT,   offsetof(struct GraphNodeObject, pos),                    false, LOT_VEC3F               },
    { "prevAngle",              LVT_COBJECT,   offsetof(struct GraphNodeObject, prevAngle),              false, LOT_VEC3S               },
    { "prevPos",                LVT_COBJECT,   offsetof(struct GraphNodeObject, prevPos),                false, LOT_VEC3F               },
    { "prevTimestamp",          LVT_U32,       offsetof(struct GraphNodeObject, prevTimestamp),          false, LOT_NONE                },
    { "prevShadowPos",          LVT_COBJECT,   offsetof(struct GraphNodeObject, prevShadowPos),          false, LOT_VEC3F               },
    { "prevShadowPosTimestamp", LVT_U32,       offsetof(struct GraphNodeObject, prevShadowPosTimestamp), false, LOT_NONE                },
    { "scale",                  LVT_COBJECT,   offsetof(struct GraphNodeObject, scale),                  false, LOT_VEC3F               },
    { "prevScale",              LVT_COBJECT,   offsetof(struct GraphNodeObject, prevScale),              false, LOT_VEC3F               },
    { "prevScaleTimestamp",     LVT_U32,       offsetof(struct GraphNodeObject, prevScaleTimestamp),     false, LOT_NONE                },
    { "animInfo",               LVT_COBJECT,   offsetof(struct GraphNodeObject, unk38),                  false, LOT_GRAPHNODEOBJECTSUB  },
    { "cameraToObject",         LVT_COBJECT,   offsetof(struct GraphNodeObject, cameraToObject),         false, LOT_VEC3F               },
    /* unimplemented
    struct GraphNode node;
    struct GraphNode *sharedChild;
    struct SpawnInfo *unk4C;
    Mat4 *throwMatrix;
    Mat4 prevThrowMatrix;
    u32 prevThrowMatrixTimestamp;
    Mat4 *throwMatrixInterpolated;
    u32 skipInterpolationTimestamp;
    */
};

#define LUA_SURFACE_FIELD_COUNT 16
static struct LuaObjectField sSurfaceFields[LUA_SURFACE_FIELD_COUNT] = {
    { "type",              LVT_S16,     offsetof(struct Surface, type),              false, LOT_NONE   },
    { "force",             LVT_S16,     offsetof(struct Surface, force),             false, LOT_NONE   },
    { "flags",             LVT_S8,      offsetof(struct Surface, flags),             false, LOT_NONE   },
    { "room",              LVT_S8,      offsetof(struct Surface, room),              false, LOT_NONE   },
    { "lowerY",            LVT_S16,     offsetof(struct Surface, lowerY),            false, LOT_NONE   },
    { "upperY",            LVT_S16,     offsetof(struct Surface, upperY),            false, LOT_NONE   },
    { "vertex1",           LVT_COBJECT, offsetof(struct Surface, vertex1),           false, LOT_VEC3S  },
    { "vertex2",           LVT_COBJECT, offsetof(struct Surface, vertex2),           false, LOT_VEC3S  },
    { "vertex3",           LVT_COBJECT, offsetof(struct Surface, vertex3),           false, LOT_VEC3S  },
    { "normal",            LVT_COBJECT, offsetof(struct Surface, normal),            false, LOT_VEC3F  },
    { "originOffset",      LVT_F32,     offsetof(struct Surface, originOffset),      false, LOT_NONE   },
    { "object",            LVT_COBJECT, offsetof(struct Surface, object),            false, LOT_OBJECT },
    { "prevVertex1",       LVT_COBJECT, offsetof(struct Surface, prevVertex1),       false, LOT_VEC3S  },
    { "prevVertex2",       LVT_COBJECT, offsetof(struct Surface, prevVertex2),       false, LOT_VEC3S  },
    { "prevVertex3",       LVT_COBJECT, offsetof(struct Surface, prevVertex3),       false, LOT_VEC3S  },
    { "modifiedTimestamp", LVT_U32,     offsetof(struct Surface, modifiedTimestamp), false, LOT_NONE   },
};

#define LUA_GRAPHNODEOBJECTSUB_FIELD_COUNT 11
static struct LuaObjectField sGraphNodeObjectSubFields[LUA_GRAPHNODEOBJECTSUB_FIELD_COUNT] = {
        { "animID",                 LVT_S16,       offsetof(struct GraphNodeObject_sub, animID),                 false, LOT_NONE      },
        { "animYTrans",             LVT_S16,       offsetof(struct GraphNodeObject_sub, animYTrans),             false, LOT_NONE      },
        { "curAnim",                LVT_COBJECT_P, offsetof(struct GraphNodeObject_sub, curAnim),                true,  LOT_ANIMATION },
        { "animFrame",              LVT_S16,       offsetof(struct GraphNodeObject_sub, animFrame),              false, LOT_NONE      },
        { "animTimer",              LVT_U16,       offsetof(struct GraphNodeObject_sub, animTimer),              false, LOT_NONE      },
        { "animFrameAccelAssist",   LVT_S32,       offsetof(struct GraphNodeObject_sub, animFrameAccelAssist),   false, LOT_NONE      },
        { "animAccel",              LVT_S32,       offsetof(struct GraphNodeObject_sub, animAccel),              false, LOT_NONE      },
        { "prevAnimFrame",          LVT_S16,       offsetof(struct GraphNodeObject_sub, prevAnimFrame),          false, LOT_NONE      },
        { "prevAnimID",             LVT_S16,       offsetof(struct GraphNodeObject_sub, prevAnimID),             false, LOT_NONE      },
        { "prevAnimFrameTimestamp", LVT_U32,       offsetof(struct GraphNodeObject_sub, prevAnimFrameTimestamp), false, LOT_NONE      },
        { "prevAnimPtr",            LVT_COBJECT_P, offsetof(struct GraphNodeObject_sub, prevAnimPtr),            true,  LOT_ANIMATION },
};


#define LUA_ANIMATION_FIELD_COUNT 7
static struct LuaObjectField sAnimationFields[LUA_ANIMATION_FIELD_COUNT] = {
    { "flags",             LVT_S16, offsetof(struct Animation, flags),  false, LOT_NONE },
    { "animYTransDivisor", LVT_S16, offsetof(struct Animation, unk02),  false, LOT_NONE },
    { "startFrame",        LVT_S16, offsetof(struct Animation, unk04),  false, LOT_NONE },
    { "loopStart",         LVT_S16, offsetof(struct Animation, unk06),  false, LOT_NONE },
    { "loopEnd",           LVT_S16, offsetof(struct Animation, unk08),  false, LOT_NONE },
    { "unusedBoneCount",   LVT_S16, offsetof(struct Animation, unk0A),  false, LOT_NONE },
    { "length",            LVT_U32, offsetof(struct Animation, length), false, LOT_NONE },
    /*
    const s16 *values;
    const u16 *index;
    */
};


struct LuaObjectTable {
    enum LuaObjectType objectType;
    struct LuaObjectField* fields;
    u16 fieldCount;
};

struct LuaObjectTable sLuaObjectTable[LOT_MAX] = {
    { LOT_NONE,               NULL,                      0                                  },
    { LOT_VEC3S,              sVec3sFields,              LUA_VEC3S_FIELD_COUNT              },
    { LOT_VEC3F,              sVec3fFields,              LUA_VEC3F_FIELD_COUNT              },
    { LOT_MARIO_STATE,        sMarioStateFields,         LUA_MARIO_STATE_FIELD_COUNT        },
    { LOT_CONTROLLER,         sControllerFields,         LUA_CONTROLLER_FIELD_COUNT         },
    { LOT_BODY_STATE,         sMarioBodyStateFields,     LUA_BODY_STATE_FIELD_COUNT         },
    { LOT_OBJECT,             sObjectFields,             LUA_OBJECT_FIELD_COUNT             },
    { LOT_OBJECTNODE,         sObjectNodeFields,         LUA_OBJECTNODE_FIELD_COUNT         },
    { LOT_GRAPHNODEOBJECT,    sGraphNodeObjectFields,    LUA_GRAPHNODEOBJECT_FIELD_COUNT    },
    { LOT_SURFACE,            sSurfaceFields,            LUA_SURFACE_FIELD_COUNT            },
    { LOT_GRAPHNODEOBJECTSUB, sGraphNodeObjectSubFields, LUA_GRAPHNODEOBJECTSUB_FIELD_COUNT },
    { LOT_ANIMATION,          sAnimationFields,          LUA_ANIMATION_FIELD_COUNT          },
};

static struct LuaObjectField* smlua_get_object_field(struct LuaObjectTable* ot, const char* key) {
    // TODO: change this to binary search or hash table or something
    for (int i = 0; i < ot->fieldCount; i++) {
        if (!strcmp(ot->fields[i].key, key)) {
            return &ot->fields[i];
        }
    }
    return NULL;
}

static int smlua__get_field(lua_State* L) {
    enum LuaObjectType lot = lua_tointeger(L, -3);
    u64 pointer = lua_tointeger(L, -2);
    const char* key = lua_tostring(L, -1);

    if (pointer == 0) {
        LOG_LUA("_get_field on null pointer");
        return 0;
    }

    if (lot >= LOT_MAX) {
        LOG_LUA("_get_field on invalid LOT '%u'", lot);
        return 0;
    }

    if (!smlua_cobject_allowlist_contains(lot, pointer)) {
        LOG_LUA("_get_field received a pointer not in allow list. '%u', '%llu", lot, (u64)pointer);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[lot], key);
    if (data == NULL) {
        LOG_LUA("_get_field on invalid key '%s', lot '%d'", key, lot);
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
        case LVT_U8:         lua_pushinteger(L, *(u8* )p);              break;
        case LVT_U16:        lua_pushinteger(L, *(u16*)p);              break;
        case LVT_U32:        lua_pushinteger(L, *(u32*)p);              break;
        case LVT_S8:         lua_pushinteger(L, *(s8* )p);              break;
        case LVT_S16:        lua_pushinteger(L, *(s16*)p);              break;
        case LVT_S32:        lua_pushinteger(L, *(s32*)p);              break;
        case LVT_F32:        lua_pushnumber( L, *(f32*)p);              break;
        case LVT_COBJECT:    smlua_push_object(L, data->lot, p);        break;
        case LVT_COBJECT_P:  smlua_push_object(L, data->lot, *(u8**)p); break;
        default:
            LOG_LUA("_get_field on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
    }

    return 1;
}

static int smlua__set_field(lua_State* L) {
    enum LuaObjectType lot = lua_tointeger(L, -4);
    u64 pointer = lua_tointeger(L, -3);
    const char* key = lua_tostring(L, -2);

    if (pointer == 0) {
        LOG_LUA("_set_field on null pointer");
        return 0;
    }

    if (lot >= LOT_MAX) {
        LOG_LUA("_set_field on invalid LOT '%u'", lot);
        return 0;
    }

    if (!smlua_cobject_allowlist_contains(lot, pointer)) {
        LOG_LUA("_set_field received a pointer not in allow list. '%u', '%llu", lot, (u64)pointer);
        return 0;
    }

    struct LuaObjectField* data = smlua_get_object_field(&sLuaObjectTable[lot], key);
    if (data == NULL) {
        LOG_LUA("_set_field on invalid key '%s'", key);
        return 0;
    }

    if (data->immutable) {
        LOG_LUA("_set_field on immutable key '%s'", key);
        return 0;
    }

    u8* p = ((u8*)pointer) + data->valueOffset;
    switch (data->valueType) {
        case LVT_U8:  *(u8*) p = smlua_to_integer(L, -1); break;
        case LVT_U16: *(u16*)p = smlua_to_integer(L, -1); break;
        case LVT_U32: *(u32*)p = smlua_to_integer(L, -1); break;
        case LVT_S8:  *(s8*) p = smlua_to_integer(L, -1); break;
        case LVT_S16: *(s16*)p = smlua_to_integer(L, -1); break;
        case LVT_S32: *(s32*)p = smlua_to_integer(L, -1); break;
        case LVT_F32: *(f32*)p = smlua_to_number(L, -1);  break;
        default:
            LOG_LUA("_set_field on unimplemented type '%d', key '%s'", data->valueType, key);
            return 0;
    }
    if (!gSmLuaConvertSuccess) {
        LOG_LUA("_set_field failed to retrieve value type '%d', key '%s'", data->valueType, key);
        return 0;
    }

    return 1;
}

void smlua_bind_cobject(void) {
    lua_State* L = gLuaState;

    smlua_bind_function(L, "_get_field", smlua__get_field);
    smlua_bind_function(L, "_set_field", smlua__set_field);

}