#include "dynos.cpp.h"

extern "C" {
#include "include/surface_terrains.h"
#include "include/level_misc_macros.h"
#include "include/special_preset_names.h"
}

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
void ClearGfxDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

  /////////////
 // Parsing //
/////////////

#define COLLISION_SIZE_PER_TOKEN 4

#define col_constant(x) if (_Arg == #x) { return (s16) (x); }

static s64 DynOS_Col_ParseConstants(const String& _Arg, bool* found) {
    *found = true;

    // Surface constants
    col_constant(SURFACE_DEFAULT);
    col_constant(SURFACE_BURNING);
    col_constant(SURFACE_0004);
    col_constant(SURFACE_HANGABLE);
    col_constant(SURFACE_SLOW);
    col_constant(SURFACE_DEATH_PLANE);
    col_constant(SURFACE_CLOSE_CAMERA);
    col_constant(SURFACE_WATER);
    col_constant(SURFACE_FLOWING_WATER);
    col_constant(SURFACE_INTANGIBLE);
    col_constant(SURFACE_VERY_SLIPPERY);
    col_constant(SURFACE_SLIPPERY);
    col_constant(SURFACE_NOT_SLIPPERY);
    col_constant(SURFACE_TTM_VINES);
    col_constant(SURFACE_MGR_MUSIC);
    col_constant(SURFACE_INSTANT_WARP_1B);
    col_constant(SURFACE_INSTANT_WARP_1C);
    col_constant(SURFACE_INSTANT_WARP_1D);
    col_constant(SURFACE_INSTANT_WARP_1E);
    col_constant(SURFACE_SHALLOW_QUICKSAND);
    col_constant(SURFACE_DEEP_QUICKSAND);
    col_constant(SURFACE_INSTANT_QUICKSAND);
    col_constant(SURFACE_DEEP_MOVING_QUICKSAND);
    col_constant(SURFACE_SHALLOW_MOVING_QUICKSAND);
    col_constant(SURFACE_QUICKSAND);
    col_constant(SURFACE_MOVING_QUICKSAND);
    col_constant(SURFACE_WALL_MISC);
    col_constant(SURFACE_NOISE_DEFAULT);
    col_constant(SURFACE_NOISE_SLIPPERY);
    col_constant(SURFACE_HORIZONTAL_WIND);
    col_constant(SURFACE_INSTANT_MOVING_QUICKSAND);
    col_constant(SURFACE_ICE);
    col_constant(SURFACE_LOOK_UP_WARP);
    col_constant(SURFACE_HARD);
    col_constant(SURFACE_WARP);
    col_constant(SURFACE_TIMER_START);
    col_constant(SURFACE_TIMER_END);
    col_constant(SURFACE_HARD_SLIPPERY);
    col_constant(SURFACE_HARD_VERY_SLIPPERY);
    col_constant(SURFACE_HARD_NOT_SLIPPERY);
    col_constant(SURFACE_VERTICAL_WIND);
    col_constant(SURFACE_BOSS_FIGHT_CAMERA);
    col_constant(SURFACE_CAMERA_FREE_ROAM);
    col_constant(SURFACE_THI3_WALLKICK);
    col_constant(SURFACE_CAMERA_8_DIR);
    col_constant(SURFACE_CAMERA_MIDDLE);
    col_constant(SURFACE_CAMERA_ROTATE_RIGHT);
    col_constant(SURFACE_CAMERA_ROTATE_LEFT);
    col_constant(SURFACE_CAMERA_BOUNDARY);
    col_constant(SURFACE_NOISE_VERY_SLIPPERY_73);
    col_constant(SURFACE_NOISE_VERY_SLIPPERY_74);
    col_constant(SURFACE_NOISE_VERY_SLIPPERY);
    col_constant(SURFACE_NO_CAM_COLLISION);
    col_constant(SURFACE_NO_CAM_COLLISION_77);
    col_constant(SURFACE_NO_CAM_COL_VERY_SLIPPERY);
    col_constant(SURFACE_NO_CAM_COL_SLIPPERY);
    col_constant(SURFACE_SWITCH);
    col_constant(SURFACE_VANISH_CAP_WALLS);
    col_constant(SURFACE_PAINTING_WOBBLE_A6);
    col_constant(SURFACE_PAINTING_WOBBLE_A7);
    col_constant(SURFACE_PAINTING_WOBBLE_A8);
    col_constant(SURFACE_PAINTING_WOBBLE_A9);
    col_constant(SURFACE_PAINTING_WOBBLE_AA);
    col_constant(SURFACE_PAINTING_WOBBLE_AB);
    col_constant(SURFACE_PAINTING_WOBBLE_AC);
    col_constant(SURFACE_PAINTING_WOBBLE_AD);
    col_constant(SURFACE_PAINTING_WOBBLE_AE);
    col_constant(SURFACE_PAINTING_WOBBLE_AF);
    col_constant(SURFACE_PAINTING_WOBBLE_B0);
    col_constant(SURFACE_PAINTING_WOBBLE_B1);
    col_constant(SURFACE_PAINTING_WOBBLE_B2);
    col_constant(SURFACE_PAINTING_WOBBLE_B3);
    col_constant(SURFACE_PAINTING_WOBBLE_B4);
    col_constant(SURFACE_PAINTING_WOBBLE_B5);
    col_constant(SURFACE_PAINTING_WOBBLE_B6);
    col_constant(SURFACE_PAINTING_WOBBLE_B7);
    col_constant(SURFACE_PAINTING_WOBBLE_B8);
    col_constant(SURFACE_PAINTING_WOBBLE_B9);
    col_constant(SURFACE_PAINTING_WOBBLE_BA);
    col_constant(SURFACE_PAINTING_WOBBLE_BB);
    col_constant(SURFACE_PAINTING_WOBBLE_BC);
    col_constant(SURFACE_PAINTING_WOBBLE_BD);
    col_constant(SURFACE_PAINTING_WOBBLE_BE);
    col_constant(SURFACE_PAINTING_WOBBLE_BF);
    col_constant(SURFACE_PAINTING_WOBBLE_C0);
    col_constant(SURFACE_PAINTING_WOBBLE_C1);
    col_constant(SURFACE_PAINTING_WOBBLE_C2);
    col_constant(SURFACE_PAINTING_WOBBLE_C3);
    col_constant(SURFACE_PAINTING_WOBBLE_C4);
    col_constant(SURFACE_PAINTING_WOBBLE_C5);
    col_constant(SURFACE_PAINTING_WOBBLE_C6);
    col_constant(SURFACE_PAINTING_WOBBLE_C7);
    col_constant(SURFACE_PAINTING_WOBBLE_C8);
    col_constant(SURFACE_PAINTING_WOBBLE_C9);
    col_constant(SURFACE_PAINTING_WOBBLE_CA);
    col_constant(SURFACE_PAINTING_WOBBLE_CB);
    col_constant(SURFACE_PAINTING_WOBBLE_CC);
    col_constant(SURFACE_PAINTING_WOBBLE_CD);
    col_constant(SURFACE_PAINTING_WOBBLE_CE);
    col_constant(SURFACE_PAINTING_WOBBLE_CF);
    col_constant(SURFACE_PAINTING_WOBBLE_D0);
    col_constant(SURFACE_PAINTING_WOBBLE_D1);
    col_constant(SURFACE_PAINTING_WOBBLE_D2);
    col_constant(SURFACE_PAINTING_WARP_D3);
    col_constant(SURFACE_PAINTING_WARP_D4);
    col_constant(SURFACE_PAINTING_WARP_D5);
    col_constant(SURFACE_PAINTING_WARP_D6);
    col_constant(SURFACE_PAINTING_WARP_D7);
    col_constant(SURFACE_PAINTING_WARP_D8);
    col_constant(SURFACE_PAINTING_WARP_D9);
    col_constant(SURFACE_PAINTING_WARP_DA);
    col_constant(SURFACE_PAINTING_WARP_DB);
    col_constant(SURFACE_PAINTING_WARP_DC);
    col_constant(SURFACE_PAINTING_WARP_DD);
    col_constant(SURFACE_PAINTING_WARP_DE);
    col_constant(SURFACE_PAINTING_WARP_DF);
    col_constant(SURFACE_PAINTING_WARP_E0);
    col_constant(SURFACE_PAINTING_WARP_E1);
    col_constant(SURFACE_PAINTING_WARP_E2);
    col_constant(SURFACE_PAINTING_WARP_E3);
    col_constant(SURFACE_PAINTING_WARP_E4);
    col_constant(SURFACE_PAINTING_WARP_E5);
    col_constant(SURFACE_PAINTING_WARP_E6);
    col_constant(SURFACE_PAINTING_WARP_E7);
    col_constant(SURFACE_PAINTING_WARP_E8);
    col_constant(SURFACE_PAINTING_WARP_E9);
    col_constant(SURFACE_PAINTING_WARP_EA);
    col_constant(SURFACE_PAINTING_WARP_EB);
    col_constant(SURFACE_PAINTING_WARP_EC);
    col_constant(SURFACE_PAINTING_WARP_ED);
    col_constant(SURFACE_PAINTING_WARP_EE);
    col_constant(SURFACE_PAINTING_WARP_EF);
    col_constant(SURFACE_PAINTING_WARP_F0);
    col_constant(SURFACE_PAINTING_WARP_F1);
    col_constant(SURFACE_PAINTING_WARP_F2);
    col_constant(SURFACE_PAINTING_WARP_F3);
    col_constant(SURFACE_TTC_PAINTING_1);
    col_constant(SURFACE_TTC_PAINTING_2);
    col_constant(SURFACE_TTC_PAINTING_3);
    col_constant(SURFACE_PAINTING_WARP_F7);
    col_constant(SURFACE_PAINTING_WARP_F8);
    col_constant(SURFACE_PAINTING_WARP_F9);
    col_constant(SURFACE_PAINTING_WARP_FA);
    col_constant(SURFACE_PAINTING_WARP_FB);
    col_constant(SURFACE_PAINTING_WARP_FC);
    col_constant(SURFACE_WOBBLING_WARP);
    col_constant(SURFACE_TRAPDOOR);

    // Surface class constants
    col_constant(SURFACE_CLASS_DEFAULT);
    col_constant(SURFACE_CLASS_VERY_SLIPPERY);
    col_constant(SURFACE_CLASS_SLIPPERY);
    col_constant(SURFACE_CLASS_NOT_SLIPPERY);

    // Surface flag constants
    col_constant(SURFACE_FLAG_DYNAMIC);
    col_constant(SURFACE_FLAG_NO_CAM_COLLISION);
    col_constant(SURFACE_FLAG_X_PROJECTION);

    // Specials
    col_constant(special_null_start);
    col_constant(special_yellow_coin);
    col_constant(special_yellow_coin_2);
    col_constant(special_unknown_3);
    col_constant(special_boo);
    col_constant(special_unknown_5);
    col_constant(special_lll_moving_octagonal_mesh_platform);
    col_constant(special_snow_ball);
    col_constant(special_lll_drawbridge_spawner);
    col_constant(special_empty_9);
    col_constant(special_lll_rotating_block_with_fire_bars);
    col_constant(special_lll_floating_wood_bridge);
    col_constant(special_tumbling_platform);
    col_constant(special_lll_rotating_hexagonal_ring);
    col_constant(special_lll_sinking_rectangular_platform);
    col_constant(special_lll_sinking_square_platforms);
    col_constant(special_lll_tilting_square_platform);
    col_constant(special_lll_bowser_puzzle);
    col_constant(special_mr_i);
    col_constant(special_small_bully);
    col_constant(special_big_bully);
    col_constant(special_empty_21);
    col_constant(special_empty_22);
    col_constant(special_empty_23);
    col_constant(special_empty_24);
    col_constant(special_empty_25);
    col_constant(special_moving_blue_coin);
    col_constant(special_jrb_chest);
    col_constant(special_water_ring);
    col_constant(special_mine);
    col_constant(special_empty_30);
    col_constant(special_empty_31);
    col_constant(special_butterfly);
    col_constant(special_bowser);
    col_constant(special_wf_rotating_wooden_platform);
    col_constant(special_small_bomp);
    col_constant(special_wf_sliding_platform);
    col_constant(special_tower_platform_group);
    col_constant(special_rotating_counter_clockwise);
    col_constant(special_wf_tumbling_bridge);
    col_constant(special_large_bomp);
    col_constant(special_level_geo_03);
    col_constant(special_level_geo_04);
    col_constant(special_level_geo_05);
    col_constant(special_level_geo_06);
    col_constant(special_level_geo_07);
    col_constant(special_level_geo_08);
    col_constant(special_level_geo_09);
    col_constant(special_level_geo_0A);
    col_constant(special_level_geo_0B);
    col_constant(special_level_geo_0C);
    col_constant(special_level_geo_0D);
    col_constant(special_level_geo_0E);
    col_constant(special_level_geo_0F);
    col_constant(special_level_geo_10);
    col_constant(special_level_geo_11);
    col_constant(special_level_geo_12);
    col_constant(special_level_geo_13);
    col_constant(special_level_geo_14);
    col_constant(special_level_geo_15);
    col_constant(special_level_geo_16);
    col_constant(special_bubble_tree);
    col_constant(special_spiky_tree);
    col_constant(special_snow_tree);
    col_constant(special_unknown_tree);
    col_constant(special_palm_tree);
    col_constant(special_wooden_door);
    col_constant(special_haunted_door);
    col_constant(special_unknown_door);
    col_constant(special_metal_door);
    col_constant(special_hmc_door);
    col_constant(special_unknown2_door);
    col_constant(special_wooden_door_warp);
    col_constant(special_unknown1_door_warp);
    col_constant(special_metal_door_warp);
    col_constant(special_unknown2_door_warp);
    col_constant(special_unknown3_door_warp);
    col_constant(special_castle_door_warp);
    col_constant(special_castle_door);
    col_constant(special_0stars_door);
    col_constant(special_1star_door);
    col_constant(special_3star_door);
    col_constant(special_key_door);
    col_constant(special_null_end);

    *found = false;
    return 0;
}

static s16 ParseColSymbolArg(GfxData* aGfxData, DataNode<Collision>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // Constants
    bool constantFound = false;
    s64 constantValue = DynOS_Col_ParseConstants(_Arg, &constantFound);
    if (constantFound) {
        return constantValue;
    }

    // Recursive descent parsing
    bool rdSuccess = false;
    s64 rdValue = DynOS_RecursiveDescent_Parse(_Arg.begin(), &rdSuccess, DynOS_Col_ParseConstants);
    if (rdSuccess) {
        return rdValue;
    }

    // Unknown
    PrintError("  ERROR: Unknown col arg: %s", _Arg.begin());
    return 0;
}

#define col_symbol_0(symb)                       \
    if (_Symbol == #symb) {                      \
        Collision _Cl[] = { symb() };            \
        memcpy(aHead, _Cl, sizeof(_Cl));         \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0])); \
        return;                                  \
    }

#define col_symbol_1(symb)                                           \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        Collision _Cl[] = { symb(_Arg0) };                           \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_2(symb)                                           \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        Collision _Cl[] = { symb(_Arg0, _Arg1) };                    \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_3(symb)                                           \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2) };             \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_4(symb)                                           \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg3 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };      \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_5(symb)                                             \
    if (_Symbol == #symb) {                                            \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);   \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);   \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);   \
        s16 _Arg3 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);   \
        s16 _Arg4 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);   \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4) }; \
        memcpy(aHead, _Cl, sizeof(_Cl));                               \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                       \
        return;                                                        \
    }

#define col_symbol_6(symb)                                                    \
    if (_Symbol == #symb) {                                                   \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg3 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg4 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg5 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) }; \
        memcpy(aHead, _Cl, sizeof(_Cl));                                      \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                              \
        return;                                                               \
    }

static void ParseCollisionSymbol(GfxData* aGfxData, DataNode<Collision>* aNode, Collision*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    col_symbol_0(COL_INIT);
    col_symbol_1(COL_VERTEX_INIT);
    col_symbol_3(COL_VERTEX);
    col_symbol_2(COL_TRI_INIT);
    col_symbol_3(COL_TRI);
    col_symbol_4(COL_TRI_SPECIAL);
    col_symbol_0(COL_TRI_STOP);
    col_symbol_0(COL_END);
    col_symbol_1(COL_SPECIAL_INIT);
    col_symbol_1(COL_WATER_BOX_INIT);
    col_symbol_6(COL_WATER_BOX);
    col_symbol_4(SPECIAL_OBJECT);
    col_symbol_5(SPECIAL_OBJECT_WITH_YAW);
    col_symbol_6(SPECIAL_OBJECT_WITH_YAW_AND_PARAM);

    // Unknown
    PrintError("  ERROR: Unknown col symbol: %s", _Symbol.begin());
}

DataNode<Collision>* DynOS_Col_Parse(GfxData* aGfxData, DataNode<Collision>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Collision data
    aNode->mData = New<Collision>(aNode->mTokens.Count() * COLLISION_SIZE_PER_TOKEN);
    Collision* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseCollisionSymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

  /////////////
 // Writing //
/////////////

void DynOS_Col_Write(FILE* aFile, GfxData* aGfxData, DataNode<Collision> *aNode) {
    if (!aNode->mData) return;

    // Name
    WriteBytes<u8>(aFile, DATA_TYPE_COLLISION);
    aNode->mName.Write(aFile);

    // Data
    WriteBytes<u32>(aFile, aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        WriteBytes<Collision>(aFile, aNode->mData[i]);
    }
}

static bool DynOS_Col_WriteBinary(const SysPath &aOutputFilename, GfxData *aGfxData, DataNode<Collision>* _Node) {
    FILE *_File = fopen(aOutputFilename.c_str(), "wb");
    if (!_File) {
        PrintError("  ERROR: Unable to create file \"%s\"", aOutputFilename.c_str());
        return false;
    }

    DynOS_Col_Write(_File, aGfxData, _Node);

    fclose(_File);
    return true;
}

  /////////////
 // Loading //
/////////////

DataNode<Collision>* DynOS_Col_Load(FILE *aFile, GfxData *aGfxData) {
    DataNode<Collision> *_Node = New<DataNode<Collision>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = ReadBytes<u32>(aFile);
    _Node->mData = New<Collision>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = ReadBytes<Collision>(aFile);
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mCollisions.Add(_Node);
    }

    return _Node;
}

DataNode<Collision>* DynOS_Col_LoadFromBinary(const SysPath &aPackFolder, const char *aCollisionName) {
    // Load data from binary file
    DataNode<Collision>* collisionNode = NULL;
    SysPath _Filename = fstring("%s/%s.col", aPackFolder.begin(), aCollisionName);
    FILE *_File = fopen(_Filename.c_str(), "rb");
    if (_File) {
        // backwards compatibility
        //long prevPos = ftell(_File);
        u8 type = ReadBytes<u8>(_File);
        //if (type != DATA_TYPE_COLLISION) { fseek(_File, prevPos, SEEK_SET); }
        if (type == DATA_TYPE_COLLISION) {
            collisionNode = DynOS_Col_Load(_File, NULL);
        }
        // DO NOT COMMIT - figure out wtf is going on
        fclose(_File);
    }

    return collisionNode;
}

  //////////////
 // Generate //
//////////////

void DynOS_Col_Generate(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    for (auto &_ColNode : _GfxData->mCollisions) {
        String _ColRootName = _ColNode->mName;

        // If there is an existing binary file for this collision, skip and go to the next actor
        SysPath _ColFilename = fstring("%s/%s.col", aPackFolder.c_str(), _ColRootName.begin());
        if (fs_sys_file_exists(_ColFilename.c_str())) {
            continue;
        }

        // Init
        _GfxData->mErrorCount = 0;
        _GfxData->mLoadIndex = 0;

        // Parse data
        PrintNoNewLine("%s.col: Model identifier: %X - Processing... ", _ColRootName.begin(), _GfxData->mModelIdentifier);
        DynOS_Col_Parse(_GfxData, _ColNode, true);

        // Write if no error
        if (_GfxData->mErrorCount == 0) {
            DynOS_Col_WriteBinary(_ColFilename, _GfxData, _ColNode);
        } else {
            Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
        }

        // Clear data pointers
        ClearGfxDataNodes(_GfxData->mCollisions);
    }
}
