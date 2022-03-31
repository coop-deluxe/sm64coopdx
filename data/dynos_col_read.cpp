#include "dynos.cpp.h"

extern "C" {
#include "include/surface_terrains.h"
}

// Free data pointers, but keep nodes and tokens intact
// Delete nodes generated from GfxDynCmds
template <typename T>
static void ClearColDataNodes(DataNodes<T> &aDataNodes) {
    for (s32 i = aDataNodes.Count(); i != 0; --i) {
        Delete(aDataNodes[i - 1]->mData);
    }
}

//
// Parse collision file
//

#define COLLISION_SIZE_PER_TOKEN 4

#define col_constant(x) if (_Arg == #x) { return (s16) (x); }
static s16 ParseColSymbolArg(GfxData* aGfxData, DataNode<Collision>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

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

    // Other constants
    col_constant(NULL);

    // Integers
    s32 x;
    if ((_Arg[1] == 'x' && sscanf(_Arg.begin(), "%x", &x) == 1) || (sscanf(_Arg.begin(), "%d", &x) == 1)) {
        return (s16) x;
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

#define col_symbol_1(symb, n)                                        \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }       \
        Collision _Cl[] = { symb(_Arg0) };                           \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_2(symb, n)                                        \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }       \
        Collision _Cl[] = { symb(_Arg0, _Arg1) };                    \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_3(symb, n)                                        \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }       \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2) };             \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_4(symb, n)                                        \
    if (_Symbol == #symb) {                                          \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        s16 _Arg3 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex); \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }       \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };      \
        memcpy(aHead, _Cl, sizeof(_Cl));                             \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                     \
        return;                                                      \
    }

#define col_symbol_6(symb, n)                                                 \
    if (_Symbol == #symb) {                                                   \
        s16 _Arg0 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg1 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg2 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg3 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg4 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        s16 _Arg5 = ParseColSymbolArg(aGfxData, aNode, aTokenIndex);          \
        if (n != 0) { aGfxData->mPointerList.Add(aHead + n); }                \
        Collision _Cl[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3, _Arg4, _Arg5) }; \
        memcpy(aHead, _Cl, sizeof(_Cl));                                      \
        aHead += (sizeof(_Cl) / sizeof(_Cl[0]));                              \
        return;                                                               \
    }

static void ParseCollisionSymbol(GfxData* aGfxData, DataNode<Collision>* aNode, Collision*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    col_symbol_0(COL_INIT);
    col_symbol_1(COL_VERTEX_INIT, 0);
    col_symbol_3(COL_VERTEX, 0);
    col_symbol_2(COL_TRI_INIT, 0);
    col_symbol_3(COL_TRI, 0);
    col_symbol_4(COL_TRI_SPECIAL, 0);
    col_symbol_0(COL_TRI_STOP);
    col_symbol_0(COL_END);
    col_symbol_1(COL_SPECIAL_INIT, 0);
    col_symbol_1(COL_WATER_BOX_INIT, 0);
    col_symbol_6(COL_WATER_BOX, 0);

    // Unknown
    PrintError("  ERROR: Unknown col symbol: %s", _Symbol.begin());
}

static DataNode<Collision>* ParseCollisionData(GfxData* aGfxData, DataNode<Collision>* aNode, bool aDisplayPercent) {
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

static DataNode<Collision> *GetCollision(GfxData *aGfxData, const String& aGeoRoot) {
    for (DataNode<Collision> *_Node : aGfxData->mCollisions) {
        if (_Node->mName == aGeoRoot) {
            return _Node;
        }
    }
    return NULL;
}

bool DynOS_Col_GeneratePack(const SysPath &aPackFolder, Array<Pair<u64, String>> _ActorsFolders, GfxData *_GfxData) {
    bool generated = false;
    for (auto &_ColNode : _GfxData->mCollisions) {
        String _ColRootName = _ColNode->mName;
        DataNode<Collision> *_ColRoot = GetCollision(_GfxData, _ColRootName);
        if (_ColRoot != NULL) {

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
            ParseCollisionData(_GfxData, _ColRoot, true);

            // Write if no error
            if (_GfxData->mErrorCount == 0) {
                DynOS_Col_WriteBinary(_ColFilename, _GfxData, _ColRoot);
            } else {
                Print("  %u error(s): Unable to parse data", _GfxData->mErrorCount);
            }
            // Clear data pointers
            ClearColDataNodes(_GfxData->mCollisions);
            generated = true;
        }
    }
    return generated;
}
