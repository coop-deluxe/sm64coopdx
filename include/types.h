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
    // For optimization reasons, See MarioState
    
    s32 port;
    f32 stickX;        // [-64, 64] positive is right
    f32 stickY;        // [-64, 64] positive is up
    f32 stickMag;      // distance from center [0, 64]
    s16 rawStickX;
    s16 rawStickY;
    s16 extStickX;       // additional (right) stick values
    s16 extStickY;
    
    u16 buttonDown;
    u16 buttonPressed;
    u16 buttonReleased;

    OSContStatus *statusData;
    OSContPad *controllerData;
};

typedef f32 Vec2f[2]; // X, Y
typedef s16 Vec2s[2];
typedef s32 Vec2i[2];
typedef f32 Vec3f[3]; // X, Y, Z, where Y is up
typedef s16 Vec3s[3];
typedef s32 Vec3i[3];
typedef f32 Vec4f[4]; // X, Y, Z, W
typedef s16 Vec4s[4];
typedef s32 Vec4i[4];

// Pointer types for return values
typedef f32 *Vec2fp;
typedef s16 *Vec2sp;
typedef s32 *Vec2ip;
typedef f32 *Vec3fp;
typedef s16 *Vec3sp;
typedef s32 *Vec3ip;
typedef f32 *Vec4fp;
typedef s16 *Vec4sp;
typedef s32 *Vec4ip;

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
    // TODO: Optimize this later if possible.
    
    s16 flags;
    s16 animYTransDivisor;
    s16 startFrame;
    s16 loopStart;
    s16 loopEnd;
    s16 unusedBoneCount;
    u16 *values;
    u16 *index;
    u32 length; // only used with Mario animations to determine how much to load. 0 otherwise.
    u32 valuesLength;
    u32 indexLength;
};

struct AnimationTable {
    u32 count;
    const struct Animation *const anims[];
};

#define ANIMINDEX_NUMPARTS(animindex) (sizeof(animindex) / sizeof(u16) / 6 - 1)
#define ANIM_FIELD_LENGTH(animindex) (sizeof(animindex) / sizeof(u16))

#define GRAPH_NODE_GUARD 0xDEADBEEF

struct GraphNode
{
    // For optimization reasons, See MarioState
    
#ifdef DEBUG
    uintptr_t _guard1;
#endif
    struct GraphNode *prev;
    struct GraphNode *next;
    struct GraphNode *parent;
    struct GraphNode *children;
    const void *georef;
    
    s16 type; // structure type
    s16 flags; // hi = drawing layer, lo = rendering modes
    u8 extraFlags;
    u8 hookProcess;
    s16 padding;
    
#ifdef DEBUG
    uintptr_t _guard2;
#endif
};

struct AnimInfo
{
    // For optimization reasons, See MarioState
    
    struct Animation *curAnim;
    struct Animation *prevAnimPtr;
    
    s16 animID;
    s16 prevAnimID;
    
    s16 animFrame;
    s16 prevAnimFrame;
    
    u32 prevAnimFrameTimestamp;
    s32 animFrameAccelAssist;
    
    s32 animAccel;
    u16 animTimer;
    s16 animYTrans;
};

struct GraphNodeObject
{
    // For optimization reasons, See MarioState
    
    struct GraphNode node;
    struct GraphNode *sharedChild;
    struct SpawnInfo *unk4C;
    
    Mat4 *throwMatrix; // matrix ptr
    Mat4 *throwMatrixPrev;
    Mat4 prevThrowMatrix;
    
    Vec3s angle;
    Vec3s prevAngle;
    
    Vec3f pos;
    Vec3f prevPos;
    
    Vec3f shadowPos;
    Vec3f prevShadowPos;
    
    Vec3f scale;
    Vec3f prevScale;
    
    Vec3f cameraToObject;
    
    u32 prevTimestamp;
    u32 prevShadowPosTimestamp;
    u32 prevScaleTimestamp;
    u32 prevThrowMatrixTimestamp;
    u32 skipInterpolationTimestamp;
    
    struct AnimInfo animInfo;
    
    s8 areaIndex;
    s8 activeAreaIndex;
    
    bool shadowInvisible;
    bool disableAutomaticShadowPos;
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
    // For optimization reasons, See MarioState
    
    struct ObjectNode header;
    struct Object *prevObj;
    struct Object *parentObj;
    struct Object *usingObj;
    struct Object *platform;
    struct Object *collidedObjs[4];
    Collision *collisionData;
    void *respawnInfo;
    void (*areaTimerRunOnceCallback)(void);
    const BehaviorScript *behavior;
    const BehaviorScript *curBhvCommand;
    uintptr_t bhvStack[OBJECT_MAX_BHV_STACK];
    
    u32 bhvStackIndex;
    s16 bhvDelayTimer;
    s16 activeFlags;
    
    u32 collidedObjInteractTypes;
    s16 numCollidedObjs;
    s16 respawnInfoType;
    
    f32 hitboxRadius;
    f32 hitboxHeight;
    
    f32 hurtboxRadius;
    f32 hurtboxHeight;
    
    f32 hitboxDownOffset;
    u32 unused1;
    
    u32 areaTimer;
    u32 areaTimerDuration;
    enum AreaTimerType areaTimerType;
    
    Mat4 transform;
    
    u32 firstSurface;
    u32 numSurfaces;
    
    u32 heldByPlayerIndex;
    
    u8 setHome;
    u8 ctx;
    u8 allowRemoteInteractions;
    u8 globalPlayerIndex;
    u8 coopFlags;
    u8 hookRender;
    
    union
    {
        // Object fields. See object_fields.h.
        u16 asU16[OBJECT_NUM_FIELDS][2];
        s16 asS16[OBJECT_NUM_FIELDS][2];
        u32 asU32[OBJECT_NUM_FIELDS];
        s32 asS32[OBJECT_NUM_FIELDS];
        f32 asF32[OBJECT_NUM_FIELDS];
    } rawData;
    
    union
    {
        s16 *asS16P[OBJECT_NUM_FIELDS];
        u16 *asU16P[OBJECT_NUM_FIELDS];
        s32 *asS32P[OBJECT_NUM_FIELDS];
        u32 *asU32P[OBJECT_NUM_FIELDS];
        f32 *asF32P[OBJECT_NUM_FIELDS];
        struct AnimationTable *asAnims[OBJECT_NUM_FIELDS];
        struct Waypoint *asWaypoint[OBJECT_NUM_FIELDS];
        struct ChainSegment *asChainSegment[OBJECT_NUM_FIELDS];
        struct Object *asObject[OBJECT_NUM_FIELDS];
        struct Surface *asSurface[OBJECT_NUM_FIELDS];
        void *asVoidPtr[OBJECT_NUM_FIELDS];
        const void *asConstVoidPtr[OBJECT_NUM_FIELDS];
    } ptrData;
};

struct ObjectHitbox
{
    u32 interactType;
    s8 health;
    s8 damageOrCoinValue;
    s8 numLootCoins;
    u8 downOffset;
    s16 radius;
    s16 height;
    s16 hurtboxRadius;
    s16 hurtboxHeight;
};

struct Waypoint
{
    s16 flags;
    Vec3s pos;
};

struct Surface
{
    // For optimization reasons, See MarioState
    
    s16 type;
    s8 flags;
    s8 room;
    s16 force;
    s16 lowerY;
    s16 upperY;
    
    Vec3s vertex1;
    Vec3s vertex2;
    Vec3s vertex3;
    Vec3s prevVertex1;
    Vec3s prevVertex2;
    Vec3s prevVertex3;
    struct {
      f32 x;
      f32 y;
      f32 z;
    } normal;
    
    f32 originOffset;
    u32 modifiedTimestamp;
    
    struct Object *object;
};

enum MarioAnimPart {
    MARIO_ANIM_PART_NONE,

    MARIO_ANIM_PART_ROOT,
    MARIO_ANIM_PART_BUTT,
    MARIO_ANIM_PART_TORSO,
    MARIO_ANIM_PART_HEAD,
    MARIO_ANIM_PART_UPPER_LEFT,
    MARIO_ANIM_PART_LEFT_ARM,
    MARIO_ANIM_PART_LEFT_FOREARM,
    MARIO_ANIM_PART_LEFT_HAND,
    MARIO_ANIM_PART_UPPER_RIGHT,
    MARIO_ANIM_PART_RIGHT_ARM,
    MARIO_ANIM_PART_RIGHT_FOREARM,
    MARIO_ANIM_PART_RIGHT_HAND,
    MARIO_ANIM_PART_LOWER_LEFT,
    MARIO_ANIM_PART_LEFT_THIGH,
    MARIO_ANIM_PART_LEFT_LEG,
    MARIO_ANIM_PART_LEFT_FOOT,
    MARIO_ANIM_PART_LOWER_RIGHT,
    MARIO_ANIM_PART_RIGHT_THIGH,
    MARIO_ANIM_PART_RIGHT_LEG,
    MARIO_ANIM_PART_RIGHT_FOOT,

    MARIO_ANIM_PART_MAX,
};

struct MarioBodyState
{
    // For optimization reasons, See MarioState
    
    s8 capState; /// see MarioCapGSCId
    s8 eyeState;
    s8 handState;
    u8 punchState; /// 2 bits for type of punch, 6 bits for punch animation timer
    s16 modelState;
    u8 allowPartRotation;
    s8 grabPos;
    
    s8 wingFlutter; /// whether Mario's wing cap wings are fluttering
    bool mirrorMario; // some of these fields are updated for Mirror Mario too
    
    Vec3s headAngle;
    Vec3s torsoAngle;
    
    Vec3f headPos;
    Vec3f torsoPos;
    Vec3f heldObjLastPosition; /// also known as HOLP

    Vec3f animPartsPos[MARIO_ANIM_PART_MAX];
    u32 currAnimPart;
    
    u32 updateTorsoTime;
    u32 updateHeadPosTime;
    
    u32 action;
    
    u16 shadeR; /// shadow red value
    u16 shadeG; /// shadow green value
    u16 shadeB; /// shadow blue value
    u16 lightR; /// light red value
    u16 lightG; /// light green value
    u16 lightB; /// light blue value
    f32 lightingDirX;
    f32 lightingDirY;
    f32 lightingDirZ;
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
    u8 *texture;
    const char *name;
    u32 width;
    u32 height;
    u8 bitSize;
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
