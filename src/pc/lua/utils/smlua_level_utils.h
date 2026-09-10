#ifndef SMLUA_LEVEL_UTILS_H
#define SMLUA_LEVEL_UTILS_H

#include "behavior_table.h"                 // for enum BehaviorId
#include "pc/lua/utils/smlua_model_utils.h" // for enum ModelExtendedId
#include "game/level_update.h"              // for enum MarioSpawnType
#include "game/area.h"                      // for struct ObjectWarpNode and struct SpawnInfo

struct CustomLevelInfo {
    LevelScript* script;
    char* scriptEntryName;
    s16 courseNum;
    s16 levelNum;
    char* fullName;
    char* shortName;
    u32 acousticReach;
    u32 echoLevel1;
    u32 echoLevel2;
    u32 echoLevel3;
    s32 modIndex;
    struct CustomLevelInfo* next;
};

struct CustomWarpNode {
    struct ObjectWarpNode node;
    struct SpawnInfo spawnInfo;
    enum MarioSpawnType marioSpawnType;
};

#define CUSTOM_LEVEL_NUM_START 50

void smlua_level_util_reset(void);
/* |description|Instantly changes the current area to `areaIndex`|descriptionEnd| */
void smlua_level_util_change_area(s32 areaIndex);
/* |description|Gets information on a custom level from `levelNum`|descriptionEnd| */
struct CustomLevelInfo* smlua_level_util_get_info(s16 levelNum);
/* |description|Gets information on a custom level from `shortName`|descriptionEnd| */
struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(const char* shortName);
/* |description|Gets information on a custom level from `courseNum`|descriptionEnd| */
struct CustomLevelInfo* smlua_level_util_get_info_from_course_num(u8 courseNum);
/* |description|Registers a fully custom level. Level ID begins at 50|descriptionEnd| */
s16 level_register(const char* scriptEntryName, s16 courseNum, const char* fullName, const char* shortName, u32 acousticReach, u32 echoLevel1, u32 echoLevel2, u32 echoLevel3);
/* |description|Checks if `levelNum` is a vanilla level|descriptionEnd| */
bool level_is_vanilla_level(s16 levelNum);
/* |description|Warps to `aWarpId` of `aArea` in `aLevel` during `aAct`|descriptionEnd| */
bool warp_to_warpnode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId);
/* |description|Warps to `aArea` of `aLevel` in `aAct`|descriptionEnd| */
bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
/* |description|Restarts the current level|descriptionEnd| */
bool warp_restart_level(void);
/* |description|Warps to the start level (Castle Grounds by default)|descriptionEnd| */
bool warp_to_start_level(void);
/* |description|Exits the current level after `aDelay`|descriptionEnd| */
bool warp_exit_level(s32 aDelay);
/* |description|Warps back to the castle from `aLevel`|descriptionEnd| */
bool warp_to_castle(s32 aLevel);

/* |description|
Creates a warp node in level `levelNum` and area `areaIndex` with id `id` to the warp node `destNode` in level `destLevel` and area `destArea`.
If `checkpoint` is true, Mario will warp directly to this node if he enters the level again (after a death for example).
`marioSpawnType` indicates which kind of action Mario should perform when exiting this node. Its value must be one of the `MARIO_SPAWN_` constants.
|descriptionEnd| */
struct CustomWarpNode *level_create_warp_node(u8 levelNum, u8 areaIndex, u8 id, enum MarioSpawnType marioSpawnType, u8 destLevel, u8 destArea, u8 destNode, bool checkpoint);

/* |description|
Creates a warp node in level `levelNum` and area `areaIndex` with id `id` to the warp node `destNode` in level `destLevel` and area `destArea`, and associates it an object described by `pos`, `angle`, `modelId`, `behaviorId` and `behParams`. Note that the object must have the `INTERACT_WARP` interaction type for the warp to work properly.
If `checkpoint` is true, Mario will warp directly to this node if he enters the level again (after a death for example).
`marioSpawnType` indicates which kind of action Mario should perform when exiting this node. Its value must be one of the `MARIO_SPAWN_` constants.
|descriptionEnd| */
struct CustomWarpNode *level_create_warp_node_with_object(u8 levelNum, u8 areaIndex, u8 id, enum MarioSpawnType marioSpawnType, u8 destLevel, u8 destArea, u8 destNode, bool checkpoint, Vec3f pos, Vec3s angle, enum ModelExtendedId modelId, enum BehaviorId behaviorId, u32 behParams);

/* |description|
Gets the warp node in level `levelNum` and area `areaIndex` with id `id`.
Only the warp nodes created by `level_create_warp_node` or `level_create_warp_node_with_object` can be returned by this function.
|descriptionEnd| */
struct CustomWarpNode *level_get_warp_node(u8 levelNum, u8 areaIndex, u8 id);

/* |description|
Deletes the warp node in level `levelNum` and area `areaIndex` with id `id`.
Only the warp nodes created by `level_create_warp_node` or `level_create_warp_node_with_object` can be deleted by this function.
|descriptionEnd| */
void level_delete_warp_node(u8 levelNum, u8 areaIndex, u8 id);

/* |description|
Deletes all the warp nodes in level `levelNum`.
Only the warp nodes created by `level_create_warp_node` or `level_create_warp_node_with_object` can be deleted by this function.
|descriptionEnd| */
void level_clear_warp_nodes(u8 levelNum);

void level_register_custom_warp_nodes(u8 levelNum, u8 areaIndex);
void level_clear_warp_node_objects(u8 levelNum, u8 areaIndex);
enum MarioSpawnType level_get_warp_spawn_type_from_object(u8 levelNum, u8 areaIndex, struct Object *obj);

#endif
