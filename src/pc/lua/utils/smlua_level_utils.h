#ifndef SMLUA_LEVEL_UTILS_H
#define SMLUA_LEVEL_UTILS_H

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

#endif
