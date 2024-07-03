#include "dynos.cpp.h"
extern "C" {
#include "include/level_commands.h"
#include "include/model_ids.h"
#include "include/behavior_data.h"
#include "include/surface_terrains.h"
#include "include/seq_ids.h"
#include "level_commands.h"
#include "game/level_update.h"
#include "include/dialog_ids.h"
#include "levels/scripts.h"
#include "levels/menu/header.h"
#include "game/area.h"
}

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
static void ClearLvlDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

  /////////////
 // Parsing //
/////////////

#define LEVEL_SCRIPT_SIZE_PER_TOKEN 4

#define lvl_constant(x) if (_Arg == #x) { return (LevelScript) (x); }
#define lvl_legacy_constant(x, y) if (_Arg == #x) { return (LevelScript) (y); }

s64 DynOS_Lvl_ParseLevelScriptConstants(const String& _Arg, bool* found) {
    *found = true;

    // Behavior constants
    s64 cBhvConstant = DynOS_Common_ParseBhvConstants(_Arg, found);
    if (*found) { return cBhvConstant; }
    *found = true; // reset found value

    // Level constants
    lvl_constant(LEVEL_UNKNOWN_1);
    lvl_constant(LEVEL_UNKNOWN_2);
    lvl_constant(LEVEL_UNKNOWN_3);
    lvl_constant(LEVEL_BBH);
    lvl_constant(LEVEL_CCM);
    lvl_constant(LEVEL_CASTLE);
    lvl_constant(LEVEL_HMC);
    lvl_constant(LEVEL_SSL);
    lvl_constant(LEVEL_BOB);
    lvl_constant(LEVEL_SL);
    lvl_constant(LEVEL_WDW);
    lvl_constant(LEVEL_JRB);
    lvl_constant(LEVEL_THI);
    lvl_constant(LEVEL_TTC);
    lvl_constant(LEVEL_RR);
    lvl_constant(LEVEL_CASTLE_GROUNDS);
    lvl_constant(LEVEL_BITDW);
    lvl_constant(LEVEL_VCUTM);
    lvl_constant(LEVEL_BITFS);
    lvl_constant(LEVEL_SA);
    lvl_constant(LEVEL_BITS);
    lvl_constant(LEVEL_LLL);
    lvl_constant(LEVEL_DDD);
    lvl_constant(LEVEL_WF);
    lvl_constant(LEVEL_ENDING);
    lvl_constant(LEVEL_CASTLE_COURTYARD);
    lvl_constant(LEVEL_PSS);
    lvl_constant(LEVEL_COTMC);
    lvl_constant(LEVEL_TOTWC);
    lvl_constant(LEVEL_BOWSER_1);
    lvl_constant(LEVEL_WMOTR);
    lvl_constant(LEVEL_UNKNOWN_32);
    lvl_constant(LEVEL_BOWSER_2);
    lvl_constant(LEVEL_BOWSER_3);
    lvl_constant(LEVEL_UNKNOWN_35);
    lvl_constant(LEVEL_TTM);
    lvl_constant(LEVEL_UNKNOWN_37);
    lvl_constant(LEVEL_UNKNOWN_38);

    // Surface constants
    lvl_constant(TERRAIN_GRASS);
    lvl_constant(TERRAIN_STONE);
    lvl_constant(TERRAIN_SNOW);
    lvl_constant(TERRAIN_SAND);
    lvl_constant(TERRAIN_SPOOKY);
    lvl_constant(TERRAIN_WATER);
    lvl_constant(TERRAIN_SLIDE);
    lvl_constant(TERRAIN_MASK);

    // Seq ids constants
    lvl_constant(SEQ_BASE_ID);
    lvl_constant(SEQ_VARIATION);
    lvl_constant(SEQ_SOUND_PLAYER);
    lvl_constant(SEQ_EVENT_CUTSCENE_COLLECT_STAR);
    lvl_constant(SEQ_MENU_TITLE_SCREEN);
    lvl_constant(SEQ_LEVEL_GRASS);
    lvl_constant(SEQ_LEVEL_INSIDE_CASTLE);
    lvl_constant(SEQ_LEVEL_WATER);
    lvl_constant(SEQ_LEVEL_HOT);
    lvl_constant(SEQ_LEVEL_BOSS_KOOPA);
    lvl_constant(SEQ_LEVEL_SNOW);
    lvl_constant(SEQ_LEVEL_SLIDE);
    lvl_constant(SEQ_LEVEL_SPOOKY);
    lvl_constant(SEQ_EVENT_PIRANHA_PLANT);
    lvl_constant(SEQ_LEVEL_UNDERGROUND);
    lvl_constant(SEQ_MENU_STAR_SELECT);
    lvl_constant(SEQ_EVENT_POWERUP);
    lvl_constant(SEQ_EVENT_METAL_CAP);
    lvl_constant(SEQ_EVENT_KOOPA_MESSAGE);
    lvl_constant(SEQ_LEVEL_KOOPA_ROAD);
    lvl_constant(SEQ_EVENT_HIGH_SCORE);
    lvl_constant(SEQ_EVENT_MERRY_GO_ROUND);
    lvl_constant(SEQ_EVENT_RACE);
    lvl_constant(SEQ_EVENT_CUTSCENE_STAR_SPAWN);
    lvl_constant(SEQ_EVENT_BOSS);
    lvl_constant(SEQ_EVENT_CUTSCENE_COLLECT_KEY);
    lvl_constant(SEQ_EVENT_ENDLESS_STAIRS);
    lvl_constant(SEQ_LEVEL_BOSS_KOOPA_FINAL);
    lvl_constant(SEQ_EVENT_CUTSCENE_CREDITS);
    lvl_constant(SEQ_EVENT_SOLVE_PUZZLE);
    lvl_constant(SEQ_EVENT_TOAD_MESSAGE);
    lvl_constant(SEQ_EVENT_PEACH_MESSAGE);
    lvl_constant(SEQ_EVENT_CUTSCENE_INTRO);
    lvl_constant(SEQ_EVENT_CUTSCENE_VICTORY);
    lvl_constant(SEQ_EVENT_CUTSCENE_ENDING);
    lvl_constant(SEQ_MENU_FILE_SELECT);
    lvl_constant(SEQ_EVENT_CUTSCENE_LAKITU);
    lvl_constant(SEQ_COUNT);

    // Model constants
    s64 cModelConstant = DynOS_Common_ParseModelConstants(_Arg, found);
    if (*found) { return cModelConstant; }
    *found = true; // reset found value

    // dialog constants
    lvl_constant(DIALOG_000);
    lvl_constant(DIALOG_001);
    lvl_constant(DIALOG_002);
    lvl_constant(DIALOG_003);
    lvl_constant(DIALOG_004);
    lvl_constant(DIALOG_005);
    lvl_constant(DIALOG_006);
    lvl_constant(DIALOG_007);
    lvl_constant(DIALOG_008);
    lvl_constant(DIALOG_009);
    lvl_constant(DIALOG_010);
    lvl_constant(DIALOG_011);
    lvl_constant(DIALOG_012);
    lvl_constant(DIALOG_013);
    lvl_constant(DIALOG_014);
    lvl_constant(DIALOG_015);
    lvl_constant(DIALOG_016);
    lvl_constant(DIALOG_017);
    lvl_constant(DIALOG_018);
    lvl_constant(DIALOG_019);
    lvl_constant(DIALOG_020);
    lvl_constant(DIALOG_021);
    lvl_constant(DIALOG_022);
    lvl_constant(DIALOG_023);
    lvl_constant(DIALOG_024);
    lvl_constant(DIALOG_025);
    lvl_constant(DIALOG_026);
    lvl_constant(DIALOG_027);
    lvl_constant(DIALOG_028);
    lvl_constant(DIALOG_029);
    lvl_constant(DIALOG_030);
    lvl_constant(DIALOG_031);
    lvl_constant(DIALOG_032);
    lvl_constant(DIALOG_033);
    lvl_constant(DIALOG_034);
    lvl_constant(DIALOG_035);
    lvl_constant(DIALOG_036);
    lvl_constant(DIALOG_037);
    lvl_constant(DIALOG_038);
    lvl_constant(DIALOG_039);
    lvl_constant(DIALOG_040);
    lvl_constant(DIALOG_041);
    lvl_constant(DIALOG_042);
    lvl_constant(DIALOG_043);
    lvl_constant(DIALOG_044);
    lvl_constant(DIALOG_045);
    lvl_constant(DIALOG_046);
    lvl_constant(DIALOG_047);
    lvl_constant(DIALOG_048);
    lvl_constant(DIALOG_049);
    lvl_constant(DIALOG_050);
    lvl_constant(DIALOG_051);
    lvl_constant(DIALOG_052);
    lvl_constant(DIALOG_053);
    lvl_constant(DIALOG_054);
    lvl_constant(DIALOG_055);
    lvl_constant(DIALOG_056);
    lvl_constant(DIALOG_057);
    lvl_constant(DIALOG_058);
    lvl_constant(DIALOG_059);
    lvl_constant(DIALOG_060);
    lvl_constant(DIALOG_061);
    lvl_constant(DIALOG_062);
    lvl_constant(DIALOG_063);
    lvl_constant(DIALOG_064);
    lvl_constant(DIALOG_065);
    lvl_constant(DIALOG_066);
    lvl_constant(DIALOG_067);
    lvl_constant(DIALOG_068);
    lvl_constant(DIALOG_069);
    lvl_constant(DIALOG_070);
    lvl_constant(DIALOG_071);
    lvl_constant(DIALOG_072);
    lvl_constant(DIALOG_073);
    lvl_constant(DIALOG_074);
    lvl_constant(DIALOG_075);
    lvl_constant(DIALOG_076);
    lvl_constant(DIALOG_077);
    lvl_constant(DIALOG_078);
    lvl_constant(DIALOG_079);
    lvl_constant(DIALOG_080);
    lvl_constant(DIALOG_081);
    lvl_constant(DIALOG_082);
    lvl_constant(DIALOG_083);
    lvl_constant(DIALOG_084);
    lvl_constant(DIALOG_085);
    lvl_constant(DIALOG_086);
    lvl_constant(DIALOG_087);
    lvl_constant(DIALOG_088);
    lvl_constant(DIALOG_089);
    lvl_constant(DIALOG_090);
    lvl_constant(DIALOG_091);
    lvl_constant(DIALOG_092);
    lvl_constant(DIALOG_093);
    lvl_constant(DIALOG_094);
    lvl_constant(DIALOG_095);
    lvl_constant(DIALOG_096);
    lvl_constant(DIALOG_097);
    lvl_constant(DIALOG_098);
    lvl_constant(DIALOG_099);
    lvl_constant(DIALOG_100);
    lvl_constant(DIALOG_101);
    lvl_constant(DIALOG_102);
    lvl_constant(DIALOG_103);
    lvl_constant(DIALOG_104);
    lvl_constant(DIALOG_105);
    lvl_constant(DIALOG_106);
    lvl_constant(DIALOG_107);
    lvl_constant(DIALOG_108);
    lvl_constant(DIALOG_109);
    lvl_constant(DIALOG_110);
    lvl_constant(DIALOG_111);
    lvl_constant(DIALOG_112);
    lvl_constant(DIALOG_113);
    lvl_constant(DIALOG_114);
    lvl_constant(DIALOG_115);
    lvl_constant(DIALOG_116);
    lvl_constant(DIALOG_117);
    lvl_constant(DIALOG_118);
    lvl_constant(DIALOG_119);
    lvl_constant(DIALOG_120);
    lvl_constant(DIALOG_121);
    lvl_constant(DIALOG_122);
    lvl_constant(DIALOG_123);
    lvl_constant(DIALOG_124);
    lvl_constant(DIALOG_125);
    lvl_constant(DIALOG_126);
    lvl_constant(DIALOG_127);
    lvl_constant(DIALOG_128);
    lvl_constant(DIALOG_129);
    lvl_constant(DIALOG_130);
    lvl_constant(DIALOG_131);
    lvl_constant(DIALOG_132);
    lvl_constant(DIALOG_133);
    lvl_constant(DIALOG_134);
    lvl_constant(DIALOG_135);
    lvl_constant(DIALOG_136);
    lvl_constant(DIALOG_137);
    lvl_constant(DIALOG_138);
    lvl_constant(DIALOG_139);
    lvl_constant(DIALOG_140);
    lvl_constant(DIALOG_141);
    lvl_constant(DIALOG_142);
    lvl_constant(DIALOG_143);
    lvl_constant(DIALOG_144);
    lvl_constant(DIALOG_145);
    lvl_constant(DIALOG_146);
    lvl_constant(DIALOG_147);
    lvl_constant(DIALOG_148);
    lvl_constant(DIALOG_149);
    lvl_constant(DIALOG_150);
    lvl_constant(DIALOG_151);
    lvl_constant(DIALOG_152);
    lvl_constant(DIALOG_153);
    lvl_constant(DIALOG_154);
    lvl_constant(DIALOG_155);
    lvl_constant(DIALOG_156);
    lvl_constant(DIALOG_157);
    lvl_constant(DIALOG_158);
    lvl_constant(DIALOG_159);
    lvl_constant(DIALOG_160);
    lvl_constant(DIALOG_161);
    lvl_constant(DIALOG_162);
    lvl_constant(DIALOG_163);
    lvl_constant(DIALOG_164);
    lvl_constant(DIALOG_165);
    lvl_constant(DIALOG_166);
    lvl_constant(DIALOG_167);
    lvl_constant(DIALOG_168);
    lvl_constant(DIALOG_169);
    lvl_constant(DIALOG_COUNT);

    // global scripts
    lvl_constant(level_main_scripts_entry);
    lvl_constant(level_main_menu_entry_1);
    lvl_constant(script_func_global_1);
    lvl_constant(script_func_global_2);
    lvl_constant(script_func_global_3);
    lvl_constant(script_func_global_4);
    lvl_constant(script_func_global_5);
    lvl_constant(script_func_global_6);
    lvl_constant(script_func_global_7);
    lvl_constant(script_func_global_8);
    lvl_constant(script_func_global_9);
    lvl_constant(script_func_global_10);
    lvl_constant(script_func_global_11);
    lvl_constant(script_func_global_12);
    lvl_constant(script_func_global_13);
    lvl_constant(script_func_global_14);
    lvl_constant(script_func_global_15);
    lvl_constant(script_func_global_16);
    lvl_constant(script_func_global_17);
    lvl_constant(script_func_global_18);

    // level command constants
    lvl_constant(OP_AND);
    lvl_constant(OP_NAND);
    lvl_constant(OP_EQ);
    lvl_constant(OP_NEQ);
    lvl_constant(OP_LT);
    lvl_constant(OP_LEQ);
    lvl_constant(OP_GT);
    lvl_constant(OP_GEQ);
    lvl_constant(OP_SET);
    lvl_constant(OP_GET);
    lvl_constant(VAR_CURR_SAVE_FILE_NUM);
    lvl_constant(VAR_CURR_COURSE_NUM);
    lvl_constant(VAR_CURR_ACT_NUM);
    lvl_constant(VAR_CURR_LEVEL_NUM);
    lvl_constant(VAR_CURR_AREA_INDEX);
    lvl_constant(WARP_CHECKPOINT);
    lvl_constant(WARP_NO_CHECKPOINT);
    lvl_constant(WHIRLPOOL_COND_ALWAYS);
    lvl_constant(WHIRLPOOL_COND_BOWSER2_BEATEN);
    lvl_constant(WHIRLPOOL_COND_AT_LEAST_SECOND_STAR);
    lvl_constant(REGULAR_FACE);
    lvl_constant(DIZZY_FACE);

    // warp transitions
    lvl_constant(WARP_TRANSITION_FADE_FROM_COLOR);
    lvl_constant(WARP_TRANSITION_FADE_INTO_COLOR);
    lvl_constant(WARP_TRANSITION_FADE_FROM_STAR);
    lvl_constant(WARP_TRANSITION_FADE_INTO_STAR);
    lvl_constant(WARP_TRANSITION_FADE_FROM_CIRCLE);
    lvl_constant(WARP_TRANSITION_FADE_INTO_CIRCLE);
    lvl_constant(WARP_TRANSITION_FADE_FROM_MARIO);
    lvl_constant(WARP_TRANSITION_FADE_INTO_MARIO);
    lvl_constant(WARP_TRANSITION_FADE_FROM_BOWSER);
    lvl_constant(WARP_TRANSITION_FADE_INTO_BOWSER);

    // Other constants
    lvl_constant(NULL);
    lvl_constant(TRUE);
    lvl_constant(FALSE);

    *found = false;
    return 0;
}

template <typename T>
DataNode<T>* FindDataNode(DataNodes<T>& aDataNodes, String& aName, u32 aModelIdentifier) {
    DataNode<T>* best = NULL;
    for (auto& node : aDataNodes) {
        if (aName == node->mName) {
            if (aModelIdentifier == node->mModelIdentifier) {
                return node;
            }
            best = node;
        }
    }
    return best;
}

static LevelScript ParseLevelScriptSymbolArgInternal(GfxData* aGfxData, DataNode<LevelScript>* aNode, u64& aTokenIndex, bool* found) {
    String _Arg = aNode->mTokens[aTokenIndex++];
    u64 _ModelIdentifier = aNode->mModelIdentifier;
    *found = true;

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // Offset
    s32 _Offset = 0;
    s32 _Plus = _Arg.Find('+');
    if (_Plus != -1) {
        _Offset = _Arg.SubString(_Plus + 1).ParseInt();
        _Arg = _Arg.SubString(0, _Plus);
    }

    // Built-in functions
    const void *_FunctionPtr = DynOS_Builtin_Func_GetFromName(_Arg.begin());
    if (_FunctionPtr != NULL) {
        return (s64) _FunctionPtr;
    }

    bool constantFound = false;
    s64 constantValue = DynOS_Lvl_ParseLevelScriptConstants(_Arg, &constantFound);
    if (constantFound) {
        return (LevelScript) constantValue;
    }

    // Level Scripts
    {
        auto _Node = FindDataNode<LevelScript>(aGfxData->mLevelScripts, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            auto base = DynOS_Lvl_Parse(aGfxData, _Node, false)->mData;
            auto data = (u8*)base + _Offset;
            if (_Offset != 0) {
                aGfxData->mPointerOffsetList.Add({ data, base });
            }
            return (LevelScript) data;
        }
    }

    // Geo layouts
    {
        auto _Node = FindDataNode<GeoLayout>(aGfxData->mGeoLayouts, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_Geo_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Collisions
    {
        auto _Node = FindDataNode<Collision>(aGfxData->mCollisions, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_Col_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // MacroObjects
    {
        auto _Node = FindDataNode<MacroObject>(aGfxData->mMacroObjects, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_MacroObject_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Trajectories
    {
        auto _Node = FindDataNode<Trajectory>(aGfxData->mTrajectories, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_Trajectory_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // Movtexs
    {
        auto _Node = FindDataNode<Movtex>(aGfxData->mMovtexs, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_Movtex_Parse(aGfxData, _Node, false)->mData;
        }
    }

    // MovtexQCs
    {
        auto _Node = FindDataNode<MovtexQC>(aGfxData->mMovtexQCs, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_MovtexQC_Parse(aGfxData, _Node)->mData;
        }
    }

    // Rooms
    {
        auto _Node = FindDataNode<u8>(aGfxData->mRooms, _Arg, aGfxData->mModelIdentifier);
        if (_Node != NULL) {
            return (LevelScript) DynOS_Rooms_Parse(aGfxData, _Node)->mData;
        }
    }

    // Built-in actors
    auto builtinActor = DynOS_Builtin_Actor_GetFromName(_Arg.begin());
    if (builtinActor != NULL) {
        return (LevelScript)builtinActor;
    }

    // Built-in Lvl Geos
    auto builtinGeo = DynOS_Builtin_LvlGeo_GetFromName(_Arg.begin());
    if (builtinGeo != NULL) {
        return (LevelScript)builtinGeo;
    }

    // Built-in Cols
    auto builtinCol = DynOS_Builtin_Col_GetFromName(_Arg.begin());
    if (builtinCol != NULL) {
        return (LevelScript)builtinCol;
    }

    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess, DynOS_Lvl_ParseLevelScriptConstants);
    if (rdSuccess) {
        return (LevelScript)rdValue;
    }

    *found = false;
    return 0;
}

static LevelScript ParseLevelScriptSymbolArg(GfxData* aGfxData, DataNode<LevelScript>* aNode, u64& aTokenIndex) {
    bool found = true;
    LevelScript value = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &found);
    if (!found) {
        const String& _Arg = aNode->mTokens[aTokenIndex - 1];
        PrintDataError("  ERROR: Unknown lvl arg: %s", _Arg.begin());
    }
    return value;
}

#define lvl_symbol_0(symb)                       \
    if (_Symbol == #symb) {                      \
        LevelScript _Ls[] = { symb() };          \
        memcpy(aHead, _Ls, sizeof(_Ls));         \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0])); \
        return;                                  \
    }

#define lvl_symbol_1(symb, n)                                                        \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }                       \
        LevelScript _Ls[] = { symb(_Arg0) };                                         \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_2(symb, n1, n2)                                                   \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1) };                                  \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_3(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2) };                           \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_4(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };                    \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_5(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) };             \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_6(symb, n1, n2, n3)                                               \
    if (_Symbol == #symb) {                                                          \
        LevelScript _Arg0 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg1 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg2 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg3 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg4 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        LevelScript _Arg5 = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n1 != 0) { aGfxData->mPointerList.Add(aHead + n1); }                     \
        if (n2 != 0) { aGfxData->mPointerList.Add(aHead + n2); }                     \
        if (n3 != 0) { aGfxData->mPointerList.Add(aHead + n3); }                     \
        LevelScript _Ls[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) };      \
        memcpy(aHead, _Ls, sizeof(_Ls));                                             \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));                                     \
        return;                                                                      \
    }

#define lvl_symbol_noop_3(symb)                  \
    if (_Symbol == #symb) {                      \
        aTokenIndex += 3;                        \
        LevelScript _Ls[] = { symb(0, 0, 0) };   \
        memcpy(aHead, _Ls, sizeof(_Ls));         \
        aHead += (sizeof(_Ls) / sizeof(_Ls[0])); \
        return;                                  \
    }

static void ParseLevelScriptSymbol(GfxData* aGfxData, DataNode<LevelScript>* aNode, LevelScript*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    // execution
    lvl_symbol_4(EXECUTE, 1, 2, 3);
    lvl_symbol_4(EXIT_AND_EXECUTE, 1, 2, 3);
    lvl_symbol_0(EXIT);

    // sleep
    lvl_symbol_1(SLEEP, 0);
    lvl_symbol_1(SLEEP_BEFORE_EXIT, 0);

    // jumps
    lvl_symbol_1(JUMP, 1);
    lvl_symbol_1(JUMP_LINK, 1);
    lvl_symbol_0(RETURN);
    lvl_symbol_1(JUMP_LINK_PUSH_ARG, 0);
    lvl_symbol_0(JUMP_N_TIMES);
    lvl_symbol_0(LOOP_BEGIN);
    lvl_symbol_2(LOOP_UNTIL, 0, 0);
    lvl_symbol_3(JUMP_IF, 2, 0, 0);
    lvl_symbol_2(SKIP_IF, 0, 0);
    lvl_symbol_0(SKIP);
    lvl_symbol_0(SKIP_NOP);
    lvl_symbol_3(JUMP_AREA_EXT, 2, 0, 0);

    // calls
    lvl_symbol_2(CALL, 1, 0);
    lvl_symbol_2(CALL_LOOP, 1, 0);

    // misc memory
    lvl_symbol_1(SET_REG, 0);
    lvl_symbol_0(PUSH_POOL);
    lvl_symbol_0(POP_POOL);
    lvl_symbol_3(FIXED_LOAD, 1, 2, 3);
    lvl_symbol_noop_3(LOAD_RAW);
    lvl_symbol_noop_3(LOAD_MIO0);
    lvl_symbol_1(LOAD_MARIO_HEAD, 0);
    lvl_symbol_noop_3(LOAD_MIO0_TEXTURE);

    // levels
    lvl_symbol_0(INIT_LEVEL);
    lvl_symbol_0(CLEAR_LEVEL);
    lvl_symbol_0(ALLOC_LEVEL_POOL);
    lvl_symbol_0(FREE_LEVEL_POOL);

    // areas
    lvl_symbol_2(AREA, 1, 0);
    lvl_symbol_0(END_AREA);

    // models
    lvl_symbol_3(LOAD_MODEL_FROM_DL, 1, 0, 0);
    lvl_symbol_3(CMD23, 1, 0, 0);

    // objects
    lvl_symbol_3(MARIO, 2, 0, 0);

    // warps
    lvl_symbol_5(INSTANT_WARP, 0, 0, 0);

    // misc
    lvl_symbol_1(LOAD_AREA, 0);
    lvl_symbol_1(CMD2A, 0);
    lvl_symbol_5(MARIO_POS, 0, 0, 0);
    lvl_symbol_0(CMD2C);
    lvl_symbol_0(CMD2D);
    lvl_symbol_1(TERRAIN, 1);
    lvl_symbol_1(ROOMS, 1);
    lvl_symbol_2(SHOW_DIALOG, 0, 0);
    lvl_symbol_1(TERRAIN_TYPE, 0);
    lvl_symbol_0(NOP);

    // transitions
    lvl_symbol_5(TRANSITION, 0, 0, 0);
    lvl_symbol_1(BLACKOUT, 0);
    lvl_symbol_1(GAMMA, 0);

    // music
    lvl_symbol_2(SET_BACKGROUND_MUSIC, 0, 0);
    lvl_symbol_1(SET_MENU_MUSIC, 0);
    lvl_symbol_1(STOP_MUSIC, 0);

    // misc
    lvl_symbol_1(MACRO_OBJECTS, 1);
    lvl_symbol_5(CMD3A, 0, 0, 0);
    lvl_symbol_6(WHIRLPOOL, 0, 0, 0);
    lvl_symbol_2(GET_OR_SET, 0, 0);
    lvl_symbol_0(ADV_DEMO);
    lvl_symbol_0(CLEAR_DEMO_PTR);

    // object
    if (_Symbol == "OBJECT") {
        u64 topTokenIndex = aTokenIndex;

        bool foundModel = true;
        bool foundBeh = true;
        LevelScript model    = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundModel);
        LevelScript posX     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posY     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posZ     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleX   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleY   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleZ   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript behParam = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript beh      = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);

        if (foundModel && foundBeh) {
            aGfxData->mPointerList.Add(aHead + 5);
            LevelScript _Ls[] = { OBJECT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else if (foundModel) {
            u32 behIndex   = DynOS_Lua_RememberVariable(aGfxData, aHead + 5, aNode->mTokens[topTokenIndex + 8]);
            LevelScript _Ls[] = { OBJECT_EXT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, behIndex) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            u32 modelIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 5, aNode->mTokens[topTokenIndex + 0]);
            u32 behIndex   = DynOS_Lua_RememberVariable(aGfxData, aHead + 6, aNode->mTokens[topTokenIndex + 8]);
            LevelScript _Ls[] = { OBJECT_EXT2(modelIndex, posX, posY, posZ, angleX, angleY, angleZ, behParam, behIndex) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // object with acts
    if (_Symbol == "OBJECT_WITH_ACTS") {
        u64 topTokenIndex = aTokenIndex;

        bool foundModel = true;
        bool foundBeh = true;
        LevelScript model    = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundModel);
        LevelScript posX     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posY     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript posZ     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleX   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleY   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript angleZ   = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript behParam = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript beh      = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundBeh);
        LevelScript acts     = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);

        if (foundModel && foundBeh) {
            aGfxData->mPointerList.Add(aHead + 5);
            LevelScript _Ls[] = { OBJECT_WITH_ACTS(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, beh, acts) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else if (foundModel) {
            u32 behIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 5, aNode->mTokens[topTokenIndex + 8]);
            LevelScript _Ls[] = { OBJECT_WITH_ACTS_EXT(model, posX, posY, posZ, angleX, angleY, angleZ, behParam, behIndex, acts) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            u32 modelIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 5, aNode->mTokens[topTokenIndex + 0]);
            u32 behIndex   = DynOS_Lua_RememberVariable(aGfxData, aHead + 6, aNode->mTokens[topTokenIndex + 8]);
            LevelScript _Ls[] = { OBJECT_WITH_ACTS_EXT2(modelIndex, posX, posY, posZ, angleX, angleY, angleZ, behParam, behIndex, acts) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // LOAD_MODEL_FROM_GEO
    if (_Symbol == "LOAD_MODEL_FROM_GEO") {
        u64 topTokenIndex = aTokenIndex;
        bool foundGeo = false;
        LevelScript model = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript geo   = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundGeo);
        if (foundGeo) {
            aGfxData->mPointerList.Add(aHead + 1);
            LevelScript _Ls[] = { LOAD_MODEL_FROM_GEO(model, geo) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            u32 geoIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 1]);
            LevelScript _Ls[] = { LOAD_MODEL_FROM_GEO_EXT(model, geoIndex) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // JUMP_AREA
    if (_Symbol == "JUMP_AREA") {
        LevelScript op = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript arg = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript target = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        aGfxData->mPointerList.Add(aHead + 2);
        LevelScript _Ls[] = { JUMP_AREA_EXT(op, arg, target) };
        memcpy(aHead, _Ls, sizeof(_Ls));
        aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        return;
    }

    // WARP_NODE
    if (_Symbol == "WARP_NODE") {
        u64 topTokenIndex = aTokenIndex;

        bool foundLevel = true;
        LevelScript id = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript destLevel = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundLevel);
        LevelScript destArea = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript destNode = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript flags = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);

        if (foundLevel) {
            LevelScript _Ls[] = { WARP_NODE(id, destLevel, destArea, destNode, flags) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            s16 destLevelIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 1]);
            LevelScript _Ls[] = { WARP_NODE(id, destLevelIndex, destArea, destNode, flags) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // PAINTING_WARP_NODE
    if (_Symbol == "PAINTING_WARP_NODE") {
        u64 topTokenIndex = aTokenIndex;

        bool foundLevel = true;
        LevelScript id = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript destLevel = ParseLevelScriptSymbolArgInternal(aGfxData, aNode, aTokenIndex, &foundLevel);
        LevelScript destArea = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript destNode = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);
        LevelScript flags = ParseLevelScriptSymbolArg(aGfxData, aNode, aTokenIndex);

        if (foundLevel) {
            LevelScript _Ls[] = { PAINTING_WARP_NODE(id, destLevel, destArea, destNode, flags) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        } else {
            s16 destLevelIndex = DynOS_Lua_RememberVariable(aGfxData, aHead + 1, aNode->mTokens[topTokenIndex + 1]);
            LevelScript _Ls[] = { PAINTING_WARP_NODE(id, destLevelIndex, destArea, destNode, flags) };
            memcpy(aHead, _Ls, sizeof(_Ls));
            aHead += (sizeof(_Ls) / sizeof(_Ls[0]));
        }
        return;
    }

    // Unknown
    PrintDataError("  ERROR: Unknown lvl symbol: %s", _Symbol.begin());
}

DataNode<LevelScript>* DynOS_Lvl_Parse(GfxData* aGfxData, DataNode<LevelScript>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Level script data
    aNode->mData = New<LevelScript>(aNode->mTokens.Count() * LEVEL_SCRIPT_SIZE_PER_TOKEN);
    LevelScript* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseLevelScriptSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

static DataNode<LevelScript> *GetLevelScript(GfxData *aGfxData, const String& aGeoRoot) {
    for (DataNode<LevelScript> *_Node : aGfxData->mLevelScripts) {
        if (_Node->mName == aGeoRoot) {
            return _Node;
        }
    }
    return NULL;
}

  /////////////
 // Writing //
/////////////

static void DynOS_Lvl_Write(BinFile* aFile, GfxData* aGfxData, DataNode<LevelScript> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_LEVEL_SCRIPT);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        LevelScript *_Head = &aNode->mData[i];
        if (aGfxData->mPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Write(aFile, (const void *) (*_Head), aGfxData);
        } else if (aGfxData->mLuaPointerList.Find((void *) _Head) != -1) {
            DynOS_Pointer_Lua_Write(aFile, *(u32 *)_Head, aGfxData);
        } else {
            aFile->Write<u32>(*((u32 *) _Head));
        }
    }
}

static bool DynOS_Lvl_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData) {
    BinFile *_File = BinFile::OpenW(aOutputFilename.c_str());
    if (!_File) {
        PrintDataError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    for (u64 i = 0; i != aGfxData->mLoadIndex; ++i) {
        for (auto &_Node : aGfxData->mLights) {
            if (_Node->mLoadIndex == i) {
                DynOS_Lights_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLight0s) {
            if (_Node->mLoadIndex == i) {
                DynOS_Light0_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLightTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_LightT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mAmbientTs) {
            if (_Node->mLoadIndex == i) {
                DynOS_AmbientT_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTextures) {
            if (_Node->mLoadIndex == i) {
                DynOS_Tex_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTextureLists) {
            if (_Node->mLoadIndex == i) {
                DynOS_TexList_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mVertices) {
            if (_Node->mLoadIndex == i) {
                DynOS_Vtx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mDisplayLists) {
            if (_Node->mLoadIndex == i) {
                DynOS_Gfx_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mGeoLayouts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Geo_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mCollisions) {
            if (_Node->mLoadIndex == i) {
                DynOS_Col_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mLevelScripts) {
            if (_Node->mLoadIndex == i) {
                DynOS_Lvl_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMacroObjects) {
            if (_Node->mLoadIndex == i) {
                DynOS_MacroObject_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mTrajectories) {
            if (_Node->mLoadIndex == i) {
                DynOS_Trajectory_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMovtexs) {
            if (_Node->mLoadIndex == i) {
                DynOS_Movtex_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mMovtexQCs) {
            if (_Node->mLoadIndex == i) {
                DynOS_MovtexQC_Write(_File, aGfxData, _Node);
            }
        }
        for (auto &_Node : aGfxData->mRooms) {
            if (_Node->mLoadIndex == i) {
                DynOS_Rooms_Write(_File, aGfxData, _Node);
            }
        }
    }
    BinFile::Close(_File);
    return DynOS_Bin_Compress(aOutputFilename);
}

  /////////////
 // Reading //
/////////////

static DataNode<LevelScript>* DynOS_Lvl_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<LevelScript> *_Node = New<DataNode<LevelScript>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<LevelScript>(_Node->mSize);

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mLevelScripts.Add(_Node);
    }

    DynOS_Lvl_Validate_Begin();

    // Read it
    for (u32 i = 0; i != _Node->mSize; ++i) {
        u32 _Value = aFile->Read<u32>();

        bool requirePointer = DynOS_Lvl_Validate_RequirePointer(_Value);

        void *_Ptr = DynOS_Pointer_Load(aFile, aGfxData, _Value, &_Node->mFlags);
        if (_Ptr) {
            if (!requirePointer) {
                PrintError("Didn't expect a pointer while reading level script: %s, %u", _Node->mName.begin(), _Value);
            }
            _Node->mData[i] = (uintptr_t) _Ptr;
        } else {
            if (requirePointer) {
                PrintError("Expected a pointer while reading level script: %s, %u", _Node->mName.begin(), _Value);
                _Node->mData[i] = 0;
            } else {
                _Node->mData[i] = (uintptr_t) _Value;
            }
        }
    }

    return _Node;
}

GfxData *DynOS_Lvl_LoadFromBinary(const SysPath &aFilename, const char *aLevelName) {
    struct DynosGfxDataCache { SysPath mPackFolder; Array<Pair<const char *, GfxData *>> mGfxData; };
    static Array<DynosGfxDataCache *> sDynosGfxDataCache;

    // Load data from binary file
    GfxData *_GfxData = NULL;
    BinFile *_File = DynOS_Bin_Decompress(aFilename);
    if (_File) {
        _GfxData = New<GfxData>();
        for (bool _Done = false; !_Done;) {
            switch (_File->Read<u8>()) {
                case DATA_TYPE_LIGHT:           DynOS_Lights_Load     (_File, _GfxData); break;
                case DATA_TYPE_LIGHT_0:         DynOS_Light0_Load     (_File, _GfxData); break;
                case DATA_TYPE_LIGHT_T:         DynOS_LightT_Load     (_File, _GfxData); break;
                case DATA_TYPE_AMBIENT_T:       DynOS_AmbientT_Load   (_File, _GfxData); break;
                case DATA_TYPE_TEXTURE:         DynOS_Tex_Load        (_File, _GfxData); break;
                case DATA_TYPE_TEXTURE_LIST:    DynOS_TexList_Load    (_File, _GfxData); break;
                case DATA_TYPE_VERTEX:          DynOS_Vtx_Load        (_File, _GfxData); break;
                case DATA_TYPE_DISPLAY_LIST:    DynOS_Gfx_Load        (_File, _GfxData); break;
                case DATA_TYPE_GEO_LAYOUT:      DynOS_Geo_Load        (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION:       DynOS_Anim_Load       (_File, _GfxData); break;
                case DATA_TYPE_ANIMATION_TABLE: DynOS_Anim_Table_Load (_File, _GfxData); break;
                case DATA_TYPE_GFXDYNCMD:       DynOS_GfxDynCmd_Load  (_File, _GfxData); break;
                case DATA_TYPE_COLLISION:       DynOS_Col_Load        (_File, _GfxData); break;
                case DATA_TYPE_LEVEL_SCRIPT:    DynOS_Lvl_Load        (_File, _GfxData); break;
                case DATA_TYPE_MACRO_OBJECT:    DynOS_MacroObject_Load(_File, _GfxData); break;
                case DATA_TYPE_TRAJECTORY:      DynOS_Trajectory_Load (_File, _GfxData); break;
                case DATA_TYPE_MOVTEX:          DynOS_Movtex_Load     (_File, _GfxData); break;
                case DATA_TYPE_MOVTEXQC:        DynOS_MovtexQC_Load   (_File, _GfxData); break;
                case DATA_TYPE_ROOMS:           DynOS_Rooms_Load      (_File, _GfxData); break;
                default:                        _Done = true;                            break;
            }
        }
        BinFile::Close(_File);
    }

    return _GfxData;
}

  //////////////
 // Generate //
//////////////

static bool DynOS_Lvl_GeneratePack_Internal(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    bool generated = false;
    for (auto &_LvlNode : _GfxData->mLevelScripts) {
        String _LvlRootName = _LvlNode->mName;
        DataNode<LevelScript> *_LvlRoot = GetLevelScript(_GfxData, _LvlRootName);
        if (_LvlRoot == NULL) { continue; }
        if (_LvlRootName.Find("_entry") == -1) { continue; }
        // If there is an existing binary file for this level, skip and go to the next level
        SysPath _LvlFilename = fstring("%s/%s.lvl", aPackFolder.c_str(), _LvlRootName.begin());
        if (fs_sys_file_exists(_LvlFilename.c_str())) {
#ifdef DEVELOPMENT
            // Compress file to gain some space
            if (!DynOS_Bin_IsCompressed(_LvlFilename)) {
                DynOS_Bin_Compress(_LvlFilename);
            }
#endif
            continue;
        }

        // Init
        _GfxData->mLoadIndex                  = 0;
        _GfxData->mErrorCount                 = 0;
        _GfxData->mModelIdentifier            = _LvlRoot->mModelIdentifier;
        _GfxData->mPackFolder                 = aPackFolder;
        _GfxData->mPointerList                = { NULL }; // The NULL pointer is needed, so we add it here
        _GfxData->mPointerOffsetList          = { };
        _GfxData->mLuaPointerList             = { };
        _GfxData->mLuaTokenList               = { };
        _GfxData->mGfxContext.mCurrentTexture = NULL;
        _GfxData->mGfxContext.mCurrentPalette = NULL;
        _GfxData->mGeoNodeStack.Clear();

        // Parse data
        PrintNoNewLine("%s.lvl: Level identifier: %X - Processing... ", _LvlRootName.begin(), _GfxData->mModelIdentifier);
        PrintConsole(CONSOLE_MESSAGE_INFO, "%s.lvl: Level identifier: %X - Processing... ", _LvlRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Lvl_Parse(_GfxData, _LvlRoot, true);

        // Force all of the movtexs, collisions, and trajectories into the compiled lvl
        for (auto &_Node : _GfxData->mMovtexs) {
            if (_Node->mModelIdentifier != _GfxData->mModelIdentifier) { continue; }
            DynOS_Movtex_Parse(_GfxData, _Node, false);
        }
        for (auto &_Node : _GfxData->mMovtexQCs) {
            if (_Node->mModelIdentifier != _GfxData->mModelIdentifier) { continue; }
            DynOS_MovtexQC_Parse(_GfxData, _Node);
        }
        for (auto &_Node : _GfxData->mCollisions) {
            if (_Node->mModelIdentifier != _GfxData->mModelIdentifier) { continue; }
            DynOS_Col_Parse(_GfxData, _Node, false);
        }
        for (auto &_Node : _GfxData->mTrajectories) {
            if (_Node->mModelIdentifier != _GfxData->mModelIdentifier) { continue; }
            DynOS_Trajectory_Parse(_GfxData, _Node, false);
        }

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Lvl_WriteBinary(_LvlFilename, _GfxData);
        } else {
            PrintError("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

        // Clear data pointers
        ClearLvlDataNodes(_GfxData->mLights);
        ClearLvlDataNodes(_GfxData->mLight0s);
        ClearLvlDataNodes(_GfxData->mLightTs);
        ClearLvlDataNodes(_GfxData->mAmbientTs);
        ClearLvlDataNodes(_GfxData->mTextures);
        ClearLvlDataNodes(_GfxData->mTextureLists);
        ClearLvlDataNodes(_GfxData->mVertices);
        ClearLvlDataNodes(_GfxData->mDisplayLists);
        ClearLvlDataNodes(_GfxData->mGeoLayouts);
        ClearLvlDataNodes(_GfxData->mCollisions);
        ClearLvlDataNodes(_GfxData->mLevelScripts);
        ClearLvlDataNodes(_GfxData->mMacroObjects);
        ClearLvlDataNodes(_GfxData->mTrajectories);
        ClearLvlDataNodes(_GfxData->mMovtexs);
        ClearLvlDataNodes(_GfxData->mMovtexQCs);
        ClearLvlDataNodes(_GfxData->mRooms);
        _GfxData->mPointerList.Clear();
        _GfxData->mPointerOffsetList.Clear();
        _GfxData->mLuaPointerList.Clear();
        _GfxData->mLuaTokenList.Clear();
        generated = true;
    }

    _GfxData->mChildGeoLayouts.Clear();

    return generated;
}

static void DynOS_Lvl_GeneratePack_Recursive(const SysPath &directory, GfxData *_GfxData) {
    DIR *aPackDir = opendir(directory.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

            SysPath path = fstring("%s/%s", directory.c_str(), _PackEnt->d_name);

            // Recurse through subfolders
            if (fs_sys_dir_exists(path.c_str())) {
                DynOS_Lvl_GeneratePack_Recursive(path, _GfxData);
                continue;
            }

            // skip files that don't end in '.c'
            size_t nameLen = strlen(_PackEnt->d_name);
            if (_PackEnt->d_name[nameLen - 2] != '.' || _PackEnt->d_name[nameLen - 1] != 'c') {
                continue;
            }

            // read the file
            DynOS_Read_Source(_GfxData, path.c_str());
        }
        closedir(aPackDir);
    }
}

void DynOS_Lvl_GeneratePack(const SysPath &aPackFolder) {
    Print("Processing levels: \"%s\"", aPackFolder.c_str());
    Array<Pair<u64, String>> _ActorsFolders;

    GfxData *_GfxData = New<GfxData>();
    _GfxData->mModelIdentifier = 0;

    DIR *aPackDir = opendir(aPackFolder.c_str());
    if (aPackDir) {
        struct dirent *_PackEnt = NULL;
        while ((_PackEnt = readdir(aPackDir)) != NULL) {

            // Skip . and ..
            if (SysPath(_PackEnt->d_name) == ".") continue;
            if (SysPath(_PackEnt->d_name) == "..") continue;

#ifdef DEVELOPMENT
            // Compress .lvl files to gain some space
            // TODO: is this required anymore?
            /*SysPath _Filename = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (SysPath(_PackEnt->d_name).find(".lvl") != SysPath::npos && !DynOS_Bin_IsCompressed(_Filename)) {
                DynOS_Bin_Compress(_Filename);
                continue;
            }*/
#endif

            // For each subfolder, read tokens from script.c
            SysPath _Folder = fstring("%s/%s", aPackFolder.c_str(), _PackEnt->d_name);
            if (!fs_sys_dir_exists(_Folder.c_str())) continue;

            // Prevent generating from folders that likely already generated
            SysPath _LvlFile = fstring("%s/level_%s_entry.lvl", aPackFolder.c_str(), _PackEnt->d_name);
            if (fs_sys_file_exists(_LvlFile.c_str())) continue;

            // Only parse folders with a 'script.c'
            if (!fs_sys_file_exists(fstring("%s/script.c", _Folder.c_str()).c_str()) && !fs_sys_file_exists(fstring("%s/custom.script.c", _Folder.c_str()).c_str())) continue;

            _GfxData->mModelIdentifier++;
            DynOS_Lvl_GeneratePack_Recursive(_Folder, _GfxData);

        }
        closedir(aPackDir);
    }

    // Generate a binary file for each level found in the GfxData
    DynOS_Lvl_GeneratePack_Internal(aPackFolder, _ActorsFolders, _GfxData);
    DynOS_Gfx_Free(_GfxData);
}
