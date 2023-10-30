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
void smlua_level_util_change_area(s32 areaIndex);
struct CustomLevelInfo* smlua_level_util_get_info(s16 levelNum);
struct CustomLevelInfo* smlua_level_util_get_info_from_short_name(const char* shortName);
struct CustomLevelInfo* smlua_level_util_get_info_from_course_num(u8 courseNum);
s16 level_register(const char* scriptEntryName, s16 courseNum, const char* fullName, const char* shortName, u32 acousticReach, u32 echoLevel1, u32 echoLevel2, u32 echoLevel3);
bool level_is_vanilla_level(s16 levelNum);
bool warp_to_warpnode(s32 aLevel, s32 aArea, s32 aAct, s32 aWarpId);
bool warp_to_level(s32 aLevel, s32 aArea, s32 aAct);
bool warp_restart_level(void);
bool warp_to_start_level(void);
bool warp_exit_level(s32 aDelay);
bool warp_to_castle(s32 aLevel);

#endif
