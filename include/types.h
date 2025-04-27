#ifndef _SM64_TYPES_H_
#define _SM64_TYPES_H_

// This file contains various data types used in Super Mario 64 that don't yet
// have an appropriate header.

#include <ultra64.h>
#include "macros.h"
#include "pc/network/version.h"
#include "pc/platform.h"

// Certain functions are marked as having return values, but do not
// actually return a value. This causes undefined behavior, which we'd rather
// avoid on modern GCC. This only impacts -O2 and can matter for both the function
// itself and functions that call it.
#ifdef AVOID_UB
    #define BAD_RETURN(cmd) void
#else
    #define BAD_RETURN(cmd) cmd
#endif

struct Controller
{
  /*0x00*/ s16 rawStickX;       //
  /*0x02*/ s16 rawStickY;       //
  /*0x04*/ f32 stickX;        // [-64, 64] positive is right
  /*0x08*/ f32 stickY;        // [-64, 64] positive is up
  /*0x0C*/ f32 stickMag;      // distance from center [0, 64]
  /*0x10*/ u16 buttonDown;
  /*0x12*/ u16 buttonPressed;
  /*0x14*/ u16 buttonReleased;
  /*0x18*/ OSContStatus *statusData;
  /*0x1C*/ OSContPad *controllerData;
  /*0x20*/ s32 port;
  /*ext */ s16 extStickX;       // additional (right) stick values
  /*ext */ s16 extStickY;
};

typedef f32 Vec2f[2];
typedef f32 Vec3f[3]; // X, Y, Z, where Y is up
typedef s16 Vec3s[3];
typedef s32 Vec3i[3];
typedef f32 Vec4f[4];
typedef s16 Vec4s[4];

typedef f32 Mat4[4][4];

typedef uintptr_t GeoLayout;
typedef uintptr_t LevelScript;
typedef s16 Movtex;
typedef s16 MacroObject;
typedef s16 Collision;
typedef s16 Trajectory;
typedef s16 PaintingData;
typedef uintptr_t BehaviorScript;
typedef u8 Texture;

typedef u8 Color[3];

enum SpTaskState {
    SPTASK_STATE_NOT_STARTED,
    SPTASK_STATE_RUNNING,
    SPTASK_STATE_INTERRUPTED,
    SPTASK_STATE_FINISHED,
    SPTASK_STATE_FINISHED_DP
};

enum AreaTimerType {
    AREA_TIMER_TYPE_NONE,
    AREA_TIMER_TYPE_LOOP,
    AREA_TIMER_TYPE_MAXIMUM,
};

struct SPTask
{
    /*0x00*/ OSTask task;
    /*0x40*/ OSMesgQueue *msgqueue;
    /*0x44*/ OSMesg msg;
    /*0x48*/ enum SpTaskState state;
}; // size = 0x4C, align = 0x8

struct VblankHandler
{
    OSMesgQueue *queue;
    OSMesg msg;
};

#define ANIM_FLAG_NOLOOP     (1 << 0) // 0x01
#define ANIM_FLAG_BACKWARD   (1 << 1) // 0x02
#define ANIM_FLAG_2          (1 << 2) // 0x04
#define ANIM_FLAG_HOR_TRANS  (1 << 3) // 0x08
#define ANIM_FLAG_VERT_TRANS (1 << 4) // 0x10
#define ANIM_FLAG_5          (1 << 5) // 0x20
#define ANIM_FLAG_6          (1 << 6) // 0x40
#define ANIM_FLAG_7          (1 << 7) // 0x80

struct Animation {
    /*0x00*/ s16 flags;
    /*0x02*/ s16 animYTransDivisor;
    /*0x04*/ s16 startFrame;
    /*0x06*/ s16 loopStart;
    /*0x08*/ s16 loopEnd;
    /*0x0A*/ s16 unusedBoneCount;
    /*0x0C*/ u16 *values;
    /*0x10*/ u16 *index;
    /*0x14*/ u32 length; // only used with Mario animations to determine how much to load. 0 otherwise.
    /*????*/ u32 valuesLength;
    /*????*/ u32 indexLength;
};

struct AnimationTable {
    u32 count;
    const struct Animation* const anims[];
};

#define ANIMINDEX_NUMPARTS(animindex) (sizeof(animindex) / sizeof(u16) / 6 - 1)
#define ANIM_FIELD_LENGTH(animindex) (sizeof(animindex) / sizeof(u16))

#define GRAPH_NODE_GUARD 0xAA

struct GraphNode
{
    s16 type; // structure type
    s16 flags; // hi = drawing layer, lo = rendering modes
    struct GraphNode *prev;
    u8 _guard1;
    struct GraphNode *next;
    u8 _guard2;
    struct GraphNode *parent;
    struct GraphNode *children;
    const void *georef;
    u8 extraFlags;
    u8 hookProcess;
};

struct AnimInfo
{
    /*0x00 0x38*/ s16 animID;
    /*0x02 0x3A*/ s16 animYTrans;
    /*0x04 0x3C*/ struct Animation *curAnim;
    /*0x08 0x40*/ s16 animFrame;
    /*0x0A 0x42*/ u16 animTimer;
    /*0x0C 0x44*/ s32 animFrameAccelAssist;
    /*0x10 0x48*/ s32 animAccel;
    s16 prevAnimFrame;
    s16 prevAnimID;
    u32 prevAnimFrameTimestamp;
    struct Animation *prevAnimPtr;
};

struct GraphNodeObject
{
    /*0x00*/ struct GraphNode node;
    /*0x14*/ struct GraphNode *sharedChild;
    /*0x18*/ s8 areaIndex;
    /*0x19*/ s8 activeAreaIndex;
    /*0x1A*/ Vec3s angle;
    /*0x20*/ Vec3f pos;
    Vec3s prevAngle;
    Vec3f prevPos;
    u32 prevTimestamp;
    Vec3f shadowPos;
    Vec3f prevShadowPos;
    u32 prevShadowPosTimestamp;
    bool shadowInvisible;
    bool disableAutomaticShadowPos;
    /*0x2C*/ Vec3f scale;
    Vec3f prevScale;
    u32 prevScaleTimestamp;
    /*0x38*/ struct AnimInfo animInfo;
    /*0x4C*/ struct SpawnInfo *unk4C;
    /*0x50*/ Mat4 *throwMatrix; // matrix ptr
    Mat4 prevThrowMatrix;
    u32 prevThrowMatrixTimestamp;
    Mat4 *throwMatrixPrev;
    /*0x54*/ Vec3f cameraToObject;
    u32 skipInterpolationTimestamp;
    bool skipInViewCheck;

    bool inited;
};

struct ObjectNode
{
    struct GraphNodeObject gfx;
    struct ObjectNode *next;
    struct ObjectNode *prev;
};

// NOTE: Since ObjectNode is the first member of Object, it is difficult to determine
// whether some of these pointers point to ObjectNode or Object.

#define OBJECT_MAX_BHV_STACK        16
#define OBJECT_NUM_REGULAR_FIELDS   0x50
#define OBJECT_NUM_CUSTOM_FIELDS    0x40
#define OBJECT_CUSTOM_FIELDS_START  (OBJECT_NUM_REGULAR_FIELDS)
#define OBJECT_NUM_FIELDS           (OBJECT_CUSTOM_FIELDS_START + OBJECT_NUM_CUSTOM_FIELDS)

struct Object
{
    /*0x000*/ struct ObjectNode header;
    /*0x068*/ struct Object *parentObj;
    /*0x06C*/ struct Object *prevObj;
    /*0x070*/ u32 collidedObjInteractTypes;
    /*0x074*/ s16 activeFlags;
    /*0x076*/ s16 numCollidedObjs;
    /*0x078*/ struct Object *collidedObjs[4];
    /*0x088*/
    union
    {
        // Object fields. See object_fields.h.
        u32 asU32[OBJECT_NUM_FIELDS];
        s32 asS32[OBJECT_NUM_FIELDS];
        s16 asS16[OBJECT_NUM_FIELDS][2];
        f32 asF32[OBJECT_NUM_FIELDS];
    } rawData;
    union {
        s16 *asS16P[OBJECT_NUM_FIELDS];
        s32 *asS32P[OBJECT_NUM_FIELDS];
        struct AnimationTable *asAnims[OBJECT_NUM_FIELDS];
        struct Waypoint *asWaypoint[OBJECT_NUM_FIELDS];
        struct ChainSegment *asChainSegment[OBJECT_NUM_FIELDS];
        struct Object *asObject[OBJECT_NUM_FIELDS];
        struct Surface *asSurface[OBJECT_NUM_FIELDS];
        void *asVoidPtr[OBJECT_NUM_FIELDS];
        const void *asConstVoidPtr[OBJECT_NUM_FIELDS];
    } ptrData;
    /*0x1C8*/ u32 unused1;
    /*0x1CC*/ const BehaviorScript *curBhvCommand;
    /*0x1D0*/ u32 bhvStackIndex;
    /*0x1D4*/ uintptr_t bhvStack[OBJECT_MAX_BHV_STACK];
    /*0x1F4*/ s16 bhvDelayTimer;
    /*0x1F6*/ s16 respawnInfoType;
    /*0x1F8*/ f32 hitboxRadius;
    /*0x1FC*/ f32 hitboxHeight;
    /*0x200*/ f32 hurtboxRadius;
    /*0x204*/ f32 hurtboxHeight;
    /*0x208*/ f32 hitboxDownOffset;
    /*0x20C*/ const BehaviorScript *behavior;
    /*0x210*/ u32 heldByPlayerIndex;
    /*0x214*/ struct Object *platform;
    /*0x218*/ Collision *collisionData;
    /*0x21C*/ Mat4 transform;
    /*0x25C*/ void *respawnInfo;
    /*?????*/ u8 coopFlags;
    /*?????*/ enum AreaTimerType areaTimerType;
    /*?????*/ u32 areaTimer;
    /*?????*/ u32 areaTimerDuration;
    /*?????*/ void (*areaTimerRunOnceCallback)(void);
    /*?????*/ u8 globalPlayerIndex;
    /*?????*/ struct Object* usingObj;
    /*?????*/ u8 hookRender;
    /*?????*/ u8 setHome;
    /*?????*/ u8 allowRemoteInteractions;
    /*?????*/ u8 ctx;
    /*?????*/ u32 firstSurface;
    /*?????*/ u32 numSurfaces;
};

struct ObjectHitbox
{
    /*0x00*/ u32 interactType;
    /*0x04*/ u8 downOffset;
    /*0x05*/ s8 damageOrCoinValue;
    /*0x06*/ s8 health;
    /*0x07*/ s8 numLootCoins;
    /*0x08*/ s16 radius;
    /*0x0A*/ s16 height;
    /*0x0C*/ s16 hurtboxRadius;
    /*0x0E*/ s16 hurtboxHeight;
};

struct Waypoint
{
    s16 flags;
    Vec3s pos;
};

struct Surface
{
    /*0x00*/ s16 type;
    /*0x02*/ s16 force;
    /*0x04*/ s8 flags;
    /*0x05*/ s8 room;
    /*0x06*/ s16 lowerY;
    /*0x08*/ s16 upperY;
    /*0x0A*/ Vec3s vertex1;
    /*0x10*/ Vec3s vertex2;
    /*0x16*/ Vec3s vertex3;
    /*0x1C*/ struct {
        f32 x;
        f32 y;
        f32 z;
    } normal;
    /*0x28*/ f32 originOffset;
    /*0x2C*/ struct Object *object;
    Vec3s prevVertex1;
    Vec3s prevVertex2;
    Vec3s prevVertex3;
    u32 modifiedTimestamp;
};

struct MarioBodyState
{
    /*0x00*/ u32 action;
    /*0x04*/ s8 capState; /// see MarioCapGSCId
    /*0x05*/ s8 eyeState;
    /*0x06*/ s8 handState;
    /*0x07*/ s8 wingFlutter; /// whether Mario's wing cap wings are fluttering
    /*0x08*/ s16 modelState;
    /*0x0A*/ s8 grabPos;
    /*0x0B*/ u8 punchState; /// 2 bits for type of punch, 6 bits for punch animation timer
    /*0x0C*/ Vec3s torsoAngle;
    /*0x12*/ Vec3s headAngle;
    /*0x18*/ Vec3f heldObjLastPosition; /// also known as HOLP
    /*????*/ Vec3f torsoPos;
    /*????*/ Vec3f handFootPos[4];
    /*????*/ u32 updateTorsoTime;
    /*????*/ Vec3f headPos;
    /*????*/ u32 updateHeadPosTime;
    /*????*/ u16 shadeR; /// shadow red value
    /*????*/ u16 shadeG; /// shadow green value
    /*????*/ u16 shadeB; /// shadow blue value
    /*????*/ u16 lightR; /// light red value
    /*????*/ u16 lightG; /// light green value
    /*????*/ u16 lightB; /// light blue value
    /*????*/ f32 lightingDirX;
    /*????*/ f32 lightingDirY;
    /*????*/ f32 lightingDirZ;
    /*????*/ u8 allowPartRotation;
    /*????*/ bool mirrorMario; // some of these fields are updated for Mirror Mario too
    // u8 padding[4];
};

struct OffsetSizePair
{
    u32 offset;
    u32 size;
};

struct MarioAnimDmaRelatedThing
{
    u32 count;
    u8 *srcAddr;
    struct OffsetSizePair anim[1]; // dynamic size
};

struct MarioAnimation
{
    struct MarioAnimDmaRelatedThing *animDmaTable;
    u8 *currentAnimAddr;
    struct Animation *targetAnim;
    u8 padding[4];
};

struct MarioState
{
    // Please try to keep this 32/64 bit aligned.
    // Bit alignment can increase perforamance and
    // reduce the memory footprint.
    //
    // Structure size was reduced by 32 bytes and fields
    // and been moved for performance and size.
    // https://en.wikipedia.org/wiki/Data_structure_alignment
    //
    // I personally also find it easier to read now.
    // - Prince Frizzy
    
    u16 playerIndex;
    u16 input;
    s16 numCoins;
    s16 numStars;
    
    s8 numLives;
    s8 numKeys; // Unused key mechanic
    s16 health;
    u8 hurtCounter;
    u8 healCounter;
    u8 isSnoring;
    u8 freeze;
    
    u32 cap;
    u16 capTimer;
    s16 invincTimer;
    
    u8 skipWarpInteractionsTimer;
    u8 squishTimer;
    u8 bounceSquishTimer;
    s8 knockbackTimer;
    u8 wallKickTimer;
    u8 doubleJumpTimer;
    u8 specialTripleJump;
    u8 fadeWarpOpacity;
    
    u8 visibleToEnemies;
    u8 wasNetworkVisible;
    s16 dialogId;
    s16 prevNumStarsForDialog;
    s16 unkB0;
    
    u32 action;
    u32 prevAction;
    
    u32 actionArg;
    u16 actionTimer;
    u16 actionState;
    
    u32 flags;
    f32 quicksandDepth;
    
    struct Controller *controller;
    struct MarioBodyState *marioBodyState;
    struct Character *character;
    
    u32 terrainSoundAddend;
    
    Vec3f pos;
    Vec3f nonInstantWarpPos;
    Vec3f vel;
    f32 slideVelX;
    f32 slideVelZ;
    f32 forwardVel;
    
    f32 peakHeight;
    f32 intendedMag;
    s16 intendedYaw;
    u8 framesSinceA;
    u8 framesSinceB;
    
    Vec3s faceAngle;
    Vec3s angleVel;
    s16 slideYaw;
    s16 twirlYaw;
    
    struct Object *heldObj;
    struct Object *heldByObj;
    struct Object *interactObj;
    struct Object *riddenObj;
    struct Object *usedObj;
    struct Object *marioObj;
    struct Object *bubbleObj;
    
    u32 collidedObjInteractTypes;
    u32 particleFlags;
    
    struct MarioAnimation *animation;
    // Variables for a spline curve animation (used for the flight path in the grand star cutscene)
    Vec4s *splineKeyframe;
    f32 splineKeyframeFraction;
    s32 splineState;
    f32 curAnimOffset;
    
    f32 minimumBoneY;
    
    struct Surface *wall;
    struct Surface *ceil;
    struct Surface *floor;
    struct SpawnInfo *spawnInfo;
    struct Area *area;
    struct PlayerCameraState *statusForCamera;
    
    f32 ceilHeight;
    f32 floorHeight;
    
    Vec3f wallNormal;
    f32 unkC4;
    
    s16 floorAngle;
    s16 waterLevel;
    s16 currentRoom;
};

struct TextureInfo
{
    u8* texture;
    u8 bitSize;
    u32 width;
    u32 height;
    const char* name;
};

#define PLAY_MODE_NORMAL 0
#define PLAY_MODE_PAUSED 2
#define PLAY_MODE_CHANGE_AREA 3
#define PLAY_MODE_CHANGE_LEVEL 4
#define PLAY_MODE_FRAME_ADVANCE 5

#define MAX_PLAYERS 16

#define COOP_OBJ_FLAG_NETWORK     (1 << 0)
#define COOP_OBJ_FLAG_LUA         (1 << 1)
#define COOP_OBJ_FLAG_NON_SYNC    (1 << 2)
#define COOP_OBJ_FLAG_INITIALIZED (1 << 3)

#include "game/characters.h"
#include "data/dynos.c.h"

#endif // _SM64_TYPES_H_
