#include "dynos.cpp.h"
extern "C" {
#include "game/segment2.h"
#include "game/save_file.h"
#include "levels/scripts.h"
#include "pc/lua/utils/smlua_level_utils.h"
}

//
// Const
//

extern "C" {
extern const BehaviorScript *sWarpBhvSpawnTable[];
#include "engine/level_script.h"
}

#define DYNOS_LEVEL_MOD_INDEX_VANILLA (-1)

extern void *gDynosLevelScriptsOriginal[LEVEL_COUNT];

void DynOS_Level_ParseScript(const void *aScript, s32 (*aPreprocessFunction)(u8, void *));

//
// Data
//

struct DynosWarp {
/* 0 */ s16 mArea = 0;
/* 1 */ s16 mId = 0;
/* 2 */ s16 mType = -1;
/* 3 */ s16 mPosX = 0;
/* 4 */ s16 mPosY = 0;
/* 5 */ s16 mPosZ = 0;
/* 6 */ s16 mAngle = 0;
/* 7 */ s16 mDestLevel = 0;
/* 8 */ s16 mDestArea = 0;
/* 9 */ s16 mDestId = 0;
};

struct DynosLevelScript {
    void *mLevelScript;
    s32 mModIndex;
};

static DynosLevelScript sDynosLevelScripts[LEVEL_COUNT] = { { NULL, DYNOS_LEVEL_MOD_INDEX_VANILLA } };
static Array<DynosWarp> sDynosLevelWarps[LEVEL_COUNT] = { Array<DynosWarp>() };

u64 DynOS_Level_CmdGet(void *aCmd, u64 aOffset) {
    u64 _Offset = (((aOffset) & 3llu) | (((aOffset) & ~3llu) << (sizeof(void *) >> 3llu)));
    return *((u64 *) (u64(aCmd) + _Offset));
}

LvlCmd *DynOS_Level_CmdNext(LvlCmd *aCmd) {
    u64 aCmdSize = aCmd->mSize;
    u64 _Offset = (((aCmdSize) & 3llu) | (((aCmdSize) & ~3llu) << (sizeof(void *) >> 3llu)));
    return (LvlCmd*) (u64(aCmd) + _Offset);
}

//
// Init
//

static s32 DynOS_Level_PreprocessMasterScript(u8 aType, void *aCmd) {
    static bool sDynosScriptExecLevelTable = false;
    static s32 sDynosLevelNum = -1;

    if (sDynosScriptExecLevelTable) {
        switch (aType) {

            // JUMP_IF
            case 0x0C: {
                sDynosLevelNum = (s32) DynOS_Level_CmdGet(aCmd, 0x04);
            } return 0;

            // EXECUTE
            case 0x00: {
                void *_Script = (void *) DynOS_Level_CmdGet(aCmd, 0x0C);
                if (sDynosLevelNum >= 0 && sDynosLevelNum < LEVEL_COUNT && !sDynosLevelScripts[sDynosLevelNum].mLevelScript) {
                    sDynosLevelScripts[sDynosLevelNum].mLevelScript = _Script;
                    sDynosLevelScripts[sDynosLevelNum].mModIndex = DYNOS_LEVEL_MOD_INDEX_VANILLA;
                    gDynosLevelScriptsOriginal[sDynosLevelNum] = _Script;
                }
                sDynosLevelNum = -1;
            } return 2;

            // EXIT or SLEEP
            case 0x02:
            case 0x03:
                return 3;
        }
    } else if (aType == 0x06) { // JUMP_LINK
        sDynosScriptExecLevelTable = true;
        return 0;
    }
    return 0;
}

static s32 sDynosCurrentLevelNum;
static u8 sDynosAreaIndex = 0;

inline static DynosWarp *DynOS_Level_GetWarpStruct(u8 aId) {
    for (s32 i = 0; i != sDynosLevelWarps[sDynosCurrentLevelNum].Count(); ++i) {
        if (sDynosLevelWarps[sDynosCurrentLevelNum][i].mArea == sDynosAreaIndex &&
            sDynosLevelWarps[sDynosCurrentLevelNum][i].mId == aId) {
            return &sDynosLevelWarps[sDynosCurrentLevelNum][i];
        }
    }
    DynosWarp _Warp;
    _Warp.mArea = sDynosAreaIndex;
    _Warp.mId = aId;
    sDynosLevelWarps[sDynosCurrentLevelNum].Add(_Warp);
    return &sDynosLevelWarps[sDynosCurrentLevelNum][sDynosLevelWarps[sDynosCurrentLevelNum].Count() - 1];
};

static s32 DynOS_Level_PreprocessScript(u8 aType, void *aCmd) {
    switch (aType) {

        // AREA
        case 0x1F: {
            sDynosAreaIndex = (u8) DynOS_Level_CmdGet(aCmd, 2);
        } break;

        // OBJECT
        case 0x24: {
            const BehaviorScript *bhv = (const BehaviorScript *) DynOS_Level_CmdGet(aCmd, 20);
            for (s32 i = 0; i < 20; ++i) {
                if (sWarpBhvSpawnTable[i] == bhv) {
                    DynosWarp *_Warp = DynOS_Level_GetWarpStruct(((((u32) DynOS_Level_CmdGet(aCmd, 16)) >> 16) & 0xFF));
                    if (_Warp->mType == -1) {
                        _Warp->mType = i;
                        _Warp->mPosX = (s16) DynOS_Level_CmdGet(aCmd, 4);
                        _Warp->mPosY = (s16) DynOS_Level_CmdGet(aCmd, 6);
                        _Warp->mPosZ = (s16) DynOS_Level_CmdGet(aCmd, 8);
                        _Warp->mAngle = ((s16) DynOS_Level_CmdGet(aCmd, 12) * 0x8000) / 180;
                    }
                    break;
                }
            }
        } break;

        // WARP_NODE or PAINTING_WARP_NODE
        case 0x26:
        case 0x27: {
            DynosWarp *_Warp = DynOS_Level_GetWarpStruct((u8) DynOS_Level_CmdGet(aCmd, 2));
            if (_Warp->mDestLevel == 0) {
                _Warp->mDestLevel = (u8) DynOS_Level_CmdGet(aCmd, 3);
                _Warp->mDestArea = (u8) DynOS_Level_CmdGet(aCmd, 4);
                _Warp->mDestId = (u8) DynOS_Level_CmdGet(aCmd, 5);
            }
        } break;

        // SLEEP or SLEEP_BEFORE_EXIT
        case 0x03:
        case 0x04:
            return 3;
    }

    return 0;
}

// Runs only once
void DynOS_Level_Init() {
    static bool sInited = false;
    if (!sInited) {

        // Level warps
        for (sDynosCurrentLevelNum = 0; sDynosCurrentLevelNum < LEVEL_COUNT; ++sDynosCurrentLevelNum) {
            sDynosLevelScripts[sDynosCurrentLevelNum].mLevelScript = gDynosLevelScriptsOriginal[sDynosCurrentLevelNum];
            sDynosLevelScripts[sDynosCurrentLevelNum].mModIndex = DYNOS_LEVEL_MOD_INDEX_VANILLA;
            if (sDynosLevelScripts[sDynosCurrentLevelNum].mLevelScript) {
                DynOS_Level_ParseScript(sDynosLevelScripts[sDynosCurrentLevelNum].mLevelScript, DynOS_Level_PreprocessScript);
            }
        }

        // Done
        sInited = true;
    }
}

//
// Common
//

s8 DynOS_Level_GetCourse(s32 aLevel) {
    return get_level_course_num(aLevel);
}

void DynOS_Level_Override(void* originalScript, void* newScript, s32 modIndex) {
    for (s32 i = 0; i < LEVEL_COUNT; i++) {
        if (sDynosLevelScripts[i].mLevelScript == originalScript) {
            sDynosCurrentLevelNum = i;
            sDynosLevelWarps[i].Clear();
            DynOS_Level_ParseScript(newScript, DynOS_Level_PreprocessScript);
            sDynosLevelScripts[i].mLevelScript = newScript;
            sDynosLevelScripts[i].mModIndex = modIndex;
            return;
        }
    }
}

void DynOS_Level_Unoverride() {
    for (s32 i = 0; i < LEVEL_COUNT; i++) {
        sDynosCurrentLevelNum = i;
        sDynosLevelWarps[i].Clear();
        sDynosLevelScripts[i].mLevelScript = gDynosLevelScriptsOriginal[i];
        sDynosLevelScripts[i].mModIndex = DYNOS_LEVEL_MOD_INDEX_VANILLA;
        DynOS_Level_ParseScript(sDynosLevelScripts[i].mLevelScript, DynOS_Level_PreprocessScript);
    }
}

const void *DynOS_Level_GetScript(s32 aLevel) {
    if (aLevel >= CUSTOM_LEVEL_NUM_START) {
        struct CustomLevelInfo* info = smlua_level_util_get_info(aLevel);
        if (!info || !info->script) { return NULL; }
        return info->script;
    }

    DynOS_Level_Init();
    return sDynosLevelScripts[aLevel].mLevelScript;
}

s32 DynOS_Level_GetModIndex(s32 aLevel) {
    if (aLevel >= CUSTOM_LEVEL_NUM_START) {
        struct CustomLevelInfo* info = smlua_level_util_get_info(aLevel);
        if (!info || !info->script) { return DYNOS_LEVEL_MOD_INDEX_VANILLA; }
        return info->modIndex;
    }

    DynOS_Level_Init();
    return sDynosLevelScripts[aLevel].mModIndex;
}

bool DynOS_Level_IsVanillaLevel(s32 aLevel) {
    DynOS_Level_Init();

    if (aLevel >= LEVEL_MIN && aLevel < LEVEL_COUNT) {
        return sDynosLevelScripts[aLevel].mLevelScript == gDynosLevelScriptsOriginal[aLevel];
    }
    return false;
}

//
// Level Script Preprocessing
// - Ifs are always true
// - Skips are always false
// - Loops break after the first loop
//

struct Stack {
    u64 mData[32];
    s32 mBaseIndex;
    s32 mTopIndex;
};

template <typename T>
static void StackPush(Stack& aStack, const T &aValue) {
    if (aStack.mTopIndex >= 0) {
        aStack.mData[aStack.mTopIndex] = u64(aValue);
        aStack.mTopIndex++;
    }
}

template <typename T>
static T StackPop(Stack& aStack) {
    if (aStack.mTopIndex <= 0) {
        return (T) 0;
    }
    aStack.mTopIndex--;
    return (T) aStack.mData[aStack.mTopIndex];
}

static LvlCmd *DynOS_Level_CmdExecute(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd));
    StackPush(aStack, aStack.mBaseIndex);
    aStack.mBaseIndex = aStack.mTopIndex;
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 12);
}

static LvlCmd *DynOS_Level_CmdExitAndExecute(Stack &aStack, LvlCmd *aCmd) {
    aStack.mTopIndex = aStack.mBaseIndex;
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 12);
}

static LvlCmd *DynOS_Level_CmdExit(Stack &aStack, LvlCmd *aCmd) {
    aStack.mTopIndex = aStack.mBaseIndex;
    aStack.mBaseIndex = StackPop<s32>(aStack);
    return StackPop<LvlCmd *>(aStack);
}

static LvlCmd *DynOS_Level_CmdJump(Stack &aStack, LvlCmd *aCmd) {
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 4);
}

static LvlCmd *DynOS_Level_CmdJumpLink(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd));
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 4);
}

static LvlCmd *DynOS_Level_CmdReturn(Stack &aStack, UNUSED LvlCmd *aCmd) {
    return StackPop<LvlCmd *>(aStack);
}

static LvlCmd *DynOS_Level_CmdJumpLinkPushArg(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd));
    StackPush(aStack, DynOS_Level_CmdGet(aCmd, 2));
    return DynOS_Level_CmdNext(aCmd);
}

static LvlCmd *DynOS_Level_CmdJumpRepeat(Stack &aStack, LvlCmd *aCmd) {
    aStack.mTopIndex -= 2;
    return DynOS_Level_CmdNext(aCmd);
}

static LvlCmd *DynOS_Level_CmdLoopBegin(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd));
    StackPush(aStack, 0);
    return DynOS_Level_CmdNext(aCmd);
}

static LvlCmd *DynOS_Level_CmdLoopUntil(Stack &aStack, LvlCmd *aCmd) {
    aStack.mTopIndex -= 2;
    return DynOS_Level_CmdNext(aCmd);
}

static LvlCmd *DynOS_Level_CmdJumpIf(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd)); /* Not an error, that's intentional */
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 8);
}

static LvlCmd *DynOS_Level_CmdJumpLinkIf(Stack &aStack, LvlCmd *aCmd) {
    StackPush(aStack, DynOS_Level_CmdNext(aCmd));
    return (LvlCmd *) DynOS_Level_CmdGet(aCmd, 8);
}

static LvlCmd *DynOS_Level_CmdJumpArea(Stack &aStack, LvlCmd *aCmd, s32 (*aPreprocessFunction)(u8, void *)) {
    DynOS_Level_ParseScript((const void *) DynOS_Level_CmdGet(aCmd, 8), aPreprocessFunction);
    return DynOS_Level_CmdNext(aCmd);
}

void DynOS_Level_ParseScript(const void *aScript, s32 (*aPreprocessFunction)(u8, void *)) {
    Stack _Stack;
    _Stack.mBaseIndex = -1;
    _Stack.mTopIndex = 0;
    for (LvlCmd *_Cmd = (LvlCmd *) aScript; _Cmd != NULL;) {
        u8 _CmdType = (_Cmd->mType & 0xFF);
        s32 _Action = aPreprocessFunction(_CmdType, (void *) _Cmd);
        switch (_Action) {
            case 0:
                switch (_CmdType) {
                    case 0x00: _Cmd = DynOS_Level_CmdExecute(_Stack, _Cmd);         break;
                    case 0x01: _Cmd = DynOS_Level_CmdExitAndExecute(_Stack, _Cmd);  break;
                    case 0x02: _Cmd = DynOS_Level_CmdExit(_Stack, _Cmd);            break;
                    case 0x05: _Cmd = DynOS_Level_CmdJump(_Stack, _Cmd);            break;
                    case 0x06: _Cmd = DynOS_Level_CmdJumpLink(_Stack, _Cmd);        break;
                    case 0x07: _Cmd = DynOS_Level_CmdReturn(_Stack, _Cmd);          break;
                    case 0x08: _Cmd = DynOS_Level_CmdJumpLinkPushArg(_Stack, _Cmd); break;
                    case 0x09: _Cmd = DynOS_Level_CmdJumpRepeat(_Stack, _Cmd);      break;
                    case 0x0A: _Cmd = DynOS_Level_CmdLoopBegin(_Stack, _Cmd);       break;
                    case 0x0B: _Cmd = DynOS_Level_CmdLoopUntil(_Stack, _Cmd);       break;
                    case 0x0C: _Cmd = DynOS_Level_CmdJumpIf(_Stack, _Cmd);          break;
                    case 0x0D: _Cmd = DynOS_Level_CmdJumpLinkIf(_Stack, _Cmd);      break;

                    // coop
                    case 0x42: _Cmd = DynOS_Level_CmdJumpArea(_Stack, _Cmd, aPreprocessFunction); break;

                    default: _Cmd = DynOS_Level_CmdNext(_Cmd); break;
                } break;

            case 1:
                _Cmd = DynOS_Level_CmdNext(_Cmd);
                break;

            case 2:
                _Cmd = DynOS_Level_CmdReturn(_Stack, _Cmd);
                break;

            case 3:
                return;
        }
    }
}

//
// Level Script Utilities
//

s16 *DynOS_Level_GetWarp(s32 aLevel, s32 aArea, u8 aWarpId) {
    if (aLevel >= CUSTOM_LEVEL_NUM_START) {
        struct CustomLevelInfo* info = smlua_level_util_get_info(aLevel);
        if (!info || !info->script) { return NULL; }
        sDynosCurrentLevelNum = 1;
        DynOS_Level_ParseScript(info->script, DynOS_Level_PreprocessScript);
        for (const auto &_Warp : sDynosLevelWarps[1]) {
            if (_Warp.mArea == aArea && _Warp.mId == aWarpId) {
                return (s16 *) &_Warp;
            }
        }
        return NULL;
    }

    DynOS_Level_Init();
    if (aLevel >= 0 && aLevel < LEVEL_COUNT) {
        for (const auto &_Warp : sDynosLevelWarps[aLevel]) {
            if (_Warp.mArea == aArea && _Warp.mId == aWarpId) {
                return (s16 *) &_Warp;
            }
        }
    }
    return NULL;
}

s16 *DynOS_Level_GetWarpEntry(s32 aLevel, s32 aArea) {
    DynOS_Level_Init();

    // override vanilla castle warps
    if (DynOS_Level_GetCourse(aLevel) == COURSE_NONE && aLevel >= 0 && aLevel < LEVEL_COUNT) {
        extern const LevelScript level_castle_grounds_entry[];
        extern const LevelScript level_castle_inside_entry[];
        extern const LevelScript level_castle_courtyard_entry[];
        if (sDynosLevelScripts[aLevel].mLevelScript == level_castle_inside_entry) {
            return DynOS_Level_GetWarp(aLevel, aArea, (aArea == 3) ? 0x00 : 0x01);
        } else if (sDynosLevelScripts[aLevel].mLevelScript == level_castle_grounds_entry) {
            return DynOS_Level_GetWarp(aLevel, aArea, 0x00);
        } else if (sDynosLevelScripts[aLevel].mLevelScript == level_castle_courtyard_entry) {
            return DynOS_Level_GetWarp(aLevel, aArea, 0x01);
        }
    }

    return DynOS_Level_GetWarp(aLevel, aArea, 0x0A);
}

s16 *DynOS_Level_GetWarpDeath(s32 aLevel, s32 aArea) {
    DynOS_Level_Init();
    s16 *_Warp = DynOS_Level_GetWarp(aLevel, aArea, 0xF1);
    if (!_Warp) _Warp = DynOS_Level_GetWarp(aLevel, aArea, 0xF3);
    return _Warp;
}
