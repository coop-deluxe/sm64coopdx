#include "dynos.cpp.h"

extern "C" {
#include "include/level_misc_macros.h"
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnarrowing"

  /////////////
 // Parsing //
/////////////

#define TRAJECTORY_SIZE_PER_TOKEN 4

#define trajectory_constant(x) if (_Arg == #x) { return (s64) (x); }
static s64 ParseTrajectorySymbolArg(GfxData* aGfxData, DataNode<Trajectory>* aNode, u64& aTokenIndex) {
    const String& _Arg = aNode->mTokens[aTokenIndex++];

    // Integers
    bool integerFound = false;
    s64 integerValue = DynOS_Misc_ParseInteger(_Arg, &integerFound);
    if (integerFound) {
        return integerValue;
    }

    // Other constants
    trajectory_constant(NULL);

    // Unknown
    PrintDataError("  ERROR: Unknown trajectory arg: %s", _Arg.begin());
    return 0;
}

#define trajectory_symbol_0(symb)                \
    if (_Symbol == #symb) {                      \
        Trajectory _Tr[] = { symb() };           \
        memcpy(aHead, _Tr, sizeof(_Tr));         \
        aHead += (sizeof(_Tr) / sizeof(_Tr[0])); \
        return;                                  \
    }

#define trajectory_symbol_4(symb)                                           \
    if (_Symbol == #symb) {                                                 \
        s64 _Arg0 = ParseTrajectorySymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg1 = ParseTrajectorySymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg2 = ParseTrajectorySymbolArg(aGfxData, aNode, aTokenIndex); \
        s64 _Arg3 = ParseTrajectorySymbolArg(aGfxData, aNode, aTokenIndex); \
        Trajectory _Tr[] = { symb(_Arg0, _Arg1, _Arg2, _Arg3) };            \
        memcpy(aHead, _Tr, sizeof(_Tr));                                    \
        aHead += (sizeof(_Tr) / sizeof(_Tr[0]));                            \
        return;                                                             \
    }

static void ParseTrajectorySymbol(GfxData* aGfxData, DataNode<Trajectory>* aNode, Trajectory*& aHead, u64& aTokenIndex, Array<u64>& aSwitchNodes) {
    const String& _Symbol = aNode->mTokens[aTokenIndex++];

    trajectory_symbol_4(TRAJECTORY_POS);
    trajectory_symbol_0(TRAJECTORY_END);

    // Unknown
    PrintDataError("  ERROR: Unknown trajectory symbol: %s", _Symbol.begin());
}

DataNode<Trajectory>* DynOS_Trajectory_Parse(GfxData* aGfxData, DataNode<Trajectory>* aNode, bool aDisplayPercent) {
    if (aNode->mData) return aNode;

    // Trajectory data
    aNode->mData = New<Trajectory>(aNode->mTokens.Count() * TRAJECTORY_SIZE_PER_TOKEN);
    Trajectory* _Head = aNode->mData;
    Array<u64> _SwitchNodes;
    for (u64 _TokenIndex = 0; _TokenIndex < aNode->mTokens.Count();) { // Don't increment _TokenIndex here!
        ParseTrajectorySymbol(aGfxData, aNode, _Head, _TokenIndex, _SwitchNodes);
        if (aDisplayPercent && aGfxData->mErrorCount == 0) { PrintNoNewLine("%3d%%\b\b\b\b", (s32) (_TokenIndex * 100) / aNode->mTokens.Count()); }
    }
    if (aDisplayPercent && aGfxData->mErrorCount == 0) { Print("100%%"); }
    aNode->mSize = (u32)(_Head - aNode->mData);
    aNode->mLoadIndex = aGfxData->mLoadIndex++;
    return aNode;
}

#pragma GCC diagnostic pop

  /////////////
 // Writing //
/////////////

void DynOS_Trajectory_Write(BinFile* aFile, GfxData* aGfxData, DataNode<Trajectory> *aNode) {
    if (!aNode->mData) return;

    // Name
    aFile->Write<u8>(DATA_TYPE_TRAJECTORY);
    aNode->mName.Write(aFile);

    // Data
    aFile->Write<u32>(aNode->mSize);
    for (u32 i = 0; i != aNode->mSize; ++i) {
        aFile->Write<Trajectory>(aNode->mData[i]);
    }
}

  /////////////
 // Reading //
/////////////

DataNode<Trajectory>* DynOS_Trajectory_Load(BinFile *aFile, GfxData *aGfxData) {
    DataNode<Trajectory> *_Node = New<DataNode<Trajectory>>();

    // Name
    _Node->mName.Read(aFile);

    // Data
    _Node->mSize = aFile->Read<u32>();
    _Node->mData = New<Trajectory>(_Node->mSize);
    for (u32 i = 0; i != _Node->mSize; ++i) {
        _Node->mData[i] = aFile->Read<Trajectory>();
    }

    // Add it
    if (aGfxData != NULL) {
        aGfxData->mTrajectories.Add(_Node);
    }

    return _Node;
}
